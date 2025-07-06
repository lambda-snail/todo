#include "todo_selection_list.hpp"

#include "controllers/todo_controller.hpp"
#include "models/todo.hpp"
#include "todo_selection_list_item.hpp"

#include <Wt/WTemplate.h>

LambdaSnail::todo::TodoSelectionList::TodoSelectionList(TodoController* todoController)
    : m_TodoController(todoController)
{
    auto* t     = addNew<Wt::WTemplate>(Wt::WString::tr("todo-selection-list"));
    m_Container = t->bindNew<Wt::WContainerWidget>("todo-list");

    recreateTodoList();
}

void LambdaSnail::todo::TodoSelectionList::recreateTodoList()
{
    m_Container->clear();
    m_TodoController->forEachTodo([this](Wt::Dbo::ptr<todo> todo) {
        auto* t = m_Container->addNew<TodoSelectionListItem>(todo);

        t->OnSelected().connect(this, &LambdaSnail::todo::TodoSelectionList::onListItemClicked);

        // t->OnSelected().connect(this, [this](TodoSelectionListItem* todoView) {
        //     if (not hasStyleClass("active")) {
        //         removeStyleClass("active");
        //         doJavaScript(std::format(
        //             "window.document.getElementById('{}').classList.add('active')", m_ElementId));
        //         // signal_OnSelected.emit(m_Todo);
        //     }
        //     // else {
        //     //     addStyleClass("active");
        //     //     doJavaScript(std::format("window.document.getElementById('{}').classList.remove('active')",
        //     //     m_ElementId));
        //     // }
        // };
    });
}
void LambdaSnail::todo::TodoSelectionList::onListItemClicked(TodoSelectionListItem* todoView)
{
    if (todoView->getTodo().id() == m_TodoController->getCurrentTodo().id())
    {
        return;
    }

    if (m_CurrentTodo)
    {
        m_CurrentTodo->setSelected(false);
    }

    m_CurrentTodo = todoView;
    m_CurrentTodo->setSelected(true);
    m_TodoController->setCurrentItem(m_CurrentTodo->getTodo());
}