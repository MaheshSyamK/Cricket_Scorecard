#include "CricketPlayer.hpp"

// Constructor that initializes a CricketPlayer object with a given name
CricketPlayer::CricketPlayer(const string &n) : name(n), hasPlayed(false) {}

// Getter function that returns the name of the player
string CricketPlayer::getName() const
{
    return name;
}

// Getter function that returns whether the player has played or not
bool CricketPlayer::getHasPlayed() const
{
    return hasPlayed;
}

// Setter function to update whether the player has played or not
void CricketPlayer::setHasPlayed(bool played)
{
    hasPlayed = played;
}
