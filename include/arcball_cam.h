#ifndef ARCBALL_H
#define ARCBALL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

class ArcballCamera
{
public:
    ArcballCamera(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {}

    bool onCam = false;
    glm::quat currentOrientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::quat lastOrientation;

    glm::vec3 getArcballVector(double x, double y)
    {
        glm::vec3 P = glm::vec3(
            (x / screenWidth * 2) - 1.0,
            (y / screenHeight * 2) - 1.0,
            0);

        P.y = -P.y;

        float op_squared = P.x * P.x + P.y * P.y;

        if (op_squared < 1.0f)
        {
            P.z = sqrt(1.0 - op_squared);
        }
        else
        {
            P = glm::normalize(P);
        }

        return P;
    }

    inline float getAngle(glm::vec3 va, glm::vec3 vb)
    {
        return acos(glm::min(1.0f, glm::dot(va, vb)));
    }

    inline glm::vec3 getAxis(glm::vec3 va, glm::vec3 vb)
    {
        return glm::cross(va, vb);
    }

    inline glm::quat getDeltaRotation(glm::vec3 va, glm::vec3 vb)
    {
        return glm::angleAxis(getAngle(va, vb), glm::normalize(getAxis(va, vb)));
    }

    inline glm::mat4 getRotationMatrix()
    {
        return glm::mat4_cast(currentOrientation);
    }

    inline void replace()
    {
        lastOrientation = currentOrientation;
    }

private:
    int screenWidth, screenHeight;
};

#endif