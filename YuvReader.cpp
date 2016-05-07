#include "YuvReader.h"
#include "opencv2\opencv.hpp"

YuvReader::YuvReader(const char * filePath, const int width, const int height, bool debug) {
	this->debug = debug;

	if (width % 2 == 1 || height % 2 == 1) {
		log("Width or Height is invalid");
	}

	this->width = width;
	this->height = height;

	open(filePath);
}



void YuvReader::open(const char * filePath) {
	this->file = fopen(filePath, "rb");
	if (file == NULL) {
		printf("Cant open file");
		exit(EXIT_FAILURE);
	}
}

bool YuvReader::read(cv::OutputArray image, bool convertBGR) {
	initMatrix();
	size_t nPixels = width * height;
	size_t byteRead = fread(this->Y.data, sizeof(uint8_t), nPixels, file);

	if (byteRead == 0) {
		//EOF
		return false;
	}else if (byteRead != nPixels) {
		//IO error
		return false;
	}
	byteRead = fread(this->Cb.data, sizeof(uint8_t), nPixels / 4, file);
	if (byteRead != nPixels / 4) {
		//IO error
		return false;
	}
	byteRead = fread(this->Cr.data, sizeof(uint8_t), nPixels / 4, file);
	if (byteRead != nPixels / 4) {
		//IO error
		return false;
	}

	resize(this->Cb, this->Cb, Size(), 2.0, 2.0, InterpolationFlags::INTER_CUBIC);
	resize(this->Cr, this->Cr, Size(), 2.0, 2.0, InterpolationFlags::INTER_CUBIC);
	//if (Cb.rows >= 480) {
	//	log("a");
	//}
	std::vector<Mat> array;
	array.push_back(this->Y);
	array.push_back(this->Cb);
	array.push_back(this->Cr);

	image.create(Size(width, height), CV_8UC3);
	merge(array, image);
	if (convertBGR) {
		cvtColor(image, image, ColorConversionCodes::COLOR_YCrCb2BGR);
	}
	return true;
}


void YuvReader::release() {
	if (this->file != NULL) {
		fclose(file);
		file = NULL;
	}

	this->Y.release();
	this->Cb.release();
	this->Cr.release();
}


YuvReader::~YuvReader() {
	log("DeAllocate YuvReader Object");
	this->release();
}

void YuvReader::log(char * str) {
	if (this->debug) {
		printf(str);
	}
}

void YuvReader::initMatrix() {
	this->Y.create(Size(width, height), CV_8UC1);
	this->Cb.create(Size(width / 2, height / 2), CV_8UC1);
	this->Cr.create(Size(width / 2, height / 2), CV_8UC1);
}

