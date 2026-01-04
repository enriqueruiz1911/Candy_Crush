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
unsigned howMany(0);
int Compteur(5);
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
    if (nbBonBons >= 10 || nbBonBons <= 0)
    {
        cerr << "Nombre de bonbons invalide" << endl;
        exit(1);
    }
    grid.resize(sizemat);
    for (int i = 0; i < sizemat; ++i)
    {
        for (int j = 0; j < sizemat; j++)
        {
            grid[i].push_back((rand() % nbBonBons) + 1);
        }
    }
}
void initMove(maPosition &pos)
{
    cout << "Entrez une ordonnée (Ligne) : ";
    cin >> pos.ord;
    cout << "Entrez une abscisse (Colonne) : ";
    cin >> pos.abs;
    if (pos.ord >= sizemat || pos.abs >= sizemat)
    {
        cout << "/!\\ Position hors de la grille ! On remet a 0." << endl;
        pos.ord = 0;
        pos.abs = 0;
    }
}
void MakeAMove(mat &grid, maPosition &pos)
{
    char direction;
    cout << "Entrez la direction du déplacement (Z/Q/S/D) : ";
    cin >> direction;

    // Convertir en majuscule si nécessaire
    direction = toupper(direction);

    maPosition newPos = pos; // Position cible

    if (direction == 'z' && pos.ord > 0) // Haut
    {
        newPos.ord -= 1;
    }
    else if (direction == 's' && pos.ord < sizemat - 1) // Bas
    {
        newPos.ord += 1;
    }
    else if (direction == 'q' && pos.abs > 0) // Gauche
    {
        newPos.abs -= 1;
    }
    else if (direction == 'd' && pos.abs < sizemat - 1) // Droite
    {
        newPos.abs += 1;
    }
    else
    {
        cout << "Déplacement invalide!" << endl;
        return;
    }

    // Échanger les bonbons
    swap(grid[pos.ord][pos.abs], grid[newPos.ord][newPos.abs]);

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
            cout << "|";
        }
        cout << endl;
    }
}
void clearScreen()
{
    cout << "\033[H\033[2J";
}
bool atLeastThreeInAColumn(mat &grid, maPosition &pos, unsigned &howMany)
{
    // Sécurité anti-crash et logique
    if (pos.ord >= sizemat || pos.abs >= sizemat)
        return false;
    unsigned count(1);
    unsigned valeur = grid[pos.ord][pos.abs];
    if (valeur == 0)
    {
        return false;
    }
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
        Score += howMany * valeur;
        return true;
    }
    else
    {
        howMany = 0;
        return false;
    }
}
bool atLeastThreeInARow(mat &grid, maPosition &pos, unsigned &howMany)
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
        Score += howMany * valeur;
        return true;
    }
    else
    {
        howMany = 0;
        return false;
    }
}
void Remove(mat &matrice)
{
    unsigned howMany;
    maPosition pos;

    for (int i = 0; i < sizemat; ++i)
    {
        for (int j = 0; j < sizemat; ++j)
        {
            pos.ord = i;
            pos.abs = j;

            if (atLeastThreeInAColumn(matrice, pos, howMany))
            {
                for (int k = 0; k < howMany; ++k)
                {
                    matrice[i + k][j] = 0;
                }
            }

            if (atLeastThreeInARow(matrice, pos, howMany))
            {
                for (int k = 0; k < howMany; ++k)
                {
                    matrice[i][j + k] = 0;
                }
            }
        }
    }
}
void gravite(mat &grid)
{
    for (int j = 0; j < sizemat; ++j)
    {
        int indexEcriture = sizemat - 1;
        for (int i = sizemat - 1; i >= 0; --i)
        {
            if (grid[i][j] != 0)
            {
                grid[indexEcriture][j] = grid[i][j];
                if (indexEcriture != i)
                {
                    grid[i][j] = 0;
                }
                --indexEcriture;
            }
        }
    }
}
void NouvBonbons(mat &grid)
{
    for (int i = 0; i < sizemat; ++i)
    {
        for (int j = 0; j < sizemat; ++j)
            if (grid[i][j] == 0)
            {
                grid[i][j] = ((rand() % nbBonBons) + 1);
            }
    }
}
int Menu()
{
    int choix;
    cout << "===========================" << endl;
    cout << "   CANDY CRUSH TERMINAL    " << endl;
    cout << "===========================" << endl;
    cout << "1. Mode Infini" << endl;
    cout << "2. Mode Objectif (1000 pts)" << endl;
    cout << "3. Mode Limite (20 coups)" << endl;
    cout << "4. Mode Histoire";
    cout << "===========================" << endl;
    cout << "Votre choix : " << endl;
    cin >> choix;
    return choix;
}
int main()
{
    int mode = Menu();

    if (mode == 1) // Mode Infini
    {
        cout << "Taille matrice : " << endl;
        cin >> sizemat;
        cout << "Nb Bonbons : " << endl;
        cin >> nbBonBons;

        mat matrice;
        initGrid(matrice, sizemat);
        maPosition pos = {0, 0}; // Initialisation importante !

        while (true)
        {
            clearScreen();
            cout << "Score : " << Score << endl;
            displayGrid(matrice);
            while (atLeastThreeInAColumn = true || atLeastThreeInARow = true)
            {
                atLeastThreeInAColumn(matrice, pos);
                atLeastThreeInARow(matrice, pos);
                Remove(matrice);
            }
            // 1. Le joueur joue
            initMove(pos);           // Choisir la case
            MakeAMove(matrice, pos); // Choisir la direction et échanger

            // 2. On calcule les conséquences (Réaction en chaine)
            // On le fait plusieurs fois tant qu'il y a des changements (optionnel mais mieux)
            Remove(matrice);      // Supprime les alignements
            gravite(matrice);     // Fait tomber
            NouvBonbons(matrice); // Remplit
        }
    }
    // ... autres modes ...
    return 0;
}
