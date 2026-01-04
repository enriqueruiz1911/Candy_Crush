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
typedef vector<unsigned> line;
typedef vector<line> mat;
struct maPosition
{
    unsigned abs;
    unsigned ord;
};
void couleur(const unsigned &coul)
{
    cout << "\033[" << coul << "m";
}
void initGrid(mat &grid, const size_t &sizemat) // fonction permettant d'assigner un chiffre à chaque case
{
    srand(time(0));
    if (nbBonBons >= 7 || nbBonBons <= 0)
    {
        cerr << "Nombre de bonbons invalide" << endl;
        exit(1);
    }
    grid.resize(sizemat);
    for (int i = 0; i < sizemat; ++i)
    {
        grid[i].clear();
        for (int j = 0; j < sizemat; j++)
        {
            grid[i].push_back((rand() % nbBonBons) + 1);
        }
    }
}
void initMove(maPosition &pos)
{
    do
    {
        cout << "Entrez une ordonnée (Ligne) : ";
        cin >> pos.ord;
        cout << "Entrez une abscisse (Colonne) : ";
        cin >> pos.abs;
        if (pos.ord >= sizemat || pos.abs >= sizemat)
        {
            cout << "Coordonnées invalides ! Elles doivent être entre 0 et " << sizemat - 1 << "." << endl;
        }
    } while (pos.ord >= sizemat || pos.abs >= sizemat);
}
void MakeAMove(mat &grid, maPosition &pos)
{
    char direction;
    cout << "Entrez la direction du déplacement (Z/Q/S/D) : ";
    cin >> direction;
    if ((direction == 'Z' || direction == 'z') && pos.ord > 0) // Haut
    {
        swap(grid[pos.ord][pos.abs], grid[pos.ord - 1][pos.abs]);
        pos.ord -= 1;
    }
    else if ((direction == 'S' || direction == 's') && pos.ord < sizemat - 1) // Bas
    {
        swap(grid[pos.ord][pos.abs], grid[pos.ord + 1][pos.abs]);
        pos.ord += 1;
    }
    else if ((direction == 'Q' || direction == 'q') && pos.abs > 0) // Gauche
    {
        swap(grid[pos.ord][pos.abs], grid[pos.ord][pos.abs - 1]);
        pos.abs -= 1;
    }
    else if ((direction == 'D' || direction == 'd') && pos.abs < sizemat - 1) // Droite
    {
        swap(grid[pos.ord][pos.abs], grid[pos.ord][pos.abs + 1]);
        pos.abs += 1;
    }
    else
    {
        cout << "Déplacement invalide!" << endl;
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
            cout << "|";
        }
        cout << endl;
    }
}
void displayGridH(mat &grid)
{
    for (int i = 0; i < sizemat; ++i)
    {
        couleur(KRouge);
        cout << "|";
        for (int j = 0; j < sizemat; ++j)
        {
            int valeur = grid[i][j];
            cout << valeur;
            cout << "|";
        }
        cout << endl;
        couleur(KReset);
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
    cout << "2. Mode Speedrun" << endl;
    cout << "3. Mode Limite (20 coups)" << endl;
    cout << "4. Mode Histoire" << endl;
    cout << "5. Hardcore" << endl;
    cout << "===========================" << endl;
    cout << "Votre choix : " << endl;
    cin >> choix;
    return choix;
}
void Infini(mat &grid)
{
    maPosition pos = {0, 0};
    cout << "Taille matrice : " << endl;
    cin >> sizemat;
    cout << "Nb Bonbons (inferieur ou égal à 6): " << endl;
    cin >> nbBonBons;
    initGrid(grid, sizemat);
    while (true)
    {
        clearScreen();
        cout << "Score : " << Score << endl;
        displayGrid(grid);
        Remove(grid);
        initMove(pos);        // Choisir la case
        MakeAMove(grid, pos); // Choisir la direction et écents (optionnel mais mieux)
        Remove(grid);         // Supprime les alignements
        gravite(grid);        // Fait tomber
        NouvBonbons(grid);    // Remplit
    }
}
void Speedrun(mat &grid)
{
    sizemat = 6;
    nbBonBons = 5;
    int difficulte;
    maPosition pos{0, 0};
    cout << "Choisissez une difficulté" << endl;
    cout << "-------------------------" << endl;
    cout << "1. Facile 200 pts" << endl;
    cout << "2. Medieum 500 pts" << endl;
    cout << "3. Difficile 1000 pts" << endl;
    cout << "-------------------------" << endl;
    cin >> difficulte;
    int objectif;
    initGrid(grid, sizemat);
    switch (difficulte)
    {
    case 1:
        objectif = 200;
        break;
    case 2:
        objectif = 500;
        break;
    case 3:
        objectif = 1000;
        break;
    default:
        cout << "Mauvais choix";
    }
    int i = 0;
    while (Score < difficulte)
    {
        ++i;
        clearScreen();
        displayGrid(grid);
        cout << "Score :" << Score << endl;
        cout << "Nombre de tour :" << i << endl;
        initMove(pos);
        MakeAMove(grid, pos);
        Remove(grid);
        gravite(grid);
        NouvBonbons(grid);
    }
    cout << "Bravo ! Vous avez gagné !";
}
void Limite(mat grid)
{
    int difficulte;
    int obj;
    cout << "Choississez une difficulté" << endl;
    cout << "--------------------------" << endl;
    cout << "1. Facile (10 coups pour faire 75)" << endl;
    cout << "2. Medieum (10 coups pour faire 100)" << endl;
    cout << "3. Difficile (10 couprs pour faire 120)" << endl;
    cin >> difficulte;
    switch (difficulte)
    {
    case 1:
        obj = 75;
        break;
    case 2:
        obj = 100;
        break;
    case 3:
        obj = 120;
        break;
    }
    maPosition pos{0, 0};
    int compteur = 10;
    sizemat = 6;
    nbBonBons = 5;
    initGrid(grid, sizemat);
    while (compteur > 0)
    {
        clearScreen();
        cout << "Nombre de coups Restants :" << compteur << endl;
        cout << "Score :" << Score << endl;
        displayGrid(grid);
        initMove(pos);
        MakeAMove(grid, pos);
        Remove(grid);
        gravite(grid);
        NouvBonbons(grid);
        --compteur;
    }
    if (Score < obj)
    {
        cout << "Bien joué ! Vous avez gagné avec un score de " << Score << "points" << endl;
    }
    else
    {
        cout << "Vous avez perdu... La prochaine fois vous reviendrez encore plus fort !" << endl;
    }
}
void Hardcore(mat grid)
{
    int compteur = 10;
    int difficulte;
    sizemat = 6;
    nbBonBons = 5;
    int obj;
    maPosition pos{0, 0};
    cout << "Choississez une difficulté" << endl;
    cout << "--------------------------" << endl;
    cout << "1. Facile (10 coups pour faire 75)" << endl;
    cout << "2. Medieum (10 coups pour faire 100)" << endl;
    cout << "3. Difficile (10 couprs pour faire 120)" << endl;
    cin >> difficulte;
    initGrid(grid, sizemat);
    switch (difficulte)
    {
    case 1:
        obj = 75;
        break;
    case 2:
        obj = 100;
        break;
    case 3:
        obj = 120;
        break;
    }
    while (compteur > 0)
    {
        clearScreen();
        cout << "Nombre de coups Restants :" << compteur << endl;
        cout << "Score :" << Score << endl;
        couleur(KRouge);
        displayGridH(grid);
        initMove(pos);
        MakeAMove(grid, pos);
        Remove(grid);
        gravite(grid);
        NouvBonbons(grid);
        --compteur;
    }
    Score = Score * 2;
    if (Score >= obj)
    {
        cout << "Bien joué ! Vous avez gagné avec un score de " << Score << "points" << endl;
    }
    else
    {
        cout << "Vous avez perdu... La prochaine fois vous reviendrez encore plus fort !" << endl;
    }
}
void afficherLore()
{
    clearScreen();
    couleur(KMAgenta);
    cout << "********************************************" << endl;
    cout << "       L'AVENTURE DU GRAND CASALI          " << endl;
    cout << "********************************************" << endl;
    couleur(KReset);
    cout << endl;

    cout << "Vous etes " << "\033[1;33m" << "Le Grand Casali" << "\033[0m" << ", un jeune magicien prodige." << endl;
    cout << "Votre pouvoir ? Deplacer les " << "\033[36m" << "Bonbons Chiffres" << "\033[0m" << " par le pouvoir des sucreries." << endl
         << endl;

    cout << "Mais une menace plane sur le Royaume de la Confiserie..." << endl;
    cout << "Le redoutable " << "\033[0m" << "MAKROUD" << "\033[0m" << ", une patisserie ancienne et huileuse," << endl;
    cout << "a decide d'ecraser tous les bonbons pour regner en maitre !" << endl
         << endl;

    cout << "Makroud vous attend dans son donjon final." << endl;
    cout << "Il possede " << "\033[1;31m" << "2000 Points de Vie (PV)" << "\033[0m" << "." << endl;
    cout << "Chaque alignement de bonbons lui inflige des degats " << "\033[1;36m" << "magiques" << "\033[0m" << " mais les grand bonbons infligent plus de degats." << endl;
    cout << "Mais vous devez battre des petites sucreries pour voir si vous êtes capable de battre le grand" << "\033[1;31m" << " Makroud." << "\033[1;31m" << endl;

    couleur(KCyan);
    cout << "Grand Casali, preparez votre baguette (clavier) !" << endl;
    couleur(KReset);

    cout << endl;
    cout << "[Appuyez sur ENTREE pour affronter le destin]";
    cin.ignore();
    cin.get();
}
void BarreDeVie(int Score, int obj)
{
    int barreSize = 20;
    int Barre = ((obj - Score) * barreSize) / obj;
    couleur(KRouge);
    for (int i = 0; i < barreSize; ++i)
    {
        if (i < Barre)
            cout << "#";
        else
            cout << " ";
    }
    couleur(KReset);
    cout << "] " << (obj - Score) << "/" << obj << " PV" << endl;
}
void LimiteHist(mat grid, int obj)
{
    maPosition pos{0, 0};
    int compteur = 10;
    sizemat = 6;
    nbBonBons = 5;
    initGrid(grid, sizemat);
    while (compteur > 0)
    {
        clearScreen();
        cout << "Nombre de coups Restants :" << compteur << endl;
        cout << "Score :" << Score << endl;
        displayGrid(grid);
        BarreDeVie(Score, obj);
        initMove(pos);
        MakeAMove(grid, pos);
        Remove(grid);
        gravite(grid);
        NouvBonbons(grid);
        --compteur;
        if (Score > obj)
            cout << "Bien joué ! Vous avez gagné avec un score de " << Score << "points" << endl;
        break;
    }
    if (Score < obj)
    {
        cout << "Vous avez perdu... La prochaine fois vous reviendrez encore plus fort !" << endl;
    }
}
void Niveau1()
{
    mat matrice;
    LimiteHist(matrice, 50);
}
void Niveau2()
{
    mat matrice;
    LimiteHist(matrice, 120);
}
void Boss()
{
    mat matrice;
    cout << "Vous voila contre le maléfique" << "/033[1;31" << "Makroud" << "/033[1;31" << endl
         << "Bonne chance !";
    LimiteHist(matrice, 200);
}
void Histoire(mat matrice)
{
    afficherLore();
    clearScreen();
    cout << "---Niveau 1---" << endl;
    Niveau1();
    clearScreen();
    cout << "---Niveau 2---" << endl;
    Niveau2();
    clearScreen();
    cout << "---Le Boss Final : Makroud---" << endl;
    Boss();
}
int main()
{
    int mode = Menu();
    mat matrice;
    if (mode == 1) // Mode Infini
    {
        Infini(matrice);
    }
    else if (mode == 2)
    {
        Speedrun(matrice);
    }
    else if (mode == 3)
    {
        Limite(matrice);
    }
    else if (mode == 4)
    {
        Histoire(matrice);
    }
    else if (mode == 5)
    {
        Hardcore(matrice);
    }

    return 0;
}