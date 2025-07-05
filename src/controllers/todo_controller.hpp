#pragma once

#include <Wt/WSignal.h>
#include <cstdint>
#include <functional>

#include <Wt/Dbo/collection.h>

namespace LambdaSnail::todo::application
{
class Session;
}

namespace LambdaSnail::todo
{
struct todo_item;
class todo;

class TodoController
{
  public:
    explicit TodoController(application::Session& session);

    void setYear(uint32_t year);

    void getTodos(std::vector<Wt::Dbo::ptr<todo>>& todoList) const;

    void setCurrentItem(Wt::Dbo::ptr<todo> item);
    Wt::Dbo::ptr<todo> getCurrentTodo() const;
    void getCurrentTodo(std::function<void(Wt::Dbo::ptr<todo>)> const& mutator);

    void addTodoItem(const std::string& text, bool isDone);
    void updateTodoItem(Wt::Dbo::ptr<todo_item>);

    void forEachItem(std::function<void(Wt::Dbo::ptr<todo_item>)> const& function) const;
    void forEachItem(Wt::Dbo::ptr<todo> todo,
                     std::function<void(Wt::Dbo::ptr<todo_item>)> const& function) const;

    Wt::Signal<>& onCurrentTodoChanged() { return signal_CurrentTodoChanged; }
    Wt::Signal<Wt::Dbo::ptr<todo_item>>& onTodoItemAdded() { return signal_TodoItemAdded; }

  private:
    Wt::Signal<> signal_CurrentTodoChanged{};
    Wt::Signal<Wt::Dbo::ptr<todo_item>> signal_TodoItemAdded{};

    uint32_t m_Year;

    application::Session& m_Session;

    Wt::Dbo::ptr<todo> m_CurrentItem;
};
} // namespace LambdaSnail::todo