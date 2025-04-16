#ifndef SERVICEMASINA_H
#define SERVICEMASINA_H

#include "a.h"
#include "Repository.h"
#include "Validator.h"
#include "assert.h"
typedef bool(*cmpFct)(const Masina&, const Masina&);

class ServiceMasina {
private:
	Repository repoMasini;
	Validator validator;

public:
	ServiceMasina() noexcept;
	void AdaugaMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);
	const MyVector<Masina>& GetAll() const noexcept;
	const size_t GetSize() const noexcept;
	void StergeMasina(const string& nrInmatriculare);
	void ModificaMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip);
	const Masina CautaMasina(const string& nrInmatriculare) const;
	void FiltrareDupaProducator(MyVector<Masina>& filtrate, const string& producator) const;
	void FiltrareDupaTip(MyVector<Masina>& filtrate, const string& tip) const;
	void AdaugaDefault();
	void Sort(cmpFct cmp);
};



#endif