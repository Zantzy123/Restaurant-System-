#include <iostream>
#include <string>
using namespace std;

class InventoryItem {
public:
    string name;
    int quantity;

    InventoryItem(string name, int quantity) :
        name(name), quantity(quantity) {}
};