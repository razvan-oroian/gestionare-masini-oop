#include "WashingList.h"

/* Creeaza un obiect de tip lista 
*  pentru masini care urmeaza sa fie spalate
*  srv: referinta la serviciul care gestioneaza lista de masini sursa
*/
WashingList::WashingList(const ServiceMasina& srv) noexcept : srv{ srv }  {}

/* Sterge toate elementele din lista
*/
void WashingList::GolesteLista() noexcept
{
	masini.clear();
}

/* Adauga o masina din lista sursa dupa numarul de inmatriculare
*  nrInmat: numar de inmatriculare
*  exception: MasinaDoesNotExistException daca nu exista o masina in lista sursa
*				care are numarul de inmatriculare dat
*			  MasinaAlreadyExistsException daca exista deja o masina cu
*               nr de inmatriculare dat in lista curenta
*/
void WashingList::AdaugaMasina(const string& nrInmat)
{
	auto& masina = srv.CautaMasina(nrInmat);
	if (masina.GetNrInmatriculare() == "")
		throw MasinaDoesNotExistException();
	for (auto& m : masini)
		if (m.GetNrInmatriculare() == nrInmat)
			throw MasinaAlreadyExistsException();

	masini.push_back(masina);
}

/* Adauga aleatoriu in lista un numar dat de masini din lista sursa
*  count: numarul dat; daca este mai mare decat lungimea listei sursa
*		se vor adauga toate elementele din lista sursa
*/
void WashingList::GenereazaLista(int count)
{
	GolesteLista();
	const int size = srv.GetSize();
	const auto& all = srv.GetAll();
	if (count > size)
		count = size;

	std::vector<int> poz(size);
	for (int i = 0; i < size; i++)
		poz.at(i) = i;

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(poz.begin(), poz.end(), std::default_random_engine(seed));

	for (int i = 0; i < count; i++)
		masini.push_back(all.at(poz.at(i)));
}

/* Returneaza o referinta la lista de masini care urmeaza sa fie spalate
*/
const std::vector<Masina>& WashingList::GetAll() const noexcept
{
	return masini;
}

/* Returneaza lungimea listei de masini care urmeaza sa fie spalate
*/
const int WashingList::GetSize() const noexcept
{
	return masini.size();
}

void WashingList::WriteToFile(const string& filename) const
{
	string csv_file = filename + ".csv";
	std::ofstream fout(csv_file);

	auto& all = GetAll();
	string masina_str;

	for (auto& masina : all)
	{
		masina_str = masina.GetNrInmatriculare() + ',' + masina.GetProducator() +
			',' + masina.GetModel() + ',' + masina.GetTip() + '\n';
		fout << masina_str;
	}

	fout.close();
}
