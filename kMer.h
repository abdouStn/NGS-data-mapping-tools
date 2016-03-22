#ifndef KMER_H
#define KMER_H

#include "sequenceFastX.h"

class KMer
{
private:
	size_t numero;
	size_t nbRepetitionsDansReads;
	std::vector<size_t> numeroReads;

    EncodedSequence2b* encodage; // avec reference?


public:
	KMer();
	KMer(size_t numero, EncodedSequence2b* e);
	KMer(const KMer& k); // const par copie
	KMer& operator=(const KMer& k);

	size_t getNumero() const;
	void setNumero(size_t n);
	
	size_t getNbRepetitionsDansReads() const;
	void setNbRepetitionsDansReads(size_t n);

	EncodedSequence2b* getEncodage() const;
	void setEncodage(EncodedSequence2b es);

	std::vector<size_t> getNumeroReads() const;


	~KMer();
	
};
#endif