#include <iostream>
#include <string>
using namespace std;

class Reservation {
public:
    int tableID;
    string customerName;
    string time;

    Reservation(int tableID, string customerName, string time) :
        tableID(tableID), customerName(customerName), time(time) {}
};