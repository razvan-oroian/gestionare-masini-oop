#include "Validator.h"

RepositoryException::RepositoryException(const string& msg) noexcept : msg {msg}
{}

const string& RepositoryException::GetMsg() const noexcept
{
	return msg;
}

MasinaDoesNotExistException::MasinaDoesNotExistException() noexcept : 
	RepositoryException("Masina cu acest numar de inmatriculare nu exista\n")
{}

MasinaAlreadyExistsException::MasinaAlreadyExistsException() noexcept : 
	RepositoryException("Masina cu acest numar de inmatriculare exista deja\n")
{}

ValidationException::ValidationException(const string& msg) noexcept : msg {msg}
{}

const string& ValidationException::GetMsg() const noexcept
{
	return msg;
}

void Validator::validateMasina(const Masina& masina) const
{
	string errors = "";
	string judete = "-AB-AR-AG-BC-BH-BN-BR-BT-BV-BZ-"
		"CS-CL-CJ-CT-CV-DB-DJ-GL-GR-GJ-"
		"HR-HD-IL-IS-IF-MM-MH-MS-NT-OT-"
		"PH-SM-SJ-SB-SV-TR-TM-TL-VS-VL-"
		"VN-B-";

	bool valid = true;
	string nr = masina.GetNrInmatriculare();
	if (nr.size() != 7)
		valid = false;

	if (valid)
	{
		string judet = nr.substr(0, 2);
		string numbers = nr.substr(2, 2);
		string letters = nr.substr(4);

		if ('0' <= judet.at(1) && judet.at(1) <= '1')
		{
			numbers.insert(0, 1, judet.at(1));
			judet.erase(1, 1);
		}

		const size_t poz = judete.find('-' + judet + '-');
		if (poz == string::npos)
			valid = false;

		for (int i = 0; i < numbers.size(); ++i)
			if (numbers.at(i) < '0' || numbers.at(i) > '9')
				valid = false;

		for (int i = 0; i < letters.size(); ++i)
			if (letters.at(i) < 'A' || letters.at(i) > 'Z')
				valid = false;
	}

	if (!valid)
		errors += "Numarul de inmatriculare trebuie sa fie un numar valid romanesc\n";
	if (masina.GetProducator() == "")
		errors += "Producatorul nu poate fi nul\n";
	if (masina.GetModel() == "")
		errors += "Modelul nu poate fi nul\n";
	if (masina.GetTip() == "")
		errors += "Tipul nu poate fi nul\n";

	if (errors.size() > 0)
		throw(ValidationException(errors));
}
