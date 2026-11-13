#include <algorithm>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <cstdint>

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
        std::uint32_t load(const std::string& path)
        {
            if (path.empty() || !std::filesystem::is_regular_file(path))
                return 0;

            const std::uint32_t id = nextId++;

            AudioData data;
            data.path = path;

            sounds.emplace(id, std::move(data));

            return id;
        }

        bool unload(std::uint32_t id)
        {
            return sounds.erase(id) > 0;
        }

        bool play(std::uint32_t id)
        {
            auto it = sounds.find(id);

            if (it == sounds.end())
                return false;

            it->second.state = AudioState::Playing;
            return true;
        }

        bool pause(std::uint32_t id)
        {
            auto it = sounds.find(id);

            if (it == sounds.end())
                return false;

            if (it->second.state != AudioState::Playing)
                return false;

            it->second.state = AudioState::Paused;
            return true;
        }

        bool resume(std::uint32_t id)
        {
            auto it = sounds.find(id);

            if (it == sounds.end())
                return false;

            if (it->second.state != AudioState::Paused)
                return false;

            it->second.state = AudioState::Playing;
            return true;
        }

        bool stop(std::uint32_t id)
        {
            auto it = sounds.find(id);

            if (it == sounds.end())
                return false;

            it->second.state = AudioState::Stopped;
            return true;
        }

        bool setVolume(std::uint32_t id, float volume)
        {
            auto it = sounds.find(id);

            if (it == sounds.end())
                return false;

            it->second.volume = std::clamp(volume, 0.0f, 1.0f);
            return true;
        }

        bool setPitch(std::uint32_t id, float pitch)
        {
            auto it = sounds.find(id);

            if (it == sounds.end())
                return false;

            it->second.pitch = std::clamp(pitch, 0.1f, 4.0f);
            return true;
        }

        bool setLooping(std::uint32_t id, bool looping)
        {
            auto it = sounds.find(id);

            if (it == sounds.end())
                return false;

            it->second.looping = looping;
            return true;
        }

        void setMasterVolume(float volume)
        {
            masterVolume = std::clamp(volume, 0.0f, 1.0f);
        }

        float getMasterVolume() const
        {
            return masterVolume;
        }

        AudioState getState(std::uint32_t id) const
        {
            auto it = sounds.find(id);

            if (it == sounds.end())
                return AudioState::Stopped;

            return it->second.state;
        }

        bool isPlaying(std::uint32_t id) const
        {
            return getState(id) == AudioState::Playing;
        }

        bool isPaused(std::uint32_t id) const
        {
            return getState(id) == AudioState::Paused;
        }

        bool exists(std::uint32_t id) const
        {
            return sounds.find(id) != sounds.end();
        }

        void stopAll()
        {
            for (auto& entry : sounds)
                entry.second.state = AudioState::Stopped;
        }

        void clear()
        {
            sounds.clear();
            nextId = 1;
        }

        std::size_t getLoadedCount() const
        {
            return sounds.size();
        }
    };
}
