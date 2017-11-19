#ifndef MAPPING_H
#define MAPPING_H

#include "kMer.h"

class Mapping
{
private:
	SequenceFastA* genome;  // references??
	SequenceFastQ* reads;
	std::vector<KMer> kmers;
	size_t seuilSimularite;  // des kmers


    

public:
	Mapping();
	Mapping(SequenceFastA* fa, SequenceFastQ* fq, size_t seuil = 70);

	SequenceFastA* getGenome() const;
	SequenceFastQ* getReads() const;
	std::vector<KMer> getKmers() const;

	size_t getSeuilSimularite() const;
	void setSeuilSimularite( size_t s);
	size_t estPresent(EncodedSequence& es, size_t lgKmer ) const;
	void constuireKMers(size_t longueurKMers);
	void constuireKMers2(size_t longueurKMers);
	void mapAkmer(const std::vector<size_t>& SA, const std::vector<size_t>& LCP, const KMer& k, size_t lgKmer) const;
	void mapAkmerApproche(const std::vector<size_t>& SA, const std::vector<size_t>& LCP, const KMer& k, size_t lgKmer) const;
	void mapALLKmers(const std::vector<size_t>& SA, const std::vector<size_t>& LCP, size_t lgKmer) const;
	void printKmer(KMer& k, size_t lgKmer) const;
	size_t calculNumRead(size_t position) const;

	~Mapping();
};

std::ostream & operator<<(std::ostream& os, const Mapping& m);

#endif
