#ifndef CRICKETTEAM_HPP
#define CRICKETTEAM_HPP

#include <iostream>
#include <string>
#include <vector>
#include "CricketPlayer.hpp"

using namespace std;

class CricketTeam {
   private:
    string name;
    vector<CricketPlayer> players;
    int choice;

    friend class CricketMatch;

   public:
    CricketTeam(const string& name);
    void addPlayer(const string& playerName);
    const string& getName() const;
    vector<CricketPlayer>& getPlayers();
    void showDetails() const;
    void setPlayerNames();
    int getChoice() const;
};

#endif  // CRICKETTEAM_HPP
