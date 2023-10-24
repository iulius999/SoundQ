#pragma once

#include <QWidget>
#include "ui_MusicPlayer.h"
#include "../Service/Service.h"
#include "SongWidget.h"
#include <qscrollarea.h>
#include "../Observer/Observer.h"

class MusicPlayer : public QWidget
{
	Q_OBJECT

public:
	MusicPlayer(Service& serv, QWidget *parent = nullptr);
	~MusicPlayer();

	void populateWithSongs(const std::string& str);

	void showRemoveButtons(const bool& value = true);

private:
	Ui::MusicPlayerClass ui;
	Service& service;
	std::vector<SongWidget*> songWidgets;
	QVBoxLayout* scrollLayout, * mainLayout;
	QScrollArea* scrollArea;
	QWidget* scrollWidget;
	
	void makeWidgetsScrollable();
};
