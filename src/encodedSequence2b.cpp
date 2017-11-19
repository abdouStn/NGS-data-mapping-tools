#include "encodedSequence2b.h"
using namespace std;


//-------------------------------- Des fonctions ------------------------------------
bool estValide(char nuc)
{
	return (nuc=='A') || (nuc=='a')
		|| (nuc=='C') || (nuc=='c')
		|| (nuc=='G') || (nuc=='g')
		|| (nuc=='T') || (nuc=='t');
}

size_t donneOctect(size_t i)
{
	return i/4;
}

size_t donnePositionOctect(size_t i)
{
	return (3-(i%4))<<1;  // <<1 est = *2; %4  == &3
}

unsigned char encode(char nuc)  
{
	if ((nuc=='A') || (nuc=='a'))
	{
		return 0;
	}
	if ((nuc=='C') || (nuc=='c'))
	{
		return 1;
	}
	if ((nuc=='G') || (nuc=='g'))
	{
		return 2;
	}
	if ((nuc=='T') || (nuc=='t'))
	{
		return 3;
	}
	return 0;
}

char decode(unsigned char nuc)    // ou char ???
{
	if (nuc==0)
	{
		return 'A';
	}
	if (nuc==1)
	{
		return 'C';
	}
	if (nuc==2)
	{
		return 'G';
	}
	if (nuc==3)
	{
		return 'T';
	}
	return 'N';
}

void printOctet(unsigned char x) 
{
	for (unsigned char i = 8; i > 0; i--) {
       cout << (i | 0 ? 1 : 0);
       //i >>= 1;
    }
	cout << endl;
}

void printOctet2(unsigned char x, size_t p) 
{
	unsigned char i = 128;
	while (i) {
		cout << (x & i ? 1 : 0);
		i >>= 1;
	}
	cout << endl;
	for (i = 8; i > p; i--) {
       cout << (i <= p+2 ? '*' : ' ');
    }
	cout << endl;
}

//----------------------------- Les Methodes ------------------------------

void EncodedSequence2b::encodeSeq(const char* raw_seq)
{
	if (raw_seq != NULL)
	{	
		while(raw_seq[longueur] != '\0')
		{
			/*if (!estValide(raw_seq[longueur]))
			{
				cout<<"Le caractère " << raw_seq[longueur] << " est invalide !!" <<endl;
			}*/
			longueur++;
		}
		longueurDeSequences.push_back(longueur);
		cout<<"longueur "<<longueur<<endl;

		tab = new unsigned char[longueur/4 + (longueur%4 != 0)]; // [longueur/2 + (longueur%2 != 0)]; pour 4 bits
		
		// remplissage du tableau
		size_t p = (size_t) -1;
		
		for (size_t i = 0; i < longueur; ++i)
		{
			if (!(i%4)) //si est multiple de 4. si 4bits !(i&1)
			{
				tab[++p] = 0;
			}
			tab[p]|=encode(raw_seq[i])<<donnePositionOctect(i) ; // le | fait office de masque. <<1 est = *2;  ((!(i&1))<<2) pour version 2 bits 
		}
	}
	
}

void EncodedSequence2b::loadAFasta(string leFichier)
{
	//lecture du fichier
	ifstream fichier(leFichier.c_str(), ios::in); 
	if (fichier.fail())
	{
		cerr<<endl<<"Impossible d'ouvrir le fichier : "<<leFichier<<endl<<endl;
		exit(0);
	}
	string ligne;
	size_t it = (size_t) 0, p = (size_t) -1, nbSeq = (size_t) 0; 
	while(getline(fichier, ligne))
	{
		if (ligne[0] == '>')
    	{
    		lesIntitules.push_back(ligne);
    		longueurDeSequences.push_back(0);
    		nbSeq++;
    	}
    	else
    	{
    		for (size_t i = 0; i < ligne.size(); ++i)
    		{
    			if (estValide(ligne[i]))
    			{
    				longueur++;
    				longueurDeSequences.at(nbSeq-1)++;
    			}
    		}
    	}	
	}
	cout<<nbSeq << " sequences"<<endl;

	//on se replace en debut de fichier
	fichier.seekg(0, ios::beg);
	//cout <<"position dans fichier: "<< fichier.tellg() <<endl;
	if((int)fichier.tellg() != 0)  //si ça marche pas on tente un clear
    {
            fichier.clear();
            fichier.seekg(0, ios::beg);
            //cout << endl << "On se trouve au " << fichier.tellg() << "ieme octet." << endl;
    }

    //longueur = totalLength();
    cout<<"Longueur de la sequence = ";
	for (size_t i = 0; i < longueurDeSequences.size(); ++i)
	{
		//longueur += longueurDeSequences.at(i);
		cout<<longueurDeSequences.at(i)<<" ";
	}
	cout<<" total= "<<longueur<<endl;

	tab = new unsigned char[longueur/4 + (longueur%4 != 0)];   // on alloue de la memoire
		
	while(getline(fichier, ligne))
	{
		if (ligne[0] != '>')
    	{
    		for (size_t i = 0; i < ligne.size(); ++i)
    		{
    			if (estValide(ligne[i]))
    			{
    				if (!(it%4)) //si est multiple de 4. si 4bits !(i&1)
					{				
						tab[++p] = 0;				
					}
					tab[p]|=encode(ligne[i])<<donnePositionOctect(it) ; // <<1 est = *2;  ((!(i&1))<<2) pour version 2 bits 
					it++;
		    	}
    		}	
    	}
	}
	fichier.close();
	/*
		if(!is.is_open()) // passage en arg de fonction ifstream &s
		if(n)
		{
			n = 0;
			n=0;
			delete[] tab; tab = NULL;
		}
		streampos p = is.tellg(); char c;
		while(!is.eof() && isValide(c=is.getchar())) { n += !isspace(c);}
		if(n)
		{
			tab = new unsigned char [n/4 + ((n&3)>0)]
			is.seekg(p);
			size_t i = 0;
			while(!is.eof() && isValide(c=is.getchar()))
			{
				...
			}
		}
	*/
}

/*
	void EncSeq::write(ostream & os)
	{
		for(size_t i = 0; i<n; i++)
		{
			os<<operator[](i);
		}
	}

*/

void EncodedSequence2b::loadAFastq(string leFichier)
{
	//lecture du fichier
	ifstream fichier(leFichier.c_str(), ios::in); 
	if (fichier.fail())
	{
		cerr<<endl<<"Impossible d'ouvrir le fichier : "<<leFichier<<endl<<endl;
		exit(0);
	}
	string ligne;
	size_t it = (size_t) 0, p = (size_t) -1, nbSeq = (size_t) 0, numligne = (size_t) 1; 
	
	while(getline(fichier, ligne))
	{
		
		if ((ligne[0] == '@') and (numligne%4 == 1))
    	{
    		lesIntitules.push_back(ligne);
    		longueurDeSequences.push_back(0);
    		//cout<<ligne<< " "<<numligne<<endl;
    		nbSeq++;
    		
    	}
    	else if ((estValide(ligne[0])) and (numligne%4 == 2 ))
    	{
    		for (size_t i = 0; i < ligne.size(); ++i)
    		{
    			if (estValide(ligne[i]))
    			{
    				longueur++;
    				longueurDeSequences.at(nbSeq-1)++;
    			}
    		}
    		//cout<<ligne<<" "<<numligne<<endl;
    	}
    	else if (ligne[0] == '+' and (numligne%4 == 3))
    	{
    		//cout<<ligne<<" "<<numligne<<endl;
    		//continue;
    	}
    	else if ((ligne.size() == longueurDeSequences.at(nbSeq-1)) and (numligne%4 == 0))
    	{
    		//cout<<ligne.size() <<" "<<longueurDeSequences.at(nbSeq-1)<<endl;
    		lesSeqQualites.push_back(ligne);
    		//cout<<ligne<<" "<<numligne<<endl;
    	}
    	numligne++;	
	}
	
	cout<<nbSeq << " sequences"<<endl;
	if ((nbSeq != lesIntitules.size()) || (nbSeq != lesSeqQualites.size()))
	{
		cout<<"erreur dans le fichier fastq "<<nbSeq<<" "<<lesSeqQualites.size()<<endl;
	}
	
	//on se replace en debut de fichier
	fichier.seekg(0, ios::beg);
	//cout <<"position dans fichier: "<< fichier.tellg() <<endl;
	if((int)fichier.tellg() != 0)  //si ça marche pas on tente un clear
    {
        fichier.clear();
        fichier.seekg(0, ios::beg);
    }

    //longueur = totalLength(); 
    numligne = (size_t) 1;
    cout<<"Longueur total de la sequence = "<<longueur<<endl;

	tab = new unsigned char[longueur/4 + (longueur%4 != 0)];   // on alloue de la memoire
		
	while(getline(fichier, ligne))
	{
		if ((estValide(ligne[0])) and (numligne%4 == 2 ))
    	{
    		for (size_t i = 0; i < ligne.size(); ++i)
    		{
    			if (estValide(ligne[i]))
    			{
    				if (!(it%4)) //si est multiple de 4. si 4bits !(i&1)
					{				
						tab[++p] = 0;				
					}
					tab[p]|=encode(ligne[i])<<donnePositionOctect(it) ; // <<1 est = *2;  ((!(i&1))<<2) pour version 2 bits 
					it++;
		    	}
    		}	
    	}
    	numligne++;
	}
	fichier.close();

}

// -------------------------------------constructeurs --------------------------

EncodedSequence2b::EncodedSequence2b() 
{	
	longueur = 0;
	longueurDeSequences = vector<size_t>() ;
	lesIntitules = vector<string>() ;
	tab = NULL;
	//cout<<"EncodedSequence2b()"<<endl;
}

EncodedSequence2b::EncodedSequence2b(const char* raw_seq)
{
	longueur = 0;
	longueurDeSequences = vector<size_t>() ;
	lesIntitules = vector<string>() ;
	tab = NULL;
	cout<<"EncodedSequence2b(const char* raw_seq)"<<endl;
	encodeSeq(raw_seq);
}

EncodedSequence2b::EncodedSequence2b(string leFichier, bool isAFasta) 
{
	longueur = 0;
	longueurDeSequences = vector<size_t>() ;
	lesIntitules = vector<string>() ;
	tab = NULL;
	//cout<<"encodedSequence2b(string, bool)"<<endl;

	if (isAFasta)
	{
		loadAFasta(leFichier);
	}
	else if (!isAFasta)
	{
		lesSeqQualites = vector<string>();
		loadAFastq(leFichier);
	}
	else
		cout<<"Je ne sais pas si c'est un fasta ou un fastq"<<endl;		
}

EncodedSequence2b::EncodedSequence2b(const EncodedSequence& es)  // constructeur par copie ()
{
	//cout<<__FUNCTION__<<" - constructeur par copie"<<endl;
	
	longueur = es.totalLength();
	lesIntitules = es.getIntitules();
	lesSeqQualites = es.getLesSeqQualites();
	longueurDeSequences = es.length();   // vector

	if (longueur)
	{
		size_t lg = totalLength()/4 + (totalLength()%4 != 0) ;
		tab = new unsigned char[lg];   // on alloue de la memoire
		for (size_t i = 0; i < lg; ++i)
		{
			tab[i] = es.tab[i];
		}
	}
	/*
	tab = new unsigned char[es.totalLength()/4 + (es.totalLength()%4 != 0)];   // on alloue de la memoire

	for (size_t i = 0; i < es.totalLength()/4 + (es.totalLength()%4 != 0); ++i)
	{
		tab[i] = es.tab[i];
	}*/

}

void EncodedSequence2b::setSymbolAt(size_t i, char c)  //ne marche pas tres bien.
{
	if (estValide(c))
	{
		//printOctet(c);
		unsigned char &m = tab[donneOctect(i)];   // on recupere l'octect
		m &= ~(3 << donnePositionOctect(i));		// On met le masque 3 (11) a la place des 2  bites puis on remet tout a zero (negation)
		m |= encode(c)<<donnePositionOctect(i); //  Ensuite un ou avec le caract concerné  <<1 est = *2;  ((!(i&1))<<2) pour version 2 bits 
	}
	else
	{
		cout<<"le caractère "<<c<<"n'est pas valide"<<endl;
	}
}

EncodedSequence2b EncodedSequence2b::reverseComplement() const
{
	EncodedSequence2b es;
	es.tab = new unsigned char[longueur];
	return es;
}

char EncodedSequence2b::operator[](size_t i) const
{
	//cout<<" t = "<<endl;
	return decode(tab[donneOctect(i)] >> donnePositionOctect(i) & 3); //i%4 est egal a &3
}

EncodedSequence &EncodedSequence2b::operator()(size_t start, size_t end) const
{
	if (end < start)
	{
		cout<<"Attention aux valeurs données"<<endl;
		exit(0);
	}

	if (end > longueur)
	{
		end = longueur;
	}

	EncodedSequence2b * sseq = new EncodedSequence2b();
	sseq->longueur = (end-start);
	//cout<<"longueur = "<<sseq.longueur<<endl;

	size_t lg = sseq->longueur/4 + ((sseq->longueur%4) != 0);
	sseq->tab = new unsigned char[lg];

	for (size_t i = 0; i < lg; ++i)
	{
		sseq->tab[i] = 0;
	}
	for (size_t i = start; i < end; ++i)
	{
		sseq->setSymbolAt(i-start, (*this)[i]);
	}
	//cout<<"ok"<<endl;
	return *sseq;
}

EncodedSequence& EncodedSequence2b::operator=(const EncodedSequence & es)
{
	cout<<__FUNCTION__<<" - operateur affectation 2b"<<endl;
	/*if (this != &es)
	{
		lesIntitules = es.getIntitules();
		lesSeqQualites = es.getLesSeqQualites();
		longueurDeSequences = es.length();   // vector
		longueur = es.totalLength();

		delete[] tab;
		tab = new unsigned char[es.totalLength()/4 + (es.totalLength()%4 != 0)];   // on alloue de la memoire

		for (size_t i = 0; i < es.totalLength()/4; ++i)
		{
			tab[i] = es.tab[i];
		}
	}

	*/
		size_t lg = es.totalLength()/4 +((es.totalLength() & 3) > 0);

		if(totalLength() != es.totalLength())
		{
			if (tab)
			{
				delete[] tab;
				tab = NULL;		
			}
			longueur = es.totalLength();
			if (longueur)
			{
				tab = new unsigned char[lg];
			}
		}
		if (es.totalLength())
		{
			for (size_t i = 0; i < lg; ++i)
			{
				tab[i] = es.tab[i];
			}
		}

	return *this;	
}

bool EncodedSequence2b::operator==(const EncodedSequence& es) const
{
	size_t i = 0;
	if (longueur != es.totalLength())
	{
		cout<<__FUNCTION__<<" : Longueurs de sequences inégales. "<<longueur<<" "<<es.totalLength()<<endl;
	}
	else
	{	
		while ( i < longueur and (*this)[i] == es[i] )
		{
			++i;
		}
	}
	return (i==longueur);
}

EncodedSequence2b::~EncodedSequence2b()
{
	
}
