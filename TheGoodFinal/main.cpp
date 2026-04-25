#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <limits>

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
void sortAscending(Expenses * list, int count);
void sortDescending(Expenses * list, int count);
void highestSpending(const Expenses* list, int count);
void lowestSpending(const Expenses* list, int count);
string getMonthName(int monthNumber);

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
    
        // Validate that user entered an integer
        if (!(cin >> choice)) {
            cout << "Numeric input only. Please try again." << endl;
            cin.clear(); // resets the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flushes the bad characters
            choice = 0; // forces the loop to continue
            continue;
        }

        switch (choice) {
        case 1:
            displayAll(list, count);
            break;
        case 2:
            highestSpending(list, count);
            break;
            case 3:
                lowestSpending(list, count);
                break;
        case 4:
            sortAscending(list, count);
            displayAll(list, count);
            break;
        case 5:
             sortDescending(list, count);
             displayAll(list, count);
             break;
        case 6:
            cout << "Have a good day!" << endl;
            break;

        default:
            cout << "Invalid choice. Input a value[1-6]\n";
        }

    } while (choice != 6);

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

void displayAll(const Expenses* list, int count) {
    // Top-level Header
    cout << left << setw(15) << "Month" 
         << setw(15) << "Category" 
         << setw(12) << "Spent" 
         << setw(12) << "Budgeted" << endl;
         
    cout << "---------------------------------------------------------" << endl;

    // Linear Traversal: We loop through the array exactly as it is ordered in memory.
    // This allows the Selection Sort results to actually be visible.
    for (int i = 0; i < count; i++) {
        // We still use getMonthName so the integer '1' prints as 'January'
        cout << left << setw(15) << getMonthName(list[i].month)
             << setw(15) << list[i].category
             << "$" << setw(11) << fixed << setprecision(2) << list[i].amount 
             << "$" << setw(11) << fixed << setprecision(2) << list[i].budgeted 
             << endl;
    }
    
    cout << "---------------------------------------------------------" << endl;
    cout << "End of Report (" << count << " records displayed)" << endl;
}
string getMonthName(int monthNumber) {
    // Add "November" to the array so there are 12 indices
    const string months[] = { 
        "January", "February", "March", "April", "May", "June", 
        "July", "August", "September", "October", "November", "December" 
    };

    if (monthNumber >= 1 && monthNumber <= 12) {
        return months[monthNumber - 1]; // Index 0 is January, Index 11 is December
    }
    return "Unknown";
}

void sortAscending(Expenses * list, int count){

    for (int i = 0; i < count - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (list[j].amount < list[minIndex].amount) {
                minIndex = j;
            }
        }
        // Swap the entire struct
        Expenses temp = list[i];
        list[i] = list[minIndex];
        list[minIndex] = temp;

    }
}

void sortDescending(Expenses* list, int count) {
    for (int i = 0; i < count - 1; i++) {
        int maxIndex = i;
        for (int j = i + 1; j < count; j++) {
            if (list[j].amount > list[maxIndex].amount) {
                maxIndex = j;
            }
        }
        Expenses temp = list[i];
        list[i] = list[maxIndex];
        list[maxIndex] = temp;
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

void lowestSpending(const Expenses* list, int count) {
    double monthTotals[12] = {0};

    // Add up totals for each month
    for (int i = 0; i < count; i++) {
        int monthIndex = list[i].month - 1;
        monthTotals[monthIndex] += list[i].amount;
    }
    int lowestIndex = -1; 
    for (int i = 0; i < 12; i++) {

        
    if (monthTotals[i] > 0) { // Only count months with recorded expenses
        if (lowestIndex == -1 || monthTotals[i] < monthTotals[lowestIndex]) {
            lowestIndex = i;
        }
    }
}

    cout << "\nMonth with lowest spending: Month " << lowestIndex + 1 << endl;
    cout << "Total spent: $" << fixed << setprecision(2)
         << monthTotals[lowestIndex] << endl;
}


