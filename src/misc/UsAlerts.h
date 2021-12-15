// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef USALERTS_H
#define USALERTS_H

#include "misc/CapAlertXml.h"
#include "ui/ComboBox.h"
#include "ui/Photo.h"
#include "ui/ScrolledWindow.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class UsAlerts : public Window {
public:
    explicit UsAlerts(QWidget *);

private:
    void downloadCap();
    void updateText();
    void filterEvents();
    static int count(const QString&, const QStringList&);
    ComboBox comboBox;
    VBox box;
    VBox boxCombo;
    VBox boxText;
    QVector<CapAlertXml> capAlerts;
    QStringList defaultFilter = {"Tornado Warning", "Severe Thunderstorm Warning", "Flash Flood Warning"};
    QStringList eventList;
    QHash<QString, int> filterCount;
    QString html;
    Photo photo;
    ScrolledWindow sw;
};

#endif  // USALERTS_H
