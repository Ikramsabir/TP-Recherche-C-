#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool rechercher(string nomFichier, string mot)
{
    ifstream fichier(nomFichier);

    if (!fichier)
        return false;

    string ligne;

    while (getline(fichier, ligne))
    {
        if (ligne.find(mot) != string::npos)
        {
            fichier.close();
            return true;
        }
    }

    fichier.close();
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
