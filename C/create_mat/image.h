/*
 *  Establishment date:  2009-5-7
 *  Author            :	 jasonleakey
 *  Copyleft(R) by jasonleakey
 *  <jasonleakey@gmail.com>
 *  <QQ:174481438>
 *  --------------------------------------------------------------------
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301, USA.
 *  --------------------------------------------------------------------
 *  image.h:
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#pragma pack(1)

#define TYPE 2 // two temperatures
#define SUBFRAMES 154
#define SCL_FRM_CNT  19 // 19 scaling photos at each temperature
#define ROW 240 // photo size = 320 * 240
#define COLUMN 320
#define TTL_FRAME 173 /* total frame count */
#define SUBF_PIXEL_COUNT 499
#define IMG_FRM_CNT 135 // 135 imaging photos totally
#define MAX_BLIND_NUM 320 * 24 /* the max blind pixel amount */

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef __int64 DDWORD;

typedef struct _point_t {
	int x;
	int y;
} point_t;


typedef enum mode_t {
	LOW_T = 0x22,
	HIGH_T = 0x33,
	IMAGING = 0x01,
} mode_t;

typedef struct {
	DWORD syn_code; //1AH CFH FCH 1DH
	BYTE satl_id_code; // E1H
	BYTE eff_load_id; // 66H
	WORD frame_count; // modulus: 65536
	DDWORD encrypt_info;
	DDWORD time_code; // 2Bytes for one cycle, 3Bytes for sec, 3Bytes for
	                      // micro sec
	BYTE subcount; // low byte represent SN in subframes.
	BYTE mode; // high byte involves 01H for imaging mode
				// 22H for room temperature, 33H for high one.
	WORD img_data[SUBF_PIXEL_COUNT]; // 998bytes where 2byte for each pixel
} subframe_t;

/*******************************************************/
/* we need store information to 24-bit BMPs.*/

#if 0
/* BMP file header */
typedef struct tagBITMAPFILEHEADER {
    WORD    bfType; /* 0x4D42 */
    DWORD   bfSize; /* Size of the BMP file */
    WORD    bfReserved1; /* Application Specific, unused */
    WORD    bfReserved2;
    DWORD   bfOffBits; /* The offset where the bitmap data (pixels) can be found.*/
} BITMAPFILEHEADER;

/* BMP information header */
typedef struct tagBITMAPINFOHEADER{
    DWORD  biSize; /* The number of bytes in the header (from this point).*/
    DWORD   biWidth; /* The width of bitmap, HERE 320 */
    DWORD   biHeight; /* the height of bitmap, HERE 240 */
    WORD   biPlanes; /* number of color planes being used.Must be 1*/
    WORD   biBitCount; /* the number of bits per pixel, HERE 24bit/pixel */
    DWORD  biCompression; /* BI_RGB, No compression used for default */
    DWORD  biSizeImage; /* The size of the raw BMP data (after this header) */
    DWORD  biXPelsPerMeter; /* The horizontal resolution of the image */
    DWORD   biYPelsPerMeter; /* The vertical resolution of the image */
    DWORD  biClrUsed; /* Number of colors in the palette */
    DWORD  biClrImportant; /* Means all colors are important */
} BITMAPINFOHEADER;

#endif /* BMP */

/***************************************************/
#if 0

int find_blind(double scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN],\
		point_t blind_point[]);
int remove_blind(double frames[][ROW][COLUMN], int frame_cnt,\
		point_t blind_point[], int cnt);

int output_txt(double matrix[IMG_FRM_CNT][ROW][COLUMN], int frames, char type);
int correct_img(double imaging[IMG_FRM_CNT][ROW][COLUMN],\
		double G[ROW][COLUMN], double O[ROW][COLUMN]);

extern int create_BMPs(double image[][ROW][COLUMN], int frame_count,char type);
extern int store_data(double scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN],\
		double imaging[IMG_FRM_CNT][ROW][COLUMN], subframe_t sub_frames[]);
extern int get_coefficient(const double scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN],\
		double G[ROW][COLUMN], double O[ROW][COLUMN]);
int create_mat(double scaling[TYPE][SCL_FRM_CNT][ROW][COLUMN],\
		double imaging[IMG_FRM_CNT][ROW][COLUMN]);

#endif

#endif /* IMAGE_H_ */
