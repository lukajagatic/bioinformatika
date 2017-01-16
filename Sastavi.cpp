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

vector<vector<Edge> > AllContigs;
vector<Edge> lonContig;
int trenutacni = 0;
vector<Edge> visited;
vector<int> visitedID;
vector<Edge> AllEdges2;

vector<Edge> Sastavi::sastavljanje(vector<Edge> AllEdges) {
	Edge curEdge;
	AllEdges2 = AllEdges;

	for (int i = 0; i < 1; i++) {

		curEdge = AllEdges[i];

		if (both(i)) {
			if (curEdge.orientationB == 1) {
				pushOrientation(curEdge);
				recursionLeft(curEdge.idB);
			} else {
				pushNormal(curEdge);
				recursionRight(curEdge.idB);
			}

			curEdge = getSecond(i);
			if (checkVisited(curEdge.idB)) {
			} else {
				if (curEdge.orientationB == 1) {
					pushOrientation(curEdge);
					recursionRight(curEdge.idB);
				} else {
					visited.push_back(curEdge);
					cout << "Pushing: " << curEdge.idA << " + " << curEdge.idB
							<< endl;
					recursionLeft(curEdge.idB);
				}
			}
		} else {
			continue;
		}

		AllContigs.push_back(visited);
		visited.clear();
		visitedID.clear();
		if (both(i)) {
			trenutacni += 2;
		} else {
			trenutacni++;
		}
	}

	lonContig = findLongest(AllContigs);
	cout << AllContigs.size() << endl;
	return lonContig;
}
void Sastavi::recursionRight(int idB) {

	pair<int, Edge> par;

	par = find(idB);
	if (par.second.idA == -1) {
		return;
	}
	if (both(par.first)) {
		if (checkVisited(par.second.idB)) {
			return;
		}

		if (par.second.orientationB == 1) {
			pushOrientation(par.second);
			recursionLeft(par.second.idB);
		} else {
			pushNormal(par.second);
			recursionRight(par.second.idB);
		}
	} else {
		if (checkVisited(par.second.idB)) {
			return;
		}
		if (ifRightB(par.second)) {
			if (par.second.orientationB == 1) {
				pushOrientation(par.second);
				recursionLeft(par.second.idB);
			} else {
				pushNormal(par.second);
				recursionRight(par.second.idB);
			}
		}
	}

}

void Sastavi::recursionLeft(int idB) {

	pair<int, Edge> par;

	par = find(idB);
	if (par.second.idA == -1) {
		return;
	}
	if (both(par.first)) {
		par = make_pair(par.first, getSecond(par.first));

		if (checkVisited(par.second.idB)) {
			return;
		}

		if (par.second.orientationB == 1) {
			pushOrientation(par.second);
			recursionRight(par.second.idB);
		} else {
			pushNormal(par.second);
			recursionLeft(par.second.idB);
		}
	} else {
		if (checkVisited(par.second.idB)) {
			return;
		}
		if (ifLeftB(par.second)) {
			if (par.second.orientationB == 1) {
				pushOrientation(par.second);
				recursionRight(par.second.idB);

			} else {
				pushNormal(par.second);
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
void Sastavi::pushOrientation(Edge brid) {
	visited.push_back(brid);
	visitedID.push_back(brid.idA);
	visitedID.push_back(brid.idB);

	cout << "Pushing: Orijentacija" << brid.idA << " + " << brid.idB << endl;
}

void Sastavi::pushNormal(Edge brid) {
	cout << "Pushing: Normal" << brid.idA << " + " << brid.idB << endl;
	visited.push_back(brid);
	visitedID.push_back(brid.idA);

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

vector<Edge> Sastavi::findLongest(vector<vector<Edge> > ev) {
	vector<Edge> longest;

	longest = ev[0];
	for (int i = 0; i < ev.size(); i++) {
		if (longest.size() < ev[i].size()) {
			longest = ev[i];
		}
	}

	return longest;
}
