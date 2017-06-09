#include "createwav.h"

CreateWav::CreateWav(std::string _filename, double _length_time) {
	filename = _filename;
	length_time = _length_time;
	outfile = std::ofstream(filename, std::ios::binary);
	data_size = SAMPLERATE * length_time * sizeof(SAMPLE) * CHANNELS;	// Samples/time * time * bytes/sample * channels = data size in bytes
	WriteHeader();
}

void CreateWav::WriteHeader() {
	int headersize = 44;
	int size = headersize + data_size;
	int len = 16;
	short type = 1;
	short channels = 2;
	short bitspersample = 16;	//2 bytes per sample (short)
	int samplerate = SAMPLERATE; //How do I fix this
	int bitrate = (SAMPLERATE*bitspersample*channels) / 8;
	short blockalign = (bitspersample * channels) / 8;	//Usually 4

	outfile.write("RIFF", 4);
	outfile.write((BYTE*)&size, 4);		//Total file size
	outfile.write("WAVEfmt\x20", 8);		
	outfile.write((BYTE*)&len, 4);
	outfile.write((BYTE*)&type, 2);
	outfile.write((BYTE*)&channels, 2);
	outfile.write((BYTE*)&samplerate, 4);	//How do I fix this
	outfile.write((BYTE*)&bitrate, 4);
	outfile.write((BYTE*)&blockalign, 2);
	outfile.write((BYTE*)&bitspersample, 2);
	outfile.write("data", 4);	
	outfile.write((BYTE*)&data_size, 4);	//Data size
}

void CreateWav::Append(SAMPLE* data, double length_time) {
	int data_length = length_time * SAMPLERATE * sizeof(SAMPLE) * CHANNELS;
	outfile.write((BYTE*)data, data_length);
}

CreateWav::~CreateWav() {
	outfile.close();
}
