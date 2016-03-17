#include "sequenceFastQ.h"
using namespace std;

SequenceFastQ::SequenceFastQ()
{
	longueurDeSequences = vector<size_t>() ;
	lesIntitules = vector<string>() ;
	encodage = NULL;
}

SequenceFastQ::SequenceFastQ(string leFichier)
{
	encodage = new EncodedSequence2b(leFichier, false);
	lesIntitules = this->getIntitules();
	longueurDeSequences = this->length();
}

void SequenceFastQ::print()
{
	cout<<lesIntitules.size()<<" seq Fastq: "<<endl;
	for (size_t i = 0; i < lesIntitules.size(); ++i)
	{
		cout<<lesIntitules.at(i)<<endl;
	}

	cout<<*encodage<<endl;
}	

SequenceFastQ::~SequenceFastQ()
{
	cout<<"~SequenceFastQ()"<<endl;
}