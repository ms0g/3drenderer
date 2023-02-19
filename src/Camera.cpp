#include "Camera.h"

Camera::Camera() :
        m_position({0, 0, 0}),
        m_direction({0, 0, 1}),
        m_forwardVelocity({0, 0, 0}),
        m_yaw(0.0) {}

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

void Camera::SetYaw(float yaw) {
    m_yaw = yaw;
}


void Camera::UpdatePosition(const vec3& position) {
    m_position += position;
}


void Camera::UpdateYaw(float angle) {
    m_yaw += angle;
}


void Camera::UpdateForward(const vec3& forward) {
    m_forwardVelocity += forward;
}
