#include "iostream"
#include "queue"
#include "string"

void afisareProblema()
{
    std::cout << std::endl
              << "------------------------------------TEMA NR. 5.1------------------------------------" << std::endl
              << "Implementati un arbore binar de cautare cu chei de numere întregi. Utilizati o" << std::endl
              << "structura NOD, care are un câmp de tip int, ce stocheaza cheia nodului si trei" << std::endl
              << "câmpuri de tip pointer la NOD pentru fiul stâng, fiul drept si parintele nodului." << std::endl
              << "De asemenea structura NOD dispune de un constructor care seteaza câmpul" << std::endl
              << "int la o valoare transmis prin parametru si câmpurile de tip pointer la NOD" << std::endl
              << "le initializeaza cu NULL. Utilizati apoi o structura de tip ARBORE_CAUT," << std::endl
              << "care are ca membru RADACINA de tip pointer la NOD În plus structura" << std::endl
              << "trebuie sa aiba metodele:" << std::endl
              << "• INSERT - insereaza un nou nod în arbore (0.25 p)" << std::endl
              << "• MAXIM(NOD * x ) / MINIM(NOD * x )- returneaza nodul cu cheia maxim/minim" << std::endl
              << "  din subarborele de radacina x (0.25 p)" << std::endl
              << "• SUCCESOR(NOD *x) / PREDECESOR(NOD *x) - returneaza nodul" << std::endl
              << "  care este succesorul/predecesorul nodului x (0.25 p)" << std::endl
              << "• SEARCH(int val) - returneaza nodul cu valoarea val daca exist sau NULL altfel" << std::endl
              << "• DELETE(NOD * x ) - sterge din arbore nodul x (care a fost mai întâi" << std::endl
              << "  identificat prin SEARCH) (0.5 p)" << std::endl
              << "• PRINT_TREE(int opt) - afiseaza arborele în preordine (daca opt=1)," << std::endl
              << "  inordine (daca opt=2), în postordine (daca opt=3), pe niveluri (daca" << std::endl
              << "  opt=4). (0.5 p dintre care 0.25 pentru primele 3 afisari si 0.25 pentru a 4-a)." << std::endl
              << "• CONSTRUCT - construieste un AB cautare pornind de la un vector de chei. (0.25p)" << std::endl
              << "• EMPTY() - sterge toate nodurile din arbore (0.25 p)" << std::endl
              << std::endl
              << "Structura trebuie sa dispuna de un constructor care initializeaza RADACINA" << std::endl
              << "cu NULL. În functia main se declara o variabila de tip ARBORE_CAUT si" << std::endl
              << "se folose3te un meniu implementat cu ajutorul unei instructiuni switch, prin" << std::endl
              << "care utilizatorul sa poata selecta oricare dintre operatiile de insertie, cautare," << std::endl
              << "stergere, minim, maxim, succesor, predecesor, afisare în cele 4 moduri - la" << std::endl
              << "alegere. (1 p)" << std::endl
              << std::endl;
}
void citireNumarNatural(int &n)
{
    float a;
    std::cin >> a;
    while (std::cin.fail() || a < 0 || a / int(a) > 1)
    {
        std::cout << "Numarul introdus trebuie sa fie natural!" << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> a;
    }
    n = int(a);
}

void citireNumarIntreg(int &n)
{
    float a;
    std::cin >> a;
    while (std::cin.fail() || a / int(a) > 1)
    {
        std::cout << "Numarul introdus trebuie sa fie intreg!" << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cout << "n=";
        std::cin >> a;
    }
    n = int(a);
}

struct NOD
{
    int cheie;
    NOD *p, *stg, *dr;

    NOD(int k = 0)
    {

        cheie = k;
        p = nullptr;
        stg = nullptr;
        dr = nullptr;
    }
};

class ARBORE_CAUT
{
private:
    NOD *RADACINA;

public:
    ARBORE_CAUT()
    {
        RADACINA = nullptr;
    }

    void INSERT(int ch);
    NOD *MAXIM(NOD *);
    NOD *MINIM(NOD *);
    NOD *SUCCESOR(NOD *x);
    NOD *PREDECESOR(NOD *x);
    NOD *SEARCH(int val);
    void TRANSPLANT(NOD *u, NOD *v);
    void DELETE(NOD *x);
    void PRINT_TREE(int opt);
    void CONSTRUCT();
    void CLEAR();

    ~ARBORE_CAUT();
};

void ARBORE_CAUT::INSERT(int ch)
{
    NOD *z = new NOD(ch);
    NOD *x = RADACINA;
    NOD *y = nullptr;

    while (x != nullptr)
    {
        y = x;
        if (x->cheie < z->cheie)
            x = x->dr;
        else
            x = x->stg;
    }
    z->p = y;
    if (y == nullptr)
        RADACINA = z;
    else
    {
        if (z->cheie < y->cheie)
            y->stg = z;
        else
            y->dr = z;
    }
}

NOD *ARBORE_CAUT::MAXIM(NOD *maxDeLa)
{
    NOD *y = maxDeLa;
    while (y->dr != nullptr)
        y = y->dr;
    return y;
}

NOD *ARBORE_CAUT::MINIM(NOD *minDeLA)
{
    NOD *y = minDeLA;
    while (y->stg != nullptr)
        y = y->stg;
    return y;
}

NOD *ARBORE_CAUT::SUCCESOR(NOD *x)
{
    NOD *y;
    if (x->dr)
        return MINIM(x->dr);
    else
    {
        y = x->p;
        while (x == y->dr && y != nullptr)
        {
            x = y;
            y = y->p;
        }
        return y;
    };
}

NOD *ARBORE_CAUT::PREDECESOR(NOD *x)
{
    NOD *y;
    if (x->stg)
        return MAXIM(x->stg);
    else
    {
        y = x->p;
        while (x == y->stg && y != nullptr)
        {
            x = y;
            y = y->p;
        }
        return y;
    };
}

NOD *ARBORE_CAUT::SEARCH(int val)
{
    NOD *curent = RADACINA;
    while (curent != nullptr && val != curent->cheie)
    {
        if (val < curent->cheie)
            curent = curent->stg;
        else
            curent = curent->dr;
    }
    return curent;
}

void ARBORE_CAUT::TRANSPLANT(NOD *u, NOD *v)
{
    if (u->p == nullptr)
        RADACINA = v;
    else
    {
        if (u == u->p->stg)
            u->p->stg = v;
        else
            u->p->dr = v;
    }
    if (v != nullptr)
        v->p = u->p;
}

void ARBORE_CAUT::DELETE(NOD *z)
{
    if (z->stg == nullptr)
        TRANSPLANT(z, z->dr);
    else
    {
        if (z->dr == nullptr)
            TRANSPLANT(z, z->stg);
        else
        {
            NOD *y = SUCCESOR(z);
            if (y != z->dr)
            {
                TRANSPLANT(y, y->dr);
                y->dr = z->dr;
                z->dr->p = y;
            }
            TRANSPLANT(z, y);
            y->stg = z->stg;
            z->stg->p = y;
        }
    }
    delete z;
}

void RSD(NOD *rad) //preordine
{
    if (rad)
    {
        std::cout << rad->cheie << ", ";
        RSD(rad->stg);
        RSD(rad->dr);
    }
}

void SRD(NOD *rad) //inordine
{
    if (rad)
    {
        SRD(rad->stg);
        std::cout << rad->cheie << ", ";
        SRD(rad->dr);
    }
}

void SDR(NOD *rad) //postordine
{
    if (rad)
    {
        SDR(rad->stg);
        SDR(rad->dr);
        std::cout << rad->cheie << ", ";
    }
}

void afisarePeNiveluri(NOD *rad) //afisare pe niveluri
{
    std::queue<NOD *> coada;
    NOD *curent = rad;
    coada.push(curent);
    while (!coada.empty())
    {
        std::cout << curent->cheie << ", ";
        if (curent->stg != nullptr)
            coada.push(curent->stg);
        if (curent->dr != nullptr)
            coada.push(curent->dr);
        coada.pop();
        curent = coada.front();
    }
}

void ARBORE_CAUT::PRINT_TREE(int opt)
{
    switch (opt)
    {
    case 1:
    {
        std::cout << "RSD: ";
        RSD(RADACINA);
        break;
    }

    case 2:
    {
        std::cout << "SRD: ";
        SRD(RADACINA);
        break;
    }

    case 3:
    {
        std::cout << "SDR: ";
        SDR(RADACINA);
        break;
    }

    case 4:
    {
        std::cout << "Pe niveluri: ";
        afisarePeNiveluri(RADACINA);
        break;
    }

    case 0:
    {
        return;
        break;
    }

    default:
    {
        std::cout << std::endl
                  << "Optiune invalida!" << std::endl;
    }
    }
}

void ARBORE_CAUT::CONSTRUCT()
{
    // int v[12] = {20, 7, 10, 35, 32, 9, 6, 0, 36, 1, 17, 11};
    // for (int i = 0; i < 12; i++)
    //     INSERT(v[i]);
    int l;
    std::cout << "Lungimea vectorului: ";
    citireNumarNatural(l);
    int *v = new int[l];
    std::cout << "Cititi elementele vectorului despartite prin spatiu gol:" << std::endl
              << "V(" << l << ") = ";
    for (int i = 0; i < l; i++)
    {
        citireNumarIntreg(v[i]);
        INSERT(v[i]);
    }
    delete[] v;
}

void ARBORE_CAUT::CLEAR()
{
    while (RADACINA != nullptr)
        DELETE(RADACINA);
}

ARBORE_CAUT::~ARBORE_CAUT()
{
}

int main()
{
    afisareProblema();
    ARBORE_CAUT arboreC;
    char op = 'x';
    while (op != '0')
    {
        std::cout << std::endl
                  << "Optiuni:" << std::endl
                  << "1 - inserare nod" << std::endl
                  << "2 - afisare maxim/minim" << std::endl
                  << "3 - afisare succesor/predecesor" << std::endl
                  << "4 - cautare nod" << std::endl
                  << "5 - stergere nod" << std::endl
                  << "6 - afisare arbore" << std::endl
                  << "7 - construire din vector" << std::endl
                  << "8 - golire" << std::endl
                  << "0 - iesire" << std::endl
                  << std::endl;

        std::cout << "Aleg: ";

        std::cin >> op;
        switch (op)
        {
        case '1':
        {
            int ch;
            std::cout << std::endl
                      << "Cheie nod: ";
            citireNumarIntreg(ch);
            arboreC.INSERT(ch);
            break;
        }

        case '2':
        {
            int x;
            std::cout << std::endl
                      << "Nodul de unde se cauta maximul/miniumul: ";
            citireNumarIntreg(x);
            std::cout << std::endl
                      << "Cheia cu valoarea maxima: " << arboreC.MAXIM(arboreC.SEARCH(x))->cheie << std::endl
                      << "Cheia cu valoarea minima: " << arboreC.MINIM(arboreC.SEARCH(x))->cheie << std::endl;
            break;
        }

        case '3':
        {
            int x;
            std::cout << std::endl
                      << "Nodul pentru care se cauta succesorul/predecesorul: ";
            citireNumarIntreg(x);
            std::cout << std::endl
                      << "Succesor: " << arboreC.SUCCESOR(arboreC.SEARCH(x))->cheie << std::endl
                      << "Predecesor: " << arboreC.PREDECESOR(arboreC.SEARCH(x))->cheie << std::endl;
            break;
        }

        case '4':
        {
            int x;
            std::cout << std::endl
                      << "Nodul care se cauta: ";
            citireNumarIntreg(x);
            std::cout << std::endl
                      << "Nodul ";
            if (arboreC.SEARCH(x) == nullptr)
                std::cout << "NU este in arbore." << std::endl;
            else
                std::cout << "este in arbore." << std::endl;
            break;
        }

        case '5':
        {
            int ch;
            std::cout << "Nodul de sters: ";
            citireNumarNatural(ch);
            if (arboreC.SEARCH(ch))
                arboreC.DELETE(arboreC.SEARCH(ch));
            else
                std::cout << "NU este in arbore." << std::endl;
            break;
        }

        case '6':
        {
            int op6;
            std::cout << std::endl
                      << "Optiuni de afisare:" << std::endl
                      << "1 - afisare preordine (RSD)" << std::endl
                      << "2 - afisare inordine (SRD)" << std::endl
                      << "3 - afisare postordine (SDR)" << std::endl
                      << "4 - afisare pe niveluri" << std::endl
                      << "0 - inapoi" << std::endl
                      << std::endl;
            std::cout << "Aleg: ";
            citireNumarNatural(op6);
            arboreC.PRINT_TREE(op6);
            std::cout << std::endl;
            break;
        }

        case '7':
        {
            arboreC.CONSTRUCT();
            break;
        }

        case '8':
        {
            arboreC.CLEAR();
            break;
        }

        case '0':
        {
            std::cout << std::endl
                      << "La revedere!" << std::endl;
            exit(1);
            break;
        }

        default:
        {
            std::cout << std::endl
                      << "Optiune invalida!" << std::endl;
        }
        }
    }
}