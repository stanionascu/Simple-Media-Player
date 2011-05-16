#include "smpsystemimageprovider.h"

#include <QApplication>
#include <QStyle>
#include <QDebug>

SMPSystemImageProvider::SMPSystemImageProvider(QDeclarativeImageProvider::ImageType imageType) :
    QDeclarativeImageProvider(imageType)
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
