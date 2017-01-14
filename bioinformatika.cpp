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
#include "ContigMaker.h"

#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <map>

using namespace std;
int main(int argc, char *argv[]) {

	string input_file = "";
	float error_threshold = 0;
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

	vector<Edge> edges = mf->getEdges();

	BestOverlap *bo = new BestOverlap;
	vector<Edge> ev = bo->createBestOverlap(edges);

//	for (int i = 0; i < ev.size(); i++) {
//		cout << ev[i].idA << " " << ev[i].idB << " " << ev[i].error << " "
//				<< ev[i].numSur << " " << ev[i].orientationA << " "
//				<< ev[i].aStart << " " << ev[i].aEnd << " "
//				<< ev[i].orientationB << " " << ev[i].bStart << " "
//				<< ev[i].bEnd << " " << ev[i].bLength << "\n";
//	}
	map<int, vector<Edge> > kontizi;
	for (int var = 0; var < ev.size(); var++) {
		if (ev[var].idA != ev[var + 1].idA) {
			vector<Edge> edgv = bo->createContigs(ev, var);
			kontizi.insert(
					pair<int, vector<Edge> >(var, bo->createContigs(ev, var)));
		}

	}
	std::map<int, vector<Edge> >::iterator it1;

	for (it1 = kontizi.begin(); it1 != kontizi.end(); it1++) {
		std::cout << it1->second.size() << '\n';
	}
	exit(0);

}

