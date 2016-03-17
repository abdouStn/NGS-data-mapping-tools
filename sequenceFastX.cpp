#include "sequenceFastX.h"
using namespace std;

/*
SequenceFastX::sequenceFastX(const SequenceFastX & s)
{
	lesIntitules = s.lesIntitules;
	longueurDeSequences = s.longueurDeSequences;
	encodage (p.encodage);
}*/

vector<size_t> SequenceFastX::length() const
{
	return encodage->length();
}

size_t SequenceFastX::totalLength() const
{
	return encodage->totalLength();
}

vector<string> SequenceFastX::getIntitules() const
{
	return encodage->getIntitules();
}

SequenceFastX::~SequenceFastX()
{
	cout<<"~SequenceFastX()"<<endl;
	encodage->~EncodedSequence(); // appel au destructeur
}

ostream & operator<<(ostream& os, const SequenceFastX & s)
{
	os<<s.getIntitules().size()<<" seq Fasta: "<<endl;
	for (size_t i = 0; i < s.getIntitules().size(); ++i)
	{
		os<<s.getIntitules().at(i)<<endl;
	}
	os<<*(s.encodage)<<endl;
	
	return os;
}