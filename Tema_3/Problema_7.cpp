#include "iostream"
#include "string"
#include "fstream"

using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 3.6------------------------------------" << endl
         << "Se citeste dintr-un fisier un arbore binar. Sa se determine înaltimea acestuia" << endl
         << "(=lungimea celui mai lung drum de la radacina la o frunza). Se cere utilizarea" << endl
         << "unei structuri NOD pentru nodurile arborelui, care sa aiba 3 câmpuri: INFO -" << endl
         << "informatie, STANGA - pointer la NOD, DREAPTA - pointer la NOD, precum" << endl
         << "si a unei structuri (clase) ARBORE. (1p)." << endl;
}

struct NOD
{
    int INFO;
    NOD *STANGA, *DREAPTA;
};

class ARBORE
{

private:
    NOD *PARINTE;
    int nrNod, *preord, *inord;

public:
    ARBORE()
    {
        PARINTE = nullptr;
        preord = nullptr;
        inord = nullptr;
        nrNod = 0;
    }

    int nodCurent()
    {
        return PARINTE->INFO;
    }

    void citireFisier(string nfis)
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
            inord = preord = new int[nrNod];
            for (int i = 0; i < nrNod; i++)
                fisier >> preord[i];
            for (int i = 0; i < nrNod; i++)
                fisier >> inord[i];
        }
    }

    void afisareFormaSecventiala()
    {
        cout << "Am citit: " << endl
             << "preordine:";
        for (int i = 0; i < nrNod; i++)
            cout << preord[i] << ",";
        cout << "\b ";
        cout << endl
             << "inordine:";
        for (int i = 0; i < nrNod; i++)
            cout << inord[i] << ",";
    }

    void PUSH(int k)
    {
        PARINTE->INFO = k;
        NOD *x = new NOD;
    }

    ~ARBORE()
    {
    }
};

main()
{
    afisareProblema();

    ARBORE arb;
    string nfis;

    cout << endl
         << "Citire din fiser text in care arborele este reprezentat in forma secventiala: ";
    cin >> nfis;
    arb.citireFisier(nfis);

    arb.afisareFormaSecventiala();

    return 0;
}