#include "BitArray.h"
#include <iostream>
#include <cassert>
#include <algorithm>

BitArray::BitArray(size_t i_numBits, bool initToZero) :
    numBits(i_numBits)
{
    bits = new BitData[getNumElements()];

    if (initToZero)
    {
        ClearAllBits();
    }
    else
    {
        SetAllBits();
    }
}

BitArray::BitArray(BitData* i_bits, size_t i_numBits) :
    bits(i_bits), numBits(i_numBits) {}

BitArray::BitArray(const BitArray& other) :
    numBits(other.numBits)
{
    //Copy over the bit data from the other array
    int otherNumElements = other.getNumElements();
    bits = new BitData[otherNumElements];
    for (int i = 0; i < otherNumElements; i++)
    {
        bits[i] = other.bits[i];
    }
}

BitArray::~BitArray()
{
    delete[] bits;
}

bool BitArray::FindFirstSetBit(size_t& firstSetBitIndex) const
{
    size_t index = 0;
    size_t numElements = getNumElements();

    //Get the block of bits that contains the first set bit
    while ((bits[index] == BitData(0)) && (index < numElements))
    {
        index++;
    }

    if (index >= numElements)
    {
        return false;
    }

    BitData currentBits = bits[index];
    unsigned long bitIndex;

    _BitScanForward64(&bitIndex, currentBits);

    firstSetBitIndex = static_cast<size_t>(bitIndex);

    return true;
}

bool BitArray::FindFirstClearBit(size_t& firstClearBitIndex) const
{
    size_t index = 0;
    size_t numElements = getNumElements();

    //Get the block of bits that contains the first clear bit
    while ((bits[index] == BitData(0)) && (index < numElements))
    {
        index++;
    }

    //Check if there are no set bits
    if (index >= numElements)
    {
        return false;
    }

    BitData currentBits = bits[index];
    unsigned long bitIndex;

    //The only difference between the first set bit and first clear bit is that we can do a bitwise NOT and then git the first set bit.
    _BitScanForward64(&bitIndex, ~currentBits);

    firstClearBitIndex = static_cast<size_t>(bitIndex);

    return true;
}

void BitArray::ClearAllBits()
{
    size_t bitsPerElement = sizeof(BitData) * 8;
    size_t numElements = getNumElements();
    size_t numBytes = numElements * (bitsPerElement / 8);
    memset(bits, 0, numBytes);
}

void BitArray::SetAllBits()
{
    size_t bitsPerElement = sizeof(BitData) * 8;
    size_t numElements = getNumElements();
    size_t numBytes = numElements * (bitsPerElement / 8);
    //To set everything to 1 we need to make sure all bits in the char are set to 1
    memset(bits, 0xFF, numBytes);
}

bool BitArray::AreAllBitsClear() const
{
    size_t index = 0;
    size_t numElements = getNumElements();

    //Iterate through until you find any nonzero bit
    while ((bits[index] == 0) && (index < numElements))
    {
        index++;
    }

    //If you got through the whole array then everything is clear
    if (index >= numElements)
    {
        return true;
    }

    return false;
}

bool BitArray::AreAllBitsSet() const
{
    size_t index = 0;
    size_t numElements = getNumElements();

    while ((bits[index] == MaxValue) && (index < numElements))
    {
        index++;
    }

    if (index >= numElements)
    {
        return true;
    }

    return false;
}

void BitArray::SetBit(size_t bitNumber)
{
    size_t bitsPerElement = sizeof(BitData) * 8;
    size_t elementIndex = bitNumber / bitsPerElement;
    size_t bitIndex = bitNumber % bitsPerElement;

    BitData element = bits[elementIndex];

    //Take the element, and OR it with a mask that has a 1 set on our desired bit
    bits[elementIndex] = element | (static_cast<BitData>(1) << bitIndex);
}

void BitArray::ClearBit(size_t bitNumber)
{
    size_t bitsPerElement = sizeof(BitData) * 8;
    size_t elementIndex = bitNumber / bitsPerElement;
    size_t bitIndex = bitNumber % bitsPerElement;

    BitData element = bits[elementIndex];

    //Take the element, and AND it with a mask that has a 0 set on our desired bit and a 1 everywhere else
    bits[elementIndex] = element & ~(static_cast<BitData>(1) << bitIndex);
}

size_t BitArray::getNumElements() const
{
    //For this project only I'm using just 8 bits, which means this breaks because it expects at least 64 bits.
    //This breaks the BitArray because when it checks for the number of elements it gets 0.
    //So I made this function to handle that.
    size_t bitsPerElement = sizeof(BitData) * 8;
    size_t numElements = numBits / bitsPerElement;
    if (numElements == 0)
    {
        numElements = 1;
    }
    return numElements;
}

bool BitArray::operator[](size_t bitIndex) const
{
    if (IsBitSet(bitIndex))
    {
        return true;
    }
    return false;
}

BitArray BitArray::operator&(const BitArray& other) const
{
    int otherNumElements = other.getNumElements();
    int numElements = getNumElements();

    //For this to work they need to have the same length of BitData array.
    assert(numElements == otherNumElements);

    BitData* oBits = new BitData[numElements];

    for (int i = 0; i < numElements; i++)
    {
        oBits[i] = bits[i] & other.bits[i];
    }

    return BitArray(oBits, std::max(numBits, other.numBits));
}

BitArray BitArray::operator|(const BitArray& other) const
{
    size_t bitsPerElement = sizeof(BitData) * 8;
    int otherNumElements = other.getNumElements();
    int numElements = getNumElements();

    assert(numElements == otherNumElements);

    BitData* oBits = new BitData[numElements];

    for (int i = 0; i < numElements; i++)
    {
        oBits[i] = bits[i] | other.bits[i];
    }

    return BitArray(oBits, std::max(numBits, other.numBits));
}

BitArray BitArray::operator~() const
{
    int numElements = getNumElements();

    BitData* oBits = new BitData[numElements];

    for (int i = 0; i < numElements; i++)
    {
        oBits[i] = ~bits[i];
    }

    return BitArray(oBits, numBits);
}

bool BitArray::operator==(BitArray& other) const
{
    if (numBits != other.numBits)
    {
        return false;
    }
    int numElements = getNumElements();

    for (int i = 0; i < numElements; i++)
    {
        BitData comp = bits[i] & other.bits[i];
        if (comp != bits[i])
        {
            return false;
        }
    }
    return true;
}

bool BitArray::operator!=(BitArray& other) const
{
    return !this->operator==(other);
}

void BitArray::print(std::string name) const
{
    std::string oString = "";
    
    for (int i = 0; i < numBits; i++)
    {
        if (IsBitSet(i))
            oString += "1";
        else
            oString += "0";
    }
    std::reverse(oString.begin(), oString.end());
    std::cout << name << ": " << oString << std::endl;
}
