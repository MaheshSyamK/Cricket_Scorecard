#include "score_value.hpp"
#include <iostream>
using namespace std;

void score_value() {
    cout << "*** REMEMBER ALL BALL INPUT OPTIONS ***\n\n";
    cout << "!!! ENTER INPUTS ONLY FROM THE GIVEN LIST BELOW !!!\n\n";
    cout << "To record a dot ball, enter <.>.\n";
    cout << "For 1 run, enter <N> followed by 1.\n";
    cout << "For 2 runs, enter <N> followed by 2.\n";
    cout << "For 3 runs, enter <N> followed by 3.\n";
    cout << "For 4 runs (boundary), enter <4>.\n";
    cout << "For 6 runs (boundary), enter <6>.\n";
    cout << "To record a wicket, enter <W>.\n";
    cout << "To record a wide, enter <w>.\n";
    cout << "To record a no ball, enter <Nb>.\n";
    cout << "To record byes, enter <B>.\n";
    cout << "!!! Incorrect inputs will prompt for re-entry !!!\n";
}
