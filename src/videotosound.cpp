#include "./header/videotosound.h"


/* The flag to see whether the sound is stopped,
	can be changed in two threads, so need to be atomic*/ 
std::atomic<bool> is_stopped = false;

VideoToSound::VideoToSound(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QObject::connect(&_converter, SIGNAL(display_img(const QPixmap &)), ui.ImgLabel, SLOT(setPixmap(const QPixmap &)));
}

VideoToSound::~VideoToSound()
{

}

void VideoToSound::on_BrowseButton_clicked()
{
	if (!is_playing)
	{
		QString filename = QFileDialog::getOpenFileName(this, "Select source file", ".", "Images (*.png *.jpg *.jpeg *.bmp);; Videos(*.avi *.3gp *.gif *.mp4 *.m4v *.wmv *.mpg *.mxf)");

		if (QString::compare(filename, QString()) != 0)
		{
			_converter.set_video_capture(filename);
			ui.ImgLabel->setText("     Ready");
		}
	}
}

void VideoToSound::on_PlayButton_clicked()
{
	std::thread sound_thread(&Converter::play_sound, &_converter); // create a new thread for playing audio, prevent the UI from dying  
	sound_thread.detach(); // don't wait for the sound thread, so the user interaction won't be 
}


void VideoToSound::on_StopButton_clicked()
{
	is_stopped = true;
	ui.ImgLabel->setText("    Terminated");
}

