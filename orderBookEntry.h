#pragma once
//This stops the inclusion of a header files multiples times.

#include<string>
using namespace std;

enum class orderBookType{bid, ask, unknown, asksale, bidsale};


//This is a specification only. Specifying the template. 
//Implemented in orderBookEntry.cpp file
class orderBookEntry
{
  public:
    double price;
    double amount;
    string timestamp; //Another way of constructing is by using {}
    string product; //Another way of constructing is by using {}
    orderBookType orderType;
    string username; //simulation user

    orderBookEntry(double p,double a,string ts,string pro,orderBookType o, string username = "dataset");
    static orderBookType stringToOrderBookType(string s);
    static bool compareByTimestamp(orderBookEntry& e1, orderBookEntry& e2)
    {
      return e1.timestamp < e2.timestamp;
    }
    static bool compareByPriceAsc(orderBookEntry& e1, orderBookEntry& e2)
    {
      return e1.price < e2.price;
    }
    static bool compareByPriceDesc(orderBookEntry& e1, orderBookEntry& e2)
    {
      return e1.price > e2.price;
    }
};