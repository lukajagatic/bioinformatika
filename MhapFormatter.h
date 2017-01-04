/*
 * MhapFormatter.h
 *
 *  Created on: 4 Jan 2017
 *      Author: manager
 */

#ifndef MHAPFORMATTER_H_
#define MHAPFORMATTER_H_

#include <string>
#include <vector>

#include "Edge.h"

using namespace std;

class MhapFormatter {
public:
	MhapFormatter();
	~MhapFormatter();

	void filter(string, float);
	vector<Edge*> getEdges();
};

#endif /* MHAPFORMATTER_H_ */
