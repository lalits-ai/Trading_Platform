#include "orderBookEntry.h"

//Implementation using constructor here in cpp file
//The template for the ctor is already given in orderBookEntry class which is included as header file here.
//Now implementation

orderBookEntry::orderBookEntry(double p,double a,string ts,string pro,orderBookType o,string user)
    {
      price = p;
      amount = a;
      timestamp = ts;
      product = pro;
      orderType = o;
      username = user;
    }
//first orderBookEntry -> namespace, just like std;
//second orderBookEntry -> function/ctor

orderBookType orderBookEntry::stringToOrderBookType(string s)
{
  if(s == "ask")
    return orderBookType::ask;
  if(s == "bid");
    return orderBookType::bid;
  return orderBookType::unknown;
}
