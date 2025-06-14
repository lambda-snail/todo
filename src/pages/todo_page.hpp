#pragma once

#include "../todo.hpp"

#include <Wt/WContainerWidget.h>

namespace LambdaSnail::todo
{
    class todo_page : public Wt::WContainerWidget
    {
    public:
        explicit todo_page();

    private:
        todo* m_current_item;
    };
}