#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "components/simple_scene.h"


namespace object2D
{
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length1, float length2, glm::vec3 color, bool fill = false);
    Mesh* CreateTrapezoid(const std::string& name, glm::vec3 leftBottomCorner, float base1, float base2, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateSemicircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string& name, glm::vec3 center, float radius, glm::vec3 color, bool fill = false);
    //void CreateLine(Tema1* scene, glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color, Shader* shader);
}