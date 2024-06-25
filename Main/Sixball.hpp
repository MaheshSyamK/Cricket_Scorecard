#ifndef SIXBALL_HPP
#define SIXBALL_HPP

#include "Ball.hpp"

class SixBall : public Ball
{
public:
    void handleBall(int runs, details &player) override;
};

#endif // SIXBALL_HPP
