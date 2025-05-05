#include "test_washing_list.h"

void test_adauga()
{
	std::ofstream file("masini_test.txt", std::ios::trunc);
	file.close();
	RepositoryFile repo("masini_test.txt");
	Validator validator;
	ServiceMasina srv{ repo, validator };
	srv.AdaugaMasina("BN11ABC", "BMW", "X6", "Sport");
	srv.AdaugaMasina("SV99XHZ", "Audi", "Seria 7", "SUV");
	srv.AdaugaMasina("BV23LAS", "Mercedes", "C-Class", "SUV");

	WashingList wlist{ srv };
	
	try
	{
		wlist.AdaugaMasina("nu exista");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}

	wlist.AdaugaMasina("SV99XHZ");
	assert(wlist.GetSize() == 1);

	try
	{
		wlist.AdaugaMasina("SV99XHZ");
		assert(false);
	}
	catch (const RepositoryException&)
	{
		assert(true);
	}

	auto& all = wlist.GetAll();
	assert(all.size() == 1);
	assert(all.at(0).GetNrInmatriculare() == "SV99XHZ");

}

void test_goleste()
{
	std::ofstream file("masini_test.txt", std::ios::trunc);
	file.close();
	RepositoryFile repo("masini_test.txt");
	Validator validator;
	ServiceMasina srv{ repo, validator };
	srv.AdaugaMasina("BN11ABC", "BMW", "X6", "Sport");
	srv.AdaugaMasina("SV99XHZ", "Audi", "Seria 7", "SUV");
	srv.AdaugaMasina("BV23LAS", "Mercedes", "C-Class", "SUV");

	WashingList wlist{ srv };
	wlist.AdaugaMasina("BN11ABC");
	wlist.AdaugaMasina("SV99XHZ");
	wlist.AdaugaMasina("BV23LAS");
	assert(wlist.GetSize() == 3);

	wlist.GolesteLista();
	assert(wlist.GetSize() == 0);
}

void test_genereaza()
{
	std::ofstream file("masini_test.txt", std::ios::trunc);
	file.close();
	RepositoryFile repo("masini_test.txt");
	Validator validator;
	ServiceMasina srv{ repo, validator };
	srv.AdaugaDefault();

	WashingList wlist{ srv };
	wlist.GenereazaLista(3);
	assert(wlist.GetSize() == 3);

	wlist.GenereazaLista(7);
	assert(wlist.GetSize() == 7);

	wlist.GenereazaLista(100);
	assert(wlist.GetSize() == srv.GetSize());
}

void test_export()
{
	std::ofstream file("masini_test.txt", std::ios::trunc);
	file.close();
	RepositoryFile repo("masini_test.txt");
	Validator validator;
	ServiceMasina srv{ repo, validator };
	srv.AdaugaMasina("BN11ABC", "BMW", "X6", "Sport");
	srv.AdaugaMasina("SV99XHZ", "Audi", "Seria 7", "SUV");
	srv.AdaugaMasina("BV23LAS", "Mercedes", "C-Class", "SUV");

	WashingList wlist{ srv };
	wlist.AdaugaMasina("BN11ABC");
	wlist.AdaugaMasina("BV23LAS");

	wlist.WriteToFile("test");

	std::ifstream fin("test.csv");
	string str1, str2, line;
	str1 = "BN11ABC,BMW,X6,Sport";
	str2 = "BV23LAS,Mercedes,C-Class,SUV";

	std::getline(fin, line);
	assert(line == str1);
	std::getline(fin, line);
	assert(line == str2);

	fin.close();
}

void test_washing_list()
{
	test_adauga();
	test_goleste();
	test_genereaza();
	test_export();
}
