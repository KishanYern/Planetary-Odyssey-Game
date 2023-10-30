#include "FuelSpaceship.h"
#include "Planet.h"
#include <iostream>
using namespace std;

FuelSpaceship::FuelSpaceship() : Spaceship(500000, 50){} // fixed stats

void FuelSpaceship::PrintInfo() const{
    cout << "Spaceship's type: Fuel Spaceship" << endl;
    cout << "Spaceship's current crew number: " << curr_crew << endl;
    cout << "Spaceship's current fuel number: " << curr_fuel << endl;
    cout << "Spaceship's current Planet name: " << currPlanet->getName() << endl;
    cout << "Planet's coordinates: (" << currPlanet->x << ", " << currPlanet->y << ")" << endl;
} // print stats