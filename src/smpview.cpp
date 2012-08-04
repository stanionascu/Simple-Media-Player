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

#include "smpview.h"
#include "smpview_p.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsObject>
#include <QDebug>

#include <QResizeEvent>

SMPViewPrivate::SMPViewPrivate() :
    forceAspectRatio(false),
    aspectRatio(1.0)
{
}

SMPViewPrivate::~SMPViewPrivate()
{
}

SMPView::SMPView(QWindow *parent) :
    QQuickView(parent),
    d_ptr(new SMPViewPrivate)
{
    d_ptr->q_ptr = this;
}

SMPView::~SMPView()
{
    delete d_ptr;
}

QSize SMPView::desktopSize() const
{
    return QApplication::desktop()->size();
}

bool SMPView::forceAspectRatio() const
{
    Q_D(const SMPView);
    return d->forceAspectRatio;
}

void SMPView::setForceAspectRatio(bool enabled)
{
    Q_D(SMPView);
    d->forceAspectRatio = enabled;
    emit forceAspectRatioChanged();
}

qreal SMPView::aspectRatio() const
{
    Q_D(const SMPView);
    return d->aspectRatio;
}

void SMPView::setAspectRatio(qreal ratio)
{
    Q_D(SMPView);
    d->aspectRatio = ratio;
    emit aspectRatioChanged();
}

void SMPView::resize(int w, int h)
{
    QQuickView::resize(w, h);
}

void SMPView::resizeEvent(QResizeEvent *event)
{
    if (forceAspectRatio()) {
        qreal ratio = (qreal)event->size().width() / (qreal)event->size().height();
        if (ratio != aspectRatio()) {
            resize(event->size().width(), event->size().width() / aspectRatio());
        }
    }
    QQuickView::resizeEvent(event);
}
