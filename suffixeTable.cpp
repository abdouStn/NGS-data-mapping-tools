#include "suffixeTable.h"

using namespace std;

/*
TABLE DES SUFFIXES
  0123456789
S.ROUDOUDOU$
SA[0--9]
*/

SAcomp::SAcomp(const EncodedSequence &es) : es(es){}

// je prends 2 valeurs au hasard sur ROUDOUDOU par ex a = 4 et b = 6
	// soit s[a] < s[b] --> V
	// soit s[a] > s[b] --> F
	// soit s[a] == s[b] --> a++, b++
bool SAcomp::operator()(size_t a, size_t b) const
{
	size_t n = es.totalLength();
	
	while((a<n) && (b<n) && (es[a]==es[b]))
	{
		a++;
		b++;
	}
    return (a>=n) || ((b<n) && (es[a]<es[b]));
    //return ((a == n) || (es[a]<es[b]));

}

vector<size_t> builtSA(const SequenceFastX & s)   // construction de la table des suffixes
{
	size_t n = s.encodage->totalLength();
	vector<size_t> SA(n);

	//iota(SA.begin(), SA.end(), 0);   // methode de la STL,exactement comme une boucle for .
	for (size_t i = 0; i < n; ++i)
	{
		SA.push_back(i);
	}
	sort(SA.begin(), SA.end(), SAcomp(*(s.encodage)) );      // Tri rapide, dernier arg donne ordre de tri, boolean. () appelle l'operator defini dans la struct
												// ordre lexicographique
												// SAcomp(size_t a, size_t b) : B renvoie a < b (lexico))
										        // va renvoyer pour ROUDOUDOU = 6,3,7,4,1,0,8,5,2
	return SA;
}


vector<size_t> buildLCP(const string &s, const vector<size_t> &SA)
{
    size_t n = s.length() ;                                     // longueur du motif
	vector<size_t> LCP(n,0) ;                                     // initialisation de la table LCP (Longuest Common Prefixes)

	string p1(""),p2("");                                       // initialisation des préfixes
	size_t lg(0);
	size_t j=0;
	
	for (size_t i=0 ; i<n-1; ++i )
	{
        p1 = s.substr(SA[i]) ;                                  // préfixe avant de la table des suffixes
        p2 = s.substr(SA[i+1]) ;                                // préfixe après de la table des suffixes
        //size_t lg(0);
        lg = (p1.size() <= p2.size()) ? p1.size() : p2.size() ;  // définir le suffixe le plus court
	  
	  j=0;
        while(j<lg and 	p1[j] == p2[j])
        {
        	LCP[i+1] = ++j;
        }		
	  /*	
        for ( size_t j=0; j<lg; ++j)                               // Pour chaque caractère du préfixe le plus court
        {
            if ( p1[j] == p2[j] ) {
                LCP[i+1] = j ;                                  // affecter à LCP la longueur du plus long préfixe commun
            }
        }*/
        //cout << p1 << " " << p2 << " - lg: " << lg << endl ;
	}

	return LCP ;
}

/*
 * s : une séquence ("ROUDOUDOU")
 * SA : la table de suffixe de la séquence
*/
string buildBWT(const string &s, const vector<size_t> &SA)
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
}