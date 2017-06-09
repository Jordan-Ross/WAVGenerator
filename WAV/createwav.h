#pragma once
#include <fstream>
#define SAMPLERATE 44100	//This is just constant for now 
#define CHANNELS 2

#define BYTE char
#define SAMPLE short	//One sample is two bytes in this implementation

class CreateWav {
public:
	CreateWav(std::string _filename = "test.wav", double _length_time = 10);
	~CreateWav();
	void Append(SAMPLE* data, double length);
private:
	void WriteHeader();
	const int header_size = 44;	//bytes

	std::ofstream outfile;
	int data_size;
	double length_time;
	std::string filename;
};
