#include <SFML/Network.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


int main(void)
{
	sf::TcpListener listener;
	listener.listen(1998);
	if(listener.listen(1998) != sf::Socket::Done){
		perror("Listen");
	}
	else
		perror("Listen");
	
	sf::TcpSocket client;
	if(listener.accept(client) != sf::Socket::Done){
		perror("Accept");
		exit(EXIT_FAILURE);
	}
	else
		perror("Accept");


	std::cout << "New client connected: " << client.getRemoteAddress() << std::endl;
   // Receive a message from the client

  while(true){
		sf::Packet packet;
    client.receive(packet);

    sf::Uint16 x;
    std::string s;
    double d;

    packet >> x >> s >> d;
    if (packet >> x) {
			std::cout << x << std::endl;
    }
  }
    return 0;
}
