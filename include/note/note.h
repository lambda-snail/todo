#pragma once

#include <string>
#include <utility>
#include <vector>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>

//BOOST_CLASS_TRACKING(Note, track_never)

namespace LambdaSnail::Todo
{
    typedef uint32_t note_id_t;

    struct SimpleTask {
        explicit SimpleTask() = default;

        explicit SimpleTask(std::string_view const &title, bool done = false) : Title(title), bIsDone(done) {}

        SimpleTask(const SimpleTask &simple_task) = default;

        SimpleTask(SimpleTask &&simple_task) noexcept
        {
            Title = std::move(simple_task.Title);
            bIsDone = simple_task.bIsDone;
        }

        note_id_t Id{};
        std::string Title;
        bool bIsDone{false};

        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int file_version)
        {
            ar & Id;
            ar & Title;
            ar & bIsDone;
        }
    };

    struct Note {
        note_id_t NoteId{};
        std::string Text{};
        std::string Title{};

        explicit Note() = default;
        Note(note_id_t id, std::string  text, std::string  title) : NoteId(id), Text(std::move(text)), Title(std::move(title)) {}

        std::vector<SimpleTask> Tasks;

        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &ar, unsigned int const file_version);
    };

    template<class Archive>
    void Note::serialize(Archive &ar, unsigned int const file_version)
    {
        ar & NoteId;
        ar & Text;
        ar & Title;
        ar & Tasks;
    }
}
