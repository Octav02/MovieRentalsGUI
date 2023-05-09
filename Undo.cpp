
#include "Undo.h"


void UndoAdauga::undo() {
    this->repo->remove(this->movie);
}


void UndoSterge::undo() {
    this->repo->add(this->movie);
}


void UndoModifica::undo() {
    this->repo->update(this->movie);
}