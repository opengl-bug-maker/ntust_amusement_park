//
// Created by 林士傑 on 2023/1/4.
//

#include "PolygonCollider.h"
#include "gpu_object.h"
#include "iostream"
#include "set"

int r = 0;

std::ostream& operator<<(std::ostream& os, const glm::vec3 & v)
{
//    os << " x : " << v.x << " y : " << v.y << " z : " << v.z;
    os << "(" << v.x << "," << v.y << "," << v.z << ")";
    return os;
}
//ostream& operator<<(ostream& os, const glm::vec3 & vv)
//{
//    os << "(" << vv.x << "," << vv.y << "," << vv.z << ")";
//    return os;
//}
//struct compareVec
//{
//    bool operator() (const glm::vec3& lhs, const glm::vec3& rhs) const
//    {
//        return glm::all(glm::lessThan(lhs, rhs));
//    }
//};

std::ostream& operator<<(std::ostream& os, const std::vector<PolygonCollider::face> & vec)
{
    for(auto v : vec){
        os << v.a << " | ";
        os << v.b << " | ";
        os << v.c << endl;
//        os << "(" << v.a << "," << v.y << "," << v.z << ")" << std::endl;
    }
    os << "diff\n";
    std::vector<glm::vec3> points;
//    set<glm::vec3, compareVec> points;
    for(auto p : vec){
        bool b = true;
        for(auto a : points){
            if(a == p.a){
                b = false;
                break;
            }
        }
        if(b) points.push_back(p.a);
    }
    for(auto p : vec){
        bool b = true;
        for(auto a : points){
            if(a == p.b){
                b = false;
                break;
            }
        }
        if(b) points.push_back(p.b);
    }
    for(auto p : vec){
        bool b = true;
        for(auto a : points){
            if(a == p.c){
                b = false;
                break;
            }
        }
        if(b) points.push_back(p.c);
    }
    for(auto p : points){
        os << p << " " << glm::length(p) << endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<glm::vec3> & vec)
{
    for(auto v : vec){
//        os << " x : " << v.x << " y : " << v.y << " z : " << v.z << std::endl;
        os << "(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<pair<glm::vec3, glm::vec3>> & vec)
{
    for(auto p : vec){
        glm::vec3 v = p.first;
        os << " x : " << v.x << " y : " << v.y << " z : " << v.z << " || ";
        v = p.second;
        os << " x : " << v.x << " y : " << v.y << " z : " << v.z << std::endl;
    }
    return os;
}

glm::vec3 PolygonCollider::face::distance() const {
    glm::vec3 nor = glm::cross(b - a, c - a);
    if(glm::length(nor) == 0.0f) return glm::vec3 (0,0.01,0);
    glm::vec3 normal = glm::normalize(nor);
    if(glm::dot(normal, a) < 0) normal = -normal;
//    cout << "distance\n";
//    cout << a << endl;
//    cout << b << endl;
//    cout << c << endl;
//    cout << normal << endl;
    float mul = glm::dot(normal, a);
    float forceMul = 0.0001;
    if(mul < forceMul) mul = forceMul;
    return normal * mul;
}

PolygonCollider::PolygonCollider() {

}

PolygonCollider::PolygonCollider(gpu_obj_t *owner): owner(owner) {
}

PolygonCollider::PolygonCollider(gpu_obj_t* owner, const std::vector<glm::vec3> &vertexes) : vertexes(vertexes) {
    this->owner = owner;
    for(auto v : vertexes){
        center += v;
    }
    center /= vertexes.size();
}

bool PolygonCollider::IsCollision(ICollider *collider, glm::vec3 &collisionVector) {
    return collider->IsCollision(this, collisionVector);
}

bool PolygonCollider::IsCollision(BoxCollider *collider, glm::vec3 &collisionVector) {
    return ((PolygonCollider*)collider)->IsCollision(this, collisionVector);
}

bool PolygonCollider::IsCollision(BallCollider *collider, glm::vec3 &collisionVector) {
    return false;
}

bool PolygonCollider::IsCollision(PolygonCollider *collider, glm::vec3 &collisionVector) {
//    std::cout << "===========\n";
//    for(auto aa : vertexes){
//        for(auto bb : collider->vertexes){
//            cout << this->owner->GetRootMatrix() * glm::vec4(aa, 1.0f) - collider->owner->GetRootMatrix() * glm::vec4(bb, 1.0f)<< endl;
//        }
//    }
//    std::cout << "===========\n";

    r = 0;
    glm::vec3 start = collider->getCenter() - this->getCenter();
    glm::vec3 thirdStart = glm::cross(start, glm::vec3(0,1,0));
    if(glm::length(thirdStart) == 0.0f) thirdStart = glm::cross(start, glm::vec3(1,0,0));

    //init 3 point
    std::vector<glm::vec3> mink;
    mink.push_back(this->support(start) - collider->support(-start));
    mink.push_back(this->support(-start) - collider->support(start));
    mink.push_back(this->support(thirdStart) - collider->support(-thirdStart));
//    std::vector<pair<glm::vec3, glm::vec3>> mink;
//    mink.push_back(make_pair(this->support(start),collider->support(-start)));
//    mink.push_back(make_pair(this->support(-start),collider->support(start)));
//    mink.push_back(make_pair(this->support(thirdStart),collider->support(-thirdStart)));

//    std::cout << "this center : " << this->center << std::endl;
//    std::cout << "collider center : " << collider->center << std::endl;
//    std::cout << "start : " << start << std::endl;
//    std::cout << "thirdStart : " << thirdStart << std::endl;
//    std::cout << "support : " << this->support(start) << std::endl;
//    std::cout << "mink : " << mink << std::endl;
    bool g = gjk(mink, collider);
    if(g){
        std::vector<face> faces = {
                face(mink[0], mink[1], mink[2]),
                face(mink[1], mink[2], mink[3]),
                face(mink[2], mink[3], mink[0]),
                face(mink[3], mink[0], mink[1])
        };
        r = 0;
        epa(faces, collider, collisionVector);
        return true;
    }else{
        return false;
    }

//    return gjk(mink, collider);
}

glm::vec3 PolygonCollider::getCenter() {
    glm::vec3 cen = owner->GetRootMatrix() * glm::vec4(this->center, 1.0f);
    return cen;
}

glm::vec3 PolygonCollider::support(glm::vec3 vec) {
    if(vertexes.empty()) return glm::vec3 (0);
    gpu_obj_t* wee = owner;
    std::vector<glm::vec3> copyVer;
    for(auto v : vertexes){
        copyVer.emplace_back(wee->GetRootMatrix() * glm::vec4(v, 1.0f));
    }


    auto biggest = std::max_element(copyVer.begin(), copyVer.end(),
                                    [&vec](glm::vec3 const& a, glm::vec3 const& b){
        return glm::dot(vec, a) < glm::dot(vec, b);
    });
//    std::cout << "supp : " << vec << std::endl;
//    for(auto ve : vertexes){
//        std::cout << glm::dot(vec, ve) << " : " << ve << std::endl;
//    }
//    std::cout << "big : " << *biggest << std::endl << std::endl;

//    return vertexes[index];

    return *biggest;
}

bool PolygonCollider::gjk(std::vector<glm::vec3> &mink, PolygonCollider *collider) {
    r++;
    if(r > 15){
//        std::cout << "too long\n";
        return false;
    }
    //find new point
    glm::vec3 next = glm::cross(mink[1] - mink[0], mink[2] - mink[0]);
    if(glm::dot(next, mink[0]) > 0) next = -next;
//    std::cout << "next : " << next << std::endl;
//    std::cout << "ori point : " << mink << std::endl;
    mink.push_back(this->support(next) - collider->support(-next));
//    std::cout << "new point : " << mink << std::endl;

    glm::vec3 bad = glm::cross(mink[1] - mink[0], mink[3] - mink[0]);
//    std::cout << "check bad : " << next << endl;
//    std::cout << "check bad : " << bad << endl;

//    if(glm::length(glm::cross(next, mink[3] - mink[0])) == 0.0f){
    if(glm::length(glm::cross(next, bad)) == 0.0f){
        //bad point
//        std::cout << "bad!!!!" << std::endl;
        mink.pop_back();
        return false;
    }

    //check origin in 3d triangle
    int inTriangle[4] = {0, 0, 0, 0};
    int InSum = 0;
    int eraseIndex = 0;
    glm::vec3 checkVec, checkOrigin, checkTrd;
    for(int i = 0; i < 4; i++){
//        std::cout << "check" << i << endl;
        checkVec = glm::cross(mink[(i + 1) % 4] - mink[i], mink[(i + 2) % 4] - mink[i]);
//        cout << "fir: " << mink[(i + 1) % 4] - mink[i] << " sec: " << mink[(i + 2) % 4] - mink[i] << endl;
        checkOrigin = mink[i];
        checkTrd = mink[i] - mink[(i + 3) % 4];
//        checkTrd = mink[(i + 3) % 4] - mink[i];
//        std::cout << "vec : " << checkVec << endl;
//        std::cout << "ori : " << checkOrigin << endl;
//        std::cout << "trd : " << checkTrd << endl;
//        std::cout << glm::dot(checkVec, checkOrigin)  << " " << glm::dot(checkVec, checkTrd) << endl;
        if(glm::dot(checkVec, checkOrigin) * glm::dot(checkVec, checkTrd) < 0){
            inTriangle[i] = 1;
            InSum++;
            eraseIndex = (i + 3) % 4;
        }
    }

    if(InSum == 0){
        //hurray
//        std::cout << "hurray!!!!" << std::endl;
        return true;
    }
    else if(InSum > 1){
//        //no chance
//        std::cout << "no chance!!!!" << std::endl;
//        for(auto a : inTriangle){
//            std::cout << a << " ";
//        }
//        std::cout << "\n";
//        return false;

//        std::cout << "next round!!!!" << std::endl;
        auto farest = std::max_element(mink.begin(), mink.end(),[](const glm::vec3& a, const glm::vec3& b){
            return glm::length(a) < glm::length(b);
        });
        mink.erase(farest);
        return gjk(mink, collider);
    }
//    std::cout << "next round!!!!" << std::endl;
//    auto farest = std::max_element(mink.begin(), mink.end(),[](const glm::vec3& a, const glm::vec3& b){
//        return glm::length(a) < glm::length(b);
//    });
//    std::cout << "erase one!!" << eraseIndex << std::endl;
    mink.erase(mink.begin() + eraseIndex);
//    mink.erase(farest);
    return gjk(mink, collider);
//    return gjk(minkk, collider);
}

void PolygonCollider::epa(vector<face> &faces, PolygonCollider *collider, glm::vec3 &collisionVector) {
    r++;
    if(r > 20) return;
    auto min = std::min_element(faces.begin(), faces.end(),[](const face& a, const face& b){
        return glm::length(a.distance()) < glm::length(b.distance());
    });
    glm::vec3 nor = min->distance();
    glm::vec3 newPoint = this->support(nor) - collider->support(-nor);

    glm::vec3 samePlane = glm::cross(newPoint - min->a, min->c - min->a);
//    if(nor[0] != 0){
//        std::cout << "faces : " << faces;
//        std::cout << "nor : " << nor << endl;
//        std::cout << "newPoint : " << newPoint << endl;
//    }
//    std::cout << "aaaaa : " << endl;
    if(glm::length(glm::cross(nor, samePlane)) == 0.0f){
        //good
        collisionVector = nor;
        if(nor[1] < -3){
            float mi = 3;
            for(auto a : faces){
                if(abs(a.a[1]) < abs(mi)){
                    mi = a.a[1];
                }
                if(abs(a.b[1]) < abs(mi)){
                    mi = a.b[1];
                }
                if(abs(a.c[1]) < abs(mi)){
                    mi = a.c[1];
                }
            }
            collisionVector[1] = mi;
//            std::cout << "faces : " << faces;
//            std::cout << "min : \n" << min->a << endl;
//            std::cout << min->b << endl;
//            std::cout << min->c << endl;
//            std::cout << "nor : " << nor << endl;
//            std::cout << "newPoint : " << newPoint << endl;
//            cout << "======== result : " << collisionVector << endl;
        }
        return;
    }
    faces.erase(min);
    faces.emplace_back(newPoint, min->a, min->b);
    faces.emplace_back(newPoint, min->b, min->c);
    faces.emplace_back(newPoint, min->c, min->a);
    epa(faces, collider, collisionVector);
}


void PolygonCollider::lookVertex() {
    if(owner == nullptr){
        cout << "look null\n";
        return;
    }
    gpu_obj_t* wee = owner;
    std::vector<glm::vec3> copyVer;
    std::cout << "look\n";
    for(auto v : vertexes){
        copyVer.emplace_back(wee->GetRootMatrix() * glm::vec4(v, 1.0f));
//        std::cout << wee->GetRootMatrix() * glm::vec4(v, 1.0f) << std::endl;
    }
}
