#ifndef NORMALBALL_HPP
#define NORMALBALL_HPP
using namespace std;

#include "Ball.hpp"

class NormalBall : public Ball
{
public:
    void handleBall(int runs, details &player) override;
};

#endif // NORMALBALL_HPP
