#include <string>
#include <iostream>

#include "Order.h"

using namespace std;

// IS THIS THE RIGHT PLACE FOR THIS?
static int id_counter = 1;

Order::Order(const  string& dealerId,
             const  string& side,
             const  string& commodity,
                    int     ammount,
                    double  price):
d_id(id_counter++),
d_dealerId(dealerId),
d_side(side),
d_commodity(commodity),
d_ammount(ammount),
d_price(price)
{ }

// MANIPULATORS
void Order::setAmmount(int ammount)
{
  d_ammount = ammount;
}

// ACCESSORS
int Order::id() const
{
  return d_id;
}

string Order::dealerId() const 
{
  return d_dealerId;
}

string Order::side() const
{
  return d_side;
}

string Order::commodity() const
{
  return d_commodity;
}

int Order::ammount() const
{
  return d_ammount;
}

double Order::price() const
{
  return d_price;
}

string Order::orderInfo() const
{
  return to_string(d_id) + " " + d_dealerId + "  " + d_side + "  " 
         + d_commodity + "  " + to_string(d_ammount) +  "  "
         + to_string(d_price); 
}
 
ostream& operator<<(ostream& os, const Order& o)
{
  return os << o.orderInfo();
}