// Home Spence Calcultor Final Project

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int displayMenu();

int main(){
    
    
displayMenu();


}
int displayMenu() {
    int choice;

    do {
        cout << " 1. expeses for every month and the most spent every month" << endl;
        cout << " 2. detailed report for any month" << endl;
        cout << " 3. exsit" << endl;
        
        cin >> choice;
        switch (choice) {
            
            case 3 : cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 3);

    return choice;
}

