#include <iostream>
#include <string>
using namespace std;

class Customer {
public:
    int id;
    string name;
    string phone;

    Customer(int id, string name, string phone) :
        id(id), name(name), phone(phone) {}
};