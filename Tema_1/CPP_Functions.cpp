-----------------------------------------------------------------------------------------------------------
//citeste un vector de lungimea l
void citireVector(float *a, int l)
{
    cout << "Introduceti elementele de numere reale a vectorului" << endl;
    for (int i = 0; i < l; i++)
    {
        cout << "a[" << i << "]=";
        cin >> a[i];
    }
    cout << endl;
}
-----------------------------------------------------------------------------------------------------------
//afiseaza un vector de lungimea l
void afisareVector(float *a, int l)
{
    cout << "Vectorul citit: v={";
    for (int i = 0; i < l; i++)
    {
        cout << a[i] << ",";
    }
    cout << "\b"
         << "}"
         << endl;
}
-----------------------------------------------------------------------------------------------------------
//afiseaza triplete crescatoare dintr-un vector
void afisareTriplete(float *a, int l)
{
    cout << "Tripletele sunt: " << endl;
    for (int i = 0; i < l; i++)
    {
        if (a[i] < a[i + 1] && a[i + 1] < a[i + 2])
        {
            cout << a[i] << "," << a[i + 1] << "," << a[i + 2] << endl;
        }
    }
}
-----------------------------------------------------------------------------------------------------------
//verifica daca un vector "v" de lungime "l" este sortat descrescator
void testSortatDescr(int *v, int l, bool *test)
{
    *test = 1;
    for (int i = 0; i < l; i++)
    {
        if (v[i] < v[i + 1])
            *test = 0;
    }
}
-----------------------------------------------------------------------------------------------------------
//verifica daca un numar introdus este natural
void testNatural(double n, bool *test)
{
    *test = 1;
    long long int m = n;
    if (n < 0 || n / m > 1)
    {
        cout << "Numarul introdus trebuie sa fie NATURAL!" << endl
             << "a=";
        *test = 0;
    }
}
-----------------------------------------------------------------------------------------------------------
//returneaza lungimea unui numar intreg
void lungimeNumar(long long int nr, int *l)
{
    while (nr >= 1)
    {
        nr /= 10;
        *l += 1;
    }
}
-----------------------------------------------------------------------------------------------------------
//transforma un numar intreg intr-un vector de caractere numerice
void numarInVector(long long int nr, int l, int *v)
{
    for (int i = l - 1; i >= 0; i--) // transformare numar in vector de caractere
    {
        v[i] = nr % 10;
        nr /= 10;
    }
}
-----------------------------------------------------------------------------------------------------------
//aviseaza un vector de lungime "l"
void afisareVector(int *v, int l)
{
    for (int i = 0; i < l; i++)
    {
        cout << v[i];
    }
}
