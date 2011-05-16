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

SMPView::SMPView(QWidget *parent) :
    QDeclarativeView(parent),
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
    QDeclarativeView::resize(w, h);
}

void SMPView::resizeEvent(QResizeEvent *event)
{
    if (forceAspectRatio() && !isFullScreen()) {
        qreal ratio = (qreal)event->size().width() / (qreal)event->size().height();
        if (ratio != aspectRatio()) {
            resize(event->size().width(), event->size().width() / aspectRatio());
        }
    }
    QDeclarativeView::resizeEvent(event);
}
