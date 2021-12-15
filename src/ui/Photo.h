// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef PHOTO_H
#define PHOTO_H

#include <QLabel>
#include "ui/PhotoSizeEnum.h"

class Photo {
public:
    Photo();
    explicit Photo(QWidget *);
    Photo(QWidget *, const QPixmap &);
    Photo(QWidget *, PhotoSizeEnum);
    void set(const QPixmap &);
    void setAlignment(Qt::Alignment);
    void setFullScreen(const QByteArray&);
    void setNoScale(const QByteArray&);
    void setToWidth(const QByteArray&, int);
    void setToWidthEven(const QByteArray&);
    void setBytes(const QByteArray&);
    void setNwsIcon(QString);
    QLabel * get();

private:
    QLabel * image;
    PhotoSizeEnum size;
    int width;
};

#endif  // PHOTO_H
