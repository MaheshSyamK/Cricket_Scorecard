#ifndef WIDEBALL_HPP
#define WIDEBALL_HPP

#include "Ball.hpp"

class WideBall : public Ball
{
public:
    void handleBall(int runs, details &player) override;
};

#endif // WIDEBALL_HPP
