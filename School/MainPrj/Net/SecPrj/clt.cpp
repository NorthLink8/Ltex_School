#include <SFML/Network.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


int main(void)
{
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("127.0.0.1", 1998);
	if (status != sf::Socket::Done){
        perror("Connect");
				exit(EXIT_FAILURE);
  }
	else
		perror("Connect");

   sf::Uint16 x = 10;
   std::string s = "hello";
   double d = 0.6;

   sf::Packet packet;
   packet << x << s << d;

   socket.send(packet);

   return 0;	
}
