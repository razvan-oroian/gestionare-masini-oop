#include "Repository.h"
#include "Validator.h"

/* Creeaza un obiect de tip repository fara elemente
*  return:-
*/
Repository::Repository() noexcept
{}

/* Adauga o masina in colectia de masini
*  masina: masina adaugata
*  return:-
*/
void Repository::Store(const Masina & masina)
{
	const int poz = Find(masina.GetNrInmatriculare());
	if (poz != -1)
		throw(MasinaAlreadyExistsException());

	masini.push_back(masina);
}

/* Returneaza pozitia masinii care are un numar de inmatriculare dat
*  nrInmatriculare: nr masinii cautate
*  return:- pozitia masinii sau -1 daca ea nu se afla in colectie
*/
const int Repository::Find(const string& nrInmatriculare) const
{
	for (int i = 0; i < masini.Size(); ++i)
		if (masini.at(i).GetNrInmatriculare() == nrInmatriculare)
			return i;

	return -1;
}

/* Returneaza colectia de masini
*  return: vector de masini
*/
const MyVector<Masina>& Repository::GetAll() const noexcept
{
	return masini;
}

/* Seteaza colectia de masini gestionata de repository
*  masini_noi: vector de masini
*  return:-
*/
void Repository::SetMasini(const MyVector<Masina>& masini_noi)
{
	masini = masini_noi;
}

/* Returneaza numarul de masini din colectie
*  return: nr de masini
*/
const size_t Repository::GetSize() const noexcept
{
	return masini.Size();
}

/* Sterge din colectie masina care are un numar de inmatriculare dat
*  nrInmatriculare: nr masinii
*  return:-
*/
void Repository::Delete(const string& nrInmatriculare)
{
	const int poz = Find(nrInmatriculare);

	if (poz == -1)
		throw((MasinaDoesNotExistException()));

	masini.erase(masini.begin() + poz);
}

/* Modifica datele masinii care are un numar de inmatriculare dat
*  masina: masina ale carei date vor fi copiate peste masina modificata
*  return:-
*/
void Repository::Update(const Masina& masina)
{
	const int poz = Find(masina.GetNrInmatriculare());

	if (poz == -1)
		throw(MasinaDoesNotExistException());

	masini.at(poz) = masina;
}