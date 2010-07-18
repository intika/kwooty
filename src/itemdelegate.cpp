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

#include "itemdelegate.h"

#include <KAboutData>
#include <KDebug>
#include <KApplication>
#include <KGlobal>
#include <KIcon>
#include <QStyleOptionViewItemV4>

#include "data/itemstatusdata.h"
#include "utility.h"
using namespace UtilityNamespace;


ItemDelegate::ItemDelegate(QWidget* parent) : QStyledItemDelegate(parent)
{

    kDebug();

    // associate text to display according to item status :
    statusTextMap.insert(DownloadStatus,            i18n("Downloading..."));
    statusTextMap.insert(DownloadFinishStatus,      i18n("Finished"));
    statusTextMap.insert(IdleStatus,                i18n("In queue"));
    statusTextMap.insert(PauseStatus,               i18n("Pause"));
    statusTextMap.insert(PausingStatus,             i18n("Pausing..."));
    statusTextMap.insert(WaitForPar2IdleStatus,     i18n("Smart queue"));
    statusTextMap.insert(ScanStatus,                i18n("Scanning..."));
    statusTextMap.insert(DecodeStatus,              i18n("Decoding..."));
    statusTextMap.insert(DecodeFinishStatus,        i18n("Decoded"));
    statusTextMap.insert(DecodeErrorStatus,         i18n("Decoding Error"));
    statusTextMap.insert(VerifyStatus,              i18n("Verifying file..."));
    statusTextMap.insert(VerifyFinishedStatus,      i18n("Verify finished"));
    statusTextMap.insert(VerifyFoundStatus,         i18n("File correct"));
    statusTextMap.insert(VerifyMatchStatus,         i18n("File correct"));
    statusTextMap.insert(VerifyMissingStatus,       i18n("File missing"));
    statusTextMap.insert(VerifyDamagedStatus,       i18n("File damaged"));
    statusTextMap.insert(RepairStatus,              i18n("Repairing file..."));
    statusTextMap.insert(RepairFinishedStatus,      i18n("Repair complete"));
    statusTextMap.insert(RepairNotPossibleStatus,   i18n("Repair not possible"));
    statusTextMap.insert(RepairFailedStatus,        i18n("Repair failed"));
    statusTextMap.insert(Par2ProgramMissing,        i18n("par2 program not found !"));
    statusTextMap.insert(ExtractStatus,             i18n("Extracting..."));
    statusTextMap.insert(ExtractBadCrcStatus,       i18n("Extract failed (bad CRC)"));
    statusTextMap.insert(ExtractFinishedStatus,     i18n("Extract finished"));
    statusTextMap.insert(ExtractSuccessStatus,      i18n("Extract complete"));
    statusTextMap.insert(ExtractFailedStatus,       i18n("Extract failed"));
    statusTextMap.insert(UnrarProgramMissing,       i18n("unrar program not found !"));
    statusTextMap.insert(SevenZipProgramMissing,    i18n("7-zip (7z or 7za) program not found !"));

    // associate color to display according to item status :
    statusColorMap.insert(DownloadStatus,            QColor(Qt::green));
    statusColorMap.insert(ScanStatus,                QColor(Qt::darkCyan));
    statusColorMap.insert(DecodeStatus,              QColor(Qt::darkCyan));
    statusColorMap.insert(DecodeErrorStatus,         QColor("orangered"));
    statusColorMap.insert(VerifyStatus,              QColor("royalblue"));
    statusColorMap.insert(RepairStatus,              QColor("royalblue"));
    statusColorMap.insert(RepairNotPossibleStatus,   QColor("orangered"));
    statusColorMap.insert(RepairFailedStatus,        QColor("orangered"));
    statusColorMap.insert(Par2ProgramMissing,        QColor("orangered"));
    statusColorMap.insert(ExtractBadCrcStatus,       QColor("orangered"));
    statusColorMap.insert(ExtractStatus,             QColor("royalblue"));
    statusColorMap.insert(UnrarProgramMissing,       QColor("orangered"));
    statusColorMap.insert(SevenZipProgramMissing,    QColor("orangered"));

}


void ItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {

    QStyleOptionViewItemV4 opt = option;
    int status = -1;

    static int progress = 0;

    if (index.parent() == QModelIndex()){
        painter->save();

        //painter->drawPie(rectangle, startAngle, spanAngle);

         KIcon iconTest = KIcon("go-next-view");
         QPixmap statusPixmap = iconTest.pixmap( 22,22 );

         painter->drawPixmap(0,0,statusPixmap);

         QFont boldFont = painter->font();
         boldFont.setBold(true);
         boldFont.setItalic(true);
         painter->setFont(boldFont);
         painter->drawText(QRect(36, 0, 500, 16), "openSUSE - 11.2 - x86_64 By Kal");
         boldFont.setBold(false);
         boldFont.setItalic(false);
         painter->setFont(boldFont);

         painter->translate(0,16);
         painter->drawText(QRect(36, 2, 500, 16), "test gauche");
         painter->drawText(QRect(600, 2, 500, 16), "test droite");

         QStyleOptionProgressBar progressBarOpt;
         progressBarOpt.rect = QRect(80, 2, 500, 16);
         progressBarOpt.minimum = 0;
         progressBarOpt.maximum = 100;
         progressBarOpt.textVisible = true;

         // set progress value and text :
         //int progress = index.data(ProgressRole).toInt();

         kDebug() << progress;
         progressBarOpt.progress = progress;
         progressBarOpt.text = i18n("<numid>%1</numid> %", progress++);


         if (progress == PROGRESS_UNKNOWN) {
             progressBarOpt.text = i18n("n/a");
         }

         KApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOpt, painter);



        painter->restore();
    }






    switch(index.column()){

    case STATE_COLUMN:{
            // get the status :
            ItemStatusData itemStatusData = index.data(StatusRole).value<ItemStatusData>();
            status = itemStatusData.getStatus();

            //set text according to status :
            opt.text = statusTextMap.value(status);

            // modify text value if download contains incomplete data :
            if (status == DownloadStatus) {
                if (itemStatusData.getDataStatus() == NoData) {
                    opt.text = i18n("No Data");
                }
                if (itemStatusData.getDataStatus() == DataIncomplete){
                    opt.text = i18n("%1 (incomplete)", opt.text);
                }
            }
            if (status == DownloadFinishStatus) {
                if (itemStatusData.getDataStatus() == NoData) {
                    opt.text = i18n("File not found");
                }
            }

            break;
        }

    case PROGRESS_COLUMN:{

            // draw progress bar for parent :
            if (index.parent() == QModelIndex()){
                this->drawProgressBar(painter, option, index);
                return;
            }
            else {
                int progress = index.data(ProgressRole).toInt();
                opt.text = i18n("<numid>%1</numid> %", progress);

                // if progress unkwnown (appears 7z extract command is launched), display n/a :
                if (progress == PROGRESS_UNKNOWN) {
                    opt.text = i18n("n/a");
                }

            }

            break;
        }

    case SIZE_COLUMN:{
            opt.text = Utility::convertByteHumanReadable(index.data(SizeRole).toULongLong());
            break;
        }

    default: {
            break;
        }

    }

    // set color according to status :
    if (statusColorMap.contains(status)) {
        opt.palette.setColor(QPalette::Text, statusColorMap.value(status));
    }

    // draw text :
    QStyledItemDelegate::paint(painter, opt, index);

    
}


void ItemDelegate::drawProgressBar(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {

    QStyleOptionProgressBar progressBarOpt;
    progressBarOpt.rect = option.rect;
    progressBarOpt.minimum = 0;
    progressBarOpt.maximum = 100;
    progressBarOpt.textVisible = true;

    // set progress value and text :
    int progress = index.data(ProgressRole).toInt();
    progressBarOpt.progress = progress;    
    progressBarOpt.text = i18n("<numid>%1</numid> %", progress);


    if (progress == PROGRESS_UNKNOWN) {
        progressBarOpt.text = i18n("n/a");
    }


    // draw progress bar :
    KApplication::style()->drawControl(QStyle::CE_ProgressBar, &progressBarOpt, painter);
}


QSize ItemDelegate::sizeHint( const QStyleOptionViewItem& option, const QModelIndex& index ) const
{


        if (index.parent() == QModelIndex()) {
            return QSize(50, 50);
        }
        else {

            kDebug();
    return QStyledItemDelegate::sizeHint(option, index);
        }

}



