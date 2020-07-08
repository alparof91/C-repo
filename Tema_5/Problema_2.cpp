#include "iostream"
#include "queue"
#include "string"

void afisareProblema()
{
    std::cout << std::endl
              << "------------------------------------TEMA NR. 5.2------------------------------------" << std::endl
              << "Implementati un arbore rosu-negru. (pentru template 0.5 p suplimentar). Utilizati" << std::endl
              << "o structura NOD care dispune de un câmp informatie, un câmp culoare" << std::endl
              << "(NU de tip sir de caractere!!!) si câmpuri de tip pointer pentru fii stâng" << std::endl
              << "si drept si pentru parinte. De asemenea structura NOD trebuie sa dispuna" << std::endl
              << "de un constructor care seteaza câmpul informatie cu valoarea transmisa prin" << std::endl
              << "parametru, câmpul culoare la rosu si câmpurile de tip pointer în mod adecvat." << std::endl
              << "Utilizati o structura ARN care dispune de un membru de tip pointer la NOD," << std::endl
              << "numit RADACINA si un câmp de tip pointer la NOD numit NIL, care este" << std::endl
              << "nodul santinel. În plus dispune de functiile:" << std::endl
              << "• INSERT - insereaza un nou nod în arbore (0.25 p)" << std::endl
              << "• INSERT_REPARA - reface proprietatile RN dupa insertie (1 p)" << std::endl
              << "• MAXIM(NOD * x ) / MINIM(NOD * x )- returneaza nodul cu cheia maxim/minim" << std::endl
              << "  din subarborele de radacina x (0.25 p ambele functii)" << std::endl
              << "• SUCCESOR(NOD *x) / PREDECESOR(NOD *x) - returneaza nodul" << std::endl
              << "  care este succesorul / predecesorul nodului x (0.25 p ambele functii)" << std::endl
              << "• SEARCH(int val) - returneaza nodul cu valoarea val daca exista sau" << std::endl
              << "  NULL altfel. (0.25 p)" << std::endl
              << "• DELETE(NOD * x ) - sterge din arbore nodul x (care a fost mai întâi" << std::endl
              << "  identificat prin SEARCH) (0.5 p)" << std::endl
              << "• DELETE_REPARA(NOD * x ) - reface proprietatile RN dupa stergere (1 p)" << std::endl
              << "• ROT_ST, ROT_DR - functiile de rotatie - (0.25 p)" << std::endl
              << "• CLEAR() - sterge toate nodurile din arbore (0.5 p)" << std::endl
              << "• PRINT_TREE(int opt) - afiseaza arborele în preordine (daca opt=1)," << std::endl
              << "  inordine (daca opt=2), în postordine (daca opt=3), pe niveluri (daca" << std::endl
              << "  opt=4). (0.5 p dintre care 0.25 pentru primele 3 afisari si 0.25 pentru a" << std::endl
              << "  4-a). Trebuie afisat si culoarea pentru fiecare nod." << std::endl
              << "• CONSTRUCT - construieste un ARN pornind de la un vector de chei. (0.25p)" << std::endl
              << std::endl
              << "Structura trebuie sa dispuna de un constructor care initializeaza RADACINA" << std::endl
              << "si santinela în modul prezentat la curs. În functia main se declara o variabila" << std::endl
              << "de tip ARN si se foloseste un menu implementat cu ajutorul unei instructiuni" << std::endl
              << "switch, prin care utilizatorul sa poata selecta oricare dintre operatiile de" << std::endl
              << "insertie, cautare, stergere, minim, maxim, succesor, predecesor, afisare în cele 4" << std::endl
              << "moduri - la alegere. (0.25 p)" << std::endl
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
    char culoare;
    NOD *p, *stg, *dr;

    NOD(int k = 0)
    {

        cheie = k;
        culoare = 'r';
        p = nullptr;
        stg = nullptr;
        dr = nullptr;
    }
};

class ARBORE_CAUT
{
private:
    NOD *RADACINA;
    NOD *NIL;

public:
    ARBORE_CAUT()
    {
        NIL = new NOD(999);
        NIL->culoare = 'n';
        NIL->stg = NIL->dr = NIL->p = NIL;
        RADACINA = NIL;
    }

    void RN_ROT_ST(NOD *);
    void RN_ROT_DR(NOD *);
    void RN_INSERT(int);
    void RN_INSERT_REPARA(NOD *);
    NOD *MAXIM(NOD *);
    NOD *MINIM(NOD *);
    NOD *SUCCESOR(NOD *);
    NOD *PREDECESOR(NOD *);
    NOD *SEARCH(int val);
    void RN_TRANSPLANT(NOD *, NOD *);
    void RN_DELETE(NOD *);
    void RN_DELETE_REPARA(NOD *);
    void RSD(NOD *);
    void SRD(NOD *);
    void SDR(NOD *);
    void afisarePeNiveluri(NOD *);
    void PRINT_TREE(int);
    void CONSTRUCT();
    void CLEAR();

    ~ARBORE_CAUT();
};

void ARBORE_CAUT::RN_ROT_ST(NOD *y)
{
    NOD *x = y->dr;
    y->dr = x->stg;

    if (x->stg != NIL)
        x->stg->p = y;

    x->p = y->p;

    if (y->p == NIL)
        RADACINA = x;
    else
    {
        if (y == y->p->stg)
            y->p->stg = x;
        else
            y->p->dr = x;
    }
    x->stg = y;
    y->p = x;
}

void ARBORE_CAUT::RN_ROT_DR(NOD *y)
{
    NOD *x = y->stg;
    y->stg = x->dr;

    if (x->dr != NIL)
        x->dr->p = y;

    x->p = y->p;

    if (y->p == NIL)
        RADACINA = x;
    else
    {
        if (y == y->p->stg)
            y->p->stg = x;
        else
            y->p->dr = x;
    }
    x->dr = y;
    y->p = x;
}

void ARBORE_CAUT::RN_INSERT_REPARA(NOD *Z)
{
    while (Z->p->culoare == 'r') //cand parintele lui Z este negru rezulta un ARN valid
    {
        if (Z->p->p->stg == Z->p) //lucram pe partea stanga
        {
            NOD *U = Z->p->p->dr;
            if (U->culoare == 'r') //Cazul 1: Unchiul lui Z este rosu
            {
                Z->p->culoare = 'n';
                U->culoare = 'n';
                Z->p->p->culoare = 'r';
                Z = Z->p->p;
            }
            else //Cazul 2 si 3: Unchiul lui Z este negru (implicit cazul 3 - Z este in exterior)
            {
                if (Z == Z->p->dr) //Cazul 2 - Z este in interior, din care se trece in cazul 3
                {
                    Z = Z->p;
                    RN_ROT_ST(Z);
                }
                Z->p->culoare = 'n';
                Z->p->p->culoare = 'r';
                RN_ROT_DR(Z->p->p);
            }
        }
        else //lucram pe partea dreapta
        {
            NOD *U = Z->p->p->stg;
            if (U->culoare == 'r') //Cazul 1: Unchiul lui Z este rosu
            {
                Z->p->culoare = 'n';
                U->culoare = 'n';
                Z->p->p->culoare = 'r';
                Z = Z->p->p;
            }
            else //Cazul 2 si 3: Unchiul lui Z este negru (implicit cazul 3 - Z este in exterior)
            {
                if (Z == Z->p->stg) //Cazul 2 - Z este in interior, din care se trece in cazul 3
                {
                    Z = Z->p;
                    RN_ROT_DR(Z);
                }
                Z->p->culoare = 'n';
                Z->p->p->culoare = 'r';
                RN_ROT_ST(Z->p->p);
            }
        }
    }
    RADACINA->culoare = 'n';
}

void ARBORE_CAUT::RN_INSERT(int ch)
{
    NOD *z = new NOD(ch);
    NOD *x = RADACINA;
    NOD *y = NIL;

    while (x != NIL)
    {
        y = x;
        if (x->cheie < z->cheie)
            x = x->dr;
        else
            x = x->stg;
    }
    z->p = y;
    if (y == NIL)
        RADACINA = z;
    else
    {
        if (z->cheie < y->cheie)
            y->stg = z;
        else
            y->dr = z;
    }
    z->stg = NIL;
    z->dr = NIL;
    z->culoare = 'r';
    RN_INSERT_REPARA(z);
}

NOD *ARBORE_CAUT::MAXIM(NOD *M)
{
    NOD *y = M;
    while (y->dr != NIL)
        y = y->dr;
    return y;
}

NOD *ARBORE_CAUT::MINIM(NOD *m)
{
    NOD *y = m;
    while (y->stg != NIL)
        y = y->stg;
    return y;
}

NOD *ARBORE_CAUT::SUCCESOR(NOD *X)
{
    NOD *y;
    if (X->dr)
        return MINIM(X->dr);
    else
    {
        y = X->p;
        while (X == y->dr && y != NIL)
        {
            X = y;
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
        while (x == y->stg && y != NIL)
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
    while (curent != NIL && val != curent->cheie)
    {
        if (val < curent->cheie)
            curent = curent->stg;
        else
            curent = curent->dr;
    }
    return curent;
}

void ARBORE_CAUT::RN_TRANSPLANT(NOD *u, NOD *v)
{
    if (u->p == NIL)
        RADACINA = v;
    else
    {
        if (u == u->p->stg)
            u->p->stg = v;
        else
            u->p->dr = v;
    }
    v->p = u->p;
}

void ARBORE_CAUT::RN_DELETE_REPARA(NOD *x)
{
    while (x != RADACINA && x->culoare == 'n')
        if (x == x->p->stg) //lucram pe partea stanga
        {
            NOD *F = x->p->dr;     //fratele lui x
            if (F->culoare == 'r') //cazul 1
            {
                F->culoare = 'n';
                x->p->culoare = 'r';
                RN_ROT_ST(x->p);
                F = x->p->dr;
            }
            if (F->stg->culoare == 'n' && F->dr->culoare == 'n') //cazul 2
            {
                F->culoare = 'r';
                x = x->p;
            }
            else //cazul 3 si 4
            {
                if (F->dr->culoare == 'n') //cazul 3
                {
                    F->stg->culoare = 'n';
                    F->culoare = 'r';
                    RN_ROT_DR(F);
                    F = x->p->dr;
                } //se ajunge in cazul 4
                F->culoare = x->p->culoare;
                x->p->culoare = 'n';
                F->dr->culoare = 'n';
                RN_ROT_ST(x->p);
                x = RADACINA;
            }
        }
        else //lucram pe partea dreapta
        {
            NOD *F = x->p->stg;    //fratele lui x
            if (F->culoare == 'r') //cazul 1
            {
                F->culoare = 'n';
                x->p->culoare = 'r';
                RN_ROT_DR(x->p);
                F = x->p->stg;
            }
            if (F->stg->culoare == 'n' && F->dr->culoare == 'n') //cazul 2
            {
                F->culoare = 'r';
                x = x->p;
            }
            else //cazul 3 si 4
            {
                if (F->stg->culoare == 'n') //cazul 3
                {
                    F->dr->culoare = 'n';
                    F->culoare = 'r';
                    RN_ROT_ST(F);
                    F = x->p->stg;
                } //se ajunge in cazul 4
                F->culoare = x->p->culoare;
                x->p->culoare = 'n';
                F->stg->culoare = 'n';
                RN_ROT_DR(x->p);
                x = RADACINA;
            }
        }
    x->culoare = 'n';
}

void ARBORE_CAUT::RN_DELETE(NOD *z)
{
    NOD *y = z;
    NOD *x;
    char culOrig_y = y->culoare;
    if (z->stg == NIL) //cazul a)
    {
        x = z->dr;
        RN_TRANSPLANT(z, x);
    }
    else //cazul b), c), d)
    {
        if (z->dr == NIL) //cazul b)
        {
            x = z->stg;
            RN_TRANSPLANT(z, x);
        }
        else
        {
            y = MAXIM(z->stg); //predecesor ca sa pot sa verific cu Tree visualizator
            culOrig_y = y->culoare;
            x = y->stg; //pentru ca lucram cu predecesor
            if (y->p == z) //cazul c)
                x->p = y;
            else //cazul d)
            {
                RN_TRANSPLANT(y, x);
                y->stg = z->stg;  //pentru ca lucram cu predecesor
                z->stg->p = y;  //pentru ca lucram cu predecesor
            }
            RN_TRANSPLANT(z, y);
            y->dr = z->dr; //pentru ca lucram cu predecesor
            z->dr->p = y;  //pentru ca lucram cu predecesor
            y->culoare = z->culoare;
        }
    }
    if (culOrig_y == 'n')
            RN_DELETE_REPARA(x);
    delete z;
}

void ARBORE_CAUT::RSD(NOD *rad) //preordine
{
    if (rad != NIL)
    {
        std::cout << rad->cheie << "(" << rad->culoare << "),";
        RSD(rad->stg);
        RSD(rad->dr);
    }
}

void ARBORE_CAUT::SRD(NOD *rad) //inordine
{
    if (rad != NIL)
    {
        SRD(rad->stg);
        std::cout << rad->cheie << "(" << rad->culoare << "),";
        SRD(rad->dr);
    }
}

void ARBORE_CAUT::SDR(NOD *rad) //postordine
{
    if (rad != NIL)
    {
        SDR(rad->stg);
        SDR(rad->dr);
        std::cout << rad->cheie << "(" << rad->culoare << "),";
    }
}

void ARBORE_CAUT::afisarePeNiveluri(NOD *rad) //afisare pe niveluri
{
    std::queue<NOD *> coada;
    NOD *curent = rad;
    coada.push(curent);
    while (!coada.empty())
    {
        std::cout << curent->cheie << "(" << curent->culoare << "),";
        if (curent->stg != NIL)
            coada.push(curent->stg);
        if (curent->dr != NIL)
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
    int v[22] = {40, 20, 58, 10, 29, 47, 65, 7, 16, 24, 35, 44, 51, 63, 70, 2, 9, 32, 37, 68, 31, 39};
    for (int i = 0; i < 22; i++)
        RN_INSERT(v[i]);

    // int v[12] = {20, 7, 10, 35, 32, 9, 6, 0, 36, 1, 17, 11};
    // for (int i = 0; i < 12; i++)
    //     RN_INSERT(v[i]);

    // int l;
    // std::cout << "Lungimea vectorului: ";
    // citireNumarNatural(l);
    // int *v = new int[l];
    // std::cout << "Cititi elementele vectorului despartite prin spatiu gol:" << std::endl
    //           << "V(" << l << ") = ";
    // for (int i = 0; i < l; i++)
    // {
    //     citireNumarIntreg(v[i]);
    //     INSERT(v[i]);
    // }
    // delete[] v;
}

void ARBORE_CAUT::CLEAR()
{
    while (RADACINA != NIL)
        RN_DELETE(RADACINA);
}

ARBORE_CAUT::~ARBORE_CAUT()
{
    delete NIL;
}

int main()
{
    afisareProblema();
    ARBORE_CAUT ARN;
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
            ARN.RN_INSERT(ch);
            break;
        }

        case '2':
        {
            int x;
            std::cout << std::endl
                      << "Nodul de unde se cauta maximul/miniumul: ";
            citireNumarIntreg(x);
            std::cout << std::endl
                      << "Cheia cu valoarea maxima: " << ARN.MAXIM(ARN.SEARCH(x))->cheie << std::endl
                      << "Cheia cu valoarea minima: " << ARN.MINIM(ARN.SEARCH(x))->cheie << std::endl;
            break;
        }

        case '3':
        {
            int x;
            std::cout << std::endl
                      << "Nodul pentru care se cauta succesorul/predecesorul: ";
            citireNumarIntreg(x);
            std::cout << std::endl
                      << "Succesor: " << ARN.SUCCESOR(ARN.SEARCH(x))->cheie << std::endl
                      << "Predecesor: " << ARN.PREDECESOR(ARN.SEARCH(x))->cheie << std::endl;
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
            if (!ARN.SEARCH(x))
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
            if (ARN.SEARCH(ch))
                ARN.RN_DELETE(ARN.SEARCH(ch));
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
            ARN.PRINT_TREE(op6);
            std::cout << std::endl;
            break;
        }

        case '7':
        {
            ARN.CONSTRUCT();
            break;
        }

        case '8':
        {
            ARN.CLEAR();
            break;
        }

        case '0':
        {
            std::cout << std::endl
                      << "La revedere!" << std::endl;
            std::cout << sizeof(ARN);
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
