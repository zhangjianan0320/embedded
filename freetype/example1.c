/* example1.c                                                      */
/*                                                                 */
/* This small program shows how to print a rotated string with the */
/* FreeType 2 library.                                             */


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iconv.h>
#include <ft2build.h>
#include <freetype/ftglyph.h>
#include FT_FREETYPE_H

#include <wchar.h>

//#define WIDTH   640
//#define HEIGHT  480

#define WIDTH   200
#define HEIGHT  24

static int g_width=200;
static int g_height=24;

/* origin is the upper left corner */
//unsigned char image[HEIGHT][WIDTH];
unsigned char image[500][500];
//UTF-8转成wchar_t
int FUTF82WConvert( const char* a_szSrc, wchar_t* a_szDest, int a_nDestSize )
{

#ifdef WINDOWS
 return MultiByteToWideChar( CP_UTF8, 0, a_szSrc, -1, a_szDest, a_nDestSize );
 #else
  size_t result;
  iconv_t env;
  int size = strlen(a_szSrc)+1;
     env = iconv_open("WCHAR_T","UTF-8");
      if(env==(iconv_t)-1)
      {
        return -1;
      }
	  result = iconv(env,(char**)&a_szSrc,(size_t*)&size,(char**)&a_szDest,(size_t*)&a_nDestSize);
	  printf("result\n");
     if (result==(size_t)-1)
     {
         return -1;
     }
	else
	{
         iconv_close(env);
         return (int)result;
	}
#endif
}

void cTow(char *str,wchar_t *wstr)
{
	FUTF82WConvert(str,wstr,128);
	int len=wcslen(wstr);
	printf("wstr len:%d\n",len);

}

/* Replace this function with something useful. */

void
draw_bitmap( FT_Bitmap*  bitmap,
             FT_Int      x,
             FT_Int      y)
{
  FT_Int  i, j, p, q;
  FT_Int  x_max = x + bitmap->width;
  FT_Int  y_max = y + bitmap->rows;
//  printf("x:%d,y:%d\n",x,y);

  /* for simplicity, we assume that `bitmap->pixel_mode' */
  /* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

  for ( i = x, p = 0; i < x_max; i++, p++ )
  {
    for ( j = y, q = 0; j < y_max; j++, q++ )
    {
      if ( i < 0      || j < 0       ||
           i >= g_width || j >= g_height )
        continue;

      image[j][i] |= bitmap->buffer[q * bitmap->width + p];
    }
  }
}


void
show_image( void )
{
  int  i, j;

/*
  for ( i = 0; i < HEIGHT; i++ )
  {
    for ( j = 0; j < WIDTH; j++ )
      putchar( image[i][j] == 0 ? '-'
                                : image[i][j] < 128 ? '+'
                                                    : '*' );
    putchar( '\n' );
  }
*/
  for ( i = 0; i < g_height; i++ )
  {
    for ( j = 0; j < g_width; j++ )
      putchar( image[i][j] == 0 ? '-'
                                : image[i][j] < 128 ? '+'
                                                    : '*' );
    putchar( '\n' );
  }
}

#define MAX_GLYPHS 100

int
main( int     argc,
      char**  argv )
{
  FT_Library    library;
  FT_Face       face;

  FT_GlyphSlot  slot;
  
  FT_Matrix     matrix;                 /* transformation matrix */
  FT_Vector     pen;                    /* untransformed origin  */
  FT_Error      error;

  char*         filename;

  double        angle;
  int           target_height;
  int           n, num_chars;
  wchar_t chinese_str[128];//=L"大家号";

  memset(chinese_str,0,sizeof(chinese_str));
  if (argc != 7)
  {
    fprintf ( stderr, "usage: %s font text width height font_size wordSpacing\n", argv[0] );
    exit( 1 );
  }

  g_width = atoi(argv[3]);
  g_height = atoi(argv[4]);

  int font_size=atoi(argv[5]);
  int word_spacing=atoi(argv[6]);

  g_height = font_size;
  filename      = argv[1];                           /* first argument     */
  char str[128];
  strcpy(str,argv[2]);


  cTow(str,chinese_str);
  angle         = ( 0.0 / 360 ) * 3.14159 * 2;      /* use 25 degrees     */
  target_height = g_height;

  error = FT_Init_FreeType( &library );              /* initialize library */
  /* error handling omitted */

  error = FT_New_Face( library, filename, 0, &face );/* create face object */
  /* error handling omitted */

  /* use 50pt at 100dpi */
  error=FT_Set_Pixel_Sizes(face,font_size,0);

  /* cmap selection omitted;                                        */
  /* for simplicity we assume that the font contains a Unicode cmap */
  slot = face->glyph;

  /* set up matrix */
  matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
  matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
  matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
  matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );

  /* the pen position in 26.6 cartesian space coordinates; */
  pen.x = 0  * 64;
  pen.y = ( target_height-g_height) * 64;
printf("target_height:%d,g_height:%d,pen.y:%d\n",target_height,g_height,pen.y);


  FT_Glyph glyphs[MAX_GLYPHS];
  FT_Vector vector[MAX_GLYPHS];
  FT_UInt num_glyphs=0;
  FT_UInt glyph_index;
  int pen_x=0,pen_y=( target_height-g_height) * 64;
printf("ok\n");
//  FT_Glyph glyph = glyphs;
  for ( n = 0; n < wcslen(chinese_str); n++ )
  {
	glyph_index = FT_Get_Char_Index(face,chinese_str[n]);
	vector[n].x=pen_x;
	vector[n].y=pen_y;
	FT_Load_Glyph(face,glyph_index,FT_LOAD_DEFAULT);
	FT_Get_Glyph(face->glyph,&glyphs[n]);
	int pos = word_spacing * slot->advance.x / 100;
	pen_x += slot->advance.x+pos;
	pen_y += slot->advance.y;
	num_glyphs++;
//	printf("num_glyphs is %d,pen_x = %d\n",num_glyphs,pen_x);
  }
  FT_Int start_x=0;

  FT_Int box_width = g_width*64;
  printf("g_width is %d\n",g_width);
//  if(box_width > pen_x)
  {
    //居中
    //start_x = (box_width - pen_x)/2;
    //右对齐
    start_x = box_width - pen_x;
  }
  printf("start_x is %d\n",start_x);

  pen.x = 0;
  pen.y = 0;
  for(n = 0;n < num_glyphs;n++)
  {
	FT_Glyph image;
        FT_Vector pen;
        image = glyphs[n];
        pen.x = vector[n].x + start_x;
        pen.y = vector[n].y;
	FT_Glyph_To_Bitmap(&image,FT_RENDER_MODE_NORMAL,&pen,0);
	FT_BitmapGlyph bit = (FT_BitmapGlyph)image;
	draw_bitmap( &bit->bitmap,bit->left,target_height - bit->top );
	FT_Done_Glyph(image);
  }

  show_image();

  FT_Done_Face    ( face );
  FT_Done_FreeType( library );

  return 0;
}

/* EOF */
