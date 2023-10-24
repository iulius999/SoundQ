#pragma once

#include <QMainWindow>
#include "ui_AdminWindow.h"
#include "../Service/Service.h"
#include "MusicPlayer.h"
#include "SongAdder.h"
#include <qlistwidget.h>

class AdminWindow : public QMainWindow, public Observer
{
	Q_OBJECT

public:
	AdminWindow(Service& serv, User& u, QWidget *parent = nullptr);
	~AdminWindow();

	void update() override;

private:
	Ui::AdminWindowClass ui;
	Service& service;
	User& user;
	QWidget* centralWidget;
	QHBoxLayout* mainLayout, * acceptRejectLayout;
	QVBoxLayout* leftLayout, * rightLayout;
	QListWidget* waitingSongList;
	QPushButton* acceptButton, * rejectButton;
	MusicPlayer* musicPlayer;
	SongAdder* songAdder;

	void configureCentralWidget();
	void configureLeftLayout();
	void configureRightLayout();

	void populateWaitingList();

	void connectSignalsAndSlots();

	void enableButtons();
	void acceptSong();
	void rejectSong();
};
