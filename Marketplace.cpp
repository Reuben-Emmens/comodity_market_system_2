#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

#include "Marketplace.h"
#include "validate.h"

using namespace std;

// CREATORS
Marketplace::Marketplace()
{
  fmap.insert(make_pair( "POST", &Marketplace::post ));
  fmap.insert(make_pair( "LIST", &Marketplace::list ));
  fmap.insert(make_pair( "REVOKE", &Marketplace::revoke ));
  fmap.insert(make_pair( "CHECK", &Marketplace::check ));
  fmap.insert(make_pair( "AGGRESS", &Marketplace::aggress ));
}

// MANIPULATORS
void Marketplace::call(const string&         dealerId, 
                       const string&         command, 
                       const vector<string>& params)
{
  try {
    validateCommand(command)
    funcPtr fp = fmap.at(command);
    return (this->*fp)(dealerId, params);
  } catch (const exception& e) {
    cerr << "ERROR: " << e.what() << endl;
  }
}

void Marketplace::post(const string& dealerId, const vector<string>& params)
{

  validatePostParameters(params);
  
  Order o(dealerId, params[0], params[1], stoi(params[2]), stod(params[3])); 

  cout << o << " HAS BEEN POSTED" << endl;

  orders.insert(make_pair(o.id(), o));
}

void Marketplace::revoke(const std::string&              dealerId, 
                         const std::vector<std::string>& params)
{
  validateRevokeParameters(params);

  int orderId = stoi(params[0]);
  map<int, Order>::const_iterator it = orders.find(orderId);
  
  if(it == orders.end())
    throw invalid_argument("UNKNOWN_ORDER");
  else if(it->second.dealerId() != dealerId) {
    throw invalid_argument("UNKNOWN_ORDER");
  } else {
    cout << it->second.id() << " HAS BEEN REVOKED" << endl;
    orders.erase(it);
  }
}

// ACCESSORS 
void Marketplace::list(const std::string&              dealerId, 
                       const std::vector<std::string>& params = vector<string>())
{ 
  for(map<int, Order>::const_iterator it = orders.begin(); it != orders.end(); ++it) {  
    bool match = true;
    // For each of the supplied search terms. 
    for(auto i = 0; i != params.size(); ++i) {
      // If the search term does not appear in the order.
      if(params[i] != it->second.commodity() and params[i] != it->second.dealerId())
        // Do not print.
        match = false; 
    }
    if(match) cout << it->second << endl;
  }
}

void Marketplace::check(const std::string&              dealerId, 
                        const std::vector<std::string>& params)
{ 
  map<int, Order>::const_iterator it = orders.find(stoi(params[0]));

  if(it == orders.end())
    cerr << "UNKNOWN_ORDER" << endl;
  else if(it->second.dealerId() != dealerId)
    cout << "UNAUTHORIZED" << endl;
  else if(it->second.ammount() == 0)
    cout << it->second.id() << " HAS BEEN FILLED" << endl;
  else
    cout << it->second << endl;
}

void Marketplace::aggress(const std::string&              dealerId, 
                          const std::vector<std::string>& params)
{ 
  for(vector<string>::size_type i = 0; i != params.size(); i += 2) {
    int orderId = stoi(params[i]);
    int tradeQuantity = stoi(params[i+1]);

    map<int, Order>::iterator it = orders.find(orderId);

    Order& oRef = (it->second);

    if(it == orders.end())
      cerr << "UNKNOWN_ORDER" << endl;
    else if(tradeQuantity > oRef.ammount())
      cerr << "INALID_AMMOUNT" << endl;
    else {
      oRef.setAmmount(oRef.ammount() - tradeQuantity);
      cout << (oRef.side() == "SELL" ? "BOUGHT" : "SOLD") << " " << tradeQuantity 
           << " @ " << oRef.price() << " FROM " << oRef.dealerId() << endl; 
    }
  }
}

