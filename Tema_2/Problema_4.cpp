#include "iostream"
using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 2.4------------------------------------" << endl
         << "Sa se implementeze algoritmul de sortare Bucket-sort utilizând liste dublu" << endl
         << "înlantuite. Utilizati o structura LISTA_DUBLU, care s aiba ca membrii un" << endl
         << "pointer la NOD, reprezentând capul listei si metodele:" << endl
         << "• INSERT_SORT - insereaza o cheie într-o lista ordonata pe pozitia potrivita." << endl
         << "• MERGE - uneste lista cu alta lista transmis ca parametru" << endl
         << "• INSERT - insereaza în capul listei." << endl
         << "• PRINT - afiseaza elementele stocate în lista." << endl
         << "Utilizati un constructor pentru initializarea capului listei cu NULL." << endl
         << "Structura NOD utilizat în lista dublu înlantuita trebuie sa aiba câmpurile" << endl
         << "INFO, NEXT si PREV." << endl
         << "Algoritmul poate fi gasit în cartea 'Introduction to Algorithms third edition'" << endl
         << "de T.C. Cormen, C.E. Leiserson, R.L. Rivest, C. Stein (2p)" << endl
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
    NOD *next, *prev;
};

struct LISTA_DUBLU
{
    NOD *cap;

    LISTA_DUBLU()
    {
        cap = nullptr;
    }

    int CAP()
    {
        return cap->info;
    }

    bool ISEMPTY()
    {
        return cap == nullptr;
    }

    void INSERT_CAP(int k)
    {
        NOD *p = new NOD();
        if (cap != nullptr)
            cap->prev = p;
        p->info = k;
        p->next = cap;
        p->prev = nullptr;
        cap = p;
    }

    void PRINT()
    {
        if (ISEMPTY())
            cout << "Lista este goala" << endl;
        else
        {
            NOD *p = cap;
            cout << "NULL|-";
            while (p != nullptr)
            {
                cout << (p->info) << "-";
                p = p->next;
            }
            cout << "|NULL " << endl;
        }
    }

    void SEARCH(int k)
    {
        int nr = 0, poz = 1;
        NOD *p = cap;

        if (ISEMPTY())
            cout << "Lista este goala" << endl;
        else
        {
            while (p != nullptr)
            {
                if (p->info == k)
                {
                    nr++;
                    cout << "Potrivire la pozitia " << poz << " (S-a sters)" << endl;
                }
                p = p->next;
                poz++;
            }
            if (nr == 0)
                cout << "Nu am gasit elementul cautat in lista." << endl;
        }
    }

    void DELETE_CAP()
    {
        NOD *p = cap;
        cap = p->next;
        cap->prev = nullptr;
        delete p;
    }

    void DELETE(int k)
    {
        int nr = 0, poz = 1;
        NOD *p = cap;
        if (ISEMPTY())
            cout << "Lista este goala" << endl;
        else
        {
            while (p != nullptr)
            {
                if (p->info == k)
                {
                    nr++;
                    if (p->prev != NULL)
                        p->prev->next = p->next;
                    else
                        cap = p->next;

                    if (p->next != NULL)
                        p->next->prev = p->prev;
                }
                p = p->next;
                poz++;
            }
            if (nr == 0)
                cout << "Nu am gasit elementul cautat in lista." << endl;
        }
    }
};

int main()
{
    LISTA_DUBLU l;
    int n, s = 1;
    afisareProblema();

    while (s != 0)
    {
        cout << endl
             << "Alegeti una dintre optiuni:" << endl
             << "1 - INSERT_SORT- nerezolvat" << endl
             << "2 - MERGE- nerezolvat" << endl
             << "3 - INSERT" << endl
             << "4 - DELETE" << endl
             << "5 - PRINT_LIST" << endl
             << "0 - iesire" << endl
             << "Ati ales: ";

        citireNumarNatural(s);
        cout << endl
             << endl;

        switch (s)
        {
        case 1:

            cout << "In dezvoltare" << endl;

            break;

        case 2:

            cout << "In dezvoltare" << endl;

            break;

        case 3:

            cout << "Elementul de inserat in lista: ";
            citireNumarNatural(n);
            l.INSERT_CAP(n);
            l.PRINT();

            break;

        case 4:

            cout << "Elementul de sters din lista: ";
            citireNumarNatural(n);
            l.DELETE(n);
            l.PRINT();

            break;

        case 5:

            l.PRINT();

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
}
