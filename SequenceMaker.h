

#ifndef CONTIGMAKER_H_
#define CONTIGMAKER_H_
#include<vector>
#include <string>
#include "Edge.h"
using namespace std;


class SequenceMaker
{
    public:
    	SequenceMaker();
        virtual ~SequenceMaker();
        string makeSequence(string, vector<pair<bool, Edge> >);
        string rComplement(string);
        void loadReads(string);

    protected:

    private:
};

#endif // CONTIGMAKER_H
