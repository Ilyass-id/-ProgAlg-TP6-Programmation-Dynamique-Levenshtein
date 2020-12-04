#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#pragma once
using namespace std;


int recursiveLevenshtein(const string& s,const string& s1);                         //Methode recursive
int recursiveLevenshteinMemoise(const string& s, const string& s1);                 //Recursive avec memoisation

int iterativeLevenshtein(const string& s,const string& s1);                         //Iterative

vector<vector<int>> iterativeLevenshteinMatrix(const string& s,const string& s1);   //Iterative qui renvoi la matrice de Levenshtein
void remonterModif(vector<vector<int>> matrix, string s, string s1);                //dont on a besoin pour afficher la suite des modifs elementaires

int damerau_levenshtein_distance(const string& s,const string& s1);                 //Damerau Levenshtein

int iterativeLevenshteinLineaire(const string& s,const string& s1);                 //Version iterative lineaire en espace où on ne garde que 2 lignes de la matrice
