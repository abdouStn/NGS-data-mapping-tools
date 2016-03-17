#include "encodedSequence4b.h"
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
	return (3-(i%4))<<1;  // <<1 est = *2;
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
//----------------------------- Les Methodes ------------------------------


void EncodedSequence4b::encodeSeq(const char* raw_seq)
{
	if (raw_seq != NULL)
	{	
		while(raw_seq[longueur] != '\0')
		{
			if (!estValide(raw_seq[longueur]))
			{
				cout<<"Le caractère " << raw_seq[longueur] << "est invalide !!" <<endl;
			}
			longueur++;
		}
		
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

void EncodedSequence4b::loadAFasta(string leFichier)
{
	//lecture du fichier
	ifstream fichier(leFichier.c_str(), ios::in); 
	if (fichier.fail())
	{
		cerr<<endl<<"Impossible d'ouvrir le fichier : "<<leFichier<<endl<<endl;
		exit(0);
	}
	string ligne;
    char caractereLu;
	size_t i = (size_t) 0, p = (size_t) -1;

	getline(fichier, ligne);
	while(fichier.get(caractereLu))  // on recommence la lecture du fichier caractere par caractere. 
	{
		if (!estValide(caractereLu))
		{
			continue;
		}
		longueur++;
	}

	cout<<"Longueur de la sequence = "<< longueur<<endl;

	//on se replace en debut de fichier
	fichier.seekg(0, ios::beg);
	cout <<"position dans fichier: "<< fichier.tellg() <<endl;
	if((int)fichier.tellg() != 0)  //si ça marche pas on tente un clear
    {
            fichier.clear();
            fichier.seekg(0, ios::beg);
            cout << endl << "On se trouve au " << fichier.tellg() << "ieme octet." << endl;
    }

	tab = new unsigned char[longueur/4 + (longueur%4 != 0)];   // on alloue de la memoire
		
	getline(fichier, ligne);
    if (ligne[0] == '>')
    {
    	//intitule = ligne;
    	//cout << "Lecture de la sequence : "<<intitule<<endl;
    }
    cout <<"position dans fichier: "<< fichier.tellg() <<endl;
    
    
	while(fichier.get(caractereLu))  // on recommence la lecture du fichier caractere par caractere. 
	{
		if(estValide(caractereLu))
		{
			//cout<<caractereLu;
			if (!(i%4)) //si est multiple de 4. si 4bits !(i&1)
			{				
				tab[++p] = 0;				
			}
			tab[p]|=encode(caractereLu)<<donnePositionOctect(i) ; // <<1 est = *2;  ((!(i&1))<<2) pour version 2 bits 
			i++;	
		}
		
	}
	//cout<<endl;
	fichier.close();

}

// -------------------------------------constructeurs --------------------------

EncodedSequence4b::EncodedSequence4b() 
{
	longueur = 0;
	tab = NULL;
	cout<<"EncodedSequence4b()"<<endl;
}

EncodedSequence4b::EncodedSequence4b(const char* raw_seq)
{
	longueur = 0;
	tab = NULL;
	cout<<"EncodedSequence4b(const char* raw_seq)"<<endl;
	encodeSeq(raw_seq);
}

EncodedSequence4b::EncodedSequence4b(string leFichier) 
{
	longueur = 0;
	tab = NULL;
	
	loadAFasta(leFichier);
}

EncodedSequence4b::EncodedSequence4b(const EncodedSequence4b & es)
{
	cout<<"EncodedSequence4b(const EncodedSequence4b)"<<endl;
}

/*
void EncodedSequence4b::setSymbolAt(size_t i, char c)
{

}

EncodedSequence& EncodedSequence4b::reverseComplement() const
{

}

char EncodedSequence4b::operator[](size_t i) const
{

}

EncodedSequence& EncodedSequence4b::operator()(size_t start, size_t end) const
{

}

EncodedSequence& EncodedSequence4b::operator=(const EncodedSequence& es)
{

}
*/
void EncodedSequence4b::print()
{
	cout<<"> Sequence Fasta: Longueur: "<<longueur<<endl;
	
	for (size_t i = 0; i < longueur; ++i)
	{
		
		cout<<decode(tab[donneOctect(i)] >> donnePositionOctect(i) & 3);   //i%4	
		
	}
	cout<<endl<<"Fin"<<endl;
}	


EncodedSequence4b::~EncodedSequence4b()
{
	if (tab != NULL)
	{
		delete[] tab;
		cout<<"~EncodedSequence4b()"<<endl;
	}
}