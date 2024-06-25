#include "ByeBall.hpp"
using namespace std;

void ByeBall::handleBall(int runs, details &player) {
    player.byes++;
    player.bscore += "B";
    cout << "Bye ball. Enter the number of bye runs: ";
    int byeRuns;
    cin >> byeRuns;
    player.runs += byeRuns;
    player.extraruns += byeRuns;
}

