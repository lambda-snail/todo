
//#include <Wt/WAbstractListModel.h>

#include "todo_view.hpp"
#include "todo_item_view.hpp"

#include <Wt/WTemplate.h>

LambdaSnail::todo::todo_view::todo_view(todo& item) : m_item(item)
{
    auto* t = addNew<Wt::WTemplate>(Wt::WString::tr("todo-view"));

    t->bindString("title", m_item.title);
    t->bindString("description", m_item.description);
    t->bindString("last-updated", m_item.modified.toString()); // TODO: "A few moments ago"
    auto* list_t = t->bindNew<Wt::WTemplate>("item-list", Wt::WString::tr("todo-list"));

    auto container = std::make_unique<Wt::WContainerWidget>();
    for (auto const& todo : item.items) {
        auto* view = container->addNew<todo_item_view>(todo->id(), todo->text, todo->is_done);

        view->register_on_checked([]() { std::cout << "Checked" << std::endl; });
        view->register_on_unchecked([]() { std::cout << "Unchecked" << std::endl; });

        //m_todo_views.push_back( view );
    }

    m_ItemContainer = list_t->bindWidget<Wt::WContainerWidget>("items", std::move(container));
}

void LambdaSnail::todo::todo_view::add_item(todo_item_view* item)
{

}

void LambdaSnail::todo::todo_view::remove_item(Wt::Dbo::ptr<todo_item> const& item)
{
    // auto const view_it = std::ranges::find_if(m_todo_views.begin(), m_todo_views.end(), [item](todo_item_view const* view)
    // {
    //     return view->get_id() == item->id();
    // });
    //
    // if (view_it == m_todo_views.end()) {
    //     return;
    // }
    //
    // m_item.items.erase(item);
    // m_todo_views.erase(view_it);
    //
    // refresh();
}