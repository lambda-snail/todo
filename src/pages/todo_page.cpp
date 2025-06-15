#include "todo_page.hpp"

#include "../components/todo_view.hpp"

#include <Wt/WTemplate.h>

LambdaSnail::todo::todo_page::todo_page()
{
    m_current_item = new todo; // TODO: Temporary

    auto item1 = Wt::Dbo::make_ptr<todo_item>();
    item1.modify()->is_done = true;
    item1.modify()->text = "Hello TODO";

    auto item2 = Wt::Dbo::make_ptr<todo_item>();
    item2.modify()->is_done = false;
    item2.modify()->text = "Goodbye TODO";

    m_current_item->items.insert(std::move(item1));
    m_current_item->items.insert(std::move(item2));

    auto* t = addNew<Wt::WTemplate>(Wt::WString::tr("todo-page"));

    t->bindString("title", "Hello World Task");
    t->bindString("description", "A description for this TODO");
    t->bindString("last-updated", "A few moments ago");

    t->bindNew<todo_view>("todo", *m_current_item);
}