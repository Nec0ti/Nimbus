#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Nimbus {

    /**
     * @brief Mesh system for the Nimbus Engine
     * 
     * The Mesh class represents 3D geometry data including vertices,
     * indices, and other mesh attributes.
     */
    class Mesh {
    public:
        /**
         * @brief Constructor
         */
        Mesh();

        /**
         * @brief Destructor
         */
        ~Mesh();

        /**
         * @brief Get the mesh name
         * @return Mesh name
         */
        const std::string& GetName() const { return m_name; }

        /**
         * @brief Set the mesh name
         * @param name New mesh name
         */
        void SetName(const std::string& name) { m_name = name; }

        /**
         * @brief Get the vertex count
         * @return Number of vertices
         */
        size_t GetVertexCount() const { return m_vertexCount; }

        /**
         * @brief Get the index count
         * @return Number of indices
         */
        size_t GetIndexCount() const { return m_indexCount; }

    private:
        std::string m_name = "Mesh";
        size_t m_vertexCount = 0;
        size_t m_indexCount = 0;
    };

} // namespace Nimbus