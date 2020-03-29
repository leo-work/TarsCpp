﻿//
// Created by jarod on 2020/2/20.
//

#include "util/tc_file.h"
#include "test_base.h"

using namespace tars;

void Test_TC_File::test()
{
	string file = "./test.dat";
	string data = "helloword";
	data[3] = '\0';

	TC_File::save2file(file, data);
	int fileSize = TC_File::getFileSize(file);
	cout << "file size:" << fileSize  << endl;
	assert(fileSize == data.size());

	string load = TC_File::load2str(file);
	cout << "load file size:" << load.size() << endl;
	assert(load == data);

	bool fileExists = TC_File::isFileExist(file, S_IFREG);
    cout << "file exists:" << fileExists << endl;
    assert(fileExists);

    string dir = "test";
    TC_File::makeDir(dir);
	fileExists = TC_File::isFileExist(dir, S_IFDIR);
	cout << "dir exists:" << fileExists << endl;
	assert(fileExists);

	string newFile = dir + FILE_SEP + file;
	TC_File::save2file(newFile, data);
	fileExists = TC_File::isFileExist(newFile, S_IFREG);
	cout << "newFile exists:" << fileExists << endl;
	assert(fileExists);

	TC_File::makeDir(dir + FILE_SEP + "test1");
	TC_File::makeDir(dir + FILE_SEP + "test2");

	vector<string> v;
	TC_File::listDirectory(dir, v, true);
	cout << "listDirectory:" << endl;
	for(auto s : v)
	{
		cout << "    " << s << endl;
	}

	TC_File::removeFile(dir, true);
	fileExists = TC_File::isFileExist(file, S_IFDIR);
	cout << "dir exists:" << fileExists << endl;
	assert(!fileExists);

	cout << "simplifyDirectory:" << TC_File::simplifyDirectory("/.") << endl;
	cout << "simplifyDirectory:" << TC_File::simplifyDirectory("/./ab/tt//t///t//../tt/") << endl;
	assert(TC_File::simplifyDirectory("/./ab/tt//t///t//../tt/") == "ab\\tt\\t\\tt");
#if TARGET_PLATFORM_WINDOWS
	cout << "simplifyDirectory:" << TC_File::simplifyDirectory("c:/ab/tt//t///t//../tt/") << endl;
	assert(TC_File::simplifyDirectory("c:/ab/tt//t///t//../tt/") == "c:\\ab\\tt\\t\\tt");
#endif

	assert(TC_File::extractFileExt("/usr/local/app/bin.exe") == "exe");
	assert(TC_File::extractFileExt("/usr/local/app/bin") == "");
	assert(TC_File::extractFileExt("/usr/local/app.dir/bin.exe") == "exe");
	assert(TC_File::extractFileExt("c:\\usr\\local\\app.dir\\bin.exe") == "exe");
	assert(TC_File::extractFileExt("c:\\usr\\local\\app.dir\\bin") == "");

	assert(TC_File::extractFileName("/usr/local/app/bin.exe") == "bin.exe");
	assert(TC_File::extractFileName("/usr/local/app/bin") == "bin");
	assert(TC_File::extractFileName("/usr/local/app.dir/bin.exe") == "bin.exe");
	assert(TC_File::extractFileName("c:\\usr\\local\\app.dir\\bin.exe") == "bin.exe");
	assert(TC_File::extractFileName("c:\\usr\\local\\app.dir\\bin") == "bin");
	assert(TC_File::extractFileName("bin.exe") == "bin.exe");

	assert(TC_File::extractFilePath("/usr/local/app/bin.exe") == "/usr/local/app/");
	assert(TC_File::extractFilePath("/usr/local/app/bin") == "/usr/local/app/");
	assert(TC_File::extractFilePath("/usr/local/app.dir/bin.exe") == "/usr/local/app.dir/");
	assert(TC_File::extractFilePath("c:\\usr\\local\\app.dir\\bin.exe") == "c:\\usr\\local\\app.dir\\");
	assert(TC_File::extractFilePath("c:\\usr\\local\\app.dir\\bin") == "c:\\usr\\local\\app.dir\\");
	assert(TC_File::extractFilePath("temp.gif") == string(".") + FILE_SEP);

	assert(TC_File::excludeFileExt("/usr/local/app/bin.exe") == "/usr/local/app/bin");

	assert(TC_File::excludeFileExt("/usr/local/app/bin") == "/usr/local/app/bin");
	assert(TC_File::excludeFileExt("/usr/local/app.dir/bin.exe") == "/usr/local/app.dir/bin");
	assert(TC_File::excludeFileExt("c:\\usr\\local\\app.dir\\bin.exe") == "c:\\usr\\local\\app.dir\\bin");
	assert(TC_File::excludeFileExt("c:\\usr\\local\\app.dir\\bin") == "c:\\usr\\local\\app.dir\\bin");
	assert(TC_File::excludeFileExt("temp.gif") == "temp");

}
