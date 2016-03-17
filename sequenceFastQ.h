#include "sequenceFastX.h"


class SequenceFastQ : virtual public SequenceFastX
{

private:
	

public:
	SequenceFastQ();
	//SequenceFastQ(std::string titre, size_t lg);
	SequenceFastQ(std::string leFichier);
	
	virtual void print();	

	virtual ~SequenceFastQ();

};