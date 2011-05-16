#ifndef SMPVIEW_H
#define SMPVIEW_H

#include <QDeclarativeView>

class SMPViewPrivate;

class SMPView : public QDeclarativeView
{
    Q_OBJECT

    Q_PROPERTY(QSize desktopSize READ desktopSize)
    Q_PROPERTY(bool forceAspectRatio READ forceAspectRatio WRITE setForceAspectRatio NOTIFY forceAspectRatioChanged)
    Q_PROPERTY(qreal aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)
public:
    SMPView(QWidget *parent = 0);
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
