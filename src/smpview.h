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

#ifndef SMPVIEW_H
#define SMPVIEW_H

#include <QQuickView>

class SMPViewPrivate;

class SMPView : public QQuickView
{
    Q_OBJECT

    Q_PROPERTY(QSize desktopSize READ desktopSize)
    Q_PROPERTY(bool forceAspectRatio READ forceAspectRatio WRITE setForceAspectRatio NOTIFY forceAspectRatioChanged)
    Q_PROPERTY(qreal aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)
public:
    SMPView(QWindow *parent = 0);
    virtual ~SMPView();

    QSize desktopSize() const;
    bool forceAspectRatio() const;
    qreal aspectRatio() const;

Q_SIGNALS:
    void forceAspectRatioChanged();
    void aspectRatioChanged();

public Q_SLOTS:
    void setForceAspectRatio(bool enabled);
    void setAspectRatio(qreal ratio);
    void resize(int w, int h);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Q_DECLARE_PRIVATE(SMPView)
    SMPViewPrivate *d_ptr;
};

#endif // SMPVIEW_H
