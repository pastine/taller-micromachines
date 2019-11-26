#include <sstream>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>
#include <QtWidgets/QSpinBox>
#include "client/Launcher.h"


Launcher::Launcher(std::map<std::string, std::tuple<int, int>> races,
                   std::map<int, std::string> botNames, int *ret,
                   int *players, int *bot, std::string *name) :
        retValue(ret), playwithbot(bot), maxPlayers(players), inputName(name) {
    mainLayout =  new QVBoxLayout();
    footerLayout = new QHBoxLayout();

    setImage();
    setCreateBtn();
    setExistingRaces(races);
    setBots(botNames);
    footerLayout->addStretch();
    setInput(name);

    mainLayout->addLayout(footerLayout);
    this->setLayout(mainLayout);
}

void Launcher::setCreateBtn() {
    QHBoxLayout *createLayout = new QHBoxLayout();
    QPushButton *createGameBtn = new QPushButton("Create Game");
    QSpinBox *numberPlayers = new QSpinBox();
    numberPlayers->setValue(4);
    numberPlayers->setMinimum(1);
    connect(numberPlayers, QOverload<int>::of(&QSpinBox::valueChanged),
            [=](int i) { *maxPlayers = i; });
    connect(createGameBtn, &QPushButton::clicked, this, [this]() {
        toggleRace("0");
        quit();
    });
    createLayout->addWidget(createGameBtn, 2);
    createLayout->addWidget(numberPlayers);
    mainLayout->addLayout(createLayout);
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
    footerLayout->addWidget(botDropdown);
}

void Launcher::setExistingRaces(std::map<std::string, std::tuple<int, int>> races) {
    QGridLayout *existingGames = new QGridLayout();
    for (auto &p : races) {
        std::ostringstream str;
        str << "Join Game #" << p.first << " (" << std::get<0>(p.second) << "/";
        str << std::get<1>(p.second) << " players)";
        std::string label = str.str();
        QPushButton *btn = new QPushButton(label.c_str());
        connect(btn, &QPushButton::clicked, this,
                [this, p]() { toggleRace(p.first); quit(); });
        existingGames->addWidget(btn);
    }
    mainLayout->addLayout(existingGames);
}


void Launcher::toggleRace(std::string id) {
    *retValue = stoi(id);
}

void Launcher::toggleBot(std::pair<const int, std::basic_string<char>> n, QToolButton *btn) {
    *playwithbot = n.first;
    btn->setText(n.second.c_str());
}

void Launcher::setInput(std::string *name) {
    input = new QLineEdit(name->c_str());
    input->setAlignment(Qt::AlignRight);
    footerLayout->addWidget(input);
}

void Launcher::quit() {
    std::string s = input->text().toStdString();
    *inputName = s;
    this->close();
}
