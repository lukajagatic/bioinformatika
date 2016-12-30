/*
 * Compression.cpp
 *
 *  Created on: Dec 30, 2016
 *      Author: luka
 */

#include "Compression.h"
#include "vector"

string fasta;
string mhap;

Compression::Compression(string fasta_file, string mhap_file) {
	fasta = fasta_file;
	mhap = mhap_file;
}

Compression::~Compression() {
	// TODO Auto-generated destructor stub
}

void parseMhap() {
//ucitaj bridove iz mhap datoteke
	ifstream myfile(mhap.c_str());
	string line;

	if (myfile.is_open()) {

		int j = 0;
		int i = 0;
		DataBase *data = DataBase::getInstance();

		while (getline(myfile, line)) {
			i++;
			Brid* brid = new Brid;
			brid->edgeInfo = line;
			std::vector<std::string> list = split(line, ' ');
			brid->readA = atoi(list[0].c_str());
			brid->readB = atoi(list[1].c_str());

			calculateEdge(atoi(list[4].c_str()), atoi(list[5].c_str()),
					atoi(list[6].c_str()), atoi(list[7].c_str()),
					atoi(list[8].c_str()), atoi(list[9].c_str()),
					atoi(list[10].c_str()), atoi(list[11].c_str()),
					atoi(list[0].c_str()), atoi(list[1].c_str()), brid);

			checkOrientation(atoi(list[4].c_str()), atoi(list[8].c_str()),
					brid);

			data->putEdge(brid);
			data->makeNeighbors(brid->readA, brid->readB);

		}
		myfile.close();

	}

	else
		cout << "Unable to open file";

}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
