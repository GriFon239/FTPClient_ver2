
#include "Decompression_ver2.h"


int decommpression_(String^ filePath_, String^ output_) {

	try
	{
		ZipFile::ExtractToDirectory(filePath_, output_);
	}
	catch (const std::exception&)
	{
		std::cout << "������ ���������� ������" << std::endl;
		return 0;
	}

	std::cout << "����� ������� �����������" << std::endl;

	return 0;
}
