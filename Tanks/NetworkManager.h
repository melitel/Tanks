#pragma once
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <memory>

class NetworkManager
{
public:

	// Functions to manage connections
	bool connectToServer(const std::string& ipAddress, unsigned short port);
	void acceptConnections(unsigned short port);

	// Function to send a message
	void sendMessage(const std::string& message);

	// Function to receive messages
	void receiveMessages();

private:

	std::unique_ptr<sf::TcpSocket> connectSocket;
	sf::TcpListener listener;
	std::vector<std::unique_ptr<sf::TcpSocket>> connectedClients;


};

