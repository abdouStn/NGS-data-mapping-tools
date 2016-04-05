#ifndef SUFFIXE_TABLE_H
#define SUFFIXE_TABLE_H


#include "sequenceFastA.h"
#include "sequenceFastQ.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream> //pour lire les fichiers
#include <vector>
#include <numeric>      // std::iota
#include <algorithm>

struct  SAcomp
{

	const EncodedSequence & es;
	SAcomp(const EncodedSequence &es);
	bool operator()(size_t a, size_t b) const;
};

std::vector<size_t> buildSA(const SequenceFastA& s);

/*
Calcul de la table des plus longs préfixes communs
Il s'agit de créer ue table qui contient le nombre de caractères commun au préfixe précédent, en fonction de la tables des Suffixes
*/
std::vector<size_t> buildLCP(const SequenceFastA& s, const std::vector<size_t> &SA);

//std::string buildBWT(const std::string &s, const std::vector<size_t> &SA);

#endif