#ifndef ENCODED_SEQUENCE_H
#define ENCODED_SEQUENCE_H


#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream> //pour lire les fichiers
#include <vector>

//extern bool estValide(char nuc);

class EncodedSequence
{

protected:
	std::vector<std::string> lesIntitules; 
	std::vector<std::string> lesSeqQualites;
	std::vector<size_t> longueurDeSequences;      // de chaque sequence dans le fichier
	size_t longueur;  // revoir les methodes
	

	virtual void encodeSeq(const char* raw_seq) = 0; //virtual pure. abstraite
	virtual void loadAFasta(std::string leFichier) = 0;
public:
	unsigned char* tab;					// concatenation des sequences.
	/*EncodedSequence();
	EncodedSequence(const char* raw_seq);
	EncodedSequence(std::string leFichier);
	EncodedSequence(const EncodedSequence & es);  // constructeur par copie*/
	
	size_t totalLength() const;
	std::vector<size_t> length() const; 				// pour ne pas modifier l'instance courante.
	std::vector<std::string> getIntitules() const;
	std::vector<std::string> getLesSeqQualites() const;

	virtual void setSymbolAt(size_t i, char c) = 0;
	virtual EncodedSequence& reverseComplement() const = 0 ;
	virtual char operator[](size_t i) const = 0;   // remplace la methode getSymbolAt(size_t i). commence à 0 ou 1?
	//virtual EncodedSequence& operator()(size_t start, size_t end=0) const = 0;  //remplace la methode  getSubSequence() avec parametre par defaut
	virtual EncodedSequence& operator=(const EncodedSequence& es) = 0;  // operateur affectation.
	//virtual void print() = 0;
	virtual ~EncodedSequence();

};
std::ostream & operator<<(std::ostream& os, const EncodedSequence& es); // declaré en fonction car on peut pas modifier os. 

#endif
/*
Memoire dynamique
	const par copie
	destruction
	operateur par copie
*/