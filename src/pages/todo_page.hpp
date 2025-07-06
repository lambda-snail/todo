#pragma once

#include "../models/todo.hpp"
#include "application/session.hpp"

#include <Wt/WContainerWidget.h>

namespace LambdaSnail::todo
{
class TodoController;
}
namespace LambdaSnail::todo
{
    class TodoPage : public Wt::WContainerWidget
    {
    public:
        explicit TodoPage(application::Session& session);

        void setCurrentItem(Wt::Dbo::ptr<todo> item);

    private:
        application::Session& m_Session;
        Wt::Dbo::ptr<todo> m_CurrentItem;

        std::unique_ptr<TodoController> m_TodoController;
    };
}