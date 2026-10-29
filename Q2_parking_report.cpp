/*
 * Name       : Akmal Sattar
 * Reg No     : L1F23BSCS0202
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ifstream inFile("parking.txt");
    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;
    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(100, '\n');
    inFile.ignore(100, '\n'); 

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;

    ofstream receipts("receipts.txt");
    receipts << "Receipts for " << d << "/" << m << "/" << y << endl;

    char plate[15], type;
    int inH, inM, outH, outM;
    char colon;

    int vehicles = 0;
    int cars = 0;
    int bikes = 0;
    int totalCollected = 0;
    int maxMinutes = -1;
    char longestPlate[15] = "";
    int longH = 0, longM = 0;

    while (inFile >> plate >> type >> inH >> colon >> inM >> outH >> colon >> outM) {
        vehicles++;
        int inMinutes = inH * 60 + inM;
        int outMinutes = outH * 60 + outM;
        int parkedMinutes = outMinutes - inMinutes;

        int hoursCharged = (parkedMinutes + 59) / 60;
        if (hoursCharged == 0) hoursCharged = 1;

        int fee = 0;
        if (type == 'C' || type == 'c') {
            cars++;
            fee = hoursCharged * 100;
            cout << plate << " Car ";
        }
        else {
            bikes++;
            fee = hoursCharged * 40;
            cout << plate << " Bike ";
        }

        int hPart = parkedMinutes / 60;
        int mPart = parkedMinutes % 60;

        cout << hPart << " h " << mPart << " min Fee: " << fee << endl;
        receipts << plate << " " << fee << endl;

        totalCollected += fee;

        if (parkedMinutes > maxMinutes) {
            maxMinutes = parkedMinutes;
            strcpy(longestPlate, plate);
            longH = hPart;
            longM = mPart;
        }
    }
    inFile.close();
    receipts.close();

    if (vehicles == 0) {
        cout << "First Parking report for " << d << "/" << m << "/" << y << ", then No vehicles found!" << endl; // Note: Adjust as per prompt formatting if needed
        return 0;
    }

    cout << "Vehicles: " << vehicles << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << totalCollected << endl;
    cout << "Longest stay: " << longestPlate << " (" << longH << " h " << longM << " min)" << endl;

    return 0;
}