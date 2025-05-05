#include "ActiuneUndo.h"

UndoAdauga::UndoAdauga(Repository& repo, const std::string nrInmat) noexcept : repo { repo }, nrInmat { nrInmat }
{}

void UndoAdauga::doUndo()
{
	repo.Delete(nrInmat);
}

UndoModifica::UndoModifica(Repository& repo, const Masina& masina) noexcept : repo {repo}, masina { masina }
{}

void UndoModifica::doUndo()
{
	repo.Update(masina);
}

UndoSterge::UndoSterge(Repository& repo, const Masina& masina) noexcept : repo { repo }, masina { masina }
{}

void UndoSterge::doUndo()
{
	repo.Store(masina);
}
