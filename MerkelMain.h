#pragma once //This allows to include header files only once.
//Should be included in header files only.

#include<vector>
#include "orderBookEntry.h"
#include "orderBook.h"
#include "Wallet.h"
using namespace std;

class MerkelMain
{
  public:
    MerkelMain();
    void init();
  private:
    void printMenu();
    void printHelp();
    void printExchangeStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption();

    string currentTime;
    orderBook OrderBook{"20200317.csv"};
    
    Wallet wallet;
};