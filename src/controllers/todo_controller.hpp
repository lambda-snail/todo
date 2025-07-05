#pragma once

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
    Wt::Dbo::ptr<todo> getCurrentItem() const;
    void getCurrentItem(std::function<void(Wt::Dbo::ptr<todo>)> const& mutator);

    void forEachItem(std::function<void(Wt::Dbo::ptr<todo_item>)> const& function) const;
    void forEachItem(Wt::Dbo::ptr<todo> todo, std::function<void(Wt::Dbo::ptr<todo_item>)> const& function) const;

  private:
    uint32_t m_Year;

    application::Session& m_Session;

    Wt::Dbo::ptr<todo> m_CurrentItem;
};
} // namespace LambdaSnail::todo