/**
 ******************************************************************************
 *
 * @file       opmap_zoom_slider_widget.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup OPMapPlugin Tau Labs Map Plugin
 * @{
 * @brief Tau Labs map plugin
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

#ifndef OPMAP_ZOOM_SLIDER_WIDGET_H
#define OPMAP_ZOOM_SLIDER_WIDGET_H

#include <QWidget>

namespace Ui {
class opmap_zoom_slider_widget;
}

class opmap_zoom_slider_widget : public QWidget
{
    Q_OBJECT

public:
    explicit opmap_zoom_slider_widget(QWidget *parent = nullptr);
    ~opmap_zoom_slider_widget();

private:
    Ui::opmap_zoom_slider_widget *ui;
};

#endif // OPMAP_ZOOM_SLIDER_WIDGET_H
