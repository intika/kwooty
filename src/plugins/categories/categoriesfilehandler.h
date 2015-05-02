/***************************************************************************
 *   Copyright (C) 2012 by Xavier Lefage                                   *
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

#ifndef CATEGORIESFILEHANDLER_H
#define CATEGORIESFILEHANDLER_H

#include <QObject>
#include <QStandardItemModel>
#include <QXmlStreamReader>

class CategoriesModel;

class CategoriesFileHandler : public QObject
{

    Q_OBJECT

public:

    explicit CategoriesFileHandler(QObject *);
    CategoriesFileHandler();

    CategoriesModel *loadModelFromFile(QObject *);
    QStringList retrieveMainTypeList();
    void saveModelToFile(CategoriesModel *);
    void addListToModel(CategoriesModel *, const QStringList &);
    void reloadModel(CategoriesModel *);

private:

    void fillModel(CategoriesModel *);
    QString retrieveCategoriesFilePath();
    QString readNextCharacters(QXmlStreamReader &);
    bool isStartElement(QXmlStreamReader &, const QString &);
    bool isEndElement(QXmlStreamReader &, const QString &);
};

#endif // CATEGORIESFILEHANDLER_H
