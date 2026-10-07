#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

bool rechercherAvecFind(string mot1, string mot2)
{
    vector<char> v;

    for (char c : mot1)
        v.push_back(c);

    for (int i = 0; i < v.size(); i++)
    {
        string partie = mot1.substr(i, mot2.length());

        if (partie.find(mot2) != string::npos)
            return true;
    }

    return false;
}

bool rechercherSansFind(string mot1, string mot2)
{
    vector<char> v;

    for (char c : mot1)
        v.push_back(c);

    for (int i = 0; i <= v.size() - mot2.size(); i++)
    {
        bool trouve = true;

        for (int j = 0; j < mot2.size(); j++)
        {
            if (v[i + j] != mot2[j])
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

int main()
{
    string mot1, mot2;

    cout << "Donner le mot : ";
    cin >> mot1;

    cout << "Donner le mot a chercher : ";
    cin >> mot2;

    auto debut1 = chrono::high_resolution_clock::now();

    bool resultat1 = rechercherAvecFind(mot1, mot2);

    auto fin1 = chrono::high_resolution_clock::now();

    double temps1 = chrono::duration<double>(fin1 - debut1).count();


    auto debut2 = chrono::high_resolution_clock::now();

    bool resultat2 = rechercherSansFind(mot1, mot2);

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
