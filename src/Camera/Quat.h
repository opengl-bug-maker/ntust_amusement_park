//
// Created by 林士傑 on 2022/12/9.
//

#ifndef AMUSEMENTPARK_QUAT_H
#define AMUSEMENTPARK_QUAT_H

#include "glm/glm.hpp"

class Quat {
public:
    enum QuatPart {X=0, Y=1, Z=2, W=3, QuatLen};

public:
    Quat();						/* gives the identity */
    Quat(float x, float y, float z, float w);
    Quat(const Quat&);			/* copy constructor */

public:
    // conversions
    glm::mat4 toGLMMatrix() const;

    // operations
    Quat conjugate() const;
    // make multiply look like multiply
    Quat operator* (const Quat&) const;
    // Normalize the quaternion back to length 1
    void renorm();

public:
    // the data
    float x, y, z, w;
};


#endif //AMUSEMENTPARK_QUAT_H
