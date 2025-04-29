//#ifndef ITERATORVECTOR_H
//#define ITERATORVECTOR_H
//#include "MyVector.h"
//#include <exception>
//#include <stdexcept>
//
///* Iterator generic pentru clasa MyVector
//*  v: referinta la vectorul spre care indica
//*  poz: pozitia curenta pe care o indica
//*/
//template<typename TElem> 
//class IteratorVector {
//private:
//	const MyVector<TElem>& v;
//	int poz = 0;
//
//public:
//	IteratorVector(const MyVector<TElem>& vct) noexcept;
//	IteratorVector(const MyVector<TElem>& vct, int poz) noexcept;
//	bool operator==(const IteratorVector& ot) const noexcept;
//	bool operator!=(const IteratorVector& ot) const noexcept;
//	TElem& operator*() const noexcept;
//	IteratorVector<TElem>& operator++();
//	IteratorVector<TElem>& operator+(const int val);
//	bool valid() const noexcept;
//	TElem& element() const noexcept;
//	void next();
//};
//
///* Creeaza un iterator care indica spre un vector dat
//* 
//*/
//template<typename TElem>
//IteratorVector<TElem>::IteratorVector(const MyVector<TElem>& vct) noexcept : v {vct}
//{}
//
///* Creeaza un iterator care indica spre un vector dat la pozitia poz
//*  poz: pozitie valida
//*  v: vector
//*/
//template<typename TElem>
//IteratorVector<TElem>::IteratorVector(const MyVector<TElem>& vct, int poz) noexcept : v{ vct }, poz{ poz }
//{}
//
///* Verifica relatia de == dintre 2 iteratori dupa pozitiile care le indica
//*  ot: un iterator
//*  return: true/false
//*/
//template<typename TElem>
//bool IteratorVector<TElem>::operator==(const IteratorVector & ot) const noexcept
//{
//	return poz == ot.poz;
//}
//
///* Verifica relatia de != dintre 2 iteratori dupa pozitiile pe care le indica
//*  ot: un iterator
//*  return: true/false
//*/
//template<typename TElem>
//bool IteratorVector<TElem>::operator!=(const IteratorVector& ot) const noexcept
//{
//	return poz != ot.poz;
//}
//
///* Returneaza o referinta la elementul indicat de iterator
//*  return: referinta la un element
//*/
//template<typename TElem>
//TElem& IteratorVector<TElem>::operator*() const noexcept
//{
//	return element();
//}
//
///* Iteratorul trece la urmatoarea pozitie din vector
//*  exception: out_of_range daca iteratorul nu este valid
//*  return: referinta la iteratorul curent
//*/
//template<typename TElem>
//IteratorVector<TElem>& IteratorVector<TElem>::operator++()
//{
//	next();
//	return *this;
//}
//
///* Relatia de adunare dintre un iterator si un intreg
//*  Se aduna la pozitia iteratorului intregul dat
//*  v: intreg dat
//*  exception: out_of_range daca iteratorul obtinut nu mai este valid
//*  return: referinta la iteratorul curent
//*/
//template<typename TElem>
//IteratorVector<TElem>& IteratorVector<TElem>::operator+(const int val)
//{
//	poz += val;
//	if (!valid())
//		throw std::out_of_range("out of range");
//	return *this;
//}
//
///* Verifica daca iteratorul indica un element valid din interiorul vectorului
//*  return: true/false
//*/
//template<typename TElem>
//bool IteratorVector<TElem>::valid() const noexcept
//{
//	return poz < v.Size();
//}
//
///* Returneaza o referinta la elementul indicat de iterator
//*  return: referinta la un element
//*/
//template<typename TElem>
//TElem& IteratorVector<TElem>::element() const noexcept
//{
//	return v.elems[poz];
//}
//
///* Iteratorul trece la urmatoarea pozitie din vector
//*  exception: out_of_range daca iteratorul nu este valid
//*/
//template<typename TElem>
//void IteratorVector<TElem>::next()
//{
//	if (!valid())
//		throw std::out_of_range("out of range");
//	poz++;
//}
//
//#endif