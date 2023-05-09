#pragma once

#include <fstream>
#include "MovieRepository.h"

class MovieRepositoryFile : public AbstractRepository {
private:
    string filename;
    void loadFromFile();
    void writeToFile();
public:
    MovieRepositoryFile();
    void add(const Movie &movie) override;
    void remove(const Movie &movie) override;
    void update(const Movie &movie) override;
    explicit MovieRepositoryFile(const string &filename);
    ~MovieRepositoryFile() override;
    const vector<Movie> &getAll() const override;
    int size() const override;
    const Movie &getMovie(int index) const override;
    int find(const Movie &movie) const override;
};