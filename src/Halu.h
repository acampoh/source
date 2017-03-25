/*
 * Halu.h
 *
 *  Created on: 12 mar. 2017
 *      Author: acampo
 */

#include "Enums.h"

#ifndef HALU_H_
#define HALU_H_

class Halu
{
public:
	Halu();
	virtual ~Halu();

	bool setup();
	void run();

private:
	bool hasEnqueuedData() const;
	void parseMessage(const char *data);
	void receive();
	void execute(Command command, Action action, const char* data);

	bool m_isSetup;
	int  m_rcvSocket;
	int  m_sendSocket;
};

#endif /* HALU_H_ */
