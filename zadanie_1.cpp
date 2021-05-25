/*
 * OPIS ALGORYTMU
 * Mój algorytm powstał na podstawie następującego rozumowania:
 * dla każdego wektora 3d istnieją płaszczyzny prostopadłe do niego.
 * Zbliżając tę płaszczyznę w stronę przeciwną do kierunku wektora pierwszy punkt należący do bryły,
 * ktory "przetnie" płaszczyznę będzie
 * punktem najdalej oddalonym w kierunku wektora. Z tego wynika, że w przypadku szescianu, kapsuły i
 * czworościanu wystarczy wziąć pod uwagę jedynie wierzchołki.
 * W przypadku sfery wszystkie punkty należace do powierechni są potencjalnymi rozwiązaniami.
 * Wybór wierzchołka opieram na wzorze, który mówi , że trzeba wybrać ten wierzchołek który ma największy iloczyn skalarny
 * z podanym wektorem.
 * Dla sfery korzystam ze wzoru : center + radius * (v \ ||v||)
 */

#include<stdio.h>
#include <math.h>
struct vec3 { float x,y,z; };

struct Sphere
{
    vec3 center;
    float radius;

        vec3 support(vec3 v){
            vec3 support_point;
            double length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
            support_point.x = center.x + (this->radius*(v.x/length));
            support_point.y = center.y + (this->radius*(v.y/length));
            support_point.z = center.z (this->radius*(v.z/length));
            return support_point;
        }
};

// Axis-aligned bounding box. Cube with edges aligned to x,y,z axis.
//szescian 3D
struct Aabb
{
    vec3 min; //przyjmuję, że dane wspołrzedne to współrzędne wierzchołkow dolnych szescianu
    vec3 max;

    vec3 support_function(vec3 v){
        vec3 points[8];
        //w pierwszej kolejnosci wyliczamy wszystkie wierzcholki
        int length = sqrt((max.x-min.x)*(max.x-min.x) + (max.y-min.y)*(max.y-min.y) * (max.z-min.z)*(max.z-min.z));
        points[0].x = min.x;
        points[0].y = min.y + length;
        points[0].z = min.z;
        points[1].x = min.x;
        points[1].y = min.y;
        points[1].z = min.z + length;
        points[2].x = min.x;
        points[2].y = min.y + length;
        points[2].z = min.z + length;
        points[3].x = min.x + length;
        points[3].y = min.y + length;
        points[3].z = min.z + length;
        points[4].x = max.x;
        points[4].y = max.y;
        points[4].z = max.z + length;
        points[5].x = max.x;
        points[5].y = max.y + length;
        points[5].z = max.z;
        points[6] = min;
        points[7] = max;

        /*
         * teraz dla kazdego wierzchołka obliczam iloczyn skalarny z naszym wektorem v. Ten z największą wartoscią to nasz
         * poszukiwany punkt
         */

        int max_dot_product = 0;
        int current_dot_product =0 ;
        vec3 support_point;
        for(int i=0; i<8; i++){
            current_dot_product = points[i].x * v.x + points[i].y * v.y + points[i].z * v.z;
            if(current_dot_product > max_dot_product){
                max_dot_product = current_dot_product;
                support_point.x = points[i].x;
                support_point.y = points[i].y;
                support_point.z = points[i].z;
            }
        }

    return support_point;

    }
};

// Triangular pyramid.
//pyramida 3D
struct Tetrahedron
{
    vec3 points[4];


    vec3 support_function(vec3 v){
        int max_dot_product = 0;
        int current_dot_product =0 ;
        vec3 support_point;
        //wyliczam dla każdego wierzchołka iloczyn skalarny, ten z najwieksza wartością,
        // to nasz poszukiwany punkt
        for(int i=0; i<4; i++){
            current_dot_product = points[i].x * v.x + points[i].y * v.y + points[i].z * v.z;
            if(current_dot_product > max_dot_product){
                max_dot_product = current_dot_product;
                support_point.x = points[i].x;
                support_point.y = points[i].y;
                support_point.z = points[i].z;
            }
        }
        return support_point;
    }
};

// Cylinder with hemispherical ends.
//kapsuła
struct Capsule

{
    vec3 points[2];// zakładam, że te dwa punkty to współrzeðne środków pół-sfer znajdujących sie u góry kapsuły
                    //points[0] -> współrzedna gornego srodka
                    //points[1] -> wspołrzedna dolnego środka
    float radius;

    vec3 support_function(vec3 v){
        /* w przypadku kapsuły zakładam, że jest ona ustawiona pionowo
         * postępuję podobnie jak dla sfery
        */
            vec3 support_point;
            double length = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
            support_point.x = points[0].x + (this->radius*(v.x/length));
            support_point.y = points[0].y + (this->radius*(v.y/length));
            support_point.z = points[0].z + (this->radius*(v.z/length));

            //trzeba wziac pod uwagę ze nasz punkt może wyjść nie na górnej powierzchni kapsuły
            //oznacza to, że punkt znajduje się na dolnej powierzcni kapsuły

            if(support_point.y < points[0].y){
                support_point.x = points[1].x + (this->radius*(v.x/length));
                support_point.y = points[1].y + (this->radius*(v.y/length));
                support_point.z = points[1].z + (this->radius*(v.z/length));
            }
            
            return support_point;
    }
} ;

