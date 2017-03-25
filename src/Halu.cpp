/*
 * Halu.cpp
 *
 *  Created on: 12 mar. 2017
 *      Author: acampo
 */

#include "Halu.h"
#include "Enums.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#include <cstdio>
#include <cstddef>
#include <cstring>
#include <unistd.h>

const int HALU_PORT = 7265;
const int MSG_SIZE = 65536;

int getMessageSize(char* data, int &pos)
{
	int size = data[pos++] << 8;
	size += data[pos++];

	return size;
}

Halu::Halu() :
		m_isSetup(false), m_rcvSocket(0), m_sendSocket(0)
{

}

Halu::~Halu()
{
	close(m_rcvSocket);
}

bool Halu::setup()
{
	m_rcvSocket = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in listener;
	listener.sin_addr.s_addr = INADDR_ANY;
	listener.sin_family = AF_INET;
	listener.sin_port = htons(HALU_PORT);

	int optValue = 1;
	int result = setsockopt(m_rcvSocket, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(int));
	result += setsockopt(m_rcvSocket, SOL_SOCKET, SO_BROADCAST, &optValue, sizeof(int));
	result += bind(m_rcvSocket, (struct sockaddr*) &listener, sizeof(sockaddr));

	fcntl(m_rcvSocket, F_SETFL, O_NONBLOCK);

	m_isSetup = true;

	return m_isSetup;
}

bool Halu::hasEnqueuedData() const
{
	char c;
	return recv(m_rcvSocket, &c, 1, MSG_PEEK) > 0;
}

void Halu::parseMessage(const char *data)
{
	int pos = 0;

	Command command = static_cast<Command>(data[pos++]);
	Action action = static_cast<Action>(data[pos++]);

	execute(command, action, data + pos);
}

void Halu::receive()
{
	sockaddr_in receiver;
	memset(&receiver, 0, sizeof(receiver));
	socklen_t sockLength = sizeof(receiver);

	int size = MSG_SIZE;
	char data[MSG_SIZE];
	int pos = 0;

	size = recvfrom(m_rcvSocket, &data, MSG_SIZE, 0, (sockaddr*) &receiver, &sockLength);
	data[size] = '\0';

	if (data[pos++] == 'L' && data[pos++] == 'U')
	{
		int size = getMessageSize(data, pos);
		int crc = data[pos++];

		int sum = 0;
		for (int i = pos; i < size; ++i)
		{
			sum += data[i];
		}

		if (crc == (sum % 256)) {
			parseMessage(data + pos);
		}

		printf("%s %i\n", data, size);
	}
	else
	{
		printf("discading %s \n", data);
	}
}

void Halu::execute(Command command, Action action, const char* data) {
	switch(command) {
		case Command::Color:
			break;
	}
}

void Halu::run()
{
	while (true)
	{
		while (hasEnqueuedData())
		{
			receive();
		}
	}
}
