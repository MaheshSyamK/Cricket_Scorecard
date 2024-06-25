
#ifndef DISPLAY_FUNCTIONS_HPP
#define DISPLAY_FUNCTIONS_HPP

#include <string>
#include <vector>

using namespace std;

#include "CricketMatch.hpp"
#include "Details.hpp"

void displayScoreboard(vector<string>& overs, details& innings);
void displayMatchResult(const CricketMatch& match, const string& team1Name, const string& team2Name, int inning1runs, int inning2runs);

#endif  // DISPLAY_FUNCTIONS_HPP
