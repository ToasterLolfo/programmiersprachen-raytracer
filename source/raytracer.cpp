#include <renderer.hpp>
#include <window.hpp>
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include "sphere.hpp"
#include "box.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "light.hpp"
#include "sdf-reader.cpp"

int main(int argc, char* argv[])
{
    unsigned const image_width = 2024;
    unsigned const image_height = 1024;
    std::string const filename = "./raytraced_scene.ppm";
    std::string sdf_filename = "C:/Users/Nils Maechler/Desktop/uebungen C++/sdfreader/scene.sdf";  // Annahme: Die Datei ist im aktuellen Verzeichnis

    std::cout << "Versuche, SDF-Datei zu �ffnen: " << sdf_filename << std::endl;

    if (!std::filesystem::exists(sdf_filename)) {
        std::cerr << "Die SDF-Datei existiert nicht: " << sdf_filename << std::endl;
        return 1;
    }

    // SDF-Datei lesen
    auto [materials, cameras] = sdf_reader(sdf_filename);

    std::cout << "Anzahl der gelesenen Materialien: " << materials.size() << std::endl;
    std::cout << "Anzahl der gelesenen Kameras: " << cameras.size() << std::endl;

    if (cameras.empty()) {
        std::cerr << "Keine Kamera in der SDF-Datei definiert." << std::endl;
        return 1;
    }

    // Verwenden Sie die erste Kamera aus der SDF-Datei
    Camera& camera = *cameras[0];

    std::cout << "Kamera erfolgreich geladen." << std::endl;

    // Erstellen Sie einen Renderer mit der Kamera
    Renderer renderer{ image_width, image_height, filename, camera };

    std::cout << "Renderer erstellt." << std::endl;

    // Erstellen Sie Objekte
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.push_back(std::make_shared<Sphere>(1.0f, glm::vec3(-2, 0, 0), "Red Sphere", materials[0]));
    shapes.push_back(std::make_shared<Sphere>(1.5f, glm::vec3(2, 0, 0), "Blue Sphere", materials[2]));
    shapes.push_back(std::make_shared<Box>(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), "Green Box", materials[1]));

    std::cout << "Objekte erstellt." << std::endl;

    // Erstellen Sie Lichtquellen
    std::vector<std::shared_ptr<Light>> lights;
    lights.push_back(std::make_shared<Light>(glm::vec3(5, 5, 5), Color{ 1.0f, 1.0f, 1.0f }));
    //lights.push_back(std::make_shared<Light>(glm::vec3(-10, 5, 5), Color{ 0.5f, 0.5f, 0.5f }));

    std::cout << "Lichtquellen erstellt." << std::endl;

    // F�gen Sie die Objekte und Lichtquellen zum Renderer hinzu
    renderer.add_shapes(shapes);
    renderer.add_lights(lights);

    std::cout << "Objekte und Lichtquellen zum Renderer hinzugef�gt." << std::endl;

    // Rendern Sie die Szene
    std::cout << "Starte Rendering-Prozess..." << std::endl;
    renderer.render();
    std::cout << "Rendering abgeschlossen." << std::endl;

    // Zeigen Sie das gerenderte Bild in einem Fenster an
    std::cout << "�ffne Fenster..." << std::endl;
    Window window{ {image_width, image_height} };

    std::cout << "Fenster erstellt. Starte Render-Schleife..." << std::endl;
    while (!window.should_close()) {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            window.close();
        }
        window.show(renderer.color_buffer());
    }

    std::cout << "Programm beendet." << std::endl;
    return 0;
}