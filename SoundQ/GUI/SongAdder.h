#pragma once

#include <QWidget>
#include "ui_SongAdder.h"
#include "../Service/Service.h"

class SongAdder : public QWidget
{
	Q_OBJECT

public:
	SongAdder(Service& serv, QWidget *parent = nullptr);
	~SongAdder();

	void showAddButton(bool value = true);
	void showProposeButton(bool value = true);

private:
	Ui::SongAdderClass ui;
	Service& service;

	void connectButtons();
	void addSong();
	void proposeSong();

	void callFunction(void (Service::*function)(const std::string&, const std::string&, const int&, const int&, const int&, const std::string&));
};
