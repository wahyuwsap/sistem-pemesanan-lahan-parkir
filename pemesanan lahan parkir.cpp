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


int main() {
    int choice;
    initializeParkingLots();
    char loggedInUser[50] = "";

    while (true) {
        clearScreen();
        displayTitle();
        if (strlen(loggedInUser) == 0) {
            
            displayMainMenu();
            cout << "Pilih opsi: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    clearScreen();
                    registerUser();
                    waitForEnter();
                    break;
                case 2:
                    clearScreen();
                    if (loginUser(loggedInUser)) {
                        cout << "Selamat datang, " << loggedInUser << "!" << endl;
                    }
                    waitForEnter();
                    break;
                case 3:
                    cout << "Terima kasih telah menggunakan sistem pemesanan lahan parkir!" << endl;
                    return 0;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                    waitForEnter();
            }
        } else {
            
            displayUserMenu();
            cout << "Pilih opsi: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    clearScreen();
                    searchParkingLot();
                    waitForEnter();
                    break;
                case 2:
                    clearScreen();
                    displayAvailableParkingLots();
                    waitForEnter();
                    break;
                case 3:
                    clearScreen();
                    bookParkingSlot(loggedInUser);
                    handleBookingQueue();
                    waitForEnter();
                    break;
                case 4:
                    clearScreen();
                    strcpy(loggedInUser, ""); 
                    cout << "Logout berhasil!" << endl;
                    waitForEnter();
                    break;
                case 5:
                    clearScreen();
                    cout << "Kembali ke menu sebelumnya." << endl;
                    waitForEnter();
                    break;
                default:
                    clearScreen();
                    cout << "Pilihan tidak valid!" << endl;
                    waitForEnter();
            }
        }
    }

    return 0;
}


void displayTitle() {
    cout << "===============================" << endl;
    cout << "  Sistem Pemesanan Lahan Parkir " << endl;
    cout << "===============================" << endl;
}


void displayMainMenu() {
    cout << "Menu Awal:" << endl;
    cout << "1. Registrasi" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
    cout << "===============================" << endl;
}


void displayUserMenu() {
    cout << "Menu:" << endl;
    cout << "1. Cari Lahan Parkir" << endl;
    cout << "2. Lihat Lahan Parkir yang Tersedia" << endl;
    cout << "3. Pesan Slot Parkir" << endl;
    cout << "4. Logout" << endl;
    cout << "===============================" << endl;
}


int findUserIndex(const char* username) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}


void registerUser() {
    char username[50], password[50];
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    if (findUserIndex(username) != -1) {
        cout << "Username sudah terdaftar!" << endl;
        return;
    }

    users.push_back(User(username, password));
    cout << "Registrasi berhasil!" << endl;
    history.push("Registrasi user: " + string(username));
}

bool loginUser(char* loggedInUser) {
    char username[50], password[50];
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    int userIndex = findUserIndex(username);
    if (userIndex != -1 && strcmp(users[userIndex].password, password) == 0) {
        strcpy(loggedInUser, username);
        cout << "Login berhasil!" << endl;
        return true;
    } else {
        cout << "Username atau password salah!" << endl;
        return false;
    }
}

void searchParkingLot() {
    string location;
    cout << "Masukkan lokasi lahan parkir yang dicari: ";
    cin.ignore();
    getline(cin, location);

    bool found = false; 
    cout << "Daftar Lahan Parkir yang Tersedia di " << location << ":" << endl;

    for (size_t i = 0; i < parkingLots.size(); ++i) {
        if (parkingLots[i].location == location) {
            cout << "- " << parkingLots[i].location << " - " << parkingLots[i].time << " - Rp" << parkingLots[i].price << endl;
            found = true; 
        }
    }
    if (!found) {
        cout << "Tidak ditemukan" << endl; 
    }

    cout << endl << endl;
    cout << "Tekan 5 untuk kembali" << endl; 
}

void displayAvailableParkingLots() {
    cout << "Daftar Lahan Parkir yang Tersedia:" << endl;
    for (size_t i = 0; i < parkingLots.size(); ++i) {
        cout << i + 1 << ". " << parkingLots[i].location << " - " << parkingLots[i].time << " - Rp" << parkingLots[i].price << endl;
        cout << "   Ketersediaan slot: ";
        for (size_t j = 0; j < parkingLots[i].slots.size(); ++j) {
            if (parkingLots[i].slots[j]) {
                cout << "X ";  
            } else {
                cout << (j + 1) << " ";  
            }
        }
        cout << endl;
    }
    cout << endl << endl;
    cout << "Tekan 5 untuk kembali" << endl; 
}

void bookParkingSlot(const char* loggedInUser) {
    int parkingLotIndex, slotNumber;
    displayAvailableParkingLots();
    cout << "Pilih nomor lahan parkir: ";
    cin >> parkingLotIndex;
    --parkingLotIndex;  

    if (parkingLotIndex < 0 || parkingLotIndex >= parkingLots.size()) {
        cout << "Pilihan lahan parkir tidak valid!" << endl;
        return;
    }

    cout << "Pilih nomor slot (1-" << parkingLots[parkingLotIndex].slots.size() << "): ";
    cin >> slotNumber;
    --slotNumber;  

    if (slotNumber < 0 || slotNumber >= parkingLots[parkingLotIndex].slots.size()) {
        cout << "Pilihan slot tidak valid!" << endl;
        return;
    }

    if (parkingLots[parkingLotIndex].slots[slotNumber]) {
        cout << "Slot sudah dipesan!" << endl;
        return;
    }

    parkingLots[parkingLotIndex].slots[slotNumber] = true;
    clearScreen();
    cout << "Pemesanan berhasil! Berikut adalah tiket parkir Anda:" << endl;
    cout << "Lokasi: " << parkingLots[parkingLotIndex].location << endl;
    cout << "Waktu: " << parkingLots[parkingLotIndex].time << endl;
    cout << "Slot: " << slotNumber + 1 << endl;
    cout << "Harga: Rp" << parkingLots[parkingLotIndex].price << endl;
    cout << "Barcode: ||||||| | || || | ||" << endl;  

    history.push("Pemesanan slot oleh: " + string(loggedInUser));
    bookingQueue.push("Pemesanan slot oleh: " + string(loggedInUser));
}

void handleBookingQueue() {
    while (!bookingQueue.empty()) {
        cout << "Memproses: " << bookingQueue.front() << endl;
        bookingQueue.pop();
    }
}

