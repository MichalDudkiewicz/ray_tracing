#include <iostream>
#include "vector.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include <vector>
#include "vector_operators.hpp"
#include "EasyBMP_BMP.h"
#include "EasyBMP_DataStructures.h"
#include "light_intensity.hpp"
#include "scene.hpp"
#include "triangle.hpp"

void task1()
{
    //podpunkt 2
    //Zdefiniowa� sfer� S o �rodku w punkcie (0,0,0) i promieniu 10
    Vector centreSphere(0, 0, 0);
    Sphere sphere(centreSphere, 10);

    //podpunkt 3
    //Zdefiniowa� promie� R1 o pocz�tku w punkcie (0,0,-20) i skierowany w �rodek kuli
    Vector r1Origin(0, 0, -20);
    Vector centreSphereDirection(0, 0, 20);
    Ray r1(r1Origin, centreSphereDirection, 1000);

    //podpunkt 4
    //Zdefiniowa� promie� R2 o pocz�tku w tym samym punkcie, co R1, skierowany r�wnolegle do osi Y
    //parametry x i z punktu ko�cowego wektora nie zmieniaja sie = wektor rownolegly do y
    Vector r2end(0, 1000, -20);
    Ray r2(r1Origin, r2end, 1000);

    //podpunkt 5
    //Prosz� sprawdzi�, czy istnieje przeci�cie sfery S z promieniami R1 oraz R2. Wynik w postaci wsp�rz�dnych punktu przeci�cia nale�y wy�wietli�.
    std::vector<Vector> intersectionPoints5a = sphere.intersect(r1);
    std::cout << "Podpunkt 5 - R1: \n";
    if (!intersectionPoints5a.empty())
    {
        for (const auto& intersectionPoint : intersectionPoints5a)
        {
            std::cout <<intersectionPoint<< '\n';
        }
    }

    std::vector<Vector> intersectionPoints5b = sphere.intersect(r2);
    std::cout << "Podpunkt 5 - R2: \n";
    if (!intersectionPoints5b.empty())
    {
        for (const auto& intersectionPoint : intersectionPoints5b)
        {
            std::cout <<intersectionPoint<< '\n';
        }
    }

    //podpunkt 6
    //zdefiniowa� dowolny promie� R3, tak aby przecina� on sfer� S w dok�adnie jednym punkcie.Poda� wsp�rz�dne punktu przeci�cia.
    //czyli np. promien rownoleg�y do jednej z osi ukladu, znajdujacy sie w odleglosci rownej promieniowi sfery

    Vector r3origin(0, 0, 10);
    Vector r3end(0, 20, 10);

    Ray r3(r3origin, r3end, 1000);

    std::vector<Vector> intersectionPoints = sphere.intersect(r3);
    std::cout << "Podpunkt 6: \n";
    if (!intersectionPoints.empty())
    {
        for (const auto& intersectionPoint : intersectionPoints)
        {
            std::cout <<intersectionPoint<< '\n';
        }
    }


    //podpunkt 7
    //Prosz� zdefiniowa� p�aszczyzn� P przechodz�c� przez punkt(0, 0, 0), kt�rej wektor normalny tworzy k�t 45 stopni z osiami Y i Z.
    // czyli y=z

    Vector surfacePoint1(0, 0, 0);
    Vector surfacePoint2(0, 100, 100);

    Surface p(surfacePoint1, surfacePoint2);

    //podpunkt 8
    //Prosz� znale�� punkt przeci�cia p�aszczyzny P z promieniem R2.

    const auto point = p.intersectionPoint(r3);

    if (point.has_value())
    {
        std::cout << point.value();

    }
}



void task2()
{
    Scene scene;
    Sphere sphere({0.0, -0.5, -3.0}, 1.0f);
    sphere.setColor({1, 0, 0});
    Sphere sphere2({0.0, 0.5, -5.0}, 1.0f);
    sphere2.setColor({0, 1, 0});
    scene.addPrimitive(sphere);
    scene.addPrimitive(sphere2);
    scene.camera().setFov(120.0);
    auto image = scene.camera().render();
    image.WriteToFile("rendered_scene.bmp");
}

int main() {
//    task1();

//    task2();

    Vector p1(0, 0, 0);
    Vector p2(10, 0, 0);
    Vector p3(0, 10, 0);
    Vector p4(0, 0, 10);
    Triangle triangle(p1, p2, p3);

    Vector p(5, 5, 0);
    Ray r3(p, p4, 1000);

    const auto point = triangle.intersection(r3);


    return 0;
}
