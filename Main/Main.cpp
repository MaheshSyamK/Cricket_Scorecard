

// COMMANDS FOR RUNNING IN TERMINAL  //

// g++ -c globals.cpp -o globals.o
// g++ -c score_value.cpp -o score_value.o
// g++ -c cricket_functions.cpp -o cricket_functions.o
// g++ -c Details.cpp -o Details.o
// g++ -c CricketPlayer.cpp -o CricketPlayer.o
// g++ -c CricketTeam.cpp -o CricketTeam.o
// g++ -c Ball.cpp -o Ball.o
// g++ -c NormalBall.cpp -o NormalBall.o
// g++ -c WideBall.cpp -o WideBall.o
// g++ -c NoBall.cpp -o NoBall.o
// g++ -c ByeBall.cpp -o ByeBall.o
// g++ -c DotBall.cpp -o DotBall.o
// g++ -c FourBall.cpp -o FourBall.o
// g++ -c SixBall.cpp -o SixBall.o
// g++ -c WicketBall.cpp -o WicketBall.o
// g++ -c CricketMatch.cpp -o CricketMatch.o
// g++ -c display_functions.cpp -o display_functions.o

// g++ -c Main.cpp -o Main.o

// g++ globals.o score_value.o cricket_functions.o Details.o CricketPlayer.o CricketTeam.o Ball.o NormalBall.o WideBall.o NoBall.o ByeBall.o DotBall.o
// FourBall.o SixBall.o WicketBall.o CricketMatch.o display_functions.o Main.o -o cricket_main

// ./cricket_main




// The ctime library is included to handle current date and time operations.
#include <ctime>

// The fstream library is included for file operations, specifically for creating and writing to HTML and CSS files.
#include <fstream>

// The iomanip library is included for input/output formatting, aiding in the precise presentation of data.
#include <iomanip>

// The iostream library is included for standard input and output operations.
#include <iostream>

// The limits library is included to manage input limits and validation.
#include <limits>

// The string library is included for string manipulation operations.
#include <string>

// The vector library is included for managing dynamic arrays, useful for storing lists like player names or teams.
#include <vector>





// Include statements with purpose and usage information

// Included to access global variables.
#include "globals.hpp"

// Included for scoring related inputs information.
#include "score_value.hpp"

// Included for general cricket-related functions, such as verifying player names.
#include "cricket_functions.hpp"

// Included for details of cricket match, including innings output details.
#include "Details.hpp"

// Included for the CricketPlayer class, which represents player details.
#include "CricketPlayer.hpp"

// Included for the CricketTeam class, which represents a team in a cricket match.
#include "CricketTeam.hpp"

// Included for the Ball class, which represents details of each ball bowled.
#include "Ball.hpp"

// Included for specialized ball types like NormalBall, WideBall, etc.
#include "ByeBall.hpp"
#include "DotBall.hpp"
#include "FourBall.hpp"
#include "NoBall.hpp"
#include "NormalBall.hpp"
#include "SixBall.hpp"
#include "WicketBall.hpp"
#include "WideBall.hpp"

// Included for the CricketMatch class, which handles match logic and operations.
#include "CricketMatch.hpp"

// Included for display-related functions in the terminal.
#include "display_functions.hpp"

using namespace std;





// Function to clear the input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// Function to delaying the terminal
void delay(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}




int main() {
    
    // Clear the console screen
    system("cls");

    // Total number of overs in the match
    int totalovers;

    // Names of Team 1 and Team 2
    // Names of the bowler, striker, and non-striker
    string team1Name, team2Name;
    string Bow, Striker, Nonstriker;

    // Input team names
    cout << "Enter Team 1 name: ";
    getline(cin, team1Name);
    cout << "Enter Team 2 name: ";
    getline(cin, team2Name);

    // Clear the console screen
    system("cls");

    // Create a CricketMatch object with the team names
    // Set match details
    // Set player names for Team 1
    // Set player names for Team 2
    CricketMatch match(team1Name, team2Name);
    match.setDetails();

    // Clear the console screen
    system("cls");

    match.setTeam1PlayerNames();
    match.setTeam2PlayerNames();

    // Get total overs in the match
    // Get the toss winner
    totalovers = match.getTotalOvers();
    string tossWinner = match.getTossWinner();

    // it clears the screen
    // it calls the function score_value
    // delay is a function which delays the screen time
    // it clears the screen
    system("cls");
    score_value();
    delay(8000);
    system("cls");

    // Iterate for each inning
    for (int inning = 1; inning <= 2; inning++) {
        // Determine the batting and bowling teams for the current inning
        cout << "Inning " << inning << endl;
        cout << "Team 1 --> " << match.getTeam1().getName() << " is ";

        // Condition for checking, eiter team 1 is getting batting or bowling
        if (((inning == 1 && ((tossWinner == match.getTeam1().getName() && match.getTeam1Choice() == 1) ||
                              (tossWinner == match.getTeam2().getName() && match.getTeam2Choice() == 2))) ||
             (inning == 2 && ((tossWinner == match.getTeam1().getName() && match.getTeam1Choice() == 2) ||
                              (tossWinner == match.getTeam2().getName() && match.getTeam2Choice() == 1))))) {
            cout << "batting" << endl;
        } else {
            cout << "bowling" << endl;
        }

        // Condition for checking either team 2 is getting bowling or batting
        cout << "Team 2 --> " << match.getTeam2().getName() << " is ";
        if (((inning == 1 && ((tossWinner == match.getTeam1().getName() && match.getTeam1Choice() == 1) ||
                              (tossWinner == match.getTeam2().getName() && match.getTeam2Choice() == 2))) ||
             (inning == 2 && ((tossWinner == match.getTeam1().getName() && match.getTeam1Choice() == 2) ||
                              (tossWinner == match.getTeam2().getName() && match.getTeam2Choice() == 1))))) {
            cout << "bowling" << endl;
        } else {
            cout << "batting" << endl;
        }

        // Get the batting team players for the current inning
        vector<CricketPlayer> &battingTeamPlayers = ((inning == 1 && ((tossWinner == match.getTeam1().getName() && match.getTeam1Choice() == 1) ||
                                                                      (tossWinner == match.getTeam2().getName() && match.getTeam2Choice() == 2))) ||
                                                     (inning == 2 && ((tossWinner == match.getTeam1().getName() && match.getTeam1Choice() == 2) ||
                                                                      (tossWinner == match.getTeam2().getName() && match.getTeam2Choice() == 1))))
                                                        ? match.getTeam1().getPlayers()
                                                        : match.getTeam2().getPlayers();

        // Getting the bowling team players for the current innings
        vector<CricketPlayer> &bowlingTeamPlayers = ((inning == 1 && ((tossWinner == match.getTeam1().getName() && match.getTeam1Choice() == 1) ||
                                                                      (tossWinner == match.getTeam2().getName() && match.getTeam2Choice() == 2))) ||
                                                     (inning == 2 && ((tossWinner == match.getTeam1().getName() && match.getTeam1Choice() == 2) ||
                                                                      (tossWinner == match.getTeam2().getName() && match.getTeam2Choice() == 1))))
                                                        ? match.getTeam2().getPlayers()
                                                        : match.getTeam1().getPlayers();

        // Input striker names and verify them
        cout << "Enter striker's name: ";
        clearInputBuffer();
        getline(cin, Striker);

        // Input non striker names and verify them
        cout << "Enter non-striker's name: ";
        getline(cin, Nonstriker);
        checkBatsmen(battingTeamPlayers, Striker, Nonstriker);

        for (int j = 1; j <= totalovers; j++) {
            // Input bowler's name and verify it
            clearInputBuffer();
            cout << "Enter bowlers name: ";
            getline(cin, Bow);
            checkBowler(bowlingTeamPlayers, Bow);

            // Giving the score input for overs
            cout << "Give the score input for the over " << j << endl;
            int sumbscore = 0;

            // Input the score for each ball in the over
            for (int i = ((6) * (j - 1)); i < ((6) * (j)); i++) {
                // initialised the ball type and input for it
                string ballType;
                cin >> ballType;

                // intialised currentBall to null for class Ball
                Ball *currentBall = nullptr;

                // Handle different types of balls based on user
                // It is for innings 1
                if (inning == 1) {
                    // Create a new ball object based on the
                    // ball type
                    // When it is a Normal Ball, we have to enter 1/2/3/..
                    if (ballType == "N") {
                        currentBall = new NormalBall();
                        int runs;
                        cout << "Enter the number of runs: ";
                        cin >> runs;
                        currentBall->handleBall(runs, playeri1);
                    }

                    // When it is a wide ball, we have to enter w
                    else if (ballType == "w") {
                        // Handle wide ball separately
                        // Decrement i to account for the
                        // extra delivery
                        currentBall = new WideBall();
                        int runs;
                        cout << "Enter the number of runs "
                                "off the wide ball: ";
                        cin >> runs;
                        currentBall->handleBall(runs, playeri1);
                        --i;
                        continue;
                    }

                    // When it is a No Ball, we have to enter Nb
                    else if (ballType == "Nb") {
                        // Handle no ball separately
                        // Decrement i to a
                        currentBall = new NoBall();
                        int runs;
                        cout << "Enter the number of runs "
                                "off the no ball: ";
                        cin >> runs;
                        currentBall->handleBall(runs, playeri1);
                        --i;
                        continue;
                    }

                    // When it is a byes, we have to enter the B
                    else if (ballType == "B") {
                        currentBall = new ByeBall();
                        currentBall->handleBall(0, playeri1);
                    }

                    // When it is a dot ball, we have to enter .
                    else if (ballType == ".") {
                        currentBall = new DotBall();
                        currentBall->handleBall(0, playeri1);
                    }

                    // When it is a four, we have to enter 4
                    else if (ballType == "4") {
                        currentBall = new FourBall();
                        currentBall->handleBall(0, playeri1);
                    }

                    // When it is a six, we have to enter 6
                    else if (ballType == "6") {
                        currentBall = new SixBall();
                        currentBall->handleBall(0, playeri1);
                    }

                    // When it is Wicket, we have to enter W
                    // and it gets verified which type of out it was.
                    else if (ballType == "W") {
                        // Handle wicket ball separately
                        // Enter a new batsman
                        currentBall = new WicketBall();
                        currentBall->handleBall(0, playeri1);
                        enterNewBatsman(battingTeamPlayers, Striker);
                        cout << "New batsman: " << Striker << endl;
                    }

                    // If the ball type doesnot belongs to any of these it results this
                    else {
                        cout << "Invalid ball type!" << endl;
                        --i; // Decrement i to account for
                             // the invalid input
                        continue;
                    }

                    // Delete the current ball object
                    // Store the over score
                    // Store the score for the over
                    // Reset bscore for the next
                    delete currentBall;
                    playeri1.oscore += playeri1.bscore + " ";
                    overs1.push_back(playeri1.bscore);
                    playeri1.bscore = "";
                }

                // It is for innings 2 input
                else {
                    // If the ball type is Normal ball enter N
                    // Handle balls for the second inning
                    if (ballType == "N") {
                        currentBall = new NormalBall();
                        int runs;
                        cout << "Enter the number of runs: ";
                        cin >> runs;
                        currentBall->handleBall(runs, playeri2);
                    }

                    // If the ball type is wide ball enter w
                    else if (ballType == "w") {
                        currentBall = new WideBall();
                        int runs;
                        cout << "Enter the number of runs "
                                "off the wide ball: ";
                        cin >> runs;
                        currentBall->handleBall(runs, playeri2);
                        // Decrement i to account for the
                        // extra delivery
                        --i;
                        continue;
                    }

                    // If the ball type is No ball enter No
                    else if (ballType == "Nb") {
                        currentBall = new NoBall();
                        int runs;
                        cout << "Enter the number of runs "
                                "off the no ball: ";
                        cin >> runs;
                        currentBall->handleBall(runs, playeri2);
                        // Decrement i to a
                        --i;
                        continue;
                    }

                    // If the ball type is Byyes ball enter B
                    else if (ballType == "B") {
                        currentBall = new ByeBall();
                        currentBall->handleBall(0, playeri2);
                    }

                    // If the ball type is Dot ball enter .
                    else if (ballType == ".") {
                        currentBall = new DotBall();
                        currentBall->handleBall(0, playeri2);
                    }

                    // If the ball type is four enter 4
                    else if (ballType == "4") {
                        currentBall = new FourBall();
                        currentBall->handleBall(0, playeri2);
                    }

                    // If the ball type is six enter 6
                    else if (ballType == "6") {
                        currentBall = new SixBall();
                        currentBall->handleBall(0, playeri2);
                    }

                    // If the ball type is Wicket ball enter W
                    else if (ballType == "W") {
                        currentBall = new WicketBall();
                        currentBall->handleBall(0, playeri2);
                        enterNewBatsman(battingTeamPlayers, Striker);
                        cout << "New batsman: " << Striker << endl;
                    }

                    // If the ball type is invalid ball then it occurs
                    else {
                        // Decrement i to account for the
                        // invalid input
                        cout << "Invalid ball type!" << endl;
                        --i;
                        continue;
                    }

                    // Store the over score
                    // Store the score for the over
                    // Reset bscore for the next
                    delete currentBall;
                    playeri2.oscore += playeri2.bscore + " ";
                    overs2.push_back(playeri2.bscore);
                    playeri2.bscore = "";
                }
            }
        }
        // Clear the console screen
        system("cls");
    }

    // Clear the console screen
    system("cls");

    // calling the function for score details of @ 1st innings
    if (match.getTeam1Choice() == 1) {
        cout << "Innings 1 Score card : \n" << endl;
        cout << "Batting  @  " << team1Name << " !!\n\n" << endl;
    } else {
        cout << "Innings 1 Score card : \n" << endl;
        cout << "Batting  @  " << team2Name << " !!\n\n" << endl;
    }

    displayScoreboard(overs1, playeri1);
    delay(8000);

    // Clear the console screen
    system("cls");

    // calling the function for score details of @ 2nd Innings
    if (match.getTeam1Choice() == 1) {
        cout << "Innings 2 Score card : \n" << endl;
        cout << "Batting  @  " << team2Name << " !!\n\n" << endl;
    } else {
        cout << "Innings 2 Score card : \n" << endl;
        cout << "Batting  @  " << team1Name << " !!\n\n" << endl;
    }

    displayScoreboard(overs2, playeri2);
    delay(8000);

    // Clear the console screen
    system("cls");

    // Calling of function to display in a text in File
    match.saveMatchDetail("match_details.txt", team1Name, team2Name);

    // Calling the function to give content to html
    match.saveMatchDetails("../Front_End/index.html");

    // Calling the function to give content to js
    match.saveJavaScript("../Front_End/script.js");

    // Calling the function for declaring who won the match
    displayMatchResult(match, team1Name, team2Name, playeri1.runs, playeri2.runs);

    return 0;
}
