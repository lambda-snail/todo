#pragma once

#include "note/notestore.h"

namespace LambdaSnail::Todo::Ui {

    class Component {
    public:
        virtual void Init() = 0;
        virtual void Render() = 0;

        [[nodiscard]] virtual bool CloseWindow() const = 0;

        virtual ~Component() = default;
    };
}