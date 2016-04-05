#include "suffixeTable.h"

using namespace std;


SAcomp::SAcomp(const EncodedSequence &es) : es(es){}

// je prends 2 valeurs au hasard sur ROUDOUDOU par ex a = 4 et b = 6
	// soit s[a] < s[b] --> V
	// soit s[a] > s[b] --> F
	// soit s[a] == s[b] --> a++, b++
bool SAcomp::operator()(size_t a, size_t b) const
{
	size_t n = es.totalLength();
	
	while((a<n) && (b<n) &&(es[a] == es[b])) 
	{
		a++; b++ ;
	}
    return (a>=n)||((b<n) && (es[a]<es[b]));
}

vector<size_t> buildSA(const SequenceFastA & s)   // construction de la table des suffixes
{
	size_t n = s.encodage->totalLength();
	vector<size_t> SA(n);

	//iota(SA.begin(), SA.end(), 0);   // methode de la STL,exactement comme une boucle for .
	for (size_t i = 0; i < n; ++i)
	{
		SA[i] = i;
	}
	sort(SA.begin(), SA.end(), SAcomp(*(s.encodage)));      // Tri rapide, dernier arg donne ordre de tri, boolean. () appelle l'operator defini dans la struct
												// ordre lexicographique
												// SAcomp(size_t a, size_t b) : B renvoie a < b (lexico))
										        // va renvoyer pour ROUDOUDOU = 6,3,7,4,1,0,8,5,2
	return SA;
}


vector<size_t> buildLCP(const SequenceFastA& genome, const vector<size_t> &SA)
{
    size_t n = genome.totalLength() ;                                     // longueur du motif
	vector<size_t> LCP(n,0) ;                                     // initialisation de la table LCP (Longuest Common Prefixes)
	size_t p1 = 0, p2 = 0;
	
	for (size_t i=0 ; i<n-1; ++i )
	{	
		
        LCP[i] = 0;
        p1 = SA[i];
        p2 = SA[i+1];

        while( (p1 < n) and (p2 < n) and ((*(genome.encodage))[p1] == (*(genome.encodage))[p2]) ) 
        {
        	LCP[i] = LCP[i] + 1;
        	p1++; p2++;
        }		
	}

	return LCP ;
}

/*
 * s : une séquence ("ROUDOUDOU")
 * SA : la table de suffixe de la séquence
*/
/*string buildBWT(const string &s, const vector<size_t> &SA)
{
    size_t n = s.length() ;
	string BWT ;

	for (size_t i(0); i<n; ++i)
	{
        if (SA[i] == 0) {
            BWT[i] = s[n-1];
        } else {
            BWT[i] = s[SA[i]-1];
        }
	}
	return BWT ;
}*/
	