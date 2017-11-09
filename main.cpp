#include <string>
#include <ctype.h>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Marketplace.h"
#include "split.h"

using namespace std;

bool validDealer(const string& dealerId)
{
  string knownDealers[] = {"DB", "JPM", "UBS", "RBC", "BARX", 
                           "MS", "CITI", "BOFA", "RBS", "HSBC"};
  int l = sizeof(knownDealers) / sizeof(knownDealers[0]);                            
  return find(knownDealers, knownDealers + l, dealerId) != knownDealers + l;
}

int main()
{ 

  cout << toupper('c') << endl;

  cout << "HA" << endl;

  //ifstream infile("orders.txt");

  Marketplace m;
  cout << "> ";
  string s;
  while(getline(cin, s)) {

    // Injest command word by word into a vector<string>.
    vector<string> words; 
    
    
    
    //transform(s.begin(), s.end(), s.begin(), toupper);
    split(s, back_inserter(words)); 

    string dealerId;
    string command;

    try {
      // The first two words are always the dealerId and the command type
      // (command).
      dealerId = words[0]; 
      command  = words[1];
    } catch(const exception& e) {
      cerr << "INVALID_MESSAGE" << endl;
      continue;
    }

    if(!validDealer(dealerId)) {
      cerr << "ERROR: UNKOWN_DEALER" << endl;
      cout << "> ";
      continue;
    }

    // Store the remaining words in a vector<string> called params.
    vector<string> params;
    try {
      params.insert(params.end(), words.begin() + 2, words.end());
    } catch (const length_error& e) {
      cerr << "ERROR: " << e.what() << endl;
    }

    //cout << " > " << s << endl;
    try {
    m.call(dealerId, command, params);
    } catch (const exception& e) {
      cerr << "ERROR: " << e.what() << endl;
    }
    cout << "> ";
  }

  return 0;
}
