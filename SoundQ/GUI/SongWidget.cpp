#include "SongWidget.h"

SongWidget::SongWidget(Service& serv, const Song& s, QWidget *parent)
	: QWidget(parent), service(serv), song(s)
{
	ui.setupUi(this);

	this->initializeTitle();
	this->initializeArtist();
	this->initializeLikes();

	this->linkPlayButton();
	this->connectRemoveButton();
}

SongWidget::~SongWidget()
{}

void SongWidget::showRemoveButton(const bool& value)
{
	if (value) {
		this->ui.removeButton->show();
	}
	else {
		this->ui.removeButton->hide();
	}
}

void SongWidget::initializeTitle()
{
	this->ui.titleLabel->setText(QString::fromStdString(song.getTitle()));
	this->ui.titleLabel->setAlignment(Qt::AlignCenter);
}

void SongWidget::initializeArtist()
{
	this->ui.artistLabel->setText(QString::fromStdString(song.getArtist()));
	this->ui.artistLabel->setAlignment(Qt::AlignCenter);
}

void SongWidget::initializeLikes()
{
	std::string str = std::to_string(this->song.getNumberOfLikes()) + "\nlikes";
	this->ui.likesLabel->setText(QString::fromStdString(str));
	this->ui.likesLabel->setAlignment(Qt::AlignCenter);
}

void SongWidget::linkPlayButton()
{
	QObject::connect(this->ui.playButton, &QPushButton::clicked, this, &SongWidget::playSong);
}

void SongWidget::playSong()
{
	this->song.play();
}

void SongWidget::connectRemoveButton()
{
	QObject::connect(this->ui.removeButton, &QPushButton::clicked, this, &SongWidget::removeSong);
}

void SongWidget::removeSong()
{
	service.removeSong(song.getTitle(), song.getArtist());
}
