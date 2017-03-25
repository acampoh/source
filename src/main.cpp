/*
 * mian.cpp
 *
 *  Created on: 12 mar. 2017
 *      Author: acampo
 */

#include "Halu.h"


int main(int argc, char** argv)
{
	Halu halu;
	if (halu.setup())
	{
		halu.run();
	}
}
