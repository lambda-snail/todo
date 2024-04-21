#include "note/notestore.h"

#include <fstream>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace LambdaSnail::Todo {

    std::string_view const NoteStore::s_DefaultFileName = "notes.data";

    NoteStore::NoteStore()
    {
        m_FileName = s_DefaultFileName;
    }

    NoteStore::NoteStore(std::string_view const &fileName)
    {
        if(fileName.empty())
        {
            m_FileName = s_DefaultFileName;
        }
    }

    void NoteStore::SaveNotes(std::vector<std::shared_ptr<Note>> const &notes) const
    {
        std::ofstream ofs(m_FileName.data());
        boost::archive::text_oarchive oa(ofs);
        oa << notes;
    }

    std::vector<std::shared_ptr<Note>> NoteStore::LoadNotes()
    {
        std::vector<std::shared_ptr<Note>> notes{};
        std::ifstream ifs(m_FileName.data());
        if(ifs.good() and ifs.peek() != std::ifstream::traits_type::eof())
        {
            boost::archive::text_iarchive ia(ifs);
            ia >> notes;
        }

        return notes;
    }
}
