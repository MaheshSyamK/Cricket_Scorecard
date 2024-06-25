#ifndef BYEBALL_HPP
#define BYEBALL_HPP

#include "Ball.hpp"

class ByeBall : public Ball {
  public:
    void handleBall(int runs, details &player) override;
};

#endif // BYEBALL_HPP
