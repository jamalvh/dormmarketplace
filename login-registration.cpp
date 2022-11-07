//
//  login-registration.cpp
//  Login-And-Registration-System
//
//  Created by Jamal Hassunizadeh on 10/23/22.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "login-registration.h"

using namespace std;

void start(string& email) {
    char regOrLog = 'z';
    
    cout << "> Register 'R' or Login 'L': ";
    cin >> regOrLog;
    
    while (regOrLog != 'R' && regOrLog != 'L') {
        cout << "# Invalid input, try again: ";
        cin >> regOrLog;
    }
    
    if (regOrLog == 'R') {
        registerEmail(email);
    } else {
        login(email);
    }
}

void registerEmail(string& email) {

    cout << "> Register your email: ";
    cin >> email;

    if (isRegistered(email)) {
        cout << "# Already registered." << endl;
        login(email);
        return;
    }
    
    ofstream foutRE("registeredEmails", ios::app);
    foutRE << email << endl;
    
    foutRE.close();
    
    setPassword(email);
    
}

    
bool isRegistered(string email) {
    
    ifstream finRE("registeredEmails");
    string emailChecker;
    bool emailFound = false;
    
    while (finRE >> emailChecker) {
        
        if (emailChecker == email)
        {
            emailFound = true;
        }
        
    }
    
    finRE.close();

    return emailFound;
}

void setPassword(string& email) {
    string password;
    cout << "> Create a password: ";
    cin >> password;

    ofstream foutUserFileCreate(email, ios::app);
    foutUserFileCreate << password << endl;
    foutUserFileCreate.close();
    
    cout << "# Account registered." << endl;
    login(email);
}

void login(string& email) {
    
    string password;
    string passwordInput;
    
    cout << "> Login with your email: ";
    cin >> email;
    
    if (!isRegistered(email)) {
        cout << "# The email you entered is unregistered." << endl;
        registerEmail(email);
    }
    
    ifstream userFileLogin(email);
    userFileLogin >> password;
    
    while (passwordInput != password) {
        cout << "> Password: ";
        cin >> passwordInput;
    }
    
    cout << "# Logged in." << endl << endl;
    
    userFileLogin.close();
}
