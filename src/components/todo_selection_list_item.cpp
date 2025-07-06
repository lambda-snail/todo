#include <Wt/WTemplate.h>

#include "models/todo.hpp"

#include "todo_selection_list_item.hpp"

LambdaSnail::todo::TodoSelectionListItem::TodoSelectionListItem(Wt::Dbo::ptr<todo> todo)
    : WTemplate(Wt::WString::tr("todo-selection-list-item")), m_Todo(todo)
{
    m_ElementId = std::format("todolist-{}", todo->id());

    WTemplate::bindString("title", todo->title);
    WTemplate::bindString("description", todo->description);
    WTemplate::bindString("id", m_ElementId);

    clicked().connect(this, [this]() {
        if (not hasStyleClass("active")) {
            // addStyleClass("active");
            // doJavaScript(std::format("window.document.getElementById('{}').classList.add('active')",
            // m_ElementId));

            signal_OnSelected.emit(this);
        }
        // else {
        //     removeStyleClass("active");
        //     doJavaScript(std::format("window.document.getElementById('{}').classList.remove('active')",
        //     m_ElementId));
        // }
    });
}
void LambdaSnail::todo::TodoSelectionListItem::setSelected(bool isSelected)
{
    // Add to the container element to easier keep track of selected status
    if (isSelected) {
        addStyleClass("active");
        doJavaScript(std::format("window.document.getElementById('{}').classList.add('active')", m_ElementId));
    }
    else {
        removeStyleClass("active");
        doJavaScript(std::format("window.document.getElementById('{}').classList.remove('active')", m_ElementId));
    }
}