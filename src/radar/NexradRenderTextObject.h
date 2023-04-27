// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXMETALTEXTOBJECT_H
#define WXMETALTEXTOBJECT_H

#include <string>
#include <vector>
#include "objects/FileStorage.h"
#include "radar/NexradState.h"

using std::string;
using std::vector;

class NexradRenderTextObject {
public:
    NexradRenderTextObject(int, NexradState&, FileStorage *);
    void add();
    void addWpcPressureCenters();
    void addTextLabelsObservations();
    void initialize();

private:
    void initializeTextLabelsCitiesExtended() const;
    static void initializeTextLabelsCountyLabels();
    void addTextLabelsCountyLabels();
    void addTextLabelsCitiesExtended();
    void checkAndDrawText(vector<TextViewMetal> *, double, double, const string&, bool = true);
    static const float cityMinZoom;
    static const float obsMinZoom;
    static const float countyMinZoom;
    NexradState * nexradState;
    int numPanes;
    FileStorage * fileStorage;
    size_t maxCitiesPerGlview;
};

#endif  // WXMETALTEXTOBJECT_H
