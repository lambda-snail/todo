#include "todo_page.hpp"

#include "../components/todo_view.hpp"

#include <Wt/WTemplate.h>

LambdaSnail::todo::todo_page::todo_page()
{
    m_current_item = new todo(10);
    m_current_item->items.emplace_back(1, "Hello TODO", true);
    m_current_item->items.emplace_back(2, "Bye TODO", false);

    auto* t = addNew<Wt::WTemplate>(Wt::WString::tr("todo-page"));

    t->bindString("title", "Hello World Task");
    t->bindString("description", "A description for this TODO");
    t->bindString("last-updated", "A few moments ago");

    t->bindNew<todo_view>("todo", *m_current_item);
}