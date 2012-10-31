#ifndef GENERALSTRUCTURES_H
#define GENERALSTRUCTURES_H

#include <ASMMacros.h>
#include <YRPPCore.h>
#include <YRMathVector.h>
#include <GeneralDefinitions.h> // need eDirection for FacingStruct

//used for cell coordinates/vectors
#ifndef VECTORSTRUCTS
#define VECTORSTRUCTS
typedef Vector2D<short> CellStruct;
typedef Vector2D<int> Point2D;
typedef Vector3D<int> CoordStruct;

// used for particle ColorList
typedef Vector3D<BYTE> RGBClass; // <pd> wuhaha
#endif

//used for most colors
struct ColorStruct
{
	BYTE R, G, B;

	void operator = (ColorStruct Color)
	{
		R = Color.R;
		G = Color.G;
		B = Color.B;
	}

	bool operator == (ColorStruct rhs)
	{
		return R == rhs.R && G == rhs.G && B == rhs.B;
	}

	ColorStruct()
	{
	}

	ColorStruct(BYTE _R, BYTE _G, BYTE _B)
	{
		R = _R;
		G = _G;
		B = _B;
	}
};

#ifndef PALETTE_STRUCT
#define PALETTE_STRUCT
struct BytePalette {
	ColorStruct Entries[256];
	ColorStruct & operator [](const int idx) {
		return this->Entries[idx];
	}
};
#endif

//used for light colors
struct TintStruct
{
	int Red, Green, Blue;
};

//16bit colors
#pragma pack(push, 1)
struct Color16Struct
{
	int R:5;
	int G:6;
	int B:5;

	void operator = (Color16Struct Color)
	{
		R = Color.R;
		G = Color.G;
		B = Color.B;
	}

	void operator = (ColorStruct Color)
	{
		R = Color.R >> 3;
		G = Color.G >> 2;
		B = Color.B >> 3;
	}

	bool operator == (Color16Struct rhs)
	{
		return R == rhs.R && G == rhs.G && B == rhs.B;
	}

	Color16Struct()
	{
	}
};
#pragma pack(pop)

//uses the clock values
struct DirStruct
{
	short Facing;
};

//Random numbe range
struct RandomStruct
{
	int Min, Max;
};

//3D Matrix
struct Matrix3DStruct
{
	float Data[12];
};

//obvious
struct RectangleStruct
{
	int X, Y, Width, Height;
};

//used for timed events, time measured in frames!
class TimerStruct
{
public:
	int StartTime;
	int unknown;
	int TimeLeft;

	void Stop()
		{ this->StartTime = -1; this->TimeLeft = 0; }

	bool IsDone() const
		{ return this->StartTime != -1 && this->GetTimeLeft() <= 0; }

	bool Ignorable() const
		{ return this->StartTime == -1 || this->GetTimeLeft() <= 0; }

	int GetTimeLeft() const
		{ JMP_THIS(0x426630); }

	void Start(int duration)
		{ JMP_THIS(0x46B640); }

	void StartIfEmpty() // just sets start frame
		{ JMP_THIS(0x6CE2C0); }
};

//also see FACING definitions
struct FacingStruct
{
	// contains an unsigned fixed point value.
	struct Data {
		typedef WORD Raw;
		typedef int Rounded;

		Data() : Value(0) { }
		Data(Raw value) : Value(value) { }
		Data(Rounded facing) : Value((facing & 0xFF) << 8) { }

		operator Rounded() const {
			// value / 256 with rounding
			return (((this->Value >> 7) + 1) >> 1) & 0xFF;
		}

		operator Raw() const {
			return this->Value;
		}

		Raw Value;
	private:
		WORD unused_2;
	};

	Data Value; //current facing
	Data Target; //target facing
	TimerStruct Timer; //rotation?
	Data ROT; //Rate of Turn. INI Value * 256

	Data* GetFacing(Data *buffer)
		{ JMP_THIS(0x4C93D0); }

	void SetFacing(Data *arg)
		{ JMP_THIS(0x4C9300); }

	operator int() {
		// <DCoder> I don't know how or what it does, but that's what the game uses
		Data nessie;
		this->GetFacing(&nessie); // mysterious facing value from the depths of the game
		return nessie;
	}
};

struct SomeVoxelCache {
	void *ptr;
	DWORD f_4;
	DWORD f_8;
	BYTE f_C;
	DWORD * ptr_10;
};

struct BasePlanningCell {
	int Weight;
	CellStruct Position;
};

// this crap is used in several Base planning routines
struct BasePlanningCellContainer {
	BasePlanningCell * Items;
	int Count;
	int Capacity;
	bool Sorted;
	DWORD Unknown_10;

	bool AddCapacity(int AdditionalCapacity)
		{ JMP_THIS(0x510860); }

	// for qsort
	static int __cdecl Comparator(const void *, const void *)
		{ JMP_STD(0x5108F0); }
};

#endif
