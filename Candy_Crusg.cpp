#include <iostream>
#include <vector>
using namespace std;
typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
struct maPosition { 
unsigned abs;
unsigned ord;
}; // une position dans la girlle
void initGrid (mat & grid, const size_t & size){}
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
