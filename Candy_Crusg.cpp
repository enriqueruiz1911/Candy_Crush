#include <iostream>
#include <vector>
#include <random>
int nbBonBons(0);
int sizemat(0);
const unsigned KReset(0);
const unsigned KNoir(30);
const unsigned KRouge(31);
const unsigned KVert(32);
const unsigned KJaune(33);
const unsigned KBleu(34);
const unsigned KMAgenta(35);
const unsigned KCyan(36);
using namespace std;
int Score(0);
typedef vector<unsigned> line; // un type représentant une ligne de la grille
typedef vector<line> mat;      // un type représentant la grille
struct maPosition
{
    unsigned abs;
    unsigned ord;
}; // une position dans la girlle
void couleur(const unsigned &coul)
{
    cout << "\033[" << coul << "m";
}
void initGrid(mat &grid, const size_t &sizemat)
{
    srand(time(0));
    if (sizemat > 10)
    {
        cerr << "Taille de la matrice invalide" << endl;
        exit(1);
    }
    grid.resize(sizemat);
    for (int i = 0; i < sizemat; ++i)
    {
        for (int j = 0; j < sizemat; j++)
        {
            grid[i].push_back(rand() % (nbBonBons + 1));
        }
    }
}
void displayGrid(const mat &grid)
{
    for (int i = 0; i < sizemat; ++i)
    {
        cout << "|";
        for (int j = 0; j < sizemat; ++j)
        {
            unsigned valeur = grid[i][j];
            switch (valeur)
            {
            case 0:
                couleur(KRouge);
                break;
            case 1:
                couleur(KVert);
                break;
            case 2:
                couleur(KJaune);
                break;
            case 3:
                couleur(KBleu);
                break;
            case 4:
                couleur(KMAgenta);
                break;
            case 5:
                couleur(KCyan);
                break;
            case 6:
                couleur(KNoir);
                break;
            }
            cout << valeur;
            couleur(KReset);
        }
        cout << "|" << endl;
    }
}
void clearScreen()
{
    cout << "\033[H\033[2J";
}
bool atLeastThreeInAColumn(const mat &grid, maPosition &pos, unsigned &howMany)
{
    unsigned count(1);
    unsigned valeur = grid[pos.ord][pos.abs];
    for (unsigned i = pos.ord + 1; i < sizemat; ++i)
    {
        if (grid[i][pos.abs] == valeur)
        {
            ++count;
        }
        else
        {
            break;
        }
    }
    if (count >= 3)
    {
        howMany = count;
        return true;
        Score += howMany * valeur;
    }
    else
    {
        howMany = 0;
        return false;
    }
}
bool atLeastThreeInARow(const mat &grid, maPosition &pos, unsigned &howMany)
{
    unsigned count(1);
    unsigned valeur = grid[pos.ord][pos.abs];
    for (unsigned j = pos.abs + 1; j < sizemat; ++j)
    {
        if (grid[pos.ord][j] == valeur)
        {
            ++count;
        }
        else
        {
            break;
        }
    }
    if (count >= 3)
    {
        howMany = count;
        return true;
        Score += howMany * valeur;
    }
    else
    {
        howMany = 0;
        return false;
    }
}
int main()
{
    cout << "Saisir un nombre de bonbons inferieur a 10" << endl;
    cin >> nbBonBons;
    cout << "Taille de la Matrice" << endl;
    cin >> sizemat;
    mat matrice;
    initGrid(matrice, sizemat);
    displayGrid(matrice);
}
