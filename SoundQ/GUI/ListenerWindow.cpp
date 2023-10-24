#include "ListenerWindow.h"

ListenerWindow::ListenerWindow(Service& serv, User& u, QWidget *parent)
	: QMainWindow(parent), service(serv), user(u)
{
	ui.setupUi(this);
	service.subscribe(this);

	this->setWindowTitle(QString::fromStdString(user.getName()));

	this->configureCentralWidget();
	this->configureLeftLayout();
	this->configureRightLayout();

	this->show();
}

ListenerWindow::~ListenerWindow()
{
	delete songProposer;
	delete rightLayout;

	delete searchEdit;
	delete searchLabel;
	delete searchLayout;
	delete songSearcher;

	delete musicPlayer;
	delete leftLayout;

	delete mainLayout;
	delete centralWidget;
}

void ListenerWindow::update()
{
	searchEdit->clear();
	musicPlayer->populateWithSongs("");
	musicPlayer->showRemoveButtons(false);
}

void ListenerWindow::configureCentralWidget()
{
	centralWidget = new QWidget(this);
	this->setCentralWidget(centralWidget);

	mainLayout = new QHBoxLayout(centralWidget);
}

void ListenerWindow::configureLeftLayout()
{
	leftLayout = new QVBoxLayout();

	musicPlayer = new MusicPlayer(service);
	musicPlayer->showRemoveButtons(false);
	leftLayout->addWidget(musicPlayer);

	this->configureSongSearcher();

	mainLayout->addLayout(leftLayout);
}

void ListenerWindow::configureRightLayout()
{
	rightLayout = new QVBoxLayout();

	songProposer = new SongAdder(service);
	songProposer->showAddButton(false);
	rightLayout->addWidget(songProposer);

	mainLayout->addLayout(rightLayout);
}

void ListenerWindow::configureSongSearcher()
{
	songSearcher = new QWidget();
	searchLayout = new QFormLayout(songSearcher);

	searchLabel = new QLabel("Search");
	searchEdit = new QLineEdit();

	searchLayout->addRow(searchLabel, searchEdit);

	leftLayout->addWidget(songSearcher);

	QObject::connect(searchEdit, &QLineEdit::textChanged, this, &ListenerWindow::searchSong);
}

void ListenerWindow::searchSong()
{
	std::string str = searchEdit->text().toStdString();
	musicPlayer->populateWithSongs(str);
}
