#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(Service& serv, QWidget *parent)
	: QWidget(parent), service(serv)
{
	ui.setupUi(this);

	this->makeWidgetsScrollable();
}

MusicPlayer::~MusicPlayer()
{
	for (SongWidget* ptr : songWidgets) {
		delete ptr;
	}

	delete scrollLayout;
	delete scrollWidget;
	delete scrollArea;
	
	delete mainLayout;
}

void MusicPlayer::makeWidgetsScrollable()
{
	scrollWidget = new QWidget();
	scrollLayout = new QVBoxLayout(scrollWidget);
	this->populateWithSongs("");

	scrollArea = new QScrollArea();
	scrollArea->setWidget(scrollWidget);
	scrollArea->setWidgetResizable(true);

	mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(scrollArea);
}

void MusicPlayer::populateWithSongs(const std::string& str)
{
	std::vector<Song> songs = service.searchSongs(str);

	for (SongWidget* ptr : songWidgets) {
		delete ptr;
	}
	songWidgets.clear();

	for (const Song& s : songs) {
		songWidgets.push_back(new SongWidget(service, s));
	}

	for (SongWidget* ptr : songWidgets) {
		scrollLayout->addWidget(ptr);
	}
}

void MusicPlayer::showRemoveButtons(const bool& value)
{
	for (SongWidget* ptr : songWidgets) {
		ptr->showRemoveButton(value);
	}
}
