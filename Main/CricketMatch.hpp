#ifndef CRICKETMATCH_HPP
#define CRICKETMATCH_HPP

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include "CricketTeam.hpp"
#include "Details.hpp"
#include "globals.hpp"

using namespace std;

class CricketMatch {
   private:
    string venue;
    CricketTeam team1, team2;
    int totalOvers;
    string tossWinner;
    int choice;
    int team1Choice;
    int team2Choice;

    // Function to get the current date and time
    void date();

   public:
    // Constructor to initialize the match with team names
    CricketMatch(const string& team1Name, const string& team2Name);

    // Function for returning the time and date
    string getCurrentDateTime() const;

    // Function for getting Team1 players
    void setTeam1PlayerNames();

    // Function for getting the Team2 players
    void setTeam2PlayerNames();

    // Getters for team1 objects
    CricketTeam& getTeam1();

    // Getters for team2 objects
    CricketTeam& getTeam2();

    // Function for returning total overs
    int getTotalOvers() const;

    // Function for getting toss winner
    string getTossWinner() const;

    // Function for getting team2Choice
    int getTeam2Choice() const;

    // Function for getting team1Choice
    int getTeam1Choice() const;

    // Functions to set player names for the teams
    void setPlayerNames(CricketTeam& team);

    // Function to set the details of the match
    void setDetails();

    /**
     * Writes the scoreboard details to a file.
     *
     * @param outFile The ofstream object for the file to write to.
     * @param overs A vector of strings representing the overs details.
     */
    void writeScoreboardToFiles(ofstream& outFile, const vector<string>& overs) const;

    /**
     * Writes a bar graph comparing two values to a file.
     *
     * @param outFile The ofstream object for the file to write to.
     * @param value1 The first value to compare.
     * @param value2 The second value to compare.
     * @param maxValue The maximum value to use for scaling the bar graph.
     * @param category The category name for the comparison.
     */
    void writeBarGraphToFiles(ofstream& outFile, int value1, int value2, int maxValue, const string& category) const;

    /**
     * Draws a bar representing a value to a file.
     *
     * @param outFile The ofstream object for the file to write to.
     * @param value The value to represent with the bar.
     * @param maxValue The maximum value to use for scaling the bar.
     * @param barChar The character to use for drawing the bar (default is '*').
     */
    void drawBarToFiles(ofstream& outFile, int value, int maxValue, char barChar = '*') const;

    /**
     * Displays the match results to a file.
     *
     * @param inning1runs The total runs scored by team 1.
     * @param inning2runs The total runs scored by team 2.
     * @param team1Name The name of team 1.
     * @param team2Name The name of team 2.
     * @param outFile The ofstream object for the file to write to.
     */
    void displayMatchResults(int inning1runs, int inning2runs, const string& team1Name, const string& team2Name, ofstream& outFile) const;

    /**
     * Saves match details to an HTML file.
     *
     * @param filename The name of the HTML file to save to.
     */
    void saveMatchDetails(const string& filename);

    /**
     * Saves JavaScript code for the match to a file.
     *
     * @param filename The name of the JavaScript file to save to.
     */
    void saveJavaScript(const string& filename);

    /**
     * Display the match results in HTML format.
     *
     * @param inning1runs Total runs scored in the first inning.
     * @param inning2runs Total runs scored in the second inning.
     * @param team1Name Name of the first team.
     * @param team2Name Name of the second team.
     * @param outFile Output file stream to write the results to.
     */
    void displayMatchResults1(int inning1runs, int inning2runs, const string& team1Name, const string& team2Name, ofstream& outFile) const;

    /**
     * Save match details to a file.
     *
     * @param filename The name of the file to save the match details to.
     */

    /**
     * Saves match details to a file.
     *
     * @param filename The name of the file to save the match details to.
     * @param team1Name The name of team 1.
     * @param team1Players The vector of player names for team 1.
     * @param team2Name The name of team 2.
     * @param team2Players The vector of player names for team 2.
     */
    void saveMatchDetail(const string& filename, const string& team1Name, const string& team2Name);
};

#endif  // CRICKETMATCH_HPP
