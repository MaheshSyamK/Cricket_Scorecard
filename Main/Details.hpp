#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <string>
using namespace std;

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

// Define instances of the structure for player details
extern details playeri1;
extern details playeri2;

#endif
