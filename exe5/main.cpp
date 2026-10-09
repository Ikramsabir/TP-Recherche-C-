
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

vector<string> lireFichier(string nomFichier)
{
    ifstream fichier(nomFichier);
    vector<string> mots;
    string mot;

    if (!fichier)
    {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
        return mots;
    }

    while (getline(fichier, mot))
    {
        if (!mot.empty())
            mots.push_back(mot);
    }

    fichier.close();

    return mots;
}

// Recherche avec find
bool rechercherAvecFind(string mot1, string mot2)
{
    if (mot2.empty() || mot2.length() > mot1.length())
        return false;

    vector<char> v;

    for (char c : mot1)
        v.push_back(c);

    for (int i = 0; i < v.size(); i++)
    {
        vector<char>::iterator it =
            find(v.begin() + i, v.end(), mot2[0]);

        if (it != v.end())
        {
            int pos = it - v.begin();

            if (mot1.substr(pos, mot2.length()) == mot2)
                return true;
        }
    }

    return false;
}

// Recherche sans find
bool rechercherSansFind(string mot1, string mot2)
{
    if (mot2.empty() || mot2.length() > mot1.length())
        return false;

    for (int i = 0; i <= mot1.length() - mot2.length(); i++)
    {
        bool trouve = true;

        for (int j = 0; j < mot2.length(); j++)
        {
            if (mot1[i + j] != mot2[j])
            {
                trouve = false;
                break;
            }
        }

        if (trouve)
            return true;
    }

    return false;
}

// Plus grande sous-chaine commune
string plusGrandeSousChaine(string mot1, string mot2)
{
    string resultat = "";

    for (int i = 0; i < mot1.length(); i++)
    {
        for (int j = 0; j < mot2.length(); j++)
        {
            string sousChaine = "";
            int k = 0;

            while (i + k < mot1.length() &&
                   j + k < mot2.length() &&
                   mot1[i + k] == mot2[j + k])
            {
                sousChaine += mot1[i + k];
                k++;
            }

            if (sousChaine.length() > resultat.length())
                resultat = sousChaine;
        }
    }

    return resultat;
}

int main()
{
    string nomFichier;

    cout << "Donner le nom du fichier : ";
    cin >> nomFichier;

    vector<string> mots = lireFichier(nomFichier);

    if (mots.size() < 2)
    {
        cout << "Le fichier doit contenir au moins deux mots." << endl;
        return 0;
    }

    string plusGrande = "";

    // Comparaison avec find
    auto debut1 = high_resolution_clock::now();

    for (int i = 0; i < mots.size(); i++)
    {
        for (int j = i + 1; j < mots.size(); j++)
        {
            if (rechercherAvecFind(mots[i], mots[j]))
            {
                string resultat =
                    plusGrandeSousChaine(mots[i], mots[j]);

                if (resultat.length() > plusGrande.length())
                    plusGrande = resultat;
            }
            else
            {
                // Meme si un mot n'est pas contenu dans l'autre,
                // ils peuvent avoir une sous-chaine commune.
                string resultat =
                    plusGrandeSousChaine(mots[i], mots[j]);

                if (resultat.length() > plusGrande.length())
                    plusGrande = resultat;
            }
        }
    }

    auto fin1 = high_resolution_clock::now();

    double tempsAvecFind =
        duration<double>(fin1 - debut1).count();

    // Comparaison sans find
    string plusGrandeSansFind = "";

    auto debut2 = high_resolution_clock::now();

    for (int i = 0; i < mots.size(); i++)
    {
        for (int j = i + 1; j < mots.size(); j++)
        {
            bool trouve = rechercherSansFind(mots[i], mots[j]);

            string resultat =
                plusGrandeSousChaine(mots[i], mots[j]);

            if (resultat.length() > plusGrandeSansFind.length())
                plusGrandeSansFind = resultat;
        }
    }

    auto fin2 = high_resolution_clock::now();

    double tempsSansFind =
        duration<double>(fin2 - debut2).count();

    cout << endl;
    cout << "===== Resultat final =====" << endl;

    if (plusGrande.length() >= plusGrandeSansFind.length())
    {
        cout << "Plus grande sous-chaine commune : "
             << plusGrande << endl;
        cout << "Longueur : " << plusGrande.length() << endl;
    }
    else
    {
        cout << "Plus grande sous-chaine commune : "
             << plusGrandeSansFind << endl;
        cout << "Longueur : " << plusGrandeSansFind.length() << endl;
    }

    cout << endl;
    cout << "===== Temps d'execution =====" << endl;

    cout << "Avec find : "
         << tempsAvecFind << " secondes" << endl;

    cout << "Sans find : "
         << tempsSansFind << " secondes" << endl;

    return 0;
}
