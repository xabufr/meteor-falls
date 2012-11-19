#ifndef NETWORKIPADRESSFINDER_H_INCLUDED
#define NETWORKIPADRESSFINDER_H_INCLUDED
#include <boost/asio.hpp>
#include <string>

boost::asio::ip::address getAddress(boost::asio::io_service &, std::string, bool *error = 0);

#endif // NETWORKIPADRESSFINDER_H_INCLUDED
