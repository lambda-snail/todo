#include "authentication_page.hpp"

#include "registration_view.hpp"

LambdaSnail::todo::pages::authentication_page::authentication_page(application::Session& session)
    : AuthWidget(session.auth(), session.users(), session.login()), m_session(session)
{
}

std::unique_ptr<Wt::WWidget>
LambdaSnail::todo::pages::authentication_page::createRegistrationView(Wt::Auth::Identity const& id)
{
    // auto model = createRegistrationModel();
    //
    // if (id.isValid())
    //     model->registerIdentified(id);
    //
    // std::unique_ptr<Wt::Auth::RegistrationWidget> w(new Wt::Auth::RegistrationWidget(this));
    // w->setModel(std::move(model));
    // return w;

    Wt::log("info") << "create registration view: " << id.id();

    auto registrationView = std::make_unique<registration_view>(m_session, this);
    std::unique_ptr<Wt::Auth::RegistrationModel> model = createRegistrationModel();

    if (id.isValid())
    {
        model->registerIdentified(id);
    }

    registrationView->setModel(std::move(model));

    // This is required otherwise the modal will not show up (due to a display:none that is not
    // cleared by the current built-in widget)
    registrationView->show();

    return std::move(registrationView);
}