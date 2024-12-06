#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "MenuItem.cpp"

class Order {
public:
    int orderID;
    string customerName;
    vector<MenuItem> items;
    double totalAmount;
    
    Order(int id, string customerName) :
        orderID(id), customerName(customerName), totalAmount(0) {}
};