#include <appman.hpp>
#include <stdio.h>

ApplicationManager &ApplicationManager::get_instance(){
    static ApplicationManager instance;
    return instance;
}

void ApplicationManager::pushApp(App *app){
    this->_Apps.insert(make_pair(app->id, app));
}

void ApplicationManager::listApps(){
    for(auto i : this->_Apps){
        printf("ID: %d, NAME: %s\n", i.second->id, i.second->name);
    }
}

int ApplicationManager::popApp(unsigned int id){
    // Application erased succesfully
    if(this->_Apps.find(id) != this->_Apps.end()){
        this->_Apps.erase(id);
        return 0;
    }
    // Application not found
    return 1;
}
