//
//  utility.cpp
//  MarketPlace
//
//  Created by Jamal Hassunizadeh on 10/24/22.
//

#include <iostream>
#include "utility.h"
#include "menu.h"

using namespace std;

void returnToMain(string email) {
    char choice;
    
    cout << endl
         << "# Return to Main: 'Q'" << endl
         << "> ";
    cin >> choice;
    
    choice = toupper(choice);
    while (choice != 'Q') {
        
        cout << "Invalid input, try again." << endl
             << "> ";
        cin >> choice;
        choice = toupper(choice);
    }
    
    menu(email);
}
