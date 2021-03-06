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

#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>
#include <QStandardItem>

#include "kwooty_export.h"

namespace UtilityNamespace
{
    Q_ENUMS(MyRoles)
    Q_ENUMS(ItemStatus)
    Q_ENUMS(ConnectionStatus)
    Q_ENUMS(Article)
    Q_ENUMS(Data)
    Q_ENUMS(SaveError)
    Q_ENUMS(ItemTarget)
    Q_ENUMS(ProcessPriority)
    Q_ENUMS(PreferencesPage)

    // treeView columns :
    static const int FILE_NAME_COLUMN = 0;
    static const int STATE_COLUMN = 1;
    static const int PROGRESS_COLUMN = 2;
    static const int SIZE_COLUMN = 3;

    // percentage progression values :
    static const int PROGRESS_COMPLETE = 100;
    static const int PROGRESS_INIT = 0;
    static const int PROGRESS_UNKNOWN = -1;

    // file patterns :
    static const QString rarFileMagicNumber = "Rar";
    static const QString zipFileMagicNumber = "PK";
    static const QString sevenZipFileMagicNumber = "7z";
    static const QString par2FileMagicNumber = "PAR2";

    static const QString par2FileExt = ".par2";
    static const QString zipFileExt = ".zip";
    static const QString sevenZipFileExt = ".7z";

    static const QString repairProgram = "par2";
    static const QString rarExtractProgram = "unrar";
    static const QString sevenZipExtractProgram = "7z;7za";

    // segment file identifier :
    static const QString applicationFileOwner = "Kwooty_87b022df-17b9-409f-a423-3cc626831adc\r\n";
    static const QString remainingDownloadsFile = "kwootyInQueueDownloads.dat";

    // units :
    static const int MINUTES_TO_MILLISECONDS = 60000;
    static const int HOURS_TO_MILLISECONDS = 3600000;

    static const int SECONDS_IN_DAY = 86400;
    static const int SECONDS_IN_HOUR = 3600;
    static const int SECONDS_IN_MINUTE = 60;

    static const double NBR_BYTES_IN_GB = 1073741824;
    static const double NBR_BYTES_IN_MB = 1048576;
    static const double NBR_BYTES_IN_KB = 1024;
    static const double ONE_UNIT = 1;

    // plugin version, if changed make sure to update X-Kwooty-Plugin-Version in .desktop files accordingly :
    static const int KWOOTY_PLUGIN_VERSION = 2;

    // number of maximum master and backup servers :
    static const int MAX_SERVERS = 5;

    // custom roles used for storing data in items :
    enum MyRoles{
        StatusRole  = Qt::UserRole + 1,
        SegmentRole = Qt::UserRole + 2,
        NzbFileDataRole = Qt::UserRole + 3,
        IdentifierRole = Qt::UserRole + 4,
        ProgressRole = Qt::UserRole + 5,
        SizeRole = Qt::UserRole + 6
    };

    // item status list :
    enum ItemStatus {
        IdleStatus,
        // -- from here download related enums :
        DownloadStatus,
        DownloadFinishStatus,
        PauseStatus,
        PausingStatus,
        WaitForPar2IdleStatus,
        // -- from here decoding related enums :
        DecodeStatus,
        DecodeErrorStatus,
        DecodeFinishStatus,
        ScanStatus,
        // -- from here verifying/repairing (par2) related enums :
        VerifyStatus,
        VerifyFoundStatus,
        VerifyMatchStatus,
        VerifyMissingStatus,
        VerifyDamagedStatus,
        VerifyFinishedStatus,
        RepairStatus,
        RepairFinishedStatus,
        RepairNotPossibleStatus,
        RepairFailedStatus,
        Par2ProgramMissing,
        // -- from here extracting (unrar) related enums :
        ExtractStatus,
        ExtractBadCrcStatus,
        ExtractSuccessStatus,
        ExtractFinishedStatus,
        ExtractFailedStatus,
        UnrarProgramMissing,
        SevenZipProgramMissing
    };


    // type of article encoding :
    enum ArticleEncodingType {
        ArticleEncodingYEnc,
        ArticleEncodingUUEnc,
        ArticleEncodingUnknown
    };


    // connection status list used by statusbar :
    enum ConnectionStatus {
        Disconnected,
        HostFound,
        HostNotFound,
        ConnectionRefused,
        RemoteHostClosed,
        SslHandshakeFailed,
        AuthenticationFailed,
        AuthenticationAccepted,
        AuthenticationNeeded,
        ConnectedSslActive,
        Connected,
        NoError
    };

    // indicate presence of segment on server :
    enum Article {
        Present,
        NotPresent,
        Unknown
    };

    // indicate if downloaded data are missing :
    enum Data {
        NoData,
        DataIncomplete,
        DataComplete,
        DataPendingBackupServer
    };


    // add details about message box error :
    enum SaveError {
        DuringDecode,
        DuringDownload
    };


    // choose target item to be updated :
    enum ItemTarget {
        ChildItemTarget,
        ParentItemTarget,
        BothItemsTarget
    };


    // indicate if file is open by another app or directly by this app :
    enum OpenFileMode {
        OpenNormal,
        OpenWith
    };


    // indicate the crc status of each downloaded file :
    enum CrcNotify {
        CrcOk,
        CrcKo,
        CrcKoNotified,
        CrcUnknown
    };

    // type of status bar file size update :
    enum StatusBarUpdateType {
        Incremental,
        Reset
    };

    // type of system shudown :
    enum SystemShutdownType {
        Shutdown,
        Standby,
        Suspend,
        Hibernate,
        ShutdownMethodUnknown
    };


    // type of archive :
    enum ArchiveFormat {
        RarFormat,
        ZipOrSevenZipFormat,
        SplitFileFormat,
        UnknownArchiveFormat
    };


    // info about free disk space :
    enum FreeDiskSpace {
        SufficientDiskSpace,
        InsufficientDiskSpace,
        UnknownDiskSpace
    };


    // process priority :
    enum ProcessPriority {
        LowPriority,
        LowestPriority,
        CustomPriority
    };


    // configuration preferences pages :
    enum PreferencesPage {
        GeneralPage,
        ServerPage,
        ProgramsPage,
        DisplayPage,
        ShutdownPage,
        PluginsPage
    };


    // server target for segments :
    enum ServerTarget {
        NoTargetServer = -1,
        MasterServer,
        ActiveBackupServer = MAX_SERVERS + 1
    };


    // current backup server mode :
    enum BackupServerMode {
        PassiveServer,
        ActiveServer,
        FailoverServer,
        DisabledServer
    };


    // nntp client bandwidth management :
    enum BandwidthClientMode {
        BandwidthNotNeeded,
        BandwidthLimited,
        BandwidthFull
    };

    // save file behavior :
    enum SaveFileBehavior {
        SaveSilently,
        SaveNotSilently
    };


    // maximum size of the segments buffer pending to decode :
    enum BufferSize {
        BufferMaxSizeMB = 104857600, // 100 MiB
        BufferMaxSizeList = 1000
    };

}


class KWOOTY_EXPORT Utility
{
    
public:
    
    Utility();
    
    
    static QString convertByteHumanReadable(const quint64);
    static QString convertDownloadSpeedHumanReadable(const quint64);
    static bool isInDownloadProcess(const UtilityNamespace::ItemStatus);
    static bool isPostDownloadFailed(const UtilityNamespace::ItemStatus);
    static bool isVerifyFileCorrect(const UtilityNamespace::ItemStatus);
    static bool isReadyToDownload(const UtilityNamespace::ItemStatus);
    static bool isInQueue(const UtilityNamespace::ItemStatus);
    static bool isPaused(const UtilityNamespace::ItemStatus);
    static bool isPausing(const UtilityNamespace::ItemStatus);
    static bool isPausedOrPausing(const UtilityNamespace::ItemStatus);
    static bool isDownloadOrPausing(const UtilityNamespace::ItemStatus);
    static bool isDownloadFinish(const UtilityNamespace::ItemStatus);
    static bool isDecoding(const UtilityNamespace::ItemStatus);
    static bool isDecodeFinish(const UtilityNamespace::ItemStatus);
    static bool isWaitingForDecode(const UtilityNamespace::ItemStatus, const UtilityNamespace::Data);
    static bool isFileNotFound(const UtilityNamespace::ItemStatus, const UtilityNamespace::Data);
    static bool isPostDownloadProcessing(const UtilityNamespace::ItemStatus);
    static bool isJobFinish(const UtilityNamespace::ItemStatus);
    static bool isBadCrcForYencArticle(const UtilityNamespace::CrcNotify&, const UtilityNamespace::ArticleEncodingType&);
    static bool saveData(const QString&, const QString&, const QByteArray&);
    static bool createFolder(const QString&);
    static bool isFolderExists(const QString&);
    static bool removeData(const QString&);
    static bool rename(const QString&, const QString&);
    static bool isTemporaryFolderDiskFull();
    static bool isCompletedFolderDiskFull();
    static QString searchExternalPrograms(const QString&, bool&);
    static QString getSystemTimeFormat(const QString&);
    static QString buildFullPath(const QString&, const QString&);
    static QString buildToolTipRow(const QString&, const QString&);
    static QStringList buildPriorityArgument(const int&, const int&);
    
    
private:

    
};



#endif // UTILITY_H
