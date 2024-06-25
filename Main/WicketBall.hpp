#ifndef WICKETBALL_HPP
#define WICKETBALL_HPP

#include "Ball.hpp"
using namespace std;

class WicketBall : public Ball
{
public:
    void handleBall(int runs, details &player) override;

private:
    void wicketout();
};

#endif // WICKETBALL_HPP
