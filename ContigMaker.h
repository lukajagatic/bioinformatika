

#ifndef CONTIGMAKER_H_
#define CONTIGMAKER_H_
#include<vector>
#include <string>
#include "Edge.h"
using namespace std;


class ContigMaker
{
    public:
    	ContigMaker();
        virtual ~ContigMaker();
        string makeContigs(string, vector<Edge>);
        string rComplement(string);
        void loadReads(string);

    protected:

    private:
};

#endif // CONTIGMAKER_H
