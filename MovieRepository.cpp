#include "MovieRepository.h"


MovieRepository::~MovieRepository() {
    this->movies.clear();
}

void MovieRepository::add(const Movie &movie) {
    if (this->find(movie) != -1)
        throw RepositoryException("Movie already exists!");
    this->movies.push_back(movie);
}

void MovieRepository::remove(const Movie &movie) {
    int index = this->find(movie);
    if (index == -1)
        throw RepositoryException("Movie does not exist!");
    this->movies.erase(this->movies.begin() + index);
}

void MovieRepository::update(const Movie &movie) {
    int index = this->find(movie);
    if (index == -1)
        throw RepositoryException("Movie does not exist!");
    this->movies[index] = movie;
}

const vector<Movie> &MovieRepository::getAll() const {
    return this->movies;
}

int MovieRepository::size() const {
    return this->movies.size();
}

const Movie &MovieRepository::getMovie(int index) const {
    return this->movies[index];
}

int MovieRepository::find(const Movie &movie) const {
    for (int i = 0; i < this->movies.size(); i++) {
        if (this->movies[i] == movie)
            return i;
    }
    return -1;
}