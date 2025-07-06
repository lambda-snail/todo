#pragma once

#include <vector>

#include <Wt/WContainerWidget.h>

#include "../models/todo.hpp"
#include "todo_item_view.hpp"

namespace LambdaSnail::todo
{
class TodoController;
class TodoView : public Wt::WContainerWidget
    {
    public:
        explicit TodoView(TodoController* todoController);

        void remove_item(Wt::Dbo::ptr<todo_item> const& item);

        Wt::JSignal<>& onAddTodoItemPressed() { return signal_AddTodoItemPressed; }
    private:
        Wt::WContainerWidget* m_ItemContainer;
        TodoController* m_TodoController;

        void addItem();
        void rebuildView();

        TodoItemView* addTodoItemView(Wt::Dbo::ptr<todo_item> item);
        void todoItemAdded(Wt::Dbo::ptr<todo_item> item);

        Wt::JSignal<> signal_AddTodoItemPressed;
    };
}