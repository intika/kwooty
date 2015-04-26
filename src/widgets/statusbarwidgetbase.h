/***************************************************************************
 *   Copyright (C) 2011 by Xavier Lefage                                   *
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



#ifndef STATUSBARWIDGETBASE_H
#define STATUSBARWIDGETBASE_H

#include <QWidget>
#include <QHBoxLayout>

#include <KIconLoader>

#include "widgets/mystatusbar.h"

class StatusBarWidgetBase : public QWidget {

    Q_OBJECT

public:
    StatusBarWidgetBase(QWidget*, MyStatusBar::WidgetIdentity);
    MyStatusBar::WidgetIdentity getWidgetIdentity();


protected:

    void mouseDoubleClickEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    MyStatusBar::WidgetIdentity widgetIdentity;

    KIconLoader* iconLoader;
    QHBoxLayout* hBoxLayout;


private:

    void setupConnections();


Q_SIGNALS:

    void statusBarWidgetDblClickSignal(MyStatusBar::WidgetIdentity);
};

#endif // STATUSBARWIDGETBASE_H
