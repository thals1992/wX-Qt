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
#include "ui/Widget2.h"

using std::string;

class Photo : public Widget2 {
public:
    Photo();  //  needed for CardCurrentConditions
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
    QLabel * getView();

private:
    QLabel * image{};
    PhotoSizeEnum size{};
    int width{};
};

#endif  // PHOTO_H
