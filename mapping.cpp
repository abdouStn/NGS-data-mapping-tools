#include "mapping.h"
using namespace std;

Mapping::Mapping():genome(NULL), reads(NULL), kmers(), seuilSimularite(0)
{
//	genome = new SequenceFastA();
//	reads = new SequenceFastQ();
}

Mapping::Mapping(SequenceFastA* fa, SequenceFastQ* fq, size_t seuil) : genome(fa), reads(fq), kmers(), seuilSimularite(seuil)
{
}

size_t Mapping::estPresent(EncodedSequence& es, size_t lgKmer ) const
{
	for (size_t i = 0; i < kmers.size(); ++i)
	{
		EncodedSequence& subseq = (*(reads->encodage))(kmers[i].getPositionDebutReads(),kmers[i].getPositionDebutReads() + lgKmer); // appel de l'operator() pour extraire la sous sequence
		if (subseq == es) // sucharge operator==
		{
			delete &subseq;
			return i; //la 
		}
		delete &subseq;
	}
	return -1; // return la valeur max de size_t
}

size_t Mapping::calculNumRead(size_t position) const
{
	size_t i=0, lg=0;
	while(i<reads->getLongueurDeSequences().size()) // nombre de sequences de reads
	{
		lg += reads->getLongueurDeSequences()[i];
		if (position <= lg)
		{
			//cout<<"position "<<position<<" i "<<i<<" reads->getLongueurDeSequences()[i] "<<reads->getLongueurDeSequences()[i]<<endl;
			return i;
		}
		i++;
	}
	return 0;
}

void Mapping::constuireKMers(size_t longueurKMers)
{
	if (longueurKMers==0 or  longueurKMers > reads->totalLength())
	{
		cout << "Attention longueur Kmer incorrecte"<<endl;
		exit(0);
	}

	size_t e = 0, num = 0;
	cout<<"position Kmer dans le genome: ";
	for (size_t i = 0; i + longueurKMers <= reads->totalLength() ; ++i)
	{
		EncodedSequence& es = (*(reads->encodage))(i,i+longueurKMers); // appel de l'operator() pour extraire la sous sequence
		e = estPresent(es, longueurKMers);
		if (e != (size_t) -1) // la seq est dans le vecteur 
		{	
			//cout<<es<<endl;
			kmers[e].incrementeNbRepetitionsDansReads();
			kmers[e].numeroReads.push_back(calculNumRead(i));	 // la fonction getNumeroReads() ne fonctionne pas ...
		}
		else
		{
			//KMer* k = new KMer(num++, &es);
			KMer k(num++, i);
			k.numeroReads.push_back(calculNumRead(i));
			kmers.push_back(k);    // appel const par copie de KMer
			
		}

		delete &es;
		cout<<i<<" ";
	}
	cout<<endl;
}

void Mapping::constuireKMers2(size_t longueurKMers)
{
	if (longueurKMers==0 or  longueurKMers > reads->totalLength())
	{
		cout << "Attention longueur Kmer incorrecte"<<endl;
		exit(0);
	}

	size_t num = 0;
	cout<<"position Kmer dans le genome: ";
	for (size_t i = 0; i + longueurKMers <= reads->totalLength() ; ++i)
	{
		//EncodedSequence& es = (*(reads->encodage))(i,i+longueurKMers); // appel de l'operator() pour extraire la sous sequence
		//e = estPresent(es, longueurKMers);
		//if (e != (size_t) -1) // la seq est dans le vecteur 
		//{	
			//cout<<es<<endl;
			//kmers[e].incrementeNbRepetitionsDansReads();
			//kmers[e].numeroReads.push_back(calculNumRead(i));	 // la fonction getNumeroReads() ne fonctionne pas ...
		//}
		//else
		//{
			//KMer* k = new KMer(num++, &es);
			KMer k(num++, i);
			k.numeroReads.push_back(calculNumRead(i));
			
			kmers.push_back(k);    // appel const par copie de KMer
			
		//}

		//delete &es;
		cout<<i<<" ";
	}
	cout<<endl;
}


void Mapping::mapAkmer(const vector<size_t>& SA, const vector<size_t>& LCP, const KMer& k, size_t lgKmer) const
{
	size_t deb = 0, fin = SA.size(), milieu = 0, i = 0, j=0, lcpUp=0, lcpDown=0;
    bool trouve = false;
    EncodedSequence& seqKmer = (*(reads->encodage))(k.getPositionDebutReads(),k.getPositionDebutReads() + lgKmer);
    
    while(!trouve && (fin - deb) > 1)
    {
		milieu = (fin + deb) /2;
   		i  = 0;	j=SA[milieu];
   		//cout <<"i = "<<i<< " j = "<<j<<" milieu "<<milieu<<" "<<(*(genome->encodage))[j] << " "<<kmer[i]<<endl;
   		while(i<lgKmer and j<genome->totalLength() and (*(genome->encodage))[j] == seqKmer[i]) 
   		{
   			//cout<< (*(genome->encodage))[j] << " x "<<kmer[i]<<endl;
   			i++; j++;
   		}
   		trouve = (i>=lgKmer || (j>genome->totalLength() and (*(genome->encodage))[j] == seqKmer[i])) ? true : false;
   		
		if((*(genome->encodage))[j] > seqKmer[i] )
		{	
			fin = milieu;
		}
		else
		{
			deb = milieu;
		}
		
    }
    //cout<<"milieu = "<<milieu <<" deb = " <<deb<<" fin = "<<fin<<" trouve = "<<trouve<<endl;
    
    if(trouve)
    {
    	//LCP
    	lcpDown = lcpUp = milieu;
		cout<<endl<<"====="<<seqKmer << k <<" positions mappées: "<<"{ ";
		while(LCP[lcpUp-1] >= lgKmer)
    	{
    		cout<<SA[--lcpUp]<< " ";
    		if (lcpUp == 0)
    		{
    			break;
    		}
    	}	
    	
    	do
    	{
    		cout<<SA[lcpDown]<<" ";    		
    	}
    	while(LCP[lcpDown++] >= lgKmer);
    	cout<<"}"<<endl;    
    }
    delete &seqKmer;
}

void Mapping::mapAkmerApproche(const vector<size_t>& SA, const vector<size_t>& LCP, const KMer& k, size_t lgKmer) const
{
	size_t deb = 0, fin = SA.size(), milieu = 0, i = 0, j=0, lcpUp=0, lcpDown=0, simularite = 0;
    bool trouve = false;
    EncodedSequence& seqKmer = (*(reads->encodage))(k.getPositionDebutReads(),k.getPositionDebutReads() + lgKmer);
    
    while(!trouve && (fin - deb) > 1)
    {
		milieu = (fin + deb) /2;

		//trouve = (text.substr(SA[milieu],motif.size()).compare(motif) == 0);// ? true : false;
   		i = simularite = 0;	j=SA[milieu];
   		//size_t p = ;

   		
   		//cout <<"i = "<<i<< " j = "<<j<<" milieu "<<milieu<<" "<<(*(genome->encodage))[j] << " "<<kmer[i]<<endl;
		while(i<lgKmer and j<genome->totalLength()) 
   		{
   			if ((*(genome->encodage))[j] == seqKmer[i])
   			{
   				simularite++;
   			}
   			//cout<< (*(genome->encodage))[j] << " x "<<kmer[i]<<endl;
   			i++; j++; 
   		}
   		//cout<<" simularite "<<(size_t)(100*simularite/lgKmer)<<endl;
   		if ((size_t)(100*simularite/lgKmer) >= seuilSimularite)
   		{
   			trouve = true;
   		}
   		else
   		{
   			trouve = false;
   		}
   		//trouve = (i>=lgKmer || (j>genome->totalLength() and (*(genome->encodage))[j] == seqKmer[i])) ? true : false;
   		
		if((*(genome->encodage))[SA[milieu]] > seqKmer[0] )
		{	
			fin = milieu;
		}
		else
		{
			deb = milieu;
		}
		
    }
    //cout<<"milieu = "<<milieu <<" deb = " <<deb<<" fin = "<<fin<<" trouve = "<<trouve<<endl;
    
    if(trouve)
    {
    	//LCP
    	lcpDown = lcpUp = milieu;
		cout<<endl<<"====="<<seqKmer << k <<" simularité: "<<(size_t)(100*simularite/lgKmer)<<"% positions mappées: "<<"{ ";
		while(LCP[lcpUp-1] >= lgKmer)
    	{
    		cout<<SA[--lcpUp]<< " ";
    		if (lcpUp == 0)
    		{
    			break;
    		}
    	}	
    	
    	do
    	{
    		cout<<SA[lcpDown]<<" ";    		
    	}
    	while(LCP[lcpDown++] >= lgKmer);
    	cout<<"}"<<endl;    
    }
    delete &seqKmer;
}


void Mapping::mapALLKmers(const vector<size_t>& SA, const vector<size_t>& LCP, size_t lgKmer) const
{
	cout<<endl<<"-----------------------------------Mapping exact-----------------------------------"<<endl<<endl;
	for (size_t i = 0; i < kmers.size(); ++i)
	{
		mapAkmer(SA,LCP, kmers[i], lgKmer);	
	}
	cout<<endl<<"-----------------------------------Mapping approché-----------------------------------"<<endl<<endl;
	for (size_t i = 0; i < kmers.size(); ++i)
	{
		mapAkmerApproche(SA,LCP, kmers[i], lgKmer);	
	}
}

vector<KMer> Mapping::getKmers() const
{
	return kmers;
}

SequenceFastA* Mapping::getGenome() const
{
	return genome;
}

SequenceFastQ* Mapping::getReads() const
{
	return reads;
}


size_t Mapping::getSeuilSimularite() const
{
	return seuilSimularite;
}

void Mapping::setSeuilSimularite( size_t s)
{
	seuilSimularite = s;
}



Mapping::~Mapping()
{
	//cout<<"~Mapping()"<<endl;
	//delete genome;
	//delete reads;
}

void Mapping::printKmer(KMer& k, size_t lgKmer ) const
{	EncodedSequence& es = (*(reads->encodage))(k.getPositionDebutReads(),k.getPositionDebutReads() + lgKmer);
	cout<<k<<" Sequence: "<<"\n\t"<<es<<endl;
	delete &es;
}

ostream & operator<<(ostream& os, const Mapping& m)
{
	os<<*(m.getGenome())<<endl<<*(m.getReads())<<endl;	
	return os;
}
