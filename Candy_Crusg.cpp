#include <iostream>
#include <vector>
using namespace std;
typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
struct maPosition { 
unsigned abs;
unsigned ord;
}; // une position dans la girlle
void initGrid (mat & grid, const size_t & size)
{
    grid.resize(size);
    for(size_t i = 0; i < size; ++i)
    {
        grid[i].resize(size, 0);
    }
}
void  displayGrid (const mat & grid)
{
    for(int i = 0;i<3;++i)
    {
        for(int j = 0;j<3;++i)
        {
            cout<< mat[i+j];
        }
    cout << "|"<<endl;
    }
}

void makeAMove(mat & grid, const maPosition & pos, const char & direction)
{
    maPosition newPos = pos;
    
    // Déterminer la nouvelle position
    if (direction == 'z') {
        newPos.ord = pos.ord - 1;  // Haut
    }
    else if (direction == 's') {
        newPos.ord = pos.ord + 1;  // Bas
    }
    else if (direction == 'q') {
        newPos.abs = pos.abs - 1;  // Gauche
    }
    else if (direction == 'd') {
        newPos.abs = pos.abs + 1;  // Droite
    }
    
    // Permuter les valeurs entre pos et newPos
    unsigned temp = grid[pos.ord][pos.abs];
    grid[pos.ord][pos.abs] = grid[newPos.ord][newPos.abs];
    grid[newPos.ord][newPos.abs] = temp;
}

void clearScreen () 
{   
    cout << "\033[H\033[2J";
}
const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);
     
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

int main ()
{
    couleur (KRouge);
    cout << "Rouge" << endl;
    couleur (KVert);
    cout << "Vert" << endl;
    couleur (KReset);
    cout << "Retour à la normale" << endl;
}
