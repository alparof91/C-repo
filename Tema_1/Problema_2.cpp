#include <iostream>
using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 1.2------------------------------------" << endl
         << "Se considera vectorul de numere v cu n elemente numere naturale ( ≤ 100 )." << endl
         << "Sa se determine ce elemente apar de mai multe ori si de câte ori apare fiecare.(1p)" << endl
         << endl;
}

void citireNumarNatural(int &n)
{
    float a;
    cout << "l=";
    cin >> a;
    while (cin.fail() || a < 0 || a / int(a) > 1)
    {
        cout << "Numarul introdus trebuie sa fie natural!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cout << "l=";
        cin >> a;
    }
    n = int(a);
}

void citireVectorNatural(int *a, int l)
{
    float f;
    cout << endl
         << "Introduceti elementele de numere naturale ale vectorului <=100" << endl;
    for (int i = 0; i < l; i++)
    {
        cout << "a[" << i << "]=";
        cin >> f;
        while (cin.fail() || f < 0 || f / int(f) > 1)
        {
            cout << "Numarul introdus trebuie sa fie natural!" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "a[" << i << "]=";
            cin >> f;
        }
        a[i] = int(f);
    }
    cout << endl;
}

void afisareVector(int *a, int l)
{
    cout << "Vectorul citit: v={";
    for (int i = 0; i < l; i++)
    {
        cout << a[i] << ",";
    }
    cout << "\b"
         << "}"
         << endl;
}

void numarAparitii(int *a, int l)
{
    int ap[101];
    for (int i = 0; i < 101; i++)
    {
        ap[i] = 0;
    }
    for (int i = 0; i < l; i++)
    {
        ap[a[i]]++;
    }
    for (int i = 0; i < 101; i++)
    {
        if (ap[i] > 1)
            cout << "Numarul " << i << " apare de " << ap[i] << " ori" << endl;
    }
}

int main(void)
{
    int *v, l;

    cout << "Intorduceti lungimea vectorului v: ";
    citireNumarNatural(l);

    v = new int[int(l)];

    citireVectorNatural(v, l);
    afisareVector(v, l);
    numarAparitii(v, l);

    delete v;
    return 0;
}
