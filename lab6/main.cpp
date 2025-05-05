#include "a.h"
#include "Console.h"
#include "MyVector.h"
#include "IteratorVector.h"
#include <crtdbg.h>
#include <vector>

void main2()
{
	RepositoryFile repo("masini.txt");
	Validator validator;
	ServiceMasina srv(repo, validator);
	Console console(srv);
	console.Run();
}

int main()
{
	main2();
	_CrtDumpMemoryLeaks();
	return 0;
}