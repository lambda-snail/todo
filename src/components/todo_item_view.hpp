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

    template <typename TFunction>
    void register_on_checked(TFunction const& callback) const;
    template <typename TFunction>
    void register_on_unchecked(TFunction const& callback) const;

    [[nodiscard]] Wt::Dbo::ptr<LambdaSnail::todo::todo_item> getId() const { return m_Item; }

  private:
    Wt::Dbo::ptr<LambdaSnail::todo::todo_item> m_Item;

    Wt::WCheckBox* m_checkbox{};
    LambdaSnail::todo::TodoController* m_TodoController;
};

template <typename TFunction>
void TodoItemView::register_on_checked(TFunction const& callback) const
{
    m_checkbox->checked().connect(callback);
}

template <typename TFunction> void TodoItemView::register_on_unchecked(TFunction const& callback) const
{
    m_checkbox->unChecked().connect(callback);
}