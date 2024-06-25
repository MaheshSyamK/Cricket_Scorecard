#include "WideBall.hpp"

void WideBall::handleBall(int runs, details &player)
{
    player.bscore += "w ";
    player.wide++;
    player.extraruns += 1 + runs;
    player.runs += 1 + runs;
}
