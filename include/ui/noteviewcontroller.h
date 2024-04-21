#pragma once

#include <queue>

#include "ui/noteviewmodel.h"
#include "component.h"

namespace LambdaSnail::Todo::Ui {

    struct NoteCommand {
        enum class CommandType {
            Delete = 0
        } Command;

        size_t NoteIndex;
    };

    class NoteViewController : public Component {

    public:
        explicit NoteViewController(std::unique_ptr<NoteStore> store) : p_NoteStore(std::move(store)) {}

        void Init() override;

        void Render() override;

        ~NoteViewController() override;;
    private:
        std::unique_ptr<NoteStore> p_NoteStore;
        std::vector<NoteViewModel> m_NoteViewModels{};
        std::vector<std::shared_ptr<Note>> m_Notes{};

        std::queue<NoteCommand> m_CommandQueue {};

        bool bIsOpen { true };

        void CreateNote(std::string_view const& text);
    };

}