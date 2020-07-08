#include <iostream>
using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 1.3------------------------------------" << endl
         << "Sa se verifice dac un vector este sortat si daca da, sa se specifice cum este" << endl
         << "sortat, crescator sau descrescator.(1p) " << endl
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

void citireVector(float *a, int l)
{
    cout << "Introduceti elementele vectorului" << endl;
    for (int i = 0; i < l; i++)
    {
        cout << "a[" << i << "]=";
        cin >> a[i];
        while (cin.fail())
        {
            cout << "Trebuie sa introduceti un numar!" << endl;
            cin.clear();
            cin.ignore(256, '\n');
            cout << "a[" << i << "]=";
            cin >> a[i];
        }
    }
    cout << endl;
}

void afisareVector(float *a, int l)
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

void testSortat(float *a, int l)
{
    int t = 0;
    for (int i = 0; i < l - 1; i++)
    {
        if (a[i] < a[i + 1] || (a[i] == a[i + 1] && a[0] < a[l - 1]))
            t++;
    }

    if (t == l - 1)
        cout << "Vectorul este sortat crescator" << endl;
    else
    {
        if (t == 0)
        {
            if (a[0] == a[l - 1])
                cout << "Vectorul contine acelasi numar de mai multe ori" << endl;
            else
                cout << "Vectorul este sortat descrescator" << endl;
        }
        else
            cout << "Vectorul nu este sortat" << endl;
    }
}

int main(void)
{
    int l;
    float *v;

    cout << "Intorduceti lungimea vectorului v: ";
    citireNumarNatural(l);

    v = new float[int(l)];

    citireVector(v, l);
    afisareVector(v, l);
    testSortat(v, l);

    delete v;
    return 0;
}
