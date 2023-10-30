#include "RegularSpaceship.h"
#include "Planet.h"
#include <iostream>
using namespace std;

RegularSpaceship::RegularSpaceship() : Spaceship(375000, 75){}; // fixed max values

void RegularSpaceship::PrintInfo() const{
    cout << "Spaceship's type: Regular Spaceship" << endl;
    cout << "Spaceship's current crew number: " << curr_crew << endl;
    cout << "Spaceship's current fuel number: " << curr_fuel << endl;
    cout << "Spaceship's current Planet name: " << currPlanet->getName() << endl;
    cout << "Planet's coordinates: (" << currPlanet->x << ", " << currPlanet->y << ")" << endl;
} // prints stats