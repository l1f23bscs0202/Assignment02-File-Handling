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
    int choice;
    do {
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            char category[20];
            int amount;
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            }
            else {
                ofstream outFile("expenses.txt", ios::app);
                outFile << category << " " << amount << endl;
                outFile.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (choice == 2) {
            ifstream inFile("expenses.txt");
            if (!inFile) {
                cout << "No expenses yet." << endl;
            }
            else {
                char cat[20];
                int amt;
                int n = 1;
                int totalSpent = 0;
                int maxAmt = -1;
                char largestCat[20] = "";
                bool hasData = false;

                while (inFile >> cat >> amt) {
                    hasData = true;
                    cout << n << ". " << cat << " " << amt << endl;
                    totalSpent += amt;
                    if (amt > maxAmt) {
                        maxAmt = amt;
                        strcpy(largestCat, cat);
                    }
                    n++;
                }
                inFile.close();

                if (!hasData) {
                    cout << "No expenses yet." << endl;
                }
                else {
                    cout << "Total spent: " << totalSpent << endl;
                    cout << "Largest expense: " << largestCat << " (" << maxAmt << ")" << endl;
                }
            }
        }
        else if (choice == 3) {
            char targetCat[20];
            cout << "Enter category: ";
            cin >> targetCat;

            ifstream inFile("expenses.txt");
            if (!inFile) {
                cout << "No expenses found for " << targetCat << endl;
            }
            else {
                char cat[20];
                int amt;
                int catCount = 0;
                int catTotal = 0;

                while (inFile >> cat >> amt) {
                    if (strcmp(cat, targetCat) == 0) {
                        catCount++;
                        catTotal += amt;
                    }
                }
                inFile.close();

                if (catCount == 0) {
                    cout << "No expenses found for " << targetCat << endl;
                }
                else {
                    cout << "Expenses in " << targetCat << ": " << catCount << endl;
                    cout << "Total for " << targetCat << ": " << catTotal << endl;
                }
            }
        }
        else if (choice == 4) {
            ofstream outFile("expenses.txt"); // Opens fresh, wiping previous content
            outFile.close();
            cout << "All expenses cleared." << endl;
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}