#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftUpperCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftUpperCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0, -length, 0), color),
        VertexFormat(corner + glm::vec3(length, -length, 0), color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length1, // height
    float length2, // width
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(0, length1, 0), color),
        VertexFormat(corner + glm::vec3(length2, length1, 0), color),
        VertexFormat(corner + glm::vec3(length2, 0, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateTrapezoid(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float base1,
    float base2,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices = {
        VertexFormat(corner, color), 
        VertexFormat(corner + glm::vec3(base1, 0, 0), color), 
        VertexFormat(corner + glm::vec3((base1 - base2) / 2, height, 0), color), 
        VertexFormat(corner + glm::vec3(base1 - (base1 - base2) / 2, height, 0), color)
    };

    Mesh* trapezoid = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 2, 1, 3 }; 

    if (!fill) {
        trapezoid->SetDrawMode(GL_LINE_LOOP); 
    }

    trapezoid->InitFromData(vertices, indices);
    return trapezoid;
}

Mesh* object2D::CreateSemicircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(VertexFormat(center, color));

    int numSegments = 50; 
    for (int i = 0; i <= numSegments; i++) {
        float angle = M_PI * i / numSegments; 
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);

        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
        if (i > 0) {
            indices.push_back(0);     
            indices.push_back(i);    
            indices.push_back(i + 1); 
        }
    }

    Mesh* semicircle = new Mesh(name);

    if (!fill) {
        semicircle->SetDrawMode(GL_LINE_LOOP);
        indices.clear();
        for (int i = 1; i <= numSegments + 1; i++) {
            indices.push_back(i); 
        }
    }

    semicircle->InitFromData(vertices, indices);
    return semicircle;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float radius,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back(VertexFormat(center, color));

    int numSegments = 50; 
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments; 
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);

        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));

        if (i > 0) {
            indices.push_back(0); 
            indices.push_back(i); 
            indices.push_back(i + 1); 
        }
    }

    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
        indices.clear();
        for (int i = 1; i <= numSegments; i++) {
            indices.push_back(i);
        }
        indices.push_back(1); 
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

//Mesh* object2D::CreateLine(glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color) {
//    std::vector<VertexFormat> vertices = {
//        VertexFormat(startPoint, color),  
//        VertexFormat(endPoint, color)   
//    };
//    std::vector<unsigned int> indices = { 0, 1 };
//
//    Mesh* line = new Mesh("Line");
//    line->SetDrawMode(GL_LINES); 
//    line->InitFromData(vertices, indices);
//    return line;
//
//    //RenderMesh2D(line, shaders["VertexColor"], glm::mat3(1));
//}



