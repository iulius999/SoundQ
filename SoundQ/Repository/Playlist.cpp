#include "Playlist.h"
#include <fstream>
#include "../Exceptions/Exceptions.h"

Playlist::Playlist(const std::string& fileName)
{
	this->fileName = fileName;
	this->loadFile();
}

std::vector<Song> Playlist::getAll()
{
	return this->songs;
}

int Playlist::getSize() const
{
	return this->songs.size();
}

void Playlist::add(const Song& s)
{
	if (!findByTitleAndArtist(s.getTitle(), s.getArtist()).getTitle().empty()) {
		throw DuplicateSong("A song with the same title and artist already exists!");
	}

	songs.push_back(s);
	this->saveFile();
}

void Playlist::remove(const Song& s)
{
	std::vector<Song>::iterator it = std::find(songs.begin(), songs.end(), s);
	if (it == songs.end()) {
		throw InexistentSong("Inexistent song!");
	}

	songs.erase(it);
	this->saveFile();
}

Song Playlist::findByTitleAndArtist(const std::string& title, const std::string& artist)
{
	for (Song s : songs) {
		if (s.getTitle() == title && s.getArtist() == artist) {
			return s;
		}
	}

	return Song();
}

void Playlist::loadFile()
{
	std::ifstream fin(this->fileName);
	
	Song s;
	while (fin >> s) {
		songs.push_back(s);
	}

	fin.close();
}

void Playlist::saveFile()
{
	std::ofstream fout(this->fileName);

	for (const Song& s : songs) {
		fout << s;
	}

	fout.close();
}
