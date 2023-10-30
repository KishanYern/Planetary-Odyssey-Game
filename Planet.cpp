#include "Planet.h"
#include <iostream>
#include <random>
#include <string>

std::string arr[20] = {"Ibreon XI", "Zexade", "Iroria 7X", "Tulia", "Udarvis", "Droutera 4IX", "Igolla W8", "Estrade", "Drehiri", "Cothorix", 
                        "Xelarvis", "Druinov", "Denkerth", "Rion", "Merth", "Leron", "Xochilia VS", "Iketer", "Brolnaistea 2OA", "Nesippe"}; // fixed names

Planet::Planet(int diff, int num){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 255);
    x = dis(gen);
    y = dis(gen);
    hostility = diff;
    name = arr[num];
} // random coordinates for the planet

Planet::~Planet(){
    std::cout << "Destroyed " << name << std::endl;
}


void Planet::PrintInfo() const{
    std::cout << "Planet's name: " << name << std::endl;
    std::cout << "Planet's difficulty: " << hostility << std::endl;
    std::cout << "Planet's coordinates: (" << x << ", " << y << ")" << std::endl;
}

int Planet::GetHostility(){
    return hostility;
}

std::string Planet::getName(){
    return name;
}





