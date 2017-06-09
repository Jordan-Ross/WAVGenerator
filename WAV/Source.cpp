#include "createwav.h"
#include "Generation.h"


int main() {
	//Generation::GenerateSingleNote();
	//Generation::GenerateTwoNotesTest();
	//Generation::GenerateFromFileNotes("notes");
	//Generation::FromData();
	//Generation::GenerateThreeNotesTest();
	//Generation::GenerateSinScale();
	

	// Get success code from Generation for errors on file reading
	return Generation::GenerateFromFileNotes("../Examples/notes", "square");
}
