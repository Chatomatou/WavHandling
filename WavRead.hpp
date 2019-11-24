#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

#include "WavDataStructure.hpp"

class WavRead 
{
public:
	WavRead() = default;
	~WavRead() = default;
	
	void read_wav(const std::string& filename)
	{
		std::ifstream wavFile{ filename, std::ios::binary};

		if (!wavFile)
		{
			std::cerr << "Impossible to open the file : " << filename << std::endl;
			return;
		}

		wavFile.read(reinterpret_cast<char*>(&m_header), sizeof(m_header));
		wavFile.read(reinterpret_cast<char*>(&m_body), sizeof(m_body));
		wavFile.read(reinterpret_cast<char*>(&m_data), sizeof(m_data));
	 
		for (decltype(m_data.DataSize) i = 0; i < m_data.DataSize; i++)
		{
			uint8_t sample;
			wavFile.read(reinterpret_cast<char*>(&sample), sizeof(sample));
			m_samples.push_back(sample);
		}
	 
	}

	void display_content()
	{
		std::cout << "FileTypeBlocID :" << m_header.FileFormatID[0] << m_header.FileFormatID[1] << m_header.FileFormatID[2] << m_header.FileFormatID[3] << std::endl;
		std::cout << "FileSize :" << m_header.FileSize << std::endl;
		std::cout << "FileFormatID :" << m_header.FileTypeBlocID[0] << m_header.FileTypeBlocID[1] << m_header.FileTypeBlocID[2] << m_header.FileTypeBlocID[3] << std::endl;

		std::cout << std::endl << std::endl;

		std::cout << "FormatBlocID :" << m_body.FormatBlocID[0] << m_body.FormatBlocID[1] << m_body.FormatBlocID[2] << m_body.FormatBlocID[3] << std::endl;
		std::cout << "BlocSize :" << m_body.BlocSize << std::endl;
		std::cout << "AudioFormat :" << m_body.AudioFormat << std::endl;
		std::cout << "NbrChannel :" << m_body.NbrChannel << std::endl;
		std::cout << "Frequency :" << m_body.Frequency << std::endl;
		std::cout << "BytePerSec :" << m_body.BytePerSec << " (Frequency * BytePerBloc)"<< std::endl;
		std::cout << "BytePerBloc :" << m_body.BytePerBloc << " (NbrChannel * BitsPerSample/8)"<< std::endl;
		std::cout << "BitsPerSample :" << m_body.BitsPerSample << std::endl;
	 
		std::cout << "DataBlocID :" << m_data.DataBlocID[0] << m_data.DataBlocID[1] << m_data.DataBlocID[2] << m_data.DataBlocID[3] << std::endl;
		std::cout << "DataSize :" << m_data.DataSize << std::endl;

		auto i = 0;
		auto rowCounter = 0;

		for (auto sample : m_samples)
		{
			if (i == 10)
			{
				i = 0;
				std::cout << " : " << rowCounter << std::endl;
				rowCounter++;
			}
			std::printf("%.4x ", static_cast<int>(sample));
			i++;
		}

	}
	

	void copy_wav(const std::string& filename)
	{
		std::ofstream output{ filename, std::ios::binary };

		if (output)
		{
			output.write(reinterpret_cast<char*>(&m_header), sizeof(m_header));
			output.write(reinterpret_cast<char*>(&m_body), sizeof(m_body));
			output.write(reinterpret_cast<char*>(&m_data), sizeof(m_data));
			output.write(reinterpret_cast<char*>(&m_samples[0]), m_samples.size());
		}
		 
	}

	WavHeader getWavHeader()				{ return m_header; };
	WavBody getWavBody()					{ return m_body; };
	WavData getWavData()					{ return m_data; };
	std::vector<uint8_t> getWavBuffer()		{ return m_samples; };
private:
	WavHeader m_header;
	WavBody m_body;
	WavData m_data;
	std::vector<uint8_t> m_samples;
};