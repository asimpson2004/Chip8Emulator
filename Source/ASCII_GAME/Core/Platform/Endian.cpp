#include "Endian.h"
#include "../Utils/Utils.h"

//define endian functions
namespace endian
{
	//function pointers ( data types )
	unsigned short	( *bigU16 )( unsigned short s );
	short			( *bigS16 )( short s );

	unsigned short	( *littleU16 )( unsigned short s );
	short			( *littleS16 )( short s );

	unsigned int	( *bigU32 )( unsigned int i );
	int				( *bigS32 )( int i );

	unsigned int	( *littleU32 )( unsigned int i );
	int				( *littleS32 )( int i );

	void			( *bigFloat )( float& f );

	void			( *littleFloat )( float& f );

	void			( *bigDouble )( double& d );

	void			( *littleDouble )( double& d );

	//functions
	unsigned short	u16Swap( unsigned short s )		{ return ( ( s >> 8 ) | ( s << 8 ) ); }
	unsigned short	u16NoSwap( unsigned short s )	{ return s; }
		
	short			s16Swap( short s )				{ return ( ( s >> 8 ) | ( s << 8 ) ); }
	short			s16NoSwap( short s )			{ return s; }
		
	unsigned int	u32Swap( unsigned int l )		{ return ( ( ( l & 0x000000FF ) << 24 ) + ( ( l & 0x0000FF00 ) << 8 ) + ( ( l & 0x00FF0000 ) >> 8 ) + ( ( l & 0xFF000000 ) >> 24 ) ); }
	unsigned int	u32NoSwap( unsigned int l )		{ return l; }
		
	int				l32Swap( int l )				{ return ( ( ( l & 0x000000FF ) << 24 ) + ( ( l & 0x0000FF00 ) << 8 ) + ( ( l & 0x00FF0000 ) >> 8 ) + ( ( l & 0xFF000000 ) >> 24 ) ); }
	int				l32NoSwap( int l )				{ return l; }

	void			floatSwap( float& f )			{ int *pnt = (int*)&f;	*pnt = l32Swap( *pnt ); }
	void			floatNoSwap( float& f )			{ 	UNUSED_VARIABLE(f); }
		
	void			doubletSwap( double& d )		{ int *pnt = (int*)&d;	*pnt = l32Swap( *pnt ); }
	void			doubleNoSwap( double& d )		{ UNUSED_VARIABLE(d); }
}


//**************************************************************************
//name: endian format
//desc:	determines endian format and sets data types
//args:	n/a
//rets:	n/a
//nots: n/a
//**************************************************************************
void endian::format( )
{
	//determine endian
	char test[2] = { 1, 0 };

	//little endian
	if( *(short *) test == 1 )
	{
		bigU16			= u16Swap;
		bigS16			= s16Swap;

		littleU16		= u16NoSwap;
		littleS16		= s16NoSwap;

		bigU32			= u32Swap;
		bigS32			= l32Swap;

		littleU32		= u32NoSwap;
		littleS32		= l32NoSwap;

		bigFloat		= floatSwap;

		littleFloat		= floatNoSwap;

		bigDouble		= doubletSwap;

		littleDouble	= doubleNoSwap;
	}

	//big endian
	else
	{
		bigU16			= u16NoSwap;
		bigS16			= s16NoSwap;

		littleU16		= u16Swap;
		littleS16		= s16Swap;

		bigU32			= u32NoSwap;
		bigS32			= l32NoSwap;

		littleU32		= u32Swap;
		littleS32		= l32Swap;

		bigFloat		= floatNoSwap;

		littleFloat		= floatSwap;

		bigDouble		= doubleNoSwap;

		littleDouble	= doubletSwap;
	}
}
