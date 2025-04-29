#ifndef MASINA_H
#define MASINA_H

#include <iostream>
#include <string>
using std::string;
using std::ostream;

class Masina {
private:
	string nrInmatriculare,
		producator, model, tip;

public:

	Masina() noexcept;
	Masina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) noexcept;
	Masina(const Masina& other) noexcept;
	const string& GetNrInmatriculare() const noexcept;
	const string& GetProducator() const noexcept;
	const string& GetModel() const noexcept;
	const string& GetTip() const noexcept;
	
	void SetNrInmatriculare(const string& nrInmatriculare) noexcept;
	void SetProducator(const string& producator) noexcept;
	void SetModel(const string& model) noexcept;
	void SetTip(const string& tip) noexcept;

	void swap(Masina& other);
	Masina& operator=(const Masina& other);

};
ostream& operator<<(ostream& os, const Masina& m);
#endif