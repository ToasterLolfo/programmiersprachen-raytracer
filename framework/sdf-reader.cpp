/*// material parsing example: Aufgabe 6.5

#include <glm/glm.hpp>

#include <iostream>
//file stream for opening files
#include <fstream>
#include <string>
// stringstream for getting parts of the read string (tokens) and
// streaming them into our Material Variables 
#include <sstream>
#include <vector>
#include "Material.hpp"
 
std::vector<std::shared_ptr<Material>> sdf_reader(std::string const sdf_file_path) {
    std::ifstream sdf_file(sdf_file_path);
    if (!sdf_file.is_open()) {
        std::cout << "Could not find or open: " << sdf_file_path << std::endl;
        std::vector<std::shared_ptr<Material>> ergeb = {};
        return ergeb;
    }

    std::vector<std::shared_ptr<Material>> mat_vec;
    std::string line_buffer;

    while (std::getline(sdf_file, line_buffer)) {
        // debug info
        // std::cout << line_count << ": " << line_buffer << std::endl;
        // ++line_count;

        // we construct an istringstream from our line buffer
        std::istringstream line_as_stream(line_buffer);

        // from here on forward we can us our stringstream object
        // to stream the next token (i.e. word until next whitespace
        // character) into compatible variables
        std::string token;
        // give us the first token (should be 'define')
        line_as_stream >> token;
        // if so, we continue
        if ("define" == token) {
            // get the next token, can only be 'material' for now
            line_as_stream >> token;
            // if so, we continue
            if ("material" == token) {

                
                Material parsed_material;
                auto mat_zeig = std::make_shared<Material> (/*parsed_material*//*);

                // parse the remaining expected parameters one by one and in order
                line_as_stream >> mat_zeig->name;

                
                // the first 3 floats represent ambient light reflection 
                // capabilities of the material (ka_red, ka_green, ka_blue)

                line_as_stream >> mat_zeig->ka.r;
                line_as_stream >> mat_zeig->ka.g;
                line_as_stream >> mat_zeig->ka.b;


                
                // the second 3 floats represent diffuse light reflection 
                // capabilities of the material (kd_red, kd_green, kd_blue)

                line_as_stream >> mat_zeig->kd.r;
                line_as_stream >> mat_zeig->kd.g;
                line_as_stream >> mat_zeig->kd.b;


                
                // the second 3 floats represent specular light reflection 
                // capabilities of the material (ks_red, ks_green, ks_blue)
                line_as_stream >> mat_zeig->ks.r;
                line_as_stream >> mat_zeig->ks.g;
                line_as_stream >> mat_zeig->ks.b;

                // the last float represents the specular power of the material (i.e.
                // whether we create hard, small highlights, or large, soft highlights)
                line_as_stream >> mat_zeig->m;

                mat_vec.push_back(mat_zeig);

                // just as a sanity check, print the material attributes
                std::cout << "Parsed material " <<
                    mat_zeig->name << " "
                    << parsed_material.ka << " " << parsed_material.kd << " " << parsed_material.ks << " " << parsed_material.m << std::endl;
            }
            else {
                std::cout << "Unexpected keyword: " << token << std::endl;
            }
        }
        else {
            std::cout << "Unexpected keyword: " << token << std::endl;
        }

    }
    sdf_file.close();
    return mat_vec;
}*/

#include "Material.hpp"
#include "camera.hpp"

#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm> // für std::all_of

std::tuple<std::vector<std::shared_ptr<Material>>, std::vector<std::shared_ptr<Camera>>> sdf_reader(const std::string& sdf_file_path) {
    std::ifstream sdf_file(sdf_file_path);
    if (!sdf_file.is_open()) {
        std::cerr << "Konnte Datei nicht finden oder oeffnen: " << sdf_file_path << std::endl;
        return {};
    }

    std::vector<std::shared_ptr<Material>> mat_vec;
    std::vector<std::shared_ptr<Camera>> cam_vec;
    std::string line_buffer;

    while (std::getline(sdf_file, line_buffer)) {
        // Entferne führende Leerzeichen
        line_buffer.erase(line_buffer.begin(), std::find_if(line_buffer.begin(), line_buffer.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));

        // Ignoriere leere Zeilen
        if (line_buffer.empty()) {
            continue;
        }

        // Ignoriere einzeilige Kommentare
        if (line_buffer[0] == '#') {
            continue;
        }

        // Ignoriere mehrzeilige Kommentare
        if (line_buffer.substr(0, 2) == "/*") {
            while (std::getline(sdf_file, line_buffer) && line_buffer.find("*/") == std::string::npos) {
                // Lese weiter, bis das Ende des Kommentars gefunden wird
            }
            continue;
        }

        std::istringstream line_as_stream(line_buffer);
        std::string token;

        line_as_stream >> token;
        if (token == "define") {
            line_as_stream >> token;
            if (token == "material") {
                auto mat_ptr = std::make_shared<Material>();

                // Material-Eigenschaften parsen
                line_as_stream >> mat_ptr->name
                    >> mat_ptr->ka.r >> mat_ptr->ka.g >> mat_ptr->ka.b
                    >> mat_ptr->kd.r >> mat_ptr->kd.g >> mat_ptr->kd.b
                    >> mat_ptr->ks.r >> mat_ptr->ks.g >> mat_ptr->ks.b
                    >> mat_ptr->m;

                mat_vec.push_back(mat_ptr);

                std::cout << "Material geparst: " << mat_ptr->name << " "
                    << mat_ptr->ka << " " << mat_ptr->kd << " " << mat_ptr->ks << " " << mat_ptr->m << std::endl;
            }
            else if (token == "camera") {
                std::string name;
                float fov_x;
                glm::vec3 eye, dir, up;

                line_as_stream >> name >> fov_x
                    >> eye.x >> eye.y >> eye.z
                    >> dir.x >> dir.y >> dir.z
                    >> up.x >> up.y >> up.z;

                auto cam_ptr = std::make_shared<Camera>(name, fov_x, eye, dir, up);
                cam_vec.push_back(cam_ptr);

                std::cout << "Kamera geparst: " << name << " FOV: " << fov_x
                    << " Auge: (" << eye.x << "," << eye.y << "," << eye.z << ")"
                    << " Richtung: (" << dir.x << "," << dir.y << "," << dir.z << ")"
                    << " Oben: (" << up.x << "," << up.y << "," << up.z << ")" << std::endl;
            }
            else {
                std::cerr << "Unerwartetes Schlüsselwort nach 'define': " << token << std::endl;
            }
        }
        else if (!std::all_of(line_buffer.begin(), line_buffer.end(), ::isspace)) {
            std::cerr << "Unerwartetes Schlüsselwort oder ungültige Zeile: " << line_buffer << std::endl;
        }
    }

    return std::make_tuple(mat_vec, cam_vec);
}
