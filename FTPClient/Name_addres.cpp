#include "Name_addres.h"
#include "global.h"

int Name_addres(std::string _path)
{
	for (auto & p : fs::directory_iterator(_path))
		fs::path path_ = p;

	fs::directory_iterator begin(_path);
	fs::directory_iterator end;

	// Получаем список файлов .xml с помощью алгоритма copy_if
	std::vector<fs::path> xmlFiles_;
	std::vector<std::string> xmlFiles;

	std::copy_if(begin, end, std::back_inserter(xmlFiles_), [](const fs::path& path) {
		return fs::is_regular_file(path) && (path.extension() == ".xml");
	});
	for (auto i : xmlFiles_) { xmlFiles.push_back(i.string()); }
	std::vector<std::string> xmlFiles_filename;

	// Выводим список файлов в cout.
	std::cout << "-- xml files --" << std::endl;
	int count = 0;
	for (auto i : xmlFiles_) {
		std::string buf = i.filename().string();
		xmlFiles_filename.push_back(buf);

	}

	int j = 0;

	std::vector<char> buffer_name;
	for (auto i : xmlFiles_filename) {
		while (i[j] != '_') {
			buffer_name.push_back(i[j]);
			j++;
		}
		j = 0;

		char* buff = new char[buffer_name.size() + 1];
		for (int i = 0; i < buffer_name.size(); i++) {
			buff[i] = buffer_name[i];
		}
		buff[buffer_name.size()] = '\0';

		BDName_addresToFile.emplace((std::string)buff, xmlFiles[count]);
		buffer_name.clear();
		delete[]buff;
		count++;
	}
	for (auto i : BDName_addresToFile) {
		std::cout << i.first << '\t' << i.second << std::endl;

	}

	return 0;
}