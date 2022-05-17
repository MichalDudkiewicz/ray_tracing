#include <iostream>
#include "vector.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "surface.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
#include "vector_operators.hpp"
#include "EasyBMP_BMP.h"
#include "EasyBMP_DataStructures.h"
#include "light_intensity.hpp"
#include "scene.hpp"
#include "triangle.hpp"
#include "obj_parser.hpp"
#include "plane.hpp"

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

    const auto point = p.intersection(r3);

    if (point.has_value())
    {
        std::cout << point.value();

    }
}



void task2()
{
//    Scene scene;
//    const Vector point1(0.0, -0.5, -3.0);
//    auto sphere = std::make_shared<Sphere>(point1, 1.0f);
//    sphere->setAmbientLightIntensity({1, 0, 0});
//    const Vector point2(0.0, 0.5, -5.0);
//    auto sphere2 = std::make_shared<Sphere>(point2, 1.0f);
//    sphere2->setAmbientLightIntensity({0, 1, 0});
//    Mesh mesh;
//    mesh.addPrimitive(sphere);
//    mesh.addPrimitive(sphere2);
//    scene.addMesh(mesh);
//    scene.camera().setFov(120.0);
//    auto image = scene.camera().render();
//    image.WriteToFile("rendered_scene.bmp");
}

void task3()
{
    Mesh mesh2;
    LightIntensity allLight(1.0f, 1.0f, 1.0f);
    const LightIntensity diffuse(0.5f, 0.5f, 0.5f);
    const LightIntensity specular(0.6f, 0.6f, 0.6f);
    const std::shared_ptr<Material> material = std::make_shared<Material>("", allLight, diffuse, specular, 0.5f);
    BMP imageT;
    imageT.ReadFromFile("earth.bmp");
    const auto texture = std::make_shared<Texture>(imageT);
    material->setTexture(texture);

    Vector centerSphere(0, 0, -1.5f);
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(centerSphere, 1.0f);
    mesh2.setMaterial(material);
    mesh2.addPrimitive(sphere);

    Vector lowerLeft(-3.0f, -7.0f, -4.0f);
    Vector upperRight(8.0f, 7.0f, -4.0f);
    Vector normal(0, 0, 1.0f);
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(lowerLeft, upperRight, normal);
    Mesh mesh1;
    LightIntensity dark(0.4f, 0.4f, 0.4f);
    const LightIntensity noLight(0.0f, 0.0f, 0.0f);
    const std::shared_ptr<Material> material2 = std::make_shared<Material>("", dark, noLight, noLight, 0.0f);
    BMP imageT2;
    imageT2.ReadFromFile("sky.bmp");
    const auto texture2 = std::make_shared<Texture>(imageT2);
    material2->setTexture(texture2);
    material2->setShadowLight(noLight);
    mesh1.setMaterial(material2);
    mesh1.addPrimitive(plane);
    Scene scene;
    scene.addMesh(mesh2);
    scene.addMesh(mesh1);
    Vector surfacePoint1(1.5, 0, 1.5);
    scene.camera().setPosition(surfacePoint1);
    auto image = scene.camera().render();
    image.WriteToFile("result.bmp");
}

int main() {
//    task1();

//    task2();

//    taskX();
    const LightIntensity ambientLight(0.05f, 0.05f, 0.05f);

    Mesh leftSideMesh("left");
    const LightIntensity redLight(1.0f);
    const auto redMaterial = std::make_shared<Material>("", ambientLight, redLight);
    leftSideMesh.setMaterial(redMaterial);
    const Vector leftSide(-1.0f);
    const Vector leftNormal(1.0f);
    const auto leftWall = std::make_shared<Surface>(leftSide, leftNormal);
    leftSideMesh.addPrimitive(leftWall);

    Mesh rightSideMesh("right");
    const LightIntensity blueLight(0.0f, 0.0f, 1.0f);
    const auto blueMaterial = std::make_shared<Material>("", ambientLight, blueLight);
    rightSideMesh.setMaterial(blueMaterial);
    const Vector rightSide(1.0f);
    const Vector rightNormal(-1.0f);
    const auto rightWall = std::make_shared<Surface>(rightSide, rightNormal);
    rightSideMesh.addPrimitive(rightWall);

    Mesh restSidesMesh;
    const LightIntensity greyLight(0.3f, 0.3f, 0.3f);
    const auto greyMaterial = std::make_shared<Material>("", ambientLight, greyLight);
    restSidesMesh.setMaterial(greyMaterial);

    const Vector backSide(0.0f, 0.0f, -2.0f);
    const Vector backNormal(0.0f, 0.0f, 1.0f);
    const auto backWall = std::make_shared<Surface>(backSide, backNormal);
    restSidesMesh.addPrimitive(backWall);

    const Vector bottomSide(0.0f, -1.0f);
    const Vector bottomNormal(0.0f, 1.0f);
    const auto bottomWall = std::make_shared<Surface>(bottomSide, bottomNormal);
    restSidesMesh.addPrimitive(bottomWall);

    const Vector upperSide(0.0f, 1.0f);
    const Vector upperNormal(0.0f, -1.0f);
    const auto upperWall = std::make_shared<Surface>(upperSide, upperNormal);
    restSidesMesh.addPrimitive(upperWall);

    Mesh frontSideMesh;
    const LightIntensity greenLight(0.0f, 1.0f, 0.0f);
    const auto greenMaterial = std::make_shared<Material>("", ambientLight, greenLight);
    frontSideMesh.setMaterial(greenMaterial);
    const Vector frontSide(0.0f, 0.0f, 0.5f);
    const Vector frontNormal(0.0f, 0.0f, -1.0f);
    const auto frontWall = std::make_shared<Surface>(frontSide, frontNormal);
    frontSideMesh.addPrimitive(frontWall);

    Mesh sphereMirrorMesh("sfera");
    const auto mirrorMaterial = std::make_shared<Material>("", ambientLight, greyLight, greyLight, 8.0f);
    mirrorMaterial->setMirror(true);
    sphereMirrorMesh.setMaterial(mirrorMaterial);
    const Vector sphere1Center(0.0f, -0.75f, -1.5f);
    const auto sphere1 = std::make_shared<Sphere>(sphere1Center, 0.25f);
    sphereMirrorMesh.addPrimitive(sphere1);

    Mesh sphereGlassMesh("sfera2");
    const auto glassMaterial = std::make_shared<Material>("", ambientLight, greyLight, greyLight, 16.0f);
    glassMaterial->setRefractionFactor(1.52f);
    sphereGlassMesh.setMaterial(glassMaterial);
    const Vector sphere2Center(0.75f, -0.75f, -1.25f);
    const auto sphere2 = std::make_shared<Sphere>(sphere2Center, 0.25f);
    sphereGlassMesh.addPrimitive(sphere2);

    Mesh lightSphereMesh("sferaLight");
    auto lightMaterial = std::make_shared<Material>("", ambientLight, greyLight);
    const LightIntensity lightEmitted(0.9f, 0.9f, 0.9f);
    lightMaterial->setLightEmitted(lightEmitted);
    lightSphereMesh.setMaterial(lightMaterial);
    const Vector sphere3Center(-0.5f, -0.75f, -1.0f);
    const auto sphere3 = std::make_shared<Sphere>(sphere3Center, 0.25f);
    lightSphereMesh.addPrimitive(sphere3);

    Scene scene;
    scene.addMesh(leftSideMesh);
    scene.addMesh(rightSideMesh);
    scene.addMesh(restSidesMesh);
    scene.addMesh(sphereMirrorMesh);
    scene.addMesh(frontSideMesh);
    scene.addMesh(sphereGlassMesh);
    scene.addMesh(lightSphereMesh);

    LightIntensity li(0.3, 0.3, 0.3);
    Vector lp(0.5, 1.0, -1.5);

    auto light = std::make_shared<PointLight>(li, lp);
    scene.addLight(light);


    LightIntensity li1(0.3, 0.3, 0.3);
    Vector lp1(-0.5, 1.0, -1.5);

    auto light1 = std::make_shared<PointLight>(li1, lp1);
    scene.addLight(light1);


    Vector centerPoint;
    scene.camera().setPosition(centerPoint);
    scene.camera().setFarPlane(3.0f);

    const auto start = std::chrono::steady_clock::now();

    auto image = scene.camera().render();

    const auto end = std::chrono::steady_clock::now();
    const auto time_span = static_cast<std::chrono::duration<double>>(end - start);
    std::cout<<"Rendering time: " << time_span.count() << " seconds";

    image.WriteToFile("result.bmp");

    return 0;
}
