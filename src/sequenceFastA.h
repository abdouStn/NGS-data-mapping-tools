#include "sequenceFastX.h"


class SequenceFastA : virtual public SequenceFastX
{

private:
	

public:
	SequenceFastA();
	//SequenceFastA(std::string titre, size_t lg);
	SequenceFastA(const char * seq);
	SequenceFastA(std::string leFichier);
	SequenceFastA(const SequenceFastA & s);
	//virtual SequenceFastX& operator=(const SequenceFastX& s);
	
	
	virtual ~SequenceFastA();

};