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
    char filename[100];
    cout << "Enter the file name: ";
    cin.getline(filename, 100);

    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Could not open " << filename << "!" << endl;
        return 1;
    }

    int n;
    inFile >> n;
    inFile.ignore(100, '\n');

    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 1;
    }

    ofstream scholarship("scholarship.txt");

    char name[30];
    double cgpa;
    int studentsCount = 0;
    double totalCgpa = 0.0;
    int eligibleCount = 0;
    double maxCgpa = -1.0;
    char topStudent[30] = "";

    for (int i = 0; i < n; i++) {
        if (!inFile.getline(name, 30, ',')) {
            cout << "Warning: only " << studentsCount << " of " << n << " records found." << endl;
            break;
        }
        if (!(inFile >> cgpa)) {
            cout << "Warning: only " << studentsCount << " of " << n << " records found." << endl;
            break;
        }
        inFile.ignore(100, '\n');

        studentsCount++;
        totalCgpa += cgpa;

        cout << "[" << name << "] CGPA: " << cgpa << endl;

        if (cgpa >= 3.50) {
            eligibleCount++;
            scholarship << name << "," << cgpa << endl;
        }

        if (cgpa > maxCgpa) {
            maxCgpa = cgpa;
            strcpy(topStudent, name);
        }
    }
    inFile.close();
    scholarship.close();

    if (studentsCount == 0) {
        cout << "No students found!" << endl;
        return 0;
    }

    cout << "Students: " << studentsCount << endl;
    cout << "Average CGPA: " << (totalCgpa / studentsCount) << endl;
    cout << "Eligible for scholarship: " << eligibleCount << endl;
    cout << "Top student: " << topStudent << " (" << maxCgpa << ")" << endl;

    return 0;
}