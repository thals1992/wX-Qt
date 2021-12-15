// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDHAZARDS_H
#define OBJECTCARDHAZARDS_H

#include <QString>
#include <QWidget>
#include "ui/Button.h"
#include "ui/VBox.h"
#include "util/ObjectHazards.h"

class ObjectCardHazards : public VBox {
public:
    explicit ObjectCardHazards();
    ObjectCardHazards(QWidget *, const ObjectHazards&);
    void removeLabels();

private:
    void launchAlert(const QString&);
    VBox vbox;
    QWidget * parent;
    QString data;
    QVector<Button *> labels;
};

#endif  // OBJECTCARDHAZARDS_H
