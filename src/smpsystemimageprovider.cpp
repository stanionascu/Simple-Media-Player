/************************************************************************************
** Simple Media Player, allows to watch videos with simple and uncluttered interface.
** Copyright (C) 2011 Stanislav Ionascu
**
** Contact: Stanislav Ionascu <stanislav.ionascu@gmail.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.

** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.

** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************************/

#include "smpsystemimageprovider.h"

#include <QApplication>
#include <QStyle>
#include <QDebug>

SMPSystemImageProvider::SMPSystemImageProvider(QQuickImageProvider::ImageType imageType) :
    QQuickImageProvider(imageType)
{
}

SMPSystemImageProvider::~SMPSystemImageProvider()
{
}

QPixmap SMPSystemImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize);
    QPixmap result;
    if (id.toLower() == "media-play")
        result = QApplication::style()->standardPixmap(QStyle::SP_MediaPlay);
    else if (id.toLower() == "media-pause")
        result = QApplication::style()->standardPixmap(QStyle::SP_MediaPause);
    else if (id.toLower() == "media-ffwd")
        result = QApplication::style()->standardPixmap(QStyle::SP_MediaSeekForward);
    else if (id.toLower() == "media-fbwd")
        result = QApplication::style()->standardPixmap(QStyle::SP_MediaSeekBackward);

    *size = result.size();

    return result;
}
