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


#include "servertabwidget.h"

#include <KDebug>
#include <KIcon>
#include <KInputDialog>

#include <QTabBar>
#include <QTabWidget>
#include <QUuid>

#include "preferences/preferencesserver.h"
#include "serverpreferenceswidget.h"
#include "preferences/kconfiggrouphandler.h"

#include "utility.h"
using namespace UtilityNamespace;


ServerTabWidget::ServerTabWidget(PreferencesServer* parent) : KTabWidget(parent) {


    this->preferencesServer = parent;

    // add a button to add backup server :
    this->newTab = new QToolButton(this);
    this->newTab->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->newTab->setIcon(KIcon("list-add"));
    this->newTab->setToolTip("Add a backup server");

    // add a button to remove backup server :
    this->closeTab = new QToolButton(this);
    this->closeTab->setToolButtonStyle(Qt::ToolButtonIconOnly);
    this->closeTab->setIcon(KIcon("list-remove"));
    this->closeTab->setToolTip("Remove current backup server");


    // set buttons to right and left corners :
    this->setCornerWidget(this->newTab, Qt::TopRightCorner);
    parent->layout()->addWidget(this);

    this->setCornerWidget(this->closeTab, Qt::TopLeftCorner);
    parent->layout()->addWidget(this);


    this->setupConnections();

}


void ServerTabWidget::setupConnections() {

    connect (this->newTab, SIGNAL(clicked (bool)), this, SLOT(newTabClickedSlot()));
    connect (this->closeTab, SIGNAL(clicked (bool)), this, SLOT(closeTabClickedSlot()));

    connect (this->tabBar(), SIGNAL(tabMoved (int, int)), this, SLOT(tabMovedSlot(int, int)));
    connect (this->tabBar(), SIGNAL(currentChanged (int)), this, SLOT(currentChangedSlot(int)));

    // save data asked from kConfigDialog :
    connect (this->preferencesServer, SIGNAL(saveDataSignal()), this, SLOT(saveDataSlot()));

    connect (this->tabBar(), SIGNAL(tabMoved (int, int)), this, SLOT(valueChangedSlot()));

}


void ServerTabWidget::addNewTab() {
    this->newTabClickedSlot(ServerTabWidget::DoNotAskServerName);
}


void ServerTabWidget::newTabClickedSlot(const ServerTabWidget::ServerNameQuery askServerName) {

    int tabNumbers = this->count();

    // if number of current tabs is < 5 allow to add a new backup server :
    if (tabNumbers < PreferencesServer::MAX_SERVERS) {

        QString tabText;
        QString iconStr;
        if (tabNumbers == MasterServer) {
            tabText = i18n("Main");
            iconStr = "applications-internet";
        }
        else {
            tabText = i18n("Backup %1", tabNumbers);
            iconStr = "document-save";

        }

        // ask server name :
        if (askServerName == ServerTabWidget::AskServerName) {

            QString input = KInputDialog::getText(i18n("Backup server name"), i18n("Please enter backup server name:"));
            if (!input.isEmpty()) {
                tabText = input;
           }

        }

        // if the backup server has already been created, search its name in settings :
        tabText = KConfigGroupHandler::getInstance()->tabName(tabNumbers, tabText);

        // add tab with new window widget :
        this->addTab(new ServerPreferencesWidget(this, this->preferencesServer, tabNumbers), tabText);
        this->setTabIcon(tabNumbers, KIcon(iconStr));

        this->setCurrentIndex(tabNumbers);
        this->enableDisableTabButtons();

        // update groupbox title according to its corresponding tab position :
        this->syncGroupBoxTitle();

        // enable apply button to notify changes :
        this->valueChangedSlot();

    }

}


void ServerTabWidget::closeTabClickedSlot() {


    int currentIndex = this->currentIndex();

    if (currentIndex != 0) {

        // delete the widget and the corresponding tab :
        kDebug() << currentIndex;
        this->deleteAndRemoveTab(currentIndex);
        this->enableDisableTabButtons();

    }

    // update groupbox title according to its corresponding tab position :
    //this->syncGroupBoxTitle();

}


void ServerTabWidget::deleteAndRemoveTab(const int& index) {

    // get the widget to delete :
    QWidget* currentWidget = this->widget(index);

    // remove the tab :
    this->removeTab(index);

    // delete the widget :
    delete currentWidget;

    // update groupbox title according to its corresponding tab position :
    this->syncGroupBoxTitle();

    // enable apply button to notify changes :
    this->valueChangedSlot();
}




void ServerTabWidget::tabMovedSlot(int from, int to) {

    // the master server tab must stay at the first position :
    if (from == MasterServer && to == 1) {
        this->tabBar()->moveTab(to, from);
    }

    this->syncGroupBoxTitle();

}

void ServerTabWidget::currentChangedSlot(int index) {

    // the master server tab must stay at the first position :
    if (index == MasterServer) {
        this->setMovable(false);
    }
    else {
        this->setMovable(true);
    }

}


void ServerTabWidget::enableDisableTabButtons() {

    this->newTab->setEnabled(true);
    this->closeTab->setEnabled(true);

    // do not allow to add more than 5 servers :
    if (this->count() == PreferencesServer::MAX_SERVERS) {
        this->newTab->setEnabled(false);
    }
    // do not allow to remove the master server :
    else if (this->count() == 1) {
        this->closeTab->setEnabled(false);
    }


}


void ServerTabWidget::syncGroupBoxTitle() {

    int tabNumber = this->count();

    for (int i = 1; i < tabNumber; i++) {
        ((ServerPreferencesWidget*)this->widget(i))->setGroupBoxTitle(i);
    }

}



void ServerTabWidget::saveDataSlot() {

    int tabNumber = this->count();

    // delete all previous server settings entries :
    for (int i = 0; i < PreferencesServer::MAX_SERVERS; i++) {
        KConfigGroupHandler::getInstance()->removeServerSettings(i);
    }

    // save the new ones :
    for (int i = 0; i < tabNumber; i++) {

        ServerData serverData = ((ServerPreferencesWidget*)this->widget(i))->getData();
        serverData.setServerId(i);

        kDebug() << this->tabText(i);
        serverData.setServerName(this->tabText(i));

        KConfigGroupHandler::getInstance()->writeServerSettings(i, serverData);

    }

    // save the current number of servers :
    KConfigGroupHandler::getInstance()->writeServerNumberSettings(tabNumber);

}




void ServerTabWidget::valueChangedSlot() {
    preferencesServer->kcfg_serverChangesNotify->setText(QUuid::createUuid().toString());
}
