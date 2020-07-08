#include "iostream"
#include "fstream"
#include "string"
//#include "conio.h"		//am lucrat in Visual Studio CODE care afiseaza direct in terminal si nu aveam nevoie de _getch

using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 3.3------------------------------------" << endl
         << "Se considera un graf orientat G = (N, A) ponderat. Sa se determine cu ajutorul" << endl
         << "algoritmului Floyd-Warshall pentru oricare doua noduri, cel mai scurt drum" << endl
         << "între acestea. În functia main utilizatorul citeste 2 noduri si apoi afiseaza cel" << endl
         << "mai scurt drum între ele precum si care este costul drumului. (2p)" << endl
         << "(Costul minim = 1; Costul maxim = 99)" << endl
         << endl;
}

class graf
{
private:
    int nrNod;
    int **mat, **mat2;

public:
    graf()
    {
        nrNod = 0;
        mat = nullptr;
    }

    void citireMatriceFisier(string);
    void afisareMatrice();
    void inputNod(int &n);
    void verifDrumScurt(int a, int b);
    void getCostMin(int a, int b);

    ~graf()
    {
        for (int i = 0; i < nrNod; i++)
            delete[] mat[i];
        delete mat;
    }
};

void graf::citireMatriceFisier(string nfis)
{
    ifstream fisier(nfis);
    if (!fisier.is_open())
    {
        cerr << "Eroare! Nu am putut deschide '" << nfis << "' pt citire" << endl;
        //_getch();
        exit(1);
    }
    else
    {
        fisier >> nrNod;
        mat = new int *[nrNod];
        mat2 = new int *[nrNod];
        for (int i = 0; i < nrNod; i++)
        {
            mat[i] = new int[nrNod];
            mat2[i] = new int[nrNod];
            for (int j = 0; j < nrNod; j++)
            {
                fisier >> mat[i][j];
                if (i == j && mat[i][j] != 0)
                {
                    cout << endl
                         << "Greseala in fisier! Costul drumului la acelasi nod trebuie sa fie 0!" << endl;
                    exit(0);
                }
                if (i != j && mat[i][j] == 0)
                {
                    mat[i][j] = INT8_MAX; //127
                    mat2[i][j] = -1;
                }
                else
                    mat2[i][j] = j;
            }
        }
    }
}

void graf::afisareMatrice()
{
    cout << "Matricea citita: " << endl;
    for (int i = 0; i < nrNod; i++)
    {
        for (int j = 0; j < nrNod; j++)
        {
            cout << mat[i][j] << " ";
            if (mat[i][j] < 100)
                cout << "  ";
        }
        cout << endl;
    }
    cout << endl;

    // for (int i = 0; i < nrNod; i++)
    // {
    //     for (int j = 0; j < nrNod; j++)
    //     {
    //         cout << mat2[i][j] << " ";
    //         if (mat2[i][j] >= 0)
    //             cout << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
}

void graf::inputNod(int &n)
{
    float a;
    cin >> a;
    while (cin.fail() || a < 0 || a >= nrNod || a / int(a) > 1)
    {
        cout << "Introduceti un numar nod valid! (0-" << nrNod - 1 << ")" << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> a;
    }
    n = int(a);
}

void graf::verifDrumScurt(int a, int b)
{
    for (int k = 0; k < nrNod; k++)
    {
        for (int i = 0; i < nrNod; i++)
        {
            for (int j = 0; j < nrNod; j++)
            {
                if (mat[i][j] > (mat[i][k] + mat[k][j]))
                {
                    mat[i][j] = (mat[i][k] + mat[k][j]);
                    mat2[i][j] = mat2[i][k];
                }
            }
        }
    }

    cout << "Drumul cel mai scurt este: " << a << ", ";
    //int NodCur = mat2[a][b];
    while (mat2[a][b] != b)
    {
        cout << mat2[a][b] << ", ";
        a = mat2[a][b];
    }
    cout << b << endl;
}

void graf::getCostMin(int a, int b)
{
    cout << "Costul minim: " << mat[a][b] << endl;
}

int main()
{
    graf gr;
    int a, b;
    afisareProblema();
    gr.citireMatriceFisier("Problema_3.txt");
    gr.afisareMatrice();
    cout
        << "Dati nodurile intre care se cauta un drum: " << endl
        << "x = ";
    gr.inputNod(a);
    cout << "y = ";
    gr.inputNod(b);
    cout << endl;
    gr.verifDrumScurt(a, b);
    //gr.afisareMatrice();
    gr.getCostMin(a, b);
    cout << "La revedere !" << endl;
    return 0;
    //_getch();
}
