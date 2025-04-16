#include "teste_domain.h"

void test_masina()
{
	Masina m1;
	assert(m1.GetNrInmatriculare() == "");
	assert(m1.GetProducator() == "");
	assert(m1.GetModel() == "");
	assert(m1.GetTip() == "");

	Masina m2{ "BN10SOS", "BMW", "X6", "SUV" };
	assert(m2.GetNrInmatriculare() == "BN10SOS");
	assert(m2.GetProducator() == "BMW");
	assert(m2.GetModel() == "X6");
	assert(m2.GetTip() == "SUV");

	m2.SetNrInmatriculare("CJ07AND");
	assert(m2.GetNrInmatriculare() == "CJ07AND");
	
	m2.SetProducator("Audi");
	assert(m2.GetProducator() == "Audi");
	
	m2.SetModel("A1");
	assert(m2.GetModel() == "A1");

	m2.SetTip("Sport");
	assert(m2.GetTip() == "Sport");

	Masina m3 = m2;
	assert(m3.GetNrInmatriculare() == "CJ07AND");
	assert(m3.GetProducator() == "Audi");
	assert(m3.GetModel() == "A1");
	assert(m3.GetTip() == "Sport");
}

void test_output_stream()
{
	Masina m{ "BN10PMO", "BMW", "Seria 7", "Sport" };
	std::stringstream out;
	assert(out.str() == "");

	out << m;
	assert(out.str() == "-------------------------\nNr. inmatriculare: BN10PMO\nProducator: BMW\nModel: Seria 7\nTip: Sport\n-------------------------\n");
}

void test_validare()
{
	Validator validator;
	Masina m1{ "BN10ABC", "BMW", "Seria 7", "Sedan"};
	try
	{
		validator.validateMasina(m1);
		assert(true);
	}
	catch (const ValidationException&)
	{
		assert(false);
	}
		
	Masina m2{ "BN10ABC", "", "Seria 7", "Sedan" };
	try
	{
		validator.validateMasina(m2);
		assert(false);
	}
	catch (const ValidationException& e)
	{
		assert(e.GetMsg() == "Producatorul nu poate fi nul\n");
		assert(true);
	}

	Masina m3{ "BN10ABC", "BMW", "", "Sedan" };
	try
	{
		validator.validateMasina(m3);
		assert(false);
	}
	catch (const ValidationException&)
	{
		assert(true);
	}

	Masina m4{ "BN10ABC", "BMW", "Seria 7", "" };
	try
	{
		validator.validateMasina(m4);
		assert(false);
	}
	catch (const ValidationException&)
	{
		assert(true);
	}

	Masina m5{ "", "BMW", "Seria 7", "Sedan" };
	try
	{
		validator.validateMasina(m5);
		assert(false);
	}
	catch (const ValidationException&)
	{
		assert(true);
	}

	Masina m6{ "BN1BCDA", "BMW", "Seria 7", "Sedan" };
	try
	{
		validator.validateMasina(m6);
		assert(false);
	}
	catch (const ValidationException&)
	{
		assert(true);
	}

	Masina m7{ "bn107PC", "BMW", "Seria 7", "Sedan" };
	try
	{
		validator.validateMasina(m7);
		assert(false);
	}
	catch (const ValidationException&)
	{
		assert(true);
	}
}

void teste_domain()
{
	test_masina();
	test_validare();
	test_output_stream();
}

