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
         << "------------------------------------TEMA NR. 1.8------------------------------------" << endl
         << "Tipariti sumele elementelor aflate pe patratele concentrice ale unei matrice patratice.(2p)"
         << endl
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

void citireMatrice(float **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "a[" << i + 1 << "]"
                 << "[" << j + 1 << "]=";
            cin >> a[i][j];
            while (cin.fail() || a[i][j] > 100)
            {
                cout << "Asteptam un numar! (<100)" << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cout << "a[" << i + 1 << "]"
                     << "[" << j + 1 << "]=";
                cin >> a[i][j];
            }
        }
    }
    cout << endl;
}

void sumaPara(float **a, int n)
{
    float *suma;
    suma = new float[n / 2];
    for (int i = 0; i < n / 2; i++)
    {

        for (int j = i; j < n - 1 - i; j++) // sumaLiniePara
        {
            suma[i] = suma[i] + a[i][j];
        }

        for (int j = n - 1 - i; j > i; j--)
        {
            suma[i] = suma[i] + a[n - i - 1][j]; //sumaLinieInvPara
        }

        for (int j = i; j < n - 1 - i; j++)
        {
            suma[i] = suma[i] + a[j][n - i - 1]; //sumaColoanaPara
        }

        for (int j = n - 1 - i; j > i; j--)
        {
            suma[i] = suma[i] + a[j][i]; //sumaColoanaInvPara
        }
        cout << "S[" << i + 1 << "]= " << suma[i] << endl;
    }
    delete[] suma;
}

void sumaImpara(float **a, int n)
{
    float *suma;
    suma = new float[n / 2];
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n / 2 - 1 - i; j <= n / 2 + i; j++) //sumaLinieImpara
        {
            suma[i] = suma[i] + a[n / 2 + 1 + i][j];
        }

        for (int j = n / 2 + 1 + i; j >= n / 2 - 1 - i; j--) //citireLinieInvImpara
        {
            suma[i] = suma[i] + a[n / 2 - 1 - i][j];
        }

        for (int j = n / 2 - i; j <= n / 2 + i; j++) //citireColoanaImpar
        {
            suma[i] = suma[i] + a[j][n / 2 - 1 - i];
        }

        for (int j = n / 2 + 1 + i; j >= n / 2 - i; j--) //citireColoanaInvImpar
        {
            suma[i] = suma[i] + a[j][n / 2 + 1 + i];
        }
    }
    for (int i = n / 2 - 1; i >= 0; i--)
        cout << "S[" << n / 2 - i << "]= " << suma[i] << endl;
    cout << "S[" << n / 2 + 1 << "]= " << a[n / 2][n / 2] << endl;
    delete[] suma;
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
         << "Introduceti elementele matricei (0 < a[i][j] < 100):" << endl; //sa fie mai vizibil la afisare
    citireMatrice(a, m, n);

    cout << endl
         << "Matricea citita este: " << endl;
    afisareMatrice(a, m, n);

    if (m % 2 == 1)
        sumaImpara(a, m);
    else
        sumaPara(a, m);

    matrfree(a, m);
    return 0;
}