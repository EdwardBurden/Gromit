#include "Packager.h"
#include <iostream>
#include <filesystem>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

GrmFile grm;


int main(int argc, char* argv[])
{
	std::string path = "pack 1";
	std::string fileName = "pack 1";
	int version = 1;
	std::cout << "Packager\n";
	std::filesystem::path rootPath = std::filesystem::current_path();
	std::cout << "Current Directory: " << rootPath << "\n";
	std::cout << "Enter path to folder to pack:";
	//std::getline(std::cin, path);
	auto newPath = rootPath / path;
	std::cout << "\nPath is :" << newPath;

	//std::cout << "\nEnter grm name: ";
	//std::getline(std::cin, fileName);

	//std::cout << "\nEnter version name: ";
	//version = std::cin.get();

	strcpy(grm.FileName, fileName.c_str());
	grm.Version = version;
	grm.AssetsCount = 0;

	//auto grmPath = rootPath / grm.FileName;
	//bool success = std::filesystem::create_directory(grmPath);
	//if (!success)
	//	return 1;
	//std::ofstream grmFile(grmPath);

	size_t offset = 0;
	for (const auto& directoryEntry : std::filesystem::directory_iterator(newPath))
	{
		if (!directoryEntry.is_regular_file())
		{
			continue;
		}
		const auto& filePath = directoryEntry.path();
		std::ifstream fileStream(filePath, std::ios::ate | std::ios::binary);
		if (!fileStream.is_open()) {
			std::cerr << "Could not open file: " << path << "\n";
		}

		auto size = directoryEntry.file_size();
		auto heapBytes = new char[size];
		fileStream.read(heapBytes, size);

		GrmEntry grmEntry{};
		const auto& namePath = filePath.filename();
		const auto& nameString = namePath.string();
		strcpy(grmEntry.FileName, nameString.c_str());
		grmEntry.ByteSize = directoryEntry.file_size();
		grmEntry.Offset = offset;




		grm.AssetsCount++;
		offset += grmEntry.ByteSize;
	}
	//grmFile.close();


}