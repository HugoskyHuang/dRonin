/**
 ******************************************************************************
 *
 * @file       brainconfiguration.h
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2014
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup Boards_BrainFPV BrainFPV boards support Plugin
 * @{
 * @brief Plugin to support boards by BrainFPV LLC
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

#ifndef BRAINRE1CONFIGURATION_H
#define BRAINRE1CONFIGURATION_H

#include <QPixmap>
#include "uavobjectwidgetutils/configtaskwidget.h"
#include "hwbrainre1.h"

namespace Ui {
class BrainRE1Configuration;
}

class BrainRE1Configuration : public ConfigTaskWidget
{
    Q_OBJECT

public:
    explicit BrainRE1Configuration(QWidget *parent = nullptr);
    ~BrainRE1Configuration();

private slots:
    void widgetsContentsChanged();
    void generateILapID();
    void generateTrackmateID();
    void mpChanged(int idx);
    void extMagChanged(int idx);

private:
    Ui::BrainRE1Configuration *ui;
    HwBrainRE1 *re1_settings_obj;

    int generateRandomNumber(int max);
};

#endif // BRAINRE1CONFIGURATION_H
