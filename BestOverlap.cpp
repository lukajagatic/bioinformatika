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
			if ((e2.ahangMinus > e2.ahangPlus)
					&& (e2.ahangMinus > e2.aLength / 20)) {
				if ((e2.bhangMinus > e2.bhangPlus
						&& (e2.bhangMinus > e2.bLength / 20))
						|| (e2.bhangMinus < e2.bhangPlus
								&& (e2.bhangPlus > e2.bLength / 20))) {

					if (e2.overlapLength > maxL) {
						maxL = e2.overlapLength;
						edL = e2;
					}
				}

			} else if ((e2.ahangMinus < e2.ahangPlus)
					&& (e2.ahangPlus > e2.aLength / 20)) {

				if ((e2.bhangMinus > e2.bhangPlus
						&& (e2.bhangMinus > e2.bLength / 20))
						|| (e2.bhangMinus < e2.bhangPlus
								&& (e2.bhangPlus > e2.bLength / 20))) {

					if (e2.overlapLength > maxR) {
						maxR = e2.overlapLength;
						edR = e2;
					}
				}
			}

		} else {
			if (maxL != 0)
				ev.push_back(edL);
			if (maxR != 0)
				ev.push_back(edR);
			if (e2.ahangMinus > e2.ahangPlus) {
				if ((e2.ahangMinus > e2.aLength / 20)) {
					maxL = e2.overlapLength;
					edL = e2;
				} else
					maxL = 0;
				maxR = 0;
			} else {
				if ((e2.ahangPlus > e2.aLength / 20)) {
					maxR = e2.overlapLength;
					edR = e2;
				} else
					maxR = 0;
				maxL = 0;
			}
		}
	}
	return ev;
}

vector<Edge> BestOverlap::createContigs(vector<Edge> ev, int x) {
	vector<int> contig;
	vector<Edge> contigE;
	int startP = ev[x].idA;
	contig.insert(contig.begin(), startP);

	for (int loop = 0; loop < 1; loop++) {
		for (int i = 0; i < ev.size(); i++) {

			if (ev[i].idA == contig[contig.size() - 1]
					and ev[i].bhangMinus < ev[i].bhangPlus) { // idB je desno od contiga
				contig.insert(contig.end(), ev[i].idB);
				//ev.erase(ev.begin()+i);
			}

			if (ev[i].idA == contig[0] and ev[i].bhangMinus > ev[i].bhangPlus) { // idB je lijevo od contiga
				contig.insert(contig.begin(), ev[i].idB);
				//ev.erase(ev.begin()+i);
			}

			if (ev[i].idB == contig[contig.size() - 1]
					and ev[i].ahangMinus < ev[i].ahangPlus) { // idA je desno od contiga
				contig.insert(contig.end(), ev[i].idA);
				//ev.erase(ev.begin()+i);
			}

			if (ev[i].idB == contig[0] and ev[i].ahangMinus > ev[i].ahangPlus) { // idA je lijevo od contiga
				contig.insert(contig.begin(), ev[i].idA);
				//ev.erase(ev.begin()+i);
			}

		}
	}

	for (int i = 0; i < contig.size(); i++) {
		for (int j = 0; j < ev.size(); j++) {
			if (contig[i] < contig[i + 1] && ev[j].idA == contig[i]
					&& ev[j].idB == contig[i + 1])
				contigE.push_back(ev[j]);
			else if (contig[i + 1] < contig[i] && ev[j].idA == contig[i + 1]
					&& ev[j].idB == contig[i])
				contigE.push_back(ev[j]);

		}
	}

//	for (int i = 0; i < contigE.size(); i++) {
//		cout << contigE[i].idA << "\t" << contigE[i].idB << "\t";
//	}
//	cout<<"\n";
//
//	for (int i = 0; i < contig.size(); i++) {
//		cout << contig[i] << "\t";
//	}
	return contigE;
}

