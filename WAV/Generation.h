#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "createwav.h"
#include <string>
#include <vector>

class Generation {
public:
	static short* GenerateSin(double freq, int volume, double length_time);
	static short* GenerateSquare(double freq, int volume, double length_time);
	static double GetFreq(int key);
	static void GenerateSingleNote();
	static void GenerateSinScale();
	static void GenerateSquareScale();
	static void GenerateTwoNotesTest();
	static void GenerateThreeNotesTest();

	static int GenerateFromFileNotes(std::string filename, std::string type = "sine");
};
