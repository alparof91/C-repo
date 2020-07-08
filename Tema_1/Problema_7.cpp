#include "iostream"
#include "iomanip"
#include "math.h"
using namespace std;

#define matralloc(mat, lin, col, datatype) \
    mat = new datatype *[lin];             \
    for (int i = 0; i < lin; i++)          \
        mat[i] = new datatype[col];

#define matrfree(mat, lin)        \
    for (int i = 0; i < lin; i++) \
        delete[] mat[i];

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 1.7------------------------------------" << endl
         << "Sa se scrie intr-o matrice patratica numerele de la 1 la n^2 în spirala: (2p)" << endl
         << "-pentru n impar începand din centru" << endl
         << "-pentru n par începând din colμul stânga-sus" << endl
         << endl
         << endl;
}

void citireNumarNatural(int &n)
{
    float a;
    cin >> a;
    while (cin.fail() || a < 0 || a / (int)a > 1)
    {
        cout << "Numarul introdus trebuie sa fie natural!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> a;
    }
    n = (int)a;
}

void citireLinie(float **a, int n, int i)
{
    for (int j = i; j < n - 1 - i; j++)
    {
        cout << "a[" << i + 1 << "][" << j + 1 << "]=";
        cin >> a[i][j];
    }
}

void citireLinieInv(float **a, int n, int i)
{
    for (int j = n - 1 - i; j > i; j--)
    {
        cout << "a[" << n - i << "][" << j + 1 << "]=";
        cin >> a[n - i - 1][j];
    }
}

void citireColoana(float **a, int n, int i)
{

    for (int j = i; j < n - 1 - i; j++)
    {
        cout << "a[" << j + 1 << "][" << n - i << "]=";
        cin >> a[j][n - i - 1];
    }
}
void citireColoanaInv(float **a, int n, int i)
{
    for (int j = n - 1 - i; j > i; j--)
    {
        cout << "a[" << j + 1 << "][" << i + 1 << "]=";
        cin >> a[j][i];
    }
}

void citirePara(float **a, int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        citireLinie(a, n, i);
        citireColoana(a, n, i);
        citireLinieInv(a, n, i);
        citireColoanaInv(a, n, i);
    }
}
//------------------------------------------------------------
void citireLinieImpar(float **a, int n, int i)
{
    for (int j = n / 2 - 1 - i; j <= n / 2 + i; j++)
    {
        cout << "a[" << n / 2 + 1 + i << "][" << j << "]=";
        cin >> a[n / 2 + 1 + i][j];
    }
}

void citireLinieInvImpar(float **a, int n, int i)
{
    for (int j = n / 2 + 1 + i; j >= n / 2 - 1 - i; j--)
    {
        cout << "a[" << n / 2 - 1 - i << "][" << j << "]=";
        cin >> a[n / 2 - 1 - i][j];
    }
}

void citireColoanaImpar(float **a, int n, int i)
{

    for (int j = n / 2 - i; j <= n / 2 + i; j++)
    {
        cout << "a[" << j << "][" << n / 2 - 1 - i << "]=";
        cin >> a[j][n / 2 - 1 - i];
    }
}
void citireColoanaInvImpar(float **a, int n, int i)
{
    for (int j = n / 2 + 1 + i; j >= n / 2 - i; j--)
    {
        cout << "a[" << j << "][" << n / 2 + 1 + i << "]=";
        cin >> a[j][n / 2 + 1 + i];
    }
}

void citireImpara(float **a, int n)
{
    cout << "a[" << n / 2 << "][" << n / 2 << "]=";
    cin >> a[n / 2][n / 2];

    for (int i = 0; i < n / 2; i++)
    {
        citireColoanaImpar(a, n, i);
        citireLinieImpar(a, n, i);
        citireColoanaInvImpar(a, n, i);
        citireLinieInvImpar(a, n, i);
    }
}

void afisareMatrice(float **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setiosflags(ios::left) << setw(4) << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    float **a;
    int m, n;
    afisareProblema();

    cout << "Introduceti dimensiunile matricei patratice (intreg, pozitiv, 0 < m < 100): " << endl
         << "m=n=";
    citireNumarNatural(m);

    n = m;

    matralloc(a, m, n, float);

    cout << endl
         << "Introduceti elementele matricei (0 < a[i][j] < 100):" << endl //sa fie mai vizibil la afisare
         << endl;
    if (m % 2 == 1)
        citireImpara(a, m);
    else
        citirePara(a, m);

    cout << endl
         << "Matricea citita este: " << endl;
    afisareMatrice(a, m, n);

    matrfree(a, m);
    return 0;
}