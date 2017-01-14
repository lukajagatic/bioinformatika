#include "ContigMaker.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <Edge.h>

using namespace std;

ContigMaker::ContigMaker()
{

}

ContigMaker::~ContigMaker()
{
    //dtor
}
vector<string> reads;

vector<Edge> test;
Edge brid1;
Edge brid2;
Edge brid3;
Edge brid4;

/* Reads all corrected reads from given file and stores it into
the vector, reads ids are starting from 1 but they are stored with index 0.
Read 10 is stored at index 9.
*/

void ContigMaker::loadReads(string corr_reads){
    ifstream myfile(corr_reads.c_str());
    string line;
    int i;

    if (myfile.is_open()) {
		while (getline(myfile, line)) {
            if(line.find(">") < 1){
                continue;
            }else{
                reads.push_back(line.c_str());
            }
		}
    }else{
        cout << "Nesto";
    }
}

string ContigMaker::rComplement(string str){
string com("");

for (int i = str.size(); i >=0 ; i--){
	if(str[i] == 'A') {
		com += 'T';
	}
	if(str[i] == 'G') {
		com += 'C';
	}
	if(str[i] == 'C') {
		com += 'G';
	}
	if(str[i] == 'T') {
		com += 'A';
	}
}
return com;
}

string ContigMaker::makeContigs(string corr_reads, vector<Edge> bridovi){
string contig;
string returnContig;
int idCenter = 0;
Edge pbrid;
string pcontig1;
string pcontig2;

    loadReads(corr_reads);
//while(true){

 /*  for(int i=idCenter; i < bridovi.size(); i++){
    	if(bridovi[i].idA == bridovi[i+1].idA){
    		idCenter = i+1;
    		break;
		}
	}
*/
	pbrid = bridovi[idCenter];
    pcontig1 = reads[pbrid.idA-1];
    contig = pcontig1;
    pcontig2 = reads[pbrid.idB-1];

	if(pbrid.orientationB == 1){
		cout << "Spajam " << pbrid.idA << "+" << pbrid.idB;
		contig += rComplement(pcontig2.substr(0,pbrid.bStart));
		}else{
			//Ovo ne valja, provjeriti!!!!
			contig += pcontig2.substr(0,pbrid.bStart);
		}

	idCenter++;
	pbrid = bridovi[idCenter];
	pcontig1 = reads[pbrid.idB-1];
	cout << "Spajam " << pbrid.idA << "+" << pbrid.idB;
	contig = contig + pcontig1.substr(pbrid.bEnd,pbrid.bLength);

	idCenter++;
	pbrid = bridovi[idCenter];
	 pcontig2 = reads[pbrid.idB-1];

	if(pbrid.orientationB == 1){
		cout << "Spajam " << pbrid.idA << "+" << pbrid.idB;
		contig = pcontig2.substr(0,pbrid.bStart) + contig;
		}else{
			//Ovo ne valja, provjeriti!!!!
			contig += pcontig2.substr(0,pbrid.bStart);
		}
/*	for(int i=idCenter+1; i < bridovi.size(); i++){
		pbrid = bridovi[i];

		pcontig1 = reads[pbrid.idB-1];
		if(pbrid.orientationB == 1){
			cout << "Spajam " << pbrid.idA << "+" << pbrid.idB;
			contig = contig +(pcontig1.substr(0,pbrid.bStart));
		}else{
			//Ovo ne valja, provjeriti!!!!
			contig += pcontig1.substr(0,pbrid.bStart);
		}
	}

	for(int i=idCenter-1; i >= 0; i--){
		pbrid = bridovi[i];

		pcontig1 = reads[pbrid.idB-1];
		cout << "Spajam " << pbrid.idA << "+" << pbrid.idB;
		if(pbrid.orientationB == 1){

			contig = rComplement(pcontig1.substr(0,pbrid.bStart)) +contig;
		}else{
			//Ovo ne valja, provjeriti!!!!
			contig = pcontig1.substr(0,pbrid.bStart) + contig;
		}
	}
	returnContig += "> iid= " + idCenter + contig;
	if( (bridovi.size() - idCenter) < 5 ){
		break;
	}
}
*/

return contig;
}




/*int main(){

string fil;
string contig;



brid1.idA = 144;
brid1.idB = 159;
brid1.aStart = 0;
brid1.aEnd = 3657;
brid1.aLength = 9975;
brid1.bStart =3292;
brid1.bEnd = 9474;
brid1.bLength = 9475;
brid1.orientationB = 1;




brid2.idA = 112;
brid2.idB = 134;
brid2.aStart = 1990;
brid2.aEnd = 7329;
brid2.aLength = 7332;
brid2.bStart = 0;
brid2.bEnd = 5353;
brid2.bLength = 5373;
brid2.orientationB = 0;




brid3.idA = 95;
brid3.idB = 133;
brid3.aStart = 3270;
brid3.aEnd = 5480;
brid3.aLength = 5481;
brid3.bStart =8646;
brid3.bEnd = 10938;
brid3.bLength = 10939;
brid3.orientationB = 1;


brid3.idA = 1;
brid3.idB = 99;
brid3.aStart = 951;
brid3.aEnd = 8441;
brid3.aLength = 8442;
brid3.bStart =1895;
brid3.bEnd = 9372;
brid3.bLength = 9386;
brid3.orientationB = 1;

brid4.idA = 99;
brid4.idB = 159;
brid4.aStart = 1680;
brid4.aEnd = 9384;
brid4.aLength = 9386;
brid4.bStart =1928;
brid4.bEnd = 9474;
brid4.bLength = 9475;
brid4.orientationB = 1;

test.push_back(brid1);
test.push_back(brid2);
test.push_back(brid3);
//test.push_back(brid4);


fil = "lambda_corrected_reads.fasta";

contig = makeContigs(fil, test);


ofstream myfile("test.fasta");
myfile << "> iid = 1 \n";
myfile << contig;

}

*/

