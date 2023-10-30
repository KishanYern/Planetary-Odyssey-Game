#ifndef SPACESHIP_H
#define SPACESHIP_H
#include "Planet.h"
#include <string>

class Spaceship{
    protected:
        int fuel_capacity, crew_capacity; // fixed fuel and crew capacity of the spaceship
        Planet* currPlanet; // pointer to the current planet object
    
    public:
        int curr_fuel, curr_crew; // fuel and crew currently on the planet
        int getfuelcap(void);
        int getcrewcap(void);
        void embark(int); // crew joined the ship
        bool disembark(int); // crew left the ship
        void fueling(int); // adding fuel on the ship
        Spaceship(int, int); // constructor
        bool UseFuel(int); // removing fuel from the ship
        void setPlanet(Planet*); 
        Planet* getPlanet(void);
        virtual ~Spaceship(void); // virtual destructor
        std::string getName(void);
        virtual void PrintInfo(void) const = 0; // will make this class abstract

}; // parent class to 3 classes

#endif