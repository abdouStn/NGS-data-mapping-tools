#ifndef SEQUENCE_FASTX_H
#define SEQUENCE_FASTX_H

#include "encodedSequence2b.h"
//#include "encodedSequence4b.h"

class SequenceFastX
{

protected:
	std::vector<std::string> lesIntitules; 
	std::vector<size_t> longueurDeSequences;      // de chaque sequence dans le fichier
	

public:
	EncodedSequence* encodage;
	/*SequenceFastX();
	SequenceFastX(std::string titre, size_t lg);
	SequenceFastX(std::string titre, const char * seq);
	SequenceFastX(std::string titre, std::string leFichier);
	*/
	//SequenceFastX(const SequenceFastX & s);

	std::vector<size_t> length() const; 				// taille de chaque sequence dans le fichier.
	size_t totalLength() const;
	std::vector<std::string> getIntitules() const;
	
	virtual ~SequenceFastX();

};
std::ostream & operator<<(std::ostream& os, const SequenceFastX& s); 

#endif