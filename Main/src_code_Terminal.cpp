#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include<time.h>

using namespace std;


    // Function to clear the input buffer
void clearInputBuffer ()
{
  cin.clear ();
  cin.ignore (numeric_limits<streamsize>::max (), '\n');
}

    //Function to delay the terminal
 void delay(unsigned int mseconds)//function for delay
{
    clock_t goal=mseconds+clock();
    while(goal>clock());
}


    // Class to represent a cricket player
class CricketPlayer
{
private:
  string name;

public:
  CricketPlayer (string n) : name (n), hasPlayed (false) {}
  bool hasPlayed;

  string getName () const
  {
    return name;
  }

  bool getHasPlayed () const
  {
    return hasPlayed;
  }

  void setHasPlayed (bool played)
  {
    hasPlayed = played;
  }
};


    // Class to represent a cricket team
class CricketTeam
{
  friend class CricketMatch;

public:
  CricketTeam (const string &name) : name (name) {}

  void addPlayer (const string &playerName)
  {
    players.emplace_back (playerName);
  }

  const string& getName () const
  {
    return name;
  }

  void showDetails () const
  {
    cout << "Team: " << name << "\nPlayers:\n";
    for (const auto &player : players)
      {
        cout << "  " << player.getName () << "\n";
      }
  }

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

  vector<CricketPlayer> &getPlayers ()
  {
    return players;
  }

  int getChoice () const
  {
    return choice;
  }

private:
  string name;
  vector<CricketPlayer> players;
  int choice;
};


    //Class for Match Details
class CricketMatch
{
public:
  // Constructor to initialize the match with team names
  CricketMatch (const string &team1Name, const string &team2Name)
      : team1 (team1Name), team2 (team2Name), totalOvers (0), tossWinner (""),
        choice (0)
  {
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

        if (tossWinner == team1.getName () || tossWinner == team2.getName ())
          {
            // Exit the loop if input is valid
            break;
          }
        else
          {
            cout << "You entered a wrong team name. Please enter the correct "
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
            cout << "Invalid input. Please enter 1 for bat or 2 for bowl.\n";
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

  // Getters for match details
  int getTotalOvers () const
  {
    return totalOvers;
  }

  string getTossWinner () const
  {
    return tossWinner;
  }

  int getTeam2Choice () const
  {
    return team2Choice;
  }

  int getTeam1Choice () const
  {
    return team1Choice;
  }

  // Functions to set player names for the teams
  void setPlayerNames (CricketTeam &team)
  {
    team.setPlayerNames ();
  }

  void setTeam1PlayerNames ()
  {
    team1.setPlayerNames ();
  }

  void setTeam2PlayerNames ()
  {
    team2.setPlayerNames ();
  }

  // Getters for team objects
  CricketTeam& getTeam1 ()
  {
    return team1;
  }

  CricketTeam& getTeam2 ()
  {
    return team2;
  }

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
};


    // Function to verify and set the batsmen
void checkBatsmen(vector<CricketPlayer>& players, string& striker, string& nonStriker) 
{
  bool strikerVerified = false, nonStrikerVerified = false;

  // Verify the striker and non-striker names
  for (int i = 0; i < players.size(); ++i) 
  {
    if (players[i].getName() == striker && !players[i].hasPlayed) 
    {
      strikerVerified = true;
      players[i].hasPlayed = true;
      cout << "Striker's name verified. You can proceed now for bat.\n";
    }
    if (players[i].getName() == nonStriker && !players[i].hasPlayed) 
    {
      nonStrikerVerified = true;
      players[i].hasPlayed = true;
      cout << "Non-striker's name verified. You can proceed now for bat.\n";
    }
  }

  // Check if the striker name is valid
  while (!strikerVerified) 
  {
    cout << "Striker's name is invalid or has already played. Enter a new name: ";
    getline(cin, striker);
    for (int i = 0; i < players.size(); ++i) 
    {
      if (players[i].getName() == striker && !players[i].hasPlayed) 
      {
        strikerVerified = true;
        players[i].hasPlayed = true;
        cout << "Striker's name verified. You can proceed now for bat.\n";
        break;
      }
    }
  }

  // Check if the non-striker name is valid
  while (!nonStrikerVerified) 
  {
    cout << "Non-striker's name is invalid or has already played. Enter a new name: ";
    getline(cin, nonStriker);
    for (int i = 0; i < players.size(); ++i) 
    {
      if (players[i].getName() == nonStriker && !players[i].hasPlayed) 
      {
        nonStrikerVerified = true;
        players[i].hasPlayed = true;
        cout << "Non-striker's name verified. You can proceed now for bat.\n";
        break;
      }
    }
  }
}

    
    // Function to check if a batsman is valid
bool isValidBatsman(const string& newBatsman, const vector<CricketPlayer>& team) 
{
    for (const auto& player : team) 
    {
        if (player.getName() == newBatsman && !player.getHasPlayed()) 
        {
            return true;
        }
    }
    return false;
}

    
    // Function to enter a new batsman
void enterNewBatsman(vector<CricketPlayer>& team, string& batsman) 
{
    clearInputBuffer();
    while (true) 
    {
        cout << "Enter the name of the new batsman: ";
        getline(cin, batsman);

        if (!isValidBatsman(batsman, team)) 
        {
            cout << "The batsman does not belong to the same team or has already played. Please enter a valid batsman." << endl;
        } else 
        {
            for (auto& player : team) 
            {
                if (player.getName() == batsman) 
                {
                    player.setHasPlayed(true);
                    break;
                }
            }
            break;
        }
    }
}

    
    // Function to verify and set the bowler
void checkBowler(vector<CricketPlayer>& players, string& bowler) 
{
  bool bowlerVerified = false;

  // Verify the bowler name
  while (!bowlerVerified) 
  {
    for (int i = 0; i < players.size(); ++i) 
    {
      if (players[i].getName() == bowler) 
      {
        bowlerVerified = true;
        cout << "Bowler's name verified. You can proceed now for bowl.\n";
        break;
      }
    }
    if (!bowlerVerified) 
    {
      cout << "Bowler's name is invalid. Enter a new name: ";
      getline(cin, bowler);
    }
  }
}


    
    // Define a structure to store details of a player
struct details {
  string bscore;  // Ball score
  string oscore;  // Over score
  int NB;         // Number of No Balls
  int dot;        // Number of Dot balls
  int byes;       // Number of Byes
  int wicket;     // Number of Wickets taken
  int runs;       // Number of Runs scored
  int extraruns;  // Extra runs (like wides, no balls)
  int fours;      // Number of Fours scored
  int sixes;      // Number of Sixes scored
  int wide;       // Indicates if the ball was a wide
};

// Declare instances of the structure for player details
struct details playeri1;
struct details playeri2;

    
    
    // Abstract base class for a ball
class Ball 
{
 public:
  virtual void handleBall(int runs, details& player) = 0;
};

    // Derived class for a normal scoring ball
class NormalBall : public Ball 
{
public:
    void handleBall(int runs, details& player) override 
    {
        player.runs += runs;
        player.bscore += to_string(runs);
    }
};

    // Derived class for a wide ball
class WideBall : public Ball 
{
public:
    void handleBall(int runs, struct details& player) override 
    {
        player.bscore += "w ";
        player.wide++;
        player.extraruns += 1 + runs;
        player.runs += 1 + runs;  // Wide ball gives 1 extra run plus any runs scored off it
    }
};

    // Derived class for a no ball
class NoBall : public Ball 
{
public:
    void handleBall(int runs, struct details& player) override 
    {
        player.bscore += "Nb ";
        player.NB++;
        player.extraruns += 1 + runs;
        player.runs += 1 + runs;  // No ball gives 1 extra run plus any runs scored off it
    }
};

    // Derived class for a bye ball
class ByeBall : public Ball 
{
 public:
  void handleBall(int runs, details& player) override 
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
  void handleBall(int runs, details& player) override 
  {
    player.dot++;
    player.bscore += ".";
  }
};

    // Derived class for a four-scoring ball
class FourBall : public Ball 
{
 public:
  void handleBall(int runs, details& player) override 
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
  void handleBall(int runs, details& player) override 
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
    void handleBall(int runs, details& player) override 
    {
        player.wicket++;
        player.bscore += "W";
        wicketout();
    }

private:
    void wicketout() 
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


    // Function to display the result of the cricket match
void displayMatchResult(const CricketMatch& match, const string& team1Name, const string& team2Name, int inning1runs, int inning2runs) 
{
    string winningTeam;
    
    // Determine the winning team based on the total runs scored in their respective innings and their choice to bat first
    if ((inning1runs > inning2runs && match.getTeam1Choice() == 1) ||
        (inning2runs > inning1runs && match.getTeam2Choice() == 1)) {
        winningTeam = team1Name;
    } else if ((inning1runs > inning2runs && match.getTeam2Choice() == 1) ||
               (inning2runs > inning1runs && match.getTeam1Choice() == 1)) {
        winningTeam = team2Name;
    } else {
        // If both teams scored the same runs, the match ends in a tie
        cout << "\n\n\n\n\n\n       The match between " << team1Name << " and " << team2Name << " ended in a tie.\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
        return;
    }

    // Display the result based on the winning team
    if (winningTeam == team1Name) {
        cout <<"\n\n\n\n\n\n\n      The Team "<< team1Name << " emerged victorious, defeating the Team "<< team2Name << " by a margin of " << abs(inning1runs - inning2runs) << " runs.\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    } else {
        cout <<"\n\n\n\n\n\n\n      The Team "<< team2Name << " emerged victorious, defeating the Team "<< team1Name << " by a margin of " << abs(inning2runs - inning1runs) << " runs.\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    }
}


    // Function to display the scorecard for each over and total innings score
void displayScoreboard(vector<string>& overs, details& innings) 
{

    // Variables to keep track of over and ball counts
    int j = 0, k = 0;

    // Iterate over each ball in the overs vector
    for (size_t i = 0; i < overs.size(); i++) 
    {
        // Check if a new over is starting
        if (i == 6 * k) {
            cout << "\nScore Details of Over " << k + 1 << ": " << endl;
            k++; // Increment the over count
        }

        j = ((i) % 6); // Calculate the ball count for the current over
        cout << "Ball " << j + 1 << ": ";
        
        // Print the type of delivery for each ball in the current over
        for (char ballType : overs[i]) 
        {
            cout << ballType << " ";      
        }
        cout << endl; // Move to the next line for the next ball
    }

    // Print total score details for the innings

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


    // Function to remember to the input value
void score_value() {
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







int main ()
{
  // Clear the console screen
  system ("cls");

  // Total number of overs in the match
  // Vectors to store the score of every over for Team 1
  // Vectors to store the score of every over for Team 2
  int totalovers;
  vector<string> overs1;
  vector<string> overs2;

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

  //it clears the screen
  //it calls the function score_value
  //delay is a function which delays the screen time
  //it clears the screen
  system("cls");                          
	score_value();                          
	delay(6000);                           
	system("cls");                          

  // Iterate for each inning
  for (int inning = 1; inning <= 2; inning++)
    {
      // Determine the batting and bowling teams for the current inning
      cout << "Inning " << inning << endl;
      cout << "Team 1 --> " << match.getTeam1 ().getName () << " is ";
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

      // Get the batting and bowling team players for the current inning
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

      // Input striker and non-striker names and verify them
      cout << "Enter striker's name: ";
      clearInputBuffer ();
      getline (cin, Striker);

      cout << "Enter non-striker's name: ";
      getline (cin, Nonstriker);
      checkBatsmen (battingTeamPlayers, Striker, Nonstriker);

      // Input bowler's name and verify it
      for (int j = 1; j <= totalovers; j++)
        {
          clearInputBuffer ();
          cout << "Enter bowlers name: ";
          getline (cin, Bow);
          checkBowler (bowlingTeamPlayers, Bow);

          cout << "Give the score input for the over " << j << endl;
          int sumbscore = 0;

          // Input the score for each ball in the over
          for (int i = ((6) * (j - 1)); i < ((6) * (j)); i++)
            {
              string ballType;
              cin >> ballType;

              Ball *currentBall = nullptr;

              // Handle different types of balls based on user input
              if (inning == 1)
                {
                  // Create a new ball object based on the ball type
                  if (ballType == "N")
                    {
                      currentBall = new NormalBall ();
                      int runs;
                      cout << "Enter the number of runs: ";
                      cin >> runs;
                      currentBall->handleBall (runs, playeri1);
                    }
                  else if (ballType == "w")
                    {
                      // Handle wide ball separately
                      // Decrement i to account for the extra delivery
                      currentBall = new WideBall ();
                      int runs;
                      cout << "Enter the number of runs off the wide ball: ";
                      cin >> runs;
                      currentBall->handleBall (runs, playeri1);
                      --i;
                      continue;
                    }
                  else if (ballType == "Nb")
                    {
                      // Handle no ball separately
                      // Decrement i to a
                      currentBall = new NoBall ();
                      int runs;
                      cout << "Enter the number of runs off the no ball: ";
                      cin >> runs;
                      currentBall->handleBall (runs, playeri1);
                      --i;
                      continue;
                    }
                  else if (ballType == "B")
                    {
                      currentBall = new ByeBall ();
                      currentBall->handleBall (0, playeri1);
                    }
                  else if (ballType == ".")
                    {
                      currentBall = new DotBall ();
                      currentBall->handleBall (0, playeri1);
                    }
                  else if (ballType == "4")
                    {
                      currentBall = new FourBall ();
                      currentBall->handleBall (0, playeri1);
                    }
                  else if (ballType == "6")
                    {
                      currentBall = new SixBall ();
                      currentBall->handleBall (0, playeri1);
                    }
                  else if (ballType == "W")
                    {
                      // Handle wicket ball separately
                      // Enter a new batsman
                      currentBall = new WicketBall ();
                      currentBall->handleBall (0, playeri1);
                      enterNewBatsman (battingTeamPlayers, Striker);
                      cout << "New batsman: " << Striker << endl;
                    }
                  else
                    {
                      cout << "Invalid ball type!" << endl;
                      --i; // Decrement i to account for the invalid input
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
              else
                {
                  // Handle balls for the second inning
                  if (ballType == "N")
                    {
                      currentBall = new NormalBall ();
                      int runs;
                      cout << "Enter the number of runs: ";
                      cin >> runs;
                      currentBall->handleBall (runs, playeri2);
                    }
                  else if (ballType == "w")
                    {
                      currentBall = new WideBall ();
                      int runs;
                      cout << "Enter the number of runs off the wide ball: ";
                      cin >> runs;
                      currentBall->handleBall (runs, playeri2);
                      // Decrement i to account for the extra delivery
                      --i;
                      continue;
                    }
                  else if (ballType == "Nb")
                    {
                      currentBall = new NoBall ();
                      int runs;
                      cout << "Enter the number of runs off the no ball: ";
                      cin >> runs;
                      currentBall->handleBall (runs, playeri2);
                      // Decrement i to a
                      --i;
                      continue;
                    }
                  else if (ballType == "B")
                    {
                      currentBall = new ByeBall ();
                      currentBall->handleBall (0, playeri2);
                    }
                  else if (ballType == ".")
                    {
                      currentBall = new DotBall ();
                      currentBall->handleBall (0, playeri2);
                    }
                  else if (ballType == "4")
                    {
                      currentBall = new FourBall ();
                      currentBall->handleBall (0, playeri2);
                    }
                  else if (ballType == "6")
                    {
                      currentBall = new SixBall ();
                      currentBall->handleBall (0, playeri2);
                    }
                  else if (ballType == "W")
                    {
                      currentBall = new WicketBall ();
                      currentBall->handleBall (0, playeri2);
                      enterNewBatsman (battingTeamPlayers, Striker);
                      cout << "New batsman: " << Striker << endl;
                    }
                  else
                    {
                      // Decrement i to account for the invalid input
                      cout << "Invalid ball type!" << endl;
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
        //Clear the console screen
        system("cls");
    }

  // Clear the console screen
  system ("cls");

  //calling the function for score details of @ 1st innings
  if(match.getTeam1Choice() == 1){
    cout << "Innings 1 Score card : \n"<<endl;
    cout << "Batting  @  "<< team1Name <<" !!\n\n"<<endl;
  }else{
    cout << "Innings 1 Score card : \n"<<endl;
    cout << "Batting  @  "<< team2Name <<" !!\n\n"<<endl; 
  }
  
  displayScoreboard(overs1, playeri1);
  delay(6000);

  // Clear the console screen
  system ("cls");

  //calling the function for score details of @ 2nd Innings
  if(match.getTeam1Choice() == 1){
    cout << "Innings 2 Score card : \n"<<endl;
    cout << "Batting  @  "<< team2Name <<" !!\n\n"<<endl;
  }else{
    cout << "Innings 2 Score card : \n"<<endl;
    cout << "Batting  @  "<< team1Name <<" !!\n\n"<<endl; 
  }
  
  displayScoreboard(overs2, playeri2);
  delay(6000);

  // Clear the console screen
  system ("cls");

  //calling the function for declaring who won the match
  displayMatchResult(match, team1Name, team2Name, playeri1.runs, playeri2.runs);

  return 0;

}
