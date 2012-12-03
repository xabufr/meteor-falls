#include "Engine/NetworkEngine/NetworkIpAdressFinder.h"

boost::asio::ip::address getAddress(boost::asio::io_service &service, std::string host, bool* error)
{
    boost::asio::ip::address address;
    boost::system::error_code error_c;
    address  = boost::asio::ip::address::from_string(host, error_c);
    if(!error_c){
        if(error)
            *error=false;
        return address;
    }
    boost::asio::ip::tcp::resolver resolver(service);
    boost::asio::ip::tcp::resolver::query query(host, "80");
    boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    if(iter!=end)
    {
        if(error)
            *error=false;
        return iter->endpoint().address();
    }
    if(error)
            *error=true;
    return boost::asio::ip::address();
}
