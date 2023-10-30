#ifndef CARGOSPACESHIP_H
#define CARGOSPACESHIP_H
#include "Spaceship.h"
#include "Planet.h"


class CargoSpaceship : public Spaceship{
    public:
        CargoSpaceship() : Spaceship(250000, 100){} // fixed stats
        void PrintInfo() const; // virtual function


};
#endif