#pragma once

#include "orderBookEntry.h"
#include "CSVReader.h"
#include<string>
#include<vector>
class orderBook
{
  public:
  /** construct, reading a csv ile*/
    orderBook(string filename);
  /**return vector of all known products in the dataset*/
    vector<string> getKnownProducts();
  /** return vector of orders according to the sent filters*/
    vector<orderBookEntry> getOrders(orderBookType type, string product, string timestampt);

    /**This returns earliest time in the order book*/
    string getEarliestTime();
    /**This returns the next time after the sent time in the order book*/
    string getNextTime(string timestamp);

    void insertOrder(orderBookEntry& order);
    static double getHighPrice(vector<orderBookEntry>& orders);
    static double getLowPrice(vector<orderBookEntry>& orders);
    static double getChange(vector<orderBookEntry>& orders);

    //Matching function
    vector<orderBookEntry> matchAskstoBids(string product,string timestamp);

  private:
    vector<orderBookEntry> orders;
};