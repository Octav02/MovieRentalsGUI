#pragma once

#include "Movie.h"
#include "Exceptions.h"
#include "AbstractRepository.h"
#include <vector>

using namespace std;

class MovieRepository : public AbstractRepository{
public:
    MovieRepository() = default;

    ~MovieRepository() override;

    void add(const Movie &movie) override;

    void remove(const Movie &movie) override;

    void update(const Movie &movie) override;

    const vector<Movie> &getAll() const override;

    int size() const override;

    const Movie &getMovie(int index) const override;

    int find(const Movie &movie) const override;

};