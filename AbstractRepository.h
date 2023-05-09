#pragma once

#include "Movie.h"
#include <vector>

class AbstractRepository {
protected:
    vector<Movie> movies;
public:

    virtual ~AbstractRepository() =default;

    virtual void add(const Movie &movie)=0;

    virtual void remove(const Movie &movie)=0;

    virtual void update(const Movie &movie)=0;

    virtual const vector<Movie> &getAll() const =0;

    virtual int size() const =0;

    virtual const Movie &getMovie(int index) const =0;

    virtual int find(const Movie &movie) const =0;


};