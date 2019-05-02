#include "Vector.h"
#include <cstdlib>
#include <cstring>
#include "ds_routiness.h"

	Vector::Vector(size_t size) :  //vykona sa to skor ako sa zacne vykonavat telo konstruktora, je to rychlejsie
		memory_(calloc(size, 1)), //chceme vycistit pamat
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_) //zavolali sme konstruktor, alokuje sa pamat
	{
		//TODO 01: Vector
		memory_ = memcpy(memory_, other.memory_, size_); //skopirovali sme obsah memory
	}

	Vector::~Vector()
	{
		//TODO 01: Vector
		free(memory_); //vycistenie pamate, uvolnenie miesta
		memory_ = nullptr;
		size_ = 0;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other); //operator priradenia, na pravej strane vector, vola metodu o jedno nizsie 
		}
		return *this; //aby sa to dalo retazit, v1=v2=v3....
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other) //skontroluj ci nie su identicke
		{
			size_ = other.size_;
			memory_ = realloc(memory_, other.size_); //musi tam byt rovnasa inak by to alokovalo inde
			memcpy(memory_, other.memory_, other.size_); //okopiruje tu pamat, nepotrebujeme kontrolovat lebo sme ju pred tym reallocovali
		}
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		return(this == &other || size_ == other.size_ && memcmp(memory_, other.memory_, size_) == 0); //zisti ci su zhodne dva objekty, vrati false ak sa jedna o ten isty objekt		
	}

	byte& Vector::operator[](const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return *(reinterpret_cast<byte*> (memory_) + index);
	}

	byte Vector::operator[](const int index) const //teraz sa vytvory novy, lebo na zaciatku nie je adresa
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return *(reinterpret_cast<byte*> (memory_) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest) //od indexu, zober tolkoto bytov a zapis do tejto adresy 
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		DSRoutines::rangeCheckExcept(index + count - 1, size_, "Invalid index + count!"); //-1 aby sme nesli mimo, indexuje sa od nuly 
		memcpy(&dest, getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		//DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Invalid src index!");
		DSRoutines::rangeCheckExcept(srcStartIndex + length - 1, src.size_, "Invalid src + length index!");
		//DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Invalid dest index!");
		DSRoutines::rangeCheckExcept(destStartIndex + length - 1, dest.size_, "Invalid dest + length index!");
		/*
		if (&dest == &src)
		{
			if (abs(srcStartIndex - destStartIndex) > length)
			{
				memmove(reinterpret_cast <byte *> (dest.memory_) + destStartIndex, reinterpret_cast<byte *> (src.memory_) + srcStartIndex, length);
			}
			else
			{
				memcpy(reinterpret_cast <byte *> (dest.memory_) + destStartIndex, reinterpret_cast<byte *> (src.memory_) + srcStartIndex, length);
			}
		}
		else
		{
			memcpy(reinterpret_cast <byte *> (dest.memory_) + destStartIndex, reinterpret_cast<byte *> (src.memory_) + srcStartIndex, length);
		}
		*/
		if (&src == &dest &&
			(destStartIndex >= srcStartIndex && destStartIndex < srcStartIndex + length) ||
			(srcStartIndex >= destStartIndex && srcStartIndex < destStartIndex + length))
		{
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else
		{
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}


	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index!");
		return (reinterpret_cast<byte*> (memory_) + index); //dali sme prec * lebo chceme smernik 
	}
	/*
		DU uloha
	*/
	Vector::Vector(Vector && other)
		: memory_(other.memory_),
		size_(other.size_)
	{
		other.memory_ = nullptr;
		other.size_ = 0;
	}

	Vector & Vector::operator=(Vector && other)
	{
		if (this != &other)
		{
			delete[] memory_;
			memory_ = std::move(other.memory_);
			size_ = (other.size_); //neviem ci tu ma byt std::move 
		}
		return *this;
	}