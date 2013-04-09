#include "ImagePost.h"
#include <opencv2/highgui/highgui.hpp>

int writer_(char *data, size_t size, size_t nmemb, char *writer_data)
{
	// nothing to do...
	return size * nmemb;
}

ImagePost::ImagePost()
	: quit_flag_(false), curl_(NULL), response_code_(0), quality_(90), interval_(100)
{
	curl_ = curl_easy_init();
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, writer_);
	//curl_easy_setopt(curl_, CURLOPT_VERBOSE, 1L);
}

ImagePost::~ImagePost()
{
	curl_easy_cleanup(curl_);
}

std::string ImagePost::url() const
{
	return url_;
}

void ImagePost::url(const std::string &val)
{
	url_ = val;
}

long ImagePost::response_code() const
{
	return response_code_;
}

int ImagePost::quality() const
{
	return quality_;
}

void ImagePost::quality(const int &val)
{
	quality_ = val;
}

int ImagePost::interval() const
{
	return interval_;
}

void ImagePost::interval(const int &val)
{
	interval_ = val;
}

cv::Mat ImagePost::image()
{
	boost::mutex::scoped_lock lock(mutex_);
	cv::Mat rv;

	image_.copyTo(rv);
	return rv;
}

void ImagePost::image(const cv::Mat &image)
{
	boost::mutex::scoped_lock lock(mutex_);
	if (image.empty()) {
		image_.release();
	}
	else {
		image.copyTo(image_);
	}
}

bool ImagePost::start()
{
	curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());

	// 
	thread_ = boost::thread(&ImagePost::run, this);
	return false;
}

void ImagePost::stop()
{
	quit_flag_ = true;
	thread_.join();
}

void ImagePost::run()
{
	while(!quit_flag_) {
		post_();	
		boost::this_thread::sleep(boost::posix_time::milliseconds(interval_));
	}
}

void ImagePost::post_()
{
	// create jpeg image data
	cv::Mat img = image();
	if (img.empty()) return;

	std::vector<int> params(2);
	params[0] = CV_IMWRITE_JPEG_QUALITY;
	params[1] = quality_;
	std::vector<uchar> buf;
	cv::imencode(".jpg", img, buf, params);

	// create multipart/form-data data
	struct curl_httppost *form_ptr = NULL;
    struct curl_httppost *last_ptr = NULL;

	curl_formadd(
		&form_ptr, &last_ptr,
		CURLFORM_COPYNAME, "name",
		CURLFORM_COPYCONTENTS, "camera0",
		CURLFORM_END);

	curl_formadd(
			&form_ptr, &last_ptr,
			CURLFORM_COPYNAME, "image",
			CURLFORM_CONTENTTYPE, "image/jpeg",
			CURLFORM_BUFFER, "uploadimage",
			CURLFORM_BUFFERPTR, &buf[0],
			CURLFORM_BUFFERLENGTH, buf.size(),
			CURLFORM_END);

	// do POST
	curl_easy_setopt(curl_, CURLOPT_HTTPPOST, form_ptr);
	CURLcode res = curl_easy_perform(curl_);
	curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &response_code_);

	curl_formfree(form_ptr);
}
