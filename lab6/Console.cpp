#include "Console.h"

/* Creeaza un obiect de tip consola
*  return:-
*/
Console::Console() noexcept : wlist(srvMasina)
{}

/* Executa aplicatia
*  return:-
*/
void Console::Run()
{
	run_tests();
	std::cout << "Testele au trecut cu succes!\n";

	srvMasina.AdaugaDefault();
	bool is_running = true;
	string optiune;

	while (is_running)
	{
		AfiseazaMeniu();
		std::cout << "Introduceti optiunea dorita: ";
		std::cin >> optiune;
		if (optiune.size() > 1)
		{
			std::cout << "Optiune invalida\n";
			continue;
		}

		switch (toupper(optiune.at(0))) {
			case '1':
				AdaugaMasinaUi();
				break;
			case '2':
				StergeMasinaUi();
				break;
			case '3':
				ModificaMasinaUi();
				break;
			case '4':
				CautaMasinaUi();
				break;
			case '5':
				FiltrareDupaProducatorUi();
				break;
			case '6':
				FiltrareDupaTipUi();
				break;
			case '7':
				SortDupaNrInmatriculare();
				break;
			case '8':
				SortDupaTip();
				break;
			case '9':
				SortDupaProducatorModel();
				break;
			case 'X':
				is_running = false;
				break;
			case 'P':
				AfiseazaMasini(srvMasina.GetAll());
				break;
			case 'A':
				AdaugaMasinaSpalatUi();
				break;
			case 'W':
				AfiseazaMasini(wlist.GetAll());
				break;
			case 'G':
				wlist.GolesteLista();
				std::cout << "Numar masini: " << wlist.GetSize() << '\n';
				break;
			case 'R':
				GenereazaMasiniSpalatUi();
				break;
			case 'S':
				WriteToFileUi();
				break;
			default:
				std::cout << "Optiune invalida\n";
				break;
		}
	}
}

/* Adauga o masina in colectie pe baza datelor citite
*  return:-
*/
void Console::AdaugaMasinaUi()
{
	string nrInmatriculare, producator, model, tip;
	CitesteDate(nrInmatriculare, producator, model, tip);
	
	try 
	{
		srvMasina.AdaugaMasina(nrInmatriculare, producator, model, tip);
	}
	catch (const ValidationException& e)
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << e.GetMsg();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
	catch (const RepositoryException& e)
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << e.GetMsg();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
}

/* Citeste datele necesare crearii unei masini
*  nrInmatriculare: adresa la care se citeste nr masinii
*  producator: adresa la care se citeste producatorul masinii
*  model: adresa la care se citeste modelul masinii
*  tip: adresa la care se citeste tipul masinii
*/
void Console::CitesteDate(string& nrInmatriculare, string& producator, string& model, string& tip) const
{
	std::cin.get();
	std::cout << "Introduceti numarul de inmatriculare:";
	std::getline(std::cin, nrInmatriculare);

	std::cout << "Introduceti producatorul:";
	std::getline(std::cin, producator);

	std::cout << "Introduceti modelul:";
	std::getline(std::cin, model);

	std::cout << "Introduceti tipul:";
	std::getline(std::cin, tip);
}

/* Afiseaza colectia de masini
*  return:-
*/
void Console::AfiseazaMasini(const std::vector<Masina>& all) const
{
	for (const Masina& masina : all)
		std::cout << masina;
}

/* Sterge o masina pe baza datelor citite
*  return:-
*/
void Console::StergeMasinaUi()
{
	string nrInmatriculare;
	std::cin.get();
	std::cout << "Introduceti numarul de inmatriculare:";
	std::getline(std::cin, nrInmatriculare);


	try
	{
		srvMasina.StergeMasina(nrInmatriculare);
	}
	catch (const RepositoryException& e)
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << e.GetMsg();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}

}

/* Modifica o masina pe baza datelor citite
*  retunr:-
*/
void Console::ModificaMasinaUi()
{
	string nrInmatriculare, producator, model, tip;
	CitesteDate(nrInmatriculare, producator, model, tip);

	try
	{
		srvMasina.ModificaMasina(nrInmatriculare, producator, model, tip);
	}
	catch (const ValidationException& e)
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << e.GetMsg();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
	catch (const RepositoryException& e)
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << e.GetMsg();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
}

/* Afiseaza masina cu nr de inmatriculare citit
*  return:-
*/
void Console::CautaMasinaUi() const
{
	string nrInmatriculare;
	std::cin.get();
	std::cout << "Introduceti numarul de inmatriculare:";
	std::getline(std::cin, nrInmatriculare);

	std::cout << srvMasina.CautaMasina(nrInmatriculare);
}

/* Afiseaza lista de masini care au un producator dat
*  return:-
*/
void Console::FiltrareDupaProducatorUi() const
{
	string producator;
	std::cin.get();
	std::cout << "Introduceti producatorul:";
	std::getline(std::cin, producator);

	std::vector<Masina> filtrate;
	srvMasina.FiltrareDupaProducator(filtrate, producator);

	for (const Masina& masina : filtrate)
		std::cout << masina;
}

/* Afiseaza lista de masini care au un tip dat
*  return:-
*/
void Console::FiltrareDupaTipUi() const
{
	string tip;
	std::cin.get();
	std::cout << "Introduceti tipul:";
	std::getline(std::cin, tip);

	std::vector<Masina> filtrate;
	srvMasina.FiltrareDupaTip(filtrate, tip);

	for (const Masina& masina : filtrate)
		std::cout << masina;
}

/* Sorteaza colectia de masini dupa nr de inmatriculare
*  return:-
*/
void Console::SortDupaNrInmatriculare()
{
	srvMasina.Sort([](const Masina& m1, const Masina& m2) {
		return m1.GetNrInmatriculare() < m2.GetNrInmatriculare();
		});
}

/* Sorteaza colectia de masini dupa tip
*  return:-
*/
void Console::SortDupaTip()
{
	srvMasina.Sort([](const Masina& m1, const Masina& m2) {
		return m1.GetTip() < m2.GetTip();
		});
}

/* Sorteaza colectia de masini dupa model
*  return:-
*/
void Console::SortDupaProducatorModel()
{
	srvMasina.Sort([](const Masina& m1, const Masina& m2) {
		return m1.GetProducator() < m2.GetProducator() ||
			(m1.GetProducator() == m2.GetProducator() &&
			 m1.GetModel() < m2.GetModel());
		});
}

/* Citeste un nr de inmatriculare si adauga in lista de spalare
*/
void Console::AdaugaMasinaSpalatUi()
{
	string nrInmat;
	std::cin.get();
	std::cout << "Introduceti nr de inmatriculare:";
	std::getline(std::cin, nrInmat);

	try {
		wlist.AdaugaMasina(nrInmat);
		std::cout << "Numar masini: " << wlist.GetSize() << '\n';
	}
	catch (const RepositoryException& e)
	{
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::cout << e.GetMsg();
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
}

/* Citeste un numar si genereaza masinile in lista de spalare
*/
void Console::GenereazaMasiniSpalatUi()
{
	int count;
	std::cout << "Introduceti un numar:";
	std::cin >> count;

	wlist.GenereazaLista(count);
	std::cout << "Numar masini: " << wlist.GetSize() << '\n';
}

void Console::WriteToFileUi()
{
	string filename;
	std::cout << "Introduceti numele fisierului: ";
	std::cin >> filename;

	wlist.WriteToFile(filename);
}

/* Afiseaza meniul aplicatiei
*  return:-
*/
void Console::AfiseazaMeniu() const
{	
	std::cout << "**********************************\n";
	std::cout<< "1. Adauga o masina\n"
		<< "2. Sterge o masina\n"
		<< "3. Modifica o masina\n"
		<< "4. Cauta masina\n"
		<< "5. Filtreaza dupa producator\n"
		<< "6. Filtreaza dupa tip\n"
		<< "7. Sorteaza dupa numarul de inmatriculare\n"
		<< "8. Sorteaza dupa tip\n"
		<< "9. Sorteaza dupa producator si model\n"
		<< "A. Adauga la lista de masini care urmeaza sa fie spalate\n"
		<< "W. Afiseaza masini care urmeaza sa fie spalate\n"
		<< "G. Goleste lista de masini care urmeaza sa fie spalate\n"
		<< "R. Genereaza masini care urmeaza sa fie spalate\n"
		<< "S. Salveaza masinile care urmeaza sa fie spalate intr-un fisier\n"
		<< "X. Iesire aplicatie\n"
		<< "P. Afiseaza masini\n";
	std::cout << "**********************************\n";
}
