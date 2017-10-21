#ifndef GUARD_validate_h
#define GUARD_validate_h


void validateCommand(const string& command)
{
  if(fmap.find(command) == fmap.end())
    throw invalid_argument("UNKNOWN_COMMAND " + command);
}

bool isDouble(const string& s)
{
    try {
        stod(s);
    }
    catch(...) {
        return false;
    }
    return true;
}

bool isInteger(const string& s)
{
    try {
        stoi(s);
    }
    catch(...) {
        return false;
    }
    return true;
}

void validatePostParameters(const vector<string>& params) 
{
  vector<string> validCommodities = {"GOLD", "SILV", "PORK", "RICE", "OIL"};
  if( params[0] != "BUY" and params[0] != "SELL" )
    throw invalid_argument("INVALID_SIDE");
  if( find(validCommodities.begin(), validCommodities.end(), params[1]) 
      == validCommodities.end() )
    throw invalid_argument("INVALID_COMMODITY");
  if( !isInteger(params[2]) )
    throw invalid_argument("INVALID_AMMOUNT");
  if( !isDouble(params[3]) )
    throw invalid_argument("INVALID_PRICE");
}

void validateRevokeParameters(const vector<string>& params)
{
  if(params.size() == 0)
    throw invalid_argument("NO_ORDER_ID_PROVIDED");
  if(!isInteger(params[0]))
    throw invalid_argument("INVALID_ORDER_ID");
}

#endif