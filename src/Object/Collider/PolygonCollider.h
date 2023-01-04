//
// Created by 林士傑 on 2023/1/4.
//

#ifndef AMUSEMENTPARK_POLYGONCOLLIDER_H
#define AMUSEMENTPARK_POLYGONCOLLIDER_H

#include "ICollider.h"
#include "glm/geometric.hpp"
#include "vector"
class gpu_obj_t;


class PolygonCollider : public ICollider {
public:
    class face{
    public:
        glm::vec3 a, b, c;
        face(glm::vec3 a, glm::vec3 b, glm::vec3 c):a(a),b(b),c(c){};
        glm::vec3 distance() const;
    };
    gpu_obj_t* owner = nullptr;
    PolygonCollider();
protected:
    glm::vec3 center = glm::vec3(0);
    std::vector<glm::vec3> vertexes;
    explicit PolygonCollider(gpu_obj_t* owner);

public:

    glm::vec3 getCenter();
    void lookVertex();

    explicit PolygonCollider(gpu_obj_t* owner, const std::vector<glm::vec3> &vertexes);

    bool IsCollision(PolygonCollider *collider, glm::vec3 &collisionVector) override;
private:


    bool gjk(std::vector<glm::vec3>& mink, PolygonCollider *collider);
//    bool gjk(std::vector<std::pair<glm::vec3, glm::vec3>>& mink, PolygonCollider *collider);
    void epa(std::vector<face>& mink, PolygonCollider *collider, glm::vec3 &collisionVector);


    glm::vec3 support(glm::vec3 vec);

    bool IsCollision(ICollider *collider, glm::vec3 &collisionVector) override;

    bool IsCollision(BoxCollider *collider, glm::vec3 &collisionVector) override;

    bool IsCollision(BallCollider *collider, glm::vec3 &collisionVector) override;

//    void SetPosition(glm::vec3 position) override;
//
//    void Translate(glm::vec3 translate) override;
//
//    void Scale(glm::vec3 scale) override;
};


#endif //AMUSEMENTPARK_POLYGONCOLLIDER_H
