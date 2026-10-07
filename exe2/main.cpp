#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool rechercher(string nomFichier, string mot)
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

int main()
{
    string nomFichier, mot;

    cout << "Donner le nom du fichier : ";
    cin >> nomFichier;

    cout << "Donner le mot a chercher : ";
    cin >> mot;

    bool resultat = rechercher(nomFichier, mot);

    if (resultat)
        cout << mot << " est contenu dans le fichier." << endl;
    else
        cout << mot << " n'est pas contenu dans le fichier." << endl;

    return 0;
}
