#include <imgui.h>

#include "ui/noteviewcontroller.h"

#include <format>
#include <source_location>

#include "ui/uiconstants.h"

void LambdaSnail::Todo::Ui::NoteViewController::Render() {
    // Toolbar for notes
    ImGui::Begin("NoteController");
        ImGui::BeginChild("Toolbar", ImVec2(0.f, 128.f), ImGuiChildFlags_Border);
            if(ImGui::Button("New Note"))
            {
                CreateNote("TODO: Type here");
            }
        ImGui::EndChild();

        ImGui::BeginChild("NoteList");

            for (size_t i = 0; i < m_NoteViewModels.size(); ++i)
            {
                auto& note_vm = m_NoteViewModels[i];
                auto const& note = note_vm.GetNote();
                if(ImGui::TreeNode(note->Title.c_str()))
                {
                    for(auto& task : note_vm.GetNote()->Tasks)
                    {
                        ImGui::Checkbox(task.Title.c_str(), &task.bIsDone);
                    }

                    ImGui::TreePop();
                }

                if (ImGui::BeginPopupContextItem())
                {
                    if (ImGui::Button("Show/Hide Note"))
                    {
                        note_vm.SetOpen(!note_vm.IsOpen());
                        ImGui::CloseCurrentPopup();
                    }

                    if(ImGui::Button("Delete Note"))
                    {
                        m_CommandQueue.emplace(NoteCommand{ .Command = NoteCommand::CommandType::Delete, .NoteIndex = i });
                    }

                    ImGui::EndPopup();
                }
            }
        ImGui::EndChild();
    ImGui::End();

    while(not m_CommandQueue.empty())
    {
        auto&[Command, NoteIndex] = m_CommandQueue.front();
        m_CommandQueue.pop();

        switch(Command)
        {
            case NoteCommand::CommandType::Delete:
                m_NoteViewModels.erase(std::next(m_NoteViewModels.cbegin(), static_cast<std::iter_difference_t<std::vector<NoteViewModel>::iterator>>(NoteIndex)));
                break;
            default:
                std::source_location location{};
                throw std::exception( std::format("Error: Unexpected default case reached in file {}:{}", location.file_name(), location.line()).c_str() );
        }
    }

    for(auto& note : m_NoteViewModels) {
        note.Render();
    }
}

LambdaSnail::Todo::Ui::NoteViewController::~NoteViewController()
{
    if(not m_NoteViewModels.empty())
    {
        p_NoteStore->SaveNotes(m_Notes);
    }
}

void LambdaSnail::Todo::Ui::NoteViewController::CreateNote(std::string_view const& text)
{
    static int next_id = 0; // TODO: This needs to be serialized as well

    auto id = next_id++;
    auto created_note = std::make_shared<Note>(id, text.data(), std::format("Note with id: {}", id));

    m_Notes.push_back(created_note);
    m_NoteViewModels.emplace_back( created_note );
}

void LambdaSnail::Todo::Ui::NoteViewController::Init() {
    m_Notes = p_NoteStore->LoadNotes(); //TODO: Change VM to point to a note in here
    for(auto const& note : m_Notes) {
        m_NoteViewModels.emplace_back( note );
    }
}
