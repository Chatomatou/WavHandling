#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
 

#include "WavDataStructure.hpp"

class WavWrite
{
public:
	WavWrite() = delete;

	WavWrite(const std::string& filename, const FrequencyWav frequency, const uint16_t bitsPerSample, const uint32_t durationInSeconds) :
		m_filename{ filename },
		m_frequency{ frequency },
		m_bitsPerSample{ bitsPerSample },
		m_durationInSeconds { durationInSeconds }
	{
		 
	}
	
	~WavWrite()
	{
		std::ofstream output{ m_filename, std::ios::binary };


		if (output)
		{
			uint32_t freq = static_cast<uint32_t>(m_frequency);
			uint32_t fileSize = static_cast<uint32_t>(output.tellp());
			fileSize -= 8;

			m_header = { { 'R', 'I', 'F', 'F' }, fileSize,  { 'W', 'A', 'V', 'E' } };
			m_body = { {'f', 'm', 't', ' '}, 16, 1, 1, freq, static_cast<uint16_t>(freq * m_bitsPerSample / 8), static_cast<uint16_t>(m_bitsPerSample / 8), m_bitsPerSample };
			m_data = { {'d', 'a', 't', 'a'}, m_durationInSeconds * m_body.Frequency }; 

			output.write(reinterpret_cast<char*>(&m_header), sizeof(m_header));
			output.write(reinterpret_cast<char*>(&m_body), sizeof(m_body));
			output.write(reinterpret_cast<char*>(&m_data), sizeof(m_data));
			output.write(reinterpret_cast<char*>(&m_samples[0]), m_samples.size());
		}
	}

	void insert_samples_in_buffer(std::vector<uint16_t> samples)
	{
		for (auto v : samples)
			m_samples.push_back(v);
	}

	WavHeader getWavHeader() { return m_header; };
	WavBody getWavBody() { return m_body; };
	WavData getWavData() { return m_data; };
private:
	std::string m_filename;
	FrequencyWav m_frequency;
	uint16_t m_bitsPerSample;
	uint32_t m_durationInSeconds;

	WavHeader m_header;
	WavBody m_body;
	WavData m_data;
	std::vector<uint16_t> m_samples;
 
};