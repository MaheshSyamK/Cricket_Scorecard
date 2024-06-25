#include "WicketBall.hpp"
#include <iostream>

void WicketBall::handleBall(int runs, details &player)
{
    player.wicket++;
    player.bscore += "W";
    wicketout();
}

void WicketBall::wicketout()
{
    cout << "\nThe Batsman on the strike was OUT\n";
    cout << "Enter 1 for bowled \n";
    cout << "Enter 2 for caught\n";
    cout << "Enter 3 for stumped\n";
    cout << "Enter 4 for LBW\n";
    cout << "Enter 5 for Run out\n";
    cout << "Enter 6 for Mankad\n";
    cout << "Enter 7 for Retired Hurt\n";
    cout << "Enter 8 for Hit Wicket\n";
    cout << "Choose the number which is given above to enter: ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Batsman was bowled out.\n";
        break;
    case 2:
        cout << "Batsman was caught out.\n";
        break;
    case 3:
        cout << "Batsman was stumped out.\n";
        break;
    case 4:
        cout << "Batsman was LBW out.\n";
        break;
    case 5:
        cout << "Batsman was run out.\n";
        break;
    case 6:
        cout << "Batsman was mankad out.\n";
        break;
    case 7:
        cout << "Batsman retired hurt.\n";
        break;
    case 8:
        cout << "Batsman was hit wicket out.\n";
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
}
