#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool rechercher(string mot1, string mot2)
{
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

int main()
{
    string mot1, mot2;

    cout << "Donner le mot : ";
    cin >> mot1;

    cout << "Donner le mot a chercher : ";
    cin >> mot2;

    bool resultat = rechercher(mot1, mot2);

    if (resultat)
        cout << mot2 << " est contenu dans " << mot1 << endl;
    else
        cout << mot2 << " n'est pas contenu dans " << mot1 << endl;

    return 0;
}
