/*
 * Name       : Akmal Sattar
 * Reg No     : L1F23BSCS0202
 * Assignment : 02 - File Handling
 * Question   : Q1 - Stock Report (Debugging)
 */

 // FIX 1: <fstream> header file was missing, required for ifstream and ofstream
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream inFile("stock.txt");
    // FIX 2: Check condition was inverted (!inFile should be checked to detect if file failed to open)
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }

    // FIX 3: Opened reorder.txt with ios::app mode so that existing old lines are kept intact
    ofstream reorder("reorder.txt", ios::app);

    char code[10];
    int qty, count = 0, low = 0;
    double price;
    // FIX 4: total must be a double because price has decimals, otherwise decimal values are truncated
    double total = 0.0;

    // FIX 5: Skipped the header line of stock.txt before entering the loop
    inFile.ignore(100, '\n');

    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
            reorder << code << " " << qty << endl; // FIX 6: Added endl to write each low stock item on a new line
            low++;
        }
    }
    inFile.close();
    reorder.close();

    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}
