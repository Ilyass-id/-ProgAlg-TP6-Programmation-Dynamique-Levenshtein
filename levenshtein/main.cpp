#include "levenshtein.h"
#include <chrono>

int main()
{
    string a = "ecoles";
    string b = "eclose";
    double elapsed_seconds;

    cout<<"########### Distance de Levenshtein  ###########"<<endl;

    cout << "Solution Recursive :";
    auto start = chrono::steady_clock::now();
    cout << recursiveLevenshtein(a, b)<< endl;
    auto end = chrono::steady_clock::now();
    elapsed_seconds = chrono::duration_cast<chrono::duration<double> >(end - start).count();
    cout << "Temps d'execution :"<< elapsed_seconds << endl;

    cout << "-----------------"<< endl;

    cout << "Solution Recursive avec Memoisation :";
    start = chrono::steady_clock::now();
    cout << recursiveLevenshteinMemoise(a, b)<< endl;
    end = chrono::steady_clock::now();
    elapsed_seconds = chrono::duration_cast<chrono::duration<double> >(end - start).count();
    cout << "Temps d'execution :"<< elapsed_seconds << endl;

    cout << "-----------------"<< endl;

    cout << "Solution Iterative :";
    start = chrono::steady_clock::now();
    cout << iterativeLevenshtein(a, b)<< endl;
    end = chrono::steady_clock::now();
    elapsed_seconds = chrono::duration_cast<chrono::duration<double> >(end - start).count();
    cout << "Temps d'execution :"<< elapsed_seconds << endl;
    cout<<" "<<endl;

    cout<<"########### Affichage des modifications elementaires  ###########"<<endl;

    remonterModif(iterativeLevenshteinMatrix(a, b),a,b);

    cout<<" "<<endl;

    cout<<"########### Comparaison des temps d'executions recursive et recursive memoisee  ###########"<<endl;

    a = "ecoles et fer";
    b = "eclose et mer";

    cout << "Solution Recursive :";
    start = chrono::steady_clock::now();
    cout << recursiveLevenshtein(a, b)<< endl;
    end = chrono::steady_clock::now();
    elapsed_seconds = chrono::duration_cast<chrono::duration<double> >(end - start).count();
    cout << "Temps d'execution :"<< elapsed_seconds << endl;

    cout << "-----------------"<< endl;

    cout << "Solution Recursive avec Memoisation :";
    start = chrono::steady_clock::now();
    cout << recursiveLevenshteinMemoise(a, b)<< endl;
    end = chrono::steady_clock::now();
    elapsed_seconds = chrono::duration_cast<chrono::duration<double> >(end - start).count();
    cout << "Temps d'execution :"<< elapsed_seconds << endl;

    cout << "-----------------"<< endl;

    cout<<" "<<endl;


    cout<<"########### Affichage des modifications elementaires  ###########"<<endl;

    remonterModif(iterativeLevenshteinMatrix(a, b),a,b);

    cout<<" "<<endl;

    cout<<"########### Distance Damerau Levenshtein  ###########"<<endl;

    cout << "Solution iterative :";
    start = chrono::steady_clock::now();
    cout << damerau_levenshtein_distance(a, b)<< endl;
    end = chrono::steady_clock::now();
    elapsed_seconds = chrono::duration_cast<chrono::duration<double> >(end - start).count();
    cout << "Temps d'execution :"<< elapsed_seconds << endl;

    cout << "-----------------"<< endl;

    cout<<" "<<endl;

    cout<<"########### Distance Levenshtein lineaire  ###########"<<endl;

    cout << "Solution iterative :";
    start = chrono::steady_clock::now();
    cout << iterativeLevenshteinLineaire(a, b)<< endl;
    end = chrono::steady_clock::now();
    elapsed_seconds = chrono::duration_cast<chrono::duration<double> >(end - start).count();
    cout << "Temps d'execution :"<< elapsed_seconds << endl;


    return 0;
}
