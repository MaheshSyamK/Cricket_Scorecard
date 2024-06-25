#ifndef DOTBALL_HPP
#define DOTBALL_HPP

#include "Ball.hpp"

class DotBall : public Ball
{
public:
    void handleBall(int runs, details &player) override;
};

#endif // DOTBALL_HPP
