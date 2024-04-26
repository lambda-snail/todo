#include "core/application.h"

#include <imgui.h>

void LambdaSnail::Todo::Core::Application::Render() {
// #ifdef IMGUI_HAS_VIEWPORT
//     ImGuiViewport const* viewport = ImGui::GetMainViewport();
//     ImGui::SetNextWindowPos(viewport->Pos);
//     ImGui::SetNextWindowSize(viewport->Size);
//     ImGui::SetNextWindowViewport(viewport->ID);
// #else
//     ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
//     ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
// #endif
//     ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
//     //ImGui::Begin(..., ..., ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

    for(auto const& view : m_Views) {
        view->Render();
        bShouldClose = view->CloseWindow();
    }

    //ImGui::End();
    //ImGui::PopStyleVar(1);
}

void LambdaSnail::Todo::Core::Application::AddComponent(std::unique_ptr<Component> view) {
    m_Views.push_back(std::move(view));
}

bool LambdaSnail::Todo::Core::Application::ShouldCloseApplication() const {
    return bShouldClose;
}
