#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Expenses {
    int month;
    string category;
    double amount;
    double budgeted;
};

// Function prototypes
bool loadExpenses(Expenses *&list, int &count);
void displayAll(const Expenses *list, int count);
int Menu(const Expenses *list, int count);
void highestSpending(const Expenses* list, int count);

int Menu(Expenses *list, int count) {
    int choice;

    cout << "Welcome to the Home Expense Tracker!" << endl;

    do {
        cout << "\n1. See all expenses grouped by month" << endl;
        cout << "2. See the month with the highest spending" << endl;
        cout << "3. See the month with the lowest spending" << endl;
        cout << "4. See each month (ascending order)" << endl;
        cout << "5. See each month (descending order)" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAll(list, count);
            break;
        case 2:
            highestSpending(list, count);
            break;
        case 3:
                lowestSpending(list, count);
        case 6:
            cout << "Have a good day!" << endl;
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return choice;
}

int main() {

    Expenses *expenseList = nullptr;
    int totalRecords = 0;

    if (loadExpenses(expenseList, totalRecords)) {
        cout << "Successfully loaded " << totalRecords << " records.\n\n";
        Menu(expenseList, totalRecords);
    } else {
        cout << "Error: Could not open expenses file.\n";
        cout << "Make sure expenses.txt exists and the file path is correct.\n";
    }
    delete[] expenseList;
    return 0;
}

// Function definitions
bool loadExpenses(Expenses *&list, int &count) {
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
        file >> list[i].month >> list[i].category >> list[i].amount >>
            list[i].budgeted;
    }

    file.close();
    return true;
}

void displayAll(const Expenses *list, int count) {
    cout << left << setw(10) << "Month" << setw(15) << "Category" << setw(12)
         << "Spent" << setw(12) << "Budgeted" << endl;

    cout << "---------------------------------------------" << endl;

    for (int m = 1; m <= 12; m++) {
        bool monthFound = false;

        for (int i = 0; i < count; i++) {
            if (list[i].month == m) {
                if (!monthFound) {
                    cout << "\n--- Month " << m << " ---" << endl;
                    monthFound = true;
                }

                cout << left << setw(10) << "" << setw(15) << list[i].category
                     << "$" << setw(11) << fixed << setprecision(2)
                     << list[i].amount << "$" << setw(11) << fixed
                     << setprecision(2) << list[i].budgeted << endl;
            }
        }
    }
}


void highestSpending(const Expenses* list, int count) {
    double monthTotals[12] = {0};

    for (int i = 0; i < count; i++) {
        int monthIndex = list[i].month - 1;
        monthTotals[monthIndex] += list[i].amount;
    }

    int highestMonth = 0;

    for (int i = 1; i < 12; i++) {
        if (monthTotals[i] > monthTotals[highestMonth]) {
            highestMonth = i;
        }
    }

    cout << "\nMonth with highest spending: Month " << highestMonth + 1 << endl;
    cout << "Total spent: $" << fixed << setprecision(2)
         << monthTotals[highestMonth] << endl;
}

void lowestMonth(const Expenses* list, int count) {
    double monthTotals[12] = {0};

    for (int i = 0; i < count; i++) {
        int monthIndex = list[i].month - 1;
        monthTotals[monthIndex] += list[i].amount;
    }

    int lowestMonth = 0;

    for (int i = 1; i < 12; i++) {
        if (monthTotals[i] < monthTotals[lowestMonth]) {
            lowestMonth = i;
        }
    }

    cout << "\nMonth with lowest spending: Month " << lowestMonth + 1 << endl;
    cout << "Total spent: $" << fixed << setprecision(2)
         << monthTotals[lowestMonth] << endl;
}

