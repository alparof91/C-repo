#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <iomanip>

int main(int argc, char **argv)
{
    std::cout << std::endl
              << "----------------------------------------------multicopy_v1--------------------------------------------" << std::endl
              << std::endl
              << "Syntax: multicopy   [source file]   [destination file(s) ...]   ['?'volume size]-optional" << std::endl
              << std::endl
              << "[source file]                     - Name of the input file" << std::endl
              << "[destination file(s) ...]         - Name of the output file(s)" << std::endl
              << "['?' + max size]  (optional)      - Maximum size (integer) of the output file(s)" << std::endl
              << std::endl
              << "------------------------------------------------------------------------------------------------------" << std::endl
              << std::endl;

    if (argc < 3)
    {
        std::cerr << "Eroare! In linie de comanda trebuie specificata fisierul sursa si cel putin un fisier destinatie!\n";
        return 1;
    }

    std::ifstream sourceFile(argv[1], std::ios::binary);
    if (sourceFile.fail())
    {
        std::cerr << "Eroare! Fisierul " << argv[1] << " nu s-a deschis. Reincercati!\n";
        return 1;
    }

    char *i = argv[argc - 1];
    // std::cout << *i;

    int lbuf = 1000000;

    // int sourceSize;
    // sourceFile.seekg(0, sourceFile.end); //pentru tellg
    // sourceSize = sourceFile.tellg();     //lungimea fisierului sursa
    // sourceFile.seekg(0, sourceFile.beg); //repozitionare stream la inceput

    if (*i == '?')
    {
        i++;
        std::string str(argv[argc - 1]);

        if (str.length() > 9)
        {
            std::cerr << "Eroare! Ati introdus o valoare prea mare pentru lungimea unui volum! Reincercati cu o valoare mai mica!" << std::endl;
            return 1;
        }

        for (int j = 1; j < str.length(); j++)
        {
            if (!isdigit(str[j]))
            {
                std::cerr << "Eroare! Dupa '?' se asteapta un numar intreg pozitiv! Vezi Syntax!" << std::endl;
                return 1;
            }
        }

        sscanf(i, "%d", &lbuf);
        argc--;

    }

    int volNr = 0;
    std::string outName;
    std::ostringstream nOut;
    char *buffer = new char[lbuf];
    if (buffer == nullptr)
    {
        std::cerr << "Eroare! Memorie insuficienta!" << std::endl;
        return 1;
    }
    int n = argc - 2;
    std::ofstream *destFile = new std::ofstream[n];

    while (!sourceFile.eof())
    {
        sourceFile.read(buffer, lbuf);
        if (sourceFile.bad())
        {
            sourceFile.close();
            std::cerr << "Eroare! Nu am putut deschide pe '" << argv[1] << "'" << std::endl;
            return 1;
        }

        for (int i = 0; i < n; i++)
        {
            nOut.str("");
            nOut.clear();
            nOut << argv[i + 2] << "_" << std::setw(3) << std::setfill('0') << std::setiosflags(std::ios::fixed | std::ios::right) << volNr;
            outName = nOut.str();

            destFile[i].open(outName, std::ios::binary);
            if (!destFile[i])
            {
                destFile[i].close();
                std::cerr << "Eroare! Nu am putut deschide pe " << argv[i + 2] << std::endl;
                return 1;
            }

            destFile[i].write(buffer, sourceFile.gcount());

            if (!destFile[i])
            {
                std::cerr << "Operatia nu s-a incheiat cu succes!\n";
                return 1;
            }
            destFile[i].close();
        }
        volNr++;
    }

    std::cout << "Lungime buffer: " << lbuf << std::endl
              << std::endl
              << "Operatia s-a incheiat cu succes." << std::endl
              << "Am copiat continutul fisierului sursa '" << argv[1] << "', in " << argc - 2;
    if (volNr != 0)
        std::cout << "x" << volNr;
    std::cout << " fisiere" << std::endl
              << "La revedere!" << std::endl;

    delete[] destFile;
    delete[] buffer;
    sourceFile.close();
    return 0;
}