#include "MerkelMain.h"
#include <iostream>
#include "CSVReader.h"
#include "OrderBook.h"

MerkelMain::MerkelMain(){}
void MerkelMain::init(){

    
    int input;
    currentTime=orderBook.getEarliestTime();
    Wallet.insertCurrency("BTC",10);
    while (true)
    {
        printMenu();

        input=getUserOption();
        processUserOption(input);
    }    
}
void MerkelMain::printHelp(){
    std::cout << "Help- choose options from the menu" << std::endl;
}
void MerkelMain::printMarkerStats(){

    for (std::string const& p:orderBook.getKnownProducts())
    {
        std::cout<<"Products: "<<p<<std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,p,currentTime);
        std::cout<<"Ask seen: "<<entries.size()<<std::endl;
        std::cout<<"Max Ask: "<<OrderBook::getHighPrice(entries)<<std::endl;
        std::cout<<"Min Ask: "<<OrderBook::getLowPrice(entries)<<std::endl;
    }
    std::cout<<"========================================="<<std::endl;

}
void MerkelMain::enterAsk(){
    std::cout << "make an asks - enter the amounth: product,price, amounth, eg ETH/BTC,200,0.5 " << std::endl;
    std::string input;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::getline(std::cin,input);
    std::vector<std::string>tokens=CSVReader::tokenise(input,',');
    if (tokens.size() !=3)
    {
        std::cout<<"Bad input! "<<input<<std::endl;
    }else{
        try{
        OrderBookEntry obe= CSVReader::stringsToOBE(tokens[1],tokens[2],currentTime,tokens[0],OrderBookType::ask);
        obe.username="simuser";
        if (Wallet.canFulfillOrder(obe))
        {
            std::cout<<"wallet looks good"<<std::endl;
            orderBook.insertOrder(obe);

            std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(tokens[0], currentTime);
            for (OrderBookEntry& sale : sales) {
                if (sale.username == "simuser") {
                    Wallet.processSale(sale);
                }
            }
        }else{
            std::cout<<"wallet has insufficient funds"<<std::endl;
        }
        
        
        }catch(const std::exception & e){
            std::cout<<"Merkelmain::enterAsk input"<<std::endl;
        }    
    }
    

    std::cout<<"you typed: "<<input<<std::endl;
}
void MerkelMain::enterBid(){
    
    std::cout << "make an bid - enter the amounth: product,price, amounth, eg ETH/BTC,200,0.5 " << std::endl;
    std::string input;
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::getline(std::cin,input);
    std::vector<std::string>tokens=CSVReader::tokenise(input,',');
    if (tokens.size() !=3)
    {
        std::cout<<"Bad input! "<<input<<std::endl;
    }else{
        try{
        OrderBookEntry obe= CSVReader::stringsToOBE(tokens[1],tokens[2],currentTime,tokens[0],OrderBookType::bid);
        obe.username="simuser";
        if (Wallet.canFulfillOrder(obe))
        {
            std::cout<<"wallet looks good"<<std::endl;
            orderBook.insertOrder(obe);

            std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(tokens[0], currentTime);
            for (OrderBookEntry& sale : sales) {
                if (sale.username == "simuser") {
                    Wallet.processSale(sale);
                }
            }


        }else{
            std::cout<<"wallet has insufficient funds"<<std::endl;
        }
        
        
        }catch(const std::exception & e){
            std::cout<<"Merkelmain::enterBid input"<<std::endl;
        }    
    }
    
    std::cout<<"you typed: "<<input<<std::endl;
}
void MerkelMain::printWallet(){
    std::cout << "your wallet is: " << std::endl;
    std::cout<<Wallet.toString()<<std::endl;
}
void MerkelMain::gotoNexTimeframe(){
    std::cout << "Goint to next time frame: " << std::endl;
    std::vector<OrderBookEntry> sales=orderBook.matchAsksToBids("ETH/BTC",currentTime);
    std::cout<<"Sales: "<<sales.size()<<std::endl;
    for (OrderBookEntry& sale : sales)
    {
        std::cout<<"sale price: "<<sale.price<<" amount "<<sale.amount<<std::endl;
        if (sale.username=="simuser")
        {
            Wallet.processSale(sale);
        }
        
    }
    
    currentTime=orderBook.getNextTime(currentTime);
}

void MerkelMain::printMenu(){
    std::cout << "1: print help" << std::endl;
    std::cout << "2: print exchance stats" << std::endl;
    std::cout << "3: place an ask " << std::endl;
    std::cout << "4: place a bid " << std::endl;
    std::cout << "5: print wallet " << std::endl;
    std::cout << "6: average price "<<std::endl;
    std::cout << "7: continue " << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout<<"current time is "<<currentTime<<std::endl;
}

void MerkelMain::findaverage(){
    for (std::string const& p : orderBook.getKnownProducts()) {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        if (!entries.empty()) {
            double meanPrice = OrderBook::getMeanPrice(entries);
            std::cout << "Average Ask Price for " << p << ": " << meanPrice << std::endl;
        } else {
            std::cout << "No orders found for " << p << " at this time." << std::endl;
        }
    }
    std::cout << "=========================================" << std::endl;
}

int MerkelMain::getUserOption(){
    int userOption=0;
    std::string line;
    std::cout << "==============================" << std::endl;
    std::cout << "Type in 1-7: ";
    std::getline(std::cin,line);
    try{
        userOption = std::stoi(line);
    }catch(const std::exception& e){
    
    }
    //std::cin >> userOption;
    return userOption;
}
void MerkelMain::processUserOption(int userOption){

    if (userOption == 1){
        printHelp();
    }
    else if (userOption == 2){
        printMarkerStats();
        
    }else if (userOption == 3){
        enterAsk();
    }
    else if (userOption == 4){
        enterBid();
    }
    else if (userOption == 5){
        printWallet();
    }
    else if(userOption == 6){
        findaverage();
    }
    else if (userOption == 7){
        gotoNexTimeframe();
    }
}