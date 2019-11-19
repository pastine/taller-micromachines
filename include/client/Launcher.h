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
#include <string>

class Launcher : public QWidget {
public:
    Launcher(std::map<std::string, int> map, int *retValue, bool *playwithbot);

private:
    int *retValue;
    bool *playwithbot;
public slots:

    void setValue(std::string id);

    void toggleBot();
};

#endif // LAUNCHER_H
