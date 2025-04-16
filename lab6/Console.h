#ifndef CONSOLE_H
#define CONSOLE_H

#include "a.h"
#include "ServiceMasina.h"
#include "run_tests.h"
#include <cctype>

class Console {
private:
	ServiceMasina srvMasina;

public:
	Console() noexcept;
	void AfiseazaMeniu() const;
	void Run();
	void AdaugaMasinaUi();
	void CitesteDate(string& nrInmatriculare, string& producator, string& model, string& tip) const;
	void AfiseazaMasini() const;
	void StergeMasinaUi();
	void ModificaMasinaUi();
	void CautaMasinaUi() const;
	void FiltrareDupaProducatorUi() const;
	void FiltrareDupaTipUi() const;
	void SortDupaNrInmatriculare();
	void SortDupaTip();
	void SortDupaProducatorModel();
	~Console() = default;
};

#endif