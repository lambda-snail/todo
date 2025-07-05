
//#include <Wt/WAbstractListModel.h>

#include "todo_view.hpp"
#include "controllers/todo_controller.hpp"
#include "todo_item_view.hpp"

#include <iostream>

#include <Wt/WTemplate.h>
#include <Wt/WInPlaceEdit.h>

LambdaSnail::todo::todo_view::todo_view(TodoController* todoController) : m_TodoController(todoController), signal_AddTodoItemPressed(this, "addTodoItemPressed")
{
    m_TodoController->onCurrentTodoChanged().connect(this, &LambdaSnail::todo::todo_view::rebuildView);
    m_TodoController->onTodoItemAdded().connect(this, &LambdaSnail::todo::todo_view::todoItemAdded);

    signal_AddTodoItemPressed.connect(this, &LambdaSnail::todo::todo_view::addItem);

    rebuildView();
}

void LambdaSnail::todo::todo_view::addItem()
{
    m_TodoController->addTodoItem("Enter task ...", false);
}

void LambdaSnail::todo::todo_view::remove_item(Wt::Dbo::ptr<todo_item> const& item)
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
void LambdaSnail::todo::todo_view::rebuildView()
{
    clear();

    auto currentTodo = m_TodoController->getCurrentTodo();
    if (not currentTodo) {
        return; // TODO: Handle this nicely
    }

    auto* t = addNew<Wt::WTemplate>(Wt::WString::tr("todo-view"));

    t->bindString("btn-add-todo-item-call", signal_AddTodoItemPressed.createCall({}));

    t->bindNew<Wt::WInPlaceEdit>("title", currentTodo->title);
    t->bindNew<Wt::WInPlaceEdit>("description", currentTodo->description);
    t->bindString("last-updated", currentTodo->modified.toString()); // TODO: "A few moments ago"

    auto* list_t    = t->bindNew<Wt::WTemplate>("item-list", Wt::WString::tr("todo-list"));
    m_ItemContainer = list_t->bindNew<Wt::WContainerWidget>("items");

    m_TodoController->forEachItem([this](Wt::Dbo::ptr<todo_item> const item) {
        auto* view = addTodoItemView(item);

        view->register_on_checked([]() { std::cout << "Checked" << std::endl; });
        view->register_on_unchecked([]() { std::cout << "Unchecked" << std::endl; });
    });
}



todo_item_view* LambdaSnail::todo::todo_view::addTodoItemView(Wt::Dbo::ptr<todo_item> item)
{
    return m_ItemContainer->addNew<todo_item_view>(item->id(), item->text, item->is_done);
}

void LambdaSnail::todo::todo_view::todoItemAdded(Wt::Dbo::ptr<todo_item> item)
{
    addTodoItemView(item);
}