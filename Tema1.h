#pragma once
#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

		void CreateTank1(glm::vec3 position, float scale, float rotation);
        void CreateTank2(glm::vec3 position, float scale, float rotation);
        void CreateTraiectorie(glm::vec3 start, glm::vec3 velocity, float g, int numSegments, float timeStep, std::vector<float> heightMap);
        void CreateLine(glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color);
        bool VerifyCollision(glm::vec3 position, float tankX, float tankY);
        void CreateCloud(glm::vec3 position);

    protected:
        glm::ivec2 resolution;
        glm::mat3 modelMatrix;
        float A_x, A_y, B_x, B_y, t;
        int index;
        float step = 1.0f;
        std::vector<float> heightMap;
        float tank1X = 270, tank1Y;
        float rotationAngle1 = M_PI / 6, angle1;
        float tank2X = 990, tank2Y;
        float rotationAngle2 = M_PI / 6 * 5 ,angle2;
        glm::vec3 proiectilPosition, proiectilDeplasare;
        float traiectorieStart1X, traiectorieStart1Y, traiectorieStart2X, traiectorieStart2Y;
        struct Proiectil {glm::vec3 pozitie; glm::vec3 viteza; };
        std::vector<Proiectil> proiectile;
        float health1 = 5.0f, health2 = 5.0f, healthMax = 5.0f;
        float razaColiziune = 30.0f, pragColiziune = 10.0f;
        float nor1X = 50, nor1Y = 600, nor2X = 1200, nor2Y = 550, nor3X = 150, nor3Y = 500, nor4X = 1250, nor4Y = 680;
    };
}