#include "sequenceFastA.h"

using namespace std;


/*
SequenceFastA::SequenceFastA(string titre, size_t lg)
{
	intitule = titre;
	longueur = lg;
	encodage = NULL;
}
*/
SequenceFastA::SequenceFastA(const char * seq)  // ne pas oublier le const 
{
	//intitule = titre;
	
	//EncodedSequence2b (seq);
}


SequenceFastA::SequenceFastA(const SequenceFastA & s)
{
	cout<<"SequenceFastA(const SequenceFastA & s) -- const par copie "<<endl;
	lesIntitules = s.lesIntitules;
	longueurDeSequences = s.longueurDeSequences;



	//encodage = * EncodedSequence2b((EncodedSequence2b)*s.encodage));
}

/*SequenceFastA& SequenceFastA::operator=(const SequenceFastA & s)
{
	if (this != &s)
	{
		lesIntitules = s.lesIntitules;
		longueurDeSequences = s.longueurDeSequences;
		*encodage = s.operator=(*s.encodage);	
	}
	return *this;	
}*/

SequenceFastA::SequenceFastA()
{
	longueurDeSequences = vector<size_t>() ;
	lesIntitules = vector<string>() ;
	encodage = NULL;
}

SequenceFastA::SequenceFastA(string leFichier)  // ne pas oublier le const 
{
	encodage = new EncodedSequence2b(leFichier, true);  // pour dire a encodedSequence de charger un fasta (loadAFasta)
	lesIntitules = this->getIntitules();
	longueurDeSequences = this->length();
	
}

SequenceFastA::~SequenceFastA()
{
	cout<<"~SequenceFastA()"<<endl;
}