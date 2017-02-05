/**
 ******************************************************************************
 *
 * @file       uavobjectutilplugin.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @see        The GNU Public License (GPL) Version 3
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup UAVObjectUtilPlugin UAVObjectUtil Plugin
 * @{
 * @brief      The UAVUObjectUtil GCS plugin
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 3 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, see <http://www.gnu.org/licenses/>
 */

#include "uavobjectutilplugin.h"

UAVObjectUtilPlugin::UAVObjectUtilPlugin()
{
}

UAVObjectUtilPlugin::~UAVObjectUtilPlugin()
{
}

void UAVObjectUtilPlugin::extensionsInitialized()
{
}

bool UAVObjectUtilPlugin::initialize(const QStringList & arguments, QString * errorString)
{
	Q_UNUSED(arguments)
	Q_UNUSED(errorString)

	// Create manager and expose object
	UAVObjectUtilManager *objUtilMngr = new UAVObjectUtilManager();
	addAutoReleasedObject(objUtilMngr);

    return true;
}

void UAVObjectUtilPlugin::shutdown()
{
}
