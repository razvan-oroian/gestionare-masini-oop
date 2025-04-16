#include "ServiceMasina.h"

/* Creeaza un obiect de tip serviciu pentru masini
*  return:-
*/
ServiceMasina::ServiceMasina() noexcept
{}

/* Adauga o masina in colectia de masini pe baza datelor primite
*  nrInmatriculare: nr masinii
*  producator: producatorul masinii
*  model: modelul masinii
*  tip: tipul masinii
*  return:-
*/
void ServiceMasina::AdaugaMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip)
{
	Masina masina{ nrInmatriculare, producator, model, tip };
	validator.validateMasina(masina);

	repoMasini.Store(masina);
}

/* Returneaza colectia de masini
*  return: vector de masini
*/
const MyVector<Masina>& ServiceMasina::GetAll() const noexcept
{
	return repoMasini.GetAll();
}

/* Returneaza numarul de masini din colectie
*  return: nr masini
*/
const size_t ServiceMasina::GetSize() const noexcept
{
	return repoMasini.GetSize();
}

/* Sterge din colectie masina care are un numar de inmatriculare dat
*  return:-
*/
void ServiceMasina::StergeMasina(const string& nrInmatriculare)
{
	repoMasini.Delete(nrInmatriculare);
}

/* Modifica masina din colectie care are un numar de inmatriculare dat pe baza datelor primite
*  nrInmatriculare: nr masinii
*  producator: producatorul masinii
*  model: modelul masinii
*  tip: tipul masinii
*  return:-
*/
void ServiceMasina::ModificaMasina(const string& nrInmatriculare, const string& producator, const string& model, const string& tip)
{
	Masina masina{ nrInmatriculare, producator, model, tip };
	validator.validateMasina(masina);

	repoMasini.Update(masina);
}

/* Returneaza masina care are un numar de inmatriculare dat
*  nrInmatriculare: nr masinii
*  return: masina cautata sau masina cu date default daca ea nu exista
*/
const Masina ServiceMasina::CautaMasina(const string& nrInmatriculare) const
{
	const int poz = repoMasini.Find(nrInmatriculare);
	if (poz == -1)
		return Masina();
	return repoMasini.GetAll().at(poz);
}

/* Selecteaza din colectia de masini pe acelea care au un producator dat
*  filtrate: vectorul in care se adauga masinile selectate
*  producator: producatorul dat
*  return:-
*/
void ServiceMasina::FiltrareDupaProducator(MyVector<Masina>& filtrate, const string& producator) const

{
	for (const Masina& masina : repoMasini.GetAll())
		if (masina.GetProducator() == producator)
			filtrate.push_back(masina);
}

/* Selecteaza din colectia de masini pe acelea care au un tip dat
*  filtrate: vectorul in care se adauga masinile selectate
*  tip: tipul dat
*  return:-
*/
void ServiceMasina::FiltrareDupaTip(MyVector<Masina>& filtrate, const string& tip) const
{
	for (const Masina& masina : repoMasini.GetAll())
		if (masina.GetTip() == tip)
			filtrate.push_back(masina);
}

/* Adauga masini in colectie
*  return:-
*/
void ServiceMasina::AdaugaDefault()
{
	AdaugaMasina("B123ABC", "Dacia", "Duster", "SUV");
	AdaugaMasina("TM45XYZ", "Volkswagen", "Golf", "Sport");
	AdaugaMasina("IF78MNO", "BMW", "X5", "SUV");
	AdaugaMasina("AG32PQR", "Mercedes-Benz", "C-Class", "Sedan");
	AdaugaMasina("BV65STU", "Audi", "A4", "Sedan");
	AdaugaMasina("GL98VWX", "Dacia", "Logan", "Sedan");
	AdaugaMasina("CJ24YZA", "Volkswagen", "Passat", "Sedan");
	AdaugaMasina("IS13BCD", "BMW", "Series 3", "Sedan");
	AdaugaMasina("PH86EFG", "Renault", "Clio", "Sport");
	AdaugaMasina("SV57HIJ", "Dacia", "Sandero", "Sport");
}

/* Sorteaza masinile din colectie dupa un criteriu specificat printr-o functie
*  cmp: criteriul de comparare
*  return:-
*/
void ServiceMasina::Sort(cmpFct cmp)
{
	if (cmp == nullptr)
		return;

	MyVector<Masina> all = GetAll();
	for (int i = 0; i < all.Size() - 1; ++i)
		for (int j = i + 1; j < all.Size(); ++j)
			if (cmp(all.at(j), all.at(i)))
			{

				Masina aux = all.at(j);
				all.at(j) = all.at(i);
				all.at(i) = aux;
			}

	repoMasini.SetMasini(all);
}
