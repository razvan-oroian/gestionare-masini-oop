#ifndef SERVICEMASINA_H
#define SERVICEMASINA_H

#include "a.h"
#include "Repository.h"
#include "Validator.h"
#include "assert.h"
#include <algorithm>
#include <fstream>
#include "ActiuneUndo.h"

typedef bool(*cmpFct)(const Masina&, const Masina&);

class ServiceMasina {
private:
	RepositoryFile& repoMasini;
	Validator& validator;
	std::vector<ActiuneUndo*> listaUndo;
public:
	ServiceMasina(RepositoryFile& repo, Validator& validator);
	void AdaugaMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);
	const std::vector<Masina>& GetAll() const noexcept;
	const size_t GetSize() const noexcept;
	void StergeMasina(const string& nrInmatriculare);
	void ModificaMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);
	const Masina CautaMasina(const string& nrInmatriculare) const;
	void FiltrareDupaProducator(std::vector<Masina>& filtrate, const string& producator) const;
	void FiltrareDupaTip(std::vector<Masina>& filtrate, const string& tip) const;
	void AdaugaDefault();
	void Sort(cmpFct cmp);
	void Undo();
	~ServiceMasina();
};



#endif