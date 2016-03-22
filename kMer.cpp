#include "kMer.h"
using namespace std;

KMer::KMer()
{
	numero = 0;
	//EncodedSequence2b e;	encodage = e;
	encodage = new EncodedSequence2b();
}

KMer::KMer(size_t numero, EncodedSequence2b* e)
{
	this->numero = numero;
	encodage = e;
}

KMer::KMer(const KMer& k) // const par copie
{
	cout<<"KMer(const KMer& k) -- const par copie"<<endl;
}

KMer& KMer::operator=(const KMer& k)
{
	cout<<"operator=(const KMer& k) -- operateur affectation"<<endl;
	
	return *this;
}

size_t KMer::getNumero() const
{
	return numero;
}
void KMer::setNumero(size_t n)
{
	numero = n;
}
	
size_t KMer::getNbRepetitionsDansReads() const
{
	return nbRepetitionsDansReads;
}
void KMer::setNbRepetitionsDansReads(size_t n)
{
	nbRepetitionsDansReads = n;	
}

EncodedSequence2b* KMer::getEncodage() const
{
	return encodage;
}
void KMer::setEncodage(EncodedSequence2b es)
{
	*encodage = es;    // appel a l'operateur d'affectation
}

vector<size_t> KMer::getNumeroReads() const
{
	return numeroReads; 
}

KMer::~KMer()
{
	encodage->~EncodedSequence2b();
}
