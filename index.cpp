#include "Bcrypt.cpp/include/bcrypt.h"
#include <iostream>
using namespace std;
int main(){
    string hashed=bcrypt::generateHash("snjnjhshjskns",11);
    cout<<hashed;
    return 0;
}