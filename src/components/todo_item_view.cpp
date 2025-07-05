#include "todo_item_view.hpp"

#include "application/session.hpp"
#include "controllers/todo_controller.hpp"

#include <Wt/WInPlaceEdit.h>
#include <Wt/WTemplate.h>

TodoItemView::TodoItemView(Wt::Dbo::ptr<LambdaSnail::todo::todo_item> item,
                           LambdaSnail::todo::TodoController* controller)
    : m_Item(item), m_TodoController(controller)
{
    auto* t = addNew<Wt::WTemplate>(Wt::WString::tr("todo-item"));

    // <input class="form-check-input me-1" type="checkbox" value="" id="$checkbox-{id}" />
    m_checkbox = t->bindNew<Wt::WCheckBox>("input-element");
    m_checkbox->setChecked(m_Item->is_done);
    m_checkbox->addStyleClass("form-check-input");
    m_checkbox->addStyleClass("me-1");
    m_checkbox->setId("checkbox" + m_Item.id());
    m_checkbox->setInline(true);

    auto editor = t->bindNew<Wt::WInPlaceEdit>("text", m_Item->text);

    m_checkbox->checked().connect([this]() {
        m_Item.modify()->is_done = m_checkbox->isChecked();
        m_TodoController->updateTodoItem(m_Item);
    });

    editor->valueChanged().connect([this, editor]() {
        m_Item.modify()->text = editor->text().toUTF8();
        m_TodoController->updateTodoItem(m_Item);
    });
}