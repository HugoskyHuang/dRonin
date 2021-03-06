/**
 ******************************************************************************
 *
 * @file       welcomeplugin.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 *             Parts by Nokia Corporation (qt-info@nokia.com) Copyright (C) 2009.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup WelcomePlugin Welcome Plugin
 * @{
 * @brief The GCS Welcome plugin
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

#ifndef WELCOMEPLUGIN_H
#define WELCOMEPLUGIN_H

#include <coreplugin/iconfigurableplugin.h>

namespace Welcome {

class WelcomeMode;

namespace Internal {

    class WelcomePlugin : public ExtensionSystem::IPlugin
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.dronin.plugins.Welcome")
    public:
        WelcomePlugin();
        ~WelcomePlugin();

        bool initialize(const QStringList &arguments, QString *error_message);

        void extensionsInitialized();

    private:
        WelcomeMode *m_welcomeMode;
    };

} // namespace Welcome
} // namespace Internal

#endif // WELCOMEPLUGIN_H
