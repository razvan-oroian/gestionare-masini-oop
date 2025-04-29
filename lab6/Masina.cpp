#include "Masina.h"

/* Creeaza un obiect de tip masina si initializeaza campurile 
*  nrInmatriculare, producator, model si tip cu string-ul gol
*  return:-
*/
Masina::Masina() noexcept
{
	this->nrInmatriculare = "";
	this->producator = "";
	this->model = "";
	this->tip = "";
}

/* Creeaza un obiect de tip masina si initializeaza campurile
*  nrInmatriculare, producator, model si tip cu datele primite
*  nrInmatriculare: string
*  producator: string
*  model: string
*  tip: string
*  return:-
*/
Masina::Masina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip) noexcept
{
	this->nrInmatriculare = nrInmatriculare;
	this->producator = producator;
	this->model = model;
	this->tip = tip;
}

/* Creeaza un obiect de tip masina prin copierea datelor de la
*  un alt obiect masina deja existent
*  other: obiect Masina de la care se copiaza
*  return:- 
*/
Masina::Masina(const Masina& other) noexcept
{
	nrInmatriculare = other.nrInmatriculare;
	producator = other.producator;
	model = other.model;
	tip = other.tip;
}

/* Returneaza numarul de inmatriculare al masinii
*  return: nr de inmatriculare
*/
const string& Masina::GetNrInmatriculare() const noexcept
{
	return this->nrInmatriculare;
}

/* Returneaza producatorul masinii
*  return: producatorul
*/
const string& Masina::GetProducator() const noexcept
{
	return this->producator;
}

/* Returneaza modelul masinii
*  return: modelul
*/
const string& Masina::GetModel() const noexcept
{
	return this->model;
}

/* Returneaza tipul masinii
*  return: tipul
*/
const string& Masina::GetTip() const noexcept
{
	return this->tip;
}

/* Seteaza numarul de inmatriculare al masinii la o valoare data
*  nrInmat: noul nr
*  return:- nr de inmatriculare este schimbat
*/
void Masina::SetNrInmatriculare(const string& nrInmat) noexcept
{
	this->nrInmatriculare = nrInmat;
}

/* Seteaza producatorul masinii la o valoare data
*  prod: noul producator
*  return:- producatorul este schimbat
*/
void  Masina::SetProducator(const string& prod) noexcept
{
	this->producator = prod;
}

/* Seteaza modelul masinii la o valoare data
*  mod: noul model
*  return:- modelul este schimbat
*/
void Masina::SetModel(const string& mod) noexcept
{
	this->model = mod;
}

/* Seteaza tipul masinii la o valoare data
*  type: noul tip
*  return:- tipul este schimbat
*/
void Masina::SetTip(const string& type) noexcept
{
	this->tip = type;
}

void Masina::swap(Masina& other)
{
	Masina aux = other;
	other = *this;
	*this = aux;
}

Masina& Masina::operator=(const Masina& other)
{
	if (this != &other)
	{
		nrInmatriculare = other.nrInmatriculare;
		producator = other.producator;
		model = other.model;
		tip = other.tip;
	}
	return *this;
}

/* Adauga in stream datele obiectului masina
*  os: output stream curent
*  m: obiect masina
*  return: referinta la output stream
*/
ostream& operator<<(ostream& os, const Masina& m)
{
	return os << "-------------------------\n"
		<< "Nr. inmatriculare: " << m.GetNrInmatriculare() << "\n"
		<< "Producator: " << m.GetProducator() << "\n"
		<< "Model: " << m.GetModel() << "\n"
		<< "Tip: " << m.GetTip() << '\n'
		<< "-------------------------\n";
}