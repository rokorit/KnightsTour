#include <iostream>
#include <vector>
using namespace std;

const int sirina = 5;
const int visina = 5;
struct a {
    int x;
    int y;
    int test = 0;
};
vector<a> obiskanaPolja;
int poteza = 0;
bool reseno = false;

bool preveriVeljavnost(int x, int y) {
    if (y < 0 || x < 0) {
        return false;
    }
    if (y >= visina || x >= sirina) {
        return false;
    }
    for (int i = 0; i < obiskanaPolja.size(); i++ ) {
        if (obiskanaPolja[i].x == x && obiskanaPolja[i].y == y) {
            return false;
        }
    }
    return true;
}


int noviX(int stariX, int test) {
    if (test == 0 || test == 7) {
        return stariX - 2;
    }
    if (test == 1 || test == 6) {
        return stariX - 1;
    }
    if (test == 3 || test == 4) {
        return stariX + 2;
    }
    if (test == 2 || test == 5) {
        return stariX + 1;
    }
}

int noviY(int stariY, int test) {
    if (test == 0 || test == 3) {
        return stariY + 1;
    }
    if (test == 1 || test == 2) {
        return stariY + 2;
    }
    if (test == 7 || test == 4) {
        return stariY - 1;
    }
    if (test == 6 || test == 5) {
        return stariY - 2;
    }
}

void premik(int x, int y) {
    if (poteza == 0) {
        obiskanaPolja.emplace_back();
    }
    if (poteza == (visina)*(sirina) - 1) {
        obiskanaPolja[poteza].x = x;
        obiskanaPolja[poteza].y = y;
        reseno = true;
        for (int i = 0; i < obiskanaPolja.size(); i++) {
            cout << char(65 + obiskanaPolja[i].x) << "-" << obiskanaPolja[i].y+1 << endl;
        }
    }
    do{
        if (preveriVeljavnost( noviX( x, obiskanaPolja[poteza].test ), noviY( y, obiskanaPolja[poteza].test ) ) ) {
            obiskanaPolja.emplace_back();
            obiskanaPolja[poteza].x = x;
            obiskanaPolja[poteza].y = y;
            poteza++;
            obiskanaPolja[poteza].test = 0;
            premik(noviX( x, obiskanaPolja[poteza - 1].test ), noviY( y, obiskanaPolja[poteza - 1].test ));
        }else {
            obiskanaPolja[poteza].test++;
        }
    }while (obiskanaPolja[poteza].test < 8 && !reseno);
    if (obiskanaPolja[poteza].test == 8 && !reseno) {
        obiskanaPolja.pop_back();
        poteza = poteza - 1;
        obiskanaPolja[poteza].test++;
    }
}

int main() {
    char x;
    int y;
    bool loop;
    cout << "Vpisite zacetni polozaj konja na X osi:";
    do {
        loop = false;
        cin >> x;
        x = tolower(x);
        if (x - 'a' < 0 || x - 'a' >= sirina) {
            loop = true;
            cout << "neveljavni začetni položaj X, vpišite še enkrat:";
        }
    }while (loop);
    cout << "Vpisite zacetni polozaj konja na Y osi:";
    do {
        loop = false;
        cin >> y;
        y--;
        if (y < 0 || y >= visina) {
            loop = true;
            cout << "neveljavni začetni položaj Y, vpišite še enkrat:";
        }
    }while (loop);
    cout<<"program se izvaja..."<<endl;
    premik(x - 'a', y);
    return 0;
}

