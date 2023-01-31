#include <windows.h>
#include <iostream>
#include <debugapi.h>
#include <errhandlingapi.h>

int main()
{
	__try
	{
		char inputchar[1];

		fprintf(stdout, "Try block\n");
		fprintf(stdout, "Enter any key to continue...)\n");
		scanf_s("%1s", inputchar, (unsigned)_countof(inputchar));
		
		fprintf(stdout, "Raise access viotion exception...)\n");
		RaiseException(EXCEPTION_ACCESS_VIOLATION, 0 ,0, NULL);
	}
	/*__except (EXCEPTION_EXECUTE_HANDLER)
	{
		fprintf(stdout, "Exception handler invoked\n");
	}*/
	__finally
	{
		std::cout << "Finally block invoked\n";
	}

}
