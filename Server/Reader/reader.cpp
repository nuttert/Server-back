#include "reader.hpp"
#include <Utils/Exceptions/file_exceptions.hpp>
#include <Utils/server_utils.hpp>
#include <iostream>

namespace
{
namespace ex = exceptions;
namespace ba = boost::asio;
} // namespace
namespace server::reader
{

Reader::Reader(const ConfigPtr& config_ptr)
{
    if (!config_ptr)
        throw ex::BadConfig{"Can't read from config!"};
    config = config_ptr;
}

std::string Reader::Read(const SocketPtr &socket_ptr)
{
    ba::streambuf buffer{};
    boost::system::error_code error{};
    std::string result;

    if (!socket_ptr)
        throw ex::CannotReadFromSocket("Socket is nullptr!");
    if (!socket_ptr->is_open())
        throw ex::CannotReadFromSocket("Socket is closed!");
    auto &socket = *socket_ptr;

    auto size = ba::read(socket, buffer, ba::transfer_at_least(1), error);

    if (error.failed() &&
        error != ba::error::eof)
        throw ex::CannotReadFromSocket("Can't read from socket!" + error.message());
    result.resize(size);

    std::istream stream(&buffer);
    while (!stream.eof())
    {
        std::string string;
        stream >> string;
        result += string;
    }
    return result;
}

} // namespace server::reader
