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
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <map>
#include <algorithm>
#include "Sastavi.h"

using namespace std;

int main(int argc, char *argv[]) {

	string input_file = "";
	string corr_reads = "";
	float error_threshold = 0;
	for (unsigned int i = 0; i < argc; i++) {
		if (i == 1) {
			input_file += argv[i];
			if (input_file.substr(input_file.find_last_of(".") + 1) != "mhap")
				throw runtime_error("Input mhap file allowed for argument one");
		}
		if (i == 2) {
			corr_reads += argv[i];
			if (corr_reads.substr(corr_reads.find_last_of(".") + 1) != "fasta")
				throw runtime_error(
						"Input fasta file allowed for argument two");
		}
		if (i == 3) {
			error_threshold = atof(argv[i]);
			if (error_threshold > 1)
				throw runtime_error(
						"Error threshold cannot be greater than 1!");
		}
		if (i > 3)
			throw runtime_error("Too many arguments");
	}
	MhapFormatter *mf = new MhapFormatter;
	mf->filter(input_file, error_threshold);

	vector<Edge> edges = mf->getEdges();

	BestOverlap *bo = new BestOverlap;
	vector<Edge> ev = bo->createBestOverlap(edges);

	Sastavi ss;
	vector<pair<bool, Edge> > testVektor;
	testVektor = ss.sastavljanje(ev);
	Edge brid;

	SequenceMaker maker;
	string sequence;

	ofstream myfile1("sequence.fasta");

	sequence = maker.makeSequence(corr_reads, testVektor);
	myfile1 << "> idd=1 \n";
	myfile1 << sequence;
	myfile1.close();

	/*
	 Edge brid1;
	 Edge brid2;
	 Edge brid3;
	 Edge brid4;
	 Edge brid5;




	 brid1.idA = 4;
	 brid1.idB = 17;
	 brid1.aStart = 4131;
	 brid1.aEnd = 9704;
	 brid1.aLength = 9705;
	 brid1.ahangPlus = brid1.aLength - brid1.aEnd;
	 brid1.ahangMinus = brid1.aStart;
	 brid1.bStart = 0;
	 brid1.bEnd = 5615;
	 brid1.bLength = 8623;
	 brid1.orientationB = 0;

	 brid2.idA = 17;
	 brid2.idB = 144;
	 brid2.aStart = 3681;
	 brid2.aEnd = 8620;
	 brid2.aLength = 8623;
	 brid2.ahangPlus = brid2.aLength - brid2.aEnd;
	 brid2.ahangMinus = brid2.aStart;
	 brid2.bStart = 9;
	 brid2.bEnd = 4968;
	 brid2.bLength = 9976;
	 brid2.orientationB = 0;
	 brid2.overlapLength = 412;

	 brid3.idA = 144;
	 brid3.idB = 159;
	 brid3.aStart = 3657;
	 brid3.aEnd = 9975;
	 brid3.aLength = 9976;
	 brid3.ahangPlus = brid3.aLength - brid3.aEnd;
	 brid3.ahangMinus = brid3.aStart;
	 brid3.bStart = 3292;
	 brid3.bEnd = 9474;
	 brid3.bLength = 9475;
	 brid3.orientationB = 1;
	 brid3.overlapLength = 725;

	 brid4.idA = 150;
	 brid4.idB = 151;
	 brid4.aStart = 4227;
	 brid4.aEnd = 9291;
	 brid4.aLength = 9292;
	 brid4.ahangPlus = brid3.aLength - brid3.aEnd;
	 brid4.ahangMinus = brid3.aStart;
	 brid4.bStart = 4178;
	 brid4.bEnd = 9235;
	 brid4.bLength = 9236;
	 brid4.orientationB = 1;
	 brid4.overlapLength = 725;



	 brid5.idA = 151;
	 brid5.idB = 155;
	 brid5.aStart = 8177;
	 brid5.aEnd = 9235;
	 brid5.aLength = 9236;
	 brid5.ahangPlus = brid4.aLength - brid4.aEnd;
	 brid5.ahangMinus = brid4.aStart;
	 brid5.bStart = 3807;
	 brid5.bEnd = 4848;
	 brid5.bLength = 4855;
	 brid5.orientationB = 1;
	 brid5.overlapLength = 600;

	 brid5.idA = 155;
	 brid5.idB = 159;
	 brid5.aStart = 0;
	 brid5.aEnd = 3792;
	 brid5.aLength = 4855;
	 brid5.ahangPlus = brid4.aLength - brid4.aEnd;
	 brid5.ahangMinus = brid4.aStart;
	 brid5.bStart = 0;
	 brid5.bEnd = 3804;
	 brid5.bLength = 9475;
	 brid5.orientationB = 1;
	 brid5.overlapLength = 999;




	 vector<Edge> test;
	 test.push_back(brid1);
	 test.push_back(brid2);
	 test.push_back(brid3);
	 test.push_back(brid4);
	 test.push_back(brid5);




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
	 */

	exit(0);

}

