/* ============================================================
 *
 * This file is a part of digiKam project
 * http://www.digikam.org
 *
 * Date        : 2009-02-06
 * Description : Thread actions manager.
 *
 * Copyright (C) 2009 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef ACTIONTHREAD_H
#define ACTIONTHREAD_H

// Qt includes.

#include <QThread>

// KDE includes.

#include <kurl.h>

// Local includes.

#include "batchtool.h"
#include "actions.h"

namespace Digikam
{

class ActionThreadPriv;

class ActionThread : public QThread
{
    Q_OBJECT

public:

    ActionThread(QObject *parent);
    ~ActionThread();

    void setWorkingUrl(const KUrl& workingUrl);
    void setExifSetOrientation(bool set);

    void processFile(const AssignedBatchTools& item);

    void cancel();

signals:

    void starting(const ActionData& ad);
    void finished(const ActionData& ad);

protected:

    void run();

private:

    ActionThreadPriv* const d;
};

}  // namespace Digikam

#endif /* ACTIONTHREAD_H */
