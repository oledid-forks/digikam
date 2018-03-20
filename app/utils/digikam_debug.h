/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2014-09-08
 * Description : digiKam debug spaces
 *
 * Copyright (C) 2014      by Laurent Montel <montel at kde dot org>
 * Copyright (C) 2015      by Mohamed Anwer <m dot anwer at gmx dot com>
 * Copyright (C) 2014-2018 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef DIGIKAM_DEBUG_H
#define DIGIKAM_DEBUG_H

// Qt includes

#include <QLoggingCategory>

// Local includes

#include "digikam_export.h"

DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_GENERAL_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_WIDGETS_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_IOJOB_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_SHOWFOTO_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_WEBSERVICES_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DATABASESERVER_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_IMPORTUI_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_METAENGINE_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_FACESENGINE_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_RAWENGINE_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_GEOIFACE_LOG)

// Databases debug spaces

DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DATABASE_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DBENGINE_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DBJOB_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_COREDB_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_FACEDB_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_THUMBSDB_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_SIMILARITYDB_LOG)

// DImg debug spaces

DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_JPEG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_JP2K)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_PGF)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_PNG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_PPM)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_TIFF)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_RAW)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_DIMG_LOG_QIMAGE)

// MediaServer debug spaces

DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_DEBUG)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_INFO)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_WARN)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_SEVERE)
DIGIKAM_EXPORT Q_DECLARE_LOGGING_CATEGORY(DIGIKAM_MEDIASRV_LOG_FATAL)

#endif // DIGIKAM_DEBUG_H
