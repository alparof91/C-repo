#include "iostream"
#include "fstream"
#include "iomanip"

struct coord
{
    int x, y;
    coord()
    {
        x = y = 0;
    }
    coord(int a, int b)
    {
        x = a;
        y = b;
    }
};

class PRIORITY_QUEUE
{
private:
    int SIZE, CAP;
    std::pair<int, coord> *DATA;

public:
    PRIORITY_QUEUE(int capacitate = 100)
    {
        CAP = capacitate;
        DATA = new std::pair<int, coord>[CAP];
        SIZE = 0;
    }

    int GET_SIZE();
    std::pair<int, coord> MIN_ELEMENT();
    void MIN_HEAPFY();
    void INCREASE_KEY(int, std::pair<int, coord>);
    void INSERT(std::pair<int, coord>);
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

std::pair<int, coord> PRIORITY_QUEUE::MIN_ELEMENT()
{
    return DATA[0];
}

void PRIORITY_QUEUE::MIN_HEAPFY() // SIFT_DOWN (iterativ)
{
    int imin, p, st, dr;
    std::pair<int, coord> aux;
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

void PRIORITY_QUEUE::INCREASE_KEY(int k, std::pair<int, coord> val)
{
    DATA[k] = val;
    int p = (k - 1) / 2;
    std::pair<int, coord> aux;
    while (k > 0 && DATA[p].first > val.first)
    {
        aux = DATA[k];
        DATA[k] = DATA[p];
        DATA[p] = aux;
        p = (k - 1) / 2;
    }
}

void PRIORITY_QUEUE::INSERT(std::pair<int, coord> a)
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
        DATA[SIZE - 1].second.x = 0;
        DATA[SIZE - 1].second.y = 0;
        SIZE--;
        MIN_HEAPFY();
    }
}

void PRIORITY_QUEUE::PRINT_QUEUE()
{
    for (int i = 0; i < SIZE; i++)
        std::cout << "(" << DATA[i].second.x << "," << DATA[i].second.y << "), ";
    std::cout << std::endl;
}

class graf
{
private:
    int dimX, dimY;
    coord branza, soricel;
    int **labirint;
    PRIORITY_QUEUE coada;

public:
    graf()
    {
        branza.x = branza.y = 0;
        soricel.x = soricel.y = 0;
        dimX = dimY = 0;
        labirint = nullptr;
    }
    void citireNumarNatural(int &n);
    void citireMatriceFisier(std::string);
    void pozitionareBranzaSoarece();
    void afisareLabirint();
    bool insertVecini(int, int, int, int);
    void drumScurt();

    ~graf()
    {
        for (int i = 0; i < dimX; i++)
            delete[] labirint[i];
        delete[] labirint;
    }
};

// LEGENDA:
//  0 = liber
// -1 = perete
// -2 = soarece
// -3 = branza
// -4 = am venit aici din stanga
// -5 = am venit aici din dreapta
// -6 = am venit aici din sus
// -7 = am venit aici din jos
// -8 = traseul optim

void graf::citireNumarNatural(int &n)
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
    std::cin.clear();
    std::cin.ignore(256, '\n');
}

void graf::citireMatriceFisier(std::string nfis = "Problema_5.txt")
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
        fisier >> dimX;
        fisier >> dimY;
        labirint = new int *[dimX];
        for (int i = 0; i < dimX; i++)
        {
            labirint[i] = new int[dimY];
            for (int j = 0; j < dimY; j++)
                fisier >> labirint[i][j];
        }
    }
}

void graf::pozitionareBranzaSoarece()
{
    bool valid = false;
    while (valid == false)
    {
        std::cout << std::endl
                  << "Soricelul se afla la: " << std::endl
                  << "linia: ";
        citireNumarNatural(soricel.x);
        std::cout << "coloana: ";
        citireNumarNatural(soricel.y);

        std::cout << std::endl
                  << "Branza se afla la: " << std::endl
                  << "linia: ";
        citireNumarNatural(branza.x);
        std::cout << "coloana: ";
        citireNumarNatural(branza.y);

        if (soricel.x > dimX - 1 || soricel.y > dimY - 1 || branza.x > dimX - 1 || branza.y > dimY - 1)
            std::cout << "Pozitie in afara labirintului! Reintroduceti!" << std::endl;

        else if (labirint[soricel.x][soricel.y] != 0 || labirint[branza.x][branza.y] != 0)
            std::cout << "Pozitionare gresita! Ati nimerit zidul labirintului! Reintroduceti!" << std::endl;

        else
        {
            labirint[soricel.x][soricel.y] = -2;
            labirint[branza.x][branza.y] = -3;
            for (int i = 0; i < dimX; i++)
            {
                for (int j = 0; j < dimY; j++)
                {
                    if (labirint[i][j] == 0)
                        labirint[i][j] = abs(i - branza.x) + abs(j - branza.y);
                }
            }
            valid = true;
        }
    }
}

void graf::afisareLabirint()
{
    std::cout << std::endl
              << " ";
    for (int i = 0; i < dimX; i++)
        std::cout << std::setw(3) << i;
    std::cout << std::endl;
    for (int i = 0; i < dimX; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < dimY; j++)
        {
            if (labirint[i][j] == -1)
                std::cout << "[X]";
            else if (labirint[i][j] == -2)
                std::cout << " S ";
            else if (labirint[i][j] == -3)
                std::cout << " o ";
            else if (labirint[i][j] == -8)
                std::cout << " * ";
            else
            {
                // std::cout << "   "; //  !!!!!!!!!!!
                std::cout << std::setw(3) << labirint[i][j]; // pt. a vedea distantele City-block};      !!!!!!!!!!
            }
        }
        std::cout << std::endl;
    }
}

// functie care trimite vecinile valabile in PQ si pune directia din care s-a ajuns la vecin si
// returneaza fals cand vecinul e branza
// am pus separat functia asta ca sa nu am 4 if-uri in functia graf::drumScurt

bool graf::insertVecini(int vx, int vy, int cost, int dir)
{
    std::pair<int, coord> vecin;
    if (labirint[vx][vy] == -3)
        return false;
    else if (labirint[vx][vy] > 0)
    {
        vecin.first = labirint[vx][vy] + cost;
        vecin.second.x = vx;
        vecin.second.y = vy;
        coada.INSERT(vecin);
        labirint[vx][vy] = dir;
    }
    return true;
}

void graf::drumScurt()
{
    int costCur = 0;
    std::pair<int, coord> nc;
    nc.first = labirint[soricel.x][soricel.y] + costCur;
    nc.second.x = soricel.x;
    nc.second.y = soricel.y;
    coada.INSERT(nc);

    while (coada.GET_SIZE() > 0)
    {
        std::cout << std::endl         // !!!!!!!!!!!!!!
                  << "PQ: ";           // !!!!!!!!!!!!!!
        coada.PRINT_QUEUE();           // !!!!!!!!!!!!!!

        costCur++;
        nc = coada.MIN_ELEMENT();
        coada.EXTRACT_MIN();

        std::cout << "Curent: " << nc.first << "|" << nc.second.x << "," << nc.second.y << std::endl;  // !!!!!!!!!!!!

        if (!insertVecini(nc.second.x, nc.second.y + 1, costCur, -4) ||
            !insertVecini(nc.second.x, nc.second.y - 1, costCur, -5) ||
            !insertVecini(nc.second.x + 1, nc.second.y, costCur, -6) ||
            !insertVecini(nc.second.x - 1, nc.second.y, costCur, -7))
            break;

        std::cout << std::endl;          // !!!!!!!!!!!!!!!!!
        afisareLabirint();               // !!!!!!!!!!!!!!!!!
    }

    while (labirint[nc.second.x][nc.second.y] != -2)
    {
        switch (labirint[nc.second.x][nc.second.y])
        {
        case -4:
            labirint[nc.second.x][nc.second.y] = -8;
            nc.second.y = nc.second.y - 1;
            break;

        case -5:
            labirint[nc.second.x][nc.second.y] = -8;
            nc.second.y = nc.second.y + 1;
            break;

        case -6:
            labirint[nc.second.x][nc.second.y] = -8;
            nc.second.x = nc.second.x - 1;
            break;

        case -7:
            labirint[nc.second.x][nc.second.y] = -8;
            nc.second.x = nc.second.x + 1;
            break;

        default:
            break;
        }
    }
}

void afisareProblema()
{
    std::cout << std::endl
              << "------------------------------------TEMA NR. 4.5------------------------------------" << std::endl
              << "Se considera un labirint reprezentat printr-o matrice în care zidurile sunt mar-" << std::endl
              << "cate prin −1 si drumurile prin 0. În labirint se afla un soricel pe pozitia (x0 , y0)" << std::endl
              << "si o bucata de brânza pe pozitia (x1 , y1). Sa se gaseasca un drum (de preferinta" << std::endl
              << "de lungime minima) de la soricel la brânza. Nu utilizati recursivitate! Utilizati A* (5p)." << std::endl
              << "Utilizati ca si functie de cost city-block (Manhattan) distance, adica |x1 − x2| + |y1 − y2|." << std::endl
              << std::endl;
}

int main()
{

    afisareProblema();
    graf harta;
    harta.citireMatriceFisier();
    std::cout << "Labirintul citit din fisier: " << std::endl;
    harta.afisareLabirint();
    harta.pozitionareBranzaSoarece();
    harta.afisareLabirint();     //  !!!!!!!!!!!!
    harta.drumScurt();
    harta.afisareLabirint();
    std::cout << std::endl
              << "Pentru o prezenatre mai buna a modului de gandire: decomentati " << std::endl
              << "liniile de cod marcate cu semnul exclamarii si rulati din nou programul" << std::endl
              << "La revedere! " << std::endl;
    return 0;
}