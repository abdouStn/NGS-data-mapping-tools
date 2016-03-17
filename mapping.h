#ifndef MAPPING_H
#define MAPPING_H
#include "sequenceFastA.h"
#include "sequenceFastQ.h"
#include "suffixeTable.h"

class Mapping
{
private:
	SequenceFastA& genome;
	SequenceFastQ& reads;


    char** constuireKMers(size_t longueurKMers) const;

public:
	Mapping();
	Mapping(SequenceFastA& fa, SequenceFastQ& fq);

	void mapper() const;

	~Mapping();
};

#endif