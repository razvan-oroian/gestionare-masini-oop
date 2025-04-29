#include "teste_repo.h"

void test_store()
{
	Repository repo;
	assert(repo.GetSize() == 0);

	Masina m1{ "BN10PMO", "BMW", "Seria 7", "Sedan" };
	repo.Store(m1);

	assert(repo.GetSize() == 1);
	const int poz = repo.Find("BN10PMO");
	assert(repo.GetAll().at(poz).GetProducator() == "BMW");
	assert(repo.GetAll().at(poz).GetModel() == "Seria 7");
	assert(repo.GetAll().at(poz).GetTip() == "Sedan");

	Masina m2{ "BN10PMO", "Audi", "A7", "Sedan" };
	try
	{
		repo.Store(m2);
		assert(false);
	}
	catch (const MasinaAlreadyExistsException& e)
	{
		assert(e.GetMsg() == "Masina cu acest numar de inmatriculare exista deja\n");
		assert(true);
	}
}

void test_update()
{
	Repository repo;
	assert(repo.GetSize() == 0);

	Masina m1{ "BN10ABC", "Audi", "A6", "SUV" };
	repo.Store(m1);
	assert(repo.GetSize() == 1);

	Masina m2{ "BN10ABC", "Toyota", "Corola", "Sedan" };
	repo.Update(m2);
	const int poz = repo.Find("BN10ABC");
	assert(repo.GetAll().at(poz).GetProducator() == "Toyota");
	assert(repo.GetAll().at(poz).GetModel() == "Corola");
	assert(repo.GetAll().at(poz).GetTip() == "Sedan");

	Masina m3{ "CJ11ABC", "Mercedes", "C-Class", "Sport" };
	try
	{
		repo.Update(m3);
		assert(false);
	}
	catch (const MasinaDoesNotExistException&)
	{
		assert(true);
	}
}

void test_delete()
{
	Repository repo;
	assert(repo.GetSize() == 0);

	Masina m1{ "BN10ABC", "Audi", "A6", "SUV" };
	repo.Store(m1);
	assert(repo.GetSize() == 1);

	try
	{
		repo.Delete("BN10XYZ");
		assert(repo.GetSize() == 1);
		assert(false);
	}
	catch (const MasinaDoesNotExistException&)
	{
		assert(true);
	}

	repo.Delete("BN10ABC");
	assert(repo.GetSize() == 0);

	try
	{
		repo.Delete("BN11JJB");
		assert(repo.GetSize() == 0);
		assert(false);
	}
	catch (const MasinaDoesNotExistException&)
	{
		assert(true);
	}
}

void test_find()
{
	Repository repo;
	assert(repo.GetSize() == 0);

	Masina m1{ "BN10ABC", "Audi", "A6", "SUV" };
	Masina m2{ "CJ12XYZ", "Toyota", "Corola", "Sedan" };
	Masina m3{ "BV99PMO", "BMW", "Seria 7", "Sedan" };
	repo.Store(m1);
	repo.Store(m2);
	repo.Store(m3);

	int poz = repo.Find("CT03ABC");
	assert(poz == -1);

	poz = repo.Find("CJ12XYZ");
	assert(repo.GetAll().at(poz).GetProducator() == "Toyota");
	assert(repo.GetAll().at(poz).GetModel() == "Corola");
	assert(repo.GetAll().at(poz).GetTip() == "Sedan");
}

void test_set()
{
	Repository repo;

	std::vector<Masina> v;
	v.push_back(Masina{ "BN11ABC", "abc", "abc", "abc" });
	v.push_back(Masina{ "CJ11ADC", "abc", "abc", "abc" });
	v.push_back(Masina{ "BV99XYZ", "abc", "abc", "abc" });

	repo.SetMasini(v);
	assert(repo.GetSize() == 3);

	int poz = repo.Find("BN11ABC");
	assert(poz != -1);
	poz = repo.Find("CJ11ADC");
	assert(poz != -1);
	poz = repo.Find("BV99XYZ");
	assert(poz != -1);
}

void teste_repo()
{
	test_store();
	test_update();
	test_delete();
	test_find();
	test_set();
}
