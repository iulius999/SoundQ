#pragma once

#include <QWidget>
#include "ui_SongWidget.h"
#include "../Domain/Song.h"
#include "../Service/Service.h"

class SongWidget : public QWidget
{
	Q_OBJECT

public:
	SongWidget(Service& serv, const Song& s, QWidget *parent = nullptr);
	~SongWidget();

	void showRemoveButton(const bool& value = true);

private:
	Ui::SongWidgetClass ui;
	Service& service;
	Song song;

	void initializeTitle();
	void initializeArtist();
	void initializeLikes();

	void linkPlayButton();
	void playSong();

	void connectRemoveButton();
	void removeSong();
};
