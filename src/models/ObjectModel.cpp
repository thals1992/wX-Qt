// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/ObjectModel.h"
#include "models/UtilityModelEsrlInterface.h"
#include "models/UtilityModelGlcfsInterface.h"
#include "models/UtilityModelNcepInterface.h"
#include "models/UtilityModelNsslWrfInterface.h"
#include "models/UtilityModelSpcHrefInterface.h"
#include "models/UtilityModelSpcHrrrInterface.h"
#include "models/UtilityModelSpcSrefInterface.h"
#include "models/UtilityModelWpcGefsInterface.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

ObjectModel::ObjectModel() {
}

ObjectModel::ObjectModel(const QString& prefModel) {
    this->prefModel = prefModel;
    timeIdx = 0;
    sectorInt = 0;
    prodIdx = 0;
    prefSector = "MODEL_" + prefModel + "_SECTOR_LAST_USED";
    prefParam = "MODEL_" + prefModel + "_PARAM_LAST_USED";
    prefRunPosn = prefModel + "_RUN_POSN";
    prefRunPosnIdx = prefModel + "_RUN_POSN" + "IDX";
    if (prefModel == "NSSLWRF") {
        run = "00Z";
        timeStr = "01";
        timeIdx = 1;
        param = "sfct";
        sector = "CONUS";
        model = "WRF";
        models = UtilityModelNsslWrfInterface::models;
    } else if (prefModel == "ESRL") {
        run = "00Z";
        timeStr = "01";
        timeIdx = 1;
        param = "1ref_sfc";
        model = "HRRR_NCEP";
        sector = "US";
        sectorInt = 0;
        models = UtilityModelEsrlInterface::models;
    } else if (prefModel == "GLCFS") {
        run = "00Z";
        timeStr = "01";
        timeIdx = 0;
        param = "wv";
        model = "GLCFS";
        models.clear();
        models << model;
        sector = "All Lakes";
    } else if (prefModel == "NCEP") {
        run = "00Z";
        timeStr = "003";
        timeIdx = 1;
        param = "500_vort_ht";
        model = "GFS";
        sector = "NAMER";
        models = UtilityModelNcepInterface::models;
    } else if (prefModel == "WPCGEFS") {
        run = "00Z";
        timeStr = "01";
        timeIdx = 1;
        param = "capegt500";
        sector = "US";
        sectorInt = 0;
        model = "WPCGEFS";
        models.clear();
        models << model;
    } else if (prefModel == "SPCHRRR") {
        prodIdx = 0;
        run = "00Z";
        timeStr = "01";
        timeIdx = 1;
        param = "sfc_prec";
        model = "HRRR";
        models.clear();
        models << model;
        sector = "National";
    } else if (prefModel == "SPCHREF") {
        prodIdx = 0;
        run = "00Z";
        timeStr = "01";
        timeIdx = 1;
        param = "500w_mean,500h_mean";
        model = "HREF";
        models.clear();
        models << model;
        sector = "CONUS";
    } else if (prefModel == "SPCSREF") {
        run = "00Z";
        timeStr = "03";
        timeIdx = 1;
        param = "SREF_H5__";
        model = "SREF";
    models.clear();
        models << model;
        sector = "US";
        sectors.clear();
        sectors << "US";
    }
    getPreferences();
}

void ObjectModel::getPreferences() {
    model = Utility::readPref(prefModel, model);
    param = Utility::readPref(prefParam, param);
    sector = Utility::readPref(prefSector, sector);
    timeStr = Utility::readPref(prefRunPosn, timeStr);
    timeIdx = Utility::readPrefInt(prefRunPosnIdx, timeIdx);
}

void ObjectModel::writePrefs() {
    Utility::writePref(prefModel, model);
    Utility::writePref(prefParam, param);
    Utility::writePref(prefSector, sector);
    Utility::writePref(prefRunPosn, timeStr);
    Utility::writePrefInt(prefRunPosnIdx, timeIdx);
}

void ObjectModel::loadTimeList(int from, int to, int by) {
    for (auto value : UtilityList::range3(from, to, by)) {
        times.push_back(To::StringPadLeftZeros(value, 2));
    }
}

void ObjectModel::loadTimeList3(int from, int to, int by) {
    for (auto value : UtilityList::range3(from, to, by)) {
        times.push_back(To::StringPadLeftZeros(value, 3));
    }
}

void ObjectModel::loadRunList(int from, int to, int by) {
    for (auto value : UtilityList::range3(from, to, by)) {
        runs.push_back(To::StringPadLeftZeros(value, 2) + "Z");
    }
}

void ObjectModel::setModelVars(const QString& modelName) {
    this->modelName = modelName;
    modelToken = prefModel + ":" + modelName;
    if (modelToken == "NSSLWRF:WRF") {
        params = UtilityModelNsslWrfInterface::paramsNsslWrf;
        paramLabels = UtilityModelNsslWrfInterface::labelsNsslWrf;
        sectors = UtilityModelNsslWrfInterface::sectorsLong;
        times.clear();
        loadTimeList(1, 36, 1);
    } else if (modelToken == "NSSLWRF:WRF_3KM") {
        params = UtilityModelNsslWrfInterface::paramsNsslWrf;
        paramLabels = UtilityModelNsslWrfInterface::labelsNsslWrf;
        sectors = UtilityModelNsslWrfInterface::sectorsLong;
        times.clear();
        loadTimeList(1, 36, 1);
    } else if (modelToken == "NSSLWRF:FV3") {
        params = UtilityModelNsslWrfInterface::paramsNsslFv3;
        paramLabels = UtilityModelNsslWrfInterface::labelsNsslFv3;
        sectors = UtilityModelNsslWrfInterface::sectorsLong;
        times.clear();
        loadTimeList(1, 60, 1);
    } else if (modelToken == "NSSLWRF:HRRRV3") {
        params = UtilityModelNsslWrfInterface::paramsNsslHrrrv3;
        paramLabels = UtilityModelNsslWrfInterface::labelsNsslHrrrv3;
        sectors = UtilityModelNsslWrfInterface::sectorsLong;
        times.clear();
        loadTimeList(1, 36, 1);
    } else if (modelToken == "ESRL:HRRR") {
        params = UtilityModelEsrlInterface::modelHrrrParams;
        paramLabels = UtilityModelEsrlInterface::modelHrrrLabels;
        sectors = UtilityModelEsrlInterface::sectorsHrrr;
        times.clear();
        loadTimeList(0, 36, 1);
    } else if (modelToken == "ESRL:HRRR_AK") {
        params = UtilityModelEsrlInterface::modelHrrrParams;
        paramLabels = UtilityModelEsrlInterface::modelHrrrLabels;
        sectors = UtilityModelEsrlInterface::sectorsHrrrAk;
        times.clear();
        loadTimeList(0, 36, 1);
    } else if (modelToken == "ESRL:HRRR_NCEP") {
        params = UtilityModelEsrlInterface::modelHrrrParams;
        paramLabels = UtilityModelEsrlInterface::modelHrrrLabels;
        sectors = UtilityModelEsrlInterface::sectorsHrrr;
        times.clear();
        loadTimeList(0, 36, 1);
    } else if (modelToken == "ESRL:RAP") {
        params = UtilityModelEsrlInterface::modelRapParams;
        paramLabels = UtilityModelEsrlInterface::modelRapLabels;
        sectors = UtilityModelEsrlInterface::sectorsRap;
        times.clear();
        loadTimeList(0, 21, 1);
    } else if (modelToken == "ESRL:RAP_NCEP") {
        params = UtilityModelEsrlInterface::modelRapParams;
        paramLabels = UtilityModelEsrlInterface::modelRapLabels;
        sectors = UtilityModelEsrlInterface::sectorsRap;
        times.clear();
        loadTimeList(0, 21, 1);
    } else if (modelToken == "GLCFS:GLCFS") {
        params = UtilityModelGlcfsInterface::params;
        paramLabels = UtilityModelGlcfsInterface::labels;
        sectors = UtilityModelGlcfsInterface::sectors;
        times.clear();
        loadTimeList(1, 13, 1);
        loadTimeList(15, 120, 3);
    } else if (modelToken == "NCEP:GFS") {
        params = UtilityModelNcepInterface::modelGfsParams;
        paramLabels = UtilityModelNcepInterface::modelGfsLabels;
        sectors = UtilityModelNcepInterface::sectorsGfs;
        times.clear();
        loadTimeList3(0, 243, 3);
        loadTimeList3(252, 396, 12);
        setupListRunZ();
    } else if (modelToken == "NCEP:HRRR") {
        params = UtilityModelNcepInterface::modelHrrrParams;
        paramLabels = UtilityModelNcepInterface::modelHrrrLabels;
        sectors = UtilityModelNcepInterface::sectorsHrrr;
        times.clear();
        loadTimeList3(0, 18, 1);
        runs.clear();
        loadRunList(0, 22, 1);
        runTimeData.listRun = runs;
    } else if (modelToken == "NCEP:RAP") {
        params = UtilityModelNcepInterface::modelRapParams;
        paramLabels = UtilityModelNcepInterface::modelRapLabels;
        sectors = UtilityModelNcepInterface::sectorsRap;
        times.clear();
        loadTimeList3(0, 21, 1);
        runs.clear();
        loadRunList(0, 22, 1);
        runTimeData.listRun = runs;
    } else if (modelToken == "NCEP:NAM-HIRES") {
        params = UtilityModelNcepInterface::modelNam4kmParams;
        paramLabels = UtilityModelNcepInterface::modelNam4kmLabels;
        sectors = UtilityModelNcepInterface::sectorsNam4km;
        times.clear();
        loadTimeList3(1, 61, 1);
        setupListRunZ();
    } else if (modelToken == "NCEP:NAM") {
        params = UtilityModelNcepInterface::modelNamParams;
        paramLabels = UtilityModelNcepInterface::modelNamLabels;
        sectors = UtilityModelNcepInterface::sectorsNam;
        times.clear();
        loadTimeList3(0, 85, 3);
        setupListRunZ();
    } else if (modelToken == "NCEP:HRW-FV3") {
        params = UtilityModelNcepInterface::modelHrwFv3Params;
        paramLabels = UtilityModelNcepInterface::modelHrwFv3Labels;
        sectors = UtilityModelNcepInterface::sectorsHrwNmm;
        times.clear();
        loadTimeList3(1, 49, 1);
        loadTimeList3(51, 61, 3);
        runs.clear();
        runs.push_back("00Z");
        runs.push_back("12Z");
        runTimeData.listRun = runs;
    } else if (modelToken == "NCEP:HRW-ARW") {
        params = UtilityModelNcepInterface::modelHrwNmmParams;
        paramLabels = UtilityModelNcepInterface::modelHrwNmmLabels;
        sectors = UtilityModelNcepInterface::sectorsHrwNmm;
        times.clear();
        loadTimeList3(1, 48, 1);
        runs.clear();
        runs.push_back("00Z");
        runs.push_back("12Z");
        runTimeData.listRun = runs;
    } else if (modelToken == "NCEP:HRW-ARW2") {
        params = UtilityModelNcepInterface::paramsHrwArw2;
        paramLabels = UtilityModelNcepInterface::labelsHrwArw2;
        sectors = UtilityModelNcepInterface::sectorsHrwArw2;
        times.clear();
        loadTimeList3(1, 48, 1);
        runs.clear();
        runs.push_back("00Z");
        runs.push_back("12Z");
        runTimeData.listRun = runs;
    } else if (modelToken == "NCEP:HREF") {
        params = UtilityModelNcepInterface::paramsHref;
        paramLabels = UtilityModelNcepInterface::labelsHref;
        sectors = UtilityModelNcepInterface::sectorsHref;
        times.clear();
        loadTimeList3(1, 36, 1);
        runs.clear();
        runs.push_back("00Z");
        runs.push_back("06Z");
        runs.push_back("12Z");
        runs.push_back("18Z");
        runTimeData.listRun = runs;
    } else if (modelToken == "NCEP:NBM") {
        params = UtilityModelNcepInterface::paramsNbm;
        paramLabels = UtilityModelNcepInterface::labelsNbm;
        sectors = UtilityModelNcepInterface::sectorsNbm;
        times.clear();
        loadTimeList3(0, 264, 3);
        runs.clear();
        runs.push_back("00Z");
        runs.push_back("06Z");
        runs.push_back("12Z");
        runs.push_back("18Z");
        runTimeData.listRun = runs;
    } else if (modelToken == "NCEP:GEFS-SPAG") {
        params = UtilityModelNcepInterface::modelGefsSpagParams;
        paramLabels = UtilityModelNcepInterface::modelGefsSpagLabels;
        sectors = UtilityModelNcepInterface::sectorsGefsSpag;
        times.clear();
        loadTimeList3(0, 180, 6);
        loadTimeList3(192, 384, 12);
        setupListRunZ();
    } else if (modelToken == "NCEP:GEFS-MEAN-SPRD") {
        params = UtilityModelNcepInterface::modelGefsMnsprdParams;
        paramLabels = UtilityModelNcepInterface::modelGefsMnsprdLabels;
        sectors = UtilityModelNcepInterface::sectorsGefsMnsprd;
        times.clear();
        loadTimeList3(0, 180, 6);
        loadTimeList3(192, 384, 12);
        setupListRunZ();
    } else if (modelToken == "NCEP:SREF") {
        params = UtilityModelNcepInterface::modelSrefParams;
        paramLabels = UtilityModelNcepInterface::modelSrefLabels;
        sectors = UtilityModelNcepInterface::sectorsSref;
        times.clear();
        loadTimeList3(0, 87, 3);
        setupListRunZ03();
    } else if (modelToken == "NCEP:NAEFS") {
        params = UtilityModelNcepInterface::modelNaefsParams;
        paramLabels = UtilityModelNcepInterface::modelNaefsLabels;
        sectors = UtilityModelNcepInterface::sectorsNaefs;
        times.clear();
        loadTimeList3(0, 384, 6);
        setupListRunZ();
    } else if (modelToken == "NCEP:POLAR") {
        params = UtilityModelNcepInterface::modelPolarParams;
        paramLabels = UtilityModelNcepInterface::modelPolarLabels;
        sectors = UtilityModelNcepInterface::sectorsPolar;
        times.clear();
        loadTimeList3(0, 384, 24);
        runs.clear();
        runs.push_back("00Z");
        runTimeData.listRun = runs;
    } else if (modelToken == "NCEP:WW3") {
        params = UtilityModelNcepInterface::modelWw3Params;
        paramLabels = UtilityModelNcepInterface::modelWw3Labels;
        sectors = UtilityModelNcepInterface::sectorsWw3;
        times.clear();
        loadTimeList3(0, 126, 6);
        setupListRunZ();
    } else if (modelToken == "NCEP:ESTOFS") {
        params = UtilityModelNcepInterface::modelEstofsParams;
        paramLabels = UtilityModelNcepInterface::modelEstofsLabels;
        sectors = UtilityModelNcepInterface::sectorsEstofs;
        times.clear();
        loadTimeList3(0, 180, 1);
        setupListRunZ();
    } else if (modelToken == "NCEP:FIREWX") {
        params = UtilityModelNcepInterface::modelFirewxParams;
        paramLabels = UtilityModelNcepInterface::modelFirewxLabels;
        sectors = UtilityModelNcepInterface::sectorsFirewx;
        times.clear();
        loadTimeList3(0, 37, 1);
        setupListRunZ();
    } else if (modelToken == "WPCGEFS:WPCGEFS") {
        params = UtilityModelWpcGefsInterface::params;
        paramLabels = UtilityModelWpcGefsInterface::labels;
        sectors = UtilityModelWpcGefsInterface::sectors;
        times.clear();
        loadTimeList3(0, 240, 6);
        runs = runTimeData.listRun;
    } else if (modelToken == "SPCHRRR:HRRR") {
        params = UtilityModelSpcHrrrInterface::params;
        paramLabels = UtilityModelSpcHrrrInterface::labels;
        sectors = UtilityModelSpcHrrrInterface::sectors;
        times.clear();
        loadTimeList(2, 15, 1);
        runs = runTimeData.listRun;
    } else if (modelToken == "SPCHREF:HREF") {
        params = UtilityModelSpcHrefInterface::params;
        paramLabels = UtilityModelSpcHrefInterface::labels;
        sectors = UtilityModelSpcHrefInterface::sectorsLong;
        times.clear();
        loadTimeList(1, 49, 1);
        runs = runTimeData.listRun;
    } else if (modelToken == "SPCSREF:SREF") {
        params = UtilityModelSpcSrefInterface::params;
        paramLabels = UtilityModelSpcSrefInterface::labels;
        sectors.clear();
        sectors.push_back("US");
        times.clear();
        loadTimeList3(0, 90, 3);
        runs = runTimeData.listRun;
    }
    if (sectors.size() > 0) {
        if (!sectors.contains(sector)) {
            sector = sectors[0];
        }
    }
    if (!params.contains(param)) {
        if (params.size() > 0) {
            param = params[0];
        }
    }
}

QString ObjectModel::getTime() {
    if (timeStr.contains(" ")) {
        return timeStr.split(" ")[0];
    }
    return timeStr;
}

void ObjectModel::setupListRunZ() {
    runs.clear();
    runs.push_back("00Z");
    runs.push_back("06Z");
    runs.push_back("12Z");
    runs.push_back("18Z");
    runTimeData.listRun = runs;
}

void ObjectModel::setupListRunZ03() {
    runs.clear();
    runs.push_back("03Z");
    runs.push_back("09Z");
    runs.push_back("15Z");
    runs.push_back("21Z");
    runTimeData.listRun = runs;
}

void ObjectModel::assignTimeIdxF(int timeIdxF) {
    if (timeIdxF > -2 && timeIdxF < times.size()) {
        timeIdx = timeIdxF;
        timeStr = times[timeIdx];
    }
}

void ObjectModel::timeIdxIncr() {
    timeIdx += 1;
    timeStr = Utility::safeGet(times, timeIdx);
}

void ObjectModel::timeIdxDecr() {
    timeIdx -= 1;
    timeStr = Utility::safeGet(times, timeIdx);
}

void ObjectModel::leftClick() {
    if (timeIdx == 0) {
        assignTimeIdxF(times.size() - 1);
    } else {
        timeIdxDecr();
    }
}

void ObjectModel::rightClick() {
    if (timeIdx == times.size() - 1) {
        assignTimeIdxF(0);
    } else {
        timeIdxIncr();
    }
}

void ObjectModel::setTimeArr(int idx, const QString& time) {
    times[idx] = time;
}
