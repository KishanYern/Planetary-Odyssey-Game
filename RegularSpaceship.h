#ifndef REGULARSPACESHIP_H
#define REGULARSPACESHIP_H
#include "Spaceship.h"
#include "Planet.h"

class RegularSpaceship : public Spaceship{
    public:
        RegularSpaceship();
        void PrintInfo() const; // virtual function
        

};

#endif