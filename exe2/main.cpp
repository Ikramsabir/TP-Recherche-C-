#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

bool rechercherAvecFind(string nomFichier, string mot)
{
    ifstream fichier(nomFichier);

    if (!fichier)
        return false;

    vector<string> lignes;
    string ligne;

    while (getline(fichier, ligne))
    {
        lignes.push_back(ligne);
    }

    fichier.close();

    for (string ligne : lignes)
    {
        if (ligne.find(mot) != string::npos)
            return true;
    }

    return false;
}

bool rechercherSansFind(string nomFichier, string mot)
{
    ifstream fichier(nomFichier);

    if (!fichier)
        return false;

    vector<string> lignes;
    string ligne;

    while (getline(fichier, ligne))
    {
        lignes.push_back(ligne);
    }

    fichier.close();

    for (string ligne : lignes)
    {
        for (int i = 0; i <= ligne.size() - mot.size(); i++)
        {
            bool trouve = true;

            for (int j = 0; j < mot.size(); j++)
            {
                if (ligne[i + j] != mot[j])
                {
                    trouve = false;
                    break;
                }
            }

            if (trouve)
                return true;
        }
    }

    return false;
}

int main()
{
    string nomFichier, mot;

    cout << "Donner le nom du fichier : ";
    cin >> nomFichier;

    cout << "Donner le mot a chercher : ";
    cin >> mot;


    auto debut1 = chrono::high_resolution_clock::now();

    bool resultat1 = rechercherAvecFind(nomFichier, mot);

    auto fin1 = chrono::high_resolution_clock::now();

    double temps1 = chrono::duration<double>(fin1 - debut1).count();


    auto debut2 = chrono::high_resolution_clock::now();

    bool resultat2 = rechercherSansFind(nomFichier, mot);

    auto fin2 = chrono::high_resolution_clock::now();

    double temps2 = chrono::duration<double>(fin2 - debut2).count();


    cout << endl;

    if (resultat1)
        cout << "Avec find : mot trouve." << endl;
    else
        cout << "Avec find : mot non trouve." << endl;

    cout << "Temps avec find : " << temps1 << " secondes" << endl;


    if (resultat2)
        cout << "Sans find : mot trouve." << endl;
    else
        cout << "Sans find : mot non trouve." << endl;

    cout << "Temps sans find : " << temps2 << " secondes" << endl;

    return 0;
}
