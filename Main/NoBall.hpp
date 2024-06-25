#ifndef NOBALL_HPP
#define NOBALL_HPP

#include "Ball.hpp"

class NoBall : public Ball
{
public:
    void handleBall(int runs, details &player) override;
};

#endif // NOBALL_HPP
