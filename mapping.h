#ifndef MAPPING_H
#define MAPPING_H

#include "sequenceFastA.h"
#include "sequenceFastQ.h"
#include "suffixeTable.h"
#include "kMer.h"

class Mapping
{
private:
	SequenceFastA* genome;  // references??
	SequenceFastQ* reads;


    

public:
	Mapping();
	Mapping(SequenceFastA* fa, SequenceFastQ* fq);

	SequenceFastA* getGenome() const;
	SequenceFastQ* getReads() const;

	std::vector<KMer> constuireKMers(size_t longueurKMers) const;
	void mapper() const;

	~Mapping();
};

std::ostream & operator<<(std::ostream& os, const Mapping& m);

#endif