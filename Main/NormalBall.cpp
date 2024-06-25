#include "NormalBall.hpp"

void NormalBall::handleBall(int runs, details &player)
{
    player.runs += runs;
    player.bscore += to_string(runs);
}
