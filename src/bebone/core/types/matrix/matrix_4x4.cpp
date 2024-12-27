#include "matrix_4x4.h"

namespace bebone::core {
    Matrix<f32, 4, 4>::Matrix(const f32& n00, const f32& n01, const f32& n02, const f32& n03,
                              const f32& n10, const f32& n11, const f32& n12, const f32& n13,
                              const f32& n20, const f32& n21, const f32& n22, const f32& n23,
                              const f32& n30, const f32& n31, const f32& n32, const f32& n33) {
        e[0][0] = n00; e[0][1] = n10; e[0][2] = n20; e[0][3] = n30;
        e[1][0] = n01; e[1][1] = n11; e[1][2] = n21; e[1][3] = n31;
        e[2][0] = n02; e[2][1] = n12; e[2][2] = n22; e[2][3] = n32;
        e[3][0] = n03; e[3][1] = n13; e[3][2] = n23; e[3][3] = n33;
    }

    Matrix<f32, 4, 4>::Matrix(const Vec4f &a, const Vec4f &b, const Vec4f &c, const Vec4f& d) {
        e[0][0] = a.x; e[0][1] = a.y; e[0][2] = a.z; e[0][3] = a.w;
        e[1][0] = b.x; e[1][1] = b.y; e[1][2] = b.z; e[1][3] = b.w;
        e[2][0] = c.x; e[2][1] = c.y; e[2][2] = c.z; e[2][3] = c.w;
        e[3][0] = d.x; e[3][1] = d.y; e[3][2] = d.z; e[3][3] = c.w;
    }

    const f32* Matrix<f32, 4, 4>::get_raw() const {
        return &e[0][0];
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_rotation_x(const f32& angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  c,   -s,   0.0f,
            0.0f,  s,    c,   0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_rotation_y(const f32& angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
             c,   0.0f,  s,   0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -s,   0.0f,  c,   0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_rotation_z(const f32& angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
             c,   -s,   0.0f, 0.0f,
             s,    c,   0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_rotation_matrix(const f32& angle, Vec3f axis) {
        axis = axis.normalize();

        f32 c = std::cos(angle);
        f32 s = std::sin(angle);
        f32 d = 1.0f - c;

        f32 x = axis.x * d;
        f32 y = axis.y * d;
        f32 z = axis.z * d;

        f32 axay = x * axis.y;
        f32 axaz = x * axis.z;
        f32 ayaz = y * axis.z;

        return {
             c + x * axis.x,   axay - s * axis.z, axaz + s * axis.y, 0.0f,
            axay + s * axis.z,   c + y * axis.y,  ayaz - s * axis.x, 0.0f,
            axaz - s * axis.y, ayaz + s * axis.x,   c + z * axis.z,  0.0f,
                 0.0f,               0.0f,              0.0f,        1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_reflection_matrix(const Vec3f& v) {
        f32 x = v.x * -2.0f;
        f32 y = v.y * -2.0f;
        f32 z = v.z * -2.0f;
        f32 vxvy = x * v.y;
        f32 vxvz = x * v.z;
        f32 vyvz = y * v.z;

        return {
            x * v.x + 1.0f,     vxvy,           vxvz,      0.0f,
                vxvy,      y * v.y + 1.0f,      vyvz,      0.0f,
                vxvz,           vyvz,      z * v.z + 1.0f, 0.0f,
                0.0f,           0.0f,           0.0f,      1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_involution_matrix(const Vec3f& v) {
        f32 x = v.x * -2.0f;
        f32 y = v.y * -2.0f;
        f32 z = v.z * -2.0f;
        f32 vxvy = x * v.y;
        f32 vxvz = x * v.z;
        f32 vyvz = y * v.z;

        return {
            x * v.x - 1.0f,     vxvy,           vxvz,      0.0f,
                vxvy,      y * v.y - 1.0f,      vyvz,      0.0f,
                vxvz,           vyvz,      z * v.z - 1.0f, 0.0f,
                0.0f,           0.0f,           0.0f,      1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::skew(f32 t, Vec3f a, Vec3f b) {
        t = std::tan(t);
        a = a.normalize();
        b = b.normalize();

        f32 x = a.x * t;
        f32 y = a.y * t;
        f32 z = a.z * t;

        return {
            x * b.x + 1.0f,     x * b.y,       x * b.z,     0.0f,
               y * b.x,     y * b.y + 1.0f,    y * b.z,     0.0f,
               z * b.x,         z * b.y,    z * b.z + 1.0f, 0.0f,
                 0.0f,           0.0f,           0.0f,      1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::scale(const f32& s) {
        return {
             s,   0.0f, 0.0f, 0.0f,
            0.0f,  s,   0.0f, 0.0f,
            0.0f, 0.0f,  s,   0.0f,
            0.0f, 0.0f, 0.0f,  1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::scale(const f32& sx, const f32& sy, const f32& sz) {
        return {
             sx,  0.0f, 0.0f, 0.0f,
            0.0f,  sy,  0.0f, 0.0f,
            0.0f, 0.0f,  sz,  0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::scale(const Vec3f& s) {
        return {
            s.x,  0.0f, 0.0f, 0.0f,
            0.0f, s.y,  0.0f, 0.0f,
            0.0f, 0.0f, s.z,  0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::scale(f32 s, Vec3f v) {
        v = v.normalize();
        s -= 1.0f;

        f32 x = v.x * s;
        f32 y = v.y * s;
        f32 z = v.z * s;
        f32 vxvy = x * v.y;
        f32 vxvz = x * v.z;
        f32 vyvz = y * v.z;

        return {
            x * v.x + 1.0f,      vxvy,           vxvz,      0.0f,
                 vxvy,      y * v.y + 1.0f,      vyvz,      0.0f,
                 vxvz,           vyvz,      z * v.z + 1.0f, 0.0f,
                 0.0f,           0.0f,           0.0f,      1.0f
        };
    }

    std::string Matrix<f32, 4, 4>::to_string() const {
        std::stringstream ss;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ss << (*this)(i, j) << " ";
            }

            ss << std::endl;
        }

        return ss.str();
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::translation(const f32& tx, const f32& ty, const f32& tz) {
        return {
            1.0f, 0.0f, 0.0f, tx,
            0.0f, 1.0f, 0.0f, ty,
            0.0f, 0.0f, 1.0f, tz,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::translation(const Vec3f& t) {
        return {
            1.0f, 0.0f, 0.0f, t.x,
            0.0f, 1.0f, 0.0f, t.y,
            0.0f, 0.0f, 1.0f, t.z,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::orthographic(const f32& right, const f32& left, const f32& bottom, const f32& top, const f32& near, const f32& far) {
        return {
                2.0f / (right - left),        0.0f,                  0.0f,         -(right + left) / (right - left),
                       0.0f,           2.0f / (bottom - top),        0.0f,         -(bottom + top) / (top - bottom),
                       0.0f,                  0.0f,           2.0f / (far - near),   -(far + near) / (far - near),
                       0.0f,                  0.0f,                  0.0f,                        1.0f
        };
    }

    /*
    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::perspective(f32 fov, const f32& aspect, const f32& near, const f32& far) {
        fov = 1.0f / std::tan(fov / 2.0f);
        f32 normalization = far / (far - near);

        return {
            1.0f / aspect * fov,   0.0f,       0.0f,               0.0f,
                  0.0f,            -fov,       0.0f,               0.0f,
                  0.0f,            0.0f,   normalization,  -normalization * near,
                  0.0f,            0.0f,       1.0f,               0.0f
        };
    }
    */

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::perspective
    (
            f32 fovy,
            const f32 & aspect,
            const f32 & zNear,
            const f32 & zFar
    )
    {
        f32 const rad = fovy;
        f32 const tanHalfFovy = tan(rad / static_cast<f32>(2));

        auto Result = Matrix<f32, 4, 4>::splat(0);
        Result.e[0][0] = static_cast<f32>(1) / (aspect * tanHalfFovy);
        Result.e[1][1] = static_cast<f32>(1) / (tanHalfFovy);
        Result.e[2][2] = - (zFar + zNear) / (zFar - zNear);
        Result.e[2][3] = - static_cast<f32>(1);
        Result.e[3][2] = - (static_cast<f32>(2) * zFar * zNear) / (zFar - zNear);
        return Result;
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::view(const Vec3f& origin, const Vec3f& direction, const Vec3f& up) {
        Vec3f zaxis = direction.normalize();
        Vec3f xaxis = Vec3f::cross(up, zaxis).normalize();
        Vec3f yaxis = Vec3f::cross(zaxis, xaxis);

        return {
            xaxis.x, xaxis.y, xaxis.z, -Vec3f::dot(xaxis, origin),
            yaxis.x, yaxis.y, yaxis.z, -Vec3f::dot(yaxis, origin),
            zaxis.x, zaxis.y, zaxis.z, -Vec3f::dot(zaxis, origin),
             0.0f,     0.0f,    0.0f,             1.0f
        };
    }

#if 1
    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::look_at
    (
            Vec3f const & eye,
            Vec3f const & center,
            Vec3f const & up
    )
{
    Vec3f const f((center - eye).normalize());
    Vec3f const s(Vec3f::cross(f, up).normalize());
    Vec3f const u(Vec3f::cross(s, f));

    auto Result = Matrix<f32, 4, 4>::identity();
    Result.e[0][0] = s.x;
    Result.e[1][0] = s.y;
    Result.e[2][0] = s.z;
    Result.e[0][1] = u.x;
    Result.e[1][1] = u.y;
    Result.e[2][1] = u.z;
    Result.e[0][2] =-f.x;
    Result.e[1][2] =-f.y;
    Result.e[2][2] =-f.z;
    Result.e[3][0] = - Vec3f::dot(s, eye);
    Result.e[3][1] = - Vec3f::dot(u, eye);
    Result.e[3][2] =   Vec3f::dot(f, eye);
    return Result;
}
#else
    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::look_at(const Vec3f& origin, const Vec3f& center, const Vec3f& up) {
        return view(origin, center - origin, up);
    }
#endif
}