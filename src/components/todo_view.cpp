
//#include <Wt/WAbstractListModel.h>

#include "todo_view.hpp"
#include "controllers/todo_controller.hpp"
#include "todo_item_view.hpp"

#include <iostream>

#include <Wt/WTemplate.h>
#include <Wt/WInPlaceEdit.h>

LambdaSnail::todo::TodoView::TodoView(TodoController* todoController) : m_TodoController(todoController), signal_AddTodoItemPressed(this, "addTodoItemPressed")
{
    m_TodoController->onCurrentTodoChanged().connect(this, &LambdaSnail::todo::TodoView::rebuildView);
    m_TodoController->onTodoItemAdded().connect(this, &LambdaSnail::todo::TodoView::todoItemAdded);

    signal_AddTodoItemPressed.connect(this, &LambdaSnail::todo::TodoView::addItem);

    rebuildView();
}

void LambdaSnail::todo::TodoView::addItem()
{
    m_TodoController->addTodoItem("Enter task ...", false);
}

void LambdaSnail::todo::TodoView::remove_item(Wt::Dbo::ptr<todo_item> const& item)
{
    // auto const view_it = std::ranges::find_if(m_todo_views.begin(), m_todo_views.end(),
    // [item](todo_item_view const* view)
    // {
    //     return view->get_id() == item->id();
    // });
    //
    // if (view_it == m_todo_views.end()) {
    //     return;
    // }
    //
    // m_item.items.erase(item);
    // m_todo_views.erase(view_it);
    //
    // refresh();
}
void LambdaSnail::todo::TodoView::rebuildView()
{
    clear();

    auto currentTodo = m_TodoController->getCurrentTodo();
    if (not currentTodo) {
        return; // TODO: Handle this nicely
    }

    auto* t = addNew<Wt::WTemplate>(Wt::WString::tr("todo-view"));

    t->bindString("btn-add-todo-item-call", signal_AddTodoItemPressed.createCall({}));

    auto titleEditor = t->bindNew<Wt::WInPlaceEdit>("title", currentTodo->title);
    auto descriptionEditor = t->bindNew<Wt::WInPlaceEdit>("description", currentTodo->description);
    t->bindString("last-updated", currentTodo->modified.toString()); // TODO: "A few moments ago"

    titleEditor->valueChanged().connect([this, titleEditor]() {
        auto current = m_TodoController->getCurrentTodo();
        current.modify()->title = titleEditor->text().toUTF8();
        m_TodoController->updateTodo(current);
    });

    descriptionEditor->valueChanged().connect([this, descriptionEditor]() {
        auto current = m_TodoController->getCurrentTodo();
        current.modify()->description = descriptionEditor->text().toUTF8();
        m_TodoController->updateTodo(current);
    });

    auto* list_t    = t->bindNew<Wt::WTemplate>("item-list", Wt::WString::tr("todo-list"));
    m_ItemContainer = list_t->bindNew<Wt::WContainerWidget>("items");

    m_TodoController->forEachItem([this](Wt::Dbo::ptr<todo_item> const item) {
        auto* view = addTodoItemView(item);
    });
}

TodoItemView* LambdaSnail::todo::TodoView::addTodoItemView(Wt::Dbo::ptr<todo_item> item)
{
    return m_ItemContainer->addNew<TodoItemView>(item, m_TodoController);
}

void LambdaSnail::todo::TodoView::todoItemAdded(Wt::Dbo::ptr<todo_item> item)
{
    addTodoItemView(item);
}