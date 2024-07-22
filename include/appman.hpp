#ifndef APP_MAN
#define APP_MAN

#include <map>
#include <memory>
using namespace std;

struct App{
    unsigned int id;
    unsigned int category;
    const char* name;
    const char* icon_path;
    const char* executable_path;
    const char* startup_parameters;
};

class ApplicationManager{
protected:
    ApplicationManager() = default;

    map <unsigned int, App*> _Apps;

public:
    static ApplicationManager& get_instance();

    ApplicationManager(const ApplicationManager&) = delete;
    ApplicationManager(ApplicationManager&&) = delete;
    ApplicationManager& operator=(const ApplicationManager&) = delete;
    ApplicationManager& operator=(ApplicationManager&) = delete;


    void pushApp(App *app);
    void listApps();
    int popApp(unsigned int id);
};

#endif