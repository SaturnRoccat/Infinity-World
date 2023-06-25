#include "NoiseSegment.h"
#include <math.h>

void NoiseSegment::calculateAllBlocks()
{

	const static int worldTaper = 50;
	const static float threshold = 0.2;
	const static float bias = 0.4f;

	int3 Bounds = {
		_chunkSize.x * _chunksToContain.x,
		_chunkSize.y,
		_chunkSize.z * _chunksToContain.z
	};
	for (size_t x = 0; x < Bounds.x; x++)
	{
		// We index into 1 and not 0 to throw an error if the size given was to small
		for (size_t y = 0; y < Bounds.y; y++)
		{

			// Same here
			for (size_t z = 0; z < Bounds.z; z++)
			{
				int3 SamplePosition = {
					(_offset.x * Bounds.x) + x,
					y,
					(_offset.y * Bounds.z) + z
				};

				float noiseValue = _fsn->GetNoise(SamplePosition.x, SamplePosition.y, SamplePosition.z);
				noiseValue = (noiseValue + 1.0f) / 2.0f;

				if (y < worldTaper && noiseValue > threshold)
				{

					float t = 1.0f - static_cast<float>(worldTaper - y) / worldTaper;

					float modifiedBias = bias * (1.0f - std::pow(2.0f, -10.0f * t));
					noiseValue -= modifiedBias;
					noiseValue = std::max(noiseValue, 0.0f);
				}

				noiseValue = (2.0f * noiseValue) - 1.0f;

				if (noiseValue < threshold)
				{
					size_t index = x + (y * Bounds.x) + (z * Bounds.x * Bounds.y);
					auto& bv = blockValues[index] = 1u;
				}

			}
		}
	}
}


void NoiseSegment::calculateHeightMap()
{


	int3 Bounds = {
		_chunkSize.x * _chunksToContain.x,
		_chunkSize.y,
		_chunkSize.z * _chunksToContain.z
	};

	for (size_t x = 0; x < Bounds.x; x++)
	{

		for (size_t z = 0; z < Bounds.z; z++)
		{
			uint16_t Distance = 0;

			while (getBlock(x, Bounds.y - Distance, z) != 1)
			{
				Distance++;
			}

			setBlock(x, Distance, z, Distance, &this->heightMap);
		}
	}
}