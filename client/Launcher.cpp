#include <sstream>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include "client/Launcher.h"


Launcher::Launcher(std::map<std::string, int> races,
        std::map<int, std::string> botNames, int *ret, int *bot) :
        retValue(ret), playwithbot(bot) {
    mainLayout =  new QVBoxLayout();

    setImage();
    setCreateBtn();
    setBots(botNames);
    setExistingRaces(races);

    this->setLayout(mainLayout);
}

void Launcher::setCreateBtn() {
    QPushButton *createGameBtn = new QPushButton("Create Game");
    connect(createGameBtn, &QPushButton::clicked, this, [this]() { toggleRace("0"); });
    mainLayout->addWidget(createGameBtn);
}

void Launcher::setImage() {
    QLabel *img = new QLabel;
    QPixmap pixmap("client/img/logo.png");
    img->setPixmap(pixmap);
    img->show();
    mainLayout->addWidget(img);
}

void Launcher::setBots(std::map<int, std::string> botNames) {
    QToolButton* botDropdown = new QToolButton;
    botDropdown->setText("Play with bot");
    botDropdown->setPopupMode(QToolButton::InstantPopup);
    QMenu* botMenu = new QMenu;
    for (auto &b : botNames) {
        QAction* qa = new QAction(b.second.c_str());
        botMenu->addAction(qa);
        connect(qa, &QAction::triggered, this,
                [this, b, botDropdown]() { toggleBot(b, botDropdown); });
    }
    botDropdown->setMenu(botMenu);
    mainLayout->addWidget(botDropdown);
}

void Launcher::setExistingRaces(std::map<std::string, int> races) {
    QGridLayout *existingGames = new QGridLayout();
    for (std::pair<const std::string, int> &p : races) {
        std::ostringstream str;
        str << "Join Game #" << p.first << " (" << p.second << " players)";
        std::string label = str.str();
        QPushButton *btn = new QPushButton(label.c_str());
        connect(btn, &QPushButton::clicked, this,
                [this, p]() { toggleRace(p.first); });
        existingGames->addWidget(btn);
    }
    mainLayout->addLayout(existingGames);
}


void Launcher::toggleRace(std::string id) {
    *retValue = stoi(id);
    this->close();
}

void Launcher::toggleBot(std::pair<const int, std::basic_string<char>> n, QToolButton *btn) {
    *playwithbot = n.first;
    btn->setText(n.second.c_str());
}
