// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include <QApplication>
#include <QDebug>
#include "common/GlobalVariables.h"
#include "radar/Nexrad.h"
#include "ui/MainWindow.h"
#include "util/MyApplication.h"

int main(int argc, char * argv[]) {
    QApplication a{argc, argv};
    // qDebug() << a.arguments();
    MyApplication::onCreate();
    a.setWindowIcon(QIcon{QString::fromStdString(GlobalVariables::imageDir) + "wx_launcher.png"});
    if (a.arguments().size() == 3 && a.arguments()[1] == "-r") {
        // TODO FIXME
        // Nexrad r(nullptr, 1, true, a.arguments()[2], false);
        // r.show();
        return a.exec();
    } else {
        MainWindow w;
        w.show();
        return a.exec();
    }
    // return a.exec();
}
