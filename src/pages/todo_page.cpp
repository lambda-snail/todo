#include "todo_page.hpp"

#include "components/todo_selection_list.hpp"
#include "components/todo_view.hpp"
#include "controllers/todo_controller.hpp"

#include <Wt/Dbo/Session.h>
#include <Wt/WApplication.h>
#include <Wt/WTemplate.h>

LambdaSnail::todo::TodoPage::TodoPage(application::Session& session) : m_Session(session)
{
    //m_current_item = new todo; // TODO: Temporary

    //m_current_item =

    // dbo::ptr<User> joe = session.find<User>().where("name = ?").bind("Joe");
    //Wt::Dbo::Transaction transaction(m_session);
    //m_current_item = m_session.find<todo>().where("owner_id = ?").bind(m_session.user().id());

    m_TodoController = std::make_unique<TodoController>(m_Session);

    std::vector<Wt::Dbo::ptr<todo>> todos{};
    m_TodoController->getTodos(todos);
    m_TodoController->setCurrentItem(todos.front());

    auto* t = addNew<Wt::WTemplate>(Wt::WString::tr("todo-page"));
    t->bindNew<TodoView>("todo", m_TodoController.get());
    t->bindNew<TodoSelectionList>("todo-list", m_TodoController.get());


    // Wt::Dbo::Transaction transaction(m_session);
    // m_current_item = m_session.addNew<todo>();
    // m_current_item.modify()->owner = m_session.user();
    //
    // auto item1 = Wt::Dbo::make_ptr<todo_item>();
    // item1.modify()->is_done = true;
    // item1.modify()->text = "Hello TODO";
    //
    //
    // auto item2 = Wt::Dbo::make_ptr<todo_item>();
    // item2.modify()->is_done = false;
    // item2.modify()->text = "Goodbye TODO";
    //
    // m_current_item.modify()->items.insert(item1);
    // m_current_item.modify()->items.insert(item2);
    //

}