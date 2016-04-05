#include "kMer.h"
using namespace std;

KMer::KMer():numero(0), nbRepetitionsDansReads(1), positionDebutDansReads(0), positionsMappees(), simularites(), numeroReads(){
	//EncodedSequence2b e;	encodage = e;
}


KMer::KMer(size_t numero, size_t positionDebDansReads) : numero(numero), nbRepetitionsDansReads(1) , positionDebutDansReads(positionDebDansReads), positionsMappees(), simularites(), numeroReads()
{
}

KMer::KMer(const KMer& k) // const par copie
{
	//cout<<__FUNCTION__<<" -- const par copie"<<endl;
	//cout<<k<<endl;
	numero = k.numero;
	nbRepetitionsDansReads = k.nbRepetitionsDansReads;
	numeroReads = k.numeroReads;
	positionDebutDansReads = k.positionDebutDansReads;
	//encodage = new EncodedSequence2b(*(k.encodage));   // appel const par copie.

}

KMer& KMer::operator=(const KMer& k)
{
	cout<<__FUNCTION__<<" -- operateur affectation"<<endl;
	
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
void KMer::incrementeNbRepetitionsDansReads()
{
	nbRepetitionsDansReads++;	
}

vector<size_t> KMer::getNumeroReads() const {return numeroReads;}

size_t KMer::getPositionDebutReads() const
{
	return positionDebutDansReads;
}

void KMer::setPositionDebutReads( size_t p)
{
	positionDebutDansReads = p;
}

vector<size_t> KMer::getPositionsMappees() const
{	
	return positionsMappees;
}

vector<size_t> KMer::getSimularites() const
{
	return simularites;
}



KMer::~KMer()
{
	//cout<<"~KMer()"<<endl;
	/*if (encodage) {
		delete encodage;
	}*/
}

ostream& operator<<(ostream& os, const KMer& k)
{
	os<< " Kmer "<<k.getNumero()<<" reads: { ";
	for (size_t i = 0; i < k.numeroReads.size(); ++i)
	{
		if (i==0) // n'afficher qu'a un exemplaire le numero du read contenant le kmer
		{
			os<<k.numeroReads[i]<<" ";
		}
		else if (k.numeroReads[i] != k.numeroReads[i-1])
		{
			os<<k.numeroReads[i]<<" ";
		}
	}
	os<<"}";
	return os;

}