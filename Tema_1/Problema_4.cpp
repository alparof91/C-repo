#include "iostream"
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
         << "------------------------------------TEMA NR. 1.4------------------------------------" << endl
         << "Se da o matrice cu m linii si n coloane avand ca elemente valori de 0 si 1." << endl
         << "Fiecare linie reprezinta cate un numar in baza 2. Sa se afiseze aceste numere in baza 10. (1p)" << endl
         << endl;
}

void citireNumarNatural(int &n)
{
    float a;
    cin >> a;
    while (cin.fail() || a < 0 || a / int(a) > 1)
    {
        cout << "Numarul introdus trebuie sa fie natural!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> a;
    }
    n = int(a);
}

void citireMatriceBazaDoi(int **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "a[" << i << "]"
                 << "[" << j << "]=";
            cin >> a[i][j];
            if (a[i][j] / 2 >= 1)
            {
                cerr << "Matricea poate sa contina doar 1 sau 0!" << endl;
                j--;
            }
        }
    }
    cout << endl;
}

void afisareMatrice(int **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << "= " << a[i][n] << endl;
    }
    cout << endl;
}

void convertireDecimal(int **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int exp = n - j - 1;
            a[i][n] += a[i][j] * pow(2, exp);
        }
    }
}

int main()
{
    afisareProblema();
    
    int **a, m, n;

    cout << "Introduceti dimensiunile matricei: " << endl;
    cout << "m=";
    citireNumarNatural(m);
    cout << "n=";
    citireNumarNatural(n);

    matralloc(a, m, n + 1, int);

    cout << "Introduceti elementele matricei astfel incat matricea sa contina doar 0 si 1: " << endl;
    citireMatriceBazaDoi(a, m, n);

    convertireDecimal(a, m, n);
    afisareMatrice(a, m, n);

    matrfree(a, m);
}
