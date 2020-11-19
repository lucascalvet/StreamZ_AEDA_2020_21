#include "user.h"
#include <sstream>

using namespace std;

///Static member to have unique id's to each user
unsigned User::counter = 0;

/**
 * Constructs a user object
 *
 * @param nickname the user's nickname
 * @param birthday the user's date of birth
 */
User::User(string nickname, Date birthday) {
    this->nickname = nickname;
    this->birthday = birthday;
    id = counter++;
}

User::~User() {
    delete s;
}

/**
 * Gets the user's name
 *
 * @return the user's name
 */
string User::getName() const {
    return nickname;
}

/**
 * Gets the user's ID
 *
 * @return the user's ID
 */
unsigned User::getID() const {
    return id;
}

/**
 * Gets the user's date of birth
 *
 * @return the user's date of birth
 */
Date User::getBirthday() const {
    return birthday;
}

/**
 * Prints the user's information
 *
 * @return a string with the user's name, id, and date of birth
 */
string User::getInfo() {
    ostringstream info;
    info << "Name: " << nickname;
    info << "\tId: " << to_string(getID());
    info << "\tBirthday: " << getBirthday() << endl;
    return info.str();
}

/**
 * Checks if a user is active.
 *
 * If the user is a viewer, checks if it is viewing any stream.
 * If the user is a streamer, checks if it is streaming
 *
 * @return the user's active state
 */
bool User::isActive() const {
    return s != nullptr;
}

/**
 * Constructs a viewer object
 *
 * @param nickname the viewer's nickname
 * @param birthday the viewer's date of birth
 */
Viewer::Viewer(string nickname, Date birthday) : User(nickname, birthday) {
}

Viewer::~Viewer() {
}

/**
 * Prints the viewer's information
 *
 * @return a string with the viewer's information
 */
string Viewer::getInfo() {
    ostringstream info;
    info << User::getInfo();
    info << "Viewing: " << to_string(isActive()) << endl;
    if (isActive()) {
        info << "Stream: " << s->getInfo() << endl;
    }
    return info.str();
}

bool Viewer::comment(const string &comment) {
    if(!isActive()) return false;
    PrivateStream* viewing_stream = dynamic_cast<PrivateStream *>(s);
    if (viewing_stream == nullptr) return false;
    viewing_stream->addComment(comment);
    return true;
}

/**
 * Constructs a streamer object
 *
 * @param nickname the streamer's nickname
 * @param birthday the streamer's date of birth
 */
Streamer::Streamer(string nickname, Date birthday, unsigned total_views) : User(nickname, birthday) {
    this->total_views = total_views;
}

Streamer::~Streamer() {
    vector<Stream *>::iterator stream;
    for (stream = streaming_history.begin(); stream != streaming_history.end(); stream++) {
        delete *stream;
    }
}

/**
 * Gets the streamer's total views
 *
 * @return the streamer's number of total views
 */
unsigned Streamer::getTotalViews() const {
    return total_views;
}

std::vector<Stream *> Streamer::getHistory() const {
    return streaming_history;
}

void Streamer::addToHistory(Stream *stream) {
    streaming_history.push_back(stream);
}

bool Streamer::stopStreaming() {
    if (!isActive()) return false;
    streaming_history.push_back(s);
    total_views += s->getNumViewers();
    s = nullptr;
    return true;
}

/**
 * Gets the streamer's number of active viewers
 *
 * @return the streamer's number of active viewers
 */
/*
unsigned Streamer::getActiveViewers() const {
   return active_viewers.size();
}
*/

/**
 * Prints the streamer's information
 *
 * @return a string with the viewer's information
 */
string Streamer::getInfo() {
    ostringstream info;
    info << User::getInfo();
    info << "Streaming: " << to_string(isActive()) << endl;
    if (isActive()) {
        info << "Stream: " << s->getInfo() << endl;
        // info << "Active viewers: " << to_string(getActiveViewers()) << endl;
    }
    return info.str();
}

/**
 * Constructs an admin object
 *
 * @param nickname the admin's nickname
 * @param birthday the admin's date of birth
 */
Admin::Admin(string nickname, Date birthday) : User(nickname, birthday) {}

Admin::~Admin() {
}
