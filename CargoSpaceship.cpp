#include "CargoSpaceship.h"
#include "Planet.h"
#include <iostream>
using namespace std;

void CargoSpaceship::PrintInfo() const{
    cout << "Spaceship's type: Cargo Spaceship" << endl;
    cout << "Spaceship's current crew number: " << curr_crew << endl;
    cout << "Spaceship's current fuel number: " << curr_fuel << endl;
    cout << "Spaceship's current Planet name: " << currPlanet->getName() << endl;
    cout << "Planet's coordinates: (" << currPlanet->x << ", " << currPlanet->y << ")" << endl;
} // prints stats