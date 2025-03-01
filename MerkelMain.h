#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include <limits>
#include "Wallet.h"

class MerkelMain{

    public:
        MerkelMain();
        void init();
    private:
        void printMenu();
        void printHelp();
        void printMarkerStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNexTimeframe();
        int getUserOption();
        void findaverage();
        void processUserOption(int userOption);

        std::string currentTime;
        OrderBook orderBook{"20200317.csv"};
        Wallet Wallet;
       

};