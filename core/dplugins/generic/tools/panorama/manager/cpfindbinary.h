/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2011-05-23
 * Description : Autodetects cpfind binary program and version
 *
 * Copyright (C) 2011-2016 by Benjamin Girault <benjamin dot girault at gmail dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef DIGIKAM_CPFIND_BINARY_H
#define DIGIKAM_CPFIND_BINARY_H

// Local includes

#include "dbinaryiface.h"

using namespace Digikam;

namespace DigikamGenericPanoramaPlugin
{

class CPFindBinary : public DBinaryIface
{

public:

    explicit CPFindBinary()
        : DBinaryIface(QLatin1String("cpfind"),
                       QLatin1String("2010.4"),
                       QString(),
                       0,
                       QLatin1String("Hugin"),
                       QLatin1String("http://hugin.sourceforge.net/download/"),
                       QLatin1String("Panorama"),
                       QStringList(QLatin1String("--version"))
                      ),
          headerRegExp(QLatin1String("^Hugin'?s cpfind( Pre-Release)? (\\d+\\.\\d+(\\.\\d+)?)(\\D.*)?$"))
        {
            setup();
        }

    ~CPFindBinary()
    {
    }

protected:

    virtual bool parseHeader(const QString& output);

private:

    QRegExp headerRegExp;
};

} // namespace DigikamGenericPanoramaPlugin

#endif // DIGIKAM_CPFIND_BINARY_H
