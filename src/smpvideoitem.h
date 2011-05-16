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

#ifndef SMPVIDEOITEM_H
#define SMPVIDEOITEM_H

#include <QDeclarativeItem>

class SMPVideoItemPrivate;

class SMPVideoItem : public QDeclarativeItem
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QSizeF resolution READ resolution WRITE setResolution NOTIFY resolutionChanged)
    Q_PROPERTY(qreal aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)
    Q_PROPERTY(qint64 duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenChanged)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    explicit SMPVideoItem(QDeclarativeItem *parent = 0);
    virtual ~SMPVideoItem();

    QString source() const;
    QSizeF resolution() const;
    qreal aspectRatio() const;
    qint64 duration() const;
    qint64 position() const;
    bool fullscreen() const;
    int volume() const;

Q_SIGNALS:
    void sourceChanged();
    void resolutionChanged();
    void aspectRatioChanged();
    void durationChanged();
    void positionChanged();
    void fullscreenChanged();
    void volumeChanged();
    void started();
    void stopped();

public Q_SLOTS:
    void setSource(const QString &source);
    void setResolution(const QSizeF &resolution);
    void setAspectRatio(qreal aspectRatio);
    void setDuration(qint64 duration);
    void setPosition(qint64 position);
    void setFullscreen(bool fullscreen);
    void setVolume(int volume);

    void play();
    void pause();
    void resume();

private:
    Q_DECLARE_PRIVATE(SMPVideoItem)
    SMPVideoItemPrivate *d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_updateDisplaySize())

};

#endif // SMPVIDEOITEM_H
