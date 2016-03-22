#include "mapping.h"
using namespace std;

Mapping::Mapping()
{
	genome = new SequenceFastA();
	reads = new SequenceFastQ();
}

Mapping::Mapping(SequenceFastA* fa, SequenceFastQ* fq)
{
	genome = fa;
	reads = fq;
}

vector<KMer> Mapping::constuireKMers(size_t longueurKMers) const
{
	vector<KMer> v;

	for (size_t i = 0; i < reads->totalLength()-longueurKMers ; ++i)
	{
		//EncodedSequence2b es = *reads(i,i+longueurKMers);	

	}

	return v;
}

void Mapping::mapper() const
{

}

SequenceFastA* Mapping::getGenome() const
{
	return genome;
}

SequenceFastQ* Mapping::getReads() const
{
	return reads;
}


Mapping::~Mapping()
{
	//genome->~SequenceFastA();
	//reads->~SequenceFastQ();
}

ostream & operator<<(ostream& os, const Mapping& m)
{
	os<<*(m.getGenome())<<endl<<*(m.getReads())<<endl;	
	return os;
}