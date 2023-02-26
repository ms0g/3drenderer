#include "Camera.h"
#include "Mat4.h"
#include "Vec4.h"

Camera::Camera() :
        m_position({0, 0, 0}),
        m_direction({0, 0, 1}),
        m_forwardVelocity({0, 0, 0}),
        m_yaw(0.0),
        m_pitch(0.0) {}

vec3 Camera::GetLookAtTarget() {
    // Initialize the target positive z-axis
    vec3 target = {0, 0, 1};

    mat4 cameraYawRotation = mat4::RotationMatrixY(m_yaw);
    mat4 cameraPitchRotation = mat4::RotationMatrixX(m_pitch);

    // Create camera rotation matrix based on yaw and pitch
    mat4 cameraRotation = mat4::IdentityMatrix();
    cameraRotation = cameraPitchRotation * cameraRotation;
    cameraRotation = cameraYawRotation * cameraRotation;

    m_direction = vec3::FromVec4(cameraRotation * vec4::FromVec3(target));

    // Offset the camera position in the direction where the camera is pointing at
    target = m_position + m_direction;
    return target;
}

vec3 Camera::GetOrigin() {
    return {0, 0, 0};
}


const vec3& Camera::GetPosition() const {
    return m_position;
}


void Camera::SetPosition(const vec3& position) {
    m_position = position;
}


const vec3& Camera::GetDirection() const {
    return m_direction;
}


void Camera::SetDirection(const vec3& direction) {
    m_direction = direction;
}


const vec3& Camera::GetForwardVelocity() const {
    return m_forwardVelocity;
}


void Camera::SetForwardVelocity(const vec3& fwv) {
    m_forwardVelocity = fwv;
}


float Camera::GetYaw() const {
    return m_yaw;
}


void Camera::SetYaw(float angle) {
    m_yaw = angle;
}


void Camera::UpdateYaw(float angle) {
    m_yaw += angle;
}


float Camera::GetPitch() const {
    return m_pitch;
}

void Camera::SetPitch(float angle) {
    m_pitch = angle;
}


void Camera::UpdatePitch(float angle) {
    m_pitch += angle;
}


void Camera::UpdatePosition(const vec3& position) {
    m_position += position;
}


void Camera::UpdateForward(const vec3& forward) {
    m_forwardVelocity += forward;
}

