/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2017-05-25
 * Description : a tool to generate video slideshow from images.
 *
 * Copyright (C) 2017-2019 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_VIDSLIDE_ALBUMS_PAGE_H
#define DIGIKAM_VIDSLIDE_ALBUMS_PAGE_H

// Qt includes

#include <QList>
#include <QUrl>
#include <QString>

// Local includes

#include "dwizardpage.h"

using namespace Digikam;

namespace DigikamGenericVideoSlideShowPlugin
{

class VidSlideAlbumsPage : public DWizardPage
{
public:

    explicit VidSlideAlbumsPage(QWizard* const dialog, const QString& title);
    ~VidSlideAlbumsPage();

    bool validatePage();
    bool isComplete() const;

private:

    class Private;
    Private* const d;
};

} // namespace DigikamGenericVideoSlideShowPlugin

#endif // DIGIKAM_VIDSLIDE_ALBUMS_PAGE_H
