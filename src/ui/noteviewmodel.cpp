#include <array>
#include <format>

#include <imgui.h>
#include "ui/noteviewmodel.h"

#include "ui/uihelpers.h"

bool LambdaSnail::Todo::Ui::NoteViewModel::IsDirty() const
{
    return bIsDirty;
}

void LambdaSnail::Todo::Ui::NoteViewModel::SetDirty(bool isDirty)
{
    bIsDirty = isDirty;
}

bool LambdaSnail::Todo::Ui::NoteViewModel::IsOpen() const
{
    return bIsOpen;
}

void LambdaSnail::Todo::Ui::NoteViewModel::SetOpen(bool isOpen)
{
    bIsOpen = isOpen;
}

std::shared_ptr<LambdaSnail::Todo::Note> LambdaSnail::Todo::Ui::NoteViewModel::GetNote() const
{
    return m_Note;
}

void LambdaSnail::Todo::Ui::NoteViewModel::Render()
{
    int flags{ ImGuiWindowFlags_None };
    if (bIsDirty)
    {
        flags |= ImGuiWindowFlags_UnsavedDocument;
    }

    if (not bIsOpen)
    {
        return;
    }

    ImGui::Begin(m_Note->Title.data(), &bIsOpen, flags);
    bool bChangedThisFrame = false;
    bChangedThisFrame = ImGui::InputTextMultiline("##",
                                                  m_EditBuffer.data(),
                                                  m_EditBuffer.size(),
                                                  { ImGui::GetContentRegionAvail().x, NoteTextRegionHeight * UiHelpers::GetDpiScaleFactor() },
                                                  ImGuiInputTextFlags_AllowTabInput
    );

    if (ImGui::Button("Add Task"))
    {
        m_Note->Tasks.emplace_back("asd");
    }

    for (int i = 0; i < m_Note->Tasks.size(); ++i)
    {
        auto& task = m_Note->Tasks[i];

        bChangedThisFrame |= ImGui::Checkbox(task.Title.c_str(), &task.bIsDone);

        // If we are in edit mode, but not editing this task, then go on to the next
        if(p_EditTaskInfo and p_EditTaskInfo->NoteIndex != i)
        {
            continue;
        }

        // If we get here then we are either not editing currently, or
        // we are editing the current task
        if (ImGui::BeginPopupContextItem())
        {
            ImGui::Text("Edit Task Title");

            if (not p_EditTaskInfo)
            {
                p_EditTaskInfo = std::make_unique<EditTaskInfo<EditTaskInfoBufferSize>>(i);
                memcpy(p_EditTaskInfo->Buffer.data(), task.Title.c_str(), std::min(p_EditTaskInfo->Buffer.size(), task.Title.size()));
            }

            ImGui::InputText("TaskTitleEditor", p_EditTaskInfo->Buffer.data(), p_EditTaskInfo->Buffer.size());
            if (ImGui::Button("Ok"))
            {
                task.Title = p_EditTaskInfo->Buffer.data();
                p_EditTaskInfo.reset();
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Button("Cancel"))
            {
                p_EditTaskInfo.reset();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }

    bIsDirty = bIsDirty || bChangedThisFrame;

    ImGui::End();
}
