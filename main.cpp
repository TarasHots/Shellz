#include <iostream>
#include "src/index.h"

using namespace std;
using namespace Battleships;

int main() {
    auto playerField1 = std::make_unique<Battleships::Field>();
    playerField1->placeShip("place h9 4 v");
    playerField1->placeShip("place a9 1 v");
    playerField1->display();

    return 0;
}
