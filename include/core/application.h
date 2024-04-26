#pragma once

#include <memory>
#include <vector>

#include "ui/component.h"

namespace LambdaSnail::Todo::Core {
    using namespace Ui;

    class Application {
    public:
        void Render();
        void AddComponent(std::unique_ptr<Component> view);

        [[nodiscard]] bool ShouldCloseApplication() const;

    private:
        std::vector<std::unique_ptr<Component>> m_Views{};
        bool bShouldClose { false };
    };
};