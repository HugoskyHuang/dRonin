#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "openpilot.h"
#include "pios.h"
#include "misc_math.h"
#include "smoothcontrol.h"

struct smoothcontrol_axis_state {
	// Last known signal value. Needed to detect change.
	float signal;

	// Current state of axis.
	float current;

	// Amount of differential per step of integration.
	float differential;

	// Stores a time-out when to stop predicting. Unit is integrator ticks.
	uint8_t integrator_timeout;

	// Which conditioning algorithm.
	uint8_t mode;
};

struct smoothcontrol_state_internal {

	// Maximum ticks to integrate. Calculate value from dT and constant. Unit is ticks.
	uint8_t time_bomb;

	// Semaphore for cheapskates.
	bool ringer;

	// Whole state tick counter
	uint8_t tick_counter;

	// Control interval determined by the ringer.
	uint8_t control_interval;

	// Duty cycle to use.
	float duty_cycle;

	// RPY+Thrust.
	struct smoothcontrol_axis_state axis[4];
};

// Ran on signal change, recalculates the diffs and timeouts for the specific mode.
static void smoothcontrol_update(smoothcontrol_state state, struct smoothcontrol_axis_state *axis, const float new_signal)
{
	float signal_diff = new_signal - axis->signal;
	float cycles = MIN((float)state->control_interval * state->duty_cycle, state->control_interval);

	switch(axis->mode) {
		default:
			// Override any crap values.
			axis->mode = SMOOTHCONTROL_NONE;
		case SMOOTHCONTROL_NONE:
			// Doesn't do anything in the integrator.
			break;

		// icee's proposal, creates chamfered steps with signal prediction
		case SMOOTHCONTROL_NORMAL:
			axis->differential = signal_diff * SMOOTHCONTROL_PREDICTOR_SLOPE / (float)state->control_interval;
			axis->current = axis->signal + signal_diff * SMOOTHCONTROL_CHAMFER_START;
			axis->integrator_timeout = (uint8_t)cycles;
			break;

		case SMOOTHCONTROL_LINEAR:
			axis->differential = (new_signal - axis->current) / cycles;
			axis->integrator_timeout = (uint8_t)cycles;
			break;
	}

	axis->signal = new_signal;
}

// Resets the axis state.
void smoothcontrol_reinit(smoothcontrol_state state, uint8_t axis_num, float new_signal)
{
	PIOS_Assert(state);

	// Prevent integrating when stick scale changes.
	state->axis[axis_num].differential = 0;
	state->axis[axis_num].signal = new_signal;
	state->axis[axis_num].current = new_signal;
}

// Resets the thrust state.
void smoothcontrol_reinit_thrust(smoothcontrol_state state, float new_signal)
{
	smoothcontrol_reinit(state, 3, new_signal);
}

// Sets mode for an axis.
void smoothcontrol_set_mode(smoothcontrol_state state, uint8_t axis_num, uint8_t mode, uint8_t duty_cycle)
{
	PIOS_Assert(state && axis_num <= 3);
	state->duty_cycle = bound_min_max((float)duty_cycle, 0, 100) / 100.0f;
	smoothcontrol_reinit(state, axis_num, state->axis[axis_num].signal);
}

// Processes the signal, if internal state allows it.
void smoothcontrol_run(smoothcontrol_state state, uint8_t axis_num, float *new_signal)
{
	PIOS_Assert(state && axis_num <= 3);

	struct smoothcontrol_axis_state *axis = &state->axis[axis_num];

	// No mode, bypass.
	if(axis->mode == SMOOTHCONTROL_NONE) return;

	if(!state->tick_counter) {
		// Manual control updated, do stuff
		smoothcontrol_update(state, axis, *new_signal);
	}

	if(state->tick_counter < axis->integrator_timeout && state->tick_counter < state->time_bomb) {
		// Don't fiddle with first value after update.
		if(state->tick_counter > 0)
			axis->current += axis->differential;
	} else {
		// If we passed the timebomb, force the receiver signal, too.
		if(state->tick_counter >= state->time_bomb) axis->current = *new_signal;
	}

	*new_signal = axis->current;
}

// Separate handling of thrust.
void smoothcontrol_run_thrust(smoothcontrol_state state, float *new_signal)
{
	/* The 0 on zero throttle causes a huge blip when throttling up, so
	 * we need to handle it separately.  Also, reset the state, if zero
	 * throttle is requested, so that none of the modes can keep it
	 * non-zero.
	 */

	if (*new_signal == 0 || *new_signal != *new_signal) {
		smoothcontrol_reinit(state, 3, 0);
	} else {
		bool sign = *new_signal > 0;

		smoothcontrol_run(state, 3, new_signal);

		// If prediction undershoots while original signal is positive
		// bound it to zero.

		bool new_sign = *new_signal > 0;

		if (sign != new_sign) {
			if (sign) {
				*new_signal = 0.00001f;
			} else {
				*new_signal = -0.00001f;
			}
		}
	}
}

// Advances the tick counters.
void smoothcontrol_next(smoothcontrol_state state)
{
	PIOS_Assert(state);

	if(state->tick_counter < 255) state->tick_counter++;

	// This function is supposed to get called at the end of the stabilization loop.
	// If MCC rang the ringer meanwhile, ticks will be at zero next loop, as expected.
	if(state->ringer) {
		int x = ((int)state->control_interval + (int)state->tick_counter) >> 1;
		state->control_interval = (uint8_t)MIN(x, 255);
		state->tick_counter = 0;

		state->ringer = false;
	}
}

// To tell us the dT, to calculate the time bomb for the integrator.
void smoothcontrol_update_dT(smoothcontrol_state state, float dT)
{
	PIOS_Assert(state);
	state->time_bomb = (uint8_t)(SMOOTHCONTROL_TIMEBOMB / 1000.0f / dT);
}

// Duh.
void smoothcontrol_initialize(smoothcontrol_state *state)
{
	PIOS_Assert(state);

	if(!*state) {
		*state = PIOS_malloc_no_dma(sizeof(**state));
		PIOS_Assert(*state);
		memset(*state, 0, sizeof(**state));
	}
}

bool* smoothcontrol_get_ringer(smoothcontrol_state state)
{
	PIOS_Assert(state);
	return &state->ringer;
}
