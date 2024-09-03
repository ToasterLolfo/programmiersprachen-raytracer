//Aufgabe 7 hinzugefügt

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include "color.hpp"

class Light {
public:
    Light(glm::vec3 const& pos, Color const& col)
        : position(pos), color(col) {}

    glm::vec3 position;
    Color color;
};

#endif // LIGHT_HPP
