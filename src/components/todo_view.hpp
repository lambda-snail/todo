#pragma once

#include <vector>

#include <Wt/WContainerWidget.h>

#include "../models/todo.hpp"
#include "todo_item_view.hpp"

namespace LambdaSnail::todo
{
    class todo_view : public Wt::WContainerWidget
    {
    public:
        explicit todo_view(todo& item);

        void add_item(todo_item_view* item);
        void remove_item(Wt::Dbo::ptr<todo_item> const& item);
    private:
        todo& m_item;
        Wt::WContainerWidget* m_ItemContainer;
    };
}