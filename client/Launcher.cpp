#include "client/Launcher.h"
#include "client/ui_Launcher.h"

Launcher::Launcher(QMainWindow *parent) : QMainWindow(parent) {
    Ui::Launcher launcher;
    launcher.setupUi(this);
}
