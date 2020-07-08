#include "iostream"
using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 2.5------------------------------------" << endl
         << "Sa se implementeze o lista simplu înlantuita cu functionalitatile descrise în" << endl
         << "continuare. Se cere utilizarea unei structuri NOD care are dou câmpuri: un" << endl
         << "câmp int pentru informatie si un câmp de tip pointer la NOD pentru legatura" << endl
         << "câtre urmatorul element. Se cere utilizarea unei structuri LISTA care are ca" << endl
         << "membru un pointer la NOD reprezentând capul listei si metodele:" << endl
         << "• INSERT - insereaza un element în capul listei (0.25 p)" << endl
         << "• SEARCH - cauta o cheie k în lista (0.25 p)" << endl
         << "• DELETE - sterge un element din lista (0.25 p)" << endl
         << "• ISEMPTY - verifica daca lista e vida (0.25 p)" << endl
         << "• INVERSE - inverseaza lista în compelxitate O(n), fara a folosi mai mult" << endl
         << "  decât o zona de memorie constanta, cu exceptia celei ocupate de lista" << endl
         << "  (adica fara a construi o a doua lista) (1 p)" << endl
         << "• INSERT_AFTER - insereaza o cheie k dupa un nod cu o anumita cheie" << endl
         << "  m data, sau la capatul listei, daca m nu exista în lista. (0.5 p)" << endl
         << "• INSERT_N_POZ - insereaza de n ori cheia k pe pozitia p, daca lista are" << endl
         << "  cel putin p elemente, sau la sfârsitul listei altfel. (1p)" << endl
         << "• PRINT_LIST - afiseaza elementele din lista (0.25 p)" << endl
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

struct LISTA
{
    NOD *cap;

    LISTA()
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
        p->info = k;
        p->next = cap;
        cap = p;
    }

    void INSERT_CAP(NOD *p) //cand definesc nodul in afara structurii
    {
        p->next = cap;
        cap = p;
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
                    cout << "Potrivire la pozitia " << poz << endl;
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
        delete p;
    }

    void DELETE(int k)
    {
        int nr = 0;
        NOD *p = cap;
        NOD *ant = cap;
        if (ISEMPTY())
            cout << "Lista este goala" << endl;
        else
        {
            while (p != nullptr)
            {
                if (p->info == k)
                {
                    nr++;
                    if (p == cap)
                    {
                        DELETE_CAP();
                        ant = p;
                        break;
                    }
                    else
                    {
                        ant->next = p->next;
                        delete p;
                        break;
                    }
                }
                if (ant != p)
                    ant = ant->next;
                p = p->next;
            }
            if (nr == 0)
                cout << "Nu am gasit elementul cautat in lista." << endl;
        }
    }

    void INSERT_AFTER(int i, int k)
    {
        int nr = 0, poz = 1;
        NOD *ins = new NOD();
        NOD *p = cap;
        ins->info = i;
        if (ISEMPTY())
            cout << "Lista este goala" << endl;
        else
        {
            while (p != nullptr)
            {
                if (p->info == k)
                {
                    nr++;
                    cout << "Inseram dupa pozitia " << poz << endl;
                    ins->next = p->next;
                    p->next = ins;
                    break;
                }
                p = p->next;
                poz++;
            }
            if (nr == 0)
            {
                cout << "Nu am gasit " << k << " inseram la capat" << endl;
                INSERT_CAP(i);
            }
        }
    }

    void INSERT_N_POZ(int i, int k, int n)
    {
        int poz = 2;
        NOD *p = cap;
        if (ISEMPTY())
            cout << "Lista este goala" << endl;
        else
        {
            if (k <= 1)
            {
                for (int j = 0; j < n; j++)
                    INSERT_CAP(i);
            }
            else
            {
                while (p != nullptr)
                {
                    if (poz == k || p->next == nullptr)
                    {
                        for (int j = 0; j < n; j++)
                        {
                            NOD *ins = new NOD();
                            ins->info = i;
                            ins->next = p->next;
                            p->next = ins;
                        }
                        break;
                    }
                    p = p->next;
                    poz++;
                }
            }
        }
    }

    /*void INVERSE()
    {
        int nr = 0, poz = 1;
        NOD *p = cap;
        NOD *cap2 = cap;
        if (ISEMPTY())
            cout << "Lista este goala" << endl;
        else
        {
            cap2 = nullptr;
            while (p != nullptr)
            {
                p->next = cap2;
                cap2 = p;
                p = p->next;
                poz++;
            }
            if (nr == 0)
                cout << "Nu am gasit elementul cautat in lista." << endl;
        }
    }*/

    void PRINT_LIST()
    {
        if (ISEMPTY())
            cout << "Lista este goala" << endl;
        else
        {
            NOD *p = cap;
            while (p != nullptr)
            {
                cout << (p->info) << "->";
                p = p->next;
            }
            cout << "|NULL " << endl;
        }
    }
};

int main()
{
    LISTA l;
    int n, nr, p, s = 1;
    afisareProblema();

    while (s != 0)
    {
        cout << endl
             << "Alegeti una dintre optiuni:" << endl
             << "1 - INSERT" << endl
             << "2 - SEARCH" << endl
             << "3 - DELETE" << endl
             << "4 - ISEMPTY" << endl
             << "5 - INVERSE - nerezolvat" << endl
             << "6 - INSERT_AFTER" << endl
             << "7 - INSERT_N_POZ" << endl
             << "8 - PRINT_LIST" << endl
             << "0 - iesire" << endl
             << "Ati ales: ";

        citireNumarNatural(s);
        cout << endl
             << endl;

        switch (s)
        {
        case 1:

            cout << "Numarul de adaugat: ";
            citireNumarNatural(n);
            l.INSERT_CAP(n);
            cout << "Lista dupa adaugare: ";
            l.PRINT_LIST();

            break;

        case 2:

            cout << "Elementul cautat in lista: ";
            citireNumarNatural(n);
            cout << "In lista: ";
            l.PRINT_LIST();
            l.SEARCH(n);

            break;

        case 3:

            cout << "Elementul de sters din lista: ";
            citireNumarNatural(n);
            l.DELETE(n);
            cout << "Lista dupa stergere: ";
            l.PRINT_LIST();

            break;

        case 4:

            if (l.ISEMPTY())
                cout << "Lista este goala." << endl;
            else
                cout << "Lista NU este goala." << endl;

            break;

        case 5:

            cout << "In dezvoltare" << endl;

            break;

        case 6:

            cout << "Elementul de inserat in lista: ";
            citireNumarNatural(n);
            cout << "Elementul dupa care se insereaza: ";
            citireNumarNatural(p);
            l.INSERT_AFTER(n, p);
            cout << "Lista dupa inserare: ";
            l.PRINT_LIST();

            break;

        case 7:

            cout << "Elementul de inserat in lista: ";
            citireNumarNatural(n);
            cout << "De cate ori sa inseram? ";
            citireNumarNatural(nr);
            cout << "Pozitia la care se insereaza: ";
            citireNumarNatural(p);
            l.INSERT_N_POZ(n, p, nr);
            cout << "Lista dupa inserare: ";
            l.PRINT_LIST();

            break;

        case 8:

            l.PRINT_LIST();

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
