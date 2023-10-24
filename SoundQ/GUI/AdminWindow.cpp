#include "AdminWindow.h"

AdminWindow::AdminWindow(Service& serv, User& u, QWidget *parent)
	: QMainWindow(parent), service(serv), user(u)
{
	ui.setupUi(this);
	service.subscribe(this);

	this->setWindowTitle(QString::fromStdString(user.getName()));

	this->configureCentralWidget();
	this->configureLeftLayout();
	this->configureRightLayout();

	this->populateWaitingList();

	this->connectSignalsAndSlots();

	this->show();
}

AdminWindow::~AdminWindow()
{
	delete acceptButton;
	delete rejectButton;
	delete acceptRejectLayout;

	delete waitingSongList;
	delete rightLayout;

	delete musicPlayer;
	delete songAdder;
	delete leftLayout;

	delete mainLayout;
	delete centralWidget;
}

void AdminWindow::update()
{
	musicPlayer->populateWithSongs("");
	this->populateWaitingList();
}

void AdminWindow::configureCentralWidget()
{
	centralWidget = new QWidget(this);
	this->setCentralWidget(centralWidget);

	mainLayout = new QHBoxLayout(centralWidget);
}

void AdminWindow::configureLeftLayout()
{
	leftLayout = new QVBoxLayout();

	musicPlayer = new MusicPlayer(service);
	musicPlayer->showRemoveButtons();
	leftLayout->addWidget(musicPlayer);

	songAdder = new SongAdder(service);
	songAdder->showProposeButton(false);
	leftLayout->addWidget(songAdder);

	mainLayout->addLayout(leftLayout);
}

void AdminWindow::configureRightLayout()
{
	rightLayout = new QVBoxLayout();

	waitingSongList = new QListWidget();
	rightLayout->addWidget(waitingSongList);

	acceptRejectLayout = new QHBoxLayout();
	acceptButton = new QPushButton("Accept");
	rejectButton = new QPushButton("Reject");

	acceptButton->setDisabled(true);
	rejectButton->setDisabled(true);

	acceptRejectLayout->addWidget(acceptButton);
	acceptRejectLayout->addWidget(rejectButton);
	rightLayout->addLayout(acceptRejectLayout);

	mainLayout->addLayout(rightLayout);
}

void AdminWindow::populateWaitingList()
{
	std::vector<Song> all = service.getAllProposedSongs();
	waitingSongList->clear();

	for (Song s : all) {
		std::string str = s.getTitle() + " | " + s.getArtist();
		waitingSongList->addItem(QString::fromStdString(str));
	}
}

void AdminWindow::connectSignalsAndSlots()
{
	QObject::connect(this->waitingSongList, &QListWidget::itemSelectionChanged, this, &AdminWindow::enableButtons);
	QObject::connect(this->acceptButton, &QPushButton::clicked, this, &AdminWindow::acceptSong);
	QObject::connect(this->rejectButton, &QPushButton::clicked, this, &AdminWindow::rejectSong);
}

void AdminWindow::enableButtons()
{
	if (waitingSongList->selectedItems().empty()) {
		acceptButton->setDisabled(true);
		rejectButton->setDisabled(true);
	}
	else {
		acceptButton->setEnabled(true);
		rejectButton->setEnabled(true);
	}
}

void AdminWindow::acceptSong()
{
	int index = waitingSongList->currentRow();
	Song s = service.getProposedSongByIndex(index);
	service.acceptProposedSong(s);
}

void AdminWindow::rejectSong()
{
	int index = waitingSongList->currentRow();
	Song s = service.getProposedSongByIndex(index);
	service.rejectProposedSong(s);
}
