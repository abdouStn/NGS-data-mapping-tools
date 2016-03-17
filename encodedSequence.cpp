#include "encodedSequence.h"

using namespace std;

vector<size_t> EncodedSequence::length() const
{
	return longueurDeSequences;
}

size_t EncodedSequence::totalLength() const
{
	size_t longueur = (size_t) 0;
	for (size_t i = 0; i < longueurDeSequences.size(); ++i)
	{
		longueur += longueurDeSequences.at(i);
	}
	return longueur;
}

vector<string> EncodedSequence::getIntitules() const
{
	return lesIntitules;
}

vector<string> EncodedSequence::getLesSeqQualites() const
{
	return lesSeqQualites;
}


EncodedSequence::~EncodedSequence()
{
	cout<<"~EncodedSequence()"<<endl;
}

ostream & operator<<(ostream& os, const EncodedSequence & es)
{
	for(size_t i=0;i<es.totalLength();i++)
	{
		os<<es[i];
	}	
	return os;
}