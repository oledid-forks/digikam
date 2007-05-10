/* ============================================================
 * File  : imageattributeswatch.h
 * Author: Marcel Wiesweg <marcel dot wiesweg at gmx dot de>
 * Date  : 2006-03-23
 * Description : Watch database image attributes
 * 
 * Copyright 2006 by Marcel Wiesweg
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

#ifndef DATABASEATTRIBUTESWATCH_H
#define DATABASEATTRIBUTESWATCH_H

// Qt includes

#include <qobject.h>

// KDE includes

#include <kurl.h>

#include "digikam_export.h"

namespace Digikam
{


class DIGIKAM_EXPORT DatabaseAttributesWatch : public QObject
{

    Q_OBJECT

    /**
     * This class notifies of changes in the database.
     * The context when these signals are emitted is important:
     * DatabaseAccess is locked when these signals are emitted,
     * but this allows direct notification immediately after the change.
     */

public:

    enum ImageDataField
    {
        ImageRating,
        ImageDate,
        ImageComment,
        ImageTags
    };

signals:

    /**
     * This signal indicates that the specified field of the
     * specified image has been changed.
     * (Note: there is no absolute guarantee
     *  that the field has actually been changed)
     */
    void imageFieldChanged(Q_LLONG imageId, int field);

protected:

    ~DatabaseAttributesWatch();

public:

    void sendImageFieldChanged(Q_LLONG imageId, ImageDataField field);

};


}

#endif
