#ifndef GUARD_Marketplace_h
#define GUARD_Marketplace_h

#include <string>
#include <map>

#include "Order.h"

class Marketplace {

  private: 
    // DATA
    std::map<int, Order> d_orders;

  public:
    // CREATORS
    Marketplace();

    // MANIPULATORS
    void call(const std::string&              dealerId, 
              const std::string&              functionName, 
              const std::vector<std::string>& params); 

    void post(const std::string& dealerId, 
              const std::string& side,
              const std::string& commodity,
              const int          ammount,
              const double       price);

    void revoke(const std::string& dealerId, const int params);

    void aggress(const std::string&              dealerId, 
                 const std::vector<std::string>& params);

    // ACCESSORS 
    const void list(const std::string&                   dealerId, 
                    const std::vector<std::string>& terms);

    const void check(const std::string& dealerId, const int orderId);
};

#endif
