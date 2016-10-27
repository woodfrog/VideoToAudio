#include "./header/Converter.h"

bool is_playing = false; // a flag to prevent multiple sound playing

float buf[SAMPLES_PER_COL * SIZE]; // the buffer for the audio of one frame

void Converter::set_video_capture(QString s)
{
	vc = cv::VideoCapture(s.toStdString());
}

    
void Converter::play_sound()
{
	if (!is_playing)
	{
		is_playing = true;
		cv::Mat image, image_for_qt;

		while (true)
		{
			if (is_stopped) // to see if the playing process is stopped by user
			{
				is_stopped = false; // reset the flag
				break;
			}
			// Get the image from the video file
			vc.read(image);
			// Stop if there are no more frames in the video
			if (image.empty())
				break;
			
			// emit the signal for displaying the image with the pixel map
			cvtColor(image, image_for_qt, CV_BGR2RGB);
			 QImage q_img((uchar*)image_for_qt.data, image_for_qt.cols, image_for_qt.rows, QImage::Format_RGB888);
			const QPixmap &pixmap = QPixmap::fromImage(q_img.scaled(320, 320, Qt::KeepAspectRatio));
			emit display_img(pixmap);

			//reformat the matrix of image
			reformat_img(image);

			Audio::Open();

			// clear the buffer before using
			reset_buffer(buf, SAMPLES_PER_COL * SIZE);

			for (int col_index = 0; col_index < image.cols; col_index++)
			{
				for (int row_index = 0; row_index < image.rows; row_index++)
				{
					int position = 63 - row_index;
					for (int i = SAMPLES_PER_COL * col_index; i < (col_index + 1) * SAMPLES_PER_COL; i++)
					{
						buf[i] += sinf(2.0f * float(M_PI) * freq[position] * i / FS)
								* image.at<float>(row_index, col_index) / image.rows;
					}

				}
			}
			// A separator sound between two frame
			/*for (int i = 0; i < SAMPLES_PER_COL; i++)
			buf[i] += sinf(2.0f * float(M_PI) * 50.0f * i);*/

			Audio::Play(buf, SAMPLES_PER_COL * image.cols);
			Audio::WaitForSilence();

			// skip some frames for sampling
			for (int i = 0; i < FRAME_INTERVAL; i++)
			{
				vc.read(image);	
				if (image.empty())
					break;
			}
		}

		is_playing = false;
	}
}