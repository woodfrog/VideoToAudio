#include "./header/videotosound.h"
#include <QtWidgets/QApplication>
#include "./header/Converter.h"

#undef main //to avoid the conflict of SDL and Qt. 

// store the intensity of the 64 notes
float freq[64];

int main(int argc, char *argv[])
{
	// set the frequencies for different notes (positions of pixels)
	set_notes_freq(freq);

	// Launch UI
	QApplication a(argc, argv);
	VideoToSound w;
	w.show();
	return a.exec();
}
