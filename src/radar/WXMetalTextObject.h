// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXMETALTEXTOBJECT_H
#define WXMETALTEXTOBJECT_H

#include <QVector>
#include "objects/FileStorage.h"
#include "radar/NexradState.h"

class WXMetalTextObject {
public:
    WXMetalTextObject(int, float, float, NexradState&, float, FileStorage *);
    void add();
    void addWpcPressureCenters();
    void addTextLabelsObservations();
    void addTextLabelsSpottersLabels();
    void initialize();

private:
    void initializeTextLabelsCitiesExtended();
    void initializeTextLabelsCountyLabels();
    void addTextLabelsCountyLabels();
    void addTextLabelsCitiesExtended();
    void checkAndDrawText(QVector<TextViewMetal> *, float, float, const QString&, bool = true);
    static const float cityMinZoom;
    static const float obsMinZoom;
    static const float countyMinZoom;
    static const int textSize;
    NexradState * nexradState;
    FileStorage * fileStorage;
    int numPanes;
    float glViewWidth;
    float glViewHeight;
    float screenScale;
    float scale;
    float fudgeFactor;
    float xFudge;
    float yFudge;
    float fudgeScaleFactor;
    int maxCitiesPerGlview;
};

#endif  // WXMETALTEXTOBJECT_H
