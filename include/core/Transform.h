#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "core/Component.h"

namespace Nimbus {

    class GameObject;

    /**
     * @brief Transform component for position, rotation, and scale
     * 
     * The Transform component is automatically added to every GameObject and
     * cannot be removed. It handles the position, rotation, and scale of
     * GameObjects in 3D space, including parent-child transformations.
     */
    class Transform : public Component {
    public:
        /**
         * @brief Constructor
         */
        Transform();

        /**
         * @brief Destructor
         */
        ~Transform() override = default;

        // Component type
        NIMBUS_COMPONENT_TYPE(Transform)
        NIMBUS_COMPONENT_CLONE(Transform)

        // Position
        /**
         * @brief Get the local position
         * @return Local position vector
         */
        const glm::vec3& GetLocalPosition() const { return m_localPosition; }

        /**
         * @brief Set the local position
         * @param position New local position
         */
        void SetLocalPosition(const glm::vec3& position);

        /**
         * @brief Get the world position
         * @return World position vector
         */
        glm::vec3 GetWorldPosition() const;

        /**
         * @brief Set the world position
         * @param position New world position
         */
        void SetWorldPosition(const glm::vec3& position);

        /**
         * @brief Translate the transform
         * @param translation Translation vector
         */
        void Translate(const glm::vec3& translation);

        // Rotation
        /**
         * @brief Get the local rotation as euler angles
         * @return Local rotation in degrees
         */
        glm::vec3 GetLocalRotation() const;

        /**
         * @brief Set the local rotation as euler angles
         * @param rotation New local rotation in degrees
         */
        void SetLocalRotation(const glm::vec3& rotation);

        /**
         * @brief Get the local rotation as quaternion
         * @return Local rotation quaternion
         */
        const glm::quat& GetLocalRotationQuat() const { return m_localRotation; }

        /**
         * @brief Set the local rotation as quaternion
         * @param rotation New local rotation quaternion
         */
        void SetLocalRotationQuat(const glm::quat& rotation);

        /**
         * @brief Get the world rotation as euler angles
         * @return World rotation in degrees
         */
        glm::vec3 GetWorldRotation() const;

        /**
         * @brief Set the world rotation as euler angles
         * @param rotation New world rotation in degrees
         */
        void SetWorldRotation(const glm::vec3& rotation);

        /**
         * @brief Get the world rotation as quaternion
         * @return World rotation quaternion
         */
        glm::quat GetWorldRotationQuat() const;

        /**
         * @brief Set the world rotation as quaternion
         * @param rotation New world rotation quaternion
         */
        void SetWorldRotationQuat(const glm::quat& rotation);

        /**
         * @brief Rotate around an axis
         * @param angle Angle in degrees
         * @param axis Rotation axis
         */
        void Rotate(float angle, const glm::vec3& axis);

        /**
         * @brief Rotate around the X axis
         * @param angle Angle in degrees
         */
        void RotateX(float angle);

        /**
         * @brief Rotate around the Y axis
         * @param angle Angle in degrees
         */
        void RotateY(float angle);

        /**
         * @brief Rotate around the Z axis
         * @param angle Angle in degrees
         */
        void RotateZ(float angle);

        // Scale
        /**
         * @brief Get the local scale
         * @return Local scale vector
         */
        const glm::vec3& GetLocalScale() const { return m_localScale; }

        /**
         * @brief Set the local scale
         * @param scale New local scale
         */
        void SetLocalScale(const glm::vec3& scale);

        /**
         * @brief Get the world scale
         * @return World scale vector
         */
        glm::vec3 GetWorldScale() const;

        /**
         * @brief Set the world scale
         * @param scale New world scale
         */
        void SetWorldScale(const glm::vec3& scale);

        /**
         * @brief Scale the transform
         * @param scale Scale vector
         */
        void Scale(const glm::vec3& scale);

        // Transform matrices
        /**
         * @brief Get the local transform matrix
         * @return Local transform matrix
         */
        const glm::mat4& GetLocalMatrix() const { return m_localMatrix; }

        /**
         * @brief Get the world transform matrix
         * @return World transform matrix
         */
        const glm::mat4& GetWorldMatrix() const { return m_worldMatrix; }

        /**
         * @brief Get the inverse world transform matrix
         * @return Inverse world transform matrix
         */
        glm::mat4 GetInverseWorldMatrix() const;

        // Direction vectors
        /**
         * @brief Get the forward direction vector
         * @return Forward direction
         */
        glm::vec3 GetForward() const;

        /**
         * @brief Get the right direction vector
         * @return Right direction
         */
        glm::vec3 GetRight() const;

        /**
         * @brief Get the up direction vector
         * @return Up direction
         */
        glm::vec3 GetUp() const;

        /**
         * @brief Set the forward direction
         * @param forward New forward direction
         */
        void SetForward(const glm::vec3& forward);

        /**
         * @brief Set the right direction
         * @param right New right direction
         */
        void SetRight(const glm::vec3& right);

        /**
         * @brief Set the up direction
         * @param up New up direction
         */
        void SetUp(const glm::vec3& up);

        // Look at
        /**
         * @brief Make the transform look at a target
         * @param target Target position
         * @param up Up direction
         */
        void LookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0, 1, 0));

        // Parent-child relationships
        /**
         * @brief Get the parent transform
         * @return Pointer to the parent transform
         */
        Transform* GetParent() const { return m_parent; }

        /**
         * @brief Set the parent transform
         * @param parent New parent transform
         */
        void SetParent(Transform* parent);

        /**
         * @brief Get all child transforms
         * @return Vector of child transforms
         */
        const std::vector<Transform*>& GetChildren() const { return m_children; }

        /**
         * @brief Add a child transform
         * @param child Child transform to add
         */
        void AddChild(Transform* child);

        /**
         * @brief Remove a child transform
         * @param child Child transform to remove
         */
        void RemoveChild(Transform* child);

        /**
         * @brief Detach from parent
         */
        void DetachFromParent();

        /**
         * @brief Check if this transform has a parent
         * @return True if has parent
         */
        bool HasParent() const { return m_parent != nullptr; }

        /**
         * @brief Check if this transform has children
         * @return True if has children
         */
        bool HasChildren() const { return !m_children.empty(); }

        // Transform hierarchy
        /**
         * @brief Update the transform hierarchy
         */
        void UpdateTransform();

        /**
         * @brief Mark the transform as dirty
         */
        void MarkDirty();

        /**
         * @brief Check if the transform is dirty
         * @return True if dirty
         */
        bool IsDirty() const { return m_dirty; }

        // Utility methods
        /**
         * @brief Get the distance to another transform
         * @param other Other transform
         * @return Distance
         */
        float GetDistanceTo(const Transform* other) const;

        /**
         * @brief Get the distance to a point
         * @param point Point to measure distance to
         * @return Distance
         */
        float GetDistanceTo(const glm::vec3& point) const;

        /**
         * @brief Get the direction to another transform
         * @param other Other transform
         * @return Direction vector
         */
        glm::vec3 GetDirectionTo(const Transform* other) const;

        /**
         * @brief Get the direction to a point
         * @param point Point to get direction to
         * @return Direction vector
         */
        glm::vec3 GetDirectionTo(const glm::vec3& point) const;

        // Serialization
        std::unordered_map<std::string, std::any> Serialize() const override;
        void Deserialize(const std::unordered_map<std::string, std::any>& data) override;

    private:
        // Local transform data
        glm::vec3 m_localPosition = glm::vec3(0.0f);
        glm::quat m_localRotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 m_localScale = glm::vec3(1.0f);

        // Transform matrices
        mutable glm::mat4 m_localMatrix = glm::mat4(1.0f);
        mutable glm::mat4 m_worldMatrix = glm::mat4(1.0f);

        // Hierarchy
        Transform* m_parent = nullptr;
        std::vector<Transform*> m_children;

        // Dirty flag for matrix updates
        mutable bool m_dirty = true;

        /**
         * @brief Update the local transform matrix
         */
        void UpdateLocalMatrix() const;

        /**
         * @brief Update the world transform matrix
         */
        void UpdateWorldMatrix() const;

        /**
         * @brief Propagate dirty flag to children
         */
        void PropagateDirty();
    };

} // namespace Nimbus