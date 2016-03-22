#include "mapping.h"

//g++ -o test -Wall -ansi -pedantic -g encodedSequence.cpp encodedSequence2b.cpp sequenceFastX.cpp sequenceFastA.cpp test_Sequence.cpp


using namespace std;

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		cerr<<endl<<"Arguments invalides. Vous devez indiquer un fichier fasta (le genome) et un fastq (les reads)"<<endl;
		exit(1);	  	
	}

	cout<<endl<<endl<<"\t>>>>>>>>>>>Bienvenue dans mon programme de Mapping<<<<<<<<<<<<<<"<<endl;
				cout<<"\t\t\tDéveloppé par DIALLO Abdoulaye M1 BCD"<<endl<<endl;

	clock_t debut = clock();
	SequenceFastA genome((string)argv[1]);
	//cout << s1;
	clock_t duree = clock() - debut;
	cout << "temps de chargement fasta: "<<double(duree) /CLOCKS_PER_SEC<<" secondes"<<endl;
	SequenceFastQ reads((string)argv[2]); 
	//cout << s2;
	Mapping map(&genome, &reads);
	//cout<<map<<endl;
	

//-----------------------------------------------------------
	/*EncodedSequence2b s ((string)argv[1], true);
	EncodedSequence2b ss = s(5, 9);
	cout<<"subs à revoir\n"<<ss<<endl;


	//EncodedSequence2b es("ATCGa");

	vector<size_t> sa = buildSA(genome);
	cout<<"SA"<<endl;
	for (size_t i = 0; i < sa.size(); ++i)
	{
		cout<<sa.at(i)<< " ";
	}
	cout<<endl;

	cout<<"LCP"<<endl;
	vector<size_t> lcp = buildLCP(s, sa);
	for (size_t i = 0; i < lcp.size(); ++i)
	{
		cout<<lcp.at(i)<< " ";
	}
	cout<<endl;*/
//--------------------------------------------------------------------

	return 0;
}
