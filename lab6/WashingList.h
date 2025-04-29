#ifndef WASHINGLIST_H
#define WASHINGLIST_H
#include <random>
#include <algorithm>
#include <chrono>
#include "ServiceMasina.h"

class WashingList {
private:
	const ServiceMasina& srv;
	std::vector<Masina> masini;
public:
	WashingList(const ServiceMasina& srv) noexcept;
	void GolesteLista() noexcept;
	void AdaugaMasina(const string& nrInmat);
	void GenereazaLista(int count);
	const std::vector<Masina>& GetAll() const noexcept;
	const int GetSize() const noexcept;
};





#endif