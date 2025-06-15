#include "pages/authentication_page.hpp"
#include "src/application/session.hpp"
#include "src/components/todo_item_view.hpp"
#include "src/components/todo_view.hpp"
#include "src/pages/todo_page.hpp"

#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/FacebookService.h>
#include <Wt/Auth/GoogleService.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Dbo/Exception.h>
#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WServer.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WTemplate.h>

class TodoApplication final : public Wt::WApplication
{
  public:
    explicit TodoApplication(const Wt::WEnvironment& env);

  private:
    Wt::WStackedWidget* m_widget_stack;

    Wt::WPushButton* m_button;

    void showTodoList();

    void handleInternalPath(std::string const& path);
};

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
 */
TodoApplication::TodoApplication(const Wt::WEnvironment& env) : WApplication(env)
{
    setTitle("Hello world"); // application title

    auto t = std::make_unique<Wt::WTemplate>(Wt::WString::tr("main-layout"));

    // m_button = t->bindWidget("greeting-button", std::make_unique<Wt::WPushButton>("Greet!"));
    //  m_button->clicked().connect(this, &TodoApplication::showTodoList);

    t->doJavaScript("window.toggleSidebar = function() { const sidebar = "
                    "document.querySelector('.sidebar'); sidebar.classList.toggle('collapsed'); }");

    m_widget_stack = t->bindWidget("main-content", std::make_unique<Wt::WStackedWidget>());

    // m_button = m_widget_stack->addNew<Wt::WPushButton>("Greet!");
    // m_button->clicked().connect(this, &TodoApplication::showTodoList);

    // auto* item = m_widget_stack->addNew<todo_item>("My TODO Item");
    //  auto* item = m_widget_stack->addWidget(std::move(std::make_unique<todo_item_view>("My TODO
    //  Item", 1)));
    //
    //  item->register_on_checked([]() { std::cout << "checked" << std::endl; });
    //   item->register_on_unchecked([]() { std::cout << "UNchecked" << std::endl; });

    auto* item =
        m_widget_stack->addWidget(std::move(std::make_unique<LambdaSnail::todo::todo_page>()));

    m_widget_stack->setCurrentWidget(item);

    // WApplication::instance()->internalPathChanged().connect(
    //     this, &TodoApplication::handleInternalPath);

    root()->addWidget(std::move(t));

    // root()->addWidget(std::make_unique<Wt::WText>("Your name, please ? ")); //
    // show some text
    //
    // nameEdit_ = root()->addWidget(std::make_unique<Wt::WLineEdit>()); // allow
    // text input nameEdit_->setFocus();                              // give
    // focus
    //
    // auto button = root()->addWidget(std::make_unique<Wt::WPushButton>("Greet
    // me."));
    //                                                     // create a button
    // button->setMargin(5, Wt::Side::Left);                   // add 5 pixels
    // margin
    //
    // root()->addWidget(std::make_unique<Wt::WBreak>());    // insert a line
    // break greeting_ = root()->addWidget(std::make_unique<Wt::WText>()); //
    // empty text
    //
    // /*
    //  * Connect signals with slots
    //  *
    //  * - simple Wt-way: specify object and method
    //  */
    // button->clicked().connect(this, &HelloApplication::greet);
    //
    // /*
    //  * - using an arbitrary function object, e.g. useful to bind
    //  *   values with std::bind() to the resulting method call
    //  */
    // nameEdit_->enterPressed().connect(std::bind(&HelloApplication::greet,
    // this));
    //
    // /*
    //  * - using a lambda:
    //  */
    // button->clicked().connect([this]() {
    //     std::cerr << "Hello there, " << nameEdit_->text() << std::endl;
    // });
}

void TodoApplication::handleInternalPath(std::string const& path)
{
    // if (session_.login().loggedIn()) {
    if (path == "/list") {
        // m_widget_stack->setCurrentWidget();
    }

    else
        WApplication::instance()->setInternalPath("/play", true);
    //}
}

// TODO: Merge into todo application
class AuthApplication : public Wt::WApplication
{
  public:
    explicit AuthApplication(const Wt::WEnvironment& env,
                             Wt::Auth::AuthService& auth_service,
                             Wt::Auth::PasswordService& password_service,
                             std::vector<std::unique_ptr<Wt::Auth::OAuthService>>& oauth_services)
        : Wt::WApplication(env),
          m_session(appRoot() + "auth.db", auth_service, password_service, oauth_services)
    {
        m_session.login().changed().connect(this, &AuthApplication::authEvent);
        WApplication::instance()->internalPathChanged().connect(
            this, &AuthApplication::handleInternalPath);

        // root()->addStyleClass("container");

        auto auth_page = std::make_unique<LambdaSnail::todo::pages::authentication_page>(m_session);

        auth_page->model()->addPasswordAuth(&m_session.password_auth());
        auth_page->model()->addOAuth(m_session.oauth());
        auth_page->setRegistrationEnabled(true);
        auth_page->processEnvironment();

        root()->addWidget(std::move(auth_page));
    }

    void setUpAuthenticatedContent()
    {
        auto t = std::make_unique<Wt::WTemplate>(Wt::WString::tr("main-layout"));

        t->doJavaScript("window.toggleSidebar = function() { const sidebar = "
                        "document.querySelector('.sidebar'); "
                        "sidebar.classList.toggle('collapsed'); }");

        m_widget_stack = t->bindWidget("main-content", std::make_unique<Wt::WStackedWidget>());

        auto* item =
            m_widget_stack->addWidget(std::move(std::make_unique<LambdaSnail::todo::todo_page>()));

        m_widget_stack->setCurrentWidget(item);

        root()->clear();
        root()->addWidget(std::move(t));
    }

    void authEvent()
    {
        if (m_session.login().loggedIn()) {
            setInternalPath("/list", true);
            const Wt::Auth::User& u = m_session.login().user();
            log("notice") << "User " << u.id() << " (" << u.identity(Wt::Auth::Identity::LoginName)
                          << ")"
                          << " logged in.";

            //setUpAuthenticatedContent();
        } else
            log("notice") << "User logged out.";
    }

    void handleInternalPath(std::string const& path)
    {
        log("path") << path;

        setUpAuthenticatedContent();

        // // if (session_.login().loggedIn()) {
        // if (path == "/list") {
        //     // m_widget_stack->setCurrentWidget();
        // }
        //
        // else
        //     WApplication::instance()->setInternalPath("/play", true);
        // //}
    }

  private:
    LambdaSnail::todo::application::Session m_session;

    Wt::WStackedWidget* m_widget_stack;
};

// TODO: Find some better place to put this
void configure_auth(Wt::Auth::AuthService& auth_service,
                    Wt::Auth::PasswordService& password_service,
                    std::vector<std::unique_ptr<Wt::Auth::OAuthService>>& oauth_services)
{
    auth_service.setAuthTokensEnabled(true, "logincookie");
    auth_service.setEmailVerificationEnabled(true);

    // TODO: Only for testing
    auth_service.setEmailVerificationRequired(false);

    auto verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
    verifier->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>(12));
    password_service.setVerifier(std::move(verifier));
    password_service.setPasswordThrottle(std::make_unique<Wt::Auth::AuthThrottle>());
    password_service.setStrengthValidator(std::make_unique<Wt::Auth::PasswordStrengthValidator>());

    if (Wt::Auth::GoogleService::configured()) {
        oauth_services.push_back(std::make_unique<Wt::Auth::GoogleService>(auth_service));
    }

    if (Wt::Auth::FacebookService::configured()) {
        oauth_services.push_back(std::make_unique<Wt::Auth::FacebookService>(auth_service));
    }

    for (const auto& oAuthService : oauth_services) {
        oAuthService->generateRedirectEndpoint();
    }
}

// <label for="${id:favourite-pet}">Favourite pet:
//                     ${name class="Wt-info"}
// </label>
// ${favourite-pet}

int main(int argc, char** argv)
{
    Wt::Auth::AuthService auth_service;
    Wt::Auth::PasswordService password_service(auth_service);
    std::vector<std::unique_ptr<Wt::Auth::OAuthService>> oauth_services;

    configure_auth(auth_service, password_service, oauth_services);

    try {
        Wt::WServer server{argc, argv, WTHTTP_CONFIGURATION};

        server.addEntryPoint(Wt::EntryPointType::Application, [&](const Wt::WEnvironment& env) {
            // auto app = std::make_unique<TodoApplication>(env);
            auto app = std::make_unique<AuthApplication>(
                env, auth_service, password_service, oauth_services);

            app->setTheme(std::make_shared<Wt::WBootstrap5Theme>());
            app->useStyleSheet("resources/style/main-content.css");

            app->messageResourceBundle().use("resources/pages/main-layout");
            app->messageResourceBundle().use("resources/pages/auth");
            app->messageResourceBundle().use("resources/pages/todo");

            app->messageResourceBundle().use("resources/components/todo-components");

            // // resolve a string using the resource bundle
            // auto welcome = std::make_unique<Wt::WText>(
            //                  tr("welcome-text").arg("Bart"));

            /*
             * You could read information from the environment to decide whether
             * the user has permission to start a new application
             */
            return std::move(app);
        });

        server.run();
    } catch (Wt::WServer::Exception& e) {
        std::cerr << e.what() << '\n';
    } catch (Wt::Dbo::Exception& e) {
        std::cerr << "Dbo exception: " << e.what() << '\n';
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << '\n';
    }
}