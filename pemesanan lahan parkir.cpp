#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;


class User {
public:
    char username[50];
    char password[50];

    User(const char* uname, const char* pwd) {
        strcpy(username, uname);
        strcpy(password, pwd);
    }
};


class ParkingLot {
public:
    string location;
    string time;
    double price;
    vector<bool> slots;

    ParkingLot(const string& loc, const string& t, double p, int numSlots) 
        : location(loc), time(t), price(p), slots(numSlots, false) {}
};

vector<ParkingLot> parkingLots; 

void initializeParkingLots() {
    
    parkingLots.push_back(ParkingLot("Lokasi 1", "08:00 - 18:00", 5000.0, 10));
    parkingLots.push_back(ParkingLot("Lokasi 2", "08:00 - 18:00", 6000.0, 15));
    parkingLots.push_back(ParkingLot("Lokasi 3", "08:00 - 18:00", 7000.0, 20));
    parkingLots.push_back(ParkingLot("Lokasi 4", "08:00 - 18:00", 8000.0, 25));
    
}

vector<User> users;            
stack<string> history;         
queue<string> bookingQueue;    


int findUserIndex(const char* username);
void registerUser();
bool loginUser(char* loggedInUser);
void searchParkingLot();
void displayAvailableParkingLots();
void bookParkingSlot(const char* loggedInUser);
void divideAndConquerSearch(int start, int end, const string& location);
void handleBookingQueue();
void displayTitle();
void displayMainMenu();
void displayUserMenu();
void clearScreen();
void waitForEnter();




