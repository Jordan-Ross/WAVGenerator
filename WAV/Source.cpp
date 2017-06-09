#include "createwav.h"
#include "Generation.h"


int main() {
	//Generation::GenerateSingleNote();
	//Generation::GenerateTwoNotesTest();
	//Generation::GenerateFromFileNotes("notes");
	//Generation::FromData();
	//Generation::GenerateThreeNotesTest();
	Generation::GenerateFromFileNotes("notes", "square");
	//Generation::GenerateSinScale();
	return 0;
}
