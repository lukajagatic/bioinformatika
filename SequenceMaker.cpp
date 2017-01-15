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

string SequenceMaker::makeSequence(string corr_reads, vector<Edge> bridovi) {
	string sequence;

	int idCenter = 0;
	Edge pbrid;

	string pcontig;

	loadReads(corr_reads);

	pbrid = bridovi[idCenter];
	pcontig = reads[pbrid.idA - 1];
	sequence = pcontig;

	pcontig = reads[pbrid.idB - 1];

	while (true) {
			cout << "\n  aHangMinus:" << pbrid.ahangMinus << " aHangPlus:" << pbrid.ahangPlus << endl;
		if (pbrid.ahangMinus > pbrid.ahangPlus) {
			cout << "Spajam Desno" << pbrid.idA << "+" << pbrid.idB << endl;
			if (pbrid.orientationB == 1) {
				sequence += rComplement(pcontig.substr(0, pbrid.bStart)) ;
			} else {
				sequence += pcontig.substr(pbrid.bEnd, pbrid.bLength) ;
			}
		} else {
			cout << "Spajam Lijevo" << pbrid.idA << "+" << pbrid.idB << endl;

			if (pbrid.orientationB == 1) {
				sequence = rComplement(pcontig.substr(pbrid.bEnd, pbrid.bLength)) + sequence;
			} else {
				sequence = pcontig.substr(0, pbrid.bStart) + sequence;
			}
		}
		idCenter++;
		if(idCenter == bridovi.size()){
			break;
		}
		pbrid = bridovi[idCenter];
		pcontig = reads[pbrid.idB - 1];
	}

	return sequence;
}

