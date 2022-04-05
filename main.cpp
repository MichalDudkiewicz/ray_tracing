#include <iostream>
#include "vector.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include "vector_operators.hpp"
#include "EasyBMP_BMP.h"
#include "EasyBMP_DataStructures.h"
#include "light_intensity.hpp"
#include "scene.hpp"
#include "triangle.hpp"
#include "obj_parser.hpp"

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
    std::optional<Vector> intersectionPoint5a = sphere.intersection(r1);
    std::cout << "Podpunkt 5 - R1: \n";
    if (intersectionPoint5a.has_value())
    {
        std::cout <<intersectionPoint5a.value()<< '\n';
    }

    std::optional<Vector> intersectionPoint5b = sphere.intersection(r2);
    std::cout << "Podpunkt 5 - R2: \n";
    if (intersectionPoint5b.has_value())
    {
        std::cout <<intersectionPoint5b.value()<< '\n';
    }

    //podpunkt 6
    //zdefiniowa� dowolny promie� R3, tak aby przecina� on sfer� S w dok�adnie jednym punkcie.Poda� wsp�rz�dne punktu przeci�cia.
    //czyli np. promien rownoleg�y do jednej z osi ukladu, znajdujacy sie w odleglosci rownej promieniowi sfery

    Vector r3origin(0, 0, 10);
    Vector r3end(0, 20, 10);

    Ray r3(r3origin, r3end, 1000);

    std::optional<Vector> intersectionPoint = sphere.intersection(r3);
    std::cout << "Podpunkt 6: \n";
    if (intersectionPoint.has_value())
    {
        std::cout <<intersectionPoint.value()<< '\n';
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
    const Vector point1(0.0, -0.5, -3.0);
    auto sphere = std::make_shared<Sphere>(point1, 1.0f);
    sphere->setColor({1, 0, 0});
    const Vector point2(0.0, 0.5, -5.0);
    auto sphere2 = std::make_shared<Sphere>(point2, 1.0f);
    sphere2->setColor({0, 1, 0});
    Mesh mesh;
    mesh.addPrimitive(sphere);
    mesh.addPrimitive(sphere2);
    scene.addMesh(mesh);
    scene.camera().setFov(120.0);
    auto image = scene.camera().render();
    image.WriteToFile("rendered_scene.bmp");
}

void task3()
{
    std::string line;
    std::string obj;
    std::ifstream objFile("cube.obj");
    if (objFile.is_open())
    {
        std::ostringstream buffer;
        while (getline(objFile, line))
        {
            buffer << line << '\n';
        }
        obj = buffer.str();
        objFile.close();
    }
    ObjParser objParser(obj);
    const auto mesh = objParser.parse();

    Scene scene;
    scene.addMesh(mesh);
    Vector surfacePoint1(0.2, 0.2, 1);
    scene.camera().setPosition(surfacePoint1);
    scene.camera().setPosition(surfacePoint1);
    auto image = scene.camera().render();
    image.WriteToFile("rendered_scene_with_mesh.bmp");
}

int main() {
//    task1();

//    task2();

    task3();

    return 0;
}
