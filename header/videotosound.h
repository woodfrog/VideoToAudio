#ifndef VIDEOTOSOUND_H
#define VIDEOTOSOUND_H

#include <QtWidgets/QMainWindow>
#include "ui_videotosound.h"
#include <qfiledialog.h>
#include <thread>
#include "Converter.h"
#include <atomic>

extern bool is_playing;

class VideoToSound : public QMainWindow
{
	Q_OBJECT

public:
	VideoToSound(QWidget *parent = 0);
	~VideoToSound();

private slots:

    void on_BrowseButton_clicked();

    void on_PlayButton_clicked();

    void on_StopButton_clicked();

private:

	Ui::VideoToSoundClass ui;

	Converter _converter;
};

#endif // VIDEOTOSOUND_H
