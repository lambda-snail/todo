#include <vector>
#include <memory>
#include <optional>
#include <boost/serialization/shared_ptr.hpp>

#include "note.h"

#pragma once

namespace LambdaSnail::Todo {
    class NoteStore {

    public:
        NoteStore();
        explicit NoteStore(std::string_view const& fileName);

        void SaveNotes(std::vector<std::shared_ptr<Note>> const &notes) const;
        std::vector<std::shared_ptr<Note>> LoadNotes();

    private:
        std::string_view m_FileName;
        static std::string_view const s_DefaultFileName;
    };
}
