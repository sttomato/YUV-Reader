#include <opencv2\core.hpp>
using namespace cv;

class YuvReader {
public:
	YuvReader(const char* filePath, const int width, const int height, bool debug = false);

	void open(const char* filePath);
	bool read(cv::OutputArray image);
	
	void release();
	
	~YuvReader();
private:
	bool debug;
	int width, height;
	Mat Y, Cb, Cr;

	FILE *file = NULL;
	void log(char* str);
	void initMatrix();
};

