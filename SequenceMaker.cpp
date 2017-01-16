#include "SequenceMaker.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Edge.h"

using namespace std;

SequenceMaker::SequenceMaker() {

}

SequenceMaker::~SequenceMaker() {

}
vector<string> reads;

vector<Edge> test;
Edge brid1;
Edge brid2;
Edge brid3;
Edge brid5;

/* Reads all corrected reads from given file and stores it into
 the vector, reads ids are starting from 1 but they are stored with index 0.
 Read 10 is stored at index 9.
 */

void SequenceMaker::loadReads(string corr_reads) {
	ifstream myfile(corr_reads.c_str());
	string line;
	int i;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line.find(">") != -1) {
				continue;
			} else {
				reads.push_back(line.c_str());
			}
		}
	} else {
		cout << "Nesto";
	}
	myfile.close();
}

string SequenceMaker::rComplement(string str) {
	string com("");

	for (int i = str.size(); i >= 0; i--) {
		if (str[i] == 'A') {
			com += 'T';
		}
		if (str[i] == 'G') {
			com += 'C';
		}
		if (str[i] == 'C') {
			com += 'G';
		}
		if (str[i] == 'T') {
			com += 'A';
		}
	}
	return com;
}

string SequenceMaker::makeSequence(string corr_reads,
		vector<pair<bool, Edge> > bridovi) {
	string sequence;
	bool rAlign;
	rAlign = false;
	int idCenter = 0;
	Edge pbrid;
	int aHang = 0;
	string pcontig;

	for (int i = 1; i < bridovi.size(); i++) {
		cout << bridovi[i].second.idA << " " << bridovi[i].second.idB << endl;
	}

	loadReads(corr_reads);

	pbrid = bridovi[idCenter].second;
	rAlign = bridovi[idCenter].first;
	pcontig = reads[pbrid.idA - 1];
	sequence = pcontig;

	pcontig = reads[pbrid.idB - 1];

	while (true) {
		//Reverse Aligned
		if (!rAlign) {

			if (pbrid.ahangMinus > pbrid.ahangPlus) {

				if (pbrid.orientationB == 1) {
					sequence += rComplement(pcontig.substr(0, pbrid.bStart));
				} else {
					sequence += pcontig.substr(pbrid.bEnd, pbrid.bLength);
				}
			} else {

				if (pbrid.orientationB == 1) {
					sequence = rComplement(
							pcontig.substr(pbrid.bEnd, pbrid.bLength))
							+ sequence;
				} else {
					sequence = pcontig.substr(0, pbrid.bStart) + sequence;
				}
			}
			// Ako je reverse onda se spaja na suprotnu stranu od dobivene
		} else {

			if (pbrid.ahangMinus > pbrid.ahangPlus) {
				if (pbrid.orientationB == 1) {
					sequence = pcontig.substr(0, pbrid.bStart) + sequence;
				} else {
					sequence = rComplement(
							pcontig.substr(pbrid.bEnd, pbrid.bLength))
							+ sequence;
				}
			} else {

				if (pbrid.orientationB == 0) {

					sequence += pcontig.substr(pbrid.bEnd, pbrid.bLength);
				} else {

					sequence += rComplement(pcontig.substr(0, pbrid.bStart));
				}
			}
		}
		idCenter++;
		if (idCenter == bridovi.size()) {
			break;
		}
		pbrid = bridovi[idCenter].second;
		rAlign = bridovi[idCenter].first;
		pcontig = reads[pbrid.idB - 1];
	}

	return sequence;
}

