#pragma once

#include "../models/todo.hpp"

#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>

namespace LambdaSnail::todo::application
{
    class Session;
}
namespace LambdaSnail::todo
{
    class TodoController;
    struct todo_item;
}

class TodoItemView final : public Wt::WContainerWidget
{
  public:
    explicit TodoItemView(Wt::Dbo::ptr<LambdaSnail::todo::todo_item> item,
                          LambdaSnail::todo::TodoController* controller);

    [[nodiscard]] Wt::Dbo::ptr<LambdaSnail::todo::todo_item> getId() const { return m_Item; }

  private:
    Wt::Dbo::ptr<LambdaSnail::todo::todo_item> m_Item;

    Wt::WCheckBox* m_checkbox{};
    LambdaSnail::todo::TodoController* m_TodoController;
};