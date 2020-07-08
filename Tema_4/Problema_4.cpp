#include "iostream"
#include "string"
#include "fstream"
#include "math.h"
#include "iomanip"
#include "stack"

struct nod
{
    std::string nume;
    int crt;
    double *pret;

    nod()
    {
        crt = 0;
        nume = "";
        pret = nullptr;
    }

    nod(int c, std::string oras, int nr)
    {
        crt = c;
        nume = oras;
        pret = new double[nr];
    }
    ~nod()
    {
        delete[] pret;
    }
};

class PRIORITY_QUEUE
{
private:
    int SIZE, CAP;
    std::pair<double, int> *DATA;

public:
    PRIORITY_QUEUE(int capacitate = 50)
    {
        CAP = capacitate;
        DATA = new std::pair<double, int>[CAP];
        SIZE = 0;
    }

    int GET_SIZE();
    std::pair<double, int> MIN_ELEMENT();
    void MIN_HEAPFY();
    void INCREASE_KEY(int, std::pair<double, int>);
    void INSERT(std::pair<double, int>);
    void EXTRACT_MIN();
    void PRINT_QUEUE();

    ~PRIORITY_QUEUE()
    {
        delete[] DATA;
    }
};

int PRIORITY_QUEUE::GET_SIZE()
{
    return SIZE;
}

std::pair<double, int> PRIORITY_QUEUE::MIN_ELEMENT()
{
    return DATA[0];
}

void PRIORITY_QUEUE::MIN_HEAPFY() // SIFT_DOWN (iterativ)
{
    int imin, p, st, dr;
    std::pair<double, int> aux;
    for (int i = (SIZE - 1) / 2; i >= 0; i--)
    {
        imin = i;
        while (2 * imin + 1 < SIZE) //cat timp imin are copii (nu este frunza)
        {
            p = imin;
            st = 2 * imin + 1;
            dr = 2 * imin + 2;

            if (st < SIZE && DATA[st].first < DATA[imin].first)
                imin = st;
            if (dr < SIZE && DATA[dr].first < DATA[imin].first)
                imin = dr;
            if (imin != p)
            {
                aux = DATA[imin];
                DATA[imin] = DATA[p];
                DATA[p] = aux;
            }
            else
                break;
        }
    }
}

void PRIORITY_QUEUE::INCREASE_KEY(int k, std::pair<double, int> val)
{
    DATA[k] = val;
    int p = (k - 1) / 2;
    std::pair<double, int> aux;
    while (k > 0 && DATA[p].first > val.first)
    {
        aux = DATA[k];
        DATA[k] = DATA[p];
        DATA[p] = aux;
        p = (k - 1) / 2;
    }
}

void PRIORITY_QUEUE::INSERT(std::pair<double, int> a)
{
    DATA[SIZE] = a;
    INCREASE_KEY(SIZE, a);
    SIZE++;
}

void PRIORITY_QUEUE::EXTRACT_MIN()
{
    if (SIZE < 1)
    {
        std::cout << "Coada este goala!" << std::endl;
        return;
    }
    else
    {
        DATA[0] = DATA[SIZE - 1];
        DATA[SIZE - 1].first = 0;
        DATA[SIZE - 1].second = 0;
        SIZE--;
        MIN_HEAPFY();
    }
}

void PRIORITY_QUEUE::PRINT_QUEUE()
{
    for (int i = 0; i < SIZE; i++)
        std::cout << "(" << DATA[i].first << "," << DATA[i].second << "), ";
    std::cout << std::endl;
}

class graf
{
private:
    int nrNod;
    nod *orase;

public:
    graf()
    {
        nrNod = 0;
        orase = nullptr;
    }
    void citireMatriceFisier(std::string);
    void afisareListaPret();
    void drumPretMic(int, int);

    ~graf()
    {
        delete[] orase;
    }
};

void graf::citireMatriceFisier(std::string nfis = "Problema_4.txt")
{
    std::ifstream fisier(nfis);
    if (!fisier.is_open())
    {
        std::cerr << "Eroare! Nu am putut deschide '" << nfis << "' pt citire" << std::endl;
        //_getch();
        exit(1);
    }
    else
    {
        std::string aux;
        fisier >> nrNod;
        for (int i = 0; i < nrNod; i++)
            fisier >> aux;
        orase = new nod[nrNod];
        for (int i = 0; i < nrNod; i++)
        {
            fisier >> orase[i].crt;
            fisier >> orase[i].nume;
            orase[i].pret = new double[nrNod];
            for (int j = 0; j < nrNod; j++)
                fisier >> orase[i].pret[j];
        }
    }
}

void graf::afisareListaPret()
{
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl
              << "| nr.|          |                           Pret bilet (RON)                                 |" << std::endl
              << "|crt.|   Oras   |----------------------------------------------------------------------------|" << std::endl
              << "|    |          |";
    for (int i = 0; i < nrNod; i++)
        std::cout << std::setw(10) << std::right << orase[i].nume << "|";
    std::cout << std::endl
              << "|----+----------+----------+----------+----------+----------+----------+----------+----------|" << std::endl;
    for (int i = 0; i < nrNod; i++)
    {
        std::cout << std::setw(4) << std::left << "|" << orase[i].crt << "|";
        std::cout << std::setw(10) << std::left << orase[i].nume << "|";

        for (int j = 0; j < nrNod; j++)
        {
            if (orase[i].pret[j] == 999.99)
                std::cout << std::setw(11) << std::right << "-|";
            else
            {
                std::cout << std::setiosflags(std::ios::fixed | std::ios::showpoint | std::ios::right);
                std::cout << std::setw(10) << std::setprecision(2) << std::right << orase[i].pret[j] << "|";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------------------------------------------------------" << std::endl
              << "ATENTIE! Preturile sunt fictive! Pentru preturile reale accesati pagina oficiala CFR Calatori." << std::endl
              << std::endl;
}

void graf::drumPretMic(int a, int b)
{
    PRIORITY_QUEUE coada;
    double *costCur = new double[nrNod];
    int *deLa = new int[nrNod];
    for (int i = 0; i < nrNod; i++)
    {
        costCur[i] = 999.99;
        deLa[i] = 0;
    }

    std::pair<double, int> nc, aux;
    nc.first = 0;
    nc.second = a;
    costCur[a] = nc.first;
    deLa[a] = nc.second;

    coada.INSERT(nc);
    while (coada.GET_SIZE() > 0)
    {
        nc = coada.MIN_ELEMENT();
        coada.EXTRACT_MIN();
        for (int i = 0; i < nrNod; i++)
        {
            if (orase[nc.second].pret[i] != 999.99 && orase[nc.second].pret[i] != 0) //ne uitam doar la vecini lui nc
            {
                if (costCur[i] > costCur[nc.second] + orase[nc.second].pret[i]) //daca costul curent este mai mare decat costul prin nc
                {
                    costCur[i] = costCur[nc.second] + orase[nc.second].pret[i]; //schimba cu varianta mai ieftina
                    deLa[i] = nc.second;
                    aux.first = costCur[i]; //si se pune in coada de prioritati
                    aux.second = i;
                    coada.INSERT(aux);
                    //coada.PRINT_QUEUE();
                }
            }
        }
    }

    // for (int i = 0; i < nrNod; i++)
    //     std::cout << costCur[i] << ", ";
    // std::cout << std::endl;
    // for (int i = 0; i < nrNod; i++)
    //     std::cout << deLa[i] << ", ";
    // std::cout << std::endl;

    std::cout << std::endl
              << "Costul minim de calatorie este: " << costCur[b] << "RON" << std::endl;
    std::cout << "Traseul de cost minim este: ";

    std::stack<int> rezultat;
    while (b != a)
    {
        rezultat.push(b);
        b = deLa[b];
    }
    rezultat.push(b);

    while (!rezultat.empty())
    {
        std::cout << orase[rezultat.top()].crt << "." << orase[rezultat.top()].nume << ", ";
        rezultat.pop();
    }
    std::cout << "\b\b " << std::endl;

    delete[] costCur;
    delete[] deLa;
}

void afisareProblema()
{
    std::cout << std::endl
              << "------------------------------------TEMA NR. 4.4------------------------------------" << std::endl
              << "Se considera o harta reprezentata sub forma unui graf neorientat ponderat" << std::endl
              << "G = (N, A) , în care fiecare nod reprezinta un oras, iar muchiile sunt legaturile" << std::endl
              << "(de cale ferata) între orase. Pentru fiecare oras se cunosc: coordonatele spatiale" << std::endl
              << "ale orasului si numele acestuia. Pentru fiecare legatura între orase se cunoaste" << std::endl
              << "pretul biletului de tren. Sa se realizeze un program în care se vor citi de la" << std::endl
              << "tastatura doua orase A si B si se va gasi cel mai ieftin drum de la A la B ." << std::endl
              << "Afisati traseul si costul acestiua. Pentru rezolvare folositi Dijkstra (5p) sau" << std::endl
              << "A* (6p). Utilizati o coada de prioritati." << std::endl
              << std::endl;
}

void citireNumarNatural(int &n)
{
    float a;
    std::cin >> a;
    while (std::cin.fail() || a < 0 || a / int(a) > 1)
    {
        std::cout << "Numarul introdus trebuie sa fie un numar natural!" << std::endl;
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> a;
    }
    n = int(a);
}

int main()
{
    afisareProblema();

    graf harta;
    harta.citireMatriceFisier();
    harta.afisareListaPret();

    int a, b;
    std::cout << "Traseul:" << std::endl
              << "De la (nr.crt.): ";
    citireNumarNatural(a);
    std::cout << "Pana la (nr.crt.): ";
    citireNumarNatural(b);

    harta.drumPretMic(a, b);
    std::cout << std::endl
              << "Calatorie placuta! " << std::endl;
    return 0;
}