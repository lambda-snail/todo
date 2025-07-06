//
// Created by niclas on 7/5/25.
//

#include "todo_controller.hpp"

#include <Wt/WDate.h>

#include "application/session.hpp"
#include "models/todo.hpp"


LambdaSnail::todo::TodoController::TodoController(application::Session& session)
    : m_Year(Wt::WDateTime::currentDateTime().date().year()), m_Session(session)
{ }

void LambdaSnail::todo::TodoController::setYear(uint32_t year)
{
    m_Year = year;
}

void LambdaSnail::todo::TodoController::getTodos(std::vector<Wt::Dbo::ptr<todo>>& todoList) const
{
    Wt::Dbo::Transaction transaction(m_Session);
    auto const& result =
        m_Session
            .find<todo>()
            // return m_Session.find<todo>()
            .where("owner_id = ?")
            .bind(m_Session.user().id())
            .resultList();
    //.where("strftime('%Y', modified) = '?'")
    //.bind(std::to_string(m_Year));

    for (auto const todo : result) {
        todoList.push_back(todo);
    }
}

void LambdaSnail::todo::TodoController::setCurrentItem(Wt::Dbo::ptr<todo> item)
{
    m_CurrentItem = item;
    signal_CurrentTodoChanged.emit();
}

Wt::Dbo::ptr<LambdaSnail::todo::todo> LambdaSnail::todo::TodoController::getCurrentTodo() const
{
    return m_CurrentItem;
}

void LambdaSnail::todo::TodoController::getCurrentTodo(
    const std::function<void(Wt::Dbo::ptr<todo>)>& mutator)
{
    Wt::Dbo::Transaction transaction(m_Session);
    mutator(m_CurrentItem);
}
void LambdaSnail::todo::TodoController::updateTodo(Wt::Dbo::ptr<todo> todo)
{
    todo.modify()->modified = Wt::WDateTime::currentDateTime();
    Wt::Dbo::Transaction transaction(m_Session);
}

void LambdaSnail::todo::TodoController::forEachItem(std::function<void(Wt::Dbo::ptr<todo_item>)> const& function) const
{
    forEachItem(m_CurrentItem, function);
}

void LambdaSnail::todo::TodoController::forEachItem(Wt::Dbo::ptr<todo> todo, std::function<void(Wt::Dbo::ptr<todo_item>)> const& function) const
{
    Wt::Dbo::Transaction transaction(m_Session);
    for (auto item : todo->items) {
        function(item);
    }
}

void LambdaSnail::todo::TodoController::addTodoItem(std::string const& text, bool isDone)
{
    if (not m_CurrentItem) {
        throw std::logic_error("Unable to add todo item to empty todo");
    }

    Wt::Dbo::Transaction transaction(m_Session);

    auto item              = m_Session.addNew<todo_item>();
    item.modify()->text    = text;
    item.modify()->is_done = isDone;

    m_CurrentItem.modify()->items.insert(item);
    transaction.commit();
    signal_TodoItemAdded(item);
}
void LambdaSnail::todo::TodoController::updateTodoItem(Wt::Dbo::ptr<todo_item> item)
{
    Wt::Dbo::Transaction transaction(m_Session);
}

void LambdaSnail::todo::TodoController::forEachTodo(
    std::function<void(Wt::Dbo::ptr<todo>)> const& function) const
{
    Wt::Dbo::Transaction transaction(m_Session);
    auto const& result =
        m_Session
            .find<todo>()
            .where("owner_id = ?")
            .bind(m_Session.user().id())
            .resultList();
    //.where("strftime('%Y', modified) = '?'")
    //.bind(std::to_string(m_Year));

    for (auto const todo : result) {
        function(todo);
    }
}