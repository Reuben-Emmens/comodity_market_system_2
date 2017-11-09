#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_map>

#include "Marketplace.h"

using namespace std;

// Anonymous namespace for functions to help validate commands.
namespace {

// Q: Why is it better to declare these static.
static void validateCommand(const string& command, const unordered_map<string, int>& fmap)
{
  if(fmap.find(command) == fmap.end())
    throw invalid_argument("UNKNOWN_COMMAND " + command);
}

static bool isDouble(const string& s)
{
    try {
        stod(s);
    }
    catch(...) {
        return false;
    }
    return true;
}

static bool isInteger(const string& s)
{
    try {
        stoi(s);
    }
    catch(...) {
        return false;
    }
    return true;
}
static void validatePost(const vector<string>& params) 
{
  vector<string> validCommodities = {"GOLD", "SILV", "PORK", "RICE", "OIL"};
  if( params[0] != "BUY" and params[0] != "SELL" )
    throw invalid_argument("INVALID_SIDE");
  if( find(validCommodities.begin(), validCommodities.end(), params[1]) 
      == validCommodities.end() )
    throw invalid_argument("INVALID_COMMODITY");
  if( !isInteger(params[2]) or stoi(params[2]) < 1 ) 
    throw invalid_argument("INVALID_AMMOUNT");
  if( !isDouble(params[3]) or stod(params[3]) < 0.0 )
    throw invalid_argument("INVALID_PRICE");
}

static void validateRevoke(const vector<string>& params)
{
  if(params.size() == 0)
    throw invalid_argument("NO_ORDER_ID_PROVIDED");
  if(!isInteger(params[0]) or stoi(params[0]) < 0)
    throw invalid_argument("INVALID_ORDER_ID");
}

}


// CREATORS
Marketplace::Marketplace()
{  }

// MANIPULATORS

void Marketplace::call(const string&         dealerId, 
                       const string&         command, 
                       const vector<string>& params)
{
  // Map of command strings to ints to allow use of a switch statement.
  const static unordered_map<string, int> command2int = {
    {"POST",    0},
    {"REVOKE",  1},
    {"AGGRESS", 2},
    {"LIST",    3},
    {"CHECK",   4}

  };

  // Throw an exception if supplied command is not known.
  validateCommand(command, command2int);

  switch(command2int.at(command)) {
      case 0 :  validatePost(params); 
                post(dealerId, params[0], params[1], stoi(params[2]),
                    stod(params[3]));
                break;
      case 1 : validateRevoke(params);
               revoke(dealerId, stoi(params[0]));
               break;
      case 2 : //validateAggress();
               aggress(dealerId, params);
               break;
      case 3 : //validateList(params);
               list(dealerId, params);
               break;
      case 4 : //validateCheck(params);
               check(dealerId, stoi(params[1]));
               break;
  }
}

void Marketplace::post(const string& dealerId, 
		       const string& side,
		       const string& commodity,
		       const int     ammount,
		       const double  price)
{
  // Construct new Order object with post parameters.
  Order o(dealerId, side,  commodity, ammount, price); 

  cout << o << " HAS BEEN POSTED" << endl;

  // Add Order to Marketplace map of orders.
  d_orders.insert(make_pair(o.id(), o));
}

void Marketplace::revoke(const string& dealerId, const int orderId)
{
  // Throw an exception supplied orderId is not in the orders map.
 // validateRevoke(orderId);

  map<int, Order>::const_iterator it = d_orders.find(orderId);
  
  if(it == d_orders.end())
    throw invalid_argument("UNKNOWN_ORDER");
  else if(it->second.dealerId() != dealerId) {
    throw invalid_argument("UNAUTHORIZED");
  } else {
    cout << it->second.id() << " HAS BEEN REVOKED" << endl;
    d_orders.erase(it);
  }
}

void Marketplace::aggress(const std::string&              dealerId, 
                          const std::vector<std::string>& tradeParams)
{ 
  for(vector<string>::size_type i = 0; i != tradeParams.size(); i += 2) {
    // Parse the trade parameters.
    int orderId = stoi(tradeParams[i]);
    int tradeQuantity = stoi(tradeParams[i+1]);

    // Search the orders map for the orderId.
    map<int, Order>::iterator it = d_orders.find(orderId);
    Order& oRef = (it->second);

    if(it == d_orders.end())
      cerr << "UNKNOWN_ORDER" << endl;
    else if(tradeQuantity > oRef.ammount())
      cerr << "INALID_AMMOUNT" << endl;
    else {
      oRef.setAmmount(oRef.ammount() - tradeQuantity);
      cout << (oRef.side() == "SELL" ? " BOUGHT " : " SOLD ") << tradeQuantity 
           << " " << oRef.commodity() << " @ " << oRef.price() 
           << (oRef.side() == "SELL" ? " FROM " : " TO ") << oRef.dealerId() << endl; 
    }
  }
}

// ACCESSORS 

const void Marketplace::list(
                       const std::string&              dealerId, 
                       const std::vector<std::string>& terms = vector<string>())
{ 
  for(map<int, Order>::const_iterator it = d_orders.begin(); it != d_orders.end(); ++it) {  
    bool match = true;
    // For each of the supplied search terms. 
    for(auto i = 0; i != terms.size(); ++i) {
      // If the search term does not appear in the order.
      if(terms[i] != it->second.commodity() and terms[i] != it->second.dealerId())
        // Do not print.
        match = false; 
    }
    if(match) cout << it->second << endl;
  }
}

const void Marketplace::check(const std::string& dealerId, const int orderId)
{ 
  map<int, Order>::const_iterator it = d_orders.find(orderId);

  if(it == d_orders.end())
    cerr << "UNKNOWN_ORDER" << endl;
  else if(it->second.dealerId() != dealerId)
    cout << "UNAUTHORIZED" << endl;
  else if(it->second.ammount() == 0)
    cout << it->second.id() << " HAS BEEN FILLED" << endl;
  else
    cout << it->second << endl;
}

