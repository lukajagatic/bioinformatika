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
#include "SequenceMaker.h"
#include "CreateContig.h"
#include <fstream>
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
//				<< ev[i].aStart << " " << ev[i].aEnd << " "<<ev[i].aLength<< " "
//				<< ev[i].orientationB << " " << ev[i].bStart << " "
//				<< ev[i].bEnd << " " << ev[i].bLength << "\n";
//	}
	CreateContig *cc = new CreateContig;
	vector<vector<Edge> > bestContig = cc->bestContig(ev);


	SequenceMaker maker;
	string sequence;
	string corr_reads;



	corr_reads ="lambda_corrected_reads.fasta";
	vector<string> str;
	str.push_back("\"sequence1.fasta\"");
	str.push_back("\"sequence2.fasta\"");
	str.push_back("\"sequence3.fasta\"");
	str.push_back("\"sequence4.fasta\"");
	str.push_back("\"sequence5.fasta\"");
	str.push_back("\"sequence6.fasta\"");
	str.push_back("\"sequence7.fasta\"");
	str.push_back("\"sequence8.fasta\"");
	str.push_back("\"sequence9.fasta\"");
	str.push_back("\"sequence10.fasta\"");


	for(int i=0; i< bestContig.size(); i++){
		ofstream myfile1(str[i].c_str());
		sequence = maker.makeSequence(corr_reads,bestContig[i]);
			myfile1 << "> idd=1 \n";
			myfile1 << sequence;
			myfile1.close();
	}







	exit(0);

}

