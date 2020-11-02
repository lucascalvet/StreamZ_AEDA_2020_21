#ifndef STREAMZ_H
#define STREAMZ_H

#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "utils.h"
#include "user.h"
#include "stream.h"

using namespace std;

class StreamZ {
private:
    static Age calculateAge(const Date& birthday);
public:
    StreamZ(unsigned capacity);
    ~StreamZ();
    unsigned capacity;   //how many streams can be active at same time
    vector<User*> users;
    vector<Stream*> active_streams;
    vector<Stream*> best_streams;
    //map<int, vector<Stream*>> history; ;  //history per id of streamer
    User* addUser(bool streamer, const string& nickname, const Date& birthday); // or addStreamer and addViewer?...
      //when stream is ended by streamer, stream is added to history after total viewers data is added to stream
      // for streamers
    bool startStream(Streamer &streamer, const string& title, const Language& lang, unsigned min_age);
    bool stopStream(const Streamer& streamer);
    //for viewers
    bool enterStream(Stream* s, Viewer *v);  //can only be in one stream at the time
    bool exitStream(Viewer *v);   //they can exit at any time (needs to check if the stream should be added to the top 10)
    bool likeStream(Stream * s, Viewer * v);
    bool dislikeStream(Stream * s, Viewer *v);
    bool isStreamActive(const Stream* s, vector<Stream*>::iterator &it);
    unsigned getActiveStreams() const;
    vector<Stream*> getStreams(const Language& lang, Age min_age) const;
    bool saveStreams(const string& filename) const;
};

#endif // STREAMZ_H
