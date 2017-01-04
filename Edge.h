/*
 * Edge.h
 *
 *  Created on: 4 Jan 2017
 *      Author: manager
 */

#ifndef EDGE_H_
#define EDGE_H_

#include <iostream>

class Edge {
public:
	Edge();
	virtual ~Edge();

	int idA;
	int idB;
	float error; //graphmap?
	int numSur; //number of seeds which survived filtering
	int aStart;
	int aEnd;
	int aLength;
	int ahangPlus;
	int ahangMinus;
	int bStart;
	int bEnd;
	int bLength;
	int bhangMinus;
	int bhangPlus;
	int overlapLength;
	int orientationA;
	int orientationB;
};

#endif /* EDGE_H_ */
