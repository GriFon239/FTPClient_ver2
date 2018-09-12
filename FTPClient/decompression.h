#pragma once
#include <iostream>
#include <zip.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include <direct.h>
#include <locale>


//using namespace std;

int writeCurrentFile(int i, zip *za, struct zip_stat zipStat, char bufForFileName[]) {
	
	struct zip_file *zipFile; // Структура для работы с текущим файлом архива

	zip_int64_t lenOfReadData; // Сколько байт было прочитано из файла

	int size =  zipStat.size;
	char * buf = new char[size+1]; // Буфер для чтения информации из архива

	zipFile = zip_fopen_index(za, i, 0);
	if (!zipFile) {

		return 1;
	}
	std::wofstream fd(bufForFileName, std::ios::binary);//Создать файл 
	if (!fd.is_open()) { // Если файл нельзя создать, значит произошла ошибка

		zip_fclose(zipFile);
		return 1;
	}
	
	zip_uint64_t sum = 0; // Полный размер текущего файла в архиве
	while (sum != zipStat.size) {

		lenOfReadData = zip_fread(zipFile, buf, size);
		if (lenOfReadData < 0) {

			zip_fclose(zipFile);
			return 1;
		}


		buf[size] = 0;
		fd << buf;
		sum += lenOfReadData;
	}
	fd.close();
	delete[] buf;
	int zipCloseResult = zip_fclose(zipFile);
	if (zipCloseResult != 0) {
		return 1;
	}
	return 0;
}

int loopThroughFiles(zip *za, const char* output) {

	int i; // Переменная для итерирования
	struct zip_stat zipStat; // Информация о файле
	size_t currentItemNameLength; // Длина имени текущего элемента в архиве

	for (i = 0; i < zip_get_num_entries(za, 0); i++) {

		if (zip_stat_index(za, i, 0, &zipStat) == 0) {

			currentItemNameLength = strlen(zipStat.name);
			std::cout << "Имя файла:  " << zipStat.name << std::endl;
			std::cout << "Размер: " << zipStat.size << std::endl;
			std::cout << std::endl;
			char bufForFileName[300]; // Буфер для имени файла с учётом корневой папки
			strcpy_s(bufForFileName, output);
			strcat_s(bufForFileName, zipStat.name);
			if (zipStat.name[currentItemNameLength - 1] == '/') { // Если текущий элемент архива - папка, то нужно создать папку на диске

				if (!_mkdir(bufForFileName)) { 
				}


			}
			else { 

				writeCurrentFile(i, za, zipStat, bufForFileName);
			}
		}
	}
	return 0;
}

int enumerateArchive(const char* filePath, const char* output) {

	zip *za;// Структура для работы с архивом
	int err; // Код последней ошибки
	// Попытаться открыть файл с архивом, если не получилось - сообщить об ощибке
	if ((za = zip_open(filePath, 0, &err)) == NULL) {
		std::cout << "Не удаеться открыть архив " << std::endl;
		return 1;
	}
	// Пройтись по всем элементам архива

	loopThroughFiles(za, output);
	// Закрыть файл с архивом (если не получилось - сообщить об ошибке)
	if (zip_close(za) == -1) {

		return 1;
	}
	std::cout << "Распаковка закончена" << std::endl;
	return 0;
}
