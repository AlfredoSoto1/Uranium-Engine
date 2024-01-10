#pragma once

#include "Core/CoreMacros.h"

namespace Uranium::Platform::Interface {

    URANIUM_API class GraphicsAPI {
    public:
        explicit GraphicsAPI() noexcept;
        ~GraphicsAPI() noexcept;

    public:
        void init();
        void shutdown();

    private:
        virtual void createInstance() = 0;
        virtual void pickPhysicalDevice() = 0;
        virtual void createLogicalDevice() = 0;
        virtual void createSurface() = 0;
        virtual void createSwapChain() = 0;

    private:
    };
}