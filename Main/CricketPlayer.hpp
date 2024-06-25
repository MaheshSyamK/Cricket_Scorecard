#ifndef CRICKETPLAYER_HPP
#define CRICKETPLAYER_HPP

#include <string>
using namespace std;

class CricketPlayer {
   private:
    string name;

   public:
    bool hasPlayed;
    CricketPlayer(const string& n);
    string getName() const;
    bool getHasPlayed() const;
    void setHasPlayed(bool played);
};

#endif  // CRICKETPLAYER_HPP
