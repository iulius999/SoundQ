#pragma once

#include <QMainWindow>
#include "ui_ListenerWindow.h"
#include "../Service/Service.h"
#include "MusicPlayer.h"
#include <qlineedit.h>
#include <qformlayout.h>
#include "SongAdder.h"

class ListenerWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	ListenerWindow(Service& serv, User& u, QWidget *parent = nullptr);
	~ListenerWindow();

	void update() override;

private:
	Ui::ListenerWindowClass ui;
	Service& service;
	User& user;
	QWidget* centralWidget, * songSearcher;
	QHBoxLayout* mainLayout;
	QVBoxLayout* leftLayout, * rightLayout;
	QFormLayout* searchLayout;
	QLabel* searchLabel;
	QLineEdit* searchEdit;
	MusicPlayer* musicPlayer;
	SongAdder* songProposer;

	void configureCentralWidget();
	void configureLeftLayout();
	void configureRightLayout();

	void configureSongSearcher();

	void searchSong();
};
