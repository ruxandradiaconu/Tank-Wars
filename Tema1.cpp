#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::Init()
{
    resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    Mesh* square = (object2D::CreateSquare("square", glm::vec3(0, 0, 0), 1, glm::vec3(0.8f, 0.55f, 0.20f), true));
    AddMeshToList(square);
    
    // Trapezul de sus al tancului 
	Mesh* trapezoid11 = object2D::CreateTrapezoid("trapezoid11", glm::vec3(0, 0, 0), 100, 50, 20, glm::vec3(0.4f, 0.3f, 1.0f), true);
    AddMeshToList(trapezoid11);

    // Trapezul de la baza
    Mesh* trapezoid12 = object2D::CreateTrapezoid("trapezoid12", glm::vec3(0, 0, 0), 30, 50, 10, glm::vec3(0.0f, 0.0f, 0.0f), true);
    AddMeshToList(trapezoid12);

    Mesh* trapezoid21 = object2D::CreateTrapezoid("trapezoid21", glm::vec3(0, 0, 0), 100, 50, 20, glm::vec3(0.4f, 1.0f, 0.3f), true);
    AddMeshToList(trapezoid21);

    Mesh* trapezoid22 = object2D::CreateTrapezoid("trapezoid22", glm::vec3(0, 0, 0), 30, 50, 10, glm::vec3(0.0f, 0.0f, 0.0f), true);
    AddMeshToList(trapezoid22);

    Mesh* semicircle = object2D::CreateSemicircle("semicircle", glm::vec3(0, 0, 0), 16, glm::vec3(0.0f, 0.0f, 0.0f), true);
    AddMeshToList(semicircle);

    Mesh* rectangle = object2D::CreateRectangle("rectangle", glm::vec3(0, 0, 0), 8, 40, glm::vec3(0.0f, 0.0f, 0.0f), true);
    AddMeshToList(rectangle);

    Mesh* rectangleOutline = object2D::CreateRectangle("rectangleOutline", glm::vec3(0, 0, 0), 12, 80, glm::vec3(0, 0, 0), false);
    AddMeshToList(rectangleOutline);

    Mesh* rectangleLife = object2D::CreateRectangle("rectangleLife", glm::vec3(0, 0, 0), 12, 80, glm::vec3(0, 0, 0), true);
    AddMeshToList(rectangleLife);

    Mesh* circle = object2D::CreateCircle("circle", glm::vec3(0, 0, 0), 4 , glm::vec3(0.4f, 0.3f, 1.0f), true);
    AddMeshToList(circle);

    // Cercurile pentru crearea norilor
    Mesh* nor1 = object2D::CreateCircle("nor1", glm::vec3(0, 0, 0), 12, glm::vec3(0.9f, 0.9f, 0.9f), true);
    AddMeshToList(nor1);
    Mesh* nor2 = object2D::CreateCircle("nor2", glm::vec3(0, 0, 0), 10, glm::vec3(0.9f, 0.9f, 0.9f), true);
    AddMeshToList(nor2);
    Mesh* nor3 = object2D::CreateCircle("nor3", glm::vec3(0, 0, 0), 8, glm::vec3(0.9f, 0.9f, 0.9f), true);
    AddMeshToList(nor3);

    for (int i = 0; i < 1300; i++) {
        float x = i * step;
        heightMap.push_back(300 + 50 * sin(0.01 * x) + 35 * sin(0.02 * x));
    }

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.8f, 1.0f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    // Metoda 1 de creare a terenului
    for (int i = 0; i < heightMap.size() - 1; i++) {
        A_x = i ;               
        A_y = heightMap[i];            
        B_x = (i + 1);        
        B_y = heightMap[i + 1];       

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(A_x, A_y);
        modelMatrix *= transform2D::Forfecare( (B_y - A_y) / (B_x - A_x) );
        modelMatrix *= transform2D::Scale(B_x - A_x, std::max(A_y, B_y));

        RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
    }

    // Plasare tancuri de teren si orientare in functie de unghiul terenului
    A_x = (int)(tank1X / step) * step;
    index = (int)(tank1X / step); 
    B_x = A_x + step;
    A_y = heightMap[index];
    B_y = heightMap[index + 1];
    t = (tank1X - A_x) / (B_x - A_x);
    tank1Y = A_y + t * (B_y - A_y);
    angle1 = atan2(B_y - A_y, B_x - A_x);

    A_x = (int)(tank2X / step) * step;
    index = (int)(tank2X / step);
    B_x = A_x + step;
    A_y = heightMap[index];
    B_y = heightMap[index + 1];
    t = (tank2X - A_x) / (B_x - A_x);
    tank2Y = A_y + t * (B_y - A_y);
    angle2 = atan2(B_y - A_y, B_x - A_x);

    if (health1 > 0) {
        CreateTank1(glm::vec3(tank1X, tank1Y, 0), 1.0f, angle1);
    }
    if (health2 > 0) {
        CreateTank2(glm::vec3(tank2X, tank2Y, 0), 1.0f, angle2);
    }
    if (health1 > 0) {
        glm::vec3 vitezaInitiala1 = glm::vec3(300.0f * cos(rotationAngle1 + angle1), 300.0f * sin(rotationAngle1 + angle1), 0);
        CreateTraiectorie(glm::vec3(traiectorieStart1X, traiectorieStart1Y, 0), vitezaInitiala1, 200, 200, 0.1f, heightMap);
    }
    if (health2 > 0) {
        glm::vec3 vitezaInitiala2 = glm::vec3(300.0f * cos(rotationAngle2 + angle2), 300.0f * sin(rotationAngle2 + angle2), 0);
        CreateTraiectorie(glm::vec3(traiectorieStart2X, traiectorieStart2Y, 0), vitezaInitiala2, 200, 200, 0.1f, heightMap);
    }

    if (nor1X < 1350) {
        CreateCloud(glm::vec3(nor1X, nor1Y, 0));
        nor1X += 10 * deltaTimeSeconds;
    }
    else {
        nor1X = -20;
    }
    if (nor2X > -20) {
        CreateCloud(glm::vec3(nor2X, nor2Y, 0));
        nor2X -= 10 * deltaTimeSeconds;
    }
    else {
        nor2X = 1350;
    }
    if (nor3X < 1350) {
        CreateCloud(glm::vec3(nor3X, nor3Y, 0));
        nor3X += 7 * deltaTimeSeconds;
    }
    else {
        nor3X = -20;
    }
    if (nor4X > -20) {
        CreateCloud(glm::vec3(nor4X, nor4Y, 0));
        nor4X -= 15 * deltaTimeSeconds;
    }
    else {
        nor4X = 1350;
    }

    for (int i = proiectile.size() - 1; i >= 0; i--) {
        Proiectil& proiectil = proiectile[i];

        proiectil.pozitie += proiectil.viteza * deltaTimeSeconds;
        proiectil.viteza.y -= 200 * deltaTimeSeconds;

        if ( health1 > 0 && VerifyCollision(proiectil.pozitie, tank1X, tank1Y)) {
            health1--;
            proiectile.erase(proiectile.begin() + i);
        } else if (health2 > 0 && VerifyCollision(proiectil.pozitie, tank2X, tank2Y)) {
            health2--;
            proiectile.erase(proiectile.begin() + i);
        } else if (proiectil.pozitie.y < 0) {
            proiectile.erase(proiectile.begin() + i);
        } else {
            int index = (int)(proiectil.pozitie.x / step);
            if (index > 0 || index < heightMap.size() - 1) {
                float x1 = index * step;
                float y1 = heightMap[index];
                float x2 = (index + 1) * step;
                float y2 = heightMap[index + 1];
                float t = (proiectil.pozitie.x - x1) / (x2 - x1);
                float yI = y1 * (1 - t) + y2 * t;

                if (abs(proiectil.pozitie.y - yI) < pragColiziune) {
                    for (int j = 0; j < heightMap.size(); j++) {
                        float dist = abs(j * step - proiectil.pozitie.x);
                        if (dist < razaColiziune) {
                            float deformare = sqrt(razaColiziune * razaColiziune - dist * dist);
                            heightMap[j] = max(0.0f, min(heightMap[j], yI - deformare));
                        }
                    }
                    proiectile.erase(proiectile.begin() + i);
                }
                RenderMesh2D(meshes["circle"], shaders["VertexColor"], transform2D::Translate(proiectil.pozitie.x, proiectil.pozitie.y));
            }
        }
    }
}

void Tema1::CreateTank1(glm::vec3 position, float scale, float rotation) {
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(position.x, position.y);
    modelMatrix *= transform2D::Rotate(rotation);
    modelMatrix *= transform2D::Scale(scale, scale);

    glm::mat3 Trapezoid1Matrix = modelMatrix;
    Trapezoid1Matrix *= transform2D::Translate(-50, 10);
    RenderMesh2D(meshes["trapezoid11"], shaders["VertexColor"], Trapezoid1Matrix);

    glm::mat3 Trapezoid2Matrix = modelMatrix;
    Trapezoid2Matrix *= transform2D::Translate(-15, 0);
    RenderMesh2D(meshes["trapezoid12"], shaders["VertexColor"], Trapezoid2Matrix);

    glm::mat3 semicircleMatrix = modelMatrix;
    semicircleMatrix *= transform2D::Translate(0, 30);
    RenderMesh2D(meshes["semicircle"], shaders["VertexColor"], semicircleMatrix);

    glm::mat3 TurretMatrix = modelMatrix;
    TurretMatrix *= transform2D::Translate(0, 30); 
    TurretMatrix *= transform2D::Rotate(rotationAngle1);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], TurretMatrix);

    // Calculez pozitia initiala a traiectoriei in functie de matricea turetei 
    // ca sa porneasa din varful ei exterior, din mijlocul latimii
    glm::vec3 start1 = TurretMatrix * glm::vec3(40, 4, 1);
    traiectorieStart1X = start1.x;
    traiectorieStart1Y = start1.y;

    glm::mat3 lifeOutlineMatrix = modelMatrix;
    lifeOutlineMatrix *= transform2D::Translate(-40, 65);
    RenderMesh2D(meshes["rectangleOutline"], shaders["VertexColor"], lifeOutlineMatrix);
    glm::mat3 lifeMatrix = modelMatrix;
    lifeMatrix *= transform2D::Translate(-40, 65);
    lifeMatrix *= transform2D::Scale(health1 / healthMax, 1);
    RenderMesh2D(meshes["rectangleLife"], shaders["VertexColor"], lifeMatrix);

}

void Tema1::CreateTank2(glm::vec3 position, float scale, float rotation) {
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(position.x, position.y);
    modelMatrix *= transform2D::Rotate(rotation);
    modelMatrix *= transform2D::Scale(scale, scale);

    glm::mat3 Trapezoid1Matrix = modelMatrix;
    Trapezoid1Matrix *= transform2D::Translate(-50, 10);
    RenderMesh2D(meshes["trapezoid21"], shaders["VertexColor"], Trapezoid1Matrix);

    glm::mat3 Trapezoid2Matrix = modelMatrix;
    Trapezoid2Matrix *= transform2D::Translate(-15, 0);
    RenderMesh2D(meshes["trapezoid22"], shaders["VertexColor"], Trapezoid2Matrix);

    glm::mat3 semicircleMatrix = modelMatrix;
    semicircleMatrix *= transform2D::Translate(0, 30);
    RenderMesh2D(meshes["semicircle"], shaders["VertexColor"], semicircleMatrix);

    glm::mat3 TurretMatrix = modelMatrix;
    TurretMatrix *= transform2D::Translate(0, 30);
    TurretMatrix *= transform2D::Rotate(rotationAngle2);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], TurretMatrix);

    glm::vec3 start2 = TurretMatrix * glm::vec3(40, 4, 1);
    traiectorieStart2X = start2.x;
    traiectorieStart2Y = start2.y;

    glm::mat3 lifeOutlineMatrix = modelMatrix;
    lifeOutlineMatrix *= transform2D::Translate(-40, 65);
    RenderMesh2D(meshes["rectangleOutline"], shaders["VertexColor"], lifeOutlineMatrix);
    glm::mat3 lifeMatrix = modelMatrix;
    lifeMatrix *= transform2D::Translate(-40, 65);
    lifeMatrix *= transform2D::Scale(health2 / healthMax, 1);
    RenderMesh2D(meshes["rectangleLife"], shaders["VertexColor"], lifeMatrix);
}

void Tema1::CreateTraiectorie(glm::vec3 start, glm::vec3 velocity, float g, int numSegments, float timeStep, std::vector<float> heightMap) {
    glm::vec3 currentPoint = start;

    for (int i = 1; i < numSegments; i++) {
        float t = i * timeStep;
        glm::vec3 nextPoint = start + glm::vec3(velocity.x * t, velocity.y * t - 0.5f * g * t * t, 0);
        CreateLine(currentPoint, nextPoint, glm::vec3(0.0f, 0.0f, 0.0f));
        currentPoint = nextPoint;
    }
}

void Tema1::CreateLine(glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color)
{
    std::vector<VertexFormat> vertices = {
        VertexFormat(startPoint, color),
        VertexFormat(endPoint, color)
    };

    std::vector<unsigned int> indices = { 0, 1 };

    Mesh* line = new Mesh("line");
    line->SetDrawMode(GL_LINES);
    line->InitFromData(vertices, indices);

    RenderMesh2D(line, shaders["VertexColor"], glm::mat3(1));
}

bool Tema1::VerifyCollision(glm::vec3 proiectilPosition, float tankX, float tankY) {
    float dx = proiectilPosition.x - tankX;
    float dy = proiectilPosition.y - tankY;
    float distanta = sqrt(dx * dx + dy * dy);
    // Distanta dintre cele 2 centre ale celor 2 'cercuri' in care 
    // am incadrat tancul si proiectilul sa fie mai mica decat suma razelor
    return distanta < (4 + 40);
}

void Tema1::CreateCloud(glm::vec3 cloudPosition) {
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(cloudPosition.x, cloudPosition.y);

    glm::mat3 circle1 = modelMatrix;
    circle1 *= transform2D::Translate(0, 10);
    RenderMesh2D(meshes["nor1"], shaders["VertexColor"], circle1);

    glm::mat3 circle2 = modelMatrix;
    circle2 *= transform2D::Translate(5, -8);
    RenderMesh2D(meshes["nor2"], shaders["VertexColor"], circle2);

    glm::mat3 circle3 = modelMatrix;
    circle3 *= transform2D::Translate(-14, 2);
    RenderMesh2D(meshes["nor2"], shaders["VertexColor"], circle3);

    glm::mat3 circle4 = modelMatrix;
    circle4 *= transform2D::Translate(-8, -7);
    RenderMesh2D(meshes["nor3"], shaders["VertexColor"], circle4);

    glm::mat3 circle5 = modelMatrix;
    circle5 *= transform2D::Translate(14, 7);
    RenderMesh2D(meshes["nor2"], shaders["VertexColor"], circle5);

    glm::mat3 circle6 = modelMatrix;
    circle6 *= transform2D::Translate(16, -2);
    RenderMesh2D(meshes["nor3"], shaders["VertexColor"], circle6);
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_A)) {
        if (tank1X > 50) {
            tank1X -= 200 * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        if (tank1X <= resolution.x - 50) {
            tank1X += 200 * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_LEFT)) {
        if (tank2X > 50) {
            tank2X -= 200 * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        if (tank2X <= resolution.x - 50) {
            tank2X += 200 * deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_W)) {
        if (rotationAngle1 < M_PI) {
            rotationAngle1 += deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        if (rotationAngle1 > 0) {
            rotationAngle1 -= deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_UP)) {
        if (rotationAngle2 > 0) {
            rotationAngle2 -= deltaTime;
        }
    }

    if (window->KeyHold(GLFW_KEY_DOWN)) {
        if (rotationAngle2 < M_PI) {
            rotationAngle2 += deltaTime;
        }
    }
}

void Tema1::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE) {
        Proiectil nouProiectil;
        nouProiectil.pozitie = glm::vec3(traiectorieStart1X, traiectorieStart1Y, 0);
        nouProiectil.viteza = glm::vec3(300.0f * cos(rotationAngle1 + angle1), 300.0f * sin(rotationAngle1 + angle1), 0);
        proiectile.push_back(nouProiectil);
    }

    if (key == GLFW_KEY_ENTER) {
        Proiectil nouProiectil;
        nouProiectil.pozitie = glm::vec3(traiectorieStart2X, traiectorieStart2Y, 0);
        nouProiectil.viteza = glm::vec3(300.0f * cos(rotationAngle2 + angle2), 300.0f * sin(rotationAngle2 + angle2), 0);
        proiectile.push_back(nouProiectil);
    }
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
