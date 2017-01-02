//============================================================================
// Name        : bioinformatika.cpp
// Author      : Luka Jagatic, Marko Gudelj, Simon Knezevic
// Version     :
// Copyright   : Your copyright notice
// Description : Projekt iz bioinformatike
//============================================================================

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <fstream>

using namespace std;

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

void read(string input_file, float error_treshold) {
	ifstream myfile(input_file.c_str());
	string line;

	if (myfile.is_open()) {

		int i = 0;

		while (getline(myfile, line)) {
			i++;
			vector<string> tokens = split(line, ' ');
			if (atof(tokens[2].c_str()) > error_treshold) {
				cout << tokens[2].c_str() << '\n';
			}

		}
		myfile.close();

	}

	else
		cout << "Unable to open file";
}

int main(int argc, char *argv[]) {
	//start mjerenja
	double start = clock();

	string input_file = "";
	string output_file = "";
	for (unsigned int i = 0; i < argc; i++) {
		if (i == 1) {
			input_file += argv[i];
			if (input_file.substr(input_file.find_last_of(".") + 1) != "mhap")
				throw runtime_error("Input mhap files allowed");
		}
		if (i > 1)
			throw runtime_error("Too many arguments");
	}

	double lap1 = clock();
	double lap2 = clock();
	read(input_file, 0.7);

	// kraj mjerenja
	double end = clock();
	//ispis mjerenja
	cout << "\nTrajanja programa:" << std::endl;
	cout << "Ucitavanje i edge removing: "
			<< (double) (lap1 - start) / (double) CLOCKS_PER_SEC << " s"
			<< std::endl;
	cout << "Chunker: " << (double) (lap2 - lap1) / (double) CLOCKS_PER_SEC
			<< " s" << std::endl;
	cout << "Ispis rezultata u datoteke: "
			<< (double) (end - lap2) / (double) CLOCKS_PER_SEC << " s"
			<< std::endl;
	cout << "Ukupno vrijeme: "
			<< (double) (double) (end - start) / (double) CLOCKS_PER_SEC << " s"
			<< std::endl;

	exit(0);

}

