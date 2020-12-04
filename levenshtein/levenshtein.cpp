#include "levenshtein.h"

////////////
/// Version recursive de Levenshtein
////////////
int recursiveLevenshtein(const string& s,const string& s1){
    if(s.length()==0 || s1.length()==0)
        return s.length()+s1.length();
    else{
        return min(
                    min(
                        (1 + recursiveLevenshtein(s.substr(0,s.length()-1),s1)),
                        (1 + recursiveLevenshtein(s,s1.substr(0,s1.length()-1)))),
                        ( (s.back()==s1.back()? 0 : 1) + recursiveLevenshtein(s.substr(0,s.length()-1),s1.substr(0,s1.length()-1)))
                   );
    }
}

////////////
/// Version récursive memoisee de Levenshtein
////////////
vector<vector<int>> F;
int recursiveLevenshteinMemoise(const string& s, const string& s1){
    if(s.length()==0 || s1.length()==0)
        return s.length()+s1.length();

    vector<int> initVector;
    initVector.resize(max(s.length(), s1.length())+1, -1);

    if (F.size()<max(s.length(), s1.length()))
        F.resize(max(s.length(), s1.length())+1, initVector);

    for(int i=0; i<int(max(s.length(), s1.length())); i++){
        if (F[i].size()<max(s.length(), s1.length()))
            F[i].resize(max(s.length(), s1.length())+1, -1);
}
    if (F[s.length() - 1][s1.length() - 1]==-1){
        F[s.length() - 1][s1.length() - 1] = min(
                    min(
                        (1 + recursiveLevenshteinMemoise(s.substr(0,s.length()-1),s1)),
                        (1 + recursiveLevenshteinMemoise(s,s1.substr(0,s1.length()-1)))),
                        ((s.back()==s1.back()? 0 : 1) + recursiveLevenshteinMemoise(s.substr(0,s.length()-1),s1.substr(0,s1.length()-1)))
                   );
    }
    return F[s.length() -1][s1.length() -1];
}

////////////
/// Version itérative de Levenshtein
////////////

int iterativeLevenshtein(const string& s,const string& s1)
{
    const int lens = int(s.length()), lens1 = int(s1.length());
    vector<vector<int>> d(lens + 1, vector<int>(lens1 + 1));

    d[0][0] = 0;
    for(int i = 1; i <= lens; ++i) d[i][0] = i;
    for(int i = 1; i <= lens1; ++i) d[0][i] = i;

    for(int i = 1; i <= lens; ++i)
        for(int j = 1; j <= lens1; ++j)
                      d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1) , d[i - 1][j - 1] + (s[i - 1] == s1[j - 1] ? 0 : 1)); //Le nombre augmente lorsqu'une opération est nécessaire
                                                                                                                                //il reste le même lorsque la lettre aux positions correspondantes dans les chaînes de caractères est la même.
    return d[lens][lens1];
}

////////////
/// Fonction qui renvoit la matrice de levenshtein
/// Elle nous sera utile pour afficher la suite de modifs élémentaires pour aller de s à s'
////////////

vector<vector<int>> iterativeLevenshteinMatrix(const string& s,const string& s1)
{
    const int lens = int(s.length()), lens1 = int(s1.length());
    vector<vector<int>> d(lens + 1, vector<int>(lens1 + 1));

    d[0][0] = 0;
    for(int i = 1; i <= lens; ++i) d[i][0] = i; //La distance entre le mot vide "" et le mot s[0,i] est toujours egale à i (correspond a i suppressions)
    for(int i = 1; i <= lens1; ++i) d[0][i] = i; //La distance entre le mot vide "" et le mot s1[0,i] est toujours egale à i (correspond a i suppressions)

    for(int i = 1; i <= lens; ++i)
        for(int j = 1; j <= lens1; ++j)
                      d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1) , d[i - 1][j - 1] + (s[i - 1] == s1[j - 1] ? 0 : 1)); //Le nombre augmente lorsqu'une opération est nécessaire
                                                                                                                                //il reste le même lorsque la lettre aux positions correspondantes dans les chaînes de caractères est la même.
    return d;
}

////////////
/// Affichez la suite de modifs élémentaires pour aller de s à s'
////////////

void remonterModif(vector<vector<int>> matrix, string s, string s1){
    int i = s.length();
    int j = s1.length();
    vector<string> optimal_path ;
    while (i > 0 && j > 0){
        int diagonal = matrix[i-1][j-1];
        int vertical = matrix[i-1][j];
        int horizontal = matrix[i][j-1];
        int current = matrix[i][j];
        if((diagonal <= vertical) && (diagonal <= horizontal) && (diagonal <= current)){
            i = i - 1;
            j = j - 1;
            string s1jletter(1, s1[j]);

            if (diagonal == current - 1){
                optimal_path.push_back("Remplacer la lettre a la " + to_string(j) + "eme place par '" + s1jletter + "'");
            }
            else if (horizontal <= vertical and horizontal <= current){
                j = j - 1;
                string s1jletter(1, s1[j]);
                optimal_path.push_back("Inserer " + s1jletter + " a la "  + to_string(j) + "eme place");
            }
            else if (vertical <= horizontal && vertical <= current){
                i = i - 1;
                string s1jletter(1, s1[j]);
                optimal_path.push_back("Supprimer la lettre a la " + to_string(i) + "eme place");
            }
        }
        else if(horizontal <= vertical and horizontal <= current){
            j = j - 1;
            string s1jletter(1, s1[j]);
            optimal_path.push_back("Inserer '" + s1jletter + "' a la "  + to_string(j) + "eme place");
        }
        else{
            i = i - 1;
            optimal_path.push_back("Supprimer la lettre a la " + to_string(i) + "eme place");
        }
    }
    reverse(begin(optimal_path), end(optimal_path));
    for(int i=0; i<int(optimal_path.size()); i++){
        cout<<optimal_path.at(i)<<endl;
    }
    return;
}


////////////
/// Damerau Levenshtein
////////////

int damerau_levenshtein_distance(const string& s,const string& s1)
{
    int lens = s.length();
    int lens1 = s1.length();

    vector<vector<int>> d(lens + 1, vector<int>(lens1 + 1));
    int i, j;

    for (i = 0;i <= lens;i++)
        d[i][0] = i;
    for(j = 0; j<= lens1; j++)
        d[0][j] = j;
    for (i = 1;i <= lens;i++)
    {
        for(j = 1; j<= lens1; j++)
        {
            d[i][j] = min(d[i-1][j] + 1, min(d[i][j-1] + 1, d[i-1][j-1] + (s[i - 1] == s1[j - 1] ? 0 : 1)));  //Respectivement : supprimer, inserer, remplacer (ou pas)

            if( (i > 1) && (j > 1) && (s[i-1] == s1[j-2]) && (s[i-2] == s1[j-1])) // Transposition de deux caracteres successifs
            d[i][j] = min(d[i][j], d[i-2][j-2] + (s[i - 1] == s1[j - 1] ? 0 : 1));
        }
    }
    return d[lens][lens1];
}

////////////
/// Levenshtein en complexité lineaire
////////////


int iterativeLevenshteinLineaire(const string& s, const string& s1)
{
    const int lens = int(s.length()), lens1 = int(s1.length());
    vector<int> v0(lens1 + 1);
    vector<int> v1(lens1 + 1);

    for(int i = 0; i <= lens1; ++i) v0[i] = i;

    for(int i = 1; i <= lens; ++i)
    {
        v1[0]=i+1;                              // Le premier element de v1 est M[i+1][0]
                                                // Levenshtein distance est egale aux (i+1)  suppressions de caracteres de s pour etre egale à "" (s1 vide)
        for(int j = 1; j <= lens1; ++j)
                          v1[j] = min(
                                      min(v0[j] + 1,   //Suppression
                                      v1[j-1]+ 1) ,     //Insertion
                                      v0[j-1] + (s[i - 1] == s1[j - 1] ? 0 : 1)); //Remplacement
        v0=v1;
    }

    return v0[lens1];
}
