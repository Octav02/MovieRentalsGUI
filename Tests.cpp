
#include "Tests.h"
#include "Service.h"
#include <fstream>

void Tests::testAll() {
    testMovie();
    testIO();
    testRepo();
    testRepoFile();
    testService();
    testUndo();
}

void Tests::testMovie() {
    Validator validator;
    Movie *movie1 = new Movie("1", "1", 1, "1");
    Movie *movie2 = new Movie(*movie1);
    Movie *movie3 = new Movie();
    *movie3 = *movie1;
    assert(*movie1 == *movie2);

    assert(movie1->getTitle() == "1");
    assert(movie1->getGenre() == "1");
    assert(movie1->getYear() == 1);
    assert(movie1->getMainActor() == "1");

    validator.validateMovie(*movie1);

    string s = movie1->toString();

    movie1->setTitle("");
    movie1->setGenre("");
    movie1->setYear(-24);
    movie1->setMainActor("");
    assert(*movie1 != *movie3);
    try {
        validator.validateMovie(*movie1);
    }
    catch (ValidationException &exception) {
        assert(true);
    }

    Movie cm1 = std::move(*movie1);
    assert(cm1.getTitle().empty());
    auto *cm2 = new Movie(std::move(*movie3));
    assert(cm2->getTitle() == "1");


    auto cm3 = new Movie();
    *cm3 = std::move(*cm2);

    assert(cm3->getTitle() == "1");


    delete movie1;
    delete movie2;
    delete movie3;
    delete cm3;
    delete cm2;
}

void Tests::testIO() {
    Movie *movie = new Movie("1", "1", 1, "1");
    Movie *movie2 = new Movie();

    Movie aux;
    ofstream fout("../testIO/out");
    ifstream fin("../testIO/in");

    fout << *movie;
    fin >> *movie2;
    fin >> aux;
    assert(movie2->getTitle() == "1");


    delete movie;
    delete movie2;
    fin.close();
    fout.close();
}

void Tests::testRepo() {
    MovieRepository repo;
    Movie movie1 = Movie("1", "1", 1, "1");
    Movie movie2 = Movie("2", "2", 2, "2");
    Movie movie3 = Movie("1", "3", 3, "3");
    repo.add(movie1);
    try {
        repo.add(movie1);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        repo.remove(movie2);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        repo.update(movie2);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    repo.add(movie2);
    repo.remove(movie2);
    repo.update(movie3);
    assert(repo.getAll().size() == 1);
    assert(repo.size() == 1);

    Movie m = repo.getMovie(0);
}

void Tests::testRepoFile() {
    MovieRepositoryFile repo = MovieRepositoryFile("../IORepoTests/test");
    Movie movie1 = Movie("1", "1", 1, "1");
    Movie movie2 = Movie("2", "2", 2, "2");
    Movie movie3 = Movie("1", "3", 3, "3");
    repo.add(movie1);
    try {
        repo.add(movie1);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        repo.remove(movie2);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        repo.update(movie2);
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    repo.add(movie2);
    repo.remove(movie2);
    repo.update(movie3);
    assert(repo.getAll().size() == 1);
    assert(repo.size() == 1);

    Movie m = repo.getMovie(0);
    repo.remove(movie3);

}

void Tests::testService() {
    MovieRepositoryFile *repo =  new MovieRepositoryFile("../IORepoTests/testService");
    Validator validator;
    Service service = Service(repo, validator);

    service.addMovie("1", "1", 1, "1");
    try {
        service.addMovie("1", "1", 1, "1");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        service.addMovie("", "", -1, "");
    }
    catch (ValidationException &exception) {
        assert(true);
    }
    try {
        service.removeMovie("2", "2", 2, "2");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        service.updateMovie("2", "2", 2, "2");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        service.updateMovie("1", "", -1, "");
    }
    catch (ValidationException &exception) {
        assert(true);
    }
    service.updateMovie("1", "3", 3, "3");
    assert(service.getAll().size() == 1);
    assert(service.getMovie(0).getTitle() == "1");
    assert(service.size() == 1);
    assert(service.find("1") == 0);
    service.removeMovie("1",  "2", 2, "2");

    service.addMovie("1", "1", 1, "1");
    service.addMovie("3", "3", 3, "3");
    service.addMovie("2", "2", 2, "2");


    assert(service.getMoviesByTitle("1").size() == 1);
    assert(service.getMoviesByYear(2).size() == 1);
    assert(service.sortMoviesByTitle(true)[0].getTitle() == "1");
    assert(service.sortMoviesByYear(true)[0].getYear() == 1);
    assert(service.sortMoviesByGenre(true)[0].getGenre() == "1");
    assert(service.sortMoviesByMainActor(true)[0].getMainActor() == "1");
    assert(service.sortMoviesByTitle(false)[0].getTitle() == "3");
    assert(service.sortMoviesByYear(false)[0].getYear() == 3);
    assert(service.sortMoviesByGenre(false)[0].getGenre() == "3");
    assert(service.sortMoviesByMainActor(false)[0].getMainActor() == "3");

    service.addToWatchlist("1", "1", 1, "1");
    try {
        service.addToWatchlist("1", "1", 1, "1");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }
    try {
        service.addToWatchlist("", "", -1, "");
    }
    catch (ValidationException &exception) {
        assert(true);
    }
    try {
        service.deleteFromWatchlist("2");
    }
    catch (RepositoryException &exception) {
        assert(true);
    }

    assert(service.getWatchlist().size() == 1);

    service.generateWatchlist(2);

    assert(service.getWatchlist().size() == 3);

    service.saveWatchlistToFile("../IORepoTests/testWatchlist");


    service.removeMovie("3", "2", 2, "2");
    service.removeMovie("2", "2", 2, "2");
    service.removeMovie("1", "2", 2, "2");

    delete repo;
}

void Tests::testUndo() {
    MovieRepositoryFile* repo =  new MovieRepositoryFile("../IORepoTests/testUndo");
    Validator validator;
    Service service = Service(repo, validator);
    try {
        service.doUndo();
        assert(false);
    }
    catch (runtime_error &exception) {
        assert(true);
    }

    service.addMovie("1", "1", 1, "1");
    service.addMovie("2", "2", 2, "2");
    service.doUndo();

    service.addMovie("2", "2", 2, "2");
    service.removeMovie("2", "2", 2, "2");
    assert(service.getAll().size() == 1);
    service.doUndo();
    assert(service.getAll().size() == 2);

    service.updateMovie("2", "3", 3, "3");
    assert(service.getMovie(1).getGenre() == "3");
    service.doUndo();
    assert(service.getMovie(1).getGenre() == "2");

    service.doUndo();
    service.doUndo();
    delete repo;
}