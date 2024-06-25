#ifndef CRICKET_FUNCTIONS_HPP
#define CRICKET_FUNCTIONS_HPP

#include "CricketPlayer.hpp"
#include <string>
#include <vector>

// Function declarations

// Check and update the striker and non-striker batsmen based on the current players list
void checkBatsmen(vector<CricketPlayer> &players, string &striker, string &nonStriker);

// Check and update the current bowler based on the current players list
void checkBowler(vector<CricketPlayer> &players, string &bowler);

// Check if a given batsman is a valid player in the team
bool isValidBatsman(const string &newBatsman, const vector<CricketPlayer> &team);

// Add a new batsman to the team
void enterNewBatsman(vector<CricketPlayer> &team, string &batsman);

#endif /* CRICKET_FUNCTIONS_HPP */
