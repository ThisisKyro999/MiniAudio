#include <string>

namespace MiniAudio
{
    static constexpr int VERSION_MAJOR = 1;
    static constexpr int VERSION_MINOR = 0;
    static constexpr int VERSION_PATCH = 0;

    const char* getName()
    {
        return "MiniAudio";
    }

    const char* getVersion()
    {
        return "1.0.0";
    }

    bool initialize()
    {
        return true;
    }

    void shutdown()
    {
    }
}
