#ifndef FUELSPACESHIP_H
#define FUELSPACESHIP_H

#include "Spaceship.h"
#include "Planet.h"

class FuelSpaceship : public Spaceship{
    public:
        FuelSpaceship();
        void PrintInfo() const; // virtual function
    
};

#endif