#include <iomanip>

#include "CricketMatch.hpp"
#include "CricketTeam.hpp"
#include "Details.hpp"
#include "globals.hpp"



// Constructor to initialize the match with team names
CricketMatch::CricketMatch(const string &team1Name, const string &team2Name)
    : team1(team1Name), team2(team2Name), totalOvers(0), tossWinner(""), choice(0) {}


// Function to get the current date and time
void CricketMatch::date() {
    time_t currentTime;
    time(&currentTime);
    cout << ctime(&currentTime);
}


// Function for returning the time and date
string CricketMatch::getCurrentDateTime() const {
    time_t currentTime;
    time(&currentTime);
    return string(ctime(&currentTime));
}


// Function for getting Team1 players
void CricketMatch::setTeam1PlayerNames() {
    team1.setPlayerNames();
}


// Function for getting the Team2 players
void CricketMatch::setTeam2PlayerNames() {
    team2.setPlayerNames();
}


// Getters for team1 objects
CricketTeam& CricketMatch::getTeam1() {
    return team1;
}


// Getters for team2 objects
CricketTeam& CricketMatch::getTeam2() {
    return team2;
}


// Function for returning total overs
int CricketMatch::getTotalOvers() const {
    return totalOvers;
}


// Function for getting toss winner
string CricketMatch::getTossWinner() const {
    return tossWinner;
}


// Function for getting team2Choice
int CricketMatch::getTeam2Choice() const {
    return team2Choice;
}


// Function for getting team1Choice
int CricketMatch::getTeam1Choice() const {
    return team1Choice;
}


// Functions to set player names for the teams
void CricketMatch::setPlayerNames(CricketTeam& team) {
    team.setPlayerNames();
}



// Function to set the details of the match
void CricketMatch::setDetails() {
    cout << "Enter the details of the match\n";
    cout << "Team 1: " << team1.getName() << "\n";
    cout << "Team 2: " << team2.getName() << "\n";

    // Ignore the newline character in the input buffer
    cout << "Venue: ";
    cin.ignore();
    getline(cin, venue);

    // Function date() to be defined separately
    cout << "Time and Date of the match   ::   ";
    date();

    // Handle incorrect input for number of overs
    while (true) {
        cout << "Number of overs: ";
        if (cin >> totalOvers) {
            // Exit the loop if input is valid
            break;
        } else {
            // Discard invalid input
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Handle incorrect input for toss winner
    while (true) {
        cout << "Toss won by which team\n";
        cout << team1.getName() << " or " << team2.getName() << ": ";
        cin >> tossWinner;

        if (tossWinner == team1.getName() || tossWinner == team2.getName()) {
            // Exit the loop if input is valid
            break;
        } else {
            cout << "You entered a wrong team name. Please enter the correct team name.\n";
        }
    }

    // Handle incorrect input for batting or bowling choice
    while (true) {
        cout << "Press 1 for bat or 2 for bowl: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            // Exit the loop if input is valid
            break;
        } else {
            cout << "Invalid input. Please enter 1 for bat or 2 for bowl.\n";
        }
    }

    // Determine the choice for the teams based on the toss result
    if (tossWinner == team1.getName()) {
        // Alternate choice for Team 2
        team1Choice = choice;
        team2Choice = (choice == 1) ? 2 : 1;
    } else {
        // Alternate choice for Team 1
        team2Choice = choice;
        team1Choice = (choice == 1) ? 2 : 1;
    }

    cout << "Team " << tossWinner << " chooses to ";
    if (choice == 1) {
        cout << "bat first\n";
    } else {
        cout << "bowl first\n";
    }
}



void CricketMatch::saveMatchDetail(const string &filename, const string &team1Name, const string &team2Name) {
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << "\n\n\nTeam 1: " << team1Name << "\n";
        outFile << "Players:\n";
        for (const auto &player : team1.getPlayers()) {
            outFile << player.getName() << "\n";
        }
        outFile << "\n";

        outFile << "Team 2: " << team2Name << "\n";
        outFile << "Players:\n";
        for (const auto &player : team2.getPlayers()) {
            outFile << player.getName() << "\n";
        }
        outFile << "\n";

        outFile << "Venue           :" << venue << "\n";
        outFile << "Time and Date   :" << getCurrentDateTime() << "\n";
        outFile << "Number of Overs :" << totalOvers << "\n";
        outFile << "Toss won by     :" << tossWinner << "\n";
        outFile << "Chosen          :" << (choice == 1 ? "Bat" : "Bowl") << "\n";

        outFile << "\n\n";

        string innings1Team, innings2Team;
        if (team1Choice == 1) {
            innings1Team = team1Name;
            innings2Team = team2Name;
        } else {
            innings1Team = team2Name;
            innings2Team = team1Name;
        }

        outFile << "\nInnings 1 Score card Ball by Ball in each Over:\n";
        outFile << "Batting @ " << innings1Team << "!\n";
        writeScoreboardToFiles(outFile, overs1);

        outFile << "\n\n";

        outFile << "\nInnings 2 Score card Ball by Ball in each Over:\n";
        outFile << "Batting @ " << innings2Team << "!\n";
        writeScoreboardToFiles(outFile, overs2);

        outFile << setw(20) << "\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tScoreboard\n\n";
        outFile << setw(20) << "\tCategory" << setw(20) << innings1Team << setw(20) << innings2Team << "\n\n";
        outFile << setw(20) << "Total Runs" << setw(20) << playeri1.runs << setw(20) << playeri2.runs << "\n";
        outFile << setw(20) << "Total Wickets" << setw(20) << playeri1.wicket << setw(20) << playeri2.wicket << "\n";
        outFile << setw(20) << "Total Fours" << setw(20) << playeri1.fours << setw(20) << playeri2.fours << "\n";
        outFile << setw(20) << "Total Sixes" << setw(20) << playeri1.sixes << setw(20) << playeri2.sixes << "\n";
        outFile << setw(20) << "Total Dot Balls" << setw(20) << playeri1.dot << setw(20) << playeri2.dot << "\n";
        outFile << setw(20) << "Total Extras" << setw(20) << playeri1.extraruns << setw(20) << playeri2.extraruns << "\n";
        outFile << setw(20) << "Total Wides" << setw(20) << playeri1.wide << setw(20) << playeri2.wide << "\n";
        outFile << setw(20) << "Total NoBalls" << setw(20) << playeri1.NB << setw(20) << playeri2.NB << "\n";
        outFile << setw(20) << "Total Byes" << setw(20) << playeri1.byes << setw(20) << playeri2.byes << "\n";

        int maxRuns = max(playeri1.runs, playeri2.runs);
        int maxWickets = max(playeri1.wicket, playeri2.wicket);
        int maxFours = max(playeri1.fours, playeri2.fours);
        int maxSixes = max(playeri1.sixes, playeri2.sixes);
        int maxDots = max(playeri1.dot, playeri2.dot);
        int maxExtras = max(playeri1.extraruns, playeri2.extraruns);
        int maxWides = max(playeri1.wide, playeri2.wide);
        int maxNoBalls = max(playeri1.NB, playeri2.NB);
        int maxByes = max(playeri1.byes, playeri2.byes);

        outFile << "\n\n\n\n\t\t\t\t\t\t\t\t\tBar Graph Data : [ " << innings1Team << " | " << innings2Team << " ]\n\n";
        outFile << setw(20) << "Category \n\n";
        writeBarGraphToFiles(outFile, playeri1.runs, playeri2.runs, maxRuns, "Total Runs");
        writeBarGraphToFiles(outFile, playeri1.wicket, playeri2.wicket, maxWickets, "Total Wickets");
        writeBarGraphToFiles(outFile, playeri1.fours, playeri2.fours, maxFours, "Total Fours");
        writeBarGraphToFiles(outFile, playeri1.sixes, playeri2.sixes, maxSixes, "Total Sixes");
        writeBarGraphToFiles(outFile, playeri1.dot, playeri2.dot, maxDots, "Total Dot Balls");
        writeBarGraphToFiles(outFile, playeri1.extraruns, playeri2.extraruns, maxExtras, "Total Extras");
        writeBarGraphToFiles(outFile, playeri1.wide, playeri2.wide, maxWides, "Total Wides");
        writeBarGraphToFiles(outFile, playeri1.NB, playeri2.NB, maxNoBalls, "Total No Balls");
        writeBarGraphToFiles(outFile, playeri1.byes, playeri2.byes, maxByes, "Total Byes");

        displayMatchResults(playeri1.runs, playeri2.runs, team1Name, team2Name, outFile);

        outFile.close();

        cout << "Match details successfully saved to " << filename << endl;
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}



    // Function to write scoreboard to file
void CricketMatch::writeScoreboardToFiles(ofstream &outFile, const vector<string> &overs) const {
    // Variables to keep track of over and ball counts
    int j = 0, k = 0;

    // Iterate over each ball in the overs vector
    for (size_t i = 0; i < overs.size(); i++) {
        // Check if a new over is starting
        if (i == 6 * k) {
            outFile << "\nScore Details of Over " << k + 1 << ":\n";
            // Increment the over count
            k++;
        }

        // Calculate the ball count for the current over
        j = ((i) % 6);
        outFile << "Ball " << j + 1 << ": ";

        // Print the type of delivery for each ball in the current over
        for (char ballType : overs[i]) {
            // Add a space after 'Nb' to ensure proper formatting
            if (ballType == 'N' && overs[i].size() == 2) {
                outFile << ballType << " ";
            } else {
                outFile << ballType;
            }
        }

        // Move to the next line for the next ball
        outFile << "\n";
    }
}



void CricketMatch::writeBarGraphToFiles(ofstream &outFile, int value1, int value2, int maxValue, const string &category) const {
    // As it was a double bar graph using @ && $ we represent
    const char team1Char = '@';
    const char team2Char = '$';

    // Print the category name
    outFile << setw(20) << category;

    // Print the bar graph for Team A
    outFile << setw(20) << value1 << " | ";
    drawBarToFiles(outFile, value1, maxValue, team1Char);

    outFile << "\n";

    // Print the bar graph for Team B
    outFile << setw(40) << value2 << " | ";
    drawBarToFiles(outFile, value2, maxValue, team2Char);

    // Add a new line for the next category
    outFile << "\n\n";
}

// Function for getting scaled value
void CricketMatch::drawBarToFiles(ofstream &outFile, int value, int maxValue, char barChar) const {
    // Calculate the width of the bar based on the maximum value
    const int maxWidth = 40; // Maximum width of the bar
    int width = (int)(((double)value / maxValue) * maxWidth);

    // Draw the bar
    for (int i = 0; i < width; ++i) {
        outFile << barChar;
    }
}



    // Function for displaying the match final result
void CricketMatch::displayMatchResults(int inning1runs, int inning2runs, const string &team1Name, const string &team2Name, ofstream &outFile) const {
    // String for winning Team
    string winningTeam;

    // Determine the winning team based on the total runs scored in their
    // respective innings and their choice to bat first
    if ((inning1runs > inning2runs && team1Choice == 1) || (inning2runs > inning1runs && team2Choice == 1)) {
        winningTeam = team1Name;
    } else if ((inning1runs > inning2runs && team2Choice == 1) || (inning2runs > inning1runs && team1Choice == 1)) {
        winningTeam = team2Name;
    } else {
        // If both teams scored the same runs, the match ends in a tie
        outFile << "\n\n\n\n\n\n       The match between " << team1Name << " and " << team2Name << " ended in a tie.\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        return;
    }

    // Display the result based on the winning team
    if (winningTeam == team1Name) {
        outFile << "\n\n\n\n\n\n\n       Team " << team1Name << " emerged victorious, defeating Team " << team2Name << " by a margin of "
                << abs(inning1runs - inning2runs) << " runs.\n\n"
                << endl;
    } else {
        outFile << "\n\n\n\n\n\n\n       Team " << team2Name << " emerged victorious, defeating Team " << team1Name << " by a margin of "
                << abs(inning2runs - inning1runs) << " runs.\n\n"
                << endl;
    }

    // Write the winning team to the file
    outFile << "\t\t\t\t\t\t\t\t\t\t\t\t\tWinning Team: " << winningTeam << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}



    // Function for generating HTML file
void CricketMatch ::saveMatchDetails(const string &filename) {
    // passing of file name
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << "<!DOCTYPE html>\n";
        outFile << "<html lang=\"en\">\n";
        outFile << "<head>\n";
        outFile << "    <meta charset=\"UTF-8\">\n";
        outFile << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
        outFile << "    <title>Live Cricket Scorecard</title>\n";
        outFile << "    <link rel=\"stylesheet\" href=\"styles.css\">\n";
        outFile << "    <style>\n";
        outFile << "        .bar { height: 20px; background-color: blue; margin: 2px 0; }\n";
        outFile << "        .bar-container { display: flex; align-items: center; }\n";
        outFile << "        .bar-label { width: 100px; }\n";
        outFile << "    </style>\n";
        outFile << "</head>\n";
        outFile << "<body>\n";
        outFile << "<header>\n";
        outFile << "    <h1 class=\"main-title\">Live Scorecard<br><span class=\"team-names\">" << team1.getName() << " vs " << team2.getName()
                << "</span></h1>\n";
        outFile << "    <h3 class=\"date-time\">" << getCurrentDateTime() << "</h3>\n";
        outFile << "</header>\n";
        outFile << "<div class=\"header-info\">\n";
        outFile << "    <div class=\"venue-overs\">\n";
        outFile << "        <p><strong>Venue:</strong> " << venue << "</p>\n";
        outFile << "        <p><strong>Total Overs:</strong> " << totalOvers << "</p>\n";
        outFile << "    </div>\n";
        outFile << "    <div class=\"toss-info\">\n";
        outFile << "        <p><strong>Toss Won By:</strong> " << tossWinner << "</p>\n";
        outFile << "        <p><strong>Choice:</strong> " << (choice == 1 ? "Bat" : "Bowl") << "</p>\n";
        outFile << "    </div>\n";
        outFile << "</div>\n";

        // Strings which gets the name of teams in innings
        string innings1Team, innings2Team;
        if (getTeam1Choice() == 1) {
            innings1Team = team1.getName();
            innings2Team = team2.getName();
        } else {
            innings1Team = team2.getName();
            innings2Team = team1.getName();
        }

        outFile << "    <div class=\"container\">\n";
        outFile << "        <section class=\"teams\">\n";
        outFile << "            <div class=\"team\">\n";
        outFile << "                <h2>Team 1: " << team1.getName() << "</h2>\n";
        outFile << "                <ul>\n";
        for (auto &player : team1.getPlayers()) {
            outFile << "                    <li>" << player.getName() << "</li>\n";
        }
        outFile << "                </ul>\n";
        outFile << "            </div>\n";
        outFile << "            <div class=\"team\">\n";
        outFile << "                <h2>Team 2: " << team2.getName() << "</h2>\n";
        outFile << "                <ul>\n";
        for (auto &player : team2.getPlayers()) {
            outFile << "                    <li>" << player.getName() << "</li>\n";
        }
        outFile << "                </ul>\n";
        outFile << "            </div>\n";
        outFile << "        </section>\n";
        outFile << "        <div class=\"details\">\n";
        outFile << "<section class=\"bar-graph\">\n";
        outFile << "    <h2>Graphical Representation</h2>\n";
        outFile << "    <canvas id='verticalBarGraph'></canvas>\n";
        outFile << "</section>\n";
        outFile << "</section>\n";
        outFile << "<section class=\"innings-details\">\n";
        outFile << "<h2>Innings Details</h2>\n";
        outFile << "                 <table>\n";
        outFile << "                    <thead>\n";
        outFile << "                        <tr>\n";
        outFile << "                            <th>Category</th>\n";
        outFile << "                            <th>Innings 1 (" << innings1Team << ")</th>\n";
        outFile << "                            <th>Innings 2 (" << innings2Team << ")</th>\n";
        outFile << "                        </tr>\n";
        outFile << "                    </thead>\n";
        outFile << "                    <tbody>\n";
        outFile << "                        <tr><td>Total Wickets</td><td>" << playeri1.wicket << "</td><td>" << playeri2.wicket << "</td></tr>\n";
        outFile << "                        <tr><td>Total Fours</td><td>" << playeri1.fours << "</td><td>" << playeri2.fours << "</td></tr>\n";
        outFile << "                        <tr><td>Total Sixes</td><td>" << playeri1.sixes << "</td><td>" << playeri2.sixes << "</td></tr>\n";
        outFile << "                        <tr><td>Total Dot Balls</td><td>" << playeri1.dot << "</td><td>" << playeri2.dot << "</td></tr>\n";
        outFile << "                        <tr><td>Total Extras</td><td>" << playeri1.extraruns << "</td><td>" << playeri2.extraruns
                << "</td></tr>\n";
        outFile << "                        <tr><td>Total Wides</td><td>" << playeri1.wide << "</td><td>" << playeri2.wide << "</td></tr>\n";
        outFile << "                        <tr><td>Total No Balls</td><td>" << playeri1.NB << "</td><td>" << playeri2.NB << "</td></tr>\n";
        outFile << "                        <tr><td>Total Byes</td><td>" << playeri1.byes << "</td><td>" << playeri2.byes << "</td></tr>\n";
        outFile << "                        <tr><td>Total Runs</td><td>" << playeri1.runs << "</td><td>" << playeri2.runs << "</td></tr>\n";
        outFile << "                    </tbody>\n";
        outFile << "                </table>\n";
        outFile << "                <div class=\"match-results\">\n\n\n";
        outFile << "<p>Innings 1 (" << innings1Team << "):  " << playeri1.runs << " runs (" << totalOvers << ") + " << playeri1.wicket << " W</p>\n";
        outFile << "<p>Innings 2 (" << innings2Team << "):  " << playeri2.runs << " runs (" << totalOvers << ") + " << playeri2.wicket
                << " W</p>\n\n";

        // Function for getting display of Match final result
        displayMatchResults1(playeri1.runs, playeri2.runs, team1.getName(), team2.getName(), outFile);

        outFile << "                </div>\n";
        outFile << "            </section>\n";
        outFile << "        </div>\n";
        outFile << "    </div>\n";
        outFile << "    <footer>\n";
        outFile << "        <p>&copy; 2024 Cricket Scorecard</p>\n";
        outFile << "    </footer>\n";
        outFile << "<script src=\"https://cdn.jsdelivr.net/npm/chart.js\"></script>\n";
        outFile << "<script src=\"script.js\"></script>\n";
        outFile << "</body>\n";
        outFile << "</html>\n";
        outFile.close();
        cout << "HTML file generated successfully.\n";

    } else {
        cerr << "Error opening file.\n";
    }
}



    // Function for generating js file
void CricketMatch ::saveJavaScript(const string &filename) {
    ofstream outFile(filename);

    // To get details of team names of innings
    string innings1Team, innings2Team;

    if (choice == 1) {
        innings1Team = team1.getName();
        innings2Team = team2.getName();
    } else {
        innings1Team = team2.getName();
        innings2Team = team1.getName();
    }

    // Calculate maximum values for scaling
    int maxWickets = max(playeri1.wicket, playeri2.wicket);
    int maxFours = max(playeri1.fours, playeri2.fours);
    int maxSixes = max(playeri1.sixes, playeri2.sixes);
    int maxDotBalls = max(playeri1.dot, playeri2.dot);
    int maxExtras = max(playeri1.extraruns, playeri2.extraruns);
    int maxWides = max(playeri1.wide, playeri2.wide);
    int maxNoBalls = max(playeri1.NB, playeri2.NB);
    int maxByes = max(playeri1.byes, playeri2.byes);

    if (outFile.is_open()) {
        outFile << "document.addEventListener(\"DOMContentLoaded\", function() {\n";
        outFile << "    var screenWidth = window.innerWidth;\n"; // Pass screen width to JavaScript
        outFile << "    var ctx = document.getElementById('verticalBarGraph').getContext('2d');\n";
        outFile << "    var verticalBarGraph = new Chart(ctx, {\n";
        outFile << "        type: 'bar',\n";
        outFile << "        data: {\n";
        outFile << "            labels: ['Wickets', 'Fours', 'Sixes', 'Dot Balls', 'Extras', 'Wides', 'No Balls', 'Byes'],\n";
        outFile << "            datasets: [{\n";
        outFile << "                label: 'Innings 1 (" << innings1Team << ")',\n";
        outFile << "                backgroundColor: 'rgba(255, 193, 7,  0.75)',\n";
        outFile << "                borderColor: 'rgba(255, 99, 132, 1)',\n";
        outFile << "                borderWidth: 1,\n";
        outFile << "                data: [" << (maxWickets != 0 ? (double)playeri1.wicket / maxWickets : 0) << ", "
                << (maxFours != 0 ? (double)playeri1.fours / maxFours : 0) << ", " << (maxSixes != 0 ? (double)playeri1.sixes / maxSixes : 0) << ", "
                << (maxDotBalls != 0 ? (double)playeri1.dot / maxDotBalls : 0) << ", "
                << (maxExtras != 0 ? (double)playeri1.extraruns / maxExtras : 0) << ", " << (maxWides != 0 ? (double)playeri1.wide / maxWides : 0)
                << ", " << (maxNoBalls != 0 ? (double)playeri1.NB / maxNoBalls : 0) << ", " << (maxByes != 0 ? (double)playeri1.byes / maxByes : 0)
                << "]\n";
        outFile << "            }, {\n";
        outFile << "                label: 'Innings 2 (" << innings2Team << ")',\n";
        outFile << "                backgroundColor: 'rgba(240, 11, 11, 0.75)',\n";
        outFile << "                borderColor: 'rgba(54, 162, 235, 1)',\n";
        outFile << "                borderWidth: 1,\n";
        outFile << "                data: [" << (maxWickets != 0 ? (double)playeri2.wicket / maxWickets : 0) << ", "
                << (maxFours != 0 ? (double)playeri2.fours / maxFours : 0) << ", " << (maxSixes != 0 ? (double)playeri2.sixes / maxSixes : 0) << ", "
                << (maxDotBalls != 0 ? (double)playeri2.dot / maxDotBalls : 0) << ", "
                << (maxExtras != 0 ? (double)playeri2.extraruns / maxExtras : 0) << ", " << (maxWides != 0 ? (double)playeri2.wide / maxWides : 0)
                << ", " << (maxNoBalls != 0 ? (double)playeri2.NB / maxNoBalls : 0) << ", " << (maxByes != 0 ? (double)playeri2.byes / maxByes : 0)
                << "]\n";
        outFile << "            }]\n";
        outFile << "        },\n";
        outFile << "        options: {\n";
        outFile << "            responsive: true,\n";
        outFile << "            maintainAspectRatio: false,\n";
        outFile << "            scales: {\n";
        outFile << "                x: {\n";
        outFile << "                    stacked: false,\n";
        outFile << "                    ticks: {\n";
        outFile << "                        color: 'white',\n";
        outFile << "                        font: {\n";
        outFile << "                            size: screenWidth > 600 ? 22 : 16\n";
        outFile << "                        }\n";
        outFile << "                    }\n";
        outFile << "                },\n";
        outFile << "                y: {\n";
        outFile << "                    ticks: {\n";
        outFile << "                        color: 'white',\n";
        outFile << "                        font: {\n";
        outFile << "                            size: screenWidth > 600 ? 22 : 16\n";
        outFile << "                        }\n";
        outFile << "                    }\n";
        outFile << "                }\n";
        outFile << "            },\n";
        outFile << "            plugins: {\n";
        outFile << "                legend: {\n";
        outFile << "                    labels: {\n";
        outFile << "                        color: 'white',\n";
        outFile << "                        font: {\n";
        outFile << "                            size: screenWidth > 600 ? 22 : 16\n";
        outFile << "                        }\n";
        outFile << "                    }\n";
        outFile << "                }\n";
        outFile << "            }\n";
        outFile << "        }\n";
        outFile << "    });\n";
        outFile << "});\n";
        outFile.close();
        cout << "JavaScript file generated successfully.\nScorecard has been generated successfully.\n\n\n" << endl;

    } else {
        cerr << "Error opening file.\n";
    }
}



    // Function for displayingthe Mtach results in the web
void CricketMatch ::displayMatchResults1(int inning1runs, int inning2runs, const string &team1Name, const string &team2Name,
                                         ofstream &outFile) const {
    string winningTeam;

    // Determine the winning team based on the total runs scored in their
    // respective innings and their choice to bat first
    if ((inning1runs > inning2runs && getTeam1Choice() == 1) || (inning2runs > inning1runs && getTeam2Choice() == 1)) {
        winningTeam = team1Name;
    } else if ((inning1runs > inning2runs && getTeam2Choice() == 1) || (inning2runs > inning1runs && getTeam1Choice() == 1)) {
        winningTeam = team2Name;
    } else {
        // If both teams scored the same runs, the match ends in a tie
        outFile << "<p>The match between " << team1Name << " and " << team2Name << " ended in a tie.</p>\n";
        return;
    }

    // Display the result based on the winning team
    if (winningTeam == team1Name) {
        outFile << "<p>Team " << team1Name << " emerged victorious, defeating Team " << team2Name << " by a margin of "
                << abs(inning1runs - inning2runs) << " runs.</p>\n";
    } else {
        outFile << "<p>Team " << team2Name << " emerged victorious, defeating Team " << team1Name << " by a margin of "
                << abs(inning2runs - inning1runs) << " runs.</p>\n";
    }
}
