#ifndef KMER_H
#define KMER_H

#include "suffixeTable.h"

class KMer
{
private:
	size_t numero;
	size_t nbRepetitionsDansReads;
	
	size_t positionDebutDansReads; // pour la sequence du kmer, au lieu de stocker la sequence kmer je garde juste la pos du premier nuc dans les reads.

	std::vector<size_t> positionsMappees;  // dans le genome si la simularité est superieur au seuil   
	std::vector<size_t> simularites;   
	

    //EncodedSequence* encodage; // avec reference?
    

public:
	std::vector<size_t> numeroReads;  // la methode ne marche pas ????
	KMer();
	KMer(size_t numero, size_t positionDebDansReads);
	KMer(const KMer& k); // const par copie
	KMer& operator=(const KMer& k);


	size_t getNumero() const;
	void setNumero(size_t n);
	
	size_t getNbRepetitionsDansReads() const;
	void incrementeNbRepetitionsDansReads();
	
	size_t getPositionDebutReads() const;
	void setPositionDebutReads( size_t p);

	
	std::vector<size_t> getNumeroReads() const;
	std::vector<size_t> getPositionsMappees() const;
	std::vector<size_t> getSimularites() const;


	~KMer();
	
};
std::ostream & operator<<(std::ostream& os, const KMer& k); 
#endif