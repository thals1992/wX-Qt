// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include "models/RunTimeData.h"

class ObjectModel {
public:
    ObjectModel();
    explicit ObjectModel(const QString&);
    void getPreferences();
    void writePrefs();
    void setModelVars(const QString&);
    QString getTime();
    void setupListRunZ();
    void setupListRunZ03();
    void assignTimeIdxF(int);
    void timeIdxIncr();
    void timeIdxDecr();
    void leftClick();
    void rightClick();
    void setTimeArr(int, const QString&);
    QString prefModel;
    QString modelName;
    QStringList params;
    QStringList paramLabels;
    QStringList sectors;
    QStringList times;
    QStringList runs;
    QStringList models;
    RunTimeData runTimeData;
    QString modelToken;
    QString prefSector;
    QString prefParam;
    QString prefRunPosn;
    QString prefRunPosnIdx;
    QString model;
    QString run;
    QString timeStr;
    int timeIdx;
    QString param;
    QString sector;
    int sectorInt;
    int prodIdx;

private:
    void loadTimeList(int, int, int);
    void loadTimeList3(int, int, int);
    void loadRunList(int, int, int);
};

#endif  // OBJECTMODEL_H
