
#include <algorithm>
#include <chrono>
#include "Service.h"


void Service::addMovie(const string &title, const string &genre, int year, const string &mainActor) {
    Movie movie(title, genre, year, mainActor);
    this->validator.validateMovie(movie);
    this->repo->add(movie);
    UndoAdauga* undoAdauga = new UndoAdauga(this->repo, movie);
    this->undoActions.push_back(unique_ptr<ActiuneUndo>(undoAdauga));
}


void Service::removeMovie(const string &title, const string &genre, int year, const string &mainActor) {
    Movie movie(title, genre, year, mainActor);
    this->repo->remove(movie);
    UndoSterge* undoSterge = new UndoSterge(this->repo, movie);
    this->undoActions.push_back(unique_ptr<ActiuneUndo>(undoSterge));
}

void Service::updateMovie(const string &title, const string &genre, int year, const string &mainActor) {
    Movie movie(title, genre, year, mainActor);
    int index = this->repo->find(movie);
    Movie oldMovie;
    if (index != -1) {
        oldMovie = this->repo->getMovie(index);
    }
    this->validator.validateMovie(movie);
    this->repo->update(movie);
    UndoModifica* undoModifica = new UndoModifica(this->repo, oldMovie);
    this->undoActions.push_back(unique_ptr<ActiuneUndo>(undoModifica));
}

const vector<Movie> &Service::getAll() const {
    return this->repo->getAll();
}

int Service::size() const {
    return this->repo->size();
}

const Movie &Service::getMovie(int index) const {
    return this->repo->getMovie(index);
}

int Service::find(const string & title) const {
    Movie movie(title, "", 0, "");
    return this->repo->find(movie);
}

vector<Movie> Service::getMoviesByTitle(const string& title) {
    vector<Movie> movies = repo->getAll();
    vector<Movie> moviesByTitle;
    copy_if(movies.begin(), movies.end(), back_inserter(moviesByTitle), [title](const Movie&  movie) {
        return movie.getTitle() == title;
    });
    return moviesByTitle;
}

vector<Movie> Service::getMoviesByYear(int year) {
    vector<Movie> movies = repo->getAll();
    vector<Movie> moviesByYear;
    copy_if(movies.begin(), movies.end(), back_inserter(moviesByYear), [year](const Movie&  movie) {
        return movie.getYear() == year;
    });
    return moviesByYear;
}

vector<Movie> Service::sortMoviesByTitle(bool ascending) {
    vector<Movie> movies = repo->getAll();
    if (ascending) {
        sort(movies.begin(), movies.end(), [](const Movie&  movie1, const Movie&  movie2) {
            return movie1.getTitle() < movie2.getTitle();
        });
    } else {
        sort(movies.begin(), movies.end(), [](const Movie&  movie1, const Movie&  movie2) {
            return movie1.getTitle() > movie2.getTitle();
        });
    }
    return movies;
}

vector<Movie> Service::sortMoviesByGenre(bool ascending) {
    vector<Movie> movies = repo->getAll();
    if (ascending) {
        sort(movies.begin(), movies.end(), [](const Movie&  movie1, const Movie&  movie2) {
            return movie1.getGenre() < movie2.getGenre();
        });
    } else {
        sort(movies.begin(), movies.end(), [](const Movie& movie1, const Movie&  movie2) {
            return movie1.getGenre() > movie2.getGenre();
        });
    }
    return movies;
}

vector<Movie> Service::sortMoviesByYear(bool ascending) {
    vector<Movie> movies = repo->getAll();
    if (ascending) {
        sort(movies.begin(), movies.end(), [](const Movie&  movie1, const Movie&  movie2) {
            return movie1.getYear() < movie2.getYear();
        });
    } else {
        sort(movies.begin(), movies.end(), [](const Movie&  movie1, const Movie&  movie2) {
            return movie1.getYear() > movie2.getYear();
        });
    }
    return movies;
}

vector<Movie> Service::sortMoviesByMainActor(bool ascending) {
    vector<Movie> movies = repo->getAll();
    if (ascending) {
        sort(movies.begin(), movies.end(), [](const Movie&  movie1, const Movie&  movie2) {
            return movie1.getMainActor() < movie2.getMainActor();
        });
    } else {
        sort(movies.begin(), movies.end(), [](const Movie&  movie1, const Movie&  movie2) {
            return movie1.getMainActor() > movie2.getMainActor();
        });
    }
    return movies;
}

void Service::addToWatchlist(const string& title, const string& genre, int year, const string& mainActor) {
    Movie movie = Movie(title, genre, year, mainActor);
    validator.validateMovie(movie);
    watchlist.add(movie);
    notify();
}

void Service::deleteFromWatchlist(const string& title) {
    Movie movie =  Movie(title, "", 0, "");
    watchlist.remove(movie);
    notify();
}

vector<Movie> Service::getWatchlist() {
    return watchlist.getAll();
}

void Service::generateWatchlist(int numberOfMovies) {
    //Generate numberOfMovies random titles, genre, year and mainActor and add them to the watchlist

    auto seed = chrono::steady_clock::now().time_since_epoch().count();
    srand(seed);

    for (int i = 0; i < numberOfMovies; i++) {
        //Generate random titles using seed
        string title;
        int titleLength = rand() % 20 + 1;
        for (int j = 0; j < titleLength; j++) {
            title += (char) (rand() % 26 + 97);
        }

        //Generate random genre
        string genre;
        int genreLength = rand() % 20 + 1;
        for (int j = 0; j < genreLength; j++) {
            genre += (char) (rand() % 26 + 97);
        }

        //Generate random year
        int year = rand() % 200 + 1900;

        //Generate random mainActor
        string mainActor;
        int mainActorLength = rand() % 20 + 1;
        for (int j = 0; j < mainActorLength; j++) {
            mainActor += (char) (rand() % 26 + 97);
        }

        Movie movie = Movie(title, genre, year, mainActor);
        watchlist.add(movie);
    }
    notify();
}

void Service::saveWatchlistToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    vector<Movie> movies = watchlist.getAll();
    for (const Movie& movie : movies) {
        file << movie.getTitle() << "," << movie.getGenre() << "," << movie.getYear() << "," << movie.getMainActor()
             << endl;
    }
    file.close();
}

void Service::doUndo() {
    if (undoActions.empty()) {
        throw std::runtime_error("No more undos");
    }
    undoActions.back()->undo();
    undoActions.pop_back();
}

Service::~Service() {
//    delete repo;
}

map<string, vector<Movie>> Service::getMoviesByType(string type) {
    map<string, vector<Movie>> moviesByType;
    if (type == "Title") {
        vector<Movie> movies = repo->getAll();
        std::copy_if(movies.begin(), movies.end(), movies.begin(), [](const Movie& movie) {
            return movie.getTitle() == movie.getTitle();
        });
        for (const Movie& movie : movies) {
            moviesByType[movie.getTitle()].push_back(movie);
        }
    }
    else if (type == "Genre") {
        vector<Movie> movies = repo->getAll();
        std::copy_if(movies.begin(), movies.end(), movies.begin(), [](const Movie& movie) {
            return movie.getGenre() == movie.getGenre();
        });
        for (const Movie& movie : movies) {
            moviesByType[movie.getGenre()].push_back(movie);
        }
    }
    else if (type == "Year") {
        vector<Movie> movies = repo->getAll();
        std::copy_if(movies.begin(), movies.end(), movies.begin(), [](const Movie& movie) {
            return movie.getYear() == movie.getYear();
        });
        for (const Movie& movie : movies) {
            moviesByType[to_string(movie.getYear())].push_back(movie);
        }
    }
    else if (type == "Main Actor") {
        vector<Movie> movies = repo->getAll();
        std::copy_if(movies.begin(), movies.end(), movies.begin(), [](const Movie& movie) {
            return movie.getMainActor() == movie.getMainActor();
        });
        for (const Movie& movie : movies) {
            moviesByType[movie.getMainActor()].push_back(movie);
        }
    }
    return moviesByType;
}

vector<Movie> Service::getMoviesByGenre(const string &genre) {
    vector<Movie> movies = repo->getAll();
    vector<Movie> moviesByGenre;
    copy_if(movies.begin(), movies.end(), back_inserter(moviesByGenre), [genre](const Movie&  movie) {
        return movie.getGenre() == genre;
    });
    return moviesByGenre;
}
