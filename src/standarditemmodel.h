/***************************************************************************
 *   Copyright (C) 2009 by Xavier Lefage                                   *
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

#ifndef STANDARDITEMMODEL_H
#define STANDARDITEMMODEL_H


#include <QStandardItemModel>
#include <QStandardItem>
#include <QModelIndex>

#include "data/itemstatusdata.h"
#include "kwooty_export.h"
#include "utility.h"
using namespace UtilityNamespace;

class CentralWidget;
class ItemStatusData;
class NzbFileData;

class KWOOTY_EXPORT StandardItemModel : public QStandardItemModel {

    Q_OBJECT

public:
    StandardItemModel(CentralWidget* parent = 0);
    StandardItemModel();
    QStandardItem* getParentItem(const QModelIndex&);
    QStandardItem* getStateItemFromIndex(const QModelIndex&);
    QStandardItem* getFileNameItemFromIndex(const QModelIndex&);
    QStandardItem* getProgressItemFromIndex(const QModelIndex&);
    QStandardItem* getSizeItemFromIndex(const QModelIndex&);
    ItemStatusData getStatusDataFromIndex(const QModelIndex&);
    QStandardItem* getNzbItem(QStandardItem* item);
    NzbFileData getNzbFileDataFromIndex(const QModelIndex&);
    int getProgressValueFromIndex(const QModelIndex&);
    quint64 getSizeValueFromIndex(const QModelIndex&);
    QString getUuidStrFromIndex(const QModelIndex&);
    UtilityNamespace::ItemStatus getStatusFromStateItem(QStandardItem*) const;
    UtilityNamespace::ItemStatus getChildStatusFromNzbIndex(const QModelIndex&, int);
    QStandardItem* getFileNameItemFromRowNumber(const int&);
    void updateStateItem(QStandardItem*, const UtilityNamespace::ItemStatus);
    void updateProgressItem(const QModelIndex&, const int);
    void storeStatusDataToItem(QStandardItem*, const ItemStatusData&);
    bool isNzbItem(QStandardItem*);
    void updateNzbFileDataToItem(QStandardItem*, const NzbFileData&);
    void updateStatusDataFromIndex(const QModelIndex&, const ItemStatusData&);


private:
    QStandardItem* getColumnItem(const QModelIndex&, const int);


signals:
    void parentStatusItemChangedSignal(QStandardItem*, ItemStatusData);
    void childStatusItemChangedSignal(QStandardItem*, ItemStatusData);
    void parentProgressItemChangedSignal();


public slots:

private slots:


};

#endif // STANDARDITEMMODEL_H
