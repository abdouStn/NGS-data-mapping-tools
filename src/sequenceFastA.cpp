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

SequenceFastA::SequenceFastA()
{
	longueurDeSequences = vector<size_t>();
	lesIntitules = vector<string>();
	encodage = NULL;
	//longueur = 0;
}


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
/*
SequenceFastX& SequenceFastA::operator=(const SequenceFastX& s)
{
	cout<<__FUNCTION__<<endl;
	if (this != &s)
	{
		lesIntitules = s.getLesIntitules();
		longueurDeSequences = s.getLongueurDeSequences();
		longueur = s.getLongueur();
		*encodage = s.operator=(*s.encodage);	
	}
	return *this;	
}
*/
SequenceFastA::SequenceFastA(string leFichier)  // ne pas oublier le const 
{
	encodage = new EncodedSequence2b(leFichier, true);  // pour dire a encodedSequence de charger un fasta (loadAFasta)
	lesIntitules = this->getLesIntitules();
	longueurDeSequences = this->getLongueurDeSequences();
	
}

SequenceFastA::~SequenceFastA()
{
	//cout<<"~SequenceFastA()"<<endl;
	
	/*if (encodage!=NULL)
	{
		delete encodage;	
	}*/
	
}