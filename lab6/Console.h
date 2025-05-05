#ifndef CONSOLE_H
#define CONSOLE_H

#include "a.h"
#include "ServiceMasina.h"
#include "WashingList.h"
#include "run_tests.h"
#include <cctype>

class Console {
private:
	ServiceMasina& srvMasina;
	WashingList wlist;

public:
	Console(ServiceMasina& srv) noexcept;
	void AfiseazaMeniu() const;
	void Run();
	void AdaugaMasinaUi();
	void CitesteDate(string& nrInmatriculare, string& producator, string& model, string& tip) const;
	void AfiseazaMasini(const std::vector<Masina>& all) const;
	void StergeMasinaUi();
	void ModificaMasinaUi();
	void CautaMasinaUi() const;
	void FiltrareDupaProducatorUi() const;
	void FiltrareDupaTipUi() const;
	void SortDupaNrInmatriculare();
	void SortDupaTip();
	void SortDupaProducatorModel();
	void AdaugaMasinaSpalatUi();
	void GenereazaMasiniSpalatUi();
	void WriteToFileUi();
	void UndoUi();
	~Console() = default;
};

#endif