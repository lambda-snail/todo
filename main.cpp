#include "src/components/todo_item_view.hpp"
#include "src/components/todo_view.hpp"
#include "src/pages/todo_page.hpp"

#include <Wt/WApplication.h>
#include <Wt/WBootstrap5Theme.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
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

    t->doJavaScript("window.toggleSidebar = function() { const sidebar = document.querySelector('.sidebar'); sidebar.classList.toggle('collapsed'); }");

    m_widget_stack = t->bindWidget("main-content", std::make_unique<Wt::WStackedWidget>());

    // m_button = m_widget_stack->addNew<Wt::WPushButton>("Greet!");
    // m_button->clicked().connect(this, &TodoApplication::showTodoList);

    // auto* item = m_widget_stack->addNew<todo_item>("My TODO Item");
    //  auto* item = m_widget_stack->addWidget(std::move(std::make_unique<todo_item_view>("My TODO
    //  Item", 1)));
    //
    //  item->register_on_checked([]() { std::cout << "checked" << std::endl; });
    //   item->register_on_unchecked([]() { std::cout << "UNchecked" << std::endl; });



    auto* item = m_widget_stack->addWidget(
        std::move(std::make_unique<LambdaSnail::todo::todo_page>()));

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

void TodoApplication::showTodoList() { m_button->setText("Greeted!"); }

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

int main(int argc, char** argv)
{
    /*
     * Your main method may set up some shared resources, but should then
     * start the server application (FastCGI or httpd) that starts listening
     * for requests, and handles all of the application life cycles.
     *
     * The last argument to WRun specifies the function that will instantiate
     * new application objects. That function is executed when a new user surfs
     * to the Wt application, and after the library has negotiated browser
     * support. The function should return a newly instantiated application
     * object.
     */
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        auto app = std::make_unique<TodoApplication>(env);
        app->setTheme(std::make_shared<Wt::WBootstrap5Theme>());
        app->useStyleSheet("resources/style/main-content.css");

        app->messageResourceBundle().use("resources/pages/main-layout");
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
}