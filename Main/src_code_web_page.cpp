
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

/* The ctime library are used to handle current date and time.   
   The fstream library is utilized for file operations, specifically to create and write to HTML and CSS files.
   The iomanip library provides utilities for input/output formatting, aiding in the precise presentation of data.
   The iostream library facilitates standard input and output operations, 
   The limits helps manage input limits and validation. 
   The string library supports string manipulation
   The vector is employed for managing dynamic arrays, useful for storing lists like player names or teams.
*/


// Define a structure to store details of a player
struct details
{
    string bscore; // Ball score
    string oscore; // Over score
    int NB;        // Number of No Balls
    int dot;       // Number of Dot balls
    int byes;      // Number of Byes
    int wicket;    // Number of Wickets taken
    int runs;      // Number of Runs scored
    int extraruns; // Extra runs (like wides, no balls)
    int fours;     // Number of Fours scored
    int sixes;     // Number of Sixes scored
    int wide;      // Indicates if the ball was a wide
};


// Declare instances of the structure for player details
struct details playeri1;
struct details playeri2;


// Declare for storing the ball by ball score
// Vectors to store the score of every over for Team 1
// Vectors to store the score of every over for Team 2 
vector<string> overs1;
vector<string> overs2;


// Function to clear the input buffer
void clearInputBuffer ()
{
    cin.clear ();
    cin.ignore (numeric_limits<streamsize>::max (), '\n');
}


// Function to delaying the terminal
void delay (unsigned int mseconds)
{
    clock_t goal = mseconds + clock ();
    while (goal > clock ());
}



            //   ****                                        ****   //
            //           CLASSES USED IN MAIN FUNCTION              //
            //   ****                                        ****   //



// Class to represent a cricket player
class CricketPlayer
{
  private:

    string name;

  public:

    CricketPlayer (string n) : name (n), hasPlayed (false) {}
    bool hasPlayed;

    //It will get the name 
    string getName () const
    {
        return name;
    }

    // Function to check wether he played or not 
    bool getHasPlayed () const
    {
        return hasPlayed;
    }

    // It will update if the played has played
    void setHasPlayed (bool played)
    {
        hasPlayed = played;
    }
};



// Class to represent a cricket team
class CricketTeam
{
  private:

    string name;
    vector<CricketPlayer> players;
    int choice;

    //Used friend class
    friend class CricketMatch;

  public:

    //Constructor was initilaised 
    CricketTeam (const string &name) : name (name) {}

    // Add player names 
    void addPlayer (const string &playerName)
    {
        players.emplace_back (playerName);
    }

    // It gets string name
    const string& getName () const
    {
        return name;
    }

    //Function for getting team players
    vector<CricketPlayer>& getPlayers() 
    {
        return players;
    }

    // It will show the player details
    void showDetails () const
    {
        cout << "Team: " << name << "\nPlayers:\n";
        for (const auto &player : players)
            {
                cout << "  " << player.getName () << "\n";
            }
    }

    // It will set player names
    void setPlayerNames ()
    {
        cout << "Enter the names of the players of team " << name << "\n";
        for (int i = 0; i < 11; i++)
            {
                cout << "Player " << i + 1 << ", Name - ";
                string playerName;
                cin >> playerName;
                addPlayer (playerName);
            }
        cout << "\n";
    }

    // It will get the choice took by toss won team
    int getChoice () const
    {
        return choice;
    }

};


// Abstract base class for a ball
class Ball
{
  public:
    virtual void handleBall (int runs, details &player) = 0;
};


// Derived class for a normal scoring ball
class NormalBall : public Ball
{
  public:

    // Function apply changes for Normal Scoring Ball
    void handleBall (int runs, details &player) override
    {
        player.runs += runs;
        player.bscore += to_string (runs);
    }
};


// Derived class for a wide ball
class WideBall : public Ball
{
  public:

    // Function apply changes for wide ball
    void handleBall (int runs, struct details &player) override
    {
        player.bscore += "w ";
        player.wide++;
        player.extraruns += 1 + runs;
        player.runs += 1 + runs; 
        // Wide ball gives 1 extra run plus any run scored off it
    }
};


// Derived class for a no ball
class NoBall : public Ball
{
  public:
    
    // Function apply changes for No Ball
    void handleBall (int runs, struct details &player) override
    {
        player.bscore += "Nb ";
        player.NB++;
        player.extraruns += 1 + runs;
        player.runs += 1 + runs; 
        // No ball gives 1 extra run plus any runs scored off it
    }
};


// Derived class for a bye ball
class ByeBall : public Ball
{
  public:

    // Function apply changes for bye ball
    void handleBall (int runs, details &player) override
    {
        player.byes++;
        player.bscore += "B";
        cout << "Bye ball. Enter the number of bye runs: ";
        int byeRuns;
        cin >> byeRuns;
        player.runs += byeRuns;
        player.extraruns += byeRuns;
    }
};


// Derived class for a dot ball
class DotBall : public Ball
{
  public:

    // Function apply changes for dot ball
    void handleBall (int runs, details &player) override
    {
        player.dot++;
        player.bscore += ".";
    }
};


// Derived class for a four-scoring ball
class FourBall : public Ball
{
  public:

    // Function apply changes for Fours
    void handleBall (int runs, details &player) override
    {
        player.runs += 4;
        player.fours++;
        player.bscore += "4";
    }
};


// Derived class for a six-scoring ball
class SixBall : public Ball
{
  public:

    // Function apply changes for Six
    void handleBall (int runs, details &player) override
    {
        player.runs += 6;
        player.sixes++;
        player.bscore += "6";
    }
};


// Derived class for a wicket-taking ball
class WicketBall : public Ball
{
  public:

    // Function apply changes for wicket
    void handleBall (int runs, details &player) override
    {
        player.wicket++;
        player.bscore += "W";
        wicketout ();
    }

  private:

    // It displays the function that displays what type of out it was
    void wicketout ()
    {

        cout << "\nThe Batsman on the strike was OUT\n";
        cout << "Enter 1 for bowled \n";
        cout << "Enter 2 for caught\n";
        cout << "Enter 3 for stumped\n";
        cout << "Enter 4 for LBW\n";
        cout << "Enter 5 for Run out\n";
        cout << "Enter 6 for Mankad\n";
        cout << "Enter 7 for Retired Hurt\n";
        cout << "Enter 8 for Hit Wicket\n";
        cout << "Choose the number which is given above to enter: ";

        int choice;
        cin >> choice;

        // Switch case which displays which type of out it was
        switch (choice)
            {
            case 1:
                cout << "Batsman was bowled out.\n";
                break;
            case 2:
                cout << "Batsman was caught out.\n";
                break;
            case 3:
                cout << "Batsman was stumped out.\n";
                break;
            case 4:
                cout << "Batsman was LBW out.\n";
                break;
            case 5:
                cout << "Batsman was run out.\n";
                break;
            case 6:
                cout << "Batsman was mankad out.\n";
                break;
            case 7:
                cout << "Batsman retired hurt.\n";
                break;
            case 8:
                cout << "Batsman was hit wicket out.\n";
                break;
            default:
                cout << "Invalid choice.\n";
                break;
            }
    }
};




// Class for Match Details
class CricketMatch
{
  private:

    string venue;
    CricketTeam team1, team2;
    int totalOvers;
    string tossWinner;
    int choice;
    int team1Choice;
    int team2Choice;

    // Function to get the current date and time
    void date ()
    {
        time_t currentTime;
        time (&currentTime);
        cout << ctime (&currentTime);
    }
    
  public:

    // Constructor to initialize the match with team names
    CricketMatch (const string &team1Name, const string &team2Name)
        : team1 (team1Name), team2 (team2Name), totalOvers (0), tossWinner (""),
          choice (0){}


    // Function for returning the time and date 
    string getCurrentDateTime () const
    {
        time_t currentTime;
        time (&currentTime);
        return string (ctime (&currentTime));
    }

    // Function for getting Team1 players                           
    void setTeam1PlayerNames ()
    {
        team1.setPlayerNames ();
    }

    // Function for getting the Team2 players
    void setTeam2PlayerNames ()
    {
        team2.setPlayerNames ();
    }

    // Getters for team1 objects
    CricketTeam& getTeam1 ()
    {
        return team1;
    }

    // Getters for team2 objects
    CricketTeam& getTeam2 ()
    {
        return team2;
    }

        // Function for returning of total overs
    int getTotalOvers () const
    {
        return totalOvers;
    }

    // Function for getting of tosswinner
    string getTossWinner () const
    {
        return tossWinner;
    }

    // Function for getting of team2Choice
    int getTeam2Choice () const
    {
        return team2Choice;
    }

    // Function for getting of team1choice
    int getTeam1Choice () const
    {
        return team1Choice;
    }

    // Functions to set player names for the teams
    void setPlayerNames (CricketTeam &team)
    {
        team.setPlayerNames ();
    }

        // Function to set the details of the match
    void setDetails ()
    {
        cout << "Enter the details of the match\n";
        cout << "Team 1: " << team1.getName () << "\n";
        cout << "Team 2: " << team2.getName () << "\n";

        // Ignore the newline character in the input buffer
        cout << "Venue: ";
        cin.ignore ();
        getline (cin, venue);

        // Function date() to be defined separately
        cout << "Time and Date of the match   ::   ";
        date ();

        // Handle incorrect input for number of overs
        while (true)
            {
                cout << "Number of overs: ";
                if (cin >> totalOvers)
                    {
                        // Exit the loop if input is valid
                        break;
                    }
                else
                    {
                        // Discard invalid input
                        cout << "Invalid input. Please enter a valid number.\n";
                        cin.clear (); // Clear the error flag
                        cin.ignore (numeric_limits<streamsize>::max (), '\n');
                    }
            }

        // Handle incorrect input for toss winner
        while (true)
            {
                cout << "Toss won by which team\n";
                cout << team1.getName () << " or " << team2.getName () << ": ";
                cin >> tossWinner;

                if (tossWinner == team1.getName ()
                    || tossWinner == team2.getName ())
                    {
                        // Exit the loop if input is valid
                        break;
                    }
                else
                    {
                        cout << "You entered a wrong team name. Please enter "
                                "the correct "
                                "team "
                                "name.\n";
                    }
            }

        // Handle incorrect input for batting or bowling choice
        while (true)
            {
                cout << "Press 1 for bat or 2 for bowl: ";
                cin >> choice;

                if (choice == 1 || choice == 2)
                    {
                        // Exit the loop if input is valid
                        break;
                    }
                else
                    {
                        cout << "Invalid input. Please enter 1 for bat or 2 "
                                "for bowl.\n";
                    }
            }

        // Determine the choice for the teams based on the toss result
        if (tossWinner == team1.getName ())
            {
                // Alternate choice for Team 2
                team1Choice = choice;
                team2Choice = (choice == 1) ? 2 : 1;
            }
        else
            {
                // Alternate choice for Team 1
                team2Choice = choice;
                team1Choice = (choice == 1) ? 2 : 1;
            }

        cout << "Team " << tossWinner << " chooses to ";
        if (choice == 1)
            {
                cout << "bat first\n";
            }
        else
            {
                cout << "bowl first\n";
            }
    }




                    //   *****                               *****   //
                    //            Generation of HTML, JS             //
                    //   *****                               *****   //




    // Function for generating HTML file 
    void saveMatchDetails (const string &filename)
    {
        //passing of file name
        ofstream outFile (filename);

        if (outFile.is_open ())
            {
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
                outFile << "    <h1 class=\"main-title\">Live Scorecard<br><span class=\"team-names\">" << team1.getName() << " vs " << team2.getName() << "</span></h1>\n";
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
                if (getTeam1Choice () == 1)
                    {
                        innings1Team = team1.getName ();
                        innings2Team = team2.getName ();
                    }
                else
                    {
                        innings1Team = team2.getName ();
                        innings2Team = team1.getName ();
                    }

                outFile << "    <div class=\"container\">\n";
                outFile << "        <section class=\"teams\">\n";
                outFile << "            <div class=\"team\">\n";
                outFile << "                <h2>Team 1: " << team1.getName ()<< "</h2>\n";
                outFile << "                <ul>\n";
                for (auto &player : team1.getPlayers ())
                    {
                        outFile << "                    <li>"<< player.getName () << "</li>\n";
                    }
                outFile << "                </ul>\n";
                outFile << "            </div>\n";
                outFile << "            <div class=\"team\">\n";
                outFile << "                <h2>Team 2: " << team2.getName ()<< "</h2>\n";
                outFile << "                <ul>\n";
                for (auto &player : team2.getPlayers ())
                    {
                        outFile << "                    <li>"<< player.getName () << "</li>\n";
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
                outFile << "                        <tr><td>Total Extras</td><td>" << playeri1.extraruns << "</td><td>" << playeri2.extraruns << "</td></tr>\n";
                outFile << "                        <tr><td>Total Wides</td><td>" << playeri1.wide << "</td><td>" << playeri2.wide << "</td></tr>\n";
                outFile << "                        <tr><td>Total No Balls</td><td>" << playeri1.NB << "</td><td>" << playeri2.NB << "</td></tr>\n";
                outFile << "                        <tr><td>Total Byes</td><td>" << playeri1.byes << "</td><td>" << playeri2.byes << "</td></tr>\n";
                outFile << "                        <tr><td>Total Runs</td><td>" << playeri1.runs << "</td><td>" << playeri2.runs << "</td></tr>\n";
                outFile << "                    </tbody>\n";
                outFile << "                </table>\n";
                outFile << "                <div class=\"match-results\">\n\n\n";
                outFile << "<p>Innings 1 (" << innings1Team << "):  " << playeri1.runs << " runs (" << totalOvers << ") + "<< playeri1.wicket << " W</p>\n";
                outFile << "<p>Innings 2 (" << innings2Team << "):  " << playeri2.runs << " runs (" << totalOvers << ") + "<< playeri2.wicket << " W</p>\n\n";

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
    void saveJavaScript(const string &filename) {
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
            outFile << "            labels: ['Wickets', 'Fours', 'Sixes', 'Dot Balls', 'Extras', 'Wides', 'No Balls', 'Byes', 'Twos', 'Threes', 'Total Runs', 'Catches'],\n";
            outFile << "            datasets: [{\n";
            outFile << "                label: 'Innings 1 (" << innings1Team << ")',\n";
            outFile << "                backgroundColor: 'rgba(255, 193, 7,  0.75)',\n";
            outFile << "                borderColor: 'rgba(255, 99, 132, 1)',\n";
            outFile << "                borderWidth: 1,\n";
            outFile << "                data: [" 
                << (maxWickets != 0 ? (double)playeri1.wicket / maxWickets : 0) << ", " 
                << (maxFours != 0 ? (double)playeri1.fours / maxFours : 0) << ", " 
                << (maxSixes != 0 ? (double)playeri1.sixes / maxSixes : 0) << ", " 
                << (maxDotBalls != 0 ? (double)playeri1.dot / maxDotBalls : 0) << ", " 
                << (maxExtras != 0 ? (double)playeri1.extraruns / maxExtras : 0) << ", " 
                << (maxWides != 0 ? (double)playeri1.wide / maxWides : 0) << ", " 
                << (maxNoBalls != 0 ? (double)playeri1.NB / maxNoBalls : 0) << ", " 
                << (maxByes != 0 ? (double)playeri1.byes / maxByes : 0) << "]\n";
            outFile << "            }, {\n";
            outFile << "                label: 'Innings 2 (" << innings2Team << ")',\n";
            outFile << "                backgroundColor: 'rgba(240, 11, 11, 0.75)',\n";
            outFile << "                borderColor: 'rgba(54, 162, 235, 1)',\n";
            outFile << "                borderWidth: 1,\n";
            outFile << "                data: [" 
                << (maxWickets != 0 ? (double)playeri2.wicket / maxWickets : 0) << ", " 
                << (maxFours != 0 ? (double)playeri2.fours / maxFours : 0) << ", " 
                << (maxSixes != 0 ? (double)playeri2.sixes / maxSixes : 0) << ", " 
                << (maxDotBalls != 0 ? (double)playeri2.dot / maxDotBalls : 0) << ", " 
                << (maxExtras != 0 ? (double)playeri2.extraruns / maxExtras : 0) << ", " 
                << (maxWides != 0 ? (double)playeri2.wide / maxWides : 0) << ", " 
                << (maxNoBalls != 0 ? (double)playeri2.NB / maxNoBalls : 0) << ", " 
                << (maxByes != 0 ? (double)playeri2.byes / maxByes : 0) << "]\n";
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
    void displayMatchResults1 (int inning1runs, int inning2runs,const string &team1Name,
                                     const string &team2Name, ofstream &outFile) const
    {
        string winningTeam;

        // Determine the winning team based on the total runs scored in their
        // respective innings and their choice to bat first
        if ((inning1runs > inning2runs && getTeam1Choice () == 1)
            || (inning2runs > inning1runs && getTeam2Choice () == 1))
            {
                winningTeam = team1Name;
            }
        else if ((inning1runs > inning2runs && getTeam2Choice () == 1)
                || (inning2runs > inning1runs && getTeam1Choice () == 1))
            {
                winningTeam = team2Name;
            }
        else
            {
                // If both teams scored the same runs, the match ends in a tie
                outFile << "<p>The match between " << team1Name << " and "
                        << team2Name << " ended in a tie.</p>\n";
                return;
            }

        // Display the result based on the winning team
        if (winningTeam == team1Name)
            {
                outFile << "<p>Team " << team1Name
                        << " emerged victorious, defeating Team " << team2Name
                        << " by a margin of " << abs (inning1runs - inning2runs)
                        << " runs.</p>\n";
            }
        else
            {
                outFile << "<p>Team " << team2Name
                        << " emerged victorious, defeating Team " << team1Name
                        << " by a margin of " << abs (inning2runs - inning1runs)
                        << " runs.</p>\n";
            }
    }


};



//  FUNCTIONS USED IN MAIN FUNCTION   //



// Function to remember to the input value
void score_value ()
{
    cout << "*** REMEMBER ALL BALL INPUT OPTIONS ***\n\n";
    cout << "!!! ENTER INPUTS ONLY FROM THE GIVEN LIST BELOW !!!\n\n";
    cout << "To record a dot ball, enter <.>.\n";
    cout << "For 1 run, enter <N> followed by 1.\n";
    cout << "For 2 runs, enter <N> followed by 2.\n";
    cout << "For 3 runs, enter <N> followed by 3.\n";
    cout << "For 4 runs (boundary), enter <4>.\n";
    cout << "For 6 runs (boundary), enter <6>.\n";
    cout << "To record a wicket, enter <W>.\n";
    cout << "To record a wide, enter <w>.\n";
    cout << "To record a no ball, enter <Nb>.\n";
    cout << "To record byes, enter <B>.\n";
    cout << "!!! Incorrect inputs will prompt for re-entry !!!\n";
}


// Function to verify and set the batsmen
void checkBatsmen (vector<CricketPlayer> &players, string &striker,string &nonStriker)
{
    bool strikerVerified = false, nonStrikerVerified = false;

    // Verify the striker and non-striker names
    for (int i = 0; i < players.size (); ++i)
        {
            if (players[i].getName () == striker && !players[i].hasPlayed)
                {
                    strikerVerified = true;
                    players[i].hasPlayed = true;
                    cout << "Striker's name verified. You can proceed now for "
                            "bat.\n";
                }
            if (players[i].getName () == nonStriker && !players[i].hasPlayed)
                {
                    nonStrikerVerified = true;
                    players[i].hasPlayed = true;
                    cout << "Non-striker's name verified. You can proceed now "
                            "for bat.\n";
                }
        }

    // Check if the striker name is valid
    while (!strikerVerified)
        {
            cout << "Striker's name is invalid or has already played. Enter a "
                    "new name: ";
            getline (cin, striker);
            for (int i = 0; i < players.size (); ++i)
                {
                    if (players[i].getName () == striker
                        && !players[i].hasPlayed)
                        {
                            strikerVerified = true;
                            players[i].hasPlayed = true;
                            cout << "Striker's name verified. You can proceed "
                                    "now for bat.\n";
                            break;
                        }
                }
        }

    // Check if the non-striker name is valid
    while (!nonStrikerVerified)
        {
            cout << "Non-striker's name is invalid or has already played. "
                    "Enter a new name: ";
            getline (cin, nonStriker);
            for (int i = 0; i < players.size (); ++i)
                {
                    // Verifying the non striker has player or not yet
                    if (players[i].getName () == nonStriker
                        && !players[i].hasPlayed)
                        {
                            nonStrikerVerified = true;
                            players[i].hasPlayed = true;
                            cout << "Non-striker's name verified. You can "
                                    "proceed now for bat.\n";
                            break;
                        }
                }
        }
}


// Function to verify and set the bowler
void checkBowler (vector<CricketPlayer> &players, string &bowler)
{
    //Initially declared player player was not verified 
    bool bowlerVerified = false;

    // Verify the bowler name
    while (!bowlerVerified)
        {
            for (int i = 0; i < players.size (); ++i)
                {
                    if (players[i].getName () == bowler)
                        {
                            bowlerVerified = true;
                            cout << "Bowler's name verified. You can proceed "
                                    "now for bowl.\n";
                            break;
                        }
                }

              // If bowler name was not verified then again ...  
            if (!bowlerVerified)
                {
                    cout << "Bowler's name is invalid. Enter a new name: ";
                    getline (cin, bowler);
                }
        }
}


// Function to check if a batsman is valid
bool isValidBatsman (const string &newBatsman, const vector<CricketPlayer> &team)
{
    for (const auto &player : team)
        {
            if (player.getName () == newBatsman && !player.getHasPlayed ())
                {
                    return true;
                }
        }
    return false;
}


// Function to enter a new batsman
void enterNewBatsman (vector<CricketPlayer> &team, string &batsman)
{
    clearInputBuffer ();
    while (true)
        {
            cout << "Enter the name of the new batsman: ";
            getline (cin, batsman);

            if (!isValidBatsman (batsman, team))
                {
                    cout << "The batsman does not belong to the same team or "
                            "has already played. Please enter a valid batsman."
                         << endl;
                }
            else
                {
                    for (auto &player : team)
                        {
                            if (player.getName () == batsman)
                                {
                                    player.setHasPlayed (true);
                                    break;
                                }
                        }
                    break;
                }
        }
}


// Function to display the scorecard for each over and total innings score
void displayScoreboard (vector<string> &overs, details &innings)
{

    // Variables to keep track of over and ball counts
    int j = 0, k = 0;

    // Iterate over each ball in the overs vector
    for (size_t i = 0; i < overs.size (); i++)
        {
            // Check if a new over is starting
            if (i == 6 * k)
                {
                    cout << "\nScore Details of Over " << k + 1 << ": " << endl;
                    // Increment the over count
                    k++;
                }

            // Calculate the ball count for the current over
            j = ((i) % 6);
            cout << "Ball " << j + 1 << ": ";

            // Print the type of delivery for each ball in the current over
            for (char ballType : overs[i])
                {
                    cout << ballType << " ";
                }

            // Move to the next line for the next ball
            cout << endl;
        }

    // Print total score details for the innings

    cout << "\n\nTotal Score in Innings --> [ " << innings.runs << " - "
         << innings.wicket << " ]\n\n"
         << endl;
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


// Function to display the result of the cricket match
void displayMatchResult (const CricketMatch &match, const string &team1Name,
                    const string &team2Name, int inning1runs, int inning2runs)
{
    //String for storing of winning Team
    string winningTeam;

    // Determine the winning team based on the total runs scored in their
    // respective innings and their choice to bat first
    if ((inning1runs > inning2runs && match.getTeam1Choice () == 1)
        || (inning2runs > inning1runs && match.getTeam2Choice () == 1))
        {
            winningTeam = team1Name;
        }
    else if ((inning1runs > inning2runs && match.getTeam2Choice () == 1)
             || (inning2runs > inning1runs && match.getTeam1Choice () == 1))
        {
            winningTeam = team2Name;
        }
    else
        {
            // If both teams scored the same runs, the match ends in a tie
            cout << "\n\n\n\n\n\n\n\n\n       The match between " << team1Name
                 << " and " << team2Name
                 << " ended in a tie.\n\n\n\n\n\n\n\n\n\n\n\n"
                 << endl;
            return;
        }

    // Display the result based on the winning team
    if (winningTeam == team1Name)
        {
            cout << "\n\n\n\n\n\n\n\n\n\n      The Team " << team1Name
                 << " emerged victorious, defeating the Team " << team2Name
                 << " by a margin of " << abs (inning1runs - inning2runs)
                 << " runs.\n\n\n\n\n\n\n\n\n\n\n\n"
                 << endl;
        }
    else
        {
            cout << "\n\n\n\n\n\n\n\n\n\n      The Team " << team2Name
                 << " emerged victorious, defeating the Team " << team1Name
                 << " by a margin of " << abs (inning2runs - inning1runs)
                 << " runs.\n\n\n\n\n\n\n\n\n\n\n\n"
                 << endl;
        }

}







int main ()
{
    // Clear the console screen
    system ("cls");

    // Total number of overs in the match
    int totalovers;

    // Names of Team 1 and Team 2
    // Names of the bowler, striker, and non-striker
    string team1Name, team2Name;
    string Bow, Striker, Nonstriker;

    // Input team names
    cout << "Enter Team 1 name: ";
    getline (cin, team1Name);
    cout << "Enter Team 2 name: ";
    getline (cin, team2Name);

    // Clear the console screen
    system ("cls");

    // Create a CricketMatch object with the team names
    // Set match details
    // Set player names for Team 1
    // Set player names for Team 2
    CricketMatch match (team1Name, team2Name);
    match.setDetails ();

    // Clear the console screen
    system ("cls");

    match.setTeam1PlayerNames ();
    match.setTeam2PlayerNames ();

    // Get total overs in the match
    // Get the toss winner
    totalovers = match.getTotalOvers ();
    string tossWinner = match.getTossWinner ();

    // it clears the screen
    // it calls the function score_value
    // delay is a function which delays the screen time
    // it clears the screen
    system ("cls");
    score_value ();
    delay (8000);
    system ("cls");

    // Iterate for each inning
    for (int inning = 1; inning <= 2; inning++)
        {
            // Determine the batting and bowling teams for the current inning
            cout << "Inning " << inning << endl;
            cout << "Team 1 --> " << match.getTeam1 ().getName () << " is ";

            // Condition for checking, eiter team 1 is getting batting or bowling
            if (((inning == 1
                  && ((tossWinner == match.getTeam1 ().getName ()
                       && match.getTeam1Choice () == 1)
                      || (tossWinner == match.getTeam2 ().getName ()
                          && match.getTeam2Choice () == 2)))
                 || (inning == 2
                     && ((tossWinner == match.getTeam1 ().getName ()
                          && match.getTeam1Choice () == 2)
                         || (tossWinner == match.getTeam2 ().getName ()
                             && match.getTeam2Choice () == 1)))))
                {
                    cout << "batting" << endl;
                }
            else
                {
                    cout << "bowling" << endl;
                }

            // Condition for checking either team 2 is getting bowling or batting
            cout << "Team 2 --> " << match.getTeam2 ().getName () << " is ";
            if (((inning == 1
                  && ((tossWinner == match.getTeam1 ().getName ()
                       && match.getTeam1Choice () == 1)
                      || (tossWinner == match.getTeam2 ().getName ()
                          && match.getTeam2Choice () == 2)))
                 || (inning == 2
                     && ((tossWinner == match.getTeam1 ().getName ()
                          && match.getTeam1Choice () == 2)
                         || (tossWinner == match.getTeam2 ().getName ()
                             && match.getTeam2Choice () == 1)))))
                {
                    cout << "bowling" << endl;
                }
            else
                {
                    cout << "batting" << endl;
                }

            // Get the batting team players for the current inning
            vector<CricketPlayer> &battingTeamPlayers
                = ((inning == 1
                    && ((tossWinner == match.getTeam1 ().getName ()
                         && match.getTeam1Choice () == 1)
                        || (tossWinner == match.getTeam2 ().getName ()
                            && match.getTeam2Choice () == 2)))
                   || (inning == 2
                       && ((tossWinner == match.getTeam1 ().getName ()
                            && match.getTeam1Choice () == 2)
                           || (tossWinner == match.getTeam2 ().getName ()
                               && match.getTeam2Choice () == 1))))
                      ? match.getTeam1 ().getPlayers ()
                      : match.getTeam2 ().getPlayers ();

            // Getting the bowling team players for the current innings
            vector<CricketPlayer> &bowlingTeamPlayers
                = ((inning == 1
                    && ((tossWinner == match.getTeam1 ().getName ()
                         && match.getTeam1Choice () == 1)
                        || (tossWinner == match.getTeam2 ().getName ()
                            && match.getTeam2Choice () == 2)))
                   || (inning == 2
                       && ((tossWinner == match.getTeam1 ().getName ()
                            && match.getTeam1Choice () == 2)
                           || (tossWinner == match.getTeam2 ().getName ()
                               && match.getTeam2Choice () == 1))))
                      ? match.getTeam2 ().getPlayers ()
                      : match.getTeam1 ().getPlayers ();

            // Input striker names and verify them
            cout << "Enter striker's name: ";
            clearInputBuffer ();
            getline (cin, Striker);

            // Input non striker names and verify them
            cout << "Enter non-striker's name: ";
            getline (cin, Nonstriker);
            checkBatsmen (battingTeamPlayers, Striker, Nonstriker);

            for (int j = 1; j <= totalovers; j++)
                {
                    // Input bowler's name and verify it
                    clearInputBuffer ();
                    cout << "Enter bowlers name: ";
                    getline (cin, Bow);
                    checkBowler (bowlingTeamPlayers, Bow);
                    
                    // Giving the score input for overs
                    cout << "Give the score input for the over " << j << endl;
                    int sumbscore = 0;

                    // Input the score for each ball in the over
                    for (int i = ((6) * (j - 1)); i < ((6) * (j)); i++)
                        {
                            //initialised the ball type and input for it
                            string ballType;
                            cin >> ballType;

                            //intialised currentBall to null for class Ball
                            Ball *currentBall = nullptr;

                            // Handle different types of balls based on user
                            // It is for innings 1
                            if (inning == 1)
                                {
                                    // Create a new ball object based on the
                                    // ball type
                                    // When it is a Normal Ball, we have to enter 1/2/3/..
                                    if (ballType == "N")
                                        {
                                            currentBall = new NormalBall ();
                                            int runs;
                                            cout
                                                << "Enter the number of runs: ";
                                            cin >> runs;
                                            currentBall->handleBall (runs,
                                                                     playeri1);
                                        }

                                    // When it is a wide ball, we have to enter w 
                                    else if (ballType == "w")
                                        {
                                            // Handle wide ball separately
                                            // Decrement i to account for the
                                            // extra delivery
                                            currentBall = new WideBall ();
                                            int runs;
                                            cout << "Enter the number of runs "
                                                    "off the wide ball: ";
                                            cin >> runs;
                                            currentBall->handleBall (runs,
                                                                     playeri1);
                                            --i;
                                            continue;
                                        }

                                    // When it is a No Ball, we have to enter Nb
                                    else if (ballType == "Nb")
                                        {
                                            // Handle no ball separately
                                            // Decrement i to a
                                            currentBall = new NoBall ();
                                            int runs;
                                            cout << "Enter the number of runs "
                                                    "off the no ball: ";
                                            cin >> runs;
                                            currentBall->handleBall (runs,
                                                                     playeri1);
                                            --i;
                                            continue;
                                        }

                                    // When it is a byes, we have to enter the B
                                    else if (ballType == "B")
                                        {
                                            currentBall = new ByeBall ();
                                            currentBall->handleBall (0,
                                                                     playeri1);
                                        }

                                    // When it is a dot ball, we have to enter .
                                    else if (ballType == ".")
                                        {
                                            currentBall = new DotBall ();
                                            currentBall->handleBall (0,
                                                                     playeri1);
                                        }

                                    // When it is a four, we have to enter 4
                                    else if (ballType == "4")
                                        {
                                            currentBall = new FourBall ();
                                            currentBall->handleBall (0,
                                                                     playeri1);
                                        }

                                    // When it is a six, we have to enter 6
                                    else if (ballType == "6")
                                        {
                                            currentBall = new SixBall ();
                                            currentBall->handleBall (0,
                                                                     playeri1);
                                        }

                                    // When it is Wicket, we have to enter W 
                                    // and it gets verified which type of out it was.
                                    else if (ballType == "W")
                                        {
                                            // Handle wicket ball separately
                                            // Enter a new batsman
                                            currentBall = new WicketBall ();
                                            currentBall->handleBall (0,
                                                                     playeri1);
                                            enterNewBatsman (battingTeamPlayers,
                                                             Striker);
                                            cout << "New batsman: " << Striker
                                                 << endl;
                                        }

                                    // If the ball type doesnot belongs to any of these it results this 
                                    else
                                        {
                                            cout << "Invalid ball type!"
                                                 << endl;
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
                                    overs1.push_back (playeri1.bscore);
                                    playeri1.bscore = "";
                                }

                            // It is for innings 2 input
                            else
                                {
                                    // If the ball type is Normal ball enter N
                                    // Handle balls for the second inning
                                    if (ballType == "N")
                                        {
                                            currentBall = new NormalBall ();
                                            int runs;
                                            cout
                                                << "Enter the number of runs: ";
                                            cin >> runs;
                                            currentBall->handleBall (runs,
                                                                     playeri2);
                                        }

                                    // If the ball type is wide ball enter w
                                    else if (ballType == "w")
                                        {
                                            currentBall = new WideBall ();
                                            int runs;
                                            cout << "Enter the number of runs "
                                                    "off the wide ball: ";
                                            cin >> runs;
                                            currentBall->handleBall (runs,
                                                                     playeri2);
                                            // Decrement i to account for the
                                            // extra delivery
                                            --i;
                                            continue;
                                        }

                                    // If the ball type is No ball enter No
                                    else if (ballType == "Nb")
                                        {
                                            currentBall = new NoBall ();
                                            int runs;
                                            cout << "Enter the number of runs "
                                                    "off the no ball: ";
                                            cin >> runs;
                                            currentBall->handleBall (runs,
                                                                     playeri2);
                                            // Decrement i to a
                                            --i;
                                            continue;
                                        }

                                    // If the ball type is Byyes ball enter B
                                    else if (ballType == "B")
                                        {
                                            currentBall = new ByeBall ();
                                            currentBall->handleBall (0,
                                                                     playeri2);
                                        }

                                    // If the ball type is Dot ball enter .
                                    else if (ballType == ".")
                                        {
                                            currentBall = new DotBall ();
                                            currentBall->handleBall (0,
                                                                     playeri2);
                                        }

                                    // If the ball type is four enter 4
                                    else if (ballType == "4")
                                        {
                                            currentBall = new FourBall ();
                                            currentBall->handleBall (0,
                                                                     playeri2);
                                        }

                                    // If the ball type is six enter 6
                                    else if (ballType == "6")
                                        {
                                            currentBall = new SixBall ();
                                            currentBall->handleBall (0,
                                                                     playeri2);
                                        }

                                    // If the ball type is Wicket ball enter W
                                    else if (ballType == "W")
                                        {
                                            currentBall = new WicketBall ();
                                            currentBall->handleBall (0,
                                                                     playeri2);
                                            enterNewBatsman (battingTeamPlayers,
                                                             Striker);
                                            cout << "New batsman: " << Striker
                                                 << endl;
                                        }

                                    // If the ball type is invalid ball then it occurs
                                    else
                                        {
                                            // Decrement i to account for the
                                            // invalid input
                                            cout << "Invalid ball type!"
                                                 << endl;
                                            --i;
                                            continue;
                                        }

                                    // Store the over score
                                    // Store the score for the over
                                    // Reset bscore for the next
                                    delete currentBall;
                                    playeri2.oscore += playeri2.bscore + " ";
                                    overs2.push_back (playeri2.bscore);
                                    playeri2.bscore = "";
                                }
                        }
                }
            // Clear the console screen
            system ("cls");
        }

    // Clear the console screen
    system ("cls");

    // calling the function for score details of @ 1st innings
    if (match.getTeam1Choice () == 1)
        {
            cout << "Innings 1 Score card : \n" << endl;
            cout << "Batting  @  " << team1Name << " !!\n\n" << endl;
        }
    else
        {
            cout << "Innings 1 Score card : \n" << endl;
            cout << "Batting  @  " << team2Name << " !!\n\n" << endl;
        }

    displayScoreboard (overs1, playeri1);
    delay(8000);

    // Clear the console screen
    system ("cls");

    // calling the function for score details of @ 2nd Innings
    if (match.getTeam1Choice () == 1)
        {
            cout << "Innings 2 Score card : \n" << endl;
            cout << "Batting  @  " << team2Name << " !!\n\n" << endl;
        }
    else
        {
            cout << "Innings 2 Score card : \n" << endl;
            cout << "Batting  @  " << team1Name << " !!\n\n" << endl;
        }

    displayScoreboard (overs2, playeri2);
    delay(8000);

    // Clear the console screen
    system ("cls");


    // Calling the function to give content to html 
    match.saveMatchDetails("../Front_End/index1.html");

    // Calling the function to give content to js
    match.saveJavaScript("../Front_End/script.js");

    // Calling the function for declaring who won the match
    displayMatchResult (match, team1Name, team2Name, playeri1.runs,
                        playeri2.runs);


    return 0;
}
