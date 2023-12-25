#pragma once

#include "orderBookEntry.h"
#include<vector>
using namespace std;

class CSVReader
{
  public:
    CSVReader();
    static vector<orderBookEntry> readCSV(string csv);
    static vector<string> tokenise(string csvLine, char separator);
    static orderBookEntry stringsToOBE( string price,
                                        string amount,
                                        string timestamp,
                                        string product, 
                                        orderBookType orderType);

  private:
    static orderBookEntry stringsToOBE(vector<string> strings);

};