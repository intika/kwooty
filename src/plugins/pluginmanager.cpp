/***************************************************************************
 *   Copyright (C) 2010 by Xavier Lefage                                   *
 *   xavier.kwooty@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "pluginmanager.h"

#include <KDebug>
#include <KComponentData>
#include <KServiceTypeTrader>

#include "mainwindow.h"


PluginManager::PluginManager(MainWindow* core) : QObject(core)
{

    this->core = core;

    // retrieve all plugins associated to kwooty :
    QString pluginVersionQuery = QString("[X-Kwooty-Plugin-Version] == %1").arg(KWOOTY_PLUGIN_VERSION);
    this->pluginInfoList = KPluginInfo::fromServices(KServiceTypeTrader::self()->query("Kwooty/Plugin", pluginVersionQuery));

}


PluginManager::~PluginManager() {

}


void PluginManager::loadPlugins() {


    KConfigGroup kConfigGroup = KGlobal::config()->group("Plugins");

    foreach (const KPluginInfo& currentPluginInfo, this->pluginInfoList) {

        // look in config file if the plugin have to be loaded :
        QString entryReadStr = kConfigGroup.readEntry(QString("%1Enabled").arg(currentPluginInfo.pluginName()), "");

        bool pluginEnable;

        // if no config previously stored found, check if plugin has to be loaded by default :
        if (entryReadStr == "") {

            pluginEnable = currentPluginInfo.isPluginEnabledByDefault();
        }
        // config has been found, enable or disable plugin accordingly :
        else {

            pluginEnable = kConfigGroup.readEntry<bool>(QString("%1Enabled").arg(currentPluginInfo.pluginName()), true);

        }

        //kDebug() << "plugin enabled ? :" << pluginEnable;

        // load plugin :
        if (pluginEnable && !this->loadedInfoPluginMap.contains(currentPluginInfo)) {
            this->loadCurrentPlugin(currentPluginInfo);
        }
        // unload plugin :
        else if (!pluginEnable && this->loadedInfoPluginMap.contains(currentPluginInfo)) {
            this->unloadCurrentPlugin(currentPluginInfo);
        }

    }

}


void PluginManager::loadCurrentPlugin(const KPluginInfo& currentPluginInfo) {

    KPluginFactory* factory = KPluginLoader(currentPluginInfo.service()->library()).factory();
    if (factory) {

        // instantiate plugin :
        Plugin* plugin = factory->create<Plugin>(this);

        if (plugin) {

            //kDebug() << "Load plugin:" << currentPluginInfo.service()->name();

            // give full access to plugin :
            plugin->setCore(this->core);

            // load current plugin :
            plugin->load();

            this->loadedInfoPluginMap.insert(currentPluginInfo, plugin);


        } else {
            kDebug() << "Plugin can not be created:" << currentPluginInfo.service()->library();
        }

    }
    // factory is null :
    else {
        kDebug() << "KPluginFactory could not load the plugin:" << currentPluginInfo.service()->library();

    }

}


void PluginManager::unloadCurrentPlugin(const KPluginInfo& currentPluginInfo) {

    // remove plugin from map :
    Plugin* pluginToUnload = this->loadedInfoPluginMap.take(currentPluginInfo);

    // check plugin validity before unload :
    if (pluginToUnload) {

        pluginToUnload->unload();
        delete pluginToUnload;

    }

}





void PluginManager::configCommittedSlot(const QByteArray& componentName) {

    // look for plugin whose config has been updated :
    foreach (Plugin* currentPlugin, this->loadedInfoPluginMap.values()) {

        // corresponding plugin has been found :
        if (componentName == currentPlugin->componentData().componentName()) {

            // update settings to current plugin :
            currentPlugin->configUpdated();
            break;
        }

    }

}



QList<KPluginInfo> PluginManager::getPluginInfoList() {

    return this->pluginInfoList;
}




