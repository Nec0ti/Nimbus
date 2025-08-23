#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <typeindex>

#include "core/Component.h"
#include "core/Transform.h"

namespace Nimbus {

    class Scene;
    class Component;
    class Transform;

    /**
     * @brief Represents an entity in the scene with components
     * 
     * GameObjects are the fundamental building blocks of scenes in the Nimbus Engine.
     * Each GameObject can have multiple components that define its behavior and appearance.
     * GameObjects form a hierarchy through parent-child relationships.
     */
    class GameObject {
    public:
        /**
         * @brief Constructor
         * @param name GameObject name
         */
        explicit GameObject(const std::string& name = "GameObject");

        /**
         * @brief Destructor
         */
        ~GameObject();

        /**
         * @brief Get the GameObject name
         * @return GameObject name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the GameObject name
         * @param name New name
         */
        void SetName(const std::string& name) { m_name = name; }

        /**
         * @brief Get the GameObject tag
         * @return GameObject tag
         */
        const std::string& GetTag() const { return m_tag; }

        /**
         * @brief Set the GameObject tag
         * @param tag New tag
         */
        void SetTag(const std::string& tag) { m_tag = tag; }

        /**
         * @brief Get the GameObject layer
         * @return GameObject layer
         */
        int GetLayer() const { return m_layer; }

        /**
         * @brief Set the GameObject layer
         * @param layer New layer
         */
        void SetLayer(int layer) { m_layer = layer; }

        /**
         * @brief Check if the GameObject is active
         * @return True if active
         */
        bool IsActive() const { return m_active; }

        /**
         * @brief Set the GameObject active state
         * @param active New active state
         */
        void SetActive(bool active);

        /**
         * @brief Check if the GameObject is active in hierarchy
         * @return True if active in hierarchy
         */
        bool IsActiveInHierarchy() const;

        /**
         * @brief Get the Transform component
         * @return Pointer to the Transform component
         */
        Transform* GetTransform() const { return m_transform.get(); }

        /**
         * @brief Get the parent GameObject
         * @return Pointer to the parent GameObject
         */
        GameObject* GetParent() const { return m_parent; }

        /**
         * @brief Set the parent GameObject
         * @param parent New parent GameObject
         */
        void SetParent(GameObject* parent);

        /**
         * @brief Get all child GameObjects
         * @return Vector of child GameObjects
         */
        const std::vector<GameObject*>& GetChildren() const { return m_children; }

        /**
         * @brief Add a child GameObject
         * @param child Child GameObject to add
         */
        void AddChild(GameObject* child);

        /**
         * @brief Remove a child GameObject
         * @param child Child GameObject to remove
         */
        void RemoveChild(GameObject* child);

        /**
         * @brief Find a child GameObject by name
         * @param name Name to search for
         * @return Pointer to the found child, or nullptr if not found
         */
        GameObject* FindChild(const std::string& name) const;

        /**
         * @brief Find a child GameObject by name recursively
         * @param name Name to search for
         * @return Pointer to the found child, or nullptr if not found
         */
        GameObject* FindChildRecursive(const std::string& name) const;

        /**
         * @brief Get all components
         * @return Vector of all components
         */
        const std::vector<std::shared_ptr<Component>>& GetComponents() const { return m_components; }

        /**
         * @brief Add a component
         * @param component Component to add
         */
        void AddComponent(std::shared_ptr<Component> component);

        /**
         * @brief Remove a component
         * @param component Component to remove
         */
        void RemoveComponent(std::shared_ptr<Component> component);

        /**
         * @brief Get a component by type
         * @tparam T Component type
         * @return Pointer to the component, or nullptr if not found
         */
        template<typename T>
        T* GetComponent() const {
            for (const auto& component : m_components) {
                if (auto casted = std::dynamic_pointer_cast<T>(component)) {
                    return casted.get();
                }
            }
            return nullptr;
        }

        /**
         * @brief Get all components of a specific type
         * @tparam T Component type
         * @return Vector of components of the specified type
         */
        template<typename T>
        std::vector<T*> GetComponents() const {
            std::vector<T*> result;
            for (const auto& component : m_components) {
                if (auto casted = std::dynamic_pointer_cast<T>(component)) {
                    result.push_back(casted.get());
                }
            }
            return result;
        }

        /**
         * @brief Get a component in children
         * @tparam T Component type
         * @return Pointer to the component, or nullptr if not found
         */
        template<typename T>
        T* GetComponentInChildren() const {
            // Check self
            if (auto component = GetComponent<T>()) {
                return component;
            }
            
            // Check children
            for (auto child : m_children) {
                if (auto component = child->GetComponentInChildren<T>()) {
                    return component;
                }
            }
            
            return nullptr;
        }

        /**
         * @brief Get a component in parent
         * @tparam T Component type
         * @return Pointer to the component, or nullptr if not found
         */
        template<typename T>
        T* GetComponentInParent() const {
            if (m_parent) {
                if (auto component = m_parent->GetComponent<T>()) {
                    return component;
                }
                return m_parent->GetComponentInParent<T>();
            }
            return nullptr;
        }

        /**
         * @brief Add a component of the specified type
         * @tparam T Component type
         * @tparam Args Constructor argument types
         * @param args Constructor arguments
         * @return Pointer to the created component
         */
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            auto component = std::make_shared<T>(std::forward<Args>(args)...);
            AddComponent(component);
            return component.get();
        }

        /**
         * @brief Check if the GameObject has a component of the specified type
         * @tparam T Component type
         * @return True if the component exists
         */
        template<typename T>
        bool HasComponent() const {
            return GetComponent<T>() != nullptr;
        }

        /**
         * @brief Get the scene this GameObject belongs to
         * @return Pointer to the scene
         */
        Scene* GetScene() const { return m_scene; }

        /**
         * @brief Set the scene this GameObject belongs to
         * @param scene Scene to set
         */
        void SetScene(Scene* scene) { m_scene = scene; }

        /**
         * @brief Get the GameObject ID
         * @return GameObject ID
         */
        uint64_t GetID() const { return m_id; }

        /**
         * @brief Initialize the GameObject
         */
        void Initialize();

        /**
         * @brief Start the GameObject
         */
        void Start();

        /**
         * @brief Update the GameObject
         * @param deltaTime Time since last frame
         */
        void Update(float deltaTime);

        /**
         * @brief Fixed update for physics
         * @param fixedDeltaTime Fixed time step
         */
        void FixedUpdate(float fixedDeltaTime);

        /**
         * @brief Late update
         * @param deltaTime Time since last frame
         */
        void LateUpdate(float deltaTime);

        /**
         * @brief Render the GameObject
         */
        void Render();

        /**
         * @brief Destroy the GameObject
         */
        void Destroy();

        /**
         * @brief Clone the GameObject
         * @return New GameObject instance
         */
        std::shared_ptr<GameObject> Clone() const;

        /**
         * @brief Serialize the GameObject
         * @return Serialized data
         */
        std::unordered_map<std::string, std::any> Serialize() const;

        /**
         * @brief Deserialize the GameObject
         * @param data Serialized data
         */
        void Deserialize(const std::unordered_map<std::string, std::any>& data);

        /**
         * @brief Compare GameObjects by ID
         * @param other Other GameObject
         * @return True if this GameObject has a smaller ID
         */
        bool operator<(const GameObject& other) const {
            return m_id < other.m_id;
        }

        /**
         * @brief Compare GameObjects by ID
         * @param other Other GameObject
         * @return True if GameObjects have the same ID
         */
        bool operator==(const GameObject& other) const {
            return m_id == other.m_id;
        }

    private:
        std::string m_name;
        std::string m_tag;
        int m_layer = 0;
        bool m_active = true;
        uint64_t m_id;

        // Hierarchy
        GameObject* m_parent = nullptr;
        std::vector<GameObject*> m_children;

        // Components
        std::vector<std::shared_ptr<Component>> m_components;
        std::shared_ptr<Transform> m_transform;

        // Scene reference
        Scene* m_scene = nullptr;

        // Static ID counter
        static uint64_t s_nextID;
    };

} // namespace Nimbus