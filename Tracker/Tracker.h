#ifndef TRACKER_H
#define TRACKER_H

#include <QtGui/QMainWindow>
#include <qtimer.h>

// for file/directory manipulations
#include <qdir.h>
#include <qfiledialog.h>

// for image processing and representation
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// basic C++ operations.
#include <iostream>
#include <string>
#include <sstream>

#include "ui_Tracker.h"
#include "Constants.h"
#include "DummyTracker.h"
#include "FragTrack.h"
#include "OpenCVToQtInterfacing.h"
#include "Detector.h"

class Tracker : public QMainWindow
{
	Q_OBJECT

public:
	Tracker(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Tracker();

private slots:
	void nextFrame();
	void loadFiles();
	
	void playOrPause();
	void restart();

private:
	static int frame_number;
	Ui::TrackerClass ui;
	QDir directory;
	QTimer *timer;
	int state;

	QStringList files;
	std::vector<BaseTracker *> trackers;
	Detector *detector;
	cv::VideoCapture *capture;

	// false if reading from an actual video file.
	bool reading_sequence_of_images;
	
	void trackFrame(cv::Mat &input, cv::Mat &output);
	cv::Mat3b getFrame();

	void beginTracking();
	void pauseTracking();
	void endTracking();

	void detectAndSeedTrackers(cv::Mat &frame);
	void updateGUI(cv::Mat3b &raw_frame, cv::Mat3b &tracked_frame);

	enum states {PAUSED, PLAYING, STOPPED};
};

#endif // TRACKER_H
