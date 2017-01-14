/*
 * BestOverlap.h
 *
 *  Created on: 4 Jan 2017
 *      Author: manager
 */

#ifndef BESTOVERLAP_H_
#define BESTOVERLAP_H_

#include <vector>
#include "Edge.h"

using namespace std;

class BestOverlap {
public:
	BestOverlap();
	virtual ~BestOverlap();

	vector<Edge> createBestOverlap(vector<Edge>);
	vector<Edge> createContigs(vector<Edge>, int);
};

#endif /* BESTOVERLAP_H_ */
