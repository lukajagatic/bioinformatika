//============================================================================
// Name        : bioinformatika.cpp
// Author      : Luka Jagatic, Marko Gudelj, Simon Knezevic
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
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
int main(int argc, char *argv[]) {
	//start mjerenja
	double start = clock();

	string input_file = "";
	string output_file = "";
	for (unsigned int i = 0; i < argc; i++) {
		if (i == 1) {
			input_file += argv[i];
			if (input_file.substr(input_file.find_last_of(".") + 1) != "fa")
				throw runtime_error("Input fa files allowed");
		}
		if (i == 2) {
			output_file += argv[i];
			if (output_file.substr(output_file.find_last_of(".") + 1) != "mhap")
				throw runtime_error("Output only in mhap");
		}
		if (i > 2)
			throw runtime_error("Too many arguments");
	}

	double lap1 = clock();
	string command(
			"gnome-terminal -x sh -c './graphmap/bin/Linux-x64/graphmap owler -r "
					+ input_file + " -d " + input_file + " -o " + output_file
					+ "'");
	system(command.c_str());
	double lap2 = clock();
	string getcontent;
	ifstream mhap_file("output.mhap");
	if (mhap_file.is_open()) {
		while (getline(mhap_file, getcontent)) {
			cout << getcontent << endl;
		}
	}

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
