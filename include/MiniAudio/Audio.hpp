#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>

namespace MiniAudio
{
    enum class AudioState
    {
        Stopped,
        Playing,
        Paused
    };

    struct AudioData
    {
        std::string path;
        AudioState state = AudioState::Stopped;
        float volume = 1.0f;
        float pitch = 1.0f;
        bool looping = false;
    };

    class AudioManager
    {
    private:
        std::unordered_map<std::uint32_t, AudioData> sounds;
        std::uint32_t nextId = 1;
        float masterVolume = 1.0f;

    public:
        AudioManager() = default;
        ~AudioManager() = default;

        AudioManager(const AudioManager&) = delete;
        AudioManager& operator=(const AudioManager&) = delete;

        std::uint32_t load(const std::string& path);

        bool unload(std::uint32_t id);

        bool play(std::uint32_t id);
        bool pause(std::uint32_t id);
        bool resume(std::uint32_t id);
        bool stop(std::uint32_t id);

        bool setVolume(std::uint32_t id, float volume);
        bool setPitch(std::uint32_t id, float pitch);
        bool setLooping(std::uint32_t id, bool looping);

        void setMasterVolume(float volume);
        float getMasterVolume() const;

        AudioState getState(std::uint32_t id) const;

        bool isPlaying(std::uint32_t id) const;
        bool isPaused(std::uint32_t id) const;
        bool exists(std::uint32_t id) const;

        void stopAll();
        void clear();

        std::size_t getLoadedCount() const;
    };
}
