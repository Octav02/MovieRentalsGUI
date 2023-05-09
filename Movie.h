#pragma once

#include <string>
#include <iostream>

using namespace std;

class Movie {
private :
    string title;
    string genre;
    int year;
    string mainActor;

public:
    Movie() = default;

    Movie(const string &title, const string &genre, int year, const string &mainActor);

    Movie(const Movie &movie);

    Movie &operator=(const Movie &movie);

    //Rule of 5
    ~Movie() = default;

    Movie(Movie &&movie) noexcept;

    Movie &operator=(Movie &&movie) noexcept;

    string getTitle() const;

    void setTitle(const string &movieTitle);

    string getGenre() const;

    void setGenre(const string &gen);

    int getYear() const;

    void setYear(int movieYear);

    string getMainActor() const;

    void setMainActor(const string &actor);

    bool operator==(const Movie &rhs) const;

    bool operator!=(const Movie &rhs) const;

    string toString();

    friend ostream &operator<<(ostream &os, const Movie &movie);

    friend istream &operator>>(istream &is, Movie &movie);
};