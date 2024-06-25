#include "SixBall.hpp"

void SixBall::handleBall(int runs, details &player)
{
    player.runs += 6;
    player.sixes++;
    player.bscore += "6";
}
