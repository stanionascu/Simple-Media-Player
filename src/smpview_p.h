#ifndef SMPVIEW_P_H
#define SMPVIEW_P_H

#include <QtGlobal>

class SMPView;

class SMPViewPrivate
{
public:
    SMPViewPrivate();
    ~SMPViewPrivate();

private:
    Q_DECLARE_PUBLIC(SMPView)
    SMPView *q_ptr;

    bool forceAspectRatio;
    qreal aspectRatio;
};

#endif // SMPVIEW_P_H
