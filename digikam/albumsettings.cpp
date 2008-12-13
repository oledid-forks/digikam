/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2003-16-10
 * Description : albums settings interface
 *
 * Copyright (C) 2003-2004 by Renchi Raju <renchi@pooh.tam.uiuc.edu>
 * Copyright (C) 2003-2008 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2007 by Arnd Baecker <arnd dot baecker at web dot de>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "albumsettings.h"

// KDE includes.

#include <kconfig.h>
#include <klocale.h>
#include <kapplication.h>
#include <kdebug.h>
#include <kglobal.h>
#include <kconfiggroup.h>

// LibKDcraw includes.

#include <libkdcraw/version.h>
#include <libkdcraw/kdcraw.h>

#if KDCRAW_VERSION < 0x000400
#include <libkdcraw/dcrawbinary.h>
#endif

// Local includes.

#include "thumbnailsize.h"
#include "mimefilter.h"
#include "databaseaccess.h"
#include "albumdb.h"
#include "albumlister.h"

namespace Digikam
{

class AlbumSettingsPrivate
{

public:

    // start up setting
    bool                                showSplash;
    // file ops settings
    bool                                useTrash;
    bool                                showTrashDeleteDialog;
    // metadata setting
    bool                                sidebarApplyDirectly;
    // database setting
    bool                                scanAtStart;

    // icon view settings
    bool                                iconShowName;
    bool                                iconShowSize;
    bool                                iconShowDate;
    bool                                iconShowModDate;
    bool                                iconShowComments;
    bool                                iconShowResolution;
    bool                                iconShowTags;
    bool                                iconShowRating;

    // tooltip settings
    bool                                showToolTips;
    bool                                tooltipShowFileName;
    bool                                tooltipShowFileDate;
    bool                                tooltipShowFileSize;
    bool                                tooltipShowImageType;
    bool                                tooltipShowImageDim;
    bool                                tooltipShowPhotoMake;
    bool                                tooltipShowPhotoDate;
    bool                                tooltipShowPhotoFocal;
    bool                                tooltipShowPhotoExpo;
    bool                                tooltipShowPhotoMode;
    bool                                tooltipShowPhotoFlash;
    bool                                tooltipShowPhotoWb;
    bool                                tooltipShowAlbumName;
    bool                                tooltipShowComments;
    bool                                tooltipShowTags;
    bool                                tooltipShowRating;

    // metadata settings
    bool                                exifRotate;
    bool                                exifSetOrientation;

    bool                                saveTags;
    bool                                savePhotographerId;
    bool                                saveCredits;

    bool                                saveComments;
    bool                                saveDateTime;
    bool                                saveRating;

    bool                                writeRawFiles;

    // preview settings
    bool                                previewLoadFullImageSize;
    bool                                showThumbbar;

    bool                                showFolderTreeViewItemsCount;

    QString                             author;
    QString                             authorTitle;
    QString                             credit;
    QString                             source;
    QString                             copyright;

    // album view settings
    int                                 treeThumbnailSize;

    // icon view settings
    int                                 thumbnailSize;
    int                                 ratingFilterCond;
    bool                                recursiveAlbums;
    bool                                recursiveTags;

    // theme settings
    QString                             currentTheme;

    // database settings
    QString                             databaseFilePath;

    // album settings
    QStringList                         albumCollectionNames;

    KSharedConfigPtr                    config;

    // album view settings
    AlbumSettings::AlbumSortOrder       albumSortOrder;

    // icon view settings
    AlbumSettings::ImageSortOrder       imageSortOrder;
    AlbumSettings::ItemRightClickAction itemRightClickAction;
};

class AlbumSettingsCreator { public: AlbumSettings object; };
K_GLOBAL_STATIC(AlbumSettingsCreator, creator)

AlbumSettings* AlbumSettings::instance()
{
    return &creator->object;
}

AlbumSettings::AlbumSettings()
             : d(new AlbumSettingsPrivate)
{
    d->config = KGlobal::config();
    init();
    readSettings();
}

AlbumSettings::~AlbumSettings()
{
    delete d;
}

void AlbumSettings::init()
{
    d->albumCollectionNames.clear();
    d->albumCollectionNames.append(i18n("Family"));
    d->albumCollectionNames.append(i18n("Travel"));
    d->albumCollectionNames.append(i18n("Holidays"));
    d->albumCollectionNames.append(i18n("Friends"));
    d->albumCollectionNames.append(i18n("Nature"));
    d->albumCollectionNames.append(i18n("Party"));
    d->albumCollectionNames.append(i18n("Todo"));
    d->albumCollectionNames.append(i18n("Miscellaneous"));
    d->albumCollectionNames.sort();

    d->albumSortOrder               = AlbumSettings::ByFolder;
    d->imageSortOrder               = AlbumSettings::ByIName;
    d->itemRightClickAction         = AlbumSettings::ShowPreview;

    d->thumbnailSize                = ThumbnailSize::Medium;
    d->treeThumbnailSize            = 22;

    d->ratingFilterCond             = AlbumLister::GreaterEqualCondition;

    d->showToolTips                 = true;
    d->showSplash                   = true;
    d->useTrash                     = true;
    d->showTrashDeleteDialog        = true;
    d->sidebarApplyDirectly         = false;

    d->iconShowName                 = false;
    d->iconShowSize                 = false;
    d->iconShowDate                 = true;
    d->iconShowModDate              = true;
    d->iconShowComments             = true;
    d->iconShowResolution           = false;
    d->iconShowTags                 = true;
    d->iconShowRating               = true;

    d->tooltipShowFileName          = true;
    d->tooltipShowFileDate          = false;
    d->tooltipShowFileSize          = false;
    d->tooltipShowImageType         = false;
    d->tooltipShowImageDim          = true;
    d->tooltipShowPhotoMake         = true;
    d->tooltipShowPhotoDate         = true;
    d->tooltipShowPhotoFocal        = true;
    d->tooltipShowPhotoExpo         = true;
    d->tooltipShowPhotoMode         = true;
    d->tooltipShowPhotoFlash        = false;
    d->tooltipShowPhotoWb           = false;
    d->tooltipShowAlbumName         = false;
    d->tooltipShowComments          = true;
    d->tooltipShowTags              = true;
    d->tooltipShowRating            = true;

    d->exifRotate                   = true;
    d->exifSetOrientation           = true;

    d->saveTags                     = false;
    d->savePhotographerId           = false;
    d->saveCredits                  = false;

    d->saveComments                 = false;
    d->saveDateTime                 = false;
    d->saveRating                   = false;

    d->writeRawFiles                = false;

    d->previewLoadFullImageSize     = false;
    d->showThumbbar                 = true;

    d->recursiveAlbums              = false;
    d->recursiveTags                = true;

    d->showFolderTreeViewItemsCount = false;

}

void AlbumSettings::readSettings()
{
    KSharedConfigPtr config = d->config;

    // ---------------------------------------------------------------------

    KConfigGroup group  = config->group("Album Settings");

    d->databaseFilePath = group.readEntry("Database File Path", QString());

    QStringList collectionList = group.readEntry("Album Collections",QStringList());
    if (!collectionList.isEmpty())
    {
        collectionList.sort();
        d->albumCollectionNames = collectionList;
    }

    d->albumSortOrder = AlbumSettings::AlbumSortOrder(group.readEntry("Album Sort Order",
                                                      (int)AlbumSettings::ByFolder));

    d->imageSortOrder               = AlbumSettings::ImageSortOrder(group.readEntry("Image Sort Order",
                                                                    (int)AlbumSettings::ByIName));

    d->itemRightClickAction         = AlbumSettings::ItemRightClickAction(group.readEntry(
                                                                         "Item Right Click Action",
                                                                          (int)AlbumSettings::ShowPreview));

    d->thumbnailSize                = group.readEntry("Default Icon Size", (int)ThumbnailSize::Medium);
    d->treeThumbnailSize            = group.readEntry("Default Tree Icon Size", 22);
    d->currentTheme                 = group.readEntry("Theme", i18n("Default"));

    d->ratingFilterCond             = group.readEntry("Rating Filter Condition",
                                                      (int)AlbumLister::GreaterEqualCondition);
    d->recursiveAlbums              = group.readEntry("Recursive Albums", false);
    d->recursiveTags                = group.readEntry("Recursive Tags", true);


    d->iconShowName                 = group.readEntry("Icon Show Name", false);
    d->iconShowResolution           = group.readEntry("Icon Show Resolution", false);
    d->iconShowSize                 = group.readEntry("Icon Show Size", false);
    d->iconShowDate                 = group.readEntry("Icon Show Date", true);
    d->iconShowModDate              = group.readEntry("Icon Show Modification Date", true);
    d->iconShowComments             = group.readEntry("Icon Show Comments", true);
    d->iconShowTags                 = group.readEntry("Icon Show Tags", true);
    d->iconShowRating               = group.readEntry("Icon Show Rating", true);

    d->showToolTips                 = group.readEntry("Show ToolTips", false);
    d->tooltipShowFileName          = group.readEntry("ToolTips Show File Name", true);
    d->tooltipShowFileDate          = group.readEntry("ToolTips Show File Date", false);
    d->tooltipShowFileSize          = group.readEntry("ToolTips Show File Size", false);
    d->tooltipShowImageType         = group.readEntry("ToolTips Show Image Type", false);
    d->tooltipShowImageDim          = group.readEntry("ToolTips Show Image Dim", true);
    d->tooltipShowPhotoMake         = group.readEntry("ToolTips Show Photo Make", true);
    d->tooltipShowPhotoDate         = group.readEntry("ToolTips Show Photo Date", true);
    d->tooltipShowPhotoFocal        = group.readEntry("ToolTips Show Photo Focal", true);
    d->tooltipShowPhotoExpo         = group.readEntry("ToolTips Show Photo Expo", true);
    d->tooltipShowPhotoMode         = group.readEntry("ToolTips Show Photo Mode", true);
    d->tooltipShowPhotoFlash        = group.readEntry("ToolTips Show Photo Flash", false);
    d->tooltipShowPhotoWb           = group.readEntry("ToolTips Show Photo WB", false);
    d->tooltipShowAlbumName         = group.readEntry("ToolTips Show Album Name", false);
    d->tooltipShowComments          = group.readEntry("ToolTips Show Comments", true);
    d->tooltipShowTags              = group.readEntry("ToolTips Show Tags", true);
    d->tooltipShowRating            = group.readEntry("ToolTips Show Rating", true);

    d->previewLoadFullImageSize     = group.readEntry("Preview Load Full Image Size", false);
    d->showThumbbar                 = group.readEntry("Show Thumbbar", true);

    d->showFolderTreeViewItemsCount = group.readEntry("Show Folder Tree View Items Count", false);

    // ---------------------------------------------------------------------

    group = config->group("EXIF Settings");

    d->exifRotate         = group.readEntry("EXIF Rotate", true);
    d->exifSetOrientation = group.readEntry("EXIF Set Orientation", true);

    // ---------------------------------------------------------------------

    group = config->group("Metadata Settings");

    d->saveTags               = group.readEntry("Save Tags", false);
    d->savePhotographerId     = group.readEntry("Save Photographer ID", false);
    d->saveCredits            = group.readEntry("Save Credits", false);

    d->saveComments           = group.readEntry("Save EXIF Comments", false);
    d->saveDateTime           = group.readEntry("Save Date Time", false);
    d->saveRating             = group.readEntry("Save Rating", false);

    d->author                 = group.readEntry("Author", QString());
    d->authorTitle            = group.readEntry("Author Title", QString());
    d->credit                 = group.readEntry("Credit", QString());
    d->source                 = group.readEntry("Source", QString());
    d->copyright              = group.readEntry("Copyright", QString());

    d->writeRawFiles          = group.readEntry("Write RAW Files", false);

    // ---------------------------------------------------------------------

    group = config->group("General Settings");

    d->showSplash            = group.readEntry("Show Splash", true);
    d->useTrash              = group.readEntry("Use Trash", true);
    d->showTrashDeleteDialog = group.readEntry("Show Trash Delete Dialog", true);
    d->sidebarApplyDirectly  = group.readEntry("Apply Sidebar Changes Directly", false);
    d->scanAtStart           = group.readEntry("Scan At Start", true);
}

void AlbumSettings::saveSettings()
{
    KSharedConfigPtr config = d->config;

    // ---------------------------------------------------------------------

    KConfigGroup group = config->group("Album Settings");

    group.writeEntry("Database File Path", d->databaseFilePath);
    group.writeEntry("Album Collections", d->albumCollectionNames);
    group.writeEntry("Album Sort Order", (int)d->albumSortOrder);
    group.writeEntry("Image Sort Order", (int)d->imageSortOrder);
    group.writeEntry("Item Right Click Action", (int)d->itemRightClickAction);
    group.writeEntry("Default Icon Size", QString::number(d->thumbnailSize));
    group.writeEntry("Default Tree Icon Size", QString::number(d->treeThumbnailSize));
    group.writeEntry("Rating Filter Condition", d->ratingFilterCond);
    group.writeEntry("Recursive Albums", d->recursiveAlbums);
    group.writeEntry("Recursive Tags", d->recursiveTags);
    group.writeEntry("Theme", d->currentTheme);

    group.writeEntry("Icon Show Name", d->iconShowName);
    group.writeEntry("Icon Show Resolution", d->iconShowResolution);
    group.writeEntry("Icon Show Size", d->iconShowSize);
    group.writeEntry("Icon Show Date", d->iconShowDate);
    group.writeEntry("Icon Show Modification Date", d->iconShowModDate);
    group.writeEntry("Icon Show Comments", d->iconShowComments);
    group.writeEntry("Icon Show Tags", d->iconShowTags);
    group.writeEntry("Icon Show Rating", d->iconShowRating);

    group.writeEntry("Show ToolTips", d->showToolTips);
    group.writeEntry("ToolTips Show File Name", d->tooltipShowFileName);
    group.writeEntry("ToolTips Show File Date", d->tooltipShowFileDate);
    group.writeEntry("ToolTips Show File Size", d->tooltipShowFileSize);
    group.writeEntry("ToolTips Show Image Type", d->tooltipShowImageType);
    group.writeEntry("ToolTips Show Image Dim", d->tooltipShowImageDim);
    group.writeEntry("ToolTips Show Photo Make", d->tooltipShowPhotoMake);
    group.writeEntry("ToolTips Show Photo Date", d->tooltipShowPhotoDate);
    group.writeEntry("ToolTips Show Photo Focal", d->tooltipShowPhotoFocal);
    group.writeEntry("ToolTips Show Photo Expo", d->tooltipShowPhotoExpo);
    group.writeEntry("ToolTips Show Photo Mode", d->tooltipShowPhotoMode);
    group.writeEntry("ToolTips Show Photo Flash", d->tooltipShowPhotoFlash);
    group.writeEntry("ToolTips Show Photo WB", d->tooltipShowPhotoWb);
    group.writeEntry("ToolTips Show Album Name", d->tooltipShowAlbumName);
    group.writeEntry("ToolTips Show Comments", d->tooltipShowComments);
    group.writeEntry("ToolTips Show Tags", d->tooltipShowTags);
    group.writeEntry("ToolTips Show Rating", d->tooltipShowRating);

    group.writeEntry("Preview Load Full Image Size", d->previewLoadFullImageSize);
    group.writeEntry("Show Thumbbar", d->showThumbbar);

    group.writeEntry("Show Folder Tree View Items Count", d->showFolderTreeViewItemsCount);

    // ---------------------------------------------------------------------

    group = config->group("EXIF Settings");

    group.writeEntry("EXIF Rotate", d->exifRotate);
    group.writeEntry("EXIF Set Orientation", d->exifSetOrientation);

    // ---------------------------------------------------------------------

    group = config->group("Metadata Settings");

    group.writeEntry("Save Tags", d->saveTags);
    group.writeEntry("Save Photographer ID", d->savePhotographerId);
    group.writeEntry("Save Credits", d->saveCredits);

    group.writeEntry("Save EXIF Comments", d->saveComments);
    group.writeEntry("Save Date Time", d->saveDateTime);
    group.writeEntry("Save Rating", d->saveRating);

    group.writeEntry("Author", d->author);
    group.writeEntry("Author Title", d->authorTitle);
    group.writeEntry("Credit", d->credit);
    group.writeEntry("Source", d->source);
    group.writeEntry("Copyright", d->copyright);

    group.writeEntry("Write RAW Files", d->writeRawFiles);

    // ---------------------------------------------------------------------

    group = config->group("General Settings");

    group.writeEntry("Show Splash", d->showSplash);
    group.writeEntry("Use Trash", d->useTrash);
    group.writeEntry("Show Trash Delete Dialog", d->showTrashDeleteDialog);
    group.writeEntry("Apply Sidebar Changes Directly", d->sidebarApplyDirectly);
    group.writeEntry("Scan At Start", d->scanAtStart);

    config->sync();
}

QString AlbumSettings::getDatabaseFilePath() const
{
    return d->databaseFilePath;
}

void AlbumSettings::setDatabaseFilePath(const QString& path)
{
    d->databaseFilePath = path;
}

void AlbumSettings::setShowSplashScreen(bool val)
{
    d->showSplash = val;
}

bool AlbumSettings::getShowSplashScreen() const
{
    return d->showSplash;
}

void AlbumSettings::setScanAtStart(bool val)
{
    d->scanAtStart = val;
}

bool AlbumSettings::getScanAtStart() const
{
    return d->scanAtStart;
}

void AlbumSettings::setAlbumCollectionNames(const QStringList& list)
{
    d->albumCollectionNames = list;
}

QStringList AlbumSettings::getAlbumCollectionNames()
{
    return d->albumCollectionNames;
}

bool AlbumSettings::addAlbumCollectionName(const QString& name)
{
    if (d->albumCollectionNames.contains(name))
        return false;

    d->albumCollectionNames.append(name);
    return true;
}

bool AlbumSettings::delAlbumCollectionName(const QString& name)
{
    uint count = d->albumCollectionNames.removeAll(name);
    return (count > 0) ? true : false;
}

void AlbumSettings::setAlbumSortOrder(const AlbumSettings::AlbumSortOrder order)
{
    d->albumSortOrder = order;
}

AlbumSettings::AlbumSortOrder AlbumSettings::getAlbumSortOrder() const
{
    return d->albumSortOrder;
}

void AlbumSettings::setImageSortOrder(const ImageSortOrder order)
{
    d->imageSortOrder = order;
}

AlbumSettings::ImageSortOrder AlbumSettings::getImageSortOrder() const
{
    return d->imageSortOrder;
}

void AlbumSettings::setItemRightClickAction(const ItemRightClickAction action)
{
    d->itemRightClickAction = action;
}

AlbumSettings::ItemRightClickAction AlbumSettings::getItemRightClickAction() const
{
    return d->itemRightClickAction;
}

QString AlbumSettings::getImageFileFilter() const
{
    QStringList imageSettings;
    DatabaseAccess().db()->getFilterSettings(&imageSettings, 0, 0);
    QStringList wildcards;
    foreach (const QString &suffix, imageSettings)
        wildcards << "*." + suffix;
    return wildcards.join(" ");
}

QString AlbumSettings::getMovieFileFilter() const
{
    QStringList movieSettings;
    DatabaseAccess().db()->getFilterSettings(0, &movieSettings, 0);
    QStringList wildcards;
    foreach (const QString &suffix, movieSettings)
        wildcards << "*." + suffix;
    return wildcards.join(" ");
}

QString AlbumSettings::getAudioFileFilter() const
{
    QStringList audioSettings;
    DatabaseAccess().db()->getFilterSettings(0, 0, &audioSettings);
    QStringList wildcards;
    foreach (const QString &suffix, audioSettings)
        wildcards << "*." + suffix;
    return wildcards.join(" ");
}

QString AlbumSettings::getRawFileFilter() const
{
#if KDCRAW_VERSION < 0x000400
    QStringList supportedRaws = KDcrawIface::DcrawBinary::rawFilesList();
#else
    QStringList supportedRaws = KDcrawIface::KDcraw::rawFilesList();
#endif

    QStringList imageSettings;
    DatabaseAccess().db()->getFilterSettings(&imageSettings, 0, 0);

    // form intersection: those extensions that are supported as RAW as well in the list of allowed extensions
    for (QStringList::iterator it = supportedRaws.begin(); it != supportedRaws.end(); )
    {
        if (imageSettings.contains(*it))
            ++it;
        else
            it = supportedRaws.erase(it);
    }

    QStringList wildcards;
    foreach (const QString &suffix, supportedRaws)
        wildcards << "*." + suffix;
    return wildcards.join(" ");
}

QString AlbumSettings::getAllFileFilter() const
{
    QStringList imageFilter, audioFilter, videoFilter;
    DatabaseAccess().db()->getFilterSettings(&imageFilter, &audioFilter, &videoFilter);
    QStringList wildcards;
    foreach (const QString &suffix, imageFilter)
        wildcards << "*." + suffix;
    foreach (const QString &suffix, audioFilter)
        wildcards << "*." + suffix;
    foreach (const QString &suffix, videoFilter)
        wildcards << "*." + suffix;
    return wildcards.join(" ");
}

void AlbumSettings::addToImageFileFilter(const QString &extensions)
{
    DatabaseAccess().db()->addToUserImageFilterSettings(extensions);
}

void AlbumSettings::setDefaultIconSize(int val)
{
    d->thumbnailSize = val;
}

int AlbumSettings::getDefaultIconSize() const
{
    return d->thumbnailSize;
}

void AlbumSettings::setDefaultTreeIconSize(int val)
{
    d->treeThumbnailSize = val;
}

int AlbumSettings::getDefaultTreeIconSize() const
{
    return ((d->treeThumbnailSize < 8) || (d->treeThumbnailSize > 48)) ? 48 : d->treeThumbnailSize;
}

void AlbumSettings::setRatingFilterCond(int val)
{
    d->ratingFilterCond = val;
}

int AlbumSettings::getRatingFilterCond() const
{
    return d->ratingFilterCond;
}

void AlbumSettings::setIconShowName(bool val)
{
    d->iconShowName = val;
}

bool AlbumSettings::getIconShowName() const
{
    return d->iconShowName;
}

void AlbumSettings::setIconShowSize(bool val)
{
    d->iconShowSize = val;
}

bool AlbumSettings::getIconShowSize() const
{
    return d->iconShowSize;
}

void AlbumSettings::setIconShowComments(bool val)
{
    d->iconShowComments = val;
}

bool AlbumSettings::getIconShowComments() const
{
    return d->iconShowComments;
}

void AlbumSettings::setIconShowResolution(bool val)
{
    d->iconShowResolution = val;
}

bool AlbumSettings::getIconShowResolution() const
{
    return d->iconShowResolution;
}

void AlbumSettings::setIconShowTags(bool val)
{
    d->iconShowTags = val;
}

bool AlbumSettings::getIconShowTags() const
{
    return d->iconShowTags;
}

void AlbumSettings::setIconShowDate(bool val)
{
    d->iconShowDate = val;
}

bool AlbumSettings::getIconShowDate() const
{
    return d->iconShowDate;
}

void AlbumSettings::setIconShowModDate(bool val)
{
    d->iconShowModDate = val;
}

bool AlbumSettings::getIconShowModDate() const
{
    return d->iconShowModDate;
}

void AlbumSettings::setIconShowRating(bool val)
{
    d->iconShowRating = val;
}

bool AlbumSettings::getIconShowRating() const
{
    return d->iconShowRating;
}

void AlbumSettings::setExifRotate(bool val)
{
    d->exifRotate = val;
}

bool AlbumSettings::getExifRotate() const
{
    return d->exifRotate;
}

void AlbumSettings::setExifSetOrientation(bool val)
{
    d->exifSetOrientation = val;
}

bool AlbumSettings::getExifSetOrientation() const
{
    return d->exifSetOrientation;
}

void AlbumSettings::setSaveTags(bool val)
{
    d->saveTags = val;
}

bool AlbumSettings::getSaveTags() const
{
    return d->saveTags;
}

void AlbumSettings::setSavePhotographerId(bool val)
{
    d->savePhotographerId = val;
}

bool AlbumSettings::getSavePhotographerId() const
{
    return d->savePhotographerId;
}

void AlbumSettings::setSaveCredits(bool val)
{
    d->saveCredits = val;
}

bool AlbumSettings::getSaveCredits() const
{
    return d->saveCredits;
}

void AlbumSettings::setWriteRawFiles(bool val)
{
    d->writeRawFiles = val;
}

bool AlbumSettings::getWriteRawFiles() const
{
    return d->writeRawFiles;
}

void AlbumSettings::setAuthor(const QString& author)
{
    d->author = author;
}

QString AlbumSettings::getAuthor() const
{
    return d->author;
}

void AlbumSettings::setAuthorTitle(const QString& authorTitle)
{
    d->authorTitle = authorTitle;
}

QString AlbumSettings::getAuthorTitle() const
{
    return d->authorTitle;
}

void AlbumSettings::setCredit(const QString& credit)
{
    d->credit = credit;
}

QString AlbumSettings::getCredit() const
{
    return d->credit;
}

void AlbumSettings::setSource(const QString& source)
{
    d->source = source;
}

QString AlbumSettings::getSource() const
{
    return d->source;
}

void AlbumSettings::setCopyright(const QString& copyright)
{
    d->copyright = copyright;
}

QString AlbumSettings::getCopyright() const
{
    return d->copyright;
}

void AlbumSettings::setSaveComments(bool val)
{
    d->saveComments = val;
}

bool AlbumSettings::getSaveComments() const
{
    return d->saveComments;
}

void AlbumSettings::setSaveDateTime(bool val)
{
    d->saveDateTime = val;
}

bool AlbumSettings::getSaveDateTime() const
{
    return d->saveDateTime;
}

bool AlbumSettings::getSaveRating() const
{
    return d->saveRating;
}

void AlbumSettings::setSaveRating(bool val)
{
    d->saveRating = val;
}

void AlbumSettings::setShowToolTips(bool val)
{
    d->showToolTips = val;
}

bool AlbumSettings::getShowToolTips() const
{
    return d->showToolTips;
}

void AlbumSettings::setToolTipsShowFileName(bool val)
{
    d->tooltipShowFileName = val;
}

bool AlbumSettings::getToolTipsShowFileName() const
{
    return d->tooltipShowFileName;
}

void AlbumSettings::setToolTipsShowFileDate(bool val)
{
    d->tooltipShowFileDate = val;
}

bool AlbumSettings::getToolTipsShowFileDate() const
{
    return d->tooltipShowFileDate;
}

void AlbumSettings::setToolTipsShowFileSize(bool val)
{
    d->tooltipShowFileSize = val;
}

bool AlbumSettings::getToolTipsShowFileSize() const
{
    return d->tooltipShowFileSize;
}

void AlbumSettings::setToolTipsShowImageType(bool val)
{
    d->tooltipShowImageType = val;
}

bool AlbumSettings::getToolTipsShowImageType() const
{
    return d->tooltipShowImageType;
}

void AlbumSettings::setToolTipsShowImageDim(bool val)
{
    d->tooltipShowImageDim = val;
}

bool AlbumSettings::getToolTipsShowImageDim() const
{
    return d->tooltipShowImageDim;
}

void AlbumSettings::setToolTipsShowPhotoMake(bool val)
{
    d->tooltipShowPhotoMake = val;
}

bool AlbumSettings::getToolTipsShowPhotoMake() const
{
    return d->tooltipShowPhotoMake;
}

void AlbumSettings::setToolTipsShowPhotoDate(bool val)
{
    d->tooltipShowPhotoDate = val;
}

bool AlbumSettings::getToolTipsShowPhotoDate() const
{
    return d->tooltipShowPhotoDate;
}

void AlbumSettings::setToolTipsShowPhotoFocal(bool val)
{
    d->tooltipShowPhotoFocal = val;
}

bool AlbumSettings::getToolTipsShowPhotoFocal() const
{
    return d->tooltipShowPhotoFocal;
}

void AlbumSettings::setToolTipsShowPhotoExpo(bool val)
{
    d->tooltipShowPhotoExpo = val;
}

bool AlbumSettings::getToolTipsShowPhotoExpo() const
{
    return d->tooltipShowPhotoExpo;
}

void AlbumSettings::setToolTipsShowPhotoMode(bool val)
{
    d->tooltipShowPhotoMode = val;
}

bool AlbumSettings::getToolTipsShowPhotoMode() const
{
    return d->tooltipShowPhotoMode;
}

void AlbumSettings::setToolTipsShowPhotoFlash(bool val)
{
    d->tooltipShowPhotoFlash = val;
}

bool AlbumSettings::getToolTipsShowPhotoFlash() const
{
    return d->tooltipShowPhotoFlash;
}

void AlbumSettings::setToolTipsShowPhotoWB(bool val)
{
    d->tooltipShowPhotoWb = val;
}

bool AlbumSettings::getToolTipsShowPhotoWB() const
{
    return d->tooltipShowPhotoWb;
}

void AlbumSettings::setToolTipsShowAlbumName(bool val)
{
    d->tooltipShowAlbumName = val;
}

bool AlbumSettings::getToolTipsShowAlbumName() const
{
    return d->tooltipShowAlbumName;
}

void AlbumSettings::setToolTipsShowComments(bool val)
{
    d->tooltipShowComments = val;
}

bool AlbumSettings::getToolTipsShowComments() const
{
    return d->tooltipShowComments;
}

void AlbumSettings::setToolTipsShowTags(bool val)
{
    d->tooltipShowTags = val;
}

bool AlbumSettings::getToolTipsShowTags() const
{
    return d->tooltipShowTags;
}

void AlbumSettings::setToolTipsShowRating(bool val)
{
    d->tooltipShowRating = val;
}

bool AlbumSettings::getToolTipsShowRating() const
{
    return d->tooltipShowRating;
}

void AlbumSettings::setCurrentTheme(const QString& theme)
{
    d->currentTheme = theme;
}

QString AlbumSettings::getCurrentTheme() const
{
    return d->currentTheme;
}

void AlbumSettings::setUseTrash(bool val)
{
    d->useTrash = val;
}

bool AlbumSettings::getUseTrash() const
{
    return d->useTrash;
}

void AlbumSettings::setShowTrashDeleteDialog(bool val)
{
    d->showTrashDeleteDialog = val;
}

bool AlbumSettings::getShowTrashDeleteDialog() const
{
    return d->showTrashDeleteDialog;
}

void AlbumSettings::setApplySidebarChangesDirectly(bool val)
{
    d->sidebarApplyDirectly= val;
}

bool AlbumSettings::getApplySidebarChangesDirectly() const
{
    return d->sidebarApplyDirectly;
}

bool AlbumSettings::showToolTipsIsValid() const
{
    if (d->showToolTips)
    {
        if (d->tooltipShowFileName   ||
            d->tooltipShowFileDate   ||
            d->tooltipShowFileSize   ||
            d->tooltipShowImageType  ||
            d->tooltipShowImageDim   ||
            d->tooltipShowPhotoMake  ||
            d->tooltipShowPhotoDate  ||
            d->tooltipShowPhotoFocal ||
            d->tooltipShowPhotoExpo  ||
            d->tooltipShowPhotoMode  ||
            d->tooltipShowPhotoFlash ||
            d->tooltipShowPhotoWb    ||
            d->tooltipShowAlbumName  ||
            d->tooltipShowComments   ||
            d->tooltipShowTags       ||
            d->tooltipShowRating)
           return true;
    }

    return false;
}

void AlbumSettings::setPreviewLoadFullImageSize(bool val)
{
    d->previewLoadFullImageSize = val;
}

bool AlbumSettings::getPreviewLoadFullImageSize() const
{
    return d->previewLoadFullImageSize;
}

void AlbumSettings::setRecurseAlbums(bool val)
{
    d->recursiveAlbums = val;
}

bool AlbumSettings::getRecurseAlbums() const
{
    return d->recursiveAlbums;
}

void AlbumSettings::setRecurseTags(bool val)
{
    d->recursiveTags = val;
}

bool AlbumSettings::getRecurseTags() const
{
    return d->recursiveTags;
}

void AlbumSettings::setShowFolderTreeViewItemsCount(bool val)
{
    d->showFolderTreeViewItemsCount = val;
}

bool AlbumSettings::getShowFolderTreeViewItemsCount() const
{
    return d->showFolderTreeViewItemsCount;
}

void AlbumSettings::setShowThumbbar(bool val)
{
    d->showThumbbar = val;
}

bool AlbumSettings::getShowThumbbar() const
{
    return d->showThumbbar;
}

}  // namespace Digikam
