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

#include "smpvideoitem.h"
#include "smpvideoitem_p.h"

#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QDeclarativeView>
#include <QMediaPlayer>
#include <QMediaContent>

SMPVideoItemPrivate::SMPVideoItemPrivate() :
    player(0),
    display(0)
{

}

SMPVideoItemPrivate::~SMPVideoItemPrivate()
{
    delete player;
    delete display;
}

void SMPVideoItemPrivate::init()
{
    Q_Q(SMPVideoItem);
    player = new QMediaPlayer(q);
    display = new QGraphicsVideoItem(q);

    player->setVideoOutput(display);
}

void SMPVideoItemPrivate::connect()
{
    Q_Q(SMPVideoItem);

    q->connect(q, SIGNAL(widthChanged()), q, SLOT(_q_updateDisplaySize()));
    q->connect(q, SIGNAL(heightChanged()), q, SLOT(_q_updateDisplaySize()));

    q->connect(display, SIGNAL(nativeSizeChanged(QSizeF)), q, SLOT(setResolution(QSizeF)));
    q->connect(player, SIGNAL(durationChanged(qint64)), q, SLOT(setDuration(qint64)));
    q->connect(player, SIGNAL(positionChanged(qint64)), q, SIGNAL(positionChanged()));
    q->connect(player, SIGNAL(volumeChanged(int)), q, SIGNAL(volumeChanged()));
}

void SMPVideoItemPrivate::_q_updateDisplaySize()
{
    Q_Q(SMPVideoItem);
    display->setSize(QSizeF(q->width(), q->height()));
}

SMPVideoItem::SMPVideoItem(QDeclarativeItem *parent) :
    QDeclarativeItem(parent),
    d_ptr(new SMPVideoItemPrivate)
{
    d_ptr->q_ptr = this;
    d_ptr->init();
    d_ptr->connect();
}

SMPVideoItem::~SMPVideoItem()
{
    delete d_ptr;
}

QString SMPVideoItem::source() const
{
    Q_D(const SMPVideoItem);
    return d->content.canonicalUrl().toString();
}

void SMPVideoItem::setSource(const QString &source)
{
    Q_D(SMPVideoItem);
    d->content = QMediaContent(QUrl::fromUserInput(source));
    emit sourceChanged();
}

QSizeF SMPVideoItem::resolution() const
{
    Q_D(const SMPVideoItem);
    return d->display->nativeSize();
}

void SMPVideoItem::setResolution(const QSizeF &resolution)
{
    Q_UNUSED(resolution);
    emit resolutionChanged();
    setAspectRatio(resolution.width() / resolution.height());
}

qreal SMPVideoItem::aspectRatio() const
{
    QSizeF videoResolution = resolution();
    qreal result = videoResolution.width() / videoResolution.height();
    return result;
}

void SMPVideoItem::setAspectRatio(qreal aspectRatio)
{
    Q_UNUSED(aspectRatio);
    emit aspectRatioChanged();
}

qint64 SMPVideoItem::duration() const
{
    Q_D(const SMPVideoItem);
    return d->player->duration();
}

void SMPVideoItem::setDuration(qint64 duration)
{
    Q_UNUSED(duration);
    emit durationChanged();
}

qint64 SMPVideoItem::position() const
{
    Q_D(const SMPVideoItem);
    return d->player->position();
}

void SMPVideoItem::setPosition(qint64 position)
{
    Q_D(SMPVideoItem);
    if (d->player->isSeekable())
        d->player->setPosition(position);
    else
        qWarning() << "This stream does not support seeking...";
}

bool SMPVideoItem::fullscreen() const
{
    Q_D(const SMPVideoItem);
    return scene()->views().at(0)->isFullScreen();
}

void SMPVideoItem::setFullscreen(bool fullscreen)
{
    if (fullscreen)
        scene()->views().at(0)->showFullScreen();
    else
        scene()->views().at(0)->showNormal();
    emit fullscreenChanged();
}

int SMPVideoItem::volume() const
{
    Q_D(const SMPVideoItem);
    return d->player->volume();
}

void SMPVideoItem::setVolume(int volume)
{
    Q_D(SMPVideoItem);
    d->player->setVolume(volume);
}

void SMPVideoItem::play()
{
    Q_D(SMPVideoItem);
    d->player->setMedia(d->content);
    d->player->play();
    emit started();
}

void SMPVideoItem::pause()
{
    Q_D(SMPVideoItem);
    d->player->pause();
    emit stopped();
}

void SMPVideoItem::resume()
{
    Q_D(SMPVideoItem);
    d->player->play();
    emit started();
}

#include "moc_smpvideoitem.cpp"
