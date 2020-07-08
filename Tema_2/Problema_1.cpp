#include <iostream>
using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 2.1------------------------------------" << endl
         << "Sa se implementeze o stiva sau o coada utilizând liste înlantuite. Creati initial" << endl
         << "o structura NOD cu doua câmpuri - un câmp de tip int pentru informatie si" << endl
         << "un camp de tip pointer la NOD pentru legatura la elementul urmator. Creati" << endl
         << "apoi o structura STIVA, care sa aiba un câmp de tip pointer la NOD, care" << endl
         << "reprezinta vârful stivei. De asemenea structura STIVA trebuie sa contin" << endl
         << "metodele PUSH, POP si TOP. PUSH adauga un element în vârful stivei, POP" << endl
         << "extrage elementul din vârful stivei, iar TOP returneaza valoarea aflat în vârful" << endl
         << "stivei. Adaugati de asemenea o metoda ISEMPTY, care verifica daca stiva este" << endl
         << "vida. De preferinta utilizati si un constructor, care sa initializeze vârful stivei" << endl
         << "cu NULL. În functia main a programului se va declara o stiva. Apoi se vor" << endl
         << "introduce n elemente, cu n citit de la tastatura. Aceste elemente se extrag" << endl
         << "apoi pe rând si se aseaza în ordinea de extragere. (1p)" << endl
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

struct NOD
{
    int info;
    NOD *next;
};

struct STIVA
{
    NOD *varf;
    STIVA()
    {
        varf = nullptr;
    }

    int TOP()
    {
        return varf->info;
    }

    bool ISEMPTY()
    {
        return varf == nullptr;
    }

    void PUSH(int k)
    {
        NOD *x = new NOD;
        x->info = k;
        x->next = varf;
        varf = x;
    }

    void POP()
    {
        if (ISEMPTY())
            cout << "Stiva este goala";
        else
        {
            NOD *x = varf;
            varf = varf->next;
            delete x;
        }
    }
};

int main()
{
    afisareProblema();
    int n, a;
    STIVA s;
    cout << endl
         << "Dati numarul de elemente care vreti sa introduceti in stiva n=";
    citireNumarNatural(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Elementul nr." << i + 1 << ": ";
        citireNumarNatural(a);
        s.PUSH(a);
    }
    cout << endl
         << "Elementele scoase din stiva: ";
    while (!s.ISEMPTY())
    {
        cout << s.TOP() << ", ";
        s.POP();
    }
    cout << "\b\b " << endl;
    return 0;
}
