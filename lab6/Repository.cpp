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
	int i = 0;
	for (auto masina : masini)
	{
		if (masini.at(i).GetNrInmatriculare() == nrInmatriculare)
			return i;
		++i;
	}

	return -1;
}

/* Returneaza colectia de masini
*  return: vector de masini
*/
const std::vector<Masina>& Repository::GetAll() const noexcept
{
	return masini;
}

/* Seteaza colectia de masini gestionata de repository
*  masini_noi: vector de masini
*  return:-
*/
void Repository::SetMasini(const std::vector<Masina>& masini_noi)
{
	masini = masini_noi;
}

/* Returneaza numarul de masini din colectie
*  return: nr de masini
*/
const size_t Repository::GetSize() const noexcept
{
	return masini.size();
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

/* Adauga in lista masinile din fisierul repository-ului
*  exception: daca fisierul nu a putut fi deschis
*/
void RepositoryFile::loadFromFile()
{
	std::ifstream fin(filename);
	string line;
	string nrInmat, producator, model, tip;
	int start, end;
	

	while (std::getline(fin, line))
	{
		if (line == "")
			continue;
		start = 0;
		end = line.find_first_of(',');
		nrInmat = line.substr(start, end - start);

		end++;
		start = end;
		end = line.find_first_of(',', end);
		producator = line.substr(start, end - start);

		end++;
		start = end;
		end = line.find_first_of(',', end);
		model = line.substr(start, end - start);

		start = end + 1;
		tip = line.substr(start, string::npos);

		Masina m{ nrInmat, producator, model, tip };
		masini.push_back(m);
	}
	
}

/* Scrie in fisierul repository-ului lista de masini
*  exception: daca fisierul nu a putut fi deschis
*/
void RepositoryFile::writeToFile()
{
	std::ofstream fout(filename);
	string masina_str;

	for (auto& masina : masini)
	{
		masina_str = masina.GetNrInmatriculare() + ',' + masina.GetProducator() +
			',' + masina.GetModel() + ',' + masina.GetTip() + '\n';
		fout << masina_str;
	}

	fout.close();
}

/* Creeaza un obiect de tip repository cu fisier
*  filename: fisier dat
*/
RepositoryFile::RepositoryFile(const string& filename) : filename { filename }
{
	loadFromFile();
}

/* Adauga o masina in lista de masini si actualizeaza fisierul
*  masina: masina data
*  post: este scrisa in fisier lista curenta
*/
void RepositoryFile::Store(const Masina& masina)
{
	Repository::Store(masina);
	writeToFile();
}

/* Sterge o masina din lista de masini pe baza nr de inmatriculare si actualizeaza fisierul
*  nrInmatricular: numar de inmatriculare dat
*  post: este scrisa in fisier lista curenta
*/
void RepositoryFile::Delete(const string& nrInmatriculare)
{
	Repository::Delete(nrInmatriculare);
	writeToFile();
}

/* Modifica datele masinii care are un nr de inmatriculare dat si actualizeaza fisierul
*  masina: masina noua
*  post: este scrisa in fisier lista curenta
*/
void RepositoryFile::Update(const Masina& masina)
{
	Repository::Update(masina);
	writeToFile();
}
