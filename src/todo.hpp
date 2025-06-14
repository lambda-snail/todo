#pragma once

#include <string>
#include <utility>
#include <vector>

namespace LambdaSnail::todo
{
    typedef size_t id_t;

    struct todo_item
    {
        explicit todo_item(id_t id, std::string  text, bool is_done) : id(id), text(std::move(text)), is_done(is_done) {}

        id_t id;
        std::string text;
        bool is_done { false };
    };

    struct todo
    {
        explicit todo(id_t id) : m_id(id) {}

        id_t m_id;
        std::vector<todo_item> items{};
    };
}