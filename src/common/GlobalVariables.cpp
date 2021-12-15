// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "common/GlobalVariables.h"

const QString GlobalVariables::appName = "wxqt";
const QString GlobalVariables::aboutString(
appName + " is an efficient and configurable method to access weather content from the NWS, NSSL WRF, and blitzortung.org."
" Software is provided \"as is\". Use at your own risk. Use for educational purposes and non-commercial purposes only."
" Do not use for operational purposes.  Copyright 2020, 2021 joshua.tee@gmail.com ."
" Privacy Policy: this app does not collect any data from the user or the user’s device."
" Please report bugs or suggestions via email. "
 + appName + " is licensed under the GNU GPLv3 license. For more information on the license please go here:"
" http://www.gnu.org/licenses/gpl-3.0.en.html"
);

const QString GlobalVariables::mainScreenShortcuts = R"mainScreenShort(
    Ctrl-a - WFO Viewer
    Ctrl-c - GOES
    Ctrl-d - Severe Dashboard
    Ctrl-f - SPC Fireweather Summary
    Ctrl-h - Hourly
    Ctrl-i - National Images
    Ctrl-l - Lightning
    Ctrl-m - Radad Mosaic
    Ctrl-n - NCEP Model Viewer
    Ctrl-o - NHC
    Ctrl-q or Ctrl-w or Escape - Quit program
    Ctrl-r - Nexrad
    Ctrl-s - SPC Convective Outlook Summary
    Ctrl-t - National text products
    Ctrl-u - update, reload data
    Ctrl-z - SPC Mesoanalaysis
    Ctrl-1 - single pane nexrad
    Ctrl-2 - dual pane nexrad
    Ctrl-4 - quad pane nexrad
    Ctrl-w or Escape - close window

    NOTE: Most screens that have a left/right button combination support Ctrl-LeftArrow and Ctrl-RightArrow

    SPC Convective Outlook Summary supports Ctrl-1, Ctrl-2, etc for access to Days 1, 2, etc

    Screens with animation support Ctrl-a to stop/start

    )mainScreenShort";


const QString GlobalVariables::nexradShortcuts = R"nexradShort(

    Ctrl-DownArrow - down
    Ctrl-UpArrow - up
    Ctrl-LeftArrow - left
    Ctrl-RightArrow - right
    Ctrl--  zoom out
    Ctrl-+  zoom in

    Ctrl-a animate (stops animation if one is going)
    Ctrl-u start/stop auto update
    Ctrl-w close window
    Ctrl-/ show shortcuts (this window)

    Ctrl-r Base Reflectivity
    Ctrl-v Basr Velocity
    Ctrl-t Enhanced Echo Tops
    Ctrl-l Vertically Integrated Liquid
    Ctrl-c Correlation Coefficient

    You can right click in the radar to open a contextual menu.

    )nexradShort";

const QString GlobalVariables::appCreatorEmail = "joshua.tee@gmail.com";
const QString GlobalVariables::resDir = ":/res/";
const QString GlobalVariables::imageDir = ":/images/";
const QString GlobalVariables::newline = "\n";
const QString GlobalVariables::degreeSymbol = QString::fromUtf8("°");
const QString GlobalVariables::nwsSPCwebsitePrefix = "https://www.spc.noaa.gov";;
const QString GlobalVariables::nwsWPCwebsitePrefix = "https://www.wpc.ncep.noaa.gov";
const QString GlobalVariables::nwsAWCwebsitePrefix = "https://www.aviationweather.gov";
const QString GlobalVariables::nwsGraphicalWebsitePrefix = "https://graphical.weather.gov";
const QString GlobalVariables::nwsCPCNcepWebsitePrefix = "https://www.cpc.ncep.noaa.gov";
const QString GlobalVariables::nwsGoesWebsitePrefix = "https://www.goes.noaa.gov";
const QString GlobalVariables::nwsOpcWebsitePrefix = "https://ocean.weather.gov";
const QString GlobalVariables::nwsNhcWebsitePrefix = "https://www.nhc.noaa.gov";
const QString GlobalVariables::nwsRadarWebsitePrefix = "https://radar.weather.gov";
const QString GlobalVariables::nwsMagNcepWebsitePrefix = "https://mag.ncep.noaa.gov";
const QString GlobalVariables::nwsSwpcWebSitePrefix = "https://services.swpc.noaa.gov";
const QString GlobalVariables::goes16Url = "https://cdn.star.nesdis.noaa.gov/";
const QString GlobalVariables::nwsApiUrl = "https://api.weather.gov/";
const QString GlobalVariables::tgftpSitePrefix = "https://tgftp.nws.noaa.gov/";
const QString GlobalVariables::prePattern = "<pre.*?>(.*?)</pre>";
const QString GlobalVariables::pre2Pattern = "<pre>(.*?)</pre>";
const QString GlobalVariables::vtecPattern = "([A-Z0]{1}\\.[A-Z]{3}\\.[A-Z]{4}\\.[A-Z]{2}\\.[A-Z]\\.[0-9]{4}\\.[0-9]{6}T[0-9]{4}Z\\-[0-9]{6}T[0-9]{4}Z)";
const QString GlobalVariables::warningLatLonPattern = "\"coordinates\":\\[\\[(.*?)\\]\\]\\}";
const QString GlobalVariables::utilUsPeriodNamePattern = ".*?period-name=(.*?)>.*?";
const QString GlobalVariables::xmlValuePattern = "<value>";
