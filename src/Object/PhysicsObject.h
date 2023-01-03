//
// Created by 林士傑 on 2022/12/25.
//

#ifndef AMUSEMENTPARK_PHYSICSOBJECT_H
#define AMUSEMENTPARK_PHYSICSOBJECT_H

#include "Object/Collider/ICollider.h"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"
#include "SFML/System/Time.hpp"
#include <string>

using std::string;

class PhysicsObject {
protected:
    glm::mat4 model_matrix = glm::mat4(1); //for scale, rotation, translation

    string name = "";

    ICollider* collider = nullptr;

    bool lastCollision = false;
    bool Collision = false;

    bool GravityObject = true;

    glm::vec3 lastVelocity = glm::vec3(0);
    glm::vec3 velocity = glm::vec3(0);

public:

    const string &getName() const;

    void setName(const string &name);

    glm::vec3 GetPosition();

    void SettingTransform(glm::vec3 transform);

    void SettingScale(glm::vec3 scale);

    void SettingRotate(glm::vec3 rotate);

    virtual bool IsCollision(PhysicsObject* obj, glm::vec3& collisionVector);

    virtual void nextTick();


    bool isGravityObject() const;

    void SetGravity(bool isGravity);

    const glm::vec3 &getVelocity() const;

    void setVelocity(const glm::vec3 &velocity);

    void addVelocity(const glm::vec3 &velocity);

    const glm::vec3 &getLastVelocity() const;

    void Move(glm::vec3 distance);

    void MoveTo(glm::vec3 position);

    void CleanRotate(glm::vec3 rotate);

    void RotateTo(glm::vec3 rorate);

    void AddForce(glm::vec3 force);



    void UpdatePosition(sf::Time deltaTime);

    void FallDown(sf::Time deltaTime);

};


#endif //AMUSEMENTPARK_PHYSICSOBJECT_H
