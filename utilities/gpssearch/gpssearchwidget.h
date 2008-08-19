/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2008-05-30
 * Description : a widget to search image over a map.
 *
 * Copyright (C) 2008 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef GPSSEARCHWIDGET_H
#define GPSSEARCHWIDGET_H

// Qt includes.

#include <QLabel>
#include <QList>

// KDE includes.

#include <klocale.h>

// Local includes.

#include "config-digikam.h"

#ifdef HAVE_MARBLEWIDGET
#include <marble/MarbleWidget.h>
using namespace Marble;
#endif // HAVE_MARBLEWIDGET

namespace Digikam
{

#ifdef HAVE_MARBLEWIDGET

class GPSSearchWidgetPriv;

class GPSSearchWidget : public MarbleWidget
{
    Q_OBJECT

public:

    GPSSearchWidget(QWidget *parent=0);
    ~GPSSearchWidget();

    bool asSelection() const;

    QList<double> selectionCoordinates() const;
    void setSelectionCoordinates(const QList<double>&);

signals:

    void signalNewSelection();

private slots:

    void slotNewSelection(const QList<double>&);

private:

    GPSSearchWidgetPriv *d;
};

#else // HAVE_MARBLEWIDGET

class GPSSearchWidget : public QLabel
{
    Q_OBJECT

public:

    GPSSearchWidget(QWidget *parent=0)
    {
        setText(i18n("Geolocation using Marble not available"));
        setWordWrap(true);
    };

    ~GPSSearchWidget(){};

    bool asSelection() const { return false; };

    QList<double> selectionCoordinates() const { return QList<double>(); };
    void setSelectionCoordinates(const QList<double>&){};

    int zoom(){ return 5; };
    double centerLongitude(){ return 0.0; };
    double centerLatitude(){ return 0.0; };
    void zoomView(int) {};
    void setCenterLongitude(double) {};
    void setCenterLatitude(double) {};

signals:

    void signalNewSelection();
};

#endif // HAVE_MARBLEWIDGET

}  // namespace Digikam

#endif // GPSSEARCHWIDGET_H
