/**************************************************************************
 *                                                                        *
 *                                                                        *
 *          This code is copyright (c) 1995                               *
 *                     Athena Design, Inc.                                *
 *                                                                        *
 *                                                                        *
 *                ALL RIGHTS RESERVED                                     *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 *                                                                        *
 **************************************************************************/

// this is the base class of all objects that have virtual tables in Mesa
// This class will allow other classes and instances to query info about themselves
// and also track the number of new's and delete's in a debug-mode
// 95-01-15 dpp

#ifndef MH_object_to_this
#define MH_object_to_this

// if this is defined, then we're in debug mode
// #define MOBJECTDEBUGMODE

// #define ISSOM

#ifdef ISSOM
// #include <som.hh>

pragma SomNoMangling(On);
pragma Off(Case_insensitive_class_names);
pragma Off(Use_override_signature);
pragma Off(SOM_inline);
pragma Off(Direct_attribute_access);
pragma Offwarn(216);

class MObject : public SOMObject
#else
class MObject
#endif
{
	public:
	MObject();
	MObject(const char *,int);
	virtual ~MObject();

	private:
	static count;
};

#ifdef MOBJECTDEBUGMODE
#define MObject() MObject(__FILE__,__LINE__)
#endif

// #ifndef MH_object_to_this
#endif
