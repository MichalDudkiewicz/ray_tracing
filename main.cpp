#include <iostream>
#include "vector.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include "vector_operators.hpp"

using namespace std;

int main() {
    
    //podpunkt 2
    //Zdefiniowa� sfer� S o �rodku w punkcie (0,0,0) i promieniu 10
    Vector centreSphere(0, 0, 0);
    Sphere sphere(centreSphere, 10);

    //podpunkt 3
    //Zdefiniowa� promie� R1 o pocz�tku w punkcie (0,0,-20) i skierowany w �rodek kuli
    Vector r1Origin(0, 0, -20);
    Ray r1(r1Origin, centreSphere, 1000);

    //podpunkt 4
    //Zdefiniowa� promie� R2 o pocz�tku w tym samym punkcie, co R1, skierowany r�wnolegle do osi Y
    //parametry x i z punktu ko�cowego wektora nie zmieniaja sie = wektor rownolegly do y
    Vector r2end(0, 1000, -20);
    Ray r2(r1Origin, r2end, 1000);

    //podpunkt 5
    //Prosz� sprawdzi�, czy istnieje przeci�cie sfery S z promieniami R1 oraz R2. Wynik w postaci wsp�rz�dnych punktu przeci�cia nale�y wy�wietli�.


    //podpunkt 6
    //zdefiniowa� dowolny promie� R3, tak aby przecina� on sfer� S w dok�adnie jednym punkcie.Poda� wsp�rz�dne punktu przeci�cia.
    //czyli np. promien rownoleg�y do jednej z osi ukladu, znajdujacy sie w odleglosci rownej promieniowi sfery

    Vector r3origin(0, 0, 10);
    Vector r3end(0, 20, 10);

    Ray r3(r3origin, r3end, 1000);
    

    float distance = 1000;
    cout << "Podpunkt 6: " <<sphere.intersect(r3, distance)<<endl;

    //podpunkt 7
    //Prosz� zdefiniowa� p�aszczyzn� P przechodz�c� przez punkt(0, 0, 0), kt�rej wektor normalny tworzy k�t 45 stopni z osiami Y i Z.
    // czyli y=z

    Vector surfacePoint1(0, 0, 0);
    Vector surfacePoint2(0, 100, 100);

    Surface p(surfacePoint1, surfacePoint2);

    //podpunkt 8
    //Prosz� znale�� punkt przeci�cia p�aszczyzny P z promieniem R2.


    auto point = p.intersectionPoint(r2);

    if (point.has_value())
    {
        cout << point.value();

    }

    
    return 0;
}
