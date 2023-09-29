#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Vozlisce {
    int predhodnik;
    int indeks;
    int dolzina;
};

bool primerjaj(Vozlisce *e1, Vozlisce *e2) {
    if (e1->dolzina < e2->dolzina) {
        return true;
    }
    return false;
}

void grafSosednjosti(int **&C, int &steviloVozlisc, int &steviloPovezav) {
    std::ifstream file("graf.txt");

    int v1, v2, cena;

    file >> steviloVozlisc;
    file >> steviloPovezav;

    C = new int *[steviloVozlisc];

    for (int i = 0; i < steviloVozlisc; i++) {
        /*V[i].predhodnik = -1;
        V[i].dolzina = INT_MAX;
        V[i].indeks = i;*/
        C[i] = new int[steviloVozlisc];
    }

    for (int i = 0;  i < steviloVozlisc; i++) {
        for (int j = 0;  j < steviloVozlisc; j++) {
            C[i][j] = 0; // napolnimo matriko s vrednostjo 0
        }
    }

    for (int i = 0; i < steviloPovezav; i++) { // napolnimo povezave s cenami
        file >> v1 >> v2 >> cena;
        C[v1 - 1][v2 - 1] = cena;
        C[v2 - 1][v1 - 1] = cena;
    }

    std::cout << "MATRIKA SOSEDNJOSTI" << "\n";
    std::cout << "-------------------" << "\n";

    for (int i = 0;  i < steviloVozlisc; i++) {
        for (int j = 0;  j < steviloVozlisc; j++) {
            if (C[i][j] >= 10) {
                std::cout << C[i][j] << "  ";
            }
            else {
                std::cout << C[i][j] << "   ";
            }
        }
        std::cout << std::endl;
    }

}

void dijkstra(Vozlisce *&V, int **&C, int s, int &steviloVozlisc, int &steviloPovezav) {

    //std::priority_queue< Vozlisce, std::vector<Vozlisce>, Primerjaj > priorQ;
    std::vector<Vozlisce*> Q;

    int v = 0;
    Vozlisce *u;

    //Vozlisce *temp = new Vozlisce;
    for (int l = 0; l < steviloVozlisc; l++) {
        V[l].dolzina = INT_MAX;
        V[l].predhodnik = -1;
        V[l].indeks = l;
    }

    V[s].dolzina = 0; // dolzino zacetnega vozlisca damo na 0

    Q.reserve(steviloVozlisc);
    for (int i = 0; i < steviloVozlisc; i++) {
        //V.push_back(temp);
        Q.push_back(&V[i]); // vrsto napolnimo z vrednostmi iz vozlisca
    }

    for (int iterator = 0; iterator < steviloVozlisc; iterator++) {
        std::sort(Q.begin(), Q.end(), primerjaj); // sortiramo cene v vrsti
        u = Q[iterator]; // premikamo se po vektorju

        //std::cout << Q.front()->dolzina << " ";

        for (int k = 0; k < steviloVozlisc; k++) {
            for (int m = 0; m < steviloVozlisc; m++) {
                if (Q[m]->indeks == k) {
                    v = m;
                }
            }

            if (C[u->indeks][k] != 0) { // ce cena ni 0
                if (Q[v]->dolzina > u->dolzina + C[u->indeks][k]) { // ce je dolzina manjsa od dolzine in cene
                    Q[v]->dolzina = u->dolzina + C[u->indeks][k];
                    //std::cout << V[v].dolzina << " ";
                    Q[v]->predhodnik = u->indeks; // predhodnik postane u
                }
            }
        }

        /*for(int i = 0; i <steviloVozlisc; i++) {
            std::cout << V[i].indeks << " " << V[i].dolzina << " " << V[i].predhodnik << "\n";
        }*/
    }
}

void izpis(Vozlisce *&V, int &steviloVozlisc) {
    for (int i = 0; i < steviloVozlisc; i++) {
        std::cout << "VOZLISCE " << V[i].indeks
                  << " Dolzina poti: " << V[i].dolzina << " Predhodnik: " << V[i].predhodnik << "\n";
    }
}

void izpisPoti(Vozlisce *&V, int s, int v) {
    if (v == s) {
        std::cout << V[s].indeks << ": dolzina: " << V[s].dolzina << "\n";
    }
    else {
        if (V[v].indeks == -1) {
            std::cout << "Med " << s << " in " << v << + " ni poti" << "\n";
        }
        else {
            izpisPoti(V, s, V[v].predhodnik);
            std::cout << V[v].indeks << ": dolzina: " << V[v].dolzina << "\n";
        }
    }
}

void meni() {
    std::cout << "Dijkstrov algoritem - izbira:" << "\n";
    std::cout << "1) Nalozi graf" << "\n";
    std::cout << "2) Zagon algoritma" << "\n";
    std::cout << "3) Izpis najkrajse poti" << "\n";
    std::cout << "4) Konec" << "\n";
    std::cout << "Vasa izbira: ";
}

int main() {
    auto *V = new Vozlisce;
    int **C = nullptr;
    int steviloVozlisc = 0;
    int steviloPovezav = 0;

    int vozlisceS = 0, vozlisceV = 0;
    bool pogoj1 = false, pogoj2 = false;

    int selection;
    bool running = true;
    do {
        meni();
        std::cin >> selection;

        switch (selection) {
            case 1:
                grafSosednjosti(C, steviloVozlisc, steviloPovezav);
                pogoj1 = true;
                break;
            case 2:
                if (pogoj1) {
                    std::cout << "Vnesi zacetno vozlisce s: ";
                    std::cin >> vozlisceS;
                    dijkstra(V, C, vozlisceS, steviloVozlisc, steviloPovezav);
                    izpis(V, steviloVozlisc);
                    pogoj1 = true;
                    pogoj2 = true;
                    break;
                }
                std::cout << "Prvo generiraj graf!" << "\n";
                pogoj1 = false;
                break;
            case 3:
                if (pogoj2) {
                    std::cout << "Vnesi koncno vozlisce v: ";
                    std::cin >> vozlisceV;
                    izpisPoti(V, vozlisceS, vozlisceV);
                    std::cout << "\n";
                    break;
                }
                else {
                    std::cout << "Prvo zazeni algoritem!" << "\n";
                    break;
                }
            case 4:
                running = false;
                break;
            default:
                std::cout << "Napacna izbira!\n";
                break;
        }
    } while(running);

    delete [] C;

    return 0;
}
