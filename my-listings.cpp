//
//  my-listings.cpp
//  MarketPlace
//
//  Created by Jamal Hassunizadeh on 10/23/22.
//

#include <iostream>
#include <fstream>
#include "main.h"
#include "my-listings.h"
#include "utility.h"

using namespace std;

void viewMyListings(string email);

void myListings(string email) {
    myListingsHeader();
    viewMyListings(email);
    returnToMain(email);
}

void myListingsHeader() {
    
    cout << "--------------------------------------------" << endl
         << "                 MY LISTINGS                " << endl
         << "--------------------------------------------" << endl;

    cout << "ID     Price     Item" << endl;
}

void viewMyListings(string email) {
    
    string id;
    string price;
    string item;
    string blank;
    int spaceCount;
    string addSpace = "";
    ifstream myListings(email);
    
    //remove password
    getline(myListings, blank);
    while (myListings >> id) {
        spaceCount = 8;
        addSpace = "";
        myListings >> price;
        //skip to next line
        getline(myListings, blank);
        getline(myListings, item);
        
        if (price.size() > 1) {
            spaceCount -= (price.size() - 1);
        }
        
        for (int i = 0; i < spaceCount; i++) {
            
            addSpace += " ";
        }
        cout << id << "   $" << price << addSpace << item << endl;
        
    }
    
    myListings.close();
}
