#include "GUI.h"
#include "Tests.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto test = Tests();
    test.testAll();
    cout << "Tests passed" << endl;

    MovieRepositoryFile* repo = new MovieRepositoryFile("../Persistence/movies.csv");
    Validator validator;
    Service service(repo, validator);
    GUI gui(service);
    gui.show();

    return QApplication::exec();
}
