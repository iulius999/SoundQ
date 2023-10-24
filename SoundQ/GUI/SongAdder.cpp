#include "SongAdder.h"
#include <qmessagebox.h>

SongAdder::SongAdder(Service& serv, QWidget *parent)
	: QWidget(parent), service(serv)
{
	ui.setupUi(this);

	this->connectButtons();
}

SongAdder::~SongAdder()
{}

void SongAdder::showAddButton(bool value)
{
	if (value) {
		this->ui.addButton->show();
	}
	else {
		this->ui.addButton->hide();
	}
}

void SongAdder::showProposeButton(bool value)
{
	if (value) {
		this->ui.proposeButton->show();
	}
	else {
		this->ui.proposeButton->hide();
	}
}

void SongAdder::connectButtons()
{
	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &SongAdder::addSong);
	QObject::connect(this->ui.proposeButton, &QPushButton::clicked, this, &SongAdder::proposeSong);
}

void SongAdder::addSong()
{
	this->callFunction(&Service::addSong);
}

void SongAdder::proposeSong()
{
	this->callFunction(&Service::proposeSong);
}

void SongAdder::callFunction(void (Service::*function)(const std::string&, const std::string&, const int&, const int&, const int&, const std::string&))
{
	std::string title = this->ui.titleEdit->text().toStdString();
	std::string artist = this->ui.artistEdit->text().toStdString();
	std::string duration = this->ui.durationEdit->text().toStdString();
	std::string likes = this->ui.likesEdit->text().toStdString();
	std::string link = this->ui.linkEdit->text().toStdString();

	int min = 10 * (duration[0] - '0') + duration[1] - '0';
	int sec = 10 * (duration[3] - '0') + duration[4] - '0';
	int numberOfLikes;

	try {
		numberOfLikes = std::stoi(likes);
	}
	catch (...) {
		numberOfLikes = -1;
	}

	try {
		(service.*function)(title, artist, min, sec, numberOfLikes, link);
	}
	catch (std::exception& e) {
		int ret = QMessageBox::critical(this, "Error", e.what(), QMessageBox::Ok);
		if (ret == QMessageBox::Ok) {
			return;
		}
	}

	this->ui.titleEdit->clear();
	this->ui.artistEdit->clear();
	this->ui.durationEdit->setTime(QTime(0, 0));
	this->ui.likesEdit->clear();
	this->ui.linkEdit->clear();
}
