    // Assuming you have a CricketMatch class
#include "CricketMatch.hpp"  
#include "Details.hpp"
#include "display_functions.hpp"

#include <iostream>



void displayScoreboard(vector<string>& overs, details& innings) {
    int j = 0, k = 0;

    for (size_t i = 0; i < overs.size(); i++) {
        if (i == 6 * k) {
            cout << "\nScore Details of Over " << k + 1 << ": " << endl;
            k++;
        }

        j = ((i) % 6);
        cout << "Ball " << j + 1 << ": ";

        for (char ballType : overs[i]) {
            cout << ballType << " ";
        }

        cout << endl;
    }

    cout << "\n\nTotal Score in Innings --> [ " << innings.runs << " - " << innings.wicket << " ]\n\n" << endl;
    cout << "Total Runs: " << innings.runs << endl;
    cout << "Total Wickets: " << innings.wicket << endl;
    cout << "Total Fours: " << innings.fours << endl;
    cout << "Total Sixes: " << innings.sixes << endl;
    cout << "Total Dot Balls: " << innings.dot << endl;
    cout << "Total Extras: " << innings.extraruns << endl;
    cout << "Total Wides: " << innings.wide << endl;
    cout << "Total NoBalls: " << innings.NB << endl;
    cout << "Total Byes: " << innings.byes << endl;
}



void displayMatchResult(const CricketMatch& match, const string& team1Name, const string& team2Name, int inning1runs, int inning2runs) {
    string winningTeam;

    if ((inning1runs > inning2runs && match.getTeam1Choice() == 1) || (inning2runs > inning1runs && match.getTeam2Choice() == 1)) {
        winningTeam = team1Name;
    } else if ((inning1runs > inning2runs && match.getTeam2Choice() == 1) || (inning2runs > inning1runs && match.getTeam1Choice() == 1)) {
        winningTeam = team2Name;
    } else {
        cout << "\n\n\n\n\n\n\n\n\n       The match between " << team1Name << " and " << team2Name << " ended in a tie.\n\n\n\n\n\n\n\n\n\n\n\n"
             << endl;
        return;
    }

    if (winningTeam == team1Name) {
        cout << "\n\n\n\n\n\n\n\n\n\n      The Team " << team1Name << " emerged victorious, defeating the Team " << team2Name << " by a margin of "
             << abs(inning1runs - inning2runs) << " runs.\n\n\n\n\n\n\n\n\n\n\n\n"
             << endl;
    } else {
        cout << "\n\n\n\n\n\n\n\n\n\n      The Team " << team2Name << " emerged victorious, defeating the Team " << team1Name << " by a margin of "
             << abs(inning2runs - inning1runs) << " runs.\n\n\n\n\n\n\n\n\n\n\n\n"
             << endl;
    }
}
