/*
 * MhapFormatter.cpp
 *
 *  Created on: 4 Jan 2017
 *      Author: manager
 */

#include "MhapFormatter.h"
#include "Edge.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

MhapFormatter::MhapFormatter() {


}

MhapFormatter::~MhapFormatter() {

}

vector<Edge> edges;

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

vector<std::string> split(string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

void MhapFormatter::filter(string input_file, float error_treshold) {
	ifstream myfile(input_file.c_str());
	string line;
	Edge edge;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			vector<string> tokens = split(line, ' ');
			if (atof(tokens[2].c_str()) > error_treshold) {
				edge.idA = atoi(tokens[0].c_str());
				edge.idB = atoi(tokens[1].c_str());
				edge.error = atof(tokens[2].c_str());
				edge.numSur = atoi(tokens[3].c_str());
				edge.orientationA = atoi(tokens[4].c_str());
				edge.aStart = atoi(tokens[5].c_str());
				edge.aEnd = atoi(tokens[6].c_str());
				edge.aLength = atoi(tokens[7].c_str());
				edge.orientationB = atoi(tokens[8].c_str());
				edge.bStart = atoi(tokens[9].c_str());
				edge.bEnd = atoi(tokens[10].c_str());
				edge.bLength = atoi(tokens[11].c_str());

				if (edge.orientationB == 0) {
					edge.ahangPlus = edge.aLength - edge.aEnd;
					edge.ahangMinus = edge.aStart;
					edge.bhangPlus = edge.bLength - edge.bEnd;
					edge.bhangMinus = edge.bStart;
					edge.overlapLength = edge.aEnd - edge.aStart;
				}

				if (edge.orientationB == 1) {

					edge.ahangPlus = edge.aLength - edge.aEnd;
					edge.ahangMinus = edge.aStart;
					edge.bhangPlus = edge.bStart;
					edge.bhangMinus = edge.bLength - edge.bEnd;
					edge.overlapLength = edge.aEnd - edge.aStart;

				}

				edges.push_back(edge);

			}

		}
		myfile.close();

	}

	else
		cout << "Unable to open file";
}

vector<Edge> MhapFormatter::getEdges() {
	return edges;
}

