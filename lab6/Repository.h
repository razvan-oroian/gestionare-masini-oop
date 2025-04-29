#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "a.h"
//#include "MyVector.h"
#include <vector>
#include "IteratorVector.h"
#include "Masina.h"

class Repository {
private:
	//MyVector<Masina> masini;
	std::vector<Masina> masini;

public:
	Repository() noexcept;
	void Store(const Masina& masina);
	const int Find(const string& nrInmatriculare) const;
	//const MyVector<Masina>& GetAll() const noexcept;
	const std::vector<Masina>& GetAll() const noexcept;
	//void SetMasini(const MyVector<Masina>& masini_noi);
	void SetMasini(const std::vector<Masina>& masini_noi);
	const size_t GetSize() const noexcept;
	void Delete(const string& nrInmatriculare);
	void Update(const Masina& masina);
};


#endif