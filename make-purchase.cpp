//
//  make-purchase.cpp
//  MarketPlace
//
//  Created by Jamal Hassunizadeh on 10/23/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "make-purchase.h"
#include "utility.h"

using namespace std;

void findProduct(string& id, string& price, string& item);
void confirmPurchase(string id, string price, string item);
void completePurchase(string id, string price, string item, string& email);
void removeListing(string id, string price, string item, string& email);

void makePurchase(string email) {
    string id = "failed";
    string price = "failed";
    string item = "failed";
    makePurchaseHeader();
    findProduct(id, price, item);
    completePurchase(id, price, item, email);
    returnToMain(email);
}

void makePurchaseHeader() {
    cout << "--------------------------------------------" << endl
         << "                  PURCHASE                  " << endl
         << "--------------------------------------------" << endl;
}


void purchase(string& id, string& price, string& item, string& email) {
    findProduct(id, price, item);
    
    if (price == "failed") {
        return;
    }
    
    completePurchase(id, price, item, email);
}

void findProduct(string& id, string& price, string& item) {

    string idInput;
    cout << "Listing ID: ";
    cin >> idInput;

    string blank;
    
    vector<string> listOfMarketListings = {};
    
    //bool foundProduct = false;
    
    ifstream marketListings("marketListings.txt");
    
    while (marketListings >> id) {
        marketListings >> price;
        getline(marketListings, blank);
        getline(marketListings, item);
        
        listOfMarketListings.push_back(id);
        listOfMarketListings.push_back(price);
        listOfMarketListings.push_back(item);
         
    }
    id = "failed";
    price = "failed";
    item = "failed";
    for (int i = 0; i < listOfMarketListings.size(); i++) {
        if (listOfMarketListings.at(i) == idInput) {
            id = listOfMarketListings.at(i);
            price = listOfMarketListings.at(i+1);
            item = listOfMarketListings.at(i+2);
            
            i = static_cast<int>(listOfMarketListings.size());
        }
    }
    //NEVER FAILS!
    while (price == "failed") {
        
        cout << "Item not found." << endl;
        cout << "Listing ID: "; 
        cin >> idInput;
        
        for (int i = 0; i < listOfMarketListings.size(); i++) {
            if (listOfMarketListings.at(i) == idInput) {
                id = listOfMarketListings.at(i);
                price = listOfMarketListings.at(i+1);
                item = listOfMarketListings.at(i+2);
                
                i = static_cast<int>(listOfMarketListings.size());
            }
        }
        return;
    }
    
    cout << ". . ." << endl;
    cout << id << "   $" << price << "    " << item << endl << endl;
}

void completePurchase(string id, string price, string item, string& email) {
    char choice;
    cout << "# Complete Purchase: 'K'" << endl
         << "# Cancel: 'C'" << endl
         << "> ";
    cin >> choice;
    choice = toupper(choice);
    
    while (choice != 'K' && choice != 'C') {
        cout << "Invalid input, try again." << endl
             << "> ";
        cin >> choice;
        choice = toupper(choice);
    }
    
    if (choice == 'C') {
        cout << "Cancelled." << endl;
        return;
    } else {
        removeListing(id, price, item, email);
        cout << "Item Purchased!" << endl;

        //UPDATE FILES
    }

}

void removeListing(string id, string price, string item, string& email) {
    
    //UPDATE MARKET
    vector<string> idPriceItemCopy = {};
    
    string idTemp = "";
    string priceTemp = "";
    string itemTemp = "";
    string blank = "";
    
    ifstream downloadMarket("marketListings.txt");
    
    while (downloadMarket >> idTemp) {
        
        downloadMarket >> priceTemp;
        getline(downloadMarket, blank);
        getline(downloadMarket, itemTemp);
        
        if (idTemp != id) {
        
            idPriceItemCopy.push_back(idTemp);
            idPriceItemCopy.push_back(priceTemp);
            idPriceItemCopy.push_back(itemTemp);

        }
    }
    
    cout << endl;
    
    for (int k = 0; k < idPriceItemCopy.size(); k++) {
        
        cout << idPriceItemCopy[k];
        if (k % 2 == 0) {
            cout << ", ";
        } else {
            cout << " ";
        }
        
    }
    
    cout << endl;
    
    downloadMarket.close();

    
    ofstream uploadNewMarket("marketListings.txt");
    
    for (int i = 0; i < idPriceItemCopy.size(); i++) {
        
        idTemp = idPriceItemCopy[i];
        i++;
        priceTemp = idPriceItemCopy[i];
        i++;
        itemTemp = idPriceItemCopy[i];
        
        uploadNewMarket << idTemp << " " << priceTemp << endl
                     << itemTemp << endl;
    }
        
    uploadNewMarket.close();
    
    
    
    //UPDATE PERSONAL
    vector<string> pIdPriceItemCopy = {};
    
    string pIdTemp;
    string pPriceTemp;
    string pItemTemp;
    string pBlank;
    string passwordTemp;
    
    ifstream downloadPersonal("marketListings.txt");
    
    downloadPersonal >> passwordTemp;
    getline(downloadPersonal, pBlank);
    
    while (downloadPersonal >> pIdTemp >> pPriceTemp) {
    
        getline(downloadPersonal, pBlank);
        getline(downloadPersonal, pItemTemp);
        
        if (pIdTemp != id) {
        
            pIdPriceItemCopy.push_back(pIdTemp);
            pIdPriceItemCopy.push_back(pPriceTemp);
            pIdPriceItemCopy.push_back(pItemTemp);

        }
    }
    
    downloadPersonal.close();
}
