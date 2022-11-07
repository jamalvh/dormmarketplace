//
//  add-listing.cpp
//  MarketPlace
//
//  Created by Jamal Hassunizadeh on 10/23/22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include "add-listing.h"
#include "utility.h"

using namespace std;

void defineListing(vector<string>& idPriceItem, string id, string email);
void updateFiles(string id, string price, string item, string email);

void addListing(string email) {
    string id = "";
    vector<string> idPriceItem = {};
    addListingHeader();
    defineListing(idPriceItem, id, email);
    returnToMain(email);
}

void addListingHeader() {
    
    cout << "--------------------------------------------" << endl
         << "                 ADD LISTING                " << endl
         << "--------------------------------------------" << endl;
}

string assignListingID(string& id) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < 4; i++) {
        char letter = rand() % 25 + 65;
        id += letter;
    }
    return id;
}

void defineListing(vector<string>& idPriceItem, string id, string email) {
    string price;
    string item;
    string temp;
    cout << "Listing ID: " << assignListingID(id) << endl;
    cout << "Price: $";
    cin >> price;
    cout << "Item: ";
    cin >> temp;
    getline(cin, item);
    item = temp + item;
    
    idPriceItem.push_back(id);
    idPriceItem.push_back(price);
    idPriceItem.push_back(item);
    
    updateFiles(id, price, item, email);
}

void updateFiles(string id, string price, string item, string email) {
    
    //open market file
    ofstream uploadMarket("marketListings", ios::app);
    
    uploadMarket << id << " " << price << endl
                 << item << endl;
    uploadMarket.close();
    
    //open personal file
    ofstream uploadPersonal(email, ios::app);
    
    uploadPersonal << endl << id << " " << price << endl
                 << item;
    uploadPersonal.close();
    //ofstream idPriceItem to market and personal
}

