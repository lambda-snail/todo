#pragma once

#include <Wt/Dbo/Dbo.h>

#include <Wt/WDateTime.h>
#include <string>

namespace LambdaSnail::todo
{
namespace application
{
class user;
}
typedef size_t id_t;

    struct todo_item : public Wt::Dbo::Dbo<todo_item>
    {
        std::string text;
        bool is_done { false };
        Wt::Dbo::ptr<class todo> todo;

        template<class Action>
        void persist(Action& a)
        {
            Wt::Dbo::field(a, text,     "text");
            Wt::Dbo::field(a, is_done,  "is_done");
            Wt::Dbo::belongsTo(a, todo, "todo");
        }
    };

    struct todo : public Wt::Dbo::Dbo<todo>
    {
        std::string title;
        std::string description;
        Wt::WDateTime modified;

        Wt::Dbo::collection<Wt::Dbo::ptr<todo_item>> items;
        Wt::Dbo::ptr<application::user> owner;

        template<class Action>
        void persist(Action& a)
        {
            Wt::Dbo::field(a, title,        "title");
            Wt::Dbo::field(a, description,  "description");
            Wt::Dbo::field(a, modified, "modified");

            Wt::Dbo::hasMany(a,     items, Wt::Dbo::ManyToOne, "todo");
            Wt::Dbo::belongsTo(a,   owner, "owner");
        }
    };
}