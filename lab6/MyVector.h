//#ifndef MYVECTOR_H
//#define MYVECTOR_H
//#include <stdexcept>
//
//template<typename TElem>
//class IteratorVector;
//
///* Vector dinamic generic; poate stoca orice tip de element
//*  size: lungimea vectorului
//*  cap: capacitatea vectorului
//*  elems: elementele vectorului
//*/
//template<typename TElem>
//class MyVector {
//private:
//	int cap;
//	int size;
//	TElem* elems;
//
//public:
//	MyVector();
//	MyVector(int cap);
//	MyVector(const MyVector& other);
//	MyVector(MyVector<TElem>** other);
//	MyVector<TElem>& operator=(MyVector<TElem>&& other) noexcept;
//	void push_back(const TElem& m);
//	IteratorVector<TElem> erase(IteratorVector<TElem> it);
//	const int Size() const noexcept;
//	const int Capacity() const noexcept;
//	IteratorVector<TElem> begin() const noexcept;
//	IteratorVector<TElem> end() const noexcept;
//	TElem& at(int poz);
//	MyVector<TElem>& operator=(const MyVector<TElem>& other);
//	const TElem& at(int poz) const;
//	void clear();
//	~MyVector();
//
//	friend class IteratorVector<TElem>;
//};
//
///* Creeaza un vector dinamic cu 5 elemente
//*/
//template<typename TElem>
//MyVector<TElem>::MyVector() : cap{ 5 }, size{ 0 }, elems{ new TElem[cap] }
//{}
//
///* Creeaza un vector dinamic de o capacitate data
//*  cap: capacitatea data
//*/
//template<typename TElem>
//MyVector<TElem>::MyVector(int cap) : size{ 0 }, cap{ cap }, elems{ new TElem[cap] }
//{}
//
///* Creeaza un vector dinamic prin copierea datelor altui vector
//*  other: alt vector
//*/
//template<typename TElem>
//MyVector<TElem>::MyVector(const MyVector& other) : size {0}, cap {0}
//{
//	elems = new TElem[other.cap];
//	if (elems == nullptr || other.elems == nullptr)
//		return;
//	for (int i = 0; i < other.size; i++)
//		elems[i] = other.elems[i];
//	size = other.size;
//	cap = other.cap;
//}
//
///* Creeaza un vector dinamic prin preluarea datelor de la alt vector R-value
//*  Vectorul sursa este apoi pregatit pentru distrugere
//*  other: vectorul de la care luam datele
//*/
//template<typename TElem>
//MyVector<TElem>::MyVector(MyVector<TElem>** other)
//{
//	elems = other.elems;
//	size = other.size;
//	cap = other.cap;
//
//	other.elems = nullptr;
//	other.size = 0;
//	other.cap = 0;
//}
//
///* Preluam datele de la un alt vector R-value
//*  Vectorul sursa este apoi pregatit pentru distrugere
//*  other: vectorul de la care luam datele
//*  return: referinta la vectorul curent
//*/
//template<typename TElem>
//MyVector<TElem>& MyVector<TElem>::operator=(MyVector<TElem>&& other) noexcept
//{
//	if (this == &other)
//		return *this;
//
//	delete[] elems;
//	elems = other.elems;
//	size = other.size;
//	cap = other.cap;
//
//	other.elems = nullptr;
//	other.size = 0;
//	other.cap = 0;
//
//	return *this;
//}
//
///* Adauga un element la sfarsitul vectorului
//*  m: element adaugat
//*/
//template<typename TElem>
//void MyVector<TElem>::push_back(const TElem& m)
//{
//	if (size == cap)
//	{
//		TElem* new_elems = new TElem[cap * 2];
//		if (new_elems == nullptr || elems == nullptr)
//			return;
//		
//		for (int i = 0; i < size; i++)
//			new_elems[i] = elems[i];
//		if (elems != nullptr)
//			delete[] elems;
//		elems = new_elems;
//		cap *= 2;
//	}
//
//	elems[size] = m;
//	size++;
//}
//
///* Returneaza lungimea vectorului
//*  return: lungime vector
//*/
//template<typename TElem>
//const int MyVector<TElem>::Size() const noexcept
//{
//	return size;
//}
//
///* Returneaza capacitatea vectorului
//*  return: capacitate vector
//*/
//template<typename TElem>
//const int MyVector<TElem>::Capacity() const noexcept
//{
//	return cap;
//}
//
///* Returneaza un iterator care indica spre primul element al vectorului
//*  return: referinta la iterator
//*/
//template<typename TElem>
//IteratorVector<TElem> MyVector<TElem>::begin() const noexcept
//{
//	return IteratorVector<TElem>(*this, 0);
//}
//
///* Returneaza un iterator care indica spre finalul vectorului
//*  return: referinta la iterator
//*/
//template<typename TElem>
//IteratorVector<TElem> MyVector<TElem>::end() const noexcept
//{
//	return IteratorVector<TElem>(*this, size);
//}
//
///* Returneaza o referinta la elementul de la pozitia poz
//*  poz: pozitia data
//*  exception: out_of_range daca pozitia data se afla in afara vectorului
//*  return: referinta la elementul de la pozitia poz
//*/
//template<typename TElem>
//TElem& MyVector<TElem>::at(int poz)
//{
//	if (poz >= size)
//		throw std::out_of_range("out of range");
//	return *(elems + poz);
//}
//
///* Atribuie vectorului curent datele altui vector prin copiere
//*  other: alt vector
//*  return: referinta la vectorul curent
//*/
//template<typename TElem>
//MyVector<TElem>& MyVector<TElem>::operator=(const MyVector<TElem>& other)
//{
//	clear();
//	for (int i = 0; i < other.size; i++)
//		push_back(other.elems[i]);
//
//	return *this;
//}
//
///* Returneaza o referinta constanta la elementul de la pozitia poz
//*  poz: pozitie data
//*  exception: out_of_range daca pozitia data se afla in afara vectorului
//*  return: referinta constanta la elementul de pe pozitia poz
//*/
//template<typename TElem>
//const TElem& MyVector<TElem>::at(int poz) const
//{
//	if (poz >= size)
//		throw std::out_of_range("out of range");
//	return *(elems + poz);
//}
//
///* Goleste vectorul prin stergerea datelor curente
//*/
//template<typename TElem>
//void MyVector<TElem>::clear()
//{
//	size = 0;
//	cap = 5;
//	if (elems != nullptr)
//		delete[] elems;
//	elems = new TElem[cap];
//}
//
///* Sterge elementul indicat de iteratorul it
//*  it: iterator care indica un element valid
//*  return: referinta la un iterator care indica urmatorul element dupa cel sters
//*/
//template<typename TElem>
//IteratorVector<TElem> MyVector<TElem>::erase(IteratorVector<TElem> it)
//{
//	auto start = it;
//	while (it != end())
//	{
//		auto& m = it.element();
//		it.next();
//		m = it.element();
//	}
//	size--;
//	return start;
//}
//
///* Distruge vectorul, dealoca memoria utilizata pentru memorarea elementelor
//*/
//template<typename TElem>
//MyVector<TElem>::~MyVector()
//{
//	if (elems == nullptr)
//		return;
//	delete[] elems;
//}
//
//#endif