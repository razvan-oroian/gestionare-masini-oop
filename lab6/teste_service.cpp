#include "teste_service.h"

void testAdaugaMasina()
{
	ServiceMasina srv;
	assert(srv.GetSize() == 0);

	srv.AdaugaMasina("BN10PMO", "BMW", "Seria 7", "SUV");
	
	assert(srv.GetSize() == 1);
	const Masina& masina = srv.CautaMasina("BN10PMO");

	assert(masina.GetProducator() == "BMW");
	assert(masina.GetModel() == "Seria 7");
	assert(masina.GetTip() == "SUV");

	try {
		srv.AdaugaMasina("BN10PMO", "Audi", "A6", "Sport");
		assert(false);
	}
	catch (const MasinaAlreadyExistsException&) {
		assert(true);
	}

	try {
		srv.AdaugaMasina("CJ10PMO", "BMW", "Seria 7", "");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

	try {
		srv.AdaugaMasina("CJ10PMO", "BMW", "", "SUV");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

	try {
		srv.AdaugaMasina("CJ10PMO", "", "Seria 7", "SUV");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

	try {
		srv.AdaugaMasina("", "BMW", "Seria 7", "SUV");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

	try {
		srv.AdaugaMasina("bN101om", "BMW", "Seria 7", "SUV");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}
}

void testStergeMasina()
{
	ServiceMasina srv;
	assert(srv.GetSize() == 0);
	srv.AdaugaMasina("BN10PMO", "BMW", "Seria 7", "SUV");
	assert(srv.GetSize() == 1);

	try {
		srv.StergeMasina("CJ16TSP");
		assert(srv.GetSize() == 1);
		assert(false);
	}
	catch (const MasinaDoesNotExistException&) {
		assert(true);
	}

	srv.StergeMasina("BN10PMO");
	assert(srv.GetSize() == 0);

	try {
		srv.StergeMasina("CT99ABC");
		assert(srv.GetSize() == 0);
		assert(false);
	}
	catch (const MasinaDoesNotExistException&) {
		assert(true);
	}
}

void testModificaMasina()
{
	ServiceMasina srv;
	assert(srv.GetSize() == 0);
	srv.AdaugaMasina("CJ11ABC", "BMW", "Seria 7", "SUV");
	assert(srv.GetSize() == 1);

	srv.ModificaMasina("CJ11ABC", "Audi", "A6", "Sport");
	const Masina& masina = srv.CautaMasina("CJ11ABC");

	assert(masina.GetProducator() == "Audi");
	assert(masina.GetModel() == "A6");
	assert(masina.GetTip() == "Sport");

	try {
		srv.ModificaMasina("CJ10ABC", "Audi", "A9", "Sport");
		assert(false);
	}
	catch (const MasinaDoesNotExistException&) {
		assert(true);
	}

	try {
		srv.ModificaMasina("CJ11ABC", "Audi", "A9", "");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

	try {
		srv.ModificaMasina("CJ11ABC", "Audi", "", "Sport");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

	try {
		srv.ModificaMasina("CJ11ABC", "", "A9", "Sport");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

	try {
		srv.ModificaMasina("", "Audi", "A9", "Sport");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

	try {
		srv.ModificaMasina("B12DABC", "Audi", "A9", "Sport");
		assert(false);
	}
	catch (const ValidationException&) {
		assert(true);
	}

}

void testCautaMasina()
{
	ServiceMasina srv;
	assert(srv.GetSize() == 0);
	srv.AdaugaMasina("BN10PMO", "BMW", "Seria 7", "SUV");
	assert(srv.GetSize() == 1);

	const Masina& masina1 = srv.CautaMasina("CT99PMO");
	assert(masina1.GetProducator() == "");
	assert(masina1.GetModel() == "");
	assert(masina1.GetTip() == "");

	const Masina& masina2 = srv.CautaMasina("BN10PMO");
	assert(masina2.GetProducator() == "BMW");
	assert(masina2.GetModel() == "Seria 7");
	assert(masina2.GetTip() == "SUV");
}

void testFiltrareDupaProducator()
{
	ServiceMasina srv;
	assert(srv.GetSize() == 0);
	srv.AdaugaMasina("B123ABC", "Dacia", "Duster", "SUV");
	srv.AdaugaMasina("TM45XYZ", "Volkswagen", "Golf", "Sport");
	srv.AdaugaMasina("IF78MNO", "BMW", "X5", "SUV");
	srv.AdaugaMasina("GL98VWX", "Dacia", "Logan", "Sedan");
	srv.AdaugaMasina("BV65STU", "Audi", "A4", "Sedan");
	assert(srv.GetSize() == 5);

	MyVector<Masina> filtrate;
	srv.FiltrareDupaProducator(filtrate, "Dacia");
	assert(filtrate.Size() == 2);
	assert(filtrate.at(0).GetNrInmatriculare() == "B123ABC");
	assert(filtrate.at(1).GetNrInmatriculare() == "GL98VWX");
}

void testFiltrareDupaTip()
{
	ServiceMasina srv;
	assert(srv.GetSize() == 0);
	srv.AdaugaMasina("B123ABC", "Dacia", "Duster", "SUV");
	srv.AdaugaMasina("TM45XYZ", "Volkswagen", "Golf", "Sport");
	srv.AdaugaMasina("IF78MNO", "BMW", "X5", "SUV");
	srv.AdaugaMasina("GL98VWX", "Dacia", "Logan", "Sedan");
	srv.AdaugaMasina("BV65STU", "Audi", "A4", "Sedan");
	assert(srv.GetSize() == 5);

	MyVector<Masina> filtrate;
	srv.FiltrareDupaTip(filtrate, "SUV");
	assert(filtrate.Size() == 2);
	assert(filtrate.at(0).GetNrInmatriculare() == "B123ABC");
	assert(filtrate.at(1).GetNrInmatriculare() == "IF78MNO");
}

void testSort()
{
	ServiceMasina srv;
	assert(srv.GetSize() == 0);
	srv.AdaugaMasina("B123ABC", "Dacia", "Duster", "SUV");
	srv.AdaugaMasina("TM45XYZ", "Volkswagen", "Golf", "Sport");
	srv.AdaugaMasina("IF78MNO", "BMW", "X5", "SUV");
	srv.AdaugaMasina("AG32PQR", "Mercedes-Benz", "C-Class", "Sedan");
	srv.AdaugaMasina("BV65STU", "Audi", "A4", "Sedan");
	srv.AdaugaMasina("GL98VWX", "Dacia", "Logan", "Sedan");
	srv.AdaugaMasina("CJ24YZA", "Volkswagen", "Passat", "Sedan");
	srv.AdaugaMasina("IS13BCD", "BMW", "Series 3", "Sedan");
	srv.AdaugaMasina("PH86EFG", "Renault", "Clio", "Sport");
	srv.AdaugaMasina("SV57HIJ", "Dacia", "Sandero", "Sport");

	assert(srv.GetSize() == 10);

	srv.Sort([](const Masina& m1, const Masina& m2) {
		return m1.GetNrInmatriculare() < m2.GetNrInmatriculare();
		});


	const MyVector<Masina>& all = srv.GetAll();
	assert(all.at(0).GetNrInmatriculare() == "AG32PQR");
	assert(all.at(1).GetNrInmatriculare() == "B123ABC");
	assert(all.at(2).GetNrInmatriculare() == "BV65STU");
	assert(all.at(3).GetNrInmatriculare() == "CJ24YZA");
	assert(all.at(4).GetNrInmatriculare() == "GL98VWX");
	assert(all.at(5).GetNrInmatriculare() == "IF78MNO");
	assert(all.at(6).GetNrInmatriculare() == "IS13BCD");
	assert(all.at(7).GetNrInmatriculare() == "PH86EFG");
	assert(all.at(8).GetNrInmatriculare() == "SV57HIJ");
	assert(all.at(9).GetNrInmatriculare() == "TM45XYZ");

	srv.Sort([](const Masina& m1, const Masina& m2) {
		return m1.GetProducator() < m2.GetProducator();
		});

	assert(all.at(0).GetNrInmatriculare() == "BV65STU");
	assert(all.at(1).GetNrInmatriculare() == "IF78MNO");
	assert(all.at(2).GetNrInmatriculare() == "IS13BCD");
	assert(all.at(3).GetNrInmatriculare() == "B123ABC");
	assert(all.at(4).GetNrInmatriculare() == "GL98VWX");
	assert(all.at(5).GetNrInmatriculare() == "SV57HIJ");
	assert(all.at(6).GetNrInmatriculare() == "AG32PQR");
	assert(all.at(7).GetNrInmatriculare() == "PH86EFG");
	assert(all.at(8).GetNrInmatriculare() == "CJ24YZA");
	assert(all.at(9).GetNrInmatriculare() == "TM45XYZ");

	srv.Sort(nullptr);
	assert(all.at(0).GetNrInmatriculare() == "BV65STU");
	assert(all.at(1).GetNrInmatriculare() == "IF78MNO");
	assert(all.at(2).GetNrInmatriculare() == "IS13BCD");
	assert(all.at(3).GetNrInmatriculare() == "B123ABC");
	assert(all.at(4).GetNrInmatriculare() == "GL98VWX");
	assert(all.at(5).GetNrInmatriculare() == "SV57HIJ");
	assert(all.at(6).GetNrInmatriculare() == "AG32PQR");
	assert(all.at(7).GetNrInmatriculare() == "PH86EFG");
	assert(all.at(8).GetNrInmatriculare() == "CJ24YZA");
	assert(all.at(9).GetNrInmatriculare() == "TM45XYZ");

}

void teste_service()
{
	testAdaugaMasina();
	testStergeMasina();
	testModificaMasina();
	testCautaMasina();
	testFiltrareDupaProducator();
	testFiltrareDupaTip();
	testSort();
}
