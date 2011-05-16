#ifndef SMPSYSTEMIMAGEPROVIDER_H
#define SMPSYSTEMIMAGEPROVIDER_H

#include <QDeclarativeImageProvider>

class SMPSystemImageProvider : public QDeclarativeImageProvider
{
public:
    SMPSystemImageProvider(QDeclarativeImageProvider::ImageType imageType = QDeclarativeImageProvider::Pixmap);
    virtual ~SMPSystemImageProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
};

#endif // SMPSYSTEMIMAGEPROVIDER_H
