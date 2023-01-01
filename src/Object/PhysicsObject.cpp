//
// Created by 林士傑 on 2022/12/25.
//

#include "PhysicsObject.h"
#include "GameWindow.h"


const string &PhysicsObject::getName() const {
    return name;
}

void PhysicsObject::setName(const string &name) {
    PhysicsObject::name = name;
}

void PhysicsObject::nextTick() {
    lastVelocity = velocity;

    lastCollision = Collision;
    Collision = false;
}

void PhysicsObject::SetGravity(bool isGravity) {
    GravityObject = isGravity;
}

const glm::vec3 &PhysicsObject::getVelocity() const {
    return velocity;
}

const glm::vec3 &PhysicsObject::getLastVelocity() const {
    return lastVelocity;
}

void PhysicsObject::setVelocity(const glm::vec3 &velocity) {
    PhysicsObject::velocity = velocity;
}

void PhysicsObject::addVelocity(const glm::vec3 &velocity) {
    PhysicsObject::velocity += velocity;
}

void PhysicsObject::Move(glm::vec3 distance) {
    this->model_matrix[3][0] += distance[0];
    this->model_matrix[3][1] += distance[1];
    this->model_matrix[3][2] += distance[2];
    if(collider)
        this->collider->Translate(distance);
}

void PhysicsObject::MoveTo(glm::vec3 position) {
    this->model_matrix[3][0] = position[0];
    this->model_matrix[3][1] = position[1];
    this->model_matrix[3][2] = position[2];
}

void PhysicsObject::AddForce(glm::vec3 force) {
    velocity += force;
}

void PhysicsObject::UpdatePosition(sf::Time deltaTime) {
    if(GravityObject){
        Move(velocity * deltaTime.asSeconds());
        float force = 50.0f * deltaTime.asSeconds();
        for(int i = 0; i < 3; i+=2){
            if(velocity[i] > 0){
                if(velocity[i] < force) velocity[i] = 0;
                else velocity[i] -= force;
            }else{
                if(velocity[i] > -force) velocity[i] = 0;
                else velocity[i] += force;
            }
        }
    } else {
        velocity[0] = velocity[1] = velocity[2] = 0;
    }
}

void PhysicsObject::FallDown(sf::Time deltaTime) {
    if(GravityObject)
        velocity += GameWindow::FallDownVector * deltaTime.asSeconds() * (velocity[1] < 0 ? 2.0f : 1.0f);
}

bool PhysicsObject::IsCollision(PhysicsObject* obj, glm::vec3& collisionVector) {
    if(this == obj){
        return false;
    }
    if(this->collider == nullptr || obj->collider == nullptr){
        return false;
    }
    return this->collider->IsCollision(obj->collider, collisionVector);
}


bool PhysicsObject::isGravityObject() const {
    return GravityObject;
}

void PhysicsObject::SettingTransform(glm::vec3 transform) {
    this->model_matrix = glm::translate(model_matrix, transform);
    if(collider)
        collider->Translate(transform);
}

void PhysicsObject::SettingScale(glm::vec3 scale) {
    this->model_matrix = glm::scale(model_matrix, scale);
    if(collider)
        collider->Scale(scale);
}

void PhysicsObject::SettingRotate(glm::vec3 rotate) {
    this->model_matrix = glm::rotate(model_matrix, glm::radians(rotate[0]), glm::vec3(1,0,0));
    this->model_matrix = glm::rotate(model_matrix, glm::radians(rotate[1]), glm::vec3(0,1,0));
    this->model_matrix = glm::rotate(model_matrix, glm::radians(rotate[2]), glm::vec3(0,0,1));
    
    if(collider){
//        collider->Rotate(rotate);
    }
}

glm::vec3 PhysicsObject::GetPosition() {
    return glm::vec3(
            this->model_matrix[3][0],
            this->model_matrix[3][1],
            this->model_matrix[3][2]
            );
}
