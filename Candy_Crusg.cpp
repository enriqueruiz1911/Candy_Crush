#include <iostream>
#include <vector>
#include <random>
int nbBonBons(0);
int sizemat(0);
using namespace std;
typedef vector<unsigned> line; // un type représentant une ligne de la grille
typedef vector<line> mat;      // un type représentant la grille
struct maPosition
{
    unsigned abs;
    unsigned ord;
}; // une position dans la girlle
void initGrid(mat &grid, const size_t &sizemat)
{
    srand(time(0));
    grid.resize(sizemat);
    for (int i = 0; i < sizemat; ++i)
    {
        for (int j = 0; j < sizemat; j++)
        {
            grid[i].push_back(rand() % nbBonBons);
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
            cout << grid[i][j];
        }
        cout << "|" << endl;
    }
}
void clearScreen()
{
    cout << "\033[H\033[2J";
}
const unsigned KReset(0);
const unsigned KNoir(30);
const unsigned KRouge(31);
const unsigned KVert(32);
const unsigned KJaune(33);
const unsigned KBleu(34);
const unsigned KMAgenta(35);
const unsigned KCyan(36);

void couleur(const unsigned &coul)
{
    cout << "\033[" << coul << "m";
}

int main()
{
    cout << "Nombre de Bonbons" << endl;
    cin >> nbBonBons;
    cout << "Taille de la Matrice" << endl;
    cin >> sizemat;
    mat matrice;
    couleur(KRouge);
    initGrid(matrice, sizemat);
    displayGrid(matrice);
}
