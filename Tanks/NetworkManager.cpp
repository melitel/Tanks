#include "NetworkManager.h"
#include <iostream>

bool NetworkManager::connectToServer(const std::string& ipAddress, unsigned short port)
{
    if (connectSocket->connect(ipAddress, port) == sf::Socket::Done) {
        std::cout << "Connected to the server." << std::endl;
        return true;
    }
    else {
        std::cout << "Connection failed." << std::endl;
        return false;
    }
}

void NetworkManager::acceptConnections(unsigned short port)
{
    if (listener.listen(port) != sf::Socket::Done) {
        std::cout << "Failed to bind the listener to port " << port << std::endl;
        return;
    }

    while (true) {

        std::unique_ptr<sf::TcpSocket> clientSocket = std::make_unique<sf::TcpSocket>();

        if (listener.accept(*clientSocket) == sf::Socket::Done) {

            std::cout << "New client connected: " << clientSocket->getRemoteAddress() << std::endl;
            connectedClients.push_back(std::move(clientSocket));
        }
    }
}

void NetworkManager::sendMessage(const std::string& message)
{

}
