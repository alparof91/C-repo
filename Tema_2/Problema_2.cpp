#include "iostream"
#include "fstream"
#include "string.h"

using namespace std;

void afisareProblema()
{
    cout << endl
         << "------------------------------------TEMA NR. 2.2------------------------------------" << endl
         << "Se citeste dintr-un fisier o expresie aritmetic alcatuit din numere întregi fara" << endl
         << "semn, operatorii aritmetici + , − , ∗ , / si paranteze rotunde. Atentie, carac-" << endl
         << "terele din sir NU sunt despartite prin spatii! Sa se construiasca forma poloneza" << endl
         << "postfixata pentru expresia aritmetica dat si sa se evalueze expresia. Utilizati" << endl
         << "stive. (Este de preferat utilizarea unui vector pentru stocarea elementelor" << endl
         << "stivei. Se cere utilizarea unei structuri STIVA!) (4p)" << endl
         << "Punctajul maxim se acorda daca: se pot utiliza si numere cu mai mult de o" << endl
         << "cifra, sunt semnalate erorile din expresie si nu se blocheaza programul, daca" << endl
         << "expresia nu este corecta." << endl
         << endl
         << "Greseli de introducere tratate:" << endl
         << "Cod0:  Caractere valide: '0-9' sau '+', '-', '*', '/', '(', ')'" << endl
         << "Cod1:  Dupa '(' nu poate sa urmeze altceva decat '0-9' sau '('" << endl
         << "Cod2:  Inainte de '(' nu poate sa afle doar: '+', '-', '*', '/' sau '('" << endl
         << "Cod3:  Inainte de ')' nu poate sa afle altceva decat '0-9' sau ')'" << endl
         << "Cod4:  Dupa ')' nu poate sa urmeze altceva decat '+', '-', '*', '/' sau ')'" << endl
         << "Cod5:  Dupa '+', '-', '*', '/' nu poate sa urmeze altceva decat '0-9' sau '('" << endl
         << "Cod6:  Primul caracter trebuie sa fie '0-9' sau '('" << endl
         << "Cod7:  Ultimul caracter trebuie sa fie '0-9' sau ')'" << endl
         << "Cod8:  Impartire cu '0'" << endl
         << "Cod9:  Parantezare neechilibrata" << endl
         << endl;
}

void citireFisier(char expr[])
{
    int i = 0;
    string nfis;
    cout << endl
         << "Dati numele fisierului text: ";
    cin >> nfis;

    ifstream fis(nfis);
    if (!fis.is_open())
    {
        cerr << "Eroare! Nu am putut deschide '" << nfis << "' pt citire" << endl;
        expr[0] = 'x';
    }
    else
    {
        fis.getline(expr, 50);
        fis.close();

        cout << endl
             << "Am citit: ";
        while (expr[i] != 0)
        {
            cout << expr[i];
            i++;
        }
        cout << endl;
    }
}

void citireManuala(char expr[])
{
    int i = 0;
    expr[0] = 0;
    cin >> expr;

    cout << endl
         << "Am citit: ";
    while (expr[i] != 0)
    {
        cout << expr[i];
        i++;
    }
    cout << endl;
}

int prec(int op)
{
    if (op == 43 || op == 45)
        return 1;
    if (op == 42 || op == 47)
        return 2;
    else
        return 0;
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

    void PUSH(int k)
    {
        NOD *x = new NOD;
        x->info = k;
        x->next = varf;
        varf = x;
    }

    void POP()
    {
        NOD *x = varf;
        varf = x->next;
        delete x;
    }

    void CLEAR()
    {
        while (varf != nullptr)
            POP();
    }

    int TOP()
    {
        return varf->info;
    }

    bool ISEMPTY()
    {
        return varf == nullptr;
    }
};

void esteCorect(char expr[])
{
    STIVA s;
    int i = 0;
    while (expr[i] != 0)
    {

        if (int(expr[i]) < 40 || int(expr[i]) > 57 || int(expr[i]) == 44 || int(expr[i]) == 46)
        {
            cout << expr[i] << "- (Cod 0) Carcater invalid. Caractere valide: '0-9' sau '+', '-', '*', '/', '(', ')'" << endl
                 << "Inlocuim '" << expr[i] << "' cu: ";
            cin >> expr[i];
            i = 0;
        }

        if ((expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == ')') && (expr[i - 1] == '('))
        {
            cout << expr[i - 1] << expr[i] << " - (Cod 1) Expresie invalida! Dupa '(' nu poate sa urmeze altceva decat '0-9' sau '('! Reintroduceti:";
            citireManuala(expr);
            i = 0;
        }

        if (!(expr[i - 1] == 0 || expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/' || expr[i - 1] == '(') && (expr[i] == '('))
        {
            cout << expr[i - 1] << expr[i] << " - (Cod 2) Expresie invalida! Inainte de '(' nu poate sa afle doar: '+', '-', '*', '/' sau '('! Reintroduceti:" << endl;
            citireManuala(expr);
            i = 0;
        }

        if ((expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/' || expr[i - 1] == '(') && (expr[i] == ')'))
        {
            cout << expr[i - 1] << expr[i] << " - (Cod 3) Expresie invalida! Inainte de ')' nu poate sa afle altceva decat '0-9' sau ')'! Reintroduceti:" << endl;
            citireManuala(expr);
            i = 0;
        }

        if (!(expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == ')') && (expr[i - 1] == ')'))
        {
            cout << expr[i - 1] << expr[i] << " - (Cod 4) Expresie invalida! Dupa ')' nu poate sa urmeze altceva decat '+', '-', '*', '/' sau ')'! Reintroduceti:" << endl;
            citireManuala(expr);
            i = 0;
        }

        if ((expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/') && (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'))
        {
            cout << expr[i - 1] << expr[i] << " - (Cod 5) Expresie invalida! Dupa '+', '-', '*', '/' nu poate sa urmeze altceva decat '0-9' sau '('! Reintroduceti:" << endl;
            citireManuala(expr);
            i = 0;
        }

        if (!((int(expr[0]) >= 48 && int(expr[0]) <= 57) || expr[0] == '('))
        {
            cout << expr[i - 1] << expr[i] << " - (Cod 6) Expresie invalida! Primul caracter trebuie sa fie '0-9' sau '('! Reintroduceti:" << endl;
            citireManuala(expr);
            i = 0;
        }

        if ((expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '(') && (expr[i + 1] == 0))
        {
            cout << expr[i - 1] << expr[i] << " - (Cod 7) Expresie invalida! Ultimul caracter trebuie sa fie '0-9' sau ')'! Reintroduceti:" << endl;
            citireManuala(expr);
            i = 0;
        }

        if (expr[i - 1] == '/' && expr[i] == '0')
        {
            cout << expr[i - 1] << expr[i] << " - (Cod 8) Impartire cu 0! Reintroduceti:" << endl;
            citireManuala(expr);
            i = 0;
        }

        if (expr[i] == '(')
            s.PUSH(i);
        if (expr[i] == ')')
            s.POP();

        i++;

        if (expr[i] == 0 && !s.ISEMPTY())
        {
            s.CLEAR();
            cout << "(Cod 9) Parantezare neechilibrata! Reintroduceti expresia:" << endl;
            citireManuala(expr);
            i = 0;
        }
    }
}

void infixPostfix(char inf[], string &postf)
{
    int E, i = 0;
    STIVA s;
    while (inf[i] != 0)
    {
        E = int(inf[i]);
        if (E >= 48 && E <= 57)
        {
            postf += inf[i];
            if (int(inf[i + 1]) < 48 || int(inf[i + 1]) > 57)
                postf += " ";
        }
        else
        {
            if (E == 40)
                s.PUSH(E);
            else
            {
                if (E == 41)
                {
                    while (!s.ISEMPTY() && s.TOP() != 40)
                    {
                        postf += char(s.TOP());
                        postf += " ";
                        s.POP();
                    }
                    s.POP();
                }
                else
                {
                    while (!s.ISEMPTY() && (prec(E) <= prec(s.TOP())))
                    {
                        postf += char(s.TOP());
                        postf += " ";
                        s.POP();
                    }
                    s.PUSH(E);
                }
            }
        }
        i++;
    }
    while (!s.ISEMPTY())
    {
        postf += char(s.TOP());
        postf += " ";
        s.POP();
    }
    cout << "Expresia citita in forma postfix: " << postf << endl;
}

float rezultatPostfix(string postf)
{
    STIVA nr;
    int val;
    for (int i = 0; i < postf[i]; i++)
    {
        if (postf[i] == ' ')
            continue;
        else
        {
            if (int(postf[i]) >= 48 && int(postf[i]) <= 57)
            {
                val = 0;
                while (int(postf[i]) >= 48 && int(postf[i]) <= 57)
                {
                    val = (val * 10) + (int(postf[i]) - 48);
                    i++;
                }
                nr.PUSH(val);
            }
            else
            {
                int val1 = nr.TOP();
                nr.POP();
                int val2 = nr.TOP();
                nr.POP();
                switch (postf[i])
                {
                case '+':
                    nr.PUSH(val2 + val1);
                    break;
                case '-':
                    nr.PUSH(val2 - val1);
                    break;
                case '*':
                    nr.PUSH(val2 * val1);
                    break;
                case '/':
                    nr.PUSH(val2 / val1);
                    break;
                }
            }
        }
    }
    return nr.TOP();
}

int main()
{
    afisareProblema();

    char expr[50], s;
    string P;
    float rez;

    citireFisier(expr);
    while (expr[0] == 'x')
    {
        cout << endl
             << "Ce faceti? " << endl
             << "'r' - reincercare citire fisier " << endl
             << "'m' - introducere manuala a expresiei" << endl
             << "'e' - iesire" << endl;

        cin >> s;
        switch (s)
        {
        case 'r':
        {
            citireFisier(expr);
        }
        break;
        case 'm':
            cout << endl
                 << "Expresie: ";
            citireManuala(expr);
            break;

        case 'e':
            exit(1);
            break;

        default:
            cout << "Optiune invalida" << endl;
        }
    }
    esteCorect(expr);
    infixPostfix(expr, P);
    rez = rezultatPostfix(P);
    cout << "Rezultat: " << expr << "=" << rez << endl
         << endl
         << "La revedere!" << endl;
    return 0;
}
