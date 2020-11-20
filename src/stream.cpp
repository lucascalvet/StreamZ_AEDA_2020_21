#include "stream.h"
#include "exceptions.h"
#include <algorithm>
#include <sstream>

using namespace std;

/// All the possible languages a stream may have
const vector<Language> Stream::LANGS = {"AB", "AA", "AF", "AK", "SQ", "AM", "AR", "AN", "HY", "AS", "AV", "AE", "AY",
                                        "AZ", "BM", "BA", "EU", "BE", "BN", "BH", "BI", "BS", "BR", "BG", "MY", "CA",
                                        "CH", "CE", "NY", "ZH", "CV", "KW", "CO", "CR", "HR", "CS", "DA", "DV", "NL",
                                        "DZ", "EN", "EO", "ET", "EE", "FO", "FJ", "FI", "FR", "FF", "GL", "KA", "DE",
                                        "EL", "GN", "GU", "HT", "HA", "HE", "HZ", "HI", "HO", "HU", "IA", "ID", "IE",
                                        "GA", "IG", "IK", "IO", "IS", "IT", "IU", "JA", "JV", "KL", "KN", "KR", "KS",
                                        "KK", "KM", "KI", "RW", "KY", "KV", "KG", "KO", "KU", "KJ", "LA", "LB", "LG",
                                        "LI", "LN", "LO", "LT", "LU", "LV", "GV", "MK", "MG", "MS", "ML", "MT", "MI",
                                        "MR", "MH", "MN", "NA", "NV", "ND", "NE", "NG", "NB", "NN", "NO", "II", "NR",
                                        "OC", "OJ", "CU", "OM", "OR", "OS", "PA", "PI", "FA", "PL", "PS", "PT", "QU",
                                        "RM", "RN", "RO", "RU", "SA", "SC", "SD", "SE", "SM", "SG", "SR", "GD", "SN",
                                        "SI", "SK", "SL", "SO", "ST", "ES", "SU", "SW", "SS", "SV", "TA", "TE", "TG",
                                        "TH", "TI", "BO", "TK", "TL", "TN", "TO", "TR", "TS", "TT", "TW", "TY", "UG",
                                        "UK", "UR", "UZ", "VE", "VI", "VO", "WA", "CY", "WO", "FY", "XH", "YI", "YO",
                                        "ZA", "ZU"};

/**
 * Constructs a stream object
 *
 * @param title the stream´s title
 * @param lang the stream's language (must be one of the languages in LANG)
 * @param min_age the stream's minimum age
 */
Stream::Stream(const string &title, const Language &lang, unsigned min_age) {
    this->title = title;
    string lang_upper = strToUpper(lang);
    if (find(LANGS.begin(), LANGS.end(), lang_upper) == LANGS.end())
        throw InvalidLanguage(lang);
    this->lang = lang_upper;
    this->min_age = min_age;
    this->starting_date = getCurrentDate();
}

/**
 * Constructs a stream object with attributes usually set at runtime (for loading from a file)
 *
 * @param title the stream´s title
 * @param lang the stream's language (must be one of the languages in LANG)
 * @param min_age the stream's minimum age
 * @param starting_date the stream's starting date
 * @param num_viewers the stream's number of viewers
 */
Stream::Stream(const string &title, const Language &lang, unsigned min_age,
               const Date &starting_date, unsigned num_total_views) {
    this->title = title;
    string lang_upper = strToUpper(lang);
    if (find(LANGS.begin(), LANGS.end(), lang_upper) == LANGS.end())
        throw InvalidLanguage(lang);
    this->lang = lang_upper;
    this->min_age = min_age;
    this->starting_date = starting_date;
    this->num_total_views = num_total_views;
}

/**
 * Gets a formatted string with the information of the stream (its title, starting date, language and minimum age)
 *
 * @return a string with the stream's information
 */
string Stream::getInfo() const {
    ostringstream info;
    info << "Title: " << this->title << "\tStarting Date: " << this->starting_date <<
         "\tLanguage: " << this->lang << "\tMin Age: " << this->min_age << '\n';
    return info.str();
}

/**
 * Gets the stream's title
 *
 * @return a string with the stream's title
 */
string Stream::getTitle() const {
    return this->title;
}

/**
 * Gets the stream's starting date
 *
 * @return a Date object with the stream's starting date
 */
Date Stream::getDate() const {
    return this->starting_date;
}

/**
 * Gets the stream's language
 *
 * @return the stream's language in the predefined language initials
 */
Language Stream::getLanguage() const {
    return this->lang;
}

/**
 * Gets the stream's minimum viewing age
 *
 * @return the stream's minimum viewing age
 */
Age Stream::getMinAge() const {
    return this->min_age;
}

/**
 * Get the number of total views of the stream
 * @return the number of total views
 */
unsigned int Stream::getNumTotalViews() const {
    return this->num_total_views;
}

/**
 * Get the number of likes on the stream
 *
 * @return the number of likes
 */
unsigned Stream::getNumLikes() const {
    return viewers_liked.size();
}

/**
 * Get the number of dislikes on the stream
 *
 * @return the number of dislikes
 */
unsigned Stream::getNumDislikes() const {
    return viewers_disliked.size();
}

/**
 * Add a view to the total view count
 */
void Stream::addView() {
    num_total_views++;
}

/**
 * Add a like to the stream
 *
 * @param id the viewer's id
 * @return
 */
bool Stream::addLike(unsigned id) {
    if (alreadyLikedOrDisliked(id)) return false;
    viewers_liked.push_back(id);
    return true;
}

/**
 * Add a dislike to the stream
 *
 * @param id the viewer's id
 * @return
 */
bool Stream::addDislike(unsigned id) {
    if (alreadyLikedOrDisliked(id)) return false;
    viewers_disliked.push_back(id);
    return true;
}

/**
 * Remove a like from the stream
 *
 * @param id the viewer's id
 * @return
 */
bool Stream::remLike(unsigned id) {
    vector<unsigned>::iterator viewer = find(viewers_liked.begin(), viewers_liked.end(), id);
    if (viewer == viewers_liked.end()) return false;
    viewers_liked.erase(viewer);
    return true;
}

/**
 * Remove a dislike from the stream
 *
 * @param id the viewer's id
 * @return
 */
bool Stream::remDislike(unsigned id) {
    vector<unsigned>::iterator viewer = find(viewers_disliked.begin(), viewers_disliked.end(), id);
    if (viewer == viewers_disliked.end()) return false;
    viewers_disliked.erase(viewer);
    return true;
}

/**
 * Checks if a viewer has already liked or disliked the stream
 *
 * @param id the viewer's id
 * @return true if a viewer has already liked or disliked the stream, false otherwise
 */
bool Stream::alreadyLikedOrDisliked(unsigned id) {
    if (find(viewers_liked.begin(), viewers_liked.end(), id) != viewers_liked.end())
        return true;
    if (find(viewers_disliked.begin(), viewers_disliked.end(), id) != viewers_disliked.end())
        return true;
    return false;
}

/**
 * Constructs a public stream
 *
 * Just calls the constructor for a stream, since it doesn't have unique methods or attributes
 *
 * @param title the stream's title
 * @param lang the stream's language (must be one of the languages in LANG)
 * @param min_age the stream's minimum age
 */
PublicStream::PublicStream(string title, Language lang, Age min_age) : Stream(title, lang, min_age) {
}

PublicStream::~PublicStream() {
}

/**
 * Constructs a private stream
 *
 * @param title the stream's title
 * @param lang the stream's language (must be one of the languages in LANG)
 * @param min_age the stream's minimum age
 */
PrivateStream::PrivateStream(string title, Language lang, Age min_age, vector<unsigned> authorized_viewers) : Stream(
        title, lang, min_age) {
    this->authorized_viewers = authorized_viewers;
}

PrivateStream::~PrivateStream() {
}

/**
 * Gets a formatted string with the normal information of the stream plus the information of the private stream
 *
 * @return a string with the private stream's information
 */
std::string PrivateStream::getInfo() const {
    ostringstream info;
    info << Stream::getInfo();
    if (!authorized_viewers.empty()) {
        info << "\nAuthorized Viewers (ID's): ";
        vector<unsigned>::const_iterator viewer;
        for (viewer = authorized_viewers.begin(); viewer != authorized_viewers.end(); viewer++) {
            info << *viewer;
            if (viewer == authorized_viewers.end()-1) info << ", ";
        }
        info << '\n';
    } else info << "\nNo authorized viewers. No one will be able to enter the stream!\n";
    if (!comments.empty()) {
        info << "\nComments:\n";
        vector<string>::const_iterator comment;
        for (comment = comments.begin(); comment != comments.end(); comment++) {
            info << "-->" <<  *comment << '\n';
        }
    } else info << "\nNo comments.\n";
    info << '\n';
    return info.str();
}

/**
 * Gets the private stream's list of authorized viewers
 *
 * @return a vector with the id's of the authorized viewers
 */
const vector<unsigned int> &PrivateStream::getAuthorizedViewers() const {
    return authorized_viewers;
}

/**
 * Get the comments on the private stream
 * @return a vector with the comments
 */
const vector<std::string> &PrivateStream::getComments() const {
    return comments;
}

/**
 * Check if a viewer is authorized in a private stream
 *
 * @param user_id the viewer's id
 * @return true if the viewer is authorized, false otherwise
 */
bool PrivateStream::isAuthorized(unsigned int user_id) const {
    return find(authorized_viewers.begin(), authorized_viewers.end(), user_id) != authorized_viewers.end();
}

/**
 * Add a comment to the private stream
 * @param comment the comment to be added
 */
void PrivateStream::addComment(const string &comment) {
    comments.push_back(comment);
}

