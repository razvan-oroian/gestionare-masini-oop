#ifndef ACTIUNE_UNDO_H
#define ACTIUNE_UNDO_H
#endif
#include "Repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	std::string nrInmat;
	Repository& repo;
public:
	UndoAdauga(Repository& repo, const std::string nrInmat) noexcept;
	void doUndo() override;
};

class UndoModifica : public ActiuneUndo {
private:
	Masina masina;
	Repository& repo;
	
public:
	UndoModifica(Repository& repo, const Masina& masina) noexcept;
	void doUndo() override;

};

class UndoSterge : public ActiuneUndo {
private:
	Masina masina;
	Repository& repo;

public:
	UndoSterge(Repository& repo, const Masina& masina) noexcept;
	void doUndo() override;
};
