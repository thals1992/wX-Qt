// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef PHOTO_H
#define PHOTO_H

#include <string>
#include <QLabel>
#include "ui/PhotoSizeEnum.h"

using std::string;

class Photo {
public:
    Photo();  //  needed for ObjectCardCurrentConditions
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
    void setNwsIcon(const string&);
    QLabel * get();

private:
    QLabel * image{};
    PhotoSizeEnum size{};
    int width{};
};

#endif  // PHOTO_H
