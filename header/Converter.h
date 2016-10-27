#ifndef _CONVERTER_H
#define _CONVERTER_H

#include "video.h"
#include "audio.h"
#include <iostream>
#include <qstring.h>
#include <QImage>
#include <QPixmap>
#include <atomic>

#define FS 8000
#define SAMPLES_PER_COL 500
#define SIZE 64
#define FRAME_INTERVAL 24

extern float freq[64];

extern std::atomic<bool> is_stopped;

class Converter : public QObject
{
	Q_OBJECT

private:
	cv::VideoCapture vc;

public:

	Converter(){
	}

	~Converter(){
	}

	void play_sound();

	void set_video_capture(QString s);

signals:
	// the signature of this function must be the same as the ui::label->setPixmap
	void display_img(const QPixmap &);
};


#endif
