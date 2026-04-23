
#include <iostream>
#include <string>
#include <memory>
#include <fstream> 
#include <iomanip>

using namespace std;


struct Expenses{

 int month;
 string category;
 double amount;
 double budgeted;

};

//function prototypes
bool loadExpenses(Expenses* &list, int &count);
void displayAll(const Expenses* list, int count);
void sortTotals(double* totals, int size);




int main(){

 Expenses* expenseList = nullptr;
    int totalRecords = 0;

    if (loadExpenses(expenseList, totalRecords)) {
        cout << "Successfully loaded " << totalRecords << " records." << endl;
        
    } else {
        cout << "Error: Could not open expenses.txt" << std::endl;
    }

    return 0;



}

//function definitons

bool loadExpenses(Expenses* &list, int &count){
    
   // Opening expenses txt 
   ifstream file("expenses.txt");
    if (!file) return false;

    int m; string c; double a, b;
    count = 0;

    //Count records
    while (file >> m >> c >> a >> b) {
        count++;
    }

    //  Allocate Dynamic Memory
    list = new Expenses[count];

    // Reset File Stream
    file.clear();
    file.seekg(0);

    // Pass 2: Read data into the array
    for (int i = 0; i < count; i++) {
        file >> list[i].month >> list[i].category >> list[i].amount >> list[i].budgeted;
    }

    file.close();
    return true;
}

void displayAll(const Expenses* list, int count) {
    cout << left << setw(10) << "Month" << setw(15) << "Category" 
         << setw(10) << "Spent" << "Budgeted" << endl;
    
    for (int m = 1; m <= 12; m++) {
     
        bool monthFound = false;
        for (int i = 0; i < count; i++) {
            if (list[i].month == m) {
                if (!monthFound) {
                    cout << "--- Month " << m << " ---" << endl;
                    monthFound = true;
                }
                cout << setw(10) << "" << setw(15) << list[i].category 
                     << "$" << setw(9) << list[i].amount << "$" << list[i].budgeted << endl;
            }
        }
    }
}
