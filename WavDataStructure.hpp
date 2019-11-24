#pragma once

 
#include <vector>
#include <array>
#include <cstdint>

enum class FrequencyWav
{
	FREQUENCY_11025 = 11025,
	FREQUENCY_22050 = 22050,
	FREQUENCY_44100 = 44100,
	FREQUENCY_48000 = 48000,
	FREQUENCY_96000 = 96000
};

struct WavHeader
{
	std::array<uint8_t, 4> FileTypeBlocID;
	uint32_t FileSize;
	std::array<uint8_t, 4> FileFormatID;
};

struct WavBody
{
	std::array<uint8_t, 4> FormatBlocID;
	uint32_t BlocSize;

	uint16_t AudioFormat;
	uint16_t NbrChannel;
	uint32_t Frequency;
	uint32_t BytePerSec;
	uint16_t BytePerBloc;
	uint16_t BitsPerSample;
};

struct WavData
{
	std::array<uint8_t, 4> DataBlocID;
	uint32_t DataSize;
};
