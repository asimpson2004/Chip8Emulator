#ifndef _ENDIAN_H_
#define _ENDIAN_H_

//big endian 0xAABB ( mac )
//little endian 0xBBAA ( intel and amd )

//endian conversion functions
namespace endian
{ 
	//functions
	void format( );

	//function pointers
	extern unsigned short ( *bigU16 )( unsigned short s );
	extern short ( *bigS16 )( short s );

	extern unsigned short ( *littleU16 )( unsigned short s );
	extern short ( *littleS16 )( short s );

	extern unsigned int	( *bigU32 )( unsigned int i );
	extern int ( *bigS32 )( int i );

	extern unsigned int	( *littleU32 )( unsigned int i );
	extern int ( *littleS32 )( int i );

	extern void ( *bigFloat )( float& f );

	extern void ( *littleFloat )( float& f );

	extern void ( *bigDouble )( double& d );

	extern void ( *littleDouble )( double& d );
}

#endif //ENDIAN_H_
