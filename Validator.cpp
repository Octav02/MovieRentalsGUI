#pragma once
#include "Validator.h"

void Validator::validateMovie(const Movie &movie) {
    string errors;
    if (movie.getTitle().empty()) {
        errors += "Title cannot be empty!\n";
    }
    if (movie.getGenre().empty()) {
        errors += "Genre cannot be empty!\n";
    }
    if (movie.getYear() < 0) {
        errors += "Year cannot be negative!\n";
    }
    if (movie.getMainActor().empty()) {
        errors += "Main actor cannot be empty!\n";
    }
    if (!errors.empty()) {
        throw ValidationException(errors);
    }
}