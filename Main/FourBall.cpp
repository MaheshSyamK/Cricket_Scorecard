#include "FourBall.hpp"

void FourBall::handleBall(int runs, details &player)
{
    player.runs += 4;
    player.fours++;
    player.bscore += "4";
}
