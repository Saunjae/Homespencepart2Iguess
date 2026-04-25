#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Expenses {
    int month;
    string category;
    double amount;
    double budgeted;
};

// Function prototypes
bool loadExpenses(Expenses*& list, int& count);
void displayAll(const Expenses* list, int count);

int main() {
    Expenses* expenseList = nullptr;
    int totalRecords = 0;

    if (loadExpenses(expenseList, totalRecords)) {
        cout << "Successfully loaded " << totalRecords << " records.\n\n";
        displayAll(expenseList, totalRecords);
    } else {
        cout << "Error: Could not open expenses file.\n";
        cout << "Make sure expenses.txt exists and the file path is correct.\n";
    }

    delete[] expenseList;
    return 0;
}

// Function definitions
bool loadExpenses(Expenses*& list, int& count) {
    // Replace this with your real file path
    ifstream file("expenses.txt");
    if (!file) {
        cout << "Failed to open file.\n";
        cout << "Check that expenses.txt is in the correct location.\n";
        return false;
    }

    count = 0;
    int m;
    string c;
    double a, b;

    // Count how many records are in the file
    while (file >> m >> c >> a >> b) {
        count++;
    }

    if (count == 0) {
        cout << "The file opened, but no valid records were found.\n";
        return false;
    }

    // Allocate dynamic array
    list = new Expenses[count];

    // Reset file to beginning
    file.clear();
    file.seekg(0, ios::beg);

    // Read records into array
    for (int i = 0; i < count; i++) {
        file >> list[i].month >> list[i].category >> list[i].amount >> list[i].budgeted;
    }

    file.close();
    return true;
}

void displayAll(const Expenses* list, int count) {
    cout << left << setw(10) << "Month"
         << setw(15) << "Category"
         << setw(12) << "Spent"
         << setw(12) << "Budgeted" << endl;

    cout << "---------------------------------------------" << endl;

    for (int m = 1; m <= 12; m++) {
        bool monthFound = false;

        for (int i = 0; i < count; i++) {
            if (list[i].month == m) {
                if (!monthFound) {
                    cout << "\n--- Month " << m << " ---" << endl;
                    monthFound = true;
                }

                cout << left << setw(10) << ""
                     << setw(15) << list[i].category
                     << "$" << setw(11) << fixed << setprecision(2) << list[i].amount
                     << "$" << setw(11) << fixed << setprecision(2) << list[i].budgeted
                     << endl;
            }
        }
    }
}
