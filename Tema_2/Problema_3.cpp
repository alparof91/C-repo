#include "iostream"

using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 2.3------------------------------------" << endl
         << "Sa se implementeze o coada circulara. Pentru aceasta se cere crearea unei " << endl
         << "structuri COADA care s contin un câmp de tip vector de int numit DATA," << endl
         << "care stocheaza elementele din coada, un câmp SIZE_MAX de tip int, care" << endl
         << "reprezinta capacitatea maxima a cozii, doua câmpuri de tip int BEGIN si END," << endl
         << "care reprezinta pozitia în vectorul DATA a primului si respectiv pozitia de dupa" << endl
         << "ultimul element din coada. De asemenea se cer în structura COADA, metodele" << endl
         << "PUSH, POP, FRONT, ISEMPTY, unde PUSH adauga un element dupa ul-" << endl
         << "timul element din coada, POP extrage primul element din coada, FRONT" << endl
         << "returneaza valoarea aflat la începutul cozii si ISEMPTY verifica daca este" << endl
         << "vid sau nu coada. În functia main se declara o variabila de tip COADA, se" << endl
         << "insereaza pe rând n elemente, cu n citit de la tastatura, apoi se extrag aceste" << endl
         << "elemente pe rând si se afiseaza în ordinea extragerii. (1p)" << endl
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
        BEGIN = END = -1;
        S_MAX;
    }

    bool isEmpty()
    {
        return (BEGIN == -1);
    }

    bool isFull()
    {
        return ((BEGIN == 0 && END == (S_MAX - 1)) || ((END + 1) % S_MAX == BEGIN));
    }

    int FRONT()
    {
        return DATA[BEGIN];
    }

    void PUSH(int k)
    {

        if (isFull())
            cout << "Coada este plina. ";
        else
        {
            if (isEmpty())
                BEGIN = 0;
            END = (END + 1) % S_MAX;
            DATA[END] = k;
        }
    }

    void POP()
    {
        if (isEmpty())
            cout << "Coada este goala. ";
        else if (BEGIN == END)
        {
            DATA[BEGIN] = 0;
            BEGIN = -1;
            END = -1;
        }
        else
        {
            DATA[BEGIN] = 0;
            BEGIN = (BEGIN + 1) % S_MAX;
        }
    }
};

void afisareCoada(COADA c)
{
    cout << "Coada: ";
    for (int i = 0; i < c.S_MAX; i++)
        cout << c.DATA[i] << ", ";
    cout << "\b\b"
         << " " << endl;
}

int main()
{
    int a, s = 1;
    afisareProblema();
    COADA c;

    cout << endl
         << "Dati numarul de elemente care vreti sa introduceti in COADA n=";
    citireNumarNatural(c.S_MAX);
    c.DATA = new int[c.S_MAX];

    for (int i = 0; i < c.S_MAX; i++)
    {
        cout << endl
             << "Numar: ";
        citireNumarNatural(a);
        c.PUSH(a);
        afisareCoada(c);
    }

    cout << endl
         << "TEMA: Elementele scoase: ";
    for (int i = 0; i < c.S_MAX; i++)
    {
        cout << c.FRONT() << ", ";
        c.POP();
    }
    cout << "\b\b"
         << " " << endl
         << "Coada este vida acuma. " << endl;

    while (s != 0)
    {
        cout << endl
             << "Ce vreti sa facet?" << endl
             << "1 - introducere in coada" << endl
             << "2 - scoatere din coada" << endl
             << "3 - afisare coada" << endl
             << "4 - afisare primul si ultimul element" << endl
             << "0 - iesire" << endl
             << "Ati ales: ";
        citireNumarNatural(s);

        switch (s)
        {
        case 1:

            cout << endl
                 << "Introduceti numarul: ";
            citireNumarNatural(a);
            c.PUSH(a);
            afisareCoada(c);

            break;

        case 2:

            cout << endl;
            c.POP();
            afisareCoada(c);

            break;

        case 3:

            cout << endl;
            afisareCoada(c);

            break;

        case 4:

            cout << "Primul element din coada: " << c.FRONT() << endl;
            cout << "Ultimul element din coada: " << c.DATA[c.END] << endl;

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

    delete[] c.DATA;
    return 0;
}