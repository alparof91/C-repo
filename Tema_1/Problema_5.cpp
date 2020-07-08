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
         << "------------------------------------TEMA NR. 1.5------------------------------------" << endl
         << "Un profesor a studiat structura relatiilor dintre elevii sai. Pentru a reprezenta" << endl
         << "aceasta structura, profesorul a numerotat elevii de la 1 la n si a construit o" << endl
         << "matrice patratica cu n linii astfel: a(i, j) = 1 daca elevul i il agreeaza pe elevul" << endl
         << "j si 0 altfel. Se considera ca fiecare elev se agreeaza pe sine insusi. (1p) " << endl
         << "a.) Afisati pe ecran toate perechile distincte de elevi care se agreeaza reciproc." << endl
         << "b.) Afisati elevii care nu agreeaz pe nimeni." << endl
         << "c.) Afisati elevii care nu sunt agreeati de nimeni" << endl
         << endl
         << endl;
}

void citireNumarNatural(int &n)
{
    float a;
    cout << "n=";
    cin >> a;
    while (cin.fail() || a < 0 || a / int(a) > 1)
    {
        cout << "Numarul introdus trebuie sa fie natural!" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cout << "n=";
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
            if (i == j)
            {
                a[i][j] = 1;
            }
            else
            {
                cout << "a[" << i + 1 << "]"
                     << "[" << j + 1 << "]=";
                cin >> a[i][j];
            }
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
        cout << endl;
    }
    cout << endl;
}

void testReciproc(int **a, int m, int n)
{
    cout << "Elevii care se agreeaza reciproc: ";
    for (int i = 1; i < m; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[i][j] == 1 && a[j][i] == 1)
            {
                cout << "(" << j + 1 << "," << i + 1 << ");";
            }
        }
    }
    cout << '\b' << " " << endl;
}

void testNuAgreeaza(int **a, int m, int n)
{
    cout << "Elevii care nu agreeaza pe nimeni sunt: ";
    int s = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            s = s + a[i][j];
        }
        if (s == 1)
        {
            cout << i + 1 << ",";
        }
        s = 0;
    }
    cout << '\b' << " " << endl;
}

void testNuSuntAgreeati(int **a, int m, int n)
{
    int *s;
    s = new int(m);
    s[0] = 0;
    cout << "Elevii care nu sunt agreeati de nimeni: ";
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            s[j] = s[j] + a[i][j];
    }
    for (int j = 0; j < n; j++)
    {
        if (s[j] == 1)
            cout << j + 1 << ",";
    }
    cout << '\b' << " " << endl;
    delete[] s;
}

int main()
{
    int m, **a;

    afisareProblema();

    cout << "Introduceti numarul elevilor: " << endl;
    citireNumarNatural(m);
    int n = m;

    matralloc(a, m, n, int);

    cout << endl
         << "Completati matricea prietniei astfel: a[i][j] = 1 sau 0" << endl
         << "1 - daca elevul i agreeaza elevul j" << endl
         << "0 - altfel" << endl
         << endl;
    citireMatriceBazaDoi(a, m, n);

    cout << "Matricea de prietenie: " << endl;
    afisareMatrice(a, m, n);

    testReciproc(a, m, n);
    testNuAgreeaza(a, m, n);
    testNuSuntAgreeati(a, m, n);

    matrfree(a, m);
    return 0;
}