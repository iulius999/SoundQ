#include <QtWidgets/QApplication>
#include <fstream>
#include "GUI/AdminWindow.h"
#include "GUI/ListenerWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Playlist playlist("songs.txt");
    Playlist waitingList("proposed.txt");
    Service service(playlist, waitingList);

    std::vector<User> users = service.getAllUsers("users.txt");
    std::vector<std::unique_ptr<AdminWindow>> admins;
    std::vector<std::unique_ptr<ListenerWindow>> listeners;

    for (User u : users) {
        if (u.getIsAdmin()) {
            admins.push_back(std::make_unique<AdminWindow>(service, u));
        }
        else {
            listeners.push_back(std::make_unique<ListenerWindow>(service, u));
        }
    }

    return a.exec();
}