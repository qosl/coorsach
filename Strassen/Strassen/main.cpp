#include "tools.h"
#include "classic.h"
#include "strassen.h"
#include "coppersmith_winograd.h"

int main() 
{
	/* set console color */
	//system("color 1E");	
	/* print salutation */
	salutation();		
	/* receive data */
	string lol;			
	getline(cin, lol);
	/* pass data to main activity*/
	main_activity(lol);			
	system("pause");
}
