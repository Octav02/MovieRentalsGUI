#pragma once

#include "Movie.h"
#include "MovieRepository.h"
#include "Validator.h"
#include "MovieRepositoryFile.h"
#include <cassert>

class Tests {
public:
    void testAll();

private:
    void testMovie();

    void testRepo();

    void testRepoFile();

    void testService();

    void testIO();

    void testUndo();
};
