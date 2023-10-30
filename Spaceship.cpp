#include "Spaceship.h"
#include "Planet.h"
#include <iostream>

Spaceship::Spaceship(int fuel, int crew){
    fuel_capacity = fuel;
    crew_capacity = crew;
    curr_crew = crew;
    curr_fuel = fuel;
}

void Spaceship::embark(int x){
    ((curr_crew + x) > crew_capacity) ? (curr_crew = crew_capacity) : (curr_crew += x);
} // sets curr_crew to max if overflow

bool Spaceship::disembark(int x){
    ((curr_crew - x) > 0) ? (curr_crew -= x) : (curr_crew = 0);
    return !(curr_crew == 0);
} // sets curr_crew to 0 if none left

void Spaceship::fueling(int x){
    ((curr_fuel + x) > fuel_capacity) ? (curr_fuel = fuel_capacity) : (curr_fuel += x);
} // sets curr_fuel to max if overflow

bool Spaceship::UseFuel(int num){
    if((curr_fuel - num) < 0){
        return false;
    }
    curr_fuel -= num;
    return true;
}// sets curr_fuel to 0 if empty

Spaceship::~Spaceship(){
    std::cout << "Deleted Ship" << std::endl;
}

void Spaceship::setPlanet(Planet* planet){
    currPlanet = planet;
}

Planet* Spaceship::getPlanet(){
    return currPlanet;
}

int Spaceship::getcrewcap(){
    return crew_capacity;
}

int Spaceship::getfuelcap(){
    return fuel_capacity;
}