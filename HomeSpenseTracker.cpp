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
        cout << " 1. Mortgage" << endl;
        cout << " 2. Utilities" << endl;
        cout << " 3. Grocies" << endl;
        cout << " 4. gas" << endl;
        cout << " 5. Internet" << endl;
        cout << " 6. Insurance" << endl;
        cout << " 7. Dining" << endl;
        cout << " 8. Travel" << endl;
        cout << " 9. Helath" << endl;
        cout << " 10. Exsit" << endl;


        cin >> choice;
        switch (choice) {
            
            case 10 : cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 10);

    return choice;
}



struct Travel{
    int 01;
    string category;
    double 200;
    double 250;
};

