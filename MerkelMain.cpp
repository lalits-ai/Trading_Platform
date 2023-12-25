#include "MerkelMain.h"
#include "orderBookEntry.h"
#include "CSVReader.h"
#include<iostream>
#include<vector>
using namespace std;

MerkelMain::MerkelMain(){} //Ctor creates the object
/**Call this to start the object*/
void MerkelMain::init() //init makes the object start operating
{
  //loadOrderBook();
  wallet.insertCurrency("BTC",10);
  currentTime = OrderBook.getEarliestTime();
  while(true)
  {
    printMenu();
    processUserOption();
  }
}
void MerkelMain::printMenu()
{
    // 1 print help
    cout << "1. Print help" << endl;
    // 2 print exchange stats
    cout << "2. Print exchange stats" << endl;
    // 3 Make offer
    cout << "3. Make an offer" << endl;
    // 4 Make bid
    cout << "4. Make a bid" << endl;
    // 5 print wallet
    cout<<"5. Print wallet"<<endl;
    // 6 next time step or continue
    cout << "6. Continue" << endl;

    cout << "===========" << endl;
    cout<<"\n\nCurrent Time: "<<currentTime<<endl;
}
void MerkelMain::printHelp()
{
  cout<<"Help - Choose one from the options"<<endl;
  cout<<"and follow the on screen instructions"<<endl;
}
void MerkelMain::printExchangeStats()
{

  for(string const& p : OrderBook.getKnownProducts())
  {
    cout<<"product: "<<p<<endl;
    vector<orderBookEntry> askEntries = OrderBook.getOrders(orderBookType::ask, p, currentTime);
    // vector<orderBookEntry> bidEntries = OrderBook.getOrders(orderBookType::bid,p,currentTime);
    cout<<"Asks seen: "<<askEntries.size()<<endl;
    // cout<<"Bids seen: "<<bidEntries.size()<<endl;
    cout<<"Max ask: "<<orderBook::getHighPrice(askEntries)<<endl;
    cout<<"Min ask: "<<orderBook::getLowPrice(askEntries)<<endl;
  }
}
void MerkelMain::enterAsk()
{
  cout<<"Make an ask - enter amount: product, price, amount, eg: ETH/BTC,200,0.5 "<<endl;
  string input;
  getline(cin,input);

  vector<string> tokens = CSVReader::tokenise(input,',');
  if(tokens.size() != 3)
    cout<<"MerkelMain::enterAsk - Bad input"<<endl;
  else
  {
    try
    {
     orderBookEntry obe = CSVReader::stringsToOBE(tokens[1],tokens[2],currentTime,tokens[0],orderBookType::ask);
     obe.username = "simuser";
     if(wallet.canFulfillOrder(obe))
     {
      cout<<"Wallet looks good."<<endl;
      OrderBook.insertOrder(obe);
     }
     else
      cout<<"Wallet has insufficient funds."<<endl;
    }
    catch(const exception& e)
    {
      cout<<"MerkelMain::enterAsk - Bad input!"<<endl;
    }
  }
}
void MerkelMain::enterBid()
{
  cout<<"Make a bid - enter amount: product, price, amount, eg: ETH/BTC,200,0.5 "<<endl;
  string input;
  getline(cin,input);

  vector<string> tokens = CSVReader::tokenise(input,',');
  if(tokens.size() != 3)
    cout<<"MerkelMain::enterBid - Bad input"<<endl;
  else
  {
    try
    {
     orderBookEntry obe = CSVReader::stringsToOBE(tokens[1],tokens[2],currentTime,tokens[0],orderBookType::bid);
     obe.username = "simuser";
     if(wallet.canFulfillOrder(obe))
     {
      cout<<"Wallet looks good."<<endl;
      OrderBook.insertOrder(obe);
     }
     else
      cout<<"Wallet has insufficient funds."<<endl;
    }
    catch(const exception& e)
    {
      cout<<"MerkelMain::enterBid - Bad input!"<<endl;
    }
  }
}
void MerkelMain::printWallet()
{
  cout<<wallet.toString()<<endl;
}
void MerkelMain::gotoNextTimeframe()
{
  cout<<"Going to next time frame. "<<endl;
  for(string p : OrderBook.getKnownProducts())
  {
    cout<<"matching "<<p<<endl;
    vector<orderBookEntry> sales = OrderBook.matchAskstoBids(p,currentTime);
    cout<<"Sales: "<<sales.size()<<endl;
    for(orderBookEntry& sale : sales)
    {
      cout<<"Sale price: "<<sale.price<<" amount "<<sale.amount<<endl;
      if(sale.username == "simuser")
      {
        //update the wallet
        wallet.processSale(sale);
      }
    }
  }
  currentTime = OrderBook.getNextTime(currentTime);
}
int MerkelMain::getUserOption()
{
    //User input
    int userOption = 0;
    string line;
    cout<<"Enter your option"<<endl;
    getline(cin,line);
    try
    {
      userOption = stoi(line);
    }
    catch(const exception& e)
    {
      cout<<"MerkelMain::getUserOption - Bad input!"<<endl;
    }
    

    cout << "You chose " << userOption << endl;
    return userOption;
}
void MerkelMain::processUserOption()
{
  int userOption = getUserOption();
  switch(userOption)
  {
    case 1: printHelp();
            break;
    case 2: printExchangeStats();
            break;
    case 3: enterAsk();
            break;
    case 4: enterBid();
            break;
    case 5: printWallet();
            break;
    case 6: gotoNextTimeframe();
            break;
    default: cout<<"Chosen option should be between 1-6"<<endl;
              break;
  }
}