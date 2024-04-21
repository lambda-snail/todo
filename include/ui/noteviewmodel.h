#pragma once

#include <array>
#include <memory>
#include "note/note.h"

namespace LambdaSnail::Todo::Ui {

    template<size_t Size = 256>
    struct EditTaskInfo {
        explicit EditTaskInfo(size_t index) : NoteIndex(index) {}

        size_t NoteIndex;
        std::array<char, Size> Buffer {};
    };

    class NoteViewModel {
    public:
        NoteViewModel() = delete;
        explicit NoteViewModel(std::shared_ptr<Note> note) : m_Note(std::move(note))
        {
            memcpy(m_EditBuffer.data(), m_Note->Text.c_str(), std::min(m_Note->Text.size(), m_EditBuffer.size()));
        };

        void Render();

        [[nodiscard]] bool IsDirty() const;
        void SetDirty(bool isDirty);

        [[nodiscard]] bool IsOpen() const;
        void SetOpen(bool isOpen);

        [[nodiscard]] std::shared_ptr<Note> GetNote() const;

    private:
        std::shared_ptr<Note> m_Note;
        std::array<char, 2048> m_EditBuffer {};// Buffer for displaying and editing the characters on the screen

        std::unique_ptr<EditTaskInfo<256>> p_EditTaskInfo;

        bool bIsDirty { false };
        bool bIsOpen { true };
    };
}