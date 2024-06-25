#ifndef FOURBALL_HPP
#define FOURBALL_HPP

#include "Ball.hpp"

class FourBall : public Ball
{
public:
    void handleBall(int runs, details &player) override;
};

#endif // FOURBALL_HPP
