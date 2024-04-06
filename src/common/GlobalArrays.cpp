// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "common/GlobalArrays.h"
#include <algorithm>
#include "objects/WString.h"
#include "util/UtilityList.h"

string GlobalArrays::getRadarCodeAtIndex(int index) {
    auto radarDescription = radars()[index];
    return WString::split(radarDescription, ":")[0];
}

vector<string> GlobalArrays::radars() {
    vector<string> radarList{nexradRadars};
    addAll(radarList, tdwrRadars);
    return radarList;
}

vector<string> GlobalArrays::tdwrRadarCodes() {
    vector<string> radarList;
    std::transform(tdwrRadars.begin(), tdwrRadars.end(), std::back_inserter(radarList),
                    [] (const auto& s) -> string { return WString::split(s, ":")[0]; });
    return radarList;
}

vector<string> GlobalArrays::nexradRadarCodes() {
    vector<string> radarList;
    std::transform(nexradRadars.begin(), nexradRadars.end(), std::back_inserter(radarList),
                    [] (const auto& s) -> string { return WString::split(s, ":")[0]; });
    return radarList;
}

const vector<string> GlobalArrays::wfos{
    "AFC: AK, Anchorage",
    "AFG: AK, Fairbanks",
    "AJK: AK, Juneau",
    "BMX: AL, Birmingham",
    "HUN: AL, Huntsville",
    "MOB: AL, Mobile",
    "LZK: AR, Little Rock",
    "FGZ: AZ, Flagstaff",
    "PSR: AZ, Phoenix",
    "TWC: AZ, Tucson",
    "EKA: CA, Eureka",
    "HNX: CA, Hanford",
    "LOX: CA, Los Angeles",
    "MTR: CA, San Francisco",
    "SGX: CA, San Diego",
    "STO: CA, Sacramento",
    "BOU: CO, Denver/Boulder",
    "GJT: CO, Grand Junction",
    "PUB: CO, Pueblo",
    "JAX: FL, Jacksonville",
    "KEY: FL, Key West",
    "MFL: FL, Miami",
    "MLB: FL, Melbourne",
    "TAE: FL, Tallahassee",
    "TBW: FL, Tampa Bay Area",
    "FFC: GA, Atlanta",
    "GUM: GU, Guam",
    "HFO: HI, Honolulu",
    "DMX: IA, Des Moines",
    "DVN: IA, Quad Cities",
    "BOI: ID, Boise",
    "PIH: ID, Pocatello",
    "ILX: IL, Lincoln",
    "LOT: IL, Chicago",
    "IND: IN, Indianapolis",
    "IWX: IN, Nrn. Indiana",
    "DDC: KS, Dodge City",
    "GLD: KS, Goodland",
    "ICT: KS, Wichita",
    "TOP: KS, Topeka",
    "JKL: KY, Jackson",
    "LMK: KY, Louisville",
    "PAH: KY, Paducah",
    "LCH: LA, Lake Charles",
    "HDC: LA, Hammond",
    "SHV: LA, Shreveport",
    "BOX: MA, Boston",
    "CAR: ME, Caribou",
    "GYX: ME, Gray",
    "APX: MI, Gaylord",
    "DTX: MI, Detroit",
    "GRR: MI, Grand Rapids",
    "MQT: MI, Marquette",
    "DLH: MN, Duluth",
    "MPX: MN, Twin Cities",
    "EAX: MO, Kansas City",
    "LSX: MO, St. Louis",
    "SGF: MO, Springfield",
    "JAN: MS, Jackson",
    "BYZ: MT, Billings",
    "GGW: MT, Glasgow",
    "MSO: MT, Missoula",
    "TFX: MT, Great Falls",
    "ILM: NC, Wilmington",
    "MHX: NC, Morehead City",
    "RAH: NC, Raleigh",
    "BIS: ND, Bismarck",
    "FGF: ND, Grand Forks",
    "GID: NE, Hastings",
    "LBF: NE, North Platte",
    "OAX: NE, Omaha",
    "PHI: NJ, Mount Holly",
    "ABQ: NM, Albuquerque",
    "LKN: NV, Elko",
    "REV: NV, Reno",
    "VEF: NV, Las Vegas",
    "ALY: NY, Albany",
    "BGM: NY, Binghamton",
    "BUF: NY, Buffalo",
    "OKX: NY, New York City",
    "CLE: OH, Cleveland",
    "ILN: OH, Wilmington",
    "OUN: OK, Norman",
    "TSA: OK, Tulsa",
    "MFR: OR, Medford",
    "PDT: OR, Pendleton",
    "PQR: OR, Portland",
    "CTP: PA, State College",
    "PBZ: PA, Pittsburgh",
    "SJU: PR, San Juan",
    "CAE: SC, Columbia",
    "CHS: SC, Charleston",
    "GSP: SC, Greer",
    "ABR: SD, Aberdeen",
    "FSD: SD, Sioux Falls",
    "UNR: SD, Rapid City",
    "MEG: TN, Memphis",
    "MRX: TN, Morristown",
    "OHX: TN, Nashville",
    "AMA: TX, Amarillo",
    "BRO: TX, Brownsville",
    "CRP: TX, Corpus Christi",
    "EPZ: TX, El Paso",
    "EWX: TX, Austin/San Antonio",
    "FWD: TX, Dallas/Fort Worth",
    "HGX: TX, Houston",
    "LUB: TX, Lubbock",
    "MAF: TX, Midland/Odessa",
    "SJT: TX, San Angelo",
    "SLC: UT, Salt Lake City",
    "AKQ: VA, Wakefield",
    "LWX: VA, Sterling",
    "RNK: VA, Blacksburg",
    "BTV: VT, Burlington",
    "OTX: WA, Spokane",
    "SEW: WA, Seattle",
    "ARX: WI, La Crosse",
    "GRB: WI, Green Bay",
    "MKX: WI, Milwaukee",
    "RLX: WV, Charleston",
    "CYS: WY, Cheyenne",
    "RIW: WY, Riverton"
};

const vector<string> GlobalArrays::nexradRadars{
    "ABC: AK, Bethel",
    "APD: AK, Fairbanks/Pedro Dome",
    "AHG: AK, Kenai",
    "AKC: AK, King Salmon",
    "AIH: AK, Middleton Island",
    "AEC: AK, Nome",
    "ACG: AK, Sitka/Biorka Island",
    "BMX: AL, Birmingham",
    "EOX: AL, Fort Rucker",
    "HTX: AL, Huntsville",
    "MXX: AL, Maxwell AFB",
    "MOB: AL, Mobile",
    "SRX: AR, Fort Smith",
    "LZK: AR, Little Rock",
    "FSX: AZ, Flagstaff",
    "IWA: AZ, Phoenix",
    "EMX: AZ, Tucson",
    "YUX: AZ, Yuma",
    "BBX: CA, Beale AFB",
    "EYX: CA, Edwards AFB",
    "BHX: CA, Eureka",
    "VTX: CA, Los Angeles",
    "DAX: CA, Sacramento",
    "NKX: CA, San Diego",
    "MUX: CA, San Francisco",
    "HNX: CA, San Joaquin Valley",
    "SOX: CA, Santa Ana Mountains",
    "VBX: CA, Vandenberg AFB",
    "FTG: CO, Denver",
    "GJX: CO, Grand Junction",
    "PUX: CO, Pueblo",
    "DOX: DE, Dover AFB",
    "EVX: FL, Eglin AFB",
    "JAX: FL, Jacksonville",
    "BYX: FL, Key West",
    "MLB: FL, Melbourne",
    "AMX: FL, Miami",
    "TLH: FL, Tallahassee",
    "TBW: FL, Tampa",
    "FFC: GA, Atlanta",
    "VAX: GA, Moody AFB",
    "JGX: GA, Robins AFB",
    "GUA: GU, Andersen AFB",
    "HKI: HI, Kauai",
    "HKM: HI, Kohala",
    "HMO: HI, Molokai",
    "HWA: HI, South Shore",
    "DVN: IA, Davenport",
    "DMX: IA, Des Moines",
    "CBX: ID, Boise",
    "SFX: ID, Pocatello/Idaho Falls",
    "LOT: IL, Chicago",
    "ILX: IL, Lincoln",
    "VWX: IN, Evansville",
    "IND: IN, Indianapolis",
    "IWX: IN, North Webster",
    "DDC: KS, Dodge City",
    "GLD: KS, Goodland",
    "TWX: KS, Topeka",
    "ICT: KS, Wichita",
    "HPX: KY, Fort Campbell",
    "JKL: KY, Jackson",
    "LVX: KY, Louisville",
    "PAH: KY, Paducah",
    "POE: LA, Fort Polk",
    "LCH: LA, Lake Charles",
    "LIX: LA, New Orleans",
    "SHV: LA, Shreveport",
    "BOX: MA, Boston",
    "CBW: ME, Loring AFB",
    "GYX: ME, Portland",
    "DTX: MI, Detroit/Pontiac",
    "APX: MI, Gaylord",
    "GRR: MI, Grand Rapids",
    "MQT: MI, Marquette",
    "DLH: MN, Duluth",
    "MPX: MN, Minneapolis/St. Paul",
    "EAX: MO, Kansas City",
    "SGF: MO, Springfield",
    "LSX: MO, St. Louis",
    "DGX: MS, Brandon/Jackson",
    "GWX: MS, Columbus AFB",
    "BLX: MT, Billings",
    "GGW: MT, Glasgow",
    "TFX: MT, Great Falls",
    "MSX: MT, Missoula",
    "MHX: NC, Morehead City",
    "RAX: NC, Raleigh/Durham",
    "LTX: NC, Wilmington",
    "BIS: ND, Bismarck",
    "MVX: ND, Grand Forks (Mayville)",
    "MBX: ND, Minot AFB",
    "UEX: NE, Grand Island/Hastings",
    "LNX: NE, North Platte",
    "OAX: NE, Omaha",
    "ABX: NM, Albuquerque",
    "FDX: NM, Cannon AFB",
    "HDX: NM, Holloman AFB",
    "LRX: NV, Elko",
    "ESX: NV, Las Vegas",
    "RGX: NV, Reno",
    "ENX: NY, Albany",
    "BGM: NY, Binghamton",
    "BUF: NY, Buffalo",
    "TYX: NY, Montague",
    "OKX: NY, New York City",
    "CLE: OH, Cleveland",
    "ILN: OH, Wilmington",
    "FDR: OK, Frederick",
    "TLX: OK, Oklahoma City",
    "INX: OK, Tulsa",
    "VNX: OK, Vance AFB",
    "MAX: OR, Medford",
    "PDT: OR, Pendleton",
    "RTX: OR, Portland",
    "DIX: PA, Philadelphia",
    "PBZ: PA, Pittsburgh",
    "CCX: PA, State College",
    "JUA: PR, San Juan",
    "CLX: SC, Charleston",
    "CAE: SC, Columbia",
    "GSP: SC, Greer",
    "ABR: SD, Aberdeen",
    "UDX: SD, Rapid City",
    "FSD: SD, Sioux Falls",
    "MRX: TN, Knoxville/Tri Cities",
    "NQA: TN, Memphis",
    "OHX: TN, Nashville",
    "AMA: TX, Amarillo",
    "EWX: TX, Austin/San Antonio",
    "BRO: TX, Brownsville",
    "CRP: TX, Corpus Christi",
    "FWS: TX, Dallas/Ft. Worth",
    "DYX: TX, Dyess AFB",
    "EPZ: TX, El Paso",
    "GRK: TX, Fort Hood",
    "HGX: TX, Houston/Galveston",
    "DFX: TX, Laughlin AFB",
    "LBB: TX, Lubbock",
    "MAF: TX, Midland/Odessa",
    "SJT: TX, San Angelo",
    "ICX: UT, Cedar City",
    "MTX: UT, Salt Lake City",
    "AKQ: VA, Norfolk/Richmond",
    "FCX: VA, Roanoke",
    "LWX: VA, Sterling",
    "CXX: VT, Burlington",
    "LGX: WA, Langley Hill",
    "ATX: WA, Seattle/Tacoma",
    "OTX: WA, Spokane",
    "GRB: WI, Green Bay",
    "ARX: WI, La Crosse",
    "MKX: WI, Milwaukee",
    "RLX: WV, Charleston",
    "CYS: WY, Cheyenne",
    "RIW: WY, Riverton",
};

const vector<string> GlobalArrays::tdwrRadars{
    "TPHX: AZ, Phoenix",
    "TDEN: CO, Denver",
    "TFLL: FL, Fort Lauderdale",
    "TMIA: FL, Miami",
    "TMCO: FL, Orlando International",
    "TTPA: FL, Tampa Bay",
    "TPBI: FL, West Palm Beach",
    "TATL: GA, Atlanta",
    "TMDW: IL, Chicago Midway",
    "TORD: IL, Chicago O'Hare",
    "TIDS: IN, Indianapolis",
    "TICH: KS, Wichita",
    "TSDF: KY, Louisville",
    "TMSY: LA, New Orleans",
    "TBOS: MA, Boston",
    "TBWI: MD, Baltimore/Wash",
    "TDCA: MD, Washington National",
    "TDTW: MI, Detroit",
    "TMSP: MN, Minneapolis",
    "TMCI: MO, Kansas City",
    "TSTL: MO, St Louis",
    "TCLT: NC, Charlotte",
    "TRDU: NC, Raleigh Durham",
    "TEWR: NJ, Newark",
    "TLAS: NV, Las Vegas",
    "TJFK: NY, New York City",
    "TLVE: OH, Cleveland",
    "TCMH: OH, Columbus",
    "TCVG: OH, Covington",
    "TDAY: OH, Dayton",
    "TOKC: OK, Oklahoma City",
    "TTUL: OK, Tulsa",
    "TPHL: PA, Philadelphia",
    "TPIT: PA, Pittsburgh",
    "TSJU: PR, San Juan",
    "TMEM: TN, Memphis",
    "TBNA: TN, Nashville",
    "TDFW: TX, Dallas/Ft. Worth",
    "TDAL: TX, Dallas Love Field",
    "THOU: TX, Houston Hobby",
    "TIAH: TX, Houston International",
    "TSLC: UT, Salt Lake City",
    "TIAD: VA, Dulles",
    "TMKE: WI, Milwaukee"
};
