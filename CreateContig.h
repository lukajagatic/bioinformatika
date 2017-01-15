#ifndef CREATECONTIG_H_
#define CREATECONTIG_H_

#include <vector>
#include <string>
#include "Edge.h"
using namespace std;

class CreateContig {
public:
	CreateContig();
	virtual ~CreateContig();
	vector<vector<Edge> > bestContig(vector<Edge>);

};

#endif // CREATECONTIG_H
