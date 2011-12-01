/*!
   @file   CamtransCamera.cpp
   @author Ben Herila (ben@herila.net)
   @author Evan Wallace (evan.exe@gmail.com)
   @date   Fall 2010

   @brief  This is the perspective camera class you will need to fill in for the
   Camtrans assignment.  See the assignment handout for more details.

   For extra credit, you can also create an Orthographic camera. Create another
   class if you want to do that.

*/

#include "CamtransCamera.h"
#include <Settings.h>
#include <qgl.h>

CamtransCamera::CamtransCamera()
{
    m_u = Vector4(1, 0, 0, 0);
    m_v = Vector4(0, 1, 0, 0);
    m_w = Vector4(0, 0, 1, 0);
    m_pos = Vector4(0, 0, 2, 0);

    updateMatrices();
}

void CamtransCamera::setAspectRatio(float a)
{
    m_aspectRatio = a;
    updateProjectionMatrix();
}

Matrix4x4 CamtransCamera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}

Matrix4x4 CamtransCamera::getModelviewMatrix() const
{
    return m_modelViewMatrix;
}

Vector4 CamtransCamera::getPosition() const
{
    return m_pos;
}

Vector4 CamtransCamera::getLook() const
{
    return -m_w;
}

Vector4 CamtransCamera::getUp() const
{
    return m_v;
}

float CamtransCamera::getAspectRatio() const
{
    return m_aspectRatio;
}

void CamtransCamera::setHeightAngle(float h)
{
    m_heightAngle = h;
    updateProjectionMatrix();
}

float CamtransCamera::getHeightAngle() const
{
    return m_heightAngle;
}

void CamtransCamera::orientLook(const Vector4 &eye, const Vector4 &look, const Vector4 &up)
{
    m_pos = eye;

    m_w = -look.getNormalized();
    Vector4 r = up.cross(look);
    m_u = -r.getNormalized();

    m_v = m_w.cross(m_u);
    updateModelviewMatrix();
}

void CamtransCamera::translate(const Vector4 &v)
{
    m_pos = m_pos + v;

    updateModelviewMatrix();
}

void CamtransCamera::rotateU(float degrees)
{
    Matrix4x4 r = getRotMat(Vector4::zero(), m_u, -degrees * M_PI / 180);

    m_v = r * m_v;
    m_w = r * m_w;

    updateModelviewMatrix();
}

void CamtransCamera::rotateV(float degrees)
{
    Matrix4x4 r = getRotMat(Vector4::zero(), m_v, degrees * M_PI / 180);

    m_u = r * m_u;
    m_w = r * m_w;

    updateModelviewMatrix();
}

void CamtransCamera::rotateN(float degrees)
{
    Matrix4x4 r = getRotMat(Vector4::zero(), m_w, degrees * M_PI / 180);

    m_u = r * m_u;
    m_v = r * m_v;

    updateModelviewMatrix();
}

void CamtransCamera::setClip(float nearPlane, float farPlane)
{
    m_near = nearPlane;
    m_far = farPlane;

    updateProjectionMatrix();
}

void CamtransCamera::updateProjectionMatrix() {
    // Mpp (unhinging)
    float c = -m_near / m_far;
    REAL arrMpp[16] = {1, 0, 0, 0,
                       0, 1, 0, 0,
                       0, 0, -1.f / (c + 1), c / (c + 1),
                       0, 0, -1, 0};

    Matrix4x4 mpp = Matrix4x4(arrMpp);

    float height = tan(m_heightAngle * M_PI / 360) * m_far;
    float width  = height * m_aspectRatio;

    Vector4 vs = Vector4(1.f / width, 1.f / height, 1.f / m_far, 1.f);
    Matrix4x4 s = getScaleMat(vs);

    m_projectionMatrix = mpp * s;
}

void CamtransCamera::updateModelviewMatrix()
{
    REAL uvwArr[16] = {m_u.x, m_u.y, m_u.z, 0,
                       m_v.x, m_v.y, m_v.z, 0,
                       m_w.x, m_w.y, m_w.z, 0,
                       0, 0, 0, 1};

    Matrix4x4 uvw = Matrix4x4(uvwArr);

    m_modelViewMatrix = uvw * getInvTransMat(m_pos);
}

Matrix4x4 CamtransCamera::getFilmToWorldMatrix() {
    REAL uvwArr[16] = {m_u.x, m_u.y, m_u.z, 0,
                       m_v.x, m_v.y, m_v.z, 0,
                       m_w.x, m_w.y, m_w.z, 0,
                       0, 0, 0, 1};

    float height = tan(m_heightAngle * M_PI / 360) * m_far;
    float width  = height * m_aspectRatio;

    Vector4 vs = Vector4(1.f / width, 1.f / height, 1.f / m_far, 1.f);
    Matrix4x4 s = getScaleMat(vs);

    return (s * Matrix4x4(uvwArr) * getInvTransMat(m_pos)).getInverse();
}

void CamtransCamera::updateMatrices() {
    updateProjectionMatrix();
    updateModelviewMatrix();
}
