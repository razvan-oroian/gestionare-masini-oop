#include "a.h"
#include "Console.h"
#include "MyVector.h"
#include "IteratorVector.h"
#include <crtdbg.h>
#include <vector>

void main2()
{
	Console console;
	console.Run();
}

int main()
{
	main2();
	_CrtDumpMemoryLeaks();
	return 0;
}