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


	for (int i = 0; i < ev.size(); i++) {
		cout << ev[i].idA << "\t" << ev[i].idB << "\t" << ev[i].overlapLength
				<< "\t" << ev[i].ahangMinus << "\t" << ev[i].ahangPlus << "\n";
	}

	exit(0);

}

