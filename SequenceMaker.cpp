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
	string pcontig1;
	string pcontig2;

	loadReads(corr_reads);

	pbrid = bridovi[idCenter];
	pcontig1 = reads[pbrid.idA - 1];
	sequence = pcontig1;

	pcontig2 = reads[pbrid.idB - 1];

	while (true) {

		if (pbrid.ahangMinus > pbrid.ahangPlus) {
		/*	cout << "Spajam lijevo" << pbrid.idA << "+" << pbrid.idB;
			if (pbrid.orientationB == 1) {
				sequence = rComplement(pcontig2.substr(0, pbrid.bStart)) + sequence;
			} else {
				sequence = pcontig2.substr(pbrid.bEnd, pbrid.bLength) + sequence;
			}*/
		} else {
			cout << "Spajam desno" << pbrid.idA << "+" << pbrid.idB << endl;

			if (pbrid.orientationB == 1) {
				sequence += rComplement(pcontig2.substr(0, pbrid.bStart));
			} else {
				sequence += pcontig2.substr(pbrid.bEnd, pbrid.bLength);
			}
		}
		idCenter++;
		if(idCenter == bridovi.size()){
			break;
		}
		pbrid = bridovi[idCenter];
		pcontig2 = reads[pbrid.idB - 1];
	}

	idCenter = 0;
	pbrid = bridovi[idCenter];
	pcontig2 = reads[pbrid.idB - 1];
	while (true) {

			if (pbrid.ahangMinus > pbrid.ahangPlus) {

				if (pbrid.orientationB == 1) {
					sequence = rComplement(pcontig2.substr(0, pbrid.bStart)) + sequence;
				} else {
					sequence = pcontig2.substr(pbrid.bEnd, pbrid.bLength) + sequence;
				}
			} else {
				/*cout << "Spajam desno" << pbrid.idA << "+" << pbrid.idB << endl;

				if (pbrid.orientationB == 1) {
					sequence += rComplement(pcontig2.substr(0, pbrid.bStart));
				} else {
					sequence += pcontig2.substr(pbrid.bEnd, pbrid.bLength);
				}
				*/
			}


			idCenter++;
			if(idCenter == bridovi.size() ){
				break;
			}
			pbrid = bridovi[idCenter];
			pcontig2 = reads[pbrid.idB - 1];
		}

	return sequence;
}

