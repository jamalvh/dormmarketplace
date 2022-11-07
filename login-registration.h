//
//  login-registration.h
//  Login-And-Registration-System
//
//  Created by Jamal Hassunizadeh on 10/23/22.
//

#ifndef login_registration_h
#define login_registration_h

using namespace std;

void registerEmail(string& email);
bool isRegistered(string email);
void setPassword(string& email);

void login(string& email);

#endif /* login_registration_h */
