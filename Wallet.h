#pragma once
#include <string>
#include <map>
#include "OrderBookEntry.h"
#include <vector>
#include <iostream>

class Wallet
{
private:
    std::map<std::string,double>currencies;
    
public:
    Wallet();
    void insertCurrency(std::string type,double amount);
    bool removeCurrency(std::string type,double amount);
    bool canFulfillOrder(OrderBookEntry order);
    bool containsCurrency(std::string type,double amount);
    std::string toString();
    void processSale(OrderBookEntry& sale);

};


