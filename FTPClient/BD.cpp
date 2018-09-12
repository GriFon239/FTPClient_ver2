#include "BD.h"
#include "global.h"

int BD(String^ connect) {

	auto con = gcnew OleDbConnection(connect);

	try
	{
		con->Open();
	}
	catch (const std::exception&)
	{
		std::cout << "Ошибка подключения к базе данных" << std::endl;
	}

	std::string create_table;

	for (auto NameBD_addres : BDName_addresToFile) {
		//create_table = "CREATE TABLE " + NameBD_addres.first + " (XMLCol xml)";
		create_table = "IF  NOT EXISTS(SELECT * FROM sys.objects --\n\
							WHERE object_id = OBJECT_ID(N'[dbo].[" + NameBD_addres.first + "]') AND type in(N'U')) --\n\
							BEGIN --\n\
							CREATE TABLE[dbo].[" + NameBD_addres.first + "](XMLCol xml) --\n\
							END;";

		String^ create_table_str = gcnew String(create_table.c_str());
		auto command = gcnew OleDbCommand(create_table_str, con);

		try
		{
			command->ExecuteNonQuery();
		}
		catch (const std::exception&)
		{
			std::cout << "Ошибка создания таблицы с именем: " << NameBD_addres.first << std::endl;
		}





		std::string query =
			"INSERT INTO " + NameBD_addres.first + "(XMLCol) --\n\
				 SELECT * FROM OPENROWSET( --\n\
				 BULK \'" + NameBD_addres.second + "\', SINGLE_CLOB) AS x;";

		String^ query_str = gcnew String(query.c_str());
		command->CommandText = query_str;

		try
		{
			command->ExecuteNonQuery();
			std::cout << "Файл  " << NameBD_addres.second << "  загружен в БД" << std::endl;
		}
		catch (const std::exception&)
		{
			std::cout << "Ошибка занесения файла в базу данных по адресу:\n" \
				<< NameBD_addres.second << std::endl;
		}



	}
	std::cout << "Файлы успешно загружены в БД" << std::endl;

	con->Close();
	return 0;
}