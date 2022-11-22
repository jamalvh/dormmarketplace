//
//  market.cpp
//  MarketPlace
//
//  Created by Jamal Hassunizadeh on 10/23/22.
//

#include <iostream>
#include <fstream>
#include "market.h"
#include "utility.h"

using namespace std;

void market(string email) {
    marketHeader();
    marketListings();
    returnToMain(email);
}

void marketHeader() {
    
    cout << "--------------------------------------------" << endl
         << "                   MARKET                   " << endl
         << "--------------------------------------------" << endl;

    cout << "ID     Price     Item" << endl;

}

void marketListings() {
    
    string id;
    string price;
    string item;
    string blank;
    int spaceCount;
    string addSpace = "";
    ifstream marketListings("marketListings.txt");
    
    while (marketListings >> id) {
        spaceCount = 8;
        addSpace = "";
        marketListings >> price;
        getline(marketListings, blank);
        getline(marketListings, item);
        
        if (price.size() > 1) {
            spaceCount -= (price.size() - 1);
        }
        
        for (int i = 0; i < spaceCount; i++) {
            
            addSpace += " ";
        }
        cout << id << "   $" << price << addSpace << item << endl;
        
    }
    
    marketListings.close();
}


