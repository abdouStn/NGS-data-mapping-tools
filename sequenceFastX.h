#ifndef SEQUENCE_FASTX_H
#define SEQUENCE_FASTX_H

#include "encodedSequence2b.h"
//#include "encodedSequence4b.h"


class SequenceFastX
{

protected:
	std::vector<std::string> lesIntitules; 
	std::vector<size_t> longueurDeSequences;      // de chaque sequence dans le fichier
	//size_t longueur;
		

public:
	EncodedSequence* encodage;
	/*SequenceFastX();
	SequenceFastX(std::string titre, size_t lg);
	SequenceFastX(std::string titre, const char * seq);
	SequenceFastX(std::string titre, std::string leFichier);
	*/
	
	//SequenceFastX(const SequenceFastX & s);

	size_t totalLength() const;
	std::vector<size_t> getLongueurDeSequences() const; 				// taille de chaque sequence dans le fichier.
	std::vector<std::string> getLesIntitules() const;
	void setLongueurDeSequences(std::vector<size_t> v);
	void setLesIntitules(std::vector<std::string> v);
	void setLongueur(size_t l);

	//virtual SequenceFastX& operator=(const SequenceFastX& s) = 0;

	virtual ~SequenceFastX();

};
std::ostream & operator<<(std::ostream& os, const SequenceFastX& s); 

#endif