#include "mapping.h"

//g++ -o test -Wall -ansi -pedantic -g encodedSequence.cpp encodedSequence2b.cpp sequenceFastX.cpp sequenceFastA.cpp test_Sequence.cpp


using namespace std;

int main(int argc, char const *argv[])
{
	if (argc != 4)
	{
		cerr<<endl<<"Arguments invalides. Vous devez indiquer un fichier fasta (le genome), un fastq (les reads) et la taille des kmers (nombre entier)"<<endl
			<<"Exple: ./nomProgramme fichier.fasta fichier.fastq 23"<<endl;
		exit(1);	  	
	}

	cout<<endl<<endl<<"\t>>>>>>>>>>>Bienvenue dans mon programme de Mapping<<<<<<<<<<<<<<"<<endl;
				cout<<"\t\t\tDéveloppé par DIALLO Abdoulaye M1 BCD"<<endl<<endl;

	cout<<"\n>>>>>>>>>>>>>>>>>>>>>>>>>Chargement du genome: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
	clock_t debut = clock();
	SequenceFastA genome((string)argv[1]);
	//cout << s1;
	clock_t duree = clock() - debut;
	cout << "\nFin de chargement fasta: "<<double(duree) /CLOCKS_PER_SEC<<" secondes"<<endl;
	
	cout<<"\n>>>>>>>>>>>>>>>>>>>>>>>>>Chargement des reads: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
	debut = clock();
	SequenceFastQ reads((string)argv[2]); 
	//cout << s2;
	duree = clock() - debut;
	cout << "\nFin de chargement reads: "<<double(duree) /CLOCKS_PER_SEC<<" secondes"<<endl;

	cout<<"\n>>>>>>>>>>>> Construction table des suffixes (SA) et LCP du genome: <<<<<<<<<<<<<<"<<endl;
	
	debut = clock();
	vector<size_t> sa = buildSA(genome);
	vector<size_t> lcp = buildLCP(genome, sa);
	cout<<"LCP  SA "<<endl;
	/*for (size_t i = 0; i < sa.size(); ++i)
	{
		cout<<lcp.at(i)<< "    "<<sa.at(i)<< "    "<<(*(genome.encodage))(sa[i])<<endl;
	}
	cout<<endl;*/

	duree = clock() - debut;
	cout << "\nFin SA et LCP: "<<double(duree) /CLOCKS_PER_SEC<<" secondes"<<endl;
	
		
	cout<<"\n>>>>>>>>>>>>>>>>>>>>>>>>>>>> Construction des K mers: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
	Mapping map(&genome, &reads);
	//cout<<map<<endl;

	size_t longueurKMers = atoi(argv[3]);
	//int saisie = 0;
	//demande clavier

	debut = clock();
	map.constuireKMers(longueurKMers);
	//affiche Kmer
	duree = clock() - debut;
	
	/*for (size_t i = 0; i < map.getKmers().size(); ++i)
	{
		//cout<<i<<endl;
		map.printKmer(map.getKmers()[i], longueurKMers);
	}*/
	
	cout << "\n Fin Construction des K mers: "<<double(duree) /CLOCKS_PER_SEC<<" secondes. Total: "<<map.getKmers().size()<<" kmers"<<endl;

	cout<<"\n>>>>>>>>>>>>>>>>>>>>>> Mapping : <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
	
	debut = clock();
	map.mapALLKmers(sa, lcp, longueurKMers);
	//affiche 
	duree = clock() - debut;
	cout << "\n Fin Mapping: "<<double(duree) /CLOCKS_PER_SEC<<" secondes"<<endl;	

	return 0;
}
