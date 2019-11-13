#include <sstream>
#include "client/Launcher.h"


Launcher::Launcher(std::map<std::string, int> races, int* ret) : retValue(ret) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QPushButton* createGameBtn = new QPushButton("Create Game");
    QLabel* img = new QLabel;
    QPixmap pixmap("client/img/logo.png");
    img->setPixmap(pixmap);
    mainLayout->addWidget(img);
    mainLayout->addWidget(createGameBtn);
    QGridLayout* existingGames = new QGridLayout();
    img->show();
    mainLayout->addLayout(existingGames);
    connect(createGameBtn, &QPushButton::clicked, this, [this]() {setValue("0"); });
    for (std::pair<const std::string, int> p : races) {
        std::ostringstream str;
        str << "Join Game #" << p.first << " (" << p.second << " players)";
        std::string label = str.str();
        QPushButton* btn = new QPushButton(label.c_str());
        connect(btn, &QPushButton::clicked, this,
                [this, p]() {setValue(p.first);});
        existingGames->addWidget(btn);
    }
    this->setLayout(mainLayout);
}

void Launcher::setValue(std::string id) {
    *retValue = stoi(id);
    this->close();
}


