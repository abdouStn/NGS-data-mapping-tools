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
	//virtual SequenceFastA& operator=(const SequenceFastA & s);
	
	
	virtual ~SequenceFastA();

};