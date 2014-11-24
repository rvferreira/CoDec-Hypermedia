#include "FUF.h"

using namespace std;

FUF::FUF(const char* filename)
		: sample(filename), lastCompression(0) {
	for (int i = 0; i < COMPRESSION_MODE_COUNT; i++) {
		compression[i] = NONE;
	}
	sample.readWav();
}

FUF::~FUF() {}

void FUF::writeToFile(const char* filename, fileExtension ext){
	WaveWriter output(sample.info, sample.data);
	
	char* fname = (char*) malloc(strlen(filename) + 1);
	strcpy(fname, filename);
	
	if (ext == eWAV) output.writeWav(strcat(fname, ".wav"));
	else if (ext == eFUF) output.writeWav(strcat(fname, ".fuf"));
}

void FUF::compress(compressMode a) {
	for (int i = 0; i < lastCompression; i++) {
		if (compression[i] == a) {
			cout << "This compression was already applied. YOCO, bro!" << endl;
			return;
		}
	}

	switch (a) {
		case HUFFMAN:
    		cout << "Applying Huffman..." << endl;
			huffmanCompress();
			break;
		case DIFFERENCE:
		    cout << "Applying Difference..." << endl;
			differencialCompress();
			break;
		case TRANSFORM:
		    cout << "Applying Transform..." << endl;
			transformCompress();
			break;

		case NONE:
		    return;
	}

	compression[lastCompression] = a;
	lastCompression++;
}

void FUF::compress(compressMode a, compressMode b){
	compress(a);
	compress(b);
}

void FUF::compress(compressMode a, compressMode b, compressMode c){
	compress(a);
	compress(b);
	compress(c);
}

void FUF::decompress(){
	while (lastCompression > 0) {
		lastCompression--;
		switch (compression[lastCompression]){
			case HUFFMAN:
				huffmanDecompress();
				break;
			case DIFFERENCE:
				differencialDecompress();
					break;
			case TRANSFORM:
				transformDecompress();
				break;
			case NONE:
				break;
		}
	}
}

