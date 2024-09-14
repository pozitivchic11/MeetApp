#include <QCoreApplication>

#include "server.h"

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;

    try {
        // Create an I/O context
        boost::asio::io_context io_context;

        // Create a UDP socket to listen on port 12345
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));

        char buffer[1024];
        udp::endpoint sender_endpoint;

        std::cout << "Server is listening on port 12345..." << std::endl;

        // Receive data from a client
        size_t len = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);

        std::cout << "Received: " << std::string(buffer, len) << " from " << sender_endpoint << std::endl;

        // Send a response to the client
        std::string response = "Message received";
        socket.send_to(boost::asio::buffer(response), sender_endpoint);

    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return a.exec();
}
