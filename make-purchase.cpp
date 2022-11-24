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

void findProduct(string& id, string& price, string& item, string& posterEmail);
void confirmPurchase(string id, string price, string item);
void completePurchase(string id, string price, string item, string& email);
void removeListing(string id, string price, string item, string& email);

void makePurchase(string email) {
    string id = "failed";
    string price = "failed";
    string item = "failed";
    string posterEmail = "";
    makePurchaseHeader();
    findProduct(id, price, item, posterEmail);
    completePurchase(id, price, item, email);
    returnToMain(email);
}

void makePurchaseHeader() {
    cout << "--------------------------------------------" << endl
         << "                  PURCHASE                  " << endl
         << "--------------------------------------------" << endl;
}


void purchase(string& id, string& price, string& item, string& email, string posterEmail) {
    findProduct(id, price, item, posterEmail);
    
    if (price == "failed") {
        return;
    }
    
    completePurchase(id, price, item, email);
}

void findProduct(string& id, string& price, string& item, string& posterEmail) {

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
        getline(marketListings, posterEmail);
        
        listOfMarketListings.push_back(id);
        listOfMarketListings.push_back(price);
        listOfMarketListings.push_back(item);
        listOfMarketListings.push_back(posterEmail);

         
    }
    id = "failed";
    price = "failed";
    item = "failed";
    
    for (int i = 0; i < listOfMarketListings.size() - 3; i++) {
        if (listOfMarketListings.at(i) == idInput) {
            id = listOfMarketListings.at(i);
            price = listOfMarketListings.at(i+1);
            item = listOfMarketListings.at(i+2);
            posterEmail = listOfMarketListings.at(i+3);
            
            i = static_cast<int>(listOfMarketListings.size());
        }
    }

    while (price == "failed") {
        
        cout << "Item not found." << endl;
        cout << "Listing ID: "; 
        cin >> idInput;
        
        for (int i = 0; i < listOfMarketListings.size() - 3; i++) {
            if (listOfMarketListings.at(i) == idInput) {
                id = listOfMarketListings.at(i);
                price = listOfMarketListings.at(i+1);
                item = listOfMarketListings.at(i+2);
                posterEmail = listOfMarketListings.at(i+3);

                
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
    string posterEmailTemp = "";
    string blank = "";
    
    string posterEmail = "";
    
    ifstream downloadMarket("marketListings.txt");
    
    while (downloadMarket >> idTemp) {
        
        downloadMarket >> priceTemp;
        getline(downloadMarket, blank);
        getline(downloadMarket, itemTemp);
        getline(downloadMarket, posterEmailTemp);

        
        if (idTemp != id) {
        
            idPriceItemCopy.push_back(idTemp);
            idPriceItemCopy.push_back(priceTemp);
            idPriceItemCopy.push_back(itemTemp);
            idPriceItemCopy.push_back(posterEmailTemp);


        } else {
            
            //save poster email to update Perosnal File later
            posterEmail = posterEmailTemp;
        }
    }
    
    downloadMarket.close();

    
    ofstream uploadNewMarket("marketListings.txt");
    
    for (int i = 0; i < idPriceItemCopy.size() - 3; i++) {
        
        idTemp = idPriceItemCopy[i];
        i++;
        priceTemp = idPriceItemCopy[i];
        i++;
        itemTemp = idPriceItemCopy[i];
        i++;
        posterEmailTemp = idPriceItemCopy[i];
        
        uploadNewMarket << idTemp << " " << priceTemp << endl
                        << itemTemp << endl << posterEmailTemp << endl;
    }
        
    uploadNewMarket.close();
    
    
    
    //UPDATE PERSONAL
    vector<string> pIdPriceItemCopy = {};
    
    string pIdTemp;
    string pPriceTemp;
    string pItemTemp;
    string pPosterEmailTemp;
    string pBlank;
    string passwordTemp;
    
    ifstream downloadPersonal(posterEmail);
    
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

    //open item-poster's email to edit Personal File
    ofstream uploadNewPersonal(posterEmail);
    
    uploadNewPersonal << passwordTemp << endl << endl;
    
    if (pIdPriceItemCopy.size() > 0) {
        
        for (int j = 0; j < pIdPriceItemCopy.size() - 2; j++) {
            pIdTemp = pIdPriceItemCopy[j];
            j++;
            pPriceTemp = pIdPriceItemCopy[j];
            j++;
            pItemTemp = pIdPriceItemCopy[j];
            
            uploadNewPersonal << pIdTemp << " " << pPriceTemp << endl
                         << pItemTemp << endl;
        }
    }
        
    uploadNewPersonal.close();

}
