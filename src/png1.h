/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef PNG_H_3874
#define PNG_H_3874

#include <png.h>
#include <string>
using std::string;

class mPng
{
	public:
	class Image
	{
		public:
		int width;
		int height;
		unsigned char * data;
		Image():width(0),height(0),data(0){}
		virtual ~Image() { delete data; }
	  unsigned char& value(int i, int j, int k) { return *( data + ( ( i * width + j ) * 4 + k )); }
    const unsigned char& value(int i, int j, int k) const { return *( data + ( ( i * width + j ) * 4 + k )); }
	};
	
	static void read( string name, Image& img )
  {
	  FILE *fp = fopen(name.c_str(), "rb" );
	  if( !fp ) return;
	
	  png_byte header[8];
	  fread(header,1,8,fp);
	  if( png_sig_cmp(header,0,8) )
	  {
		  fclose(fp);
		  return;
	  }
	
	  png_structp png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
	  if(!png_ptr)
	  {
		  fclose(fp);
		  return;
	  }
	
	  png_infop info_ptr = png_create_info_struct(png_ptr);
	  if( !info_ptr)
	  {
		  png_destroy_read_struct( &png_ptr, 0, 0 );
		  fclose(fp);
		  return;
	  }
	
	  png_infop end_info = png_create_info_struct(png_ptr);
	  if( !end_info)
	  {
		  png_destroy_read_struct( &png_ptr, &info_ptr, 0 );
		  fclose(fp);
		  return;
	  }
	
	  if( setjmp( png_jmpbuf( png_ptr ) ) )
	  {
		  png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
		  fclose(fp);
		  return;
	  }
	
	  png_init_io( png_ptr, fp );
	  png_set_sig_bytes( png_ptr, 8 );
	
	  png_read_info( png_ptr, info_ptr );
	
	  png_uint_32 width, height;
	  int bit_depth, color_type, interlace_type, compression_type, filter_method;
	  png_get_IHDR( png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_method );
	
    if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
      png_set_palette_to_rgb(png_ptr);
  	  if (png_get_valid(png_ptr, info_ptr,
                 PNG_INFO_tRNS)) 
		  png_set_tRNS_to_alpha(png_ptr);		
    }
	  //png_size_t rowbytes =  png_get_rowbytes( png_ptr, info_ptr );

	  img.width = width; img.height = height;
	  delete img.data;
	  img.data = new unsigned char[4*width*height];
	  png_bytep * row_pointers = new png_bytep[height];
	  int i;
	  for( i = 0; i < height; ++i )
		  row_pointers[height-i-1] = (png_bytep)(img.data + 4*width*i);
	  png_read_image(png_ptr, row_pointers);
	
	  png_read_end( png_ptr, end_info );
	
	  //Expand image if needed
	  if( color_type == PNG_COLOR_TYPE_GRAY )
	  {
		  int i;
		  long src, dst, count;
		  for( i = 0; i < height; ++i )
		  {
			  count = (long)width;
			  src = i*(long)width*4+count;
			  dst = (i+1)*(long)width*4-1;
			  while( count > 0 )
			  {
				  img.data[dst] = 255;
				  img.data[dst-1] = img.data[src-1];
				  img.data[dst-2] = img.data[src-1];
				  img.data[dst-3] = img.data[src-1];
				  src -= 1;
				  count -= 1;
				  dst -= 4;
			  }
		  }
	  }
	  else if( color_type == PNG_COLOR_TYPE_GRAY_ALPHA )
	  {
	    printf("png color type gray alpha\n");
		  int i;
		  long src, dst, count;
		  for( i = 0; i < height; ++i )
		  {
			  count = (long)width*2;
			  src = i*(long)width*4+count;
			  dst = (i+1)*(long)width*4;
			  while( count > 1 )
			  {
				  img.data[dst-1] = img.data[src-1];
				  img.data[dst-2] = img.data[src-2];
				  img.data[dst-3] = img.data[src-2];
				  img.data[dst-4] = img.data[src-2];
				  src -= 2;
				  count -= 2;
				  dst -= 4;
			  }
		  }
	  }
	  else if( color_type == PNG_COLOR_TYPE_RGB )
	  {
		  int i;
		  long src, dst, count;
		  for( i = 0; i < height; ++i )
		  {
			  count = (long)width*3;
			  src = i*(long)width*4+count;
			  dst = (i+1)*(long)width*4-1;
			  while( count > 2 )
			  {
				  img.data[dst] = 255;
				  img.data[dst-1] = img.data[src-1];
				  img.data[dst-2] = img.data[src-2];
				  img.data[dst-3] = img.data[src-3];
				  src -= 3;
				  count -= 3;
				  dst -= 4;
			  }
		  }
	  }

	
	
	  delete row_pointers;
	  png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
	  fclose(fp);
  }
	
	static void write( string name, const Image& img )
	{
	  FILE * fp = fopen( name.c_str(), "wb" );
	  if( !fp ) return;
	
	  png_structp png_ptr = png_create_write_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );
	  if(!png_ptr)
	  {
		  fclose(fp);
		  return;
	  }
	
	  png_infop info_ptr = png_create_info_struct(png_ptr);
	  if( !info_ptr)
	  {
		  png_destroy_write_struct( &png_ptr, 0 );
		  fclose(fp);
		  return;
	  }
	
	  if( setjmp( png_jmpbuf( png_ptr ) ) )
	  {
		  png_destroy_write_struct( &png_ptr, &info_ptr );
		  fclose(fp);
		  return;
	  }
	
	  png_init_io( png_ptr, fp );
	
	  png_set_IHDR( png_ptr, info_ptr, img.width, img.height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT );
	
	  png_write_info( png_ptr, info_ptr );
	
	  png_bytep * row_pointers = new png_bytep[img.height];
	  int i;
	  for( i = 0; i < img.height; ++i )
		  row_pointers[img.height-i-1] = (png_bytep)(img.data + 4*img.width*i);
	  png_write_image(png_ptr, row_pointers);
	  png_write_end( png_ptr, 0 );
	
	  delete row_pointers;
	  png_destroy_write_struct( &png_ptr, &info_ptr );
	  fclose(fp);
  }
};

#endif

