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
#include <algorithm>
#include <map>

using namespace std;


map<int,float> mapa;

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

void read(string input_file, float error_threshold) {
	ifstream myfile(input_file.c_str());
	string line;
	if (myfile.is_open()) {


		vector<float> largest_error;
		int v = 0;
		while (getline(myfile, line)) {

			vector<string> tokens = split(line, ' ');
			if(v == 0){
				v = atoi(tokens[0].c_str());
			}
			if(atoi(tokens[0].c_str()) != v){


				sort(largest_error.begin(), largest_error.end());
				mapa[v]=largest_error[0];
				largest_error.clear();
				v = atoi(tokens[0].c_str());

			}
				largest_error.push_back(atof(tokens[2].c_str()));



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
	float error_threshold = 0;
	for (unsigned int i = 0; i < argc; i++) {
		if (i == 1) {
			input_file += argv[i];
			if (input_file.substr(input_file.find_last_of(".") + 1) != "mhap")
				throw runtime_error("Input mhap files allowed");
		}
		if (i == 2) {
			error_threshold = atof(argv[i]);
			if (error_threshold>1)
				throw runtime_error("Error treshold cannot be greather than 1!");
		}
		if (i > 2)
			throw runtime_error("Too many arguments");
	}

	read(input_file, error_threshold);

	for(map<int, float >::const_iterator it = mapa.begin();
	    it != mapa.end(); ++it)
	{
		std::cout << it->first << " " << it->second << "\n";
	}

	exit(0);

}

