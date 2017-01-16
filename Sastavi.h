/*
 * Sastavi.h
 *
 *  Created on: 15 Jan 2017
 *      Author: manager
 */

#ifndef SASTAVI_H_
#define SASTAVI_H_
#include "Edge.h"
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
class Sastavi {
public:
	Sastavi();
	virtual ~Sastavi();

	vector<pair<bool, Edge> >sastavljanje(vector<Edge> AllEdges);

	bool ifRightB(Edge);

	bool ifLeftB(Edge);

	bool ifRightA(Edge);

	bool ifLeftA(Edge);
	bool both(int);
	void recursionLeft(int);
	void recursionRight(int);
	pair<int, Edge>  find(int);
	Edge getSecond(int);
	void pushOrientation(pair<bool, Edge>);
	void pushNormal(pair<bool, Edge>);
	bool checkVisited(int);


	vector<pair<bool, Edge> >  findLongest(vector<vector<pair<bool, Edge> > >ev);
};

#endif /* SASTAVI_H_ */
