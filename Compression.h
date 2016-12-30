/*
 * Compression.h
 *
 *  Created on: Dec 30, 2016
 *      Author: luka
 */

#ifndef COMPRESSION_H_
#define COMPRESSION_H_

#include "string.h"

using namespace std;
class Compression {
public:
	Compression(string fasta_file, string mhap_file);
	virtual ~Compression();
};

#endif /* COMPRESSION_H_ */
