
#include "Movie.h"

#include <vector>
#include <sstream>

Movie::Movie(const Movie &movie) {
    this->title = movie.title;
    this->genre = movie.genre;
    this->year = movie.year;
    this->mainActor = movie.mainActor;
}

Movie &Movie::operator=(const Movie &movie) {
    if (this != &movie) {
        this->title = movie.title;
        this->genre = movie.genre;
        this->year = movie.year;
        this->mainActor = movie.mainActor;
    }
    return *this;
}

string Movie::getTitle() const {
    return this->title;
}

void Movie::setTitle(const string &movieTitle) {
    this->title = movieTitle;
}

string Movie::getGenre() const {
    return this->genre;
}

void Movie::setGenre(const string &gen) {
    this->genre = gen;
}

int Movie::getYear() const {
    return this->year;
}

void Movie::setYear(int movieYear) {
    this->year = movieYear;
}

string Movie::getMainActor() const {
    return this->mainActor;
}

void Movie::setMainActor(const string &actor) {
    this->mainActor = actor;
}

bool Movie::operator==(const Movie &rhs) const {
    return this->title == rhs.title;
}

Movie::Movie(Movie &&movie) noexcept {
    this->title = movie.title;
    this->genre = movie.genre;
    this->year = movie.year;
    this->mainActor = movie.mainActor;
}

Movie &Movie::operator=(Movie &&movie) noexcept {
    if (this != &movie) {
        this->title = movie.title;
        this->genre = movie.genre;
        this->year = movie.year;
        this->mainActor = movie.mainActor;
    }
    return *this;
}

bool Movie::operator!=(const Movie &rhs) const {
    return !(rhs == *this);
}

string Movie::toString() {
    return "Movie : " + this->title + " " + this->genre + " " + to_string(this->year) + " " + this->mainActor;
}

ostream &operator<<(ostream &os, const Movie &movie) {
    os << movie.title << "," << movie.genre << "," << movie.year << "," << movie.mainActor;
    return os;
}

istream &operator>>(istream &is, Movie &movie) {
    string line;
    getline(is, line);

    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() != 4) {
        return is;
    }

    movie.title = tokens[0];
    movie.genre = tokens[1];
    movie.year = stoi(tokens[2]);
    movie.mainActor = tokens[3];

    return is;
}

Movie::Movie(const string &title, const string &genre, int year, const string &mainActor) {
    this->title = title;
    this->genre = genre;
    this->year = year;
    this->mainActor = mainActor;
}
