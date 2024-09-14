#include <QCoreApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QUrl>
#include <QObject>
#include <QGuiApplication>

#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    try {
        // Create an I/O context
        boost::asio::io_context io_context;

        // Create a UDP socket
        udp::socket socket(io_context);

        // Resolve the server address and port
        udp::resolver resolver(io_context);
        udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), "127.0.0.1", "12345");

        // Open the socket
        socket.open(udp::v4());

        // Send a message to the server
        std::string message = "Hello from client";
        socket.send_to(boost::asio::buffer(message), *endpoints.begin());

        // Receive a response from the server
        char buffer[1024];
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);

        std::cout << "Server replied: " << std::string(buffer, len) << std::endl;

    } catch (std::exception& e) {
        // std::cerr << "Error: " << e.what() << std::endl;
    }

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/qml/main_window.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &a, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return a.exec();
}
