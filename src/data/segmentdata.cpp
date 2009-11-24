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

#include "segmentdata.h"

#include "utility.h"
using namespace UtilityNamespace;

SegmentData::SegmentData()
{

}


SegmentData::SegmentData(const QString& bytes, const QString& number, const QString& part, const int status)
{
    this->bytes = bytes;
    this->number = number;
    this->part = part;
    this->status = status;
    this->articlePresence = Unknown;
}




void SegmentData::setBytes(const QString& bytes){
    this->bytes = bytes;
}

QString SegmentData::getBytes() const{
    return this->bytes;
}

void SegmentData::setNumber(const QString& number){
    this->number = number;
}

QString SegmentData::getNumber() const{
    return this->number;
}

void SegmentData::setPart(const QString& part){
    this->part = part;
}

QString SegmentData::getPart() const{
    return this->part;
}

int SegmentData::getStatus() const{
    return this->status;
}

void SegmentData::setStatus(const int status){
    this->status = status;
}

int SegmentData::getProgress() const{
    return this->progress;
}

void SegmentData::setProgress(const int progress){
    this->progress = progress;
}

void SegmentData::setElementInList(const quint32 elementInList){
    this->elementInList = elementInList;
}

quint32 SegmentData::getElementInList() const{
    return this->elementInList;
}

void SegmentData::setParentUniqueIdentifier(const QVariant& parentUniqueIdentifier){
    this->parentUniqueIdentifier = parentUniqueIdentifier;
}

QVariant SegmentData::getParentUniqueIdentifier() const{
    return this->parentUniqueIdentifier;
}

int SegmentData::getArticlePresenceOnServer() const{
    return this->articlePresence;
}

void SegmentData::setArticlePresenceOnServer(const int articlePresence){
    this->articlePresence = articlePresence;
}


QDataStream& operator<<(QDataStream& out, const SegmentData& segmentData) {

    out << segmentData.getBytes()
        << segmentData.getNumber()
        << segmentData.getPart()
        << segmentData.getElementInList()
        << segmentData.getStatus()
        << segmentData.getProgress()
        << segmentData.getArticlePresenceOnServer();

    return out;
}


QDataStream& operator>>(QDataStream& in, SegmentData& segmentData) {

    QString bytes;
    QString number;
    QString part;
    QString fileSavePath;
    QVariant parentUniqueIdentifier;
    quint32 elementInList;
    int status;
    int progress;
    int articlePresenceOnServer;

    in >> bytes
       >> number
       >> part
       >> elementInList
       >> status
       >> progress
       >> articlePresenceOnServer;


    segmentData.setBytes(bytes);
    segmentData.setNumber(number);
    segmentData.setPart(part);
    segmentData.setElementInList(elementInList);
    segmentData.setStatus(status);
    segmentData.setProgress(progress);
    segmentData.setArticlePresenceOnServer(articlePresenceOnServer);

    return in;
}

