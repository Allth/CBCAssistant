
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <cmath>
#include <opencv2\opencv.hpp>
#include <opencv2\opencv_lib.hpp>
#include <opencv2\opencv_modules.hpp>

#define TH_COLORDIFF	0x30
#define TH_GRAYCOUNTER	90

using namespace std;
using namespace tr2::sys;
using namespace cv;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Error:Input only 1 folder." << endl;
		cout << "Exit:Press any key." << endl;
		getchar();
		return 0;
	}

	string Str = argv[1];
	Str.append("\\");

	path Path(Str.c_str());
	for_each(directory_iterator(Path), directory_iterator(), [Str](const path& Path)
	{
		if (is_regular_file(Path))
		{
			Mat Image = imread(Str + Path.filename());
			Mat dst = Mat(200, 200, CV_8UC3);
			resize(Image, dst, dst.size());
			cout << Str + Path.filename() << endl;
			int GrayCounter = 0;
			int NofData = 0;
			for (int y = 0; y < Image.cols; y++)
			{
				for (int x = 0; x < Image.rows; x++)
				{
					uchar* data = &Image.data[y * Image.cols + x];
					int ColorDiff = 0;
					for (int i = 0; i < (int)(Image.elemSize() - 1) && i < 3 - 1; i++)
					{
						ColorDiff += ::abs(*data - *(data + 1));
					}
					NofData++;
					if (ColorDiff > TH_COLORDIFF)
						GrayCounter++;
				}
			}
			if (NofData == 0)
				cout << Path.filename() << " is unknown data." << endl;
			else if (GrayCounter * 100 / NofData > TH_GRAYCOUNTER)
				cout << Path.filename() << "is Gray data." << endl;
		}
	});

	cout << "Exit:Press any key." << endl;
	getchar();
	return 0;
}
