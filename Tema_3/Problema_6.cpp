#include "iostream"
#include "queue"
#include "string"
#include "fstream"
//#include "conio.h"

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

struct nod
{
    int info;
    nod *st, *dr, *p;
    nod(int k = 0)
    {
        info = k;
        st = dr = p = nullptr;
    }
};

struct ARBORE
{
    nod *rad;
    vector<pair<nod *, int>> frunze;

    ARBORE()
    {
        rad = nullptr;
    }

    void citireFisier(std::string filename)
    {
        std::ifstream f;
        f.open(filename);

        int info;
        int copii;
        nod *nod_curent;

        queue<pair<nod *, int>> C;
        pair<nod *, int> curent; //nodul curent cu nr de copii
        pair<nod *, int> frunza; //frunza curenta cu adincime

        f >> info;
        f >> copii;
        rad = new nod(info);

        C.push(pair<nod *, int>(rad, copii)); //pun in coada nodul curent cu informatia si cu nr de copii pe care ii are (2, -1 pt copil st, 1, pt copil drept, 0)
        while (!C.empty())
        {
            nod *stanga = nullptr, *dreapta = nullptr;
            curent = C.front(); //nodul curent impreuna cu numarul de copii. Pentru acest nod se citesc din fisier copiii si se realizeaza legaturile
            C.pop();

            nod_curent = curent.first;

            //acum citesc copiii nodulul curent

            if (curent.second == -1 || curent.second == 2) //am copil stang sau am 2 copii - citesc copilul stang, impreuna cu numarul
                                                           // de copii pe care ii are, si il leg de parinte. Apoi il pun in coada
            {
                f >> info;
                f >> copii;

                stanga = new nod(info);
                stanga->p = nod_curent;

                C.push(std::pair<nod *, int>(stanga, copii));
            }

            if (curent.second == 1 || curent.second == 2) //am copil drept sau am 2 copii - citesc copilul stang , impreuna cu numarul
                                                          // de copii pe care ii are,si il leg de parinte. Apoi il pun in coada
            {
                f >> info;
                f >> copii;

                dreapta = new nod(info);
                dreapta->p = nod_curent;
                C.push(std::pair<nod *, int>(dreapta, copii));
            }

            nod_curent->st = stanga;
            nod_curent->dr = dreapta;

            if (curent.second == 0)
            {
                frunza.first = curent.first;
                frunza.second = 0;
                nod_curent = curent.first;
                while (nod_curent != rad)
                {
                    nod_curent = nod_curent->p;
                    frunza.second++;
                }
                frunze.push_back(frunza);
            }
        }

        f.close();
    }

    void frunzeAdancime(vector<pair<nod *, int>> fru)
    {
        cout << "Frunza (adancime): ";
        int h = 0;
        for (auto i = fru.begin(); i != fru.end(); ++i)
        {
            cout << i->first->info << "(" << i->second << "), ";
            if (h < i->second)
                h = i->second;
        }
        cout << endl
             << "Inaltimea arborelui este: " << h << endl;
    }

    void RSD(nod *x)
    {
        if (x)
        {
            cout << x->info << " ";
            RSD(x->st);
            RSD(x->dr);
        }
    }
};

int main()
{
    afisareProblema();

    ARBORE arb;
    string nfis;

    cout << endl
         << "Citire din fiser: ";
    cin >> nfis;
    arb.citireFisier(nfis);
    //arb.citireFisier("Problema_6.txt");
    cout << "Parcurgerea in preordine(RSD):";
    arb.RSD(arb.rad);
    cout << endl;

    arb.frunzeAdancime(arb.frunze);

    //_getch();
    return 0;
}