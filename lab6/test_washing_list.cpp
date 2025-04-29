#include "test_washing_list.h"

void test_adauga()
{
	ServiceMasina srv;
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
	ServiceMasina srv;
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
	ServiceMasina srv;
	srv.AdaugaDefault();

	WashingList wlist{ srv };
	wlist.GenereazaLista(3);
	assert(wlist.GetSize() == 3);

	wlist.GenereazaLista(7);
	assert(wlist.GetSize() == 7);

	wlist.GenereazaLista(100);
	assert(wlist.GetSize() == srv.GetSize());
}

void test_washing_list()
{
	test_adauga();
	test_goleste();
	test_genereaza();
}
