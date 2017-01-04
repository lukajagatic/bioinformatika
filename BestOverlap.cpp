/*
 * BestOverlap.cpp
 *
 *  Created on: 4 Jan 2017
 *      Author: manager
 */

#include "BestOverlap.h"

BestOverlap::BestOverlap() {
}

BestOverlap::~BestOverlap() {
}

vector<Edge> BestOverlap::createBestOverlap(vector<Edge> edges) {

	int maxL = 0, maxR = 0;
	Edge edL;
	Edge edR;
	vector<Edge> ev;

	for (int i = 1; i < edges.size(); i++) {
		Edge e1 = edges[i - 1];
		Edge e2 = edges[i];
		if (e2.idA == e1.idA) {
			if (e2.ahangMinus > e2.ahangPlus) {

				if (e2.overlapLength > maxL) {
					maxL = e2.overlapLength;
					edL = e2;
				}
			} else {

				if (e2.overlapLength > maxR) {
					maxR = e2.overlapLength;
					edR = e2;
				}
			}

		} else {
			if (maxL != 0)
				ev.push_back(edL);
			if (maxR != 0)
				ev.push_back(edR);
			if (e2.ahangMinus > e2.ahangPlus) {
				maxL = e2.overlapLength;
				edL = e2;
				maxR=0;
			} else {
				maxR = e2.overlapLength;
				edR = e2;
				maxL=0;
			}
		}

	}

	return ev;
}
