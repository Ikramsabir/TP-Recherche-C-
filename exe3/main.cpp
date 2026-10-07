#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

vector<string> lireFichier(string nomFichier)
{
    ifstream fichier(nomFichier);

    vector<string> lignes;
    string ligne;

    if (!fichier)
    {
        cout << "Erreur lors de l'ouverture du fichier." << endl;
        return lignes;
    }

    while (getline(fichier, ligne))
    {
        lignes.push_back(ligne);
    }

    fichier.close();

    return lignes;
}

void remplacerAvecFind(vector<string>& lignes, string mot, string nouveauMot)
{
    for (string& ligne : lignes)
    {
        size_t pos = ligne.find(mot);

        while (pos != string::npos)
        {
            ligne.replace(pos, mot.length(), nouveauMot);

            pos = ligne.find(mot, pos + nouveauMot.length());
        }
    }
}

void remplacerSansFind(vector<string>& lignes, string mot, string nouveauMot)
{
    for (string& ligne : lignes)
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
            {
                ligne.replace(i, mot.length(), nouveauMot);

                i += nouveauMot.length() - 1;
            }
        }
    }
}

void afficherVector(vector<string> lignes)
{
    for (string ligne : lignes)
    {
        cout << ligne << endl;
    }
}

int main()
{
    string nomFichier;
    string mot;
    string nouveauMot;

    cout << "Donner le nom du fichier : ";
    cin >> nomFichier;

    cout << "Donner le mot a remplacer : ";
    cin >> mot;

    cout << "Donner le nouveau mot : ";
    cin >> nouveauMot;

    vector<string> lignes = lireFichier(nomFichier);

    cout << endl;
    cout << "===== Avec find =====" << endl;

    vector<string> lignesAvecFind = lignes;

    auto debut1 = chrono::high_resolution_clock::now();

    remplacerAvecFind(lignesAvecFind, mot, nouveauMot);

    auto fin1 = chrono::high_resolution_clock::now();

    double temps1 = chrono::duration<double>(fin1 - debut1).count();

    afficherVector(lignesAvecFind);

    cout << "Temps d'execution avec find : "
         << temps1
         << " secondes" << endl;

    cout << endl;
    cout << "===== Sans find =====" << endl;

    vector<string> lignesSansFind = lignes;

    auto debut2 = chrono::high_resolution_clock::now();

    remplacerSansFind(lignesSansFind, mot, nouveauMot);

    auto fin2 = chrono::high_resolution_clock::now();

    double temps2 = chrono::duration<double>(fin2 - debut2).count();

    afficherVector(lignesSansFind);

    cout << "Temps d'execution sans find : "
         << temps2
         << " secondes" << endl;

    return 0;
}
