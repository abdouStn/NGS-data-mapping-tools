#include "sequenceFastA.h"
#include "sequenceFastQ.h"
#include "suffixeTable.h"

//g++ -o test -Wall -ansi -pedantic -g encodedSequence.cpp encodedSequence2b.cpp sequenceFastX.cpp sequenceFastA.cpp test_Sequence.cpp


using namespace std;

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		cerr<<endl<<"Arguments invalides. Vous devez indiquer un fichier fasta (le genome) et un fastq (les reads)"<<endl;
		exit(1);	  	
	}

	cout<<endl<<endl<<"\t>>>>>>>>>>>Bienvenue dans mon programme de Mapping<<<<<<<<<<<<<<"<<endl;
				cout<<"\t\t\tDévéloppé par DIALLO Abdoulaye M1 BCD"<<endl<<endl;

	SequenceFastA s1((string)argv[1]);
	//cout << s1;

	//SequenceFastQ s2((string)argv[1]); s2.print();

	//EncodedSequence2b es("ATCGa");

	vector<size_t> v = builtSA(s1);
	cout<<"SA"<<endl;
	for (size_t i = 0; i < v.size()/4; ++i)
	{
		cout<<v.at(i)<< " ";
	}
	cout<<endl;

	return 0;
}
