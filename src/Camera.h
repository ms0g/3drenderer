#pragma once

#include "Vec3.h"


class Camera {
public:
    Camera();

    vec3 GetLookAtTarget();

    vec3 GetOrigin();

    [[nodiscard]] const vec3& GetPosition() const;

    void SetPosition(const vec3& position);

    [[nodiscard]] const vec3& GetDirection() const;

    void SetDirection(const vec3& direction);

    [[nodiscard]] const vec3& GetForwardVelocity() const;

    void SetForwardVelocity(const vec3& fwv);

    [[nodiscard]] float GetYaw() const;

    void SetYaw(float angle);

    void UpdateYaw(float angle);

    [[nodiscard]] float GetPitch() const;

    void SetPitch(float angle);

    void UpdatePitch(float angle);

    void UpdatePosition(const vec3& position);

    void UpdateForward(const vec3& forward);

private:
    vec3 m_position;
    vec3 m_direction;
    vec3 m_forwardVelocity;
    float m_yaw;
    float m_pitch;
};
