
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// Recherche avec find : inspiree de exe1
bool rechercherAvecFind(string mot1, string mot2)
{
    if (mot2.empty() || mot2.length() > mot1.length())
        return false;

    vector<char> v;

    for (char c : mot1)
        v.push_back(c);

    for (int i = 0; i < v.size(); i++)
    {
        vector<char>::iterator it = find(v.begin() + i, v.end(), mot2[0]);

        if (it != v.end())
        {
            int pos = it - v.begin();

            if (mot1.substr(pos, mot2.length()) == mot2)
                return true;
        }
    }

    return false;
}

// Recherche sans find : inspiree de exe1
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

// Remplacement avec find : inspire de exe3
string remplacerAvecFind(string mot, string ancienMot, string nouveauMot)
{
    if (ancienMot.empty())
        return mot;

    size_t pos = mot.find(ancienMot);

    while (pos != string::npos)
    {
        mot.replace(pos, ancienMot.length(), nouveauMot);

        pos = mot.find(ancienMot, pos + nouveauMot.length());
    }

    return mot;
}

// Remplacement sans find : inspire de exe3
string remplacerSansFind(string mot, string ancienMot, string nouveauMot)
{
    if (ancienMot.empty())
        return mot;

    for (int i = 0; i + ancienMot.length() <= mot.length(); i++)
    {
        bool trouve = true;

        for (int j = 0; j < ancienMot.length(); j++)
        {
            if (mot[i + j] != ancienMot[j])
            {
                trouve = false;
                break;
            }
        }

        if (trouve)
        {
            mot.replace(i, ancienMot.length(), nouveauMot);

            i += nouveauMot.length() - 1;
        }
    }

    return mot;
}

// Recherche de la plus longue sous-chaine commune
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
    string mot;
    string ancienMot;
    string nouveauMot;

    cout << "Donner le mot original : ";
    cin >> mot;

    cout << "Donner le mot a remplacer : ";
    cin >> ancienMot;

    cout << "Donner le nouveau mot : ";
    cin >> nouveauMot;

    cout << endl;
    cout << "===== Recherche =====" << endl;

    // Mesure du temps avec find
    auto debut1 = high_resolution_clock::now();

    bool trouveAvecFind = rechercherAvecFind(mot, ancienMot);

    auto fin1 = high_resolution_clock::now();

    double tempsAvecFind =
        duration<double>(fin1 - debut1).count();

    // Mesure du temps sans find
    auto debut2 = high_resolution_clock::now();

    bool trouveSansFind = rechercherSansFind(mot, ancienMot);

    auto fin2 = high_resolution_clock::now();

    double tempsSansFind =
        duration<double>(fin2 - debut2).count();

    if (trouveAvecFind)
        cout << "Avec find : le mot a remplacer existe." << endl;
    else
        cout << "Avec find : le mot a remplacer n'existe pas." << endl;

    cout << "Temps d'execution avec find : "
         << tempsAvecFind << " secondes" << endl;

    if (trouveSansFind)
        cout << "Sans find : le mot a remplacer existe." << endl;
    else
        cout << "Sans find : le mot a remplacer n'existe pas." << endl;

    cout << "Temps d'execution sans find : "
         << tempsSansFind << " secondes" << endl;

    if (!trouveAvecFind)
    {
        cout << endl;
        cout << "Le remplacement est impossible." << endl;
        return 0;
    }

    cout << endl;
    cout << "===== Remplacement =====" << endl;

    string motAvecFind = remplacerAvecFind(mot, ancienMot, nouveauMot);
    string motSansFind = remplacerSansFind(mot, ancienMot, nouveauMot);

    cout << "Mot original : " << mot << endl;
    cout << "Resultat avec find : " << motAvecFind << endl;
    cout << "Resultat sans find : " << motSansFind << endl;

    cout << endl;
    cout << "===== Plus grande sous-chaine commune =====" << endl;

    string resultat = plusGrandeSousChaine(mot, motAvecFind);

    cout << "Sous-chaine commune : " << resultat << endl;
    cout << "Longueur : " << resultat.length() << endl;

    return 0;
}

