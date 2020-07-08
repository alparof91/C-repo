#include "iostream"
using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 1.1------------------------------------" << endl
         << "Sa se afiseze toate tripletele de numere in ordine crescatoare de pe pozitii consecutive" << endl
         << "din vectorul v de numere reale.(1p)" << endl
         << "Exemplu : pentru vectorul {20, 35, 37, 30, 12, 14, 25, 26, 0, 3, 1, 7, 14} " << endl
         << "          aceste triplete ar fi : (20, 35, 37)(12, 14, 25)(14, 25, 26)(1, 7, 14) " << endl
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
    cout << endl
         << "Introduceti elementele de numere reale ale vectorului" << endl;
    for (int i = 0; i < l; i++)
    {
        cout << "a[" << i << "]=";
        cin >> a[i];
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
         << endl
         << endl;
}

void afisareTriplete(float *a, int l)
{
    cout << "Tripletele sunt: " << endl;
    for (int i = 0; i < l; i++)
    {
        if (a[i] < a[i + 1] && a[i + 1] < a[i + 2])
        {
            cout << a[i] << "," << a[i + 1] << "," << a[i + 2] << endl;
        }
    }
}

int main()
{
    afisareProblema();

    int l;
    float *a;

    cout << "Introduceti lungimea vectorului:";
    citireNumarNatural(l);

    a = new float[int(l)];

    citireVector(a, l);
    afisareVector(a, l);
    afisareTriplete(a, l);

    delete[] a;
}
