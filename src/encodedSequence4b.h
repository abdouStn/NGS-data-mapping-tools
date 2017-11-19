#ifndef ENCODED_SEQUENCE_4B_H
#define ENCODED_SEQUENCE_4B_H


#include "encodedSequence.h"

class EncodedSequence4b : EncodedSequence
{
private:
	virtual void encodeSeq(const char* raw_seq);
	virtual void loadAFasta(std::string leFichier);
	
public:
	EncodedSequence4b();
	EncodedSequence4b(const char* raw_seq);
	EncodedSequence4b(std::string leFichier);
	EncodedSequence4b(const EncodedSequence4b & es);  // constructeur par copie

	virtual void print();
	/*virtual void setSymbolAt(size_t i, char c);
	virtual EncodedSequence& reverseComplement() const ;
	virtual char operator[](size_t i) const;   // remplace la methode getSymbolAt(size_t i). commence à 0 ou 1?
	virtual EncodedSequence& operator()(size_t start, size_t end=0) const ;  //remplace la methode  getSubSequence() avec parametre par defaut
	virtual EncodedSequence& operator=(const EncodedSequence& es);  // operateur affectation.	*/

	virtual ~EncodedSequence4b();

};

#endif