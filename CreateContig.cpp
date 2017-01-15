#include "MhapFormatter.h"
#include "BestOverlap.h"
#include "Edge.h"
#include "CreateContig.h"

#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <algorithm>
using namespace std;

CreateContig::CreateContig() {

}

CreateContig::~CreateContig() {

}

vector< vector<Edge> > CreateContig::bestContig(vector<Edge> ev) {
	vector<Edge> evE = ev;

	//BestOverlap *bo = new BestOverlap;
	//vector<Edge> ev = bo->createBestOverlap(edges);

	//vector<int> contig;
	//int startP = ev[0].idA;
	//contig.insert(contig.begin(), startP);

	vector<vector<Edge> > contigList;
	vector<Edge> longestContig;

	for (int startP = 0; startP < ev[ev.size()].idA; startP++) {
		vector<int> contig;
		vector<Edge> contigE;
		contig.insert(contig.begin(), startP);

		for (int i = 0; i < ev.size(); i++) {

			if (ev[i].idA == contig[contig.size() - 1]
					and ev[i].bhangMinus < ev[i].bhangPlus) { // idB je desno od contiga
				if (std::find(contig.begin(), contig.end(), ev[i].idB)
						== contig.end()) {
					// someName not in name, add it
					contig.insert(contig.end(), ev[i].idB);
				}
				//cout << ev[i].idA << ev[i].idB << "\n";
				ev.erase(ev.begin() + i);
				i--;
			}

			if (ev[i].idA == contig[0] and ev[i].bhangMinus > ev[i].bhangPlus) { // idB je lijevo od contiga
				if (std::find(contig.begin(), contig.end(), ev[i].idB)
						== contig.end()) {
					// someName not in name, add it
					contig.insert(contig.begin(), ev[i].idB);
				}

				//cout << ev[i].idA << ev[i].idB << "\n";
				ev.erase(ev.begin() + i);
				i--;
			}

			if (ev[i].idB == contig[contig.size() - 1]
					and ev[i].ahangMinus < ev[i].ahangPlus) { // idA je desno od contiga
				if (std::find(contig.begin(), contig.end(), ev[i].idA)
						== contig.end()) {
					// someName not in name, add it
					contig.insert(contig.end(), ev[i].idA);
				}

				//cout << ev[i].idA << ev[i].idB << "\n";
				ev.erase(ev.begin() + i);
				i--;
			}

			if (ev[i].idB == contig[0] and ev[i].ahangMinus > ev[i].ahangPlus) { // idA je lijevo od contiga
				if (std::find(contig.begin(), contig.end(), ev[i].idA)
						== contig.end()) {
					// someName not in name, add it
					contig.insert(contig.begin(), ev[i].idA);
				}

				//cout << ev[i].idA << ev[i].idB << "\n";
				ev.erase(ev.begin() + i);
				i--;
			}

			/*cout << ev[i].idA << "\t" << ev[i].idB << "\t" << ev[i].aStart << "\t" << ev[i].aEnd << "\t" << ev[i].aLength 
			 << "\t" << ev[i].ahangPlus << "\t" << ev[i].ahangMinus
			 << "\t" << ev[i].bStart << "\t" << ev[i].bEnd << "\t" << ev[i].bLength << "\t" << ev[i].bhangPlus
			 << "\t" << ev[i].bhangMinus
			 << "\t" << ev[i].overlapLength << "\t" << ev[i].orientationA << "\t" << ev[i].orientationB <<"\n";*/

		}

		/*for (int i = 0; i < contig.size(); i++) {

		 cout << contig[i] << "\t";
		 }
		 cout << "\n";*/

		for (int i = 0; i < contig.size(); i++) {
			for (int j = 0; j < evE.size(); j++) {
				if (contig[i] < contig[i + 1] && evE[j].idA == contig[i]
						&& evE[j].idB == contig[i + 1])
					contigE.push_back(evE[j]);
				else if (contig[i + 1] < contig[i]
						&& evE[j].idA == contig[i + 1]
						&& evE[j].idB == contig[i])
					contigE.push_back(evE[j]);

			}
		}

		contigList.push_back(contigE);

		/*for (int i = 0; i < contigE.size(); i++) {

		 cout << contigE[i].idA << "|" << contigE[i].idB << "|";
		 }
		 cout << "\n";*/

	}

	//cout << "Number of contigs:" << contigList.size() << "\n";
	vector< vector<Edge> > bestList;
	int size = 5;
	for (int i = 0; i < contigList.size(); i++) {

		//cout << contigList[i].size() << "\n";
		if (contigList[i].size() >= size) {
			bestList.push_back(contigList[i]);
		}
	}

	//ispisi navecu kontigu
	/*for (int i = 0; i < longestContig.size(); i++) {

		cout << longestContig[i].idA << "|" << longestContig[i].idB << "|";
	}
	cout << "\n";*/

	return bestList;
}

