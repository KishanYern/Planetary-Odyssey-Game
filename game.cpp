#include <iostream>
#include "Planet.h"
#include "Planet.cpp"
#include "Spaceship.h"
#include "Spaceship.cpp"
#include "CargoSpaceship.h"
#include "CargoSpaceship.cpp"
#include "FuelSpaceship.h"
#include "FuelSpaceship.cpp"
#include "RegularSpaceship.h"
#include "RegularSpaceship.cpp"
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <random>
using namespace std;

const int FuelToDistance = 2; // 2 units of fuel to move 1 unit of distance
const int NumberofPlanets = 20; // constant number of planets in the district
const int MoneyToFuel = 2; // 2 units of money is 1 unit of fuel
int Spaceshipcount = 0; // when at 0, game ends and you lose
int NumberOfPlanetsLeft = 20; // when at 0, game ends and you win

void SwapSpaceship(vector<Spaceship*>& arr, int pos1, int pos2){
    Spaceship* temp;
    temp = arr.at(pos2);
    arr.at(pos2) = arr.at(pos1);
    arr.at(pos1) = temp; // function to switch 
}

void FillPlanets(Planet* arr[]){
    for(int i = 0; i < NumberofPlanets; i++){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 2);
        int x = dis(gen); // generates a random number and assigns planets the random difficulty level.
        switch(x){
            case 0:
                arr[i] = new Planet(1, i);
                break;
            case 1:
                arr[i] = new Planet(2, i);
                break;
            case 2:
                arr[i] = new Planet(3, i);
                break;
        }
    }
}

void AddSpaceShip(vector<Spaceship*>& arr, int& balance){
    
    if(balance < 400000){
        cout << "Insufficient Funds!" << endl;
        return;
    } // if user has less then 400000 coins, they can not buy a ship

    int x;
    cout << "Which SpaceShip would you like to Purchase:" << endl;
    cout << "(1) Regular SpaceShip [75 crew capacity, 390000 fuel capacity]" << endl;
    cout << "(2) Cargo SpaceShip [100 crew capacity, 250000 fuel capacity]" << endl;
    cout << "(3) Fuel SpaceShip [50 crew capacity, 500000 fuel capacity]" << endl;
    cout << "Cost for all is: 400000 coins." << endl;
    cout << "You have: " << balance << endl;
    cout << "Do you want to continue? (yes/no): ";
    string user;
    cin >> user;

    if(user == "no"){
        return;
    }

    cout << "Choose an Option (1/2/3): ";
    cin >> x;

    while(cin.fail() || ((x < 0) || (x > 4))){
        cout << endl;
        cin.clear();
        fflush(stdin); // clears cin buffer
        cout << "Invalid Choice!" << endl;
        cout << "Choose another Option: ";
        cin >> x;
    } // keeps going until user chooses a choice

    Spaceship* temp;

    switch(x){
        case 1:
            temp = new RegularSpaceship();
            break;
        case 2:
            temp = new CargoSpaceship();
            break;
        case 3:
            temp = new FuelSpaceship();
            break;
    }

    arr.push_back(temp); // adds the spaceship to the inventory
    Spaceshipcount++; // increments spaceship count
    balance -= 400000; // takes the cost away
}

int calFuelNeeded(Planet* p1, Planet* p2){
    int magnitude = ((p1->x - p2->x) * (p1->x - p2->x)) + ((p1->y - p2->y) * (p1->y - p2->y)); // subtracts the two vectors pointing to the planets and finds the magnitude of the resultant vector
    return magnitude * FuelToDistance; // converts the distance into the amount of fuel needed
}

void LoadData(vector<Spaceship*>& arr, Planet* parr[], int& balance){
    ifstream inFS("Progress.txt");
    if(!inFS.is_open()){
        cout << "Unable to open Progress.txt" << endl;
        cout << "Check if you accidentally opted for the load game option" << endl;
        exit(0); // check if file is open or not
    }

    inFS >> balance; // get the balance from the previous game
    string data;
    Spaceship* temp;
    int tmpcrew, tmpfuel, tmpccrew;

    while(getline(inFS >> ws, data)){
        stringstream inSS(data); // use string stream to extract the data of the ships
        inSS >> tmpccrew;
        inSS >> tmpcrew;
        inSS >> tmpfuel;
        switch(tmpccrew){
            case 50:
                temp = new FuelSpaceship();
                break;
            case 75:
                temp = new RegularSpaceship();
                break;
            case 100:
                temp = new CargoSpaceship();
                break;
        }
        temp->curr_fuel = tmpfuel;
        temp->curr_crew = tmpcrew;
        temp->setPlanet(parr[NumberOfPlanetsLeft - 1]); // assign a new planet for the spaceship
        NumberOfPlanetsLeft--;
        arr.push_back(temp);
        Spaceshipcount++;   // increment the spaceship count.

    }
    // open file -> >> the balance -> >> each diff spaceship stats
}

void SaveData(vector<Spaceship*>& arr, int& balance){
    ofstream oFS;
    oFS.open("Progress.txt", std::ios::trunc); // overwrite the existing file
    oFS << balance << endl;
    for(int i = 0; i < arr.size(); i++){
        oFS << arr[i]->getcrewcap() << " " << arr[i]->curr_crew << " " << arr[i]->curr_fuel << endl;
    }
    // open file -> >> the balance -> >> each diff spaceship stats
    oFS.close();
}

void SearchPlanet(Planet* arr[], Spaceship** spaceship, vector<Spaceship*>& arr2){
    string option;
    int min = 10000000; // assign an arbituary high value to get overwritten later with the min to see if the user has enough to leave the current planet
    for(int i = NumberofPlanets - 1; i >= 0; i--){
        if(arr[i] != nullptr){
            int fuelneeded = calFuelNeeded((*spaceship)->getPlanet(), arr[i]);

            if(fuelneeded < min){
                min = fuelneeded;
            }

            if((*spaceship)->curr_fuel < fuelneeded){
                continue; // skips over places that the ship cant reach
            }
            cout << "Would you like to travel to "<< arr[i]->getName() << endl;
            cout << "Difficulty Level: " << arr[i]->GetHostility() << endl;
            cout << "(yes/no): ";
            cin >> option;
            if(option == "yes"){
                cout << "Arrived at " << arr[i]->getName() << endl;
                delete (*spaceship)->getPlanet(); // deletes the current planet
                (*spaceship)->setPlanet(arr[i]);
                (*spaceship)->UseFuel(fuelneeded); // uses the fuel needed to change planets
                NumberOfPlanetsLeft--; // decrements the number of planets left to explore
                return;
            }
        }
    }

    if((*spaceship)->curr_fuel < min){
        if((*spaceship)->getPlanet()->eventleft == 0){
            cout << "Spaceship is trapped on the planet and is eventually lost" << endl;
            delete *spaceship;
            *spaceship = nullptr;
            for(int i = 0; i < arr2.size(); i++){
                if(arr2.at(i) == nullptr){
                SwapSpaceship(arr2, i, arr2.size() - 1);
                arr2.pop_back();
                Spaceshipcount--;
                return;
                }
            }
        }
    } // on the condition that the spaceship is trapped on the planet, it is lost and deleted
    
    cout << "Did to move to a different planet" << endl;
}

bool GameOverWin(){
    return NumberOfPlanetsLeft == 0;
} // checks if the game is over and player won

bool GameOverLose(){
    return Spaceshipcount == 0;
} // checks if the game is over and the player lost

void deletearray(vector<Spaceship*>& arr){
    for(int i = 0; i < arr.size(); i++){
        if(arr.at(i) != nullptr){
            delete arr.at(i);
            arr.at(i) = nullptr;
        }
    }
    cout << "Deleted Ships" << endl;
} // deletes the vector

void deletearray(Planet* arr[]){
    for(int i = 0; i < NumberofPlanets; i++){
        if(arr[i] != nullptr){
            delete arr[i];
            arr[i] = nullptr;
        }
    }
    cout << "Deleted Planets" << endl;
} // overloaded the delete array function with a Planet pointer array, deletes the elements in the array

void PrintMenu(){
    cout << "\nMenu:\n";
    cout << "1. View balance\n";
    cout << "2. View ship inventory\n";
    cout << "3. View Planet stats\n";
    cout << "4. Buy new spaceship\n";
    cout << "5. Move to another Planet\n";
    cout << "6. Do Quests on Planet\n";
    cout << "7. Save Game Data \n";
    cout << "8. Quit" << endl;
    cout << "Your Option: ";
} // prints the options

void ShowShipInv(vector<Spaceship*>& arr){
    for(int i = 0; i < arr.size(); i++){
        if(arr.at(i) != nullptr){
            cout << "Ship " << i+1 << "'s info: "<< '\n';
            arr.at(i)->PrintInfo();
			cout << '\n' << endl;
        }
    }
} // uses the PrintInfo() function in the spaceship class to print each spaceship in the spaceship* vector

void DoEvent(Spaceship** ship, int& balance, vector<Spaceship*>& arr){
    srand(time(NULL));
    int x, y, z;
    cout << "\nYou have selected to do a mission on the planet " << (*ship)->getPlanet()->getName() << endl;
    cout << "Hostility Level: " << (*ship)->getPlanet()->GetHostility() << endl;
    switch((*ship)->getPlanet()->eventleft){ // checks the number of events left on the planet
        case 0:
            cout << "No quests left on the planet\n" << endl;
            return;
            break; // if there are no more events left on the planet
        
        case 1: // event 1 is the traitor event, it has different levels of based on the hostility.
                // win/lose leads to gain/loss of money and fuel
            ((*ship)->getPlanet()->eventleft)--;
            switch((*ship)->getPlanet()->GetHostility()){
                case 1:
                    cout << "You have discovered that there is a traitor on your team!" << endl;
                    cout << "They are leaking important data to your enemies" << endl;
                    cout << "They challenge you to a duel for leadership of your ship" << endl;
                    cout << "Traitor: \"Lets pick a random number between 0-100 and who ever gets the closest number to a generated value wins!\"" << endl;
                    cout << "Pick a number: ";
                    cin >> x;
                    y = rand() % 100;
                    z = rand() % 100;
                    if(abs(x-y) > abs(z-y)){
                        cout << "You lost!" << endl;
                        cout << "The traitor has taken 100000 units of fuel and 100000 coins";
                        balance -= 100000;
                        if(!((*ship)->UseFuel(100000))){
                            delete *ship;
                            *ship = nullptr;
                            for(int i = 0; i < arr.size(); i++){
                                if(arr.at(i) == nullptr){
                                    cout << "Out of Fuel. Spaceship is unusable and is lost!" << endl;
                                    SwapSpaceship(arr, i, arr.size() - 1);
                                    arr.pop_back();
                                    Spaceshipcount--;
                                    return;
                                }
                            }
                        } 
                    }
                    else{
                        cout << "You won!" << endl;
                        cout << "The traitor has been identified and killed!\n";
                        cout << "You have also revieved 100000 coins and 100000 units of fuel\n\n";
                        balance += 100000;
                        (*ship)->fueling(100000);
                        return;
                    }
                    break;
                case 2:
                    cout << "You have discovered that there is a traitor on your team!" << endl;
                    cout << "They are leaking important data to your enemies" << endl;
                    cout << "They challenge you to a duel for leadership of your ship" << endl;
                    cout << "Traitor: \"Lets pick a random number between 0-100 and who ever gets the closest number to a generated value wins!\"" << endl;
                    cout << "Pick a number: ";
                    cin >> x;
                    y = rand() % 100;
                    if(abs(x-y) > 30){
                        cout << "You lost!" << endl;
                        cout << "The traitor has taken 200000 units of fuel and 200000 coins";
                        balance -= 200000;
                        if(!((*ship)->UseFuel(200000))){
                            delete *ship;
                            *ship = nullptr;
                            for(int i = 0; i < arr.size(); i++){
                                if(arr.at(i) == nullptr){
                                    cout << "Out of Fuel. Spaceship is unusable and is lost!" << endl;
                                    SwapSpaceship(arr, i, arr.size() - 1);
                                    arr.pop_back();
                                    Spaceshipcount--;
                                    return;
                                }
                            }
                        } 
                    }
                    else{
                        cout << "You won!" << endl;
                        cout << "The traitor has been identified and killed!\n";
                        cout << "You have also revieved 200000 coins and 200000 units of fuel\n\n";
                        balance += 200000;
                        (*ship)->fueling(200000);
                        return;
                    }
                    break;
                case 3:
                    cout << "You have discovered that there is a traitor on your team!" << endl;
                    cout << "They are leaking important data to your enemies" << endl;
                    cout << "They challenge you to a duel for leadership of your ship" << endl;
                    cout << "Traitor: \"Lets pick a random number between 0-100 and who ever gets the closest number to a generated value wins!\"" << endl;
                    cout << "Pick a number: ";
                    cin >> x;
                    y = rand() % 100;
                    if(abs(x-y) > 10){
                        cout << "You lost!" << endl;
                        cout << "The traitor has taken 400000 units of fuel and 400000 coins";
                        balance -= 400000;
                        if(!((*ship)->UseFuel(400000))){
                            delete *ship;
                            *ship = nullptr;
                            for(int i = 0; i < arr.size(); i++){
                                if(arr.at(i) == nullptr){
                                    cout << "Out of Fuel. Spaceship is unusable and is lost!" << endl;
                                    SwapSpaceship(arr, i, arr.size() - 1);
                                    arr.pop_back();
                                    Spaceshipcount--;
                                    return;
                                }
                            }
                        }
                    }
                    else{
                        cout << "You won!" << endl;
                        cout << "The traitor has been identified and killed!\n";
                        cout << "You have also revieved 400000 coins and 400000 units of fuel\n\n";
                        balance += 400000;
                        (*ship)->fueling(400000);
                        return;
                    }
                    break;
            }
            break;

        case 2: // 2nd event is the bandits event, also based off the hostility of the planet
                // event leads to gain/loss in money and crew members
            ((*ship)->getPlanet()->eventleft)--;
            switch((*ship)->getPlanet()->GetHostility()){
                case 1:
                    cout << "A dangerous group of bandits have come by your ship\n";
                    cout << "Your team has killed most of them!\n";
                    cout << "You need to kill their King or else you will lose!\n";
                    cout << "He is hiding behind one of two rocks and you only have one bomb left!\n";
                    cout << "Choose the rock which you think he is hiding behind (1 or 2): ";
                    cin >> x;
                    y = (rand() % 2) + 1;
                    if(x == y){
                        cout << "\n\nYou have killed the King of the bandits!\n";
                        cout << "On his body was 100000 coins and you took his remaining crew of 20 members" << endl;
                        balance += 100000;
                        (*ship)->embark(20);
                    }
                    else{
                        cout << "\n\n You have not killed the King with your last bomb\n";
                        cout << "Since you are out of weapons, the King has taken 100000 coins from you\n";
                        cout << "20 of your crew members have lost faith in you and left you for the bandits" << endl;
                        balance -= 100000;
                        if(!((*ship)->disembark(20))){
                            cout << "Your ship ran out of crew members and you lost the ship" << endl;
                            delete *ship;
                            *ship = nullptr;
                            for(int i = 0; i < arr.size(); i++){
                                if(arr.at(i) == nullptr){
                                    cout << "AAA" << endl;
                                    SwapSpaceship(arr, i, arr.size() - 1);
                                    arr.pop_back();
                                    Spaceshipcount--;
                                    return;
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    cout << "A dangerous group of bandits have come by your ship\n";
                    cout << "Your team has killed most of them!\n";
                    cout << "You need to kill their King or else you will lose!\n";
                    cout << "He is hiding behind one of three rocks and you only have one bomb left!\n";
                    cout << "Choose the rock which you think he is hiding behind (1/2/3): ";
                    cin >> x;
                    y = (rand() % 3) + 1;
                    if(x == y){
                        cout << "\n\nYou have killed the King of the bandits!\n";
                        cout << "On his body was 200000 coins and you took his remaining crew of 30 members" << endl;
                        balance += 200000;
                        (*ship)->embark(30);
                    }
                    else{
                        cout << "\n\n You have not killed the King with your last bomb\n";
                        cout << "Since you are out of weapons, the King has taken 200000 coins from you\n";
                        cout << "30 of your crew members have lost faith in you and left you for the bandits" << endl;
                        balance -= 200000;
                        if(!((*ship)->disembark(30))){
                            cout << "Your ship ran out of crew members and you lost the ship" << endl;
                            delete *ship;
                            *ship = nullptr;
                            for(int i = 0; i < arr.size(); i++){
                                if(arr.at(i) == nullptr){
                                    cout << "AAA" << endl;
                                    SwapSpaceship(arr, i, arr.size() - 1);
                                    arr.pop_back();
                                    Spaceshipcount--;
                                    return;
                                }
                            }
                        }
                    }

                    break;
                case 3:
                    cout << "A dangerous group of bandits have come by your ship\n";
                    cout << "Your team has killed most of them!\n";
                    cout << "You need to kill their King or else you will lose!\n";
                    cout << "He is hiding behind one of five rocks and you only have one bomb left!\n";
                    cout << "Choose the rock which you think he is hiding behind (1-5): ";
                    cin >> x;
                    y = (rand() % 5) + 1;
                    if(x == y){
                        cout << "\n\nYou have killed the King of the bandits!\n";
                        cout << "On his body was 300000 coins and you took his remaining crew of 50 members" << endl;
                        balance += 300000;
                        (*ship)->embark(50);
                    }
                    else{
                        cout << "\n\n You have not killed the King with your last bomb\n";
                        cout << "Since you are out of weapons, the King has taken 300000 coins from you\n";
                        cout << "50 of your crew members have lost faith in you and left you for the bandits" << endl;
                        balance -= 300000;
                        if(!((*ship)->disembark(50))){
                            cout << "Your ship ran out of crew members and you lost the ship" << endl;
                            delete *ship;
                            *ship = nullptr;
                            for(int i = 0; i < arr.size(); i++){
                                if(arr.at(i) == nullptr){
                                    cout << "AAA" << endl;
                                    SwapSpaceship(arr, i, arr.size() - 1);
                                    arr.pop_back();
                                    Spaceshipcount--;
                                    return;
                                }
                            }
                        }
                    }
                    break;
            }
            break;
    }
    
}

int main(){
    Planet* Planetarr[NumberofPlanets]; // array of pointers to planets
    FillPlanets(Planetarr);
    int x; // throwaway var

    vector<Spaceship*> Spacearr; // vector of pointers to the subclasses of spaceships. Uses polymorphism to contain all the different types of spaceships in one array.
    int balance;

    cout << "Welcome to Planetary Odyssey!\n";
    cout << "Would you like to continue the previous game or start a new game? \n (1) Continue\n (2) New Game\n (3) Exit\nYou Choose (1/2/3): ";
    cin >> x;
    
    if(x == 1){
        cout << "Loading old game...\n";
        LoadData(Spacearr, Planetarr, balance);
        cout << "Old game loaded" << endl;
    } // loads old game

    else if(x == 2){
        cout << "Starting new game!" << endl;
        balance = 150000; // starting balance
        Spaceship* temp = new RegularSpaceship(); // starter spaceship
        Spaceshipcount++;
        Spacearr.push_back(temp);
        Spacearr.at(0)->setPlanet(Planetarr[19]); // starting planet
    } // starts new game

    else if(x == 3){
        cout << "Goodbye!" << endl;
        deletearray(Planetarr);
        exit(0);
    } // exits program

    else{
        cout << "Invalid Response" << endl;
        deletearray(Planetarr);
        exit(0);
    } // exits program

    do{
        /*  1. View Balance
            2. view ship inventory
            3. View Planet stats
            4. Buy new spaceship
            5. Move to another Planet
            6. Do Quests on Planet
            7. Save and Quit
            8. quit*/ // in printmenu()

        PrintMenu();
        int user_choice;
        cin >> user_choice;
        cout << "\n";

        if((user_choice <= 0) || (user_choice > 8) || (cin.fail())){
            cout << "Invalid Response\n" << endl;
            cin.clear();
            fflush(stdin); // clears cin buffer
            continue;
        }


        switch(user_choice){
            case 1:
                cout << "Balance: " << balance << endl;
                break; // outputs balance
            case 2:
				ShowShipInv(Spacearr);
                break; // shows ship inv with ShowShipInv() func

            case 3:
                cout << "Which Spaceship's Planet would you like to see? #";
                cin >> x;
                if((x > Spaceshipcount) || (x <= 0)){
                    cout << "Invalid Response!" << endl;
                } // invalid response will start loop again
                else{
                    Spacearr.at(x-1)->getPlanet()->PrintInfo();
                    cout << '\n';
                } // uses the PrintInfo() method in the planet class
                break;

            case 4:
                AddSpaceShip(Spacearr, balance);
                break; // adds spaceship to inventory if conditions in AddSpaceShip() are met

            case 5:
                cout << "Which Spaceship would you like to move? #";
                cin >> x;
                if((x > Spaceshipcount) || (x <= 0)){
                    cout << "Invalid Response!" << endl;
                } // invalid response will start loop again
                else{
                    SearchPlanet(Planetarr, &(Spacearr.at(x - 1)), Spacearr);
                } // searches for planet
                break;

            case 6:
                cout << "Which Spaceship's planet would you like to do the quest on? #";
                cin >> x;
                if((x > Spaceshipcount) || (x <= 0)){
                    cout << "Invalid Response!" << endl;
                } // invalid response will start loop again
                else{
                    DoEvent(&(Spacearr.at(x-1)), balance, Spacearr);
                } // does the events on the planet if conditions are met
                break;
            
            case 7:
                SaveData(Spacearr, balance); 
                cout << "Saved Data!\n";
                deletearray(Planetarr);
                deletearray(Spacearr);
                cout << "Ending Game" << endl;
                exit(0);
                break; // saves data and deletes the arrays

            case 8:
                cout << "Exiting Game!" << endl;
                deletearray(Planetarr);
                deletearray(Spacearr);
                exit(0);
                break; // exits game without saving 
        }

        if(GameOverLose()){
            cout << "You Lost!" << endl;
            break;
        } // checks if game is over

        else if(GameOverWin()){
            cout << "You Won!" << endl;
            break;
        } // checks if game is over

    }while(true);

    deletearray(Planetarr);
    deletearray(Spacearr); // deletes the arrays at the end of game

    return 0;
}
