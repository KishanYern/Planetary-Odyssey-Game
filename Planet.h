#ifndef PLANET_H
#define PLANET_H
#include <ctime>
#include <string>

class Planet{
    private:
        int hostility; // hostility level of the planet
        std::string name; // name of the planet
    
    public:
        int eventleft = 2; // keeps track of events left on the planet
        Planet(int diff, int num); // constructor
        int x, y; // coordinates of the planet
        int GetHostility();
        std::string getName();
        ~Planet(); // destructor of planet
        void PrintInfo() const; // print info of planet

};

#endif
