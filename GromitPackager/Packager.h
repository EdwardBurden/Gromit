#pragma once
#include <cstdint>

struct GrmFile
{
	char FileExtension[4] = "GRM";
	uint8_t Version = 0;
	char FileName[64];
	uint8_t AssetsCount = 0;
};

struct GrmEntry
{
	char FileName[64];
	size_t ByteSize;
	size_t Offset;


};