#include <iostream>
#include "library/src/vector.cpp"
#include "library/src/ray.cpp"
#include "library/src/sphere.cpp"
#include "library/src/surface.cpp"

using namespace std;

int main() {
    
    //podpunkt 2
    //Zdefiniowaæ sferê S o œrodku w punkcie (0,0,0) i promieniu 10
    Vector centreSphere(0, 0, 0);
    Sphere sphere(centreSphere, 10);

    //podpunkt 3
    //Zdefiniowaæ promieñ R1 o pocz¹tku w punkcie (0,0,-20) i skierowany w œrodek kuli
    Vector r1Origin(0, 0, -20);
    Ray r1(r1Origin, centreSphere, 1000);

    //podpunkt 4
    //Zdefiniowaæ promieñ R2 o pocz¹tku w tym samym punkcie, co R1, skierowany równolegle do osi Y
    //parametry x i z punktu koñcowego wektora nie zmieniaja sie = wektor rownolegly do y
    Vector r2end(0, 1000, -20);
    Ray r2(r1Origin, r2end, 1000);

    //podpunkt 5
    //Proszê sprawdziæ, czy istnieje przeciêcie sfery S z promieniami R1 oraz R2. Wynik w postaci wspó³rzêdnych punktu przeciêcia nale¿y wyœwietliæ.


    //podpunkt 6
    //zdefiniowaæ dowolny promieñ R3, tak aby przecina³ on sferê S w dok³adnie jednym punkcie.Podaæ wspó³rzêdne punktu przeciêcia.
    //czyli np. promien rownoleg³y do jednej z osi ukladu, znajdujacy sie w odleglosci rownej promieniowi sfery

    Vector r3origin(0, 0, 10);
    Vector r3end(0, 20, 10);

    Ray r3(r3origin, r3end, 1000);
    

    float distance = 1000;
    cout << "Podpunkt 6: " <<sphere.intersect(r3, distance)<<endl;

    //podpunkt 7
    //Proszê zdefiniowaæ p³aszczyznê P przechodz¹c¹ przez punkt(0, 0, 0), której wektor normalny tworzy k¹t 45 stopni z osiami Y i Z.
    // czyli y=z

    Vector surfacePoint1 = (0, 0, 0);
    Vector surfacePoint2 = (0, 100, 100);

    Surface p(surfacePoint1, surfacePoint2);

    //podpunkt 8
    //Proszê znaleŸæ punkt przeciêcia p³aszczyzny P z promieniem R2.

    
        
    //p.intersectionPoint(r2);

    cout<<p.intersectionPoint(r2).has_value();
    
    return 0;
}
