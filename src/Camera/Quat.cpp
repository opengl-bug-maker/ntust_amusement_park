//
// Created by 林士傑 on 2022/12/9.
//

#include "Quat.h"

Quat::Quat(float ix, float iy, float iz, float iw)
        :  x(ix), y(iy), z(iz), w(iw) { }

Quat::Quat()
        :  x(0), y(0), z(0), w(1) { }

Quat::Quat(const Quat& q)
        :  x(q.x), y(q.y), z(q.z), w(q.w) { }

void Quat::renorm() {
    float Nq = 1.f / (float) sqrt(x*x + y*y + z*z + w*w);
    x *= Nq;
    y *= Nq;
    z *= Nq;
    w *= Nq;
}

glm::mat4 Quat::toGLMMatrix() const {
    float Nq = x*x + y*y + z*z + w*w;
    float s = (Nq > 0.f) ? (2.0f / Nq) : 0.f;
    float xs = x*s,	      ys = y*s,	  zs = z*s;
    float wx = w*xs,	  wy = w*ys,  wz = w*zs;
    float xx = x*xs,	  xy = x*ys,  xz = x*zs;
    float yy = y*ys,	  yz = y*zs,  zz = z*zs;

    return glm::mat4(
            1.0f - (yy + zz), xy - wz, xz + wy, 0.0f,
            xy + wz, 1.0f - (xx + zz), yz - wx, 0.0f,
            xz - wy, yz + wx, 1.0f - (xx + yy), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
    );
}

Quat Quat::conjugate() const {
    return Quat(-x,-y,-z,w);
}

Quat Quat::operator* (const Quat& qR) const {
    Quat qq;
    qq.w = w*qR.w - x*qR.x - y*qR.y - z*qR.z;
    qq.x = w*qR.x + x*qR.w + y*qR.z - z*qR.y;
    qq.y = w*qR.y + y*qR.w + z*qR.x - x*qR.z;
    qq.z = w*qR.z + z*qR.w + x*qR.y - y*qR.x;
    return (qq);
}
