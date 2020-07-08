#include "iostream"

using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 2.3------------------------------------" << endl
         << "Coada cu array" << endl
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
        cout << "n=";
        cin >> a;
    }
    n = int(a);
}

struct COADA
{
    int S_MAX, BEGIN, END;
    int *DATA;

    COADA()
    {
        BEGIN = END = 0;
        S_MAX = 0;
    }

    void PUSH(int k)
    {
        if (END == (S_MAX))
        {
            cout << "Nu se mai poate adauga! ";
        }

        else
        {
            DATA[END] = k;
            END++;
        }
    }

    void POP()
    {
        if (BEGIN == END)
            cout << "Nu se mai poate extrage.";
        else
            BEGIN++;
    }

    int FRONT()
    {
        return DATA[BEGIN];
    }

    bool ISEMPTY()
    {
        return BEGIN == END;
    }
};

void afisareCoada(COADA c)
{
    if (c.BEGIN == c.END)
        cout << "Coada este goala.  ";
    else
    {
        if (c.END == c.S_MAX)
            cout << "Coada este plina.  ";

        cout << endl
             << "In coada este: ";
        for (int j = c.BEGIN; j < c.END; j++)
            cout << c.DATA[j] << ", ";
    }
    cout << "\b\b"
         << " " << endl;
}

int main()
{
    int a, s;
    afisareProblema();
    COADA c;

    cout << endl
         << "Dati numarul de elemente care vreti sa introduceti in COADA n=";
    citireNumarNatural(c.S_MAX);
    c.DATA = new int[c.S_MAX];

    while (s != 0)
    {
        cout << endl
             << "Ce vreti sa facet?" << endl
             << "1 - introducere in coada" << endl
             << "2 - scoatere din coada" << endl
             << "3 - afisare coada" << endl
             << "4 - afisare primul si ultimul element" << endl
             << "0 - iesire" << endl
             << endl
             << "Aleg: ";
        citireNumarNatural(s);

        switch (s)
        {
        case 1:

            cout << "Introduceti numarul: ";
            citireNumarNatural(a);
            c.PUSH(a);
            afisareCoada(c);

            break;

        case 2:

            cout << "Dupa scoatere: ";
            c.POP();
            afisareCoada(c);

            break;

        case 3:

            afisareCoada(c);

            break;

        case 4:

            cout << "Primul element din coada: " << c.FRONT() << endl;
            cout << "Ultimul element din coada: " << c.DATA[c.END - 1] << endl;

            break;

        case 0:
            cout << "La revedere!" << endl;
            exit(1);
            break;

        default:
            cout << "Va rog sa alegeti o optiune valida!" << endl;
            break;
        }
    }

    /*for (int i = 0; i < c.S_MAX; i++)
    {
        cout << endl
             << "Nr. " << i + 1 << ": ";
        citireNumarNatural(a);
        c.PUSH(a);
        afisareCoada(c);
    }

    for (int i = 0; i < c.S_MAX; i++)
    {
        cout << "POP si ramane:";
        c.POP();
        afisareCoada(c);
    }*/

    delete c.DATA;
    return 0;
}
