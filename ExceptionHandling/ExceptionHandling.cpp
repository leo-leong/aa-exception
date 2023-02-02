#include <windows.h>
#include <iostream>
#include <debugapi.h>
#include <errhandlingapi.h>

int FilterException(unsigned int code, struct _EXCEPTION_POINTERS* ep)
{
	if (code == EXCEPTION_ACCESS_VIOLATION)
	{
		fprintf(stdout, "\n1st chance EXCEPTION_ACCESS_VIOLATION raised and proceeding to handle exception.\n");
		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		fprintf(stdout, "\nNot handling raised 1st chance exception and expecting to crash. Check the Event Application Log for a Windows Error Reporting entry.\n");
		return EXCEPTION_CONTINUE_SEARCH;
	};
}

int main()
{
	__try
	{
		int option;
		do {
			fprintf(stdout, "\n\nThis is a sample console app intended to demo 1st and 2nd chance exception behaviors.\n");
			fprintf(stdout, "Currently in a try block. Please choose the following options to proceed:\n\n");
			fprintf(stdout, "\t\t1. Raise a 1st chance exception and handle it\n");
			fprintf(stdout, "\t\t2. Raise a 1st chance exception but let is escalate to 2nd chance and crash\n");
			fprintf(stdout, "\n\t\tEnter Your Option: ");
			fflush(stdin);
			scanf_s("%d", &option); 
			if (option < 1 || option > 2) {
				fprintf(stderr, "\n\t\t *** Invalid Option, hit enter to continue.\n");
				getchar();
				continue;
			}
			else
				break;
		} while (1);
		
		if (1 == option)
		{
			RaiseException(EXCEPTION_ACCESS_VIOLATION, 0, 0, NULL);
		}
		else
		{
			RaiseException(EXCEPTION_NONCONTINUABLE, 0, 0, NULL);
		}
		
	}
	__except (FilterException(GetExceptionCode(), GetExceptionInformation()))
	{
		fprintf(stdout, "\Exception caught and handled. Exiting process...\n\n");
	}

}
