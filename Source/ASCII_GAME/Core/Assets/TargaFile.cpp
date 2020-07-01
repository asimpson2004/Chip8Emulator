#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "../Platform/Endian.h"
#include "../Platform/File.h"

#include "TargaFile.h"

bool TargaFile::load(const char *filename)
{
	//targa header structure
	struct targaHeader
	{
		unsigned char idLength;
		unsigned char colorMapType;
		unsigned char type;
		unsigned char colorMapOrigin[2];
		unsigned char colorMapLength[2];
		unsigned char colorMapEntrySize;
		unsigned char originX[2];
		unsigned char originY[2];
		unsigned char width[2];
		unsigned char height[2];
		unsigned char bits;
		unsigned char descriptor;
	};
	
	//targa load data
	long			pos;
	fileType		file;
	targaHeader		tgaHeader;
	unsigned short	channels;
	long			i;
	long			n = 0;

	//load tga
	if (!file.load(filename))
		return false;

	//targa header
	pos = 0;
	memcpy( &tgaHeader, file.buffer, sizeof( targaHeader ) );
	pos += sizeof( targaHeader );

	//image format
	channels = tgaHeader.bits / 8;
	
	//image size
	width	= *( (unsigned short *) tgaHeader.width );
	height	= *( (unsigned short *) tgaHeader.height );

	size	= width * height * 4;

	long finalsize	= width * height * channels;

	//create image buffer
	if ( buffer != nullptr ) free( buffer );
	buffer = (unsigned char *) malloc( size );
	memset( buffer, 0, size );

	//uncompressed targa
	if ( tgaHeader.type == 2 || tgaHeader.type == 3 )
	{
		//transfer bgr(a) to rgb(a) buffer
		for ( i = 0; i < finalsize; i += channels )
		{

			buffer[n]	= file.buffer[pos+i+2];
			buffer[n+1] = file.buffer[pos+i+1];
			buffer[n+2] = file.buffer[pos+i];
				
			//alpha value
			if ( channels == 4 )
			{
				buffer[n+3] = file.buffer[pos+i+3];
			}
			else
			{
				buffer[n+3] = 255;
			}
			n += 4;
		}
	}
	else//compressed targa (RLE)
	{
		unsigned int	pixel_count		= height * width;
		unsigned int	current_pixel	= 0;
		unsigned char  *pixel_channels = (unsigned char *) malloc( channels );
		short			counter;

		//read pixel chunks
		do
		{
			//read chunk header
			unsigned char chunk_header = 0;
			chunk_header = file.buffer[pos];
			pos++;

			//raw chunk
			if ( chunk_header < 128 )
			{			
				//chunk size
				chunk_header++;

				for( counter = 0; counter < chunk_header; counter++ )
				{
					//read pixels
					memcpy( pixel_channels, file.buffer+pos, channels );
					pos += channels;

					//transfer pixel to image buffer ( bgr to rgb )

					buffer[n	] = pixel_channels[2];
					buffer[n + 1] = pixel_channels[1];
					buffer[n + 2] = pixel_channels[0];
					if ( channels == 4 )	buffer[n + 3] = pixel_channels[3];
					else buffer[n + 3] = 255;

					//increment byte and pixel count
					n += 4;
					current_pixel++;
				}
			}

			//rle chunk
			else
			{			
				//chunk size
				chunk_header -= 127;

				//read next pixel
				memcpy( pixel_channels, file.buffer+pos, channels );
				pos += channels;

				for ( counter = 0; counter < chunk_header; counter++ )
				{
					//transfer pixel to image buffer ( bgr to rgb ) multiple times
					buffer[n	] = pixel_channels[2];
					buffer[n + 1] = pixel_channels[1];
					buffer[n + 2] = pixel_channels[0];
					if( channels == 4 )
					{
						buffer[n + 3] = pixel_channels[3];
					}
					else
					{
						buffer[n + 3] = 255;
					}
					
					//increment byte and pixel count
					n += 4;
					current_pixel++;
				}
			}
		}

		while( current_pixel < pixel_count );
	}

	return true;
}
