#pragma once

#include <Wt/WContainerWidget.h>

namespace LambdaSnail::todo {

class TodoSelectionListItem;
class TodoController;

/**
 * The component that displays the list of available TODOs.
 */
class TodoSelectionList : public Wt::WContainerWidget {
public:
    explicit TodoSelectionList(TodoController* todoController);
    void recreateTodoList();

private:
    TodoController* m_TodoController;
    WContainerWidget* m_Container;

    TodoSelectionListItem* m_CurrentTodo { nullptr };

    void onListItemClicked(TodoSelectionListItem* todoView);
};

}