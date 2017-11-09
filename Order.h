#ifndef GUARD_order_h
#define GUARD_order_h

#include <string>

class Order {

  private:
    // DATA
    int         d_id;
    std::string d_dealerId;
    std::string d_side;
    std::string d_commodity;
    int         d_ammount;
    double      d_price;

  public:
    // CREATORS
    Order(const std::string& dealerId, 
          const std::string& side, 
          const std::string& commodity, 
          int                ammount, 
          double             price);

    // MANIPULATORS
    void setAmmount(int ammount);

    // ACCESSORS 
    int         id()        const;
    std::string dealerId()  const;
    std::string side()      const;
    std::string commodity() const;
    int         ammount()   const;
    double      price()     const;
    
    std::string orderInfo() const;

    friend 
    std::ostream& operator<<(std::ostream& os, const Order& o);
};

#endif

