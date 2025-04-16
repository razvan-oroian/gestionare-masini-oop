#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "a.h"
#include "Masina.h"
#include <exception>

class MasinaException : public std::exception {
public:
	MasinaException() = default;
};

class RepositoryException : public MasinaException {
private:
	string msg;
public:
	RepositoryException(const string& msg) noexcept;
	const string& GetMsg() const noexcept;
};

class MasinaDoesNotExistException : public RepositoryException {
public:
	MasinaDoesNotExistException() noexcept;
};

class MasinaAlreadyExistsException : public RepositoryException {
public:
	MasinaAlreadyExistsException() noexcept;
};

class ValidationException : public MasinaException {
private:
	string msg;
public:
	ValidationException(const string& msg) noexcept;
	const string& GetMsg() const noexcept;
};

class Validator {
public:
	Validator() = default;
	void validateMasina(const Masina& masina) const;
};


#endif