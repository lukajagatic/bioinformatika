//============================================================================
// Name        : bioinformatika.cpp
// Author      : Luka Jagatic, Marko Gudelj, Simon Knezevic
// Version     :
// Copyright   : Your copyright notice
// Description : Projekt iz bioinformatike
//============================================================================

#include "MhapFormatter.h"
#include "BestOverlap.h"
#include "Edge.h"

#include <stdlib.h>
#include <stdexcept>
#include <string>

using namespace std;
int main(int argc, char *argv[]) {

	string input_file = "";
	float error_threshold = 0;
	int count = 0;

	for (unsigned int i = 0; i < argc; i++) {
		if (i == 1) {
			input_file += argv[i];
			if (input_file.substr(input_file.find_last_of(".") + 1) != "mhap")
				throw runtime_error("Input mhap files allowed");
		}
		if (i == 2) {
			error_threshold = atof(argv[i]);
			if (error_threshold > 1)
				throw runtime_error(
						"Error threshold cannot be greater than 1!");
		}
		if (i > 2)
			throw runtime_error("Too many arguments");
	}
	MhapFormatter *mf = new MhapFormatter;
	mf->filter(input_file, error_threshold);

	vector<Edge> ev = mf->getEdges();

	//BestOverlap *bo = new BestOverlap;
	//vector<Edge> ev = bo->createBestOverlap(edges);

	//vector<int> contig;
	//int startP = ev[0].idA;
	//contig.insert(contig.begin(), startP);
	
	for (int startP = 0; startP < 157; startP++) {
		vector<int> contig;
		contig.insert(contig.begin(), startP);

		for (int i = 0; i < ev.size(); i++) {

			if(ev[i].idA == contig[contig.size()-1] and ev[i].bhangMinus < ev[i].bhangPlus) { // idB je desno od contiga
				contig.insert(contig.end(), ev[i].idB);
				//cout << ev[i].idA << ev[i].idB << "\n";
				ev.erase(ev.begin()+i);
				i--;
			}

			if(ev[i].idA == contig[0] and ev[i].bhangMinus > ev[i].bhangPlus) { // idB je lijevo od contiga
				contig.insert(contig.begin(), ev[i].idB);
				//cout << ev[i].idA << ev[i].idB << "\n";
				ev.erase(ev.begin()+i);
				i--;
			}

			if(ev[i].idB == contig[contig.size()-1] and ev[i].ahangMinus < ev[i].ahangPlus) { // idA je desno od contiga
				contig.insert(contig.end(), ev[i].idA);
				//cout << ev[i].idA << ev[i].idB << "\n";
				ev.erase(ev.begin()+i);
				i--;
			}

			if(ev[i].idB == contig[0] and ev[i].ahangMinus > ev[i].ahangPlus) { // idA je lijevo od contiga
				contig.insert(contig.begin(), ev[i].idA);
				//cout << ev[i].idA << ev[i].idB << "\n";
				ev.erase(ev.begin()+i);
				i--;
			}

	
			/*cout << ev[i].idA << "\t" << ev[i].idB << "\t" << ev[i].aStart << "\t" << ev[i].aEnd << "\t" << ev[i].aLength 
				<< "\t" << ev[i].ahangPlus << "\t" << ev[i].ahangMinus
				<< "\t" << ev[i].bStart << "\t" << ev[i].bEnd << "\t" << ev[i].bLength << "\t" << ev[i].bhangPlus 
				<< "\t" << ev[i].bhangMinus 
				<< "\t" << ev[i].overlapLength << "\t" << ev[i].orientationA << "\t" << ev[i].orientationB <<"\n";*/
	
		}
	//}

		for (int i = 0; i < contig.size(); i++) {
			cout << contig[i] << "\t";
		}
		cout << "\n";

	}

/*
	cout << "idA" << "\t" << "idB" << "\t" << "aStart" << "\t" << "aEnd" << "\t" << "aLength" 
			<< "\t" << "ahangPlus" << "\t" << "ahangMinus"
			<< "\t" << "bStart" << "\t" << "bEnd" << "\t" << "bLength" << "\t" << "bhangPlus" 
			<< "\t" << "bhangMinus" 
			<< "\t" << "overlapLength" << "\t" << "orientationA" << "\t" << "orientationB" <<"\n";
*/

	exit(0);

}

