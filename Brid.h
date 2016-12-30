/*
 * Brid.h
 *
 *  Created on: Dec 30, 2016
 *      Author: luka
 */

#ifndef BRID_H_
#define BRID_H_

//svi podaci parsirani iz mhap datoteke

class Brid {
public:
	Brid();
	virtual ~Brid();

	int readA; //id prvi fragment
	int readB; //id drugi fragment
	int bhang;
	int aStart;
	int aEnd;
	int bStart;
	int bEnd;
	int APlus;
	int AMinus;
	int BPlus;
	int bMinus;
	int aLenghth;
	int bLenght;
	int oLenght; //lenght of overlap
	int edgeLenght; //lenght of edge
	int orientationA; //orientation of readA
	int orientationB; //orientation of readB
	int oB;
	int first;
};

#endif /* BRID_H_ */
