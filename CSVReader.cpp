#include "CSVReader.h"
#include<iostream>
#include<fstream>

CSVReader::CSVReader(){}
vector<orderBookEntry> CSVReader::readCSV(string csv)
{
  vector<orderBookEntry> Entries;

  ifstream csvFile(csv,ios::in);
  string line;
  if(csvFile.is_open())
  {
    while(getline(csvFile,line))
    {
      try
      {
        orderBookEntry obe = stringsToOBE(tokenise(line,','));
        Entries.push_back(obe);
      }
      catch(const exception& e)
      {
        cout<<"CSVReader::readCSV - Bad data"<<endl;
      }
    }//end of while
  }
  cout<<"CSVReader::readCSV read : "<<Entries.size()<<" entries"<<endl;
  return Entries;
}
vector<string> CSVReader::tokenise(string csvLine, char separator)
{
  vector<string> tokens;
  signed int start,end; //They can be pos and neg because when using string, and if any char is not found in the string the function returns negative number.
  string token;
  start = csvLine.find_first_not_of(separator,0);
  do
  {
    end = csvLine.find_first_of(separator,start);
    if(start == csvLine.length() || start == end) break;
    if(end >= 0)
    {
      token = csvLine.substr(start,end-start);
    }
    else
    {
      token = csvLine.substr(start,csvLine.length() - start);
    }
    tokens.push_back(token);
    start = end + 1;
  } while (end != string::npos);
  
  return tokens;
}
orderBookEntry CSVReader::stringsToOBE(vector<string> tokens)
{
  double price,amount;

  if(tokens.size() != 5) //Exception Handling
  {
    cout<<"Bad Line"<<endl;
    throw exception();
  }
  try
  {
    price = stod(tokens.at(3)); //crashes if any non double or floating point occurs in the line
    amount = stod(tokens.at(4)); //use exception handling to handle the error
  }
  catch(const exception& e)
  {
    throw;
  }
  

  orderBookEntry obe(price,amount,tokens[0],tokens[1],orderBookEntry::stringToOrderBookType(tokens[2]));
  return obe;
}

orderBookEntry CSVReader::stringsToOBE( string priceString,
                                        string amountString,
                                        string timestamp,
                                        string product, 
                                        orderBookType orderType)
{
  double price,amount;
   try
  {
    price = stod(priceString); //crashes if any non double or floating point occurs in the line
    amount = stod(amountString); //use exception handling to handle the error
  }
  catch(const exception& e)
  {
    cout<<"CSVReader::stringsToOBE - Bad float"<<priceString<<endl;
    cout<<"CSVReader::stringsToOBE - Bad float"<<amountString<<endl;
    throw;
  }
  orderBookEntry obe(price,amount,timestamp,product,orderType);
  return obe;
}