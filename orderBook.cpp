#include "orderBook.h"
#include<map>
#include<algorithm>
#include<iostream>


orderBook::orderBook(string filename)
{
  orders = CSVReader::readCSV(filename);
}
vector<string> orderBook::getKnownProducts()
{
  vector<string> products;
  //mapping data - structure , stores in key value pairs
  //string = key, bool = value
  //used to uniquely identify the all types of products and assign it to true value
  map<string,bool> prodMap;
  for(orderBookEntry& e : orders)
  {
    prodMap[e.product] = true;
  }
  //now flatten the map to a vecotr of strings
  for(auto const& e : prodMap)
  {
    products.push_back(e.first);
  }
  
  return products;
}
vector<orderBookEntry> orderBook::getOrders(orderBookType type, string product, string timestamp)
{
  vector<orderBookEntry> orders_sub;
  for(orderBookEntry& e : orders)
  {
    if(e.orderType == type && e.product == product && e.timestamp == timestamp)
    {
      orders_sub.push_back(e);
    }
  }
  return orders_sub;
}
double orderBook::getHighPrice(vector<orderBookEntry>& orders)
{
  double highest = orders[0].price;
  for(orderBookEntry& e : orders)
  {
    if(e.price > highest)
      highest = e.price;
  }
  return highest;
}
double orderBook::getLowPrice(vector<orderBookEntry>& orders)
{
  double lowest = orders[0].price;
  for(orderBookEntry& e : orders)
  {
    if(e.price < lowest)
      lowest = e.price;
  }
  return lowest;
}

string orderBook::getEarliestTime()
{
  return orders[0].timestamp;
}
string orderBook::getNextTime(string timestamp)
{
  string next_timestamp = "";
  for(orderBookEntry& e : orders)
  {
    if(e.timestamp > timestamp)
    {
      next_timestamp = e.timestamp;
      break;
    }
  }
  if(next_timestamp == "")
  {
    next_timestamp = orders[0].timestamp;
  }
  return next_timestamp;
}

void orderBook::insertOrder(orderBookEntry& order)
{
  orders.push_back(order);
  sort(orders.begin(),orders.end(),orderBookEntry::compareByTimestamp);
}

vector<orderBookEntry> orderBook::matchAskstoBids(string product, string timestamp)
{
  vector<orderBookEntry> asks = getOrders(orderBookType::ask,product,timestamp);
  vector<orderBookEntry> bids = getOrders(orderBookType::bid,product,timestamp);

  vector<orderBookEntry> sales;

  // I put in a little check to ensure we have bids and asks
    // to process.
    if (asks.size() == 0 || bids.size() == 0)
    {
        cout << " OrderBook::matchAsksToBids no bids or asks" << endl;
        return sales;
    }

  //sort asks lowest first
  sort(asks.begin(),asks.end(),orderBookEntry::compareByPriceAsc);

  //sort bids hightest first
  sort(bids.begin(),bids.end(),orderBookEntry::compareByPriceDesc);

  //for ask in asks:
  for(orderBookEntry& ask : asks)
  {
    //for bid in bids:
    for(orderBookEntry& bid : bids)
    {
      if(bid.price >= ask.price)
      {
        orderBookEntry sale{ask.price,0,timestamp,
        product,
        orderBookType::asksale};

        if(bid.username == "simuser")
        {
          sale.username = "simuser";
          sale.orderType = orderBookType::bidsale;
        }
        if(ask.username == "simuser")
        {
          sale.username = "simuser";
          sale.orderType = orderBookType::asksale;
        }
         
        if(bid.amount == ask.amount)
        {
          sale.amount = ask.amount;
          sales.push_back(sale);
          bid.amount = 0;
          break;
        }
        if(bid.amount > ask.amount)
        {
          sale.amount = ask.amount;
          sales.push_back(sale);
          bid.amount = bid.amount - ask.amount;
          break;
        }
        if(bid.amount < ask.amount && bid.amount > 0)
        {
          sale.amount = bid.amount;
          sales.push_back(sale);
          ask.amount = ask.amount - bid.amount;
          bid.amount = 0;
          continue;
        }

      }
    }
  }
  return sales;
}

