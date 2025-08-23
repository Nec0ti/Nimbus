#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "core/GameObject.h"

namespace Nimbus {

    class GameObject;

    /**
     * @brief Represents a scene in the Nimbus Engine
     * 
     * A Scene contains a collection of GameObjects and manages their lifecycle.
     * Scenes can be loaded, saved, and switched between during runtime.
     */
    class Scene {
    public:
        /**
         * @brief Constructor
         * @param name Scene name
         */
        explicit Scene(const std::string& name = "Scene");

        /**
         * @brief Destructor
         */
        ~Scene();

        /**
         * @brief Initialize the scene
         */
        void Initialize();

        /**
         * @brief Shutdown the scene
         */
        void Shutdown();

        /**
         * @brief Get the scene name
         * @return Scene name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the scene name
         * @param name New scene name
         */
        void SetName(const std::string& name) { m_name = name; }

        /**
         * @brief Check if the scene is active
         * @return True if the scene is active
         */
        bool IsActive() const { return m_active; }

        /**
         * @brief Set the scene active state
         * @param active New active state
         */
        void SetActive(bool active);

        /**
         * @brief Called when the scene becomes active
         */
        void OnActivate();

        /**
         * @brief Called when the scene becomes inactive
         */
        void OnDeactivate();

        /**
         * @brief Update the scene
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
         * @brief Render the scene
         */
        void Render();

        /**
         * @brief Add a GameObject to the scene
         * @param gameObject GameObject to add
         */
        void AddGameObject(std::shared_ptr<GameObject> gameObject);

        /**
         * @brief Remove a GameObject from the scene
         * @param gameObject GameObject to remove
         */
        void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

        /**
         * @brief Get all GameObjects in the scene
         * @return Vector of GameObjects
         */
        const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() const { return m_gameObjects; }

        /**
         * @brief Find a GameObject by name
         * @param name Name to search for
         * @return Pointer to the found GameObject, or nullptr if not found
         */
        std::shared_ptr<GameObject> FindGameObject(const std::string& name) const;

        /**
         * @brief Find GameObjects by tag
         * @param tag Tag to search for
         * @return Vector of GameObjects with the specified tag
         */
        std::vector<std::shared_ptr<GameObject>> FindGameObjectsByTag(const std::string& tag) const;

        /**
         * @brief Find GameObjects by layer
         * @param layer Layer to search for
         * @return Vector of GameObjects in the specified layer
         */
        std::vector<std::shared_ptr<GameObject>> FindGameObjectsByLayer(int layer) const;

        /**
         * @brief Get all root GameObjects (no parent)
         * @return Vector of root GameObjects
         */
        std::vector<std::shared_ptr<GameObject>> GetRootGameObjects() const;

        /**
         * @brief Destroy all GameObjects in the scene
         */
        void Clear();

        /**
         * @brief Get the scene statistics
         * @return Scene statistics
         */
        struct SceneStats {
            int gameObjectCount = 0;
            int componentCount = 0;
            int activeGameObjectCount = 0;
            int inactiveGameObjectCount = 0;
        };

        /**
         * @brief Get the current scene statistics
         * @return Current scene statistics
         */
        SceneStats GetStats() const;

        /**
         * @brief Serialize the scene to a data structure
         * @return Serialized data
         */
        std::unordered_map<std::string, std::any> Serialize() const;

        /**
         * @brief Deserialize the scene from a data structure
         * @param data Serialized data
         */
        void Deserialize(const std::unordered_map<std::string, std::any>& data);

        /**
         * @brief Save the scene to a file
         * @param filepath Path to save the scene to
         * @return True if save was successful
         */
        bool SaveToFile(const std::string& filepath) const;

        /**
         * @brief Load the scene from a file
         * @param filepath Path to load the scene from
         * @return True if load was successful
         */
        bool LoadFromFile(const std::string& filepath);

        /**
         * @brief Clone the scene
         * @return New scene instance
         */
        std::shared_ptr<Scene> Clone() const;

        /**
         * @brief Get the scene ID
         * @return Scene ID
         */
        uint64_t GetID() const { return m_id; }

    private:
        std::string m_name;
        uint64_t m_id;
        bool m_active = false;
        bool m_initialized = false;

        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
        std::unordered_map<std::string, std::shared_ptr<GameObject>> m_gameObjectMap;
        std::unordered_map<std::string, std::vector<std::shared_ptr<GameObject>>> m_taggedGameObjects;
        std::unordered_map<int, std::vector<std::shared_ptr<GameObject>>> m_layeredGameObjects;

        // Static ID counter
        static uint64_t s_nextID;

        /**
         * @brief Update the scene's internal data structures
         */
        void UpdateSceneData();

        /**
         * @brief Remove destroyed GameObjects
         */
        void CleanupDestroyedGameObjects();
    };

} // namespace Nimbus