#include "todo_page.hpp"

#include "components/todo_view.hpp"

#include <Wt/WApplication.h>
#include <Wt/WTemplate.h>
#include <Wt/Dbo/Session.h>

LambdaSnail::todo::todo_page::todo_page(application::Session& session) : m_session(session)
{
    //m_current_item = new todo; // TODO: Temporary

    //m_current_item =

    Wt::Dbo::Transaction transaction(m_session);
    m_current_item = m_session.addNew<todo>();
    m_current_item.modify()->owner = m_session.user();

    auto item1 = Wt::Dbo::make_ptr<todo_item>();
    item1.modify()->is_done = true;
    item1.modify()->text = "Hello TODO";


    auto item2 = Wt::Dbo::make_ptr<todo_item>();
    item2.modify()->is_done = false;
    item2.modify()->text = "Goodbye TODO";

    m_current_item.modify()->items.insert(item1);
    m_current_item.modify()->items.insert(item2);

    auto* t = addNew<Wt::WTemplate>(Wt::WString::tr("todo-page"));

    t->bindString("title", "Hello World Task");
    t->bindString("description", "A description for this TODO");
    t->bindString("last-updated", "A few moments ago");

    t->bindNew<todo_view>("todo", *m_current_item.modify());
}