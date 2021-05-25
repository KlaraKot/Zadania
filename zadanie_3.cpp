#include <iostream>
#include <unordered_map>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
using namespace std;

//funkcja hashujaca
double hash_function(int value){
    return value%100;
}


int main() {

    //korzystam z kontenera unordered_map

    unordered_map<double, double > hash_map;
    int tab[7] = {8,6,9,3,5,2,1};

    /*
    tworzenie tablicy z elementami z tablicy tab
    używam tablicy pomocniczej z wartościami ponieważ, chce potem usunąć konkretny element, dlatego chce wiedzieć jakie są w mojej tablicy elementy
    */

    int i=0;
    while(i<7){
        int value = tab[i];
        double hash = hash_function(value);
        hash_map[hash] = value;
        i++;
    }

    //usuwanie z tablicy haszowanej ma złożoność O(1)
    /*
    chce usunac wartosc 9, w normalnej tablicy musiałabym
    przejsc po calej dlugosci i znalezc nasz szukany element. W tablicy hashowanej wystarczy, że podam klucz po ktorym mam usunac element
    */

    double key = hash_function(9);
    hash_map.erase(key);

return 0;

}