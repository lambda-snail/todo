#pragma once

#include <Wt/Dbo/ptr.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>

namespace LambdaSnail::todo
{

class todo;

class TodoSelectionListItem : public Wt::WTemplate
//class TodoSelectionListItem : public Wt::WContainerWidget
{
  public:
    explicit TodoSelectionListItem(Wt::Dbo::ptr<todo> todo);

    void setSelected(bool isSelected);
    bool isSelected() const { return hasStyleClass("active"); }
    Wt::Dbo::ptr<todo> getTodo() const { return m_Todo; }
    Wt::Signal<TodoSelectionListItem*>& OnSelected() { return signal_OnSelected; }

    // Wt::DomElementType domElementType() const override { return Wt::DomElementType::LI; }

private:
    Wt::Dbo::ptr<todo> m_Todo;
    Wt::Signal<TodoSelectionListItem*> signal_OnSelected{};

    std::string m_ElementId;
};

}