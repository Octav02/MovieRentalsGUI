cmake_minimum_required(VERSION 3.25)
project(Lab10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/octav/Qt/6.5.0/gcc_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Lab10 main.cpp Movie.cpp Movie.h AbstractRepository.cpp AbstractRepository.h MovieRepository.cpp MovieRepository.h Exceptions.cpp Exceptions.h Tests.cpp Tests.h Validator.cpp Validator.h Undo.cpp Undo.h MovieRepositoryFile.cpp MovieRepositoryFile.h Service.cpp Service.h GUI.cpp GUI.h)
target_link_libraries(Lab10
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

