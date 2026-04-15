#pragma once
#include <glm/glm.hpp>

struct Tri 
{
public:
    glm::vec3 vertex0;
    glm::vec3 vertex1;
    glm::vec3 vertex2;
    glm::vec3 centroid;

    Tri(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
        : vertex0(v0), vertex1(v1), vertex2(v2), centroid(0.0f) {}
    
    // Default constructor
    Tri() : vertex0(0.0f), vertex1(0.0f), vertex2(0.0f), centroid(0.0f) {}
};