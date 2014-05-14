/*
	ParticleSystems
*/

#ifndef PARTICLESYS_H
#define PARTICLESYS_H

#include <ObjectClass.h>
#include <ParticleSystemTypeClass.h>
#include <ParticleClass.h>

class ParticleSystemClass : public ObjectClass
{
public:
	enum {AbsID = abs_ParticleSystem};

	//Static
	static DynamicVectorClass<ParticleSystemClass*>* Array;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~ParticleSystemClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() const R0;
	virtual int Size() const R0;

	//Constructor
	ParticleSystemClass(
		ParticleSystemTypeClass* pParticleSystemType,
		const CoordStruct& coords,
		AbstractClass* pTarget,
		TechnoClass* pOwner,
		const CoordStruct& targetCoords,
		HouseClass* pOwnerHouse) : ObjectClass(false)
			{ JMP_THIS(0x62DC50); }

protected:
	ParticleSystemClass() : ObjectClass(false) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	ParticleSystemTypeClass* Type;
	CoordStruct  SpawnDistanceToOwner;
	DynamicVectorClass<ParticleClass*> Particles;
	CoordStruct TargetCoords;
	TechnoClass* Owner;
	AbstractClass* Target; // CellClass or TechnoClass
	int          SpawnFrames; //from ParSysTypeClass
	int          Lifetime; //from ParSysTypeClass
	int          SparkSpawnFrames; //from ParSysTypeClass
	int          SpotlightRadius; //defaults to 29
	bool         TimeToDie;
	bool         unknown_bool_F9;
	HouseClass*  OwnerHouse;
};

#endif
