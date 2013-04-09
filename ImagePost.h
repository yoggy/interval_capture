#ifndef __IMAGE_POST_H__
#define __IMAGE_POST_H__

#include <boost/thread.hpp>
#include <opencv2/core/core.hpp>
#include <curl/curl.h>
#include <string>

class ImagePost {
public:
	ImagePost();
	virtual ~ImagePost();

	std::string url() const;
	void url(const std::string &val);

	long response_code() const;

	int quality() const;
	void quality(const int &val);

	int interval() const;
	void interval(const int &val);

	cv::Mat image();
	void image(const cv::Mat &image);

	bool start();
	void stop();

	void run();

protected:
	void post_();

protected:
	cv::Mat image_;
	std::string url_;

	boost::thread thread_;
	boost::mutex mutex_;
	bool quit_flag_;

	CURL *curl_;
	long response_code_;

	int quality_;
	int interval_;
};

#endif //#ifndef __IMAGE_POST_H__
