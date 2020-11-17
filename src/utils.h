#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

#define MIN_AGE_STREAMER 12
#define MIN_AGE_VIEWER 15

/// Unsigned type for representing an age
typedef unsigned Age;
/// String type for representing a language, in the predefined format
typedef std::string Language;

/**
 * Combination of the day, month and year of a date
 */
struct Date {
    Date() = default;
    Date(unsigned day, unsigned month, unsigned year);
    unsigned day;
    unsigned month;
    unsigned year;
};

std::ostream& operator<< (std::ostream& out, const Date& date);

std::string strToUpper(const std::string& str);

/*
enum Language{
    AB, AA, AF, AK, SQ, AM, AR, AN, HY, AS, AV, AE, AY, AZ, BM, BA, EU, BE, BN, BH, BI, BS, BR, BG, MY, CA, CH, CE, NY, ZH, CV, KW, CO, CR, HR, CS, DA, DV, NL, DZ, EN, EO, ET, EE, FO, FJ, FI, FR, FF, GL, KA, DE, EL, GN, GU, HT, HA, HE, HZ, HI, HO, HU, IA, ID, IE, GA, IG, IK, IO, IS, IT, IU, JA, JV, KL, KN, KR, KS, KK, KM, KI, RW, KY, KV, KG, KO, KU, KJ, LA, LB, LG, LI, LN, LO, LT, LU, LV, GV, MK, MG, MS, ML, MT, MI, MR, MH, MN, NA, NV, ND, NE, NG, NB, NN, NO, II, NR, OC, OJ, CU, OM, OR, OS, PA, PI, FA, PL, PS, PT, QU, RM, RN, RO, RU, SA, SC, SD, SE, SM, SG, SR, GD, SN, SI, SK, SL, SO, ST, ES, SU, SW, SS, SV, TA, TE, TG, TH, TI, BO, TK, TL, TN, TO, TR, TS, TT, TW, TY, UG, UK, UR, UZ, VE, VI, VO, WA, CY, WO, FY, XH, YI, YO, ZA, ZU
};
*/

#endif //UTILS_H