#pragma once

#include <memory>
#include <vector>

#include "ui/component.h"

namespace LambdaSnail::Todo::Core {
    using namespace Ui;

    class Application {
        std::vector<std::unique_ptr<Component>> m_Views{};

    public:
        void Render();
        void AddComponent(std::unique_ptr<Component> view);
    };
};