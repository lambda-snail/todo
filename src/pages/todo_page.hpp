#pragma once

#include "../models/todo.hpp"
#include "application/session.hpp"

#include <Wt/WContainerWidget.h>

namespace LambdaSnail::todo
{
    class todo_page : public Wt::WContainerWidget
    {
    public:
        explicit todo_page(application::Session& session);

    private:
        application::Session& m_session;
        Wt::Dbo::ptr<todo> m_current_item;
    };
}