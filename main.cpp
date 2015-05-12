
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>
#include <opencv2\opencv.hpp>
#include <opencv2\opencv_lib.hpp>
#include <opencv2\opencv_modules.hpp>


using namespace std;
using namespace tr2::sys;

int main(int argc, char** argv)
{
	char temp[100];
	if (argc != 2)
	{
		cout << "Error:Input only 1 folder." << endl;
		cout << "Exit:Press any key." << endl;
		cin >> temp;
		return 0;
	}

	string Str = argv[1];
	Str.append("/.");

	path Path(Str.c_str());
	for_each(directory_iterator(Path), directory_iterator(), [](const path& Path, string Str)
	{
		if (is_regular_file(Path))
		{
			cv::Mat Image = cv::imread(Str + Path.filename());

		}
	});


	cin >> temp;
	return 0;
}
