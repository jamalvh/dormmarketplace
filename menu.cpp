//
//  menu.cpp
//  MarketPlace
//
//  Created by Jamal Hassunizadeh on 10/23/22.
//

#include <iostream>
#include <fstream>
#include "menu.h"
#include "market.h"
#include "my-listings.h"
#include "add-listing.h"
#include "make-purchase.h"
#include "quit.h"

using namespace std;

void menu(string email) {
    
    char menuChoice;
    
    menuHeader();
    
    cout << "> ";
    cin  >> menuChoice;
    menuChoice = toupper(menuChoice);
    
    //checks if valid choice
    while (menuChoice != 'M' && menuChoice != 'L' && menuChoice != 'A'
           && menuChoice != 'P' && menuChoice != 'X') {
        
        cout << "Invalid input, try again." << endl
             << "> ";
        cin >> menuChoice;
        menuChoice = toupper(menuChoice);
        
    }
    
    useMenuChoice(menuChoice, email);

}

void menuHeader() {
    
    cout << "--------------------------------------------" << endl
         << "            BUY/SELL MARKETPLACE            " << endl
         << "--------------------------------------------" << endl;
    cout << "# View Market        'M'" << endl
         << "# View My Listings   'L'" << endl
         << "# Add Listing        'A'" << endl
         << "# Make Purchase      'P'" << endl
         << "# Exit               'X'" << endl;
}


void useMenuChoice(char choice, string email) {
    
    if (choice == 'M') {
        market(email);
    } else if (choice == 'L') {
        myListings(email);
    } else if (choice == 'A') {
        addListing(email);
    } else if (choice == 'P') {
        makePurchase(email);
    } else {
        quit();
    }
    
}
