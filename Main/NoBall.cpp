#include "NoBall.hpp"

void NoBall::handleBall(int runs, details &player)
{
    player.bscore += "Nb ";
    player.NB++;
    player.extraruns += 1 + runs;
    player.runs += 1 + runs;
}
