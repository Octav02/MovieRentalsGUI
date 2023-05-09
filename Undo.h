#pragma once

#include "MovieRepositoryFile.h"


class ActiuneUndo {
public :
    virtual void undo() = 0;
    virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
    Movie movie;
    AbstractRepository* repo;
public:
    UndoAdauga(AbstractRepository* repo, const Movie& movie) :  repo{repo}, movie{movie} {};
    void undo() override;
};

class UndoSterge : public ActiuneUndo {
private:
    Movie movie;
    AbstractRepository* repo;
public:
    UndoSterge(AbstractRepository* repo, const Movie& movie) : repo{repo}, movie{movie} {};
    void undo() override;
};

class UndoModifica : public ActiuneUndo {
private:
    Movie movie;
    AbstractRepository* repo;
public:
    UndoModifica(AbstractRepository* repo, const Movie& movie) : repo{repo}, movie{movie} {};
    void undo() override;
};