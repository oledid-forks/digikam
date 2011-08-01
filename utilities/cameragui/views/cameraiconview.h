/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2004-09-18
 * Description : camera icon view
 *
 * Copyright (C) 2004-2005 by Renchi Raju <renchi@pooh.tam.uiuc.edu>
 * Copyright (C) 2006-2011 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2009 by Andi Clemens <andi dot clemens at gmx dot net>
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

#ifndef CAMERAICONVIEW_H
#define CAMERAICONVIEW_H

// Qt includes

#include <QRect>
#include <QDropEvent>

// KDE includes

#include <kurl.h>

// Local includes

#include "iconview.h"
#include "renamecustomizer.h"
#include "camiteminfo.h"

class QPixmap;
class KPixmapSequence;

namespace Digikam
{

class ThumbnailSize;
class RenameCustomizer;
class CameraUI;
class CameraIconItem;

class CameraIconView : public IconView
{
    Q_OBJECT

public:

    CameraIconView(CameraUI* ui, QWidget* parent);
    ~CameraIconView();

    void setRenameCustomizer(RenameCustomizer* renamer);

    void addItem(const CamItemInfo& itemInfo);
    void removeItem(const QString& folder, const QString& file);

    void setThumbnail(const QString& folder, const QString& filename, const QImage& image);
    void setItemInfo(const QString& folder, const QString& filename, const CamItemInfo& itemInfo);

    void ensureItemVisible(CameraIconItem* item);
    void ensureItemVisible(const CamItemInfo& itemInfo);
    void ensureItemVisible(const QString& folder, const QString& file);

    void setThumbnailSize(int thumbSize);
    int  thumbnailSize() const;

    CameraIconItem* findItem(const QString& folder, const QString& file) const;

    CameraIconItem* firstItemSelected() const;

    int countItemsByFolder(const QString& folder) const;
    int itemsDownloaded() const;

    QPixmap itemBaseRegPixmap()      const;
    QPixmap itemBaseSelPixmap()      const;
    QPixmap newPicturePixmap()       const;
    QPixmap downloadUnknownPixmap()  const;
    QPixmap lockedPixmap()           const;
    QPixmap downloadedPixmap()       const;
    QPixmap downloadFailedPixmap()   const;
    KPixmapSequence progressPixmap() const;

    QString defaultDownloadName(CameraIconItem* item) const;

    void itemsSelectionSizeInfo(unsigned long& fSize, unsigned long& dSize);

    virtual QRect itemRect() const;

Q_SIGNALS:

    void signalSelected(const CamItemInfo&, bool);
    void signalFileView(const CamItemInfo&);
    void signalThumbSizeChanged(int);

    void signalUpload(const KUrl::List&);
    void signalDownload();
    void signalDownloadAndDelete();
    void signalDelete();
    void signalToggleLock();
    void signalNewSelection(bool);

public Q_SLOTS:

    void slotDownloadNameChanged();
    void slotSelectionChanged();
    void slotSelectAll();
    void slotSelectNone();
    void slotSelectInvert();
    void slotSelectNew();
    void slotSelectLocked();

private Q_SLOTS:

    void slotRightButtonClicked(const QPoint& pos);
    void slotContextMenu(IconItem* item, const QPoint& pos);
    void slotDoubleClicked(IconItem* item);
    void slotThemeChanged();
    void slotUpdateDownloadNames(bool hasSelection);
    void slotShowToolTip(IconItem* item);

protected:

    void startDrag();
    void contentsDragEnterEvent(QDragEnterEvent* e);
    void contentsDropEvent(QDropEvent* e);
    void updateItemRectsPixmap();
    bool acceptToolTip(IconItem* item, const QPoint& mousePos);

private:

    QString getTemplatedName(const CamItemInfo& itemInfo) const;
    QString getCasedName(const RenameCustomizer::Case ccase, const CamItemInfo& itemInfo) const;
    void    uploadItemPopupMenu(const KUrl::List& srcURLs);

private:

    class CameraIconViewPriv;
    CameraIconViewPriv* const d;
};

}  // namespace Digikam

#endif /* CAMERAICONVIEW_H */
