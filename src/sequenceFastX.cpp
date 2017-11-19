#include "sequenceFastX.h"
using namespace std;

/*
SequenceFastX::sequenceFastX(const SequenceFastX & s)
{
	lesIntitules = s.lesIntitules;
	longueurDeSequences = s.longueurDeSequences;
	encodage (p.encodage);
}*/

vector<size_t> SequenceFastX::getLongueurDeSequences() const
{
	return encodage->length();
}

size_t SequenceFastX::totalLength() const
{
	return encodage->totalLength();
}

vector<string> SequenceFastX::getLesIntitules() const
{
	return encodage->getIntitules();
}

void SequenceFastX::setLongueurDeSequences(vector<size_t> v)
{
	longueurDeSequences = v;
}
void SequenceFastX::setLesIntitules(vector<string> v)
{
	lesIntitules = v;
	
}

void SequenceFastX::setLongueur(size_t l)
{
	//longueur = l;
}



SequenceFastX::~SequenceFastX()
{
	//cout<<"~SequenceFastX()"<<endl;
	if (encodage!=NULL)
	{
		delete encodage;	
	}
}

ostream & operator<<(ostream& os, const SequenceFastX & s)
{
	os<<s.getLesIntitules().size()<<" seq Fasta: "<<endl;
	for (size_t i = 0; i < s.getLesIntitules().size(); ++i)
	{
		os<<s.getLesIntitules().at(i)<<endl;
	}
	os<<*(s.encodage)<<endl;
	
	return os;
}