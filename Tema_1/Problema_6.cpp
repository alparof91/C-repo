#include "iostream"
#include "math.h"
using namespace std;

typedef unsigned long long int ullong;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 1.6------------------------------------" << endl
         << "Se considera un numar natural cu n cifre. Se taie p cifre, p < n , astfel incat" << endl
         << "numarul ramas sa fie cel mai mare posibil. Nu este permis schimbarea ordinii cifrelor în numar.(3p)." << endl
         << endl
         << endl;
}
template <class T>
void citireNumarNatural(T &n, T r)
{
    double a;
    cin >> a;
    while (cin.fail() || a < 0 || a / (T)a > 1 || a > r)
    {
        if (a > r)
            cout << "Numarul trebuie sa fie mai mic decat " << r << endl;
        else
            cout << "Numarul introdus trebuie sa fie natural!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> a;
    }
    n = (ullong)a;
}

void lungimeNumar(ullong nr, int &l)
{
    while (nr >= 1)
    {
        nr /= 10;
        l += 1;
    }
}

void numarInVector(ullong nr, int l, int *v)
{
    for (int i = l - 1; i >= 0; i--)
    {
        v[i] = nr % 10;
        nr /= 10;
    }
}

void afisareVector(int *v, int l)
{
    for (int i = 0; i < l; i++)
    {
        cout << v[i];
    }
}

void scoatereDinVector(int *v, int l, ullong p)
{
    for (int i = 1; i <= p; i++)
    {

        int j = 0;
        while (v[j] >= v[j + 1])
        {
            j++;
        }
        for (int r = j; r < l - i; r++)
        {
            v[r] = v[r + 1];
        }
        v[l - i] = 0;
    }
}

int main()
{
    ullong nr, lim = pow(2, 61);
    int p, l = 0, *v;

    afisareProblema();

    cout << "Introduceti un numar natural (maxim 18 caractere): " << endl
         << "a=";
    citireNumarNatural(nr, lim);

    lungimeNumar(nr, l);

    cout << endl
         << "Numarul " << nr << " este compus din n=" << l << " caractere. Cate caractere vreti sa taiem? " << endl
         << "p=";
    citireNumarNatural(p, l);

    v = new int[l];
    numarInVector(nr, l, v);
    scoatereDinVector(v, l, p);

    cout << endl
         << "Numarul maxim posibil este: ";
    afisareVector(v, l - p);
    cout << endl;
    delete[] v;
}
