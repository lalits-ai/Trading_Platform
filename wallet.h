#pragma once
#include<string>
#include<map>
#include "orderBookEntry.h"
using namespace std;

class Wallet
{
  public:
    Wallet();
    /** insert currency to the wallet*/
    void insertCurrency(string type, double amount);
    /** Check if wallet contains money*/
    bool containsCurrency(string type,double amount);
    /** Generate a string representation*/
    string toString();
    /** removing curreny from wallet*/
    bool removeCurrency(string type, double amount);
    /** Checks if the wallet can cop with this ask or bid*/
    bool canFulfillOrder(orderBookEntry order);
    /** update the contents of the wallet
     * assumes the order was made by the owner of the wallet
    */
    void processSale(orderBookEntry& sale);

  private:
    map<string,double> currencies;
};