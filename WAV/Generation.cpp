#include "Generation.h"

SAMPLE* Generation::GenerateSin(double freq, int volume, double length_time) {
	int samples = SAMPLERATE * length_time * sizeof(SAMPLE) * CHANNELS;
	SAMPLE* waveform = new SAMPLE[samples];
	for (int s = 0; s < samples; s++) {
		double t = (double)s / SAMPLERATE;
		waveform[s] = volume*sin(freq * t * M_PI);
	}
	return waveform;
}

SAMPLE* Generation::GenerateSquare(double freq, int volume, double length_time) {
	int samples = SAMPLERATE * length_time * sizeof(SAMPLE) * CHANNELS;
	SAMPLE* waveform = new short[samples];
	for (int s = 0; s < samples; s++) {
		double t = (double)s / SAMPLERATE;
		waveform[s] = sin(freq * t * M_PI) >= 0 ? volume : -1 * volume;
	}
	return waveform;
}

double Generation::GetFreq(int key) {
	double freq;
	freq = pow(2.0, (key - 49.0) / 12.0) * 440.0;
	return freq;
}

void Generation::GenerateSingleNote() {
	double length = 5;
	CreateWav create("singlenote.wav", length);
	create.Append(GenerateSin(GetFreq(53), 3000, length), length);
}

void Generation::GenerateSinScale() {
	double length = 5;	//seconds

	CreateWav create("sinscale.wav", length);
	create.Append(GenerateSin(GetFreq(50), 3000, length / 8), length / 8);
	create.Append(GenerateSin(GetFreq(52), 3000, length / 8), length / 8);
	create.Append(GenerateSin(GetFreq(54), 3000, length / 8), length / 8);
	create.Append(GenerateSin(GetFreq(55), 3000, length / 8), length / 8);
	create.Append(GenerateSin(GetFreq(57), 3000, length / 8), length / 8);
	create.Append(GenerateSin(GetFreq(59), 3000, length / 8), length / 8);
	create.Append(GenerateSin(GetFreq(61), 3000, length / 8), length / 8);
	create.Append(GenerateSin(GetFreq(62), 3000, length / 8), length / 8);
}

void Generation::GenerateSquareScale() {
	double length = 5;	//seconds

	CreateWav create("squarescale.wav", length);
	create.Append(GenerateSquare(GetFreq(50), 3000, length / 8), length / 8);
	create.Append(GenerateSquare(GetFreq(52), 3000, length / 8), length / 8);
	create.Append(GenerateSquare(GetFreq(54), 3000, length / 8), length / 8);
	create.Append(GenerateSquare(GetFreq(55), 3000, length / 8), length / 8);
	create.Append(GenerateSquare(GetFreq(57), 3000, length / 8), length / 8);
	create.Append(GenerateSquare(GetFreq(59), 3000, length / 8), length / 8);
	create.Append(GenerateSquare(GetFreq(61), 3000, length / 8), length / 8);
	create.Append(GenerateSquare(GetFreq(62), 3000, length / 8), length / 8);
}

void Generation::GenerateTwoNotesTest() {
	double length_time = 5;	//seconds
	int samples = SAMPLERATE * length_time * sizeof(SAMPLE) * CHANNELS;
	CreateWav create("twonotes.wav", length_time);
	SAMPLE* data1 = GenerateSquare(GetFreq(49), 3000, length_time);
	SAMPLE* data2 = GenerateSquare(GetFreq(53), 3000, length_time);
	SAMPLE* data = new SAMPLE[samples];
	for (int k = 0; k < samples; k++) {
		data[k] = data1[k] + data2[k];
	}
	create.Append(data, length_time);
}

void Generation::GenerateThreeNotesTest() {
	double length_time = 5;	//seconds
	int samples = SAMPLERATE * length_time * sizeof(SAMPLE) * CHANNELS;
	CreateWav create("threenotes.wav", length_time);
	SAMPLE* data1 = GenerateSin(GetFreq(49), 3000, length_time);
	SAMPLE* data2 = GenerateSin(GetFreq(53), 3000, length_time);
	SAMPLE* data3 = GenerateSin(GetFreq(56), 3000, length_time);
	SAMPLE* data = new SAMPLE[samples];
	for (int k = 0; k < samples; k++) {
		data[k] = data1[k] + data2[k] + data3[k];
	}
	create.Append(data, length_time);
}

//Syntax: note_number[ret]note_length
// TODO: Type should be an enum
int Generation::GenerateFromFileNotes(std::string filename, std::string type) {	//type = "sine"
	SAMPLE* (*GenWaveform)(double, int, double);
	for (int k = 0; k < type.length(); k++) {
		type[k] = tolower(type[k]);
	}

	if (type == "square") {
		GenWaveform = &GenerateSquare;
	}
	else if (type == "sine") {
		GenWaveform = &GenerateSin;
	}
	else return -1;	//Bad input	(do something here...?)

	std::ifstream file(filename);

	std::string line;
	std::vector<std::string> vec;
	double length = 0;
	int line_num = 0;
	while (std::getline(file, line)) {
		vec.push_back(line);	//Read file into vec
		if (line_num % 2 == 1) length += stod(line);
		line_num++;
	}
	if (vec.size() == 0) return -1; // No file input

	CreateWav create(filename.append(".wav").c_str(), length);

	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it += 2) {
		double note_length = stod(*(it + 1));
		short* note = GenWaveform(GetFreq(stoi(*it)), 2000, note_length);
		create.Append(note, note_length);	//total length / num notes
	}
	return 0;
}
