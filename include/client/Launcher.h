#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QPushButton>
#include <qt5/QtWidgets/QRadioButton>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QLineEdit>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <utility>

class Launcher : public QWidget {
public:
    Launcher(std::map<std::string, int> map,
            std::map<int, std::string> botNames, int *retValue, int *playwithbot);

private:
    int *retValue;
    QVBoxLayout *mainLayout;
    int *playwithbot;
public slots:

    void toggleRace(std::string id);

    void toggleBot(std::pair<const int, std::basic_string<char>> n, QToolButton *pButton);

    void setBots(std::map<int, std::string> map);

    void setImage();

    void setCreateBtn();

    void setExistingRaces(std::map<std::string, int> map);
};

#endif // LAUNCHER_H
