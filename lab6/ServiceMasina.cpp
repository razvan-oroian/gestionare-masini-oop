#include "ServiceMasina.h"
#include "WashingList.h"
/* Creeaza un obiect de tip serviciu pentru masini
*  return:-
*/
ServiceMasina::ServiceMasina(RepositoryFile& repo, Validator& validator) : repoMasini { repo }, validator { validator }
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
	UndoAdauga* ua = new UndoAdauga(repoMasini, nrInmatriculare);
	listaUndo.push_back(ua);
}

/* Returneaza colectia de masini
*  return: vector de masini
*/
const std::vector<Masina>& ServiceMasina::GetAll() const noexcept
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
	auto masina = CautaMasina(nrInmatriculare);

	repoMasini.Delete(nrInmatriculare);
	UndoSterge* us = new UndoSterge(repoMasini, masina);
	listaUndo.push_back(us);
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

	auto masina_veche = CautaMasina(nrInmatriculare);

	repoMasini.Update(masina);

	UndoModifica* um = new UndoModifica(repoMasini, masina_veche);
	listaUndo.push_back(um);
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
void ServiceMasina::FiltrareDupaProducator(std::vector<Masina>& filtrate, const string& producator) const

{
	auto& masini = GetAll();
	std::copy_if(masini.begin(), masini.end(), std::back_inserter(filtrate), [&producator](const Masina& m) {return m.GetProducator() == producator; });
	/*for (const Masina& masina : repoMasini.GetAll())
		if (masina.GetProducator() == producator)
			filtrate.push_back(masina);*/
}

/* Selecteaza din colectia de masini pe acelea care au un tip dat
*  filtrate: vectorul in care se adauga masinile selectate
*  tip: tipul dat
*  return:-
*/
void ServiceMasina::FiltrareDupaTip(std::vector<Masina>& filtrate, const string& tip) const
{
	auto& masini = GetAll();
	auto it = std::copy_if(masini.begin(), masini.end(), std::back_inserter(filtrate), [&tip](const Masina& m) {return m.GetTip() == tip; });

	/*for (const Masina& masina : repoMasini.GetAll())
		if (masina.GetTip() == tip)
			filtrate.push_back(masina);*/
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

	auto all = GetAll();
	sort(all.begin(), all.end(), cmp);
	repoMasini.SetMasini(all);
	repoMasini.writeToFile();

	/*for (int i = 0; i < all.size() - 1; ++i)
		for (int j = i + 1; j < all.size(); ++j)
			if (cmp(all.at(j), all.at(i)))
			{

				Masina aux = all.at(j);
				all.at(j) = all.at(i);
				all.at(i) = aux;
			}*/

}

/* Reface starea listei de masini dinaintea ultimei operatii
*  exception: daca nu se mai poate efectua undo
*/

void ServiceMasina::Undo()
{
	if (listaUndo.empty())
		throw std::exception("Nu se mai poate face undo!\n");

	listaUndo.back()->doUndo();
	delete listaUndo.back();
	listaUndo.pop_back();
	repoMasini.writeToFile();
}

/* Distruge service-ul si dealoca memoria rezervata acestuia
*/
ServiceMasina::~ServiceMasina()
{
	if (!listaUndo.empty())
		for (auto& act : listaUndo)
			delete act;
}
