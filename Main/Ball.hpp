#ifndef BALL_HPP
#define BALL_HPP

#include "Details.hpp"

#include <iostream>
#include <string>

class Ball {
  public:
    virtual void handleBall(int runs, details &player) = 0;
};

#endif // BALL_HPP
