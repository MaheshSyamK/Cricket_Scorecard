#include "cricket_functions.hpp"
#include <iostream>



void checkBatsmen(vector<CricketPlayer> &players, string &striker, string &nonStriker) {
    bool strikerVerified = false, nonStrikerVerified = false;

    for (int i = 0; i < players.size(); ++i) {
        if (players[i].getName() == striker && !players[i].getHasPlayed()) {
            strikerVerified = true;
            players[i].setHasPlayed(true);
            cout << "Striker's name verified. You can proceed now for bat.\n";
        }
        if (players[i].getName() == nonStriker && !players[i].getHasPlayed()) {
            nonStrikerVerified = true;
            players[i].setHasPlayed(true);
            cout << "Non-striker's name verified. You can proceed now for bat.\n";
        }
    }

    while (!strikerVerified) {
        cout << "Striker's name is invalid or has already played. Enter a new name: ";
        getline(cin, striker);
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].getName() == striker && !players[i].getHasPlayed()) {
                strikerVerified = true;
                players[i].setHasPlayed(true);
                cout << "Striker's name verified. You can proceed now for bat.\n";
                break;
            }
        }
    }

    while (!nonStrikerVerified) {
        cout << "Non-striker's name is invalid or has already played. Enter a new name: ";
        getline(cin, nonStriker);
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].getName() == nonStriker && !players[i].getHasPlayed()) {
                nonStrikerVerified = true;
                players[i].setHasPlayed(true);
                cout << "Non-striker's name verified. You can proceed now for bat.\n";
                break;
            }
        }
    }
}



void checkBowler(vector<CricketPlayer> &players, string &bowler) {
    bool bowlerVerified = false;

    while (!bowlerVerified) {
        for (int i = 0; i < players.size(); ++i) {
            if (players[i].getName() == bowler) {
                bowlerVerified = true;
                cout << "Bowler's name verified. You can proceed now for bowl.\n";
                break;
            }
        }

        if (!bowlerVerified) {
            cout << "Bowler's name is invalid. Enter a new name: ";
            getline(cin, bowler);
        }
    }
}



bool isValidBatsman(const string &newBatsman, const vector<CricketPlayer> &team) {
    for (const auto &player : team) {
        if (player.getName() == newBatsman && !player.getHasPlayed()) {
            return true;
        }
    }
    return false;
}



void enterNewBatsman(vector<CricketPlayer> &team, string &batsman) {
    while (true) {
        cout << "Enter the name of the new batsman: ";
        getline(cin, batsman);

        if (!isValidBatsman(batsman, team)) {
            cout << "The batsman does not belong to the same team or has already played. Please enter a valid batsman." << endl;
        } else {
            for (auto &player : team) {
                if (player.getName() == batsman) {
                    player.setHasPlayed(true);
                    break;
                }
            }
            break;
        }
    }
}
