#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QPushButton>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QLineEdit>
#include <list>
#include <map>
#include <string>

class Launcher : public QWidget {
public:
    Launcher(std::map<std::string, int> map, int *retValue);
private:
    int* retValue;
public slots:
    void setValue(std::string id);
};

#endif // LAUNCHER_H
