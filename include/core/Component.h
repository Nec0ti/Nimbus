#pragma once

#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <any>

#include "core/GameObject.h"
#include "core/Transform.h"

namespace Nimbus {

    class GameObject;
    class Transform;

    /**
     * @brief Base class for all engine components
     * 
     * Components are the building blocks of GameObjects in the Nimbus Engine.
     * Each component provides specific functionality and can be attached to
     * GameObjects to create complex behaviors and systems.
     */
    class Component {
    public:
        /**
         * @brief Component types enumeration
         */
        enum class Type {
            Transform,
            Renderer,
            Camera,
            Light,
            AudioSource,
            AudioListener,
            Rigidbody,
            Collider,
            Animator,
            Script,
            Custom
        };

        /**
         * @brief Constructor
         * @param name Component name
         */
        explicit Component(const std::string& name = "Component");

        /**
         * @brief Virtual destructor
         */
        virtual ~Component() = default;

        /**
         * @brief Get the component name
         * @return Component name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the component name
         * @param name New component name
         */
        void SetName(const std::string& name) { m_name = name; }

        /**
         * @brief Get the component type
         * @return Component type
         */
        virtual Type GetType() const = 0;

        /**
         * @brief Get the component type name as string
         * @return Type name string
         */
        virtual std::string GetTypeName() const = 0;

        /**
         * @brief Get the GameObject this component is attached to
         * @return Pointer to the GameObject
         */
        GameObject* GetGameObject() const { return m_gameObject; }

        /**
         * @brief Set the GameObject this component is attached to
         * @param gameObject GameObject to attach to
         */
        void SetGameObject(GameObject* gameObject) { m_gameObject = gameObject; }

        /**
         * @brief Get the Transform component of the GameObject
         * @return Pointer to the Transform component
         */
        Transform* GetTransform() const;

        /**
         * @brief Check if the component is enabled
         * @return True if enabled
         */
        bool IsEnabled() const { return m_enabled; }

        /**
         * @brief Set the component enabled state
         * @param enabled New enabled state
         */
        void SetEnabled(bool enabled) { m_enabled = enabled; }

        /**
         * @brief Initialize the component
         * Called when the component is first created
         */
        virtual void Initialize() {}

        /**
         * @brief Start the component
         * Called when the game starts or the GameObject becomes active
         */
        virtual void Start() {}

        /**
         * @brief Update the component
         * Called every frame
         * @param deltaTime Time since last frame
         */
        virtual void Update(float deltaTime) {}

        /**
         * @brief Fixed update for physics
         * Called at fixed time intervals for physics calculations
         * @param fixedDeltaTime Fixed time step
         */
        virtual void FixedUpdate(float fixedDeltaTime) {}

        /**
         * @brief Late update
         * Called after all other updates
         * @param deltaTime Time since last frame
         */
        virtual void LateUpdate(float deltaTime) {}

        /**
         * @brief Render the component
         * Called during the rendering phase
         */
        virtual void Render() {}

        /**
         * @brief On destroy callback
         * Called when the component is being destroyed
         */
        virtual void OnDestroy() {}

        /**
         * @brief On enable callback
         * Called when the component is enabled
         */
        virtual void OnEnable() {}

        /**
         * @brief On disable callback
         * Called when the component is disabled
         */
        virtual void OnDisable() {}

        /**
         * @brief Serialize the component to a data structure
         * @return Serialized data
         */
        virtual std::unordered_map<std::string, std::any> Serialize() const;

        /**
         * @brief Deserialize the component from a data structure
         * @param data Serialized data
         */
        virtual void Deserialize(const std::unordered_map<std::string, std::any>& data);

        /**
         * @brief Clone the component
         * @return New component instance
         */
        virtual std::shared_ptr<Component> Clone() const = 0;

        /**
         * @brief Get a custom property value
         * @param name Property name
         * @return Property value
         */
        template<typename T>
        T GetProperty(const std::string& name) const {
            auto it = m_properties.find(name);
            if (it != m_properties.end()) {
                try {
                    return std::any_cast<T>(it->second);
                } catch (const std::bad_any_cast&) {
                    return T{};
                }
            }
            return T{};
        }

        /**
         * @brief Set a custom property value
         * @param name Property name
         * @param value Property value
         */
        template<typename T>
        void SetProperty(const std::string& name, const T& value) {
            m_properties[name] = value;
        }

        /**
         * @brief Check if a property exists
         * @param name Property name
         * @return True if property exists
         */
        bool HasProperty(const std::string& name) const {
            return m_properties.find(name) != m_properties.end();
        }

        /**
         * @brief Remove a property
         * @param name Property name
         */
        void RemoveProperty(const std::string& name) {
            m_properties.erase(name);
        }

        /**
         * @brief Get all properties
         * @return Map of all properties
         */
        const std::unordered_map<std::string, std::any>& GetProperties() const {
            return m_properties;
        }

    protected:
        std::string m_name;
        GameObject* m_gameObject = nullptr;
        bool m_enabled = true;
        std::unordered_map<std::string, std::any> m_properties;
    };

    /**
     * @brief Macro to define component type information
     */
    #define NIMBUS_COMPONENT_TYPE(type) \
        Nimbus::Component::Type GetType() const override { return Nimbus::Component::Type::type; } \
        std::string GetTypeName() const override { return #type; }

    /**
     * @brief Macro to define component cloning
     */
    #define NIMBUS_COMPONENT_CLONE(className) \
        std::shared_ptr<Component> Clone() const override { \
            return std::make_shared<className>(*this); \
        }

} // namespace Nimbus