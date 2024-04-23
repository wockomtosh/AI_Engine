#pragma once
#include <cstdint>
#include <string>

class BitArray
{
	typedef uint64_t BitData;
	const BitData MaxValue = 0xFFFFFFFFFFFFFFFF;

public:
	BitArray(size_t numBits, bool initToZero = true);
	BitArray(BitData* i_bits, size_t i_numBits);
	BitArray(const BitArray& other);
	~BitArray();

	bool FindFirstSetBit(size_t& firstSetBitIndex) const;
	bool FindFirstClearBit(size_t& firstClearBitIndex) const;

	void ClearAllBits();
	void SetAllBits();

	bool AreAllBitsClear() const;
	bool AreAllBitsSet() const;

	inline bool IsBitSet(size_t bitNumber) const;
	inline bool IsBitClear(size_t bitNumber) const;

	void SetBit(size_t bitNumber);
	void ClearBit(size_t bitNumber);

	size_t getNumElements() const;

	
	bool operator[](size_t bitIndex) const;
	BitArray operator&(const BitArray& other) const;
	BitArray operator|(const BitArray& other) const;
	BitArray operator~() const;
	bool operator==(BitArray& other) const;
	bool operator!=(BitArray& other) const;

	void print(std::string name = "BitArray") const;

private:
	BitData* bits;
	size_t numBits;
};

inline bool BitArray::IsBitSet(size_t bitNumber) const
{
	size_t bitsPerElement = sizeof(BitData) * 8;
	size_t elementIndex = bitNumber / bitsPerElement;
	size_t bitIndex = bitNumber % bitsPerElement;

	BitData element = bits[elementIndex];

	//Do an AND to find out if the bit is 1. Because we are using just 1 set bit in our mask, the value will be positive only if the desired bit is set to 1.
	return element & (static_cast<BitData>(1) << bitIndex);
}

inline bool BitArray::IsBitClear(size_t bitNumber) const
{
	return !IsBitSet(bitNumber);
}