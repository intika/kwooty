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


#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <KUrl>

#include <QObject>
#include <QFile>
#include "kwooty_export.h"

#include "utilities/utility.h"
using namespace UtilityNamespace;

class Core;
class CentralWidget;

class KWOOTY_EXPORT FileOperations : public QObject {

    Q_OBJECT

public:

    FileOperations(Core*);
    void openFile();
    void openFileWithFileMode(KUrl, UtilityNamespace::OpenFileMode);

    static bool isSplitFileFormat(const QFile&);

private:
    Core* core;
    void openUrl(KUrl, bool&, UtilityNamespace::OpenFileMode);


signals:

public slots:



};

#endif // FILEOPERATIONS_H

