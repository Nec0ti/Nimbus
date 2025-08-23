#pragma once

namespace Nimbus {

    /**
     * @brief Audio engine for the Nimbus Engine
     * 
     * The AudioEngine class manages audio playback using OpenAL
     * and provides 3D spatial audio functionality.
     */
    class AudioEngine {
    public:
        /**
         * @brief Constructor
         */
        AudioEngine();

        /**
         * @brief Destructor
         */
        ~AudioEngine();

        /**
         * @brief Initialize the audio engine
         * @return True if initialization was successful
         */
        bool Initialize();

        /**
         * @brief Shutdown the audio engine
         */
        void Shutdown();

        /**
         * @brief Update the audio engine
         * @param deltaTime Time since last frame
         */
        void Update(float deltaTime);

    private:
        bool m_initialized = false;
    };

} // namespace Nimbus