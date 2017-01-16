/*
 * Sastavi.cpp
 *
 *  Created on: 15 Jan 2017
 *      Author: manager
 */

#include "Sastavi.h"
#include "Edge.h"
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
Sastavi::Sastavi() {
	// TODO Auto-generated constructor stub

}

Sastavi::~Sastavi() {
	// TODO Auto-generated destructor stub
}

vector<vector<pair<bool, Edge> > > AllContigs;

int trenutacni = 0;
vector<pair<bool, Edge> > visited;
vector<int> visitedID;
vector<Edge> AllEdges2;
bool rAlign = false;
vector<pair<bool, Edge> > Sastavi::sastavljanje(vector<Edge> AllEdges) {
	pair<bool, Edge> ret;
	Edge curEdge;
	AllEdges2 = AllEdges;

	for (int i = 0; i < AllEdges2.size(); i++) {

		curEdge = AllEdges[i];
		ret = make_pair(rAlign, curEdge);
		if (both(i)) {
			if (curEdge.orientationB == 1) {
				pushOrientation(ret);
				rAlign = true;
				recursionLeft(curEdge.idB);
			} else {
				pushNormal(ret);
				recursionRight(curEdge.idB);
			}
			rAlign = false;
			curEdge = getSecond(i);
			ret = make_pair(rAlign, curEdge);
			if (checkVisited(curEdge.idB)) {
			} else {
				if (curEdge.orientationB == 1) {
					pushOrientation(ret);
					rAlign = true;
					recursionRight(curEdge.idB);
				} else {
					visited.push_back(ret);
					recursionLeft(curEdge.idB);
				}
			}
		} else {
			continue;
		}

		AllContigs.push_back(visited);
		rAlign = false;
		visited.clear();
		visitedID.clear();
		if (both(i)) {
			trenutacni += 2;
		} else {
			trenutacni++;
		}
	}

	return findLongest(AllContigs);
}
void Sastavi::recursionRight(int idB) {
	pair<bool,Edge > ret;
	pair<int, Edge> par;

	par = find(idB);
	if (par.second.idA == -1) {
		return;
	}
	ret = make_pair(rAlign, par.second);
	if (both(par.first)) {
		if (checkVisited(par.second.idB)) {
			return;
		}

		if (par.second.orientationB == 1) {
			rAlign = true;
			pushOrientation(ret);
			recursionLeft(par.second.idB);
		} else {
			pushNormal(ret);
			recursionRight(par.second.idB);
		}
	} else {
		if (checkVisited(par.second.idB)) {
			return;
		}
		if (ifRightB(par.second)) {
			if (par.second.orientationB == 1) {
				rAlign = true;
				pushOrientation(ret);
				recursionLeft(par.second.idB);
			} else {
				pushNormal(ret);
				recursionRight(par.second.idB);
			}
		}
	}

}

void Sastavi::recursionLeft(int idB) {
	pair<bool,Edge> ret;
	pair<int, Edge> par;

	par = find(idB);
	if (par.second.idA == -1) {
		return;
	}

	if (both(par.first)) {
		par = make_pair(par.first, getSecond(par.first));
		ret = make_pair(rAlign, par.second);
		if (checkVisited(par.second.idB)) {
			return;
		}

		if (par.second.orientationB == 1) {
			rAlign = true;
			pushOrientation(ret);
			recursionRight(ret.second.idB);
		} else {
			pushNormal(ret);
			recursionLeft(ret.second.idB);
		}
	} else {
		if (checkVisited(par.second.idB)) {
			return;
		}
		if (ifLeftB(par.second)) {
			make_pair(rAlign,par.second);
			if (par.second.orientationB == 1) {
				rAlign = true;
				pushOrientation(ret);
				recursionRight(par.second.idB);

			} else {
				pushNormal(ret);
				recursionLeft(par.second.idB);
			}
		}
	}
}

pair<int, Edge> Sastavi::find(int idB) {
	Edge dummy;
	dummy.idA = -1;

	for (int i = trenutacni; i < AllEdges2.size(); i++)
		if (AllEdges2[i].idA == idB) {
			return make_pair(i, AllEdges2[i]);
		}
	return make_pair(0, dummy);
}

bool Sastavi::checkVisited(int idB) {
	if ((std::find(visitedID.begin(), visitedID.end(), idB))
			!= visitedID.end()) {
		return true;
	}
	return false;
}
void Sastavi::pushOrientation(pair<bool, Edge> par) {
	visited.push_back(par);
	visitedID.push_back(par.second.idA);
	visitedID.push_back(par.second.idB);

}

void Sastavi::pushNormal(pair<bool, Edge> par) {
	visited.push_back(par);
	visitedID.push_back(par.second.idA);
	visitedID.push_back(par.second.idB);
}
bool Sastavi::ifRightB(Edge e) {
	if (e.bhangMinus < e.bhangPlus)
		return true;
	return false;
}

bool Sastavi::ifLeftB(Edge e) {
	if (e.bhangMinus > e.bhangPlus)
		return true;
	return false;
}

bool Sastavi::ifRightA(Edge e) {
	if (e.ahangMinus < e.ahangPlus)
		return true;
	return false;
}

bool Sastavi::ifLeftA(Edge e) {
	if (e.ahangMinus > e.ahangPlus)
		return true;
	return false;
}

bool Sastavi::both(int current) {
	if (getSecond(current).idA == AllEdges2[current].idA)
		return true;
	return false;
}

Edge Sastavi::getSecond(int current) {
	return AllEdges2[current + 1];
}

vector<pair<bool, Edge> > Sastavi::findLongest(vector<vector<pair<bool, Edge> > >ev) {
	vector<pair<bool, Edge> > longest;

	longest = ev[0];

	for (int i = 0; i < ev.size(); i++) {
		if(longest.size() < ev[i].size()){
			longest = ev[i];
		}
	}
	return longest;
}
