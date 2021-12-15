// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityUI.h"
#include <QGuiApplication>
#include <QScreen>

QVector<int> UtilityUI::getScreenBounds() {
    QScreen * screen = QGuiApplication::primaryScreen();
    // int height = screen->availableSize().height();
    // int width = screen->availableSize().width();
    int height = screen->availableGeometry().height();
    int width = screen->availableGeometry().width();
    return {width, height};
}

int UtilityUI::getImageWidth(int numberOfImages) {
    auto dim = getScreenBounds();
    return static_cast<int>(dim[0] / numberOfImages) - 15;
}

void UtilityUI::updateImage(QLabel * label, const QByteArray& data, int imageSize) {
    const auto pixmap = QPixmap::fromImage(QImage::fromData(data));
    const double width = pixmap.width();
    const double height = pixmap.height();
    const auto pixmapResized = pixmap.scaled(imageSize, imageSize * (height / width), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pixmapResized);
}

void UtilityUI::removeChildren(QLayout * layout) {
    auto deleteWidgets = true;
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (deleteWidgets) {
            if (QWidget* widget = item->widget())
                widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout())
            removeChildren(childLayout);
        delete item;
    }
}
