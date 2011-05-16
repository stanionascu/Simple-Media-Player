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

#include <QApplication>
#include <QDebug>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDesktopWidget>
#include <QFileInfo>
#include <QGraphicsVideoItem>
#include <QMediaContent>
#include <QMediaPlayer>

#include <QGLWidget>

#include "smpview.h"
#include "smpvideoitem.h"
#include "smpsystemimageprovider.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    qmlRegisterType<SMPView>("com.ionascu.SMP", 1, 0, "View");
    qmlRegisterType<SMPVideoItem>("com.ionascu.SMP", 1, 0, "VideoItem");

    QGLWidget *viewport = new QGLWidget;
    SMPView *view = new SMPView;
    view->setViewport(viewport);
    view->setBackgroundBrush(Qt::black);
    view->setViewportUpdateMode(SMPView::FullViewportUpdate);
    view->setResizeMode(SMPView::SizeRootObjectToView);
    view->engine()->addImageProvider("system", new SMPSystemImageProvider);

    if (app.arguments().count() > 1) {
        QString filePath = app.arguments().at(1);
        view->rootContext()->setContextProperty("currentVideo", QUrl::fromLocalFile(filePath));
        view->rootContext()->setContextProperty("window", view);
        qDebug() << "Opening " << filePath << "...";
        view->setWindowTitle(QFileInfo(filePath).fileName());
    }

    view->setSource(QUrl("qrc:///qml/main.qml"));
    view->move(0, 0);
    view->show();

    return app.exec();
}
