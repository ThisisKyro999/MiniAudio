#include <MiniAudio/Audio.hpp>

#include <atomic>
#include <mutex>
#include <string>

namespace MiniAudio
{
    namespace
    {
        constexpr int VERSION_MAJOR = 1;
        constexpr int VERSION_MINOR = 0;
        constexpr int VERSION_PATCH = 0;

        std::atomic<bool> initialized{false};
        std::mutex lifecycleMutex;
    }

    const char* getName()
    {
        return "MiniAudio";
    }

    const char* getVersion()
    {
        return "1.0.0";
    }

    int getVersionMajor()
    {
        return VERSION_MAJOR;
    }

    int getVersionMinor()
    {
        return VERSION_MINOR;
    }

    int getVersionPatch()
    {
        return VERSION_PATCH;
    }

    bool initialize()
    {
        std::lock_guard<std::mutex> lock(lifecycleMutex);

        if (initialized.load())
            return true;

        initialized.store(true);

        return true;
    }

    void shutdown()
    {
        std::lock_guard<std::mutex> lock(lifecycleMutex);

        if (!initialized.load())
            return;

        initialized.store(false);
    }

    bool isInitialized()
    {
        return initialized.load();
    }

    const char* getPlatform()
    {
#if defined(_WIN32)
        return "Windows";
#elif defined(__ANDROID__)
        return "Android";
#elif defined(__APPLE__)
        return "Apple";
#elif defined(__linux__)
        return "Linux";
#else
        return "Unknown";
#endif
    }

    const char* getArchitecture()
    {
#if defined(__x86_64__) || defined(_M_X64)
        return "x86_64";
#elif defined(__aarch64__) || defined(_M_ARM64)
        return "ARM64";
#elif defined(__i386__) || defined(_M_IX86)
        return "x86";
#elif defined(__arm__) || defined(_M_ARM)
        return "ARM";
#else
        return "Unknown";
#endif
    }

    bool is64Bit()
    {
        return sizeof(void*) == 8;
    }
}
