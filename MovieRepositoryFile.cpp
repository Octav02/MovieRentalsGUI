#include <sstream>
#include "MovieRepositoryFile.h"

void MovieRepositoryFile::loadFromFile() {
    ifstream fin(this->filename);
    if (!fin.is_open()) {
        throw RepositoryException("File could not be opened!");
    }
    //Clear the vector
    this->movies.clear();
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() != 4) {
            continue;
        }
        string title = tokens[0];
        string genre = tokens[1];
        int year = stoi(tokens[2]);
        string mainActor = tokens[3];
        Movie movie(title, genre, year, mainActor);
        this->movies.push_back(movie);
    }
}

MovieRepositoryFile::MovieRepositoryFile(const string &filename) {
    this->filename = filename;
    this->loadFromFile();
}

void MovieRepositoryFile::writeToFile() {
    ofstream fout(this->filename);
    if (!fout.is_open()) {
        throw RepositoryException("File could not be opened!");
    }
    for (const auto &movie : this->movies) {
        fout << movie << "\n";
    }
}

void MovieRepositoryFile::add(const Movie &movie) {
    this->loadFromFile();
    if (this->find(movie) != -1)
        throw RepositoryException("Movie already exists!");
    this->movies.push_back(movie);
    this->writeToFile();
    this->loadFromFile();
}

void MovieRepositoryFile::remove(const Movie &movie) {
    this->loadFromFile();
    int index = this->find(movie);
    if (index == -1)
        throw RepositoryException("Movie does not exist!");
    this->movies.erase(this->movies.begin() + index);
    this->writeToFile();
    this->loadFromFile();
}

void MovieRepositoryFile::update(const Movie &movie) {
    this->loadFromFile();
    int index = this->find(movie);
    if (index == -1)
        throw RepositoryException("Movie does not exist!");
    this->movies[index] = movie;
    this->writeToFile();
    this->loadFromFile();
}

MovieRepositoryFile::~MovieRepositoryFile() {
//    this->writeToFile();
//    this->movies.clear();
}

const vector<Movie> &MovieRepositoryFile::getAll() const {
    return this->movies;
}

int MovieRepositoryFile::size() const {
    return this->movies.size();
}

const Movie &MovieRepositoryFile::getMovie(int index) const {
    return this->movies[index];
}

int MovieRepositoryFile::find(const Movie &movie) const {
    for (int i = 0; i < this->movies.size(); i++) {
        if (this->movies[i] == movie)
            return i;
    }
    return -1;
}

MovieRepositoryFile::MovieRepositoryFile() {
    this->filename = "";
}