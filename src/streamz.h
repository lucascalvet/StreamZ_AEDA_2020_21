#ifndef STREAMZ_H
#define STREAMZ_H

#include <vector>
#include <string>
#include <map>
#include "utils.h"
#include "user.h"
#include "stream.h"

/**
 * Main class for handling a StreamZ platform
 */
class StreamZ {
private:
    Admin *admin;
    static int counter;
    unsigned id;
    unsigned capacity;   //how many streamers can be active at same time
    std::vector<Streamer *> streamers;
    std::vector<Viewer *> viewers;
    ///A container with the 10 most viewed streams, followed by the 10 most liked streams, sorted in descending order
    std::vector<Stream *> best_streams = std::vector<Stream *>(20, nullptr);
public:
    StreamZ(unsigned capacity, const std::string &nickname, const Date &birthday, const std::string &password);
    explicit StreamZ(const std::string &filename);
    ~StreamZ();
    unsigned getCapacity() const;
    unsigned getID() const;
    User *getUserByName(const std::string &nickname);
    unsigned getNumViewers() const;
    unsigned getNumStreamViewers(Stream *stream) const;
    std::vector<Viewer *> getViewers() const;
    Viewer *getViewerByID(unsigned user_id) const;
    Viewer *getViewerByName(const std::string &nickname) const;
    unsigned getNumStreamers() const;
    unsigned getNumActiveStreamers() const;
    std::vector<Streamer *> getStreamers() const;
    Streamer *getStreamerByID(unsigned user_id) const;
    Streamer *getStreamerByName(const std::string &nickname) const;
    std::vector<Streamer *> getActiveStreamers() const;
    std::vector<Stream *> getBestStreams() const;
    Streamer *getMostViewedStreamer() const;
    unsigned getNumCreatedStreams() const;
    unsigned getNumCreatedStreams(const Language &lang) const;
    unsigned getNumCreatedStreams(bool public_streams, const Date &dt1 = Date(0, 0, 0),
                                  const Date &dt2 = Date(31, 12, UINT_MAX)) const;
    std::string getMostUsedLanguage();
    double getAverageViews() const;
    void addStreamer(const std::string &nickname, const Date &birthday, const std::string &password);
    void addViewer(const std::string &nickname, const Date &birthday, const std::string &password);
    //when stream is ended by streamer, stream is added to history after total viewers data is added to stream
    // for streamers
    void startPublicStream(Streamer *streamer, const std::string &title, const Language &lang, unsigned min_age) const;
    void startPrivateStream(Streamer *streamer, const std::string &title, const Language &lang, unsigned min_age,
                            const std::vector<unsigned> &authorized_viewers) const;
    void stopStream(Streamer *streamer);
    void printStreams(const std::vector<Streamer *> &streams) const;
    std::vector<Streamer *> getStreams(const Language &lang = "", Age min_age = UINT_MAX) const;
    void stopAllStreams();
    bool loginVerifier(std::string nickname, std::string password) const;
    void save(const std::string &filename) const;
};

#endif // STREAMZ_H
