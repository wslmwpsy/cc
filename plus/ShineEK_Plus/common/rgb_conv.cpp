#include "StdAfx.h"
#include ".\rgb_conv.h"

/*-----------windows 256色颜色索引表----------------------*/
RGB_QUAD rgb_quad[256] = {
	0, 0, 0, 0, 0, 0, 128, 0, 0, 128, 0, 0, 0, 128, 128, 0, 
		128, 0, 0, 0, 128, 0, 128, 0, 128, 128, 0, 0, 192, 192, 192, 0, 
		192, 220, 192, 0, 240, 202, 166, 0, 0, 32, 64, 0, 0, 32, 96, 0, 
		0, 32, 128, 0, 0, 32, 160, 0, 0, 32, 192, 0, 0, 32, 224, 0, 
		0, 64, 0, 0, 0, 64, 32, 0, 0, 64, 64, 0, 0, 64, 96, 0, 
		0, 64, 128, 0, 0, 64, 160, 0, 0, 64, 192, 0, 0, 64, 224, 0, 
		0, 96, 0, 0, 0, 96, 32, 0, 0, 96, 64, 0, 0, 96, 96, 0, 
		0, 96, 128, 0, 0, 96, 160, 0, 0, 96, 192, 0, 0, 96, 224, 0, 
		0, 128, 0, 0, 0, 128, 32, 0, 0, 128, 64, 0, 0, 128, 96, 0, 
		0, 128, 128, 0, 0, 128, 160, 0, 0, 128, 192, 0, 0, 128, 224, 0, 
		0, 160, 0, 0, 0, 160, 32, 0, 0, 160, 64, 0, 0, 160, 96, 0, 
		0, 160, 128, 0, 0, 160, 160, 0, 0, 160, 192, 0, 0, 160, 224, 0, 
		0, 192, 0, 0, 0, 192, 32, 0, 0, 192, 64, 0, 0, 192, 96, 0, 
		0, 192, 128, 0, 0, 192, 160, 0, 0, 192, 192, 0, 0, 192, 224, 0, 
		0, 224, 0, 0, 0, 224, 32, 0, 0, 224, 64, 0, 0, 224, 96, 0, 
		0, 224, 128, 0, 0, 224, 160, 0, 0, 224, 192, 0, 0, 224, 224, 0, 
		64, 0, 0, 0, 64, 0, 32, 0, 64, 0, 64, 0, 64, 0, 96, 0, 
		64, 0, 128, 0, 64, 0, 160, 0, 64, 0, 192, 0, 64, 0, 224, 0, 
		64, 32, 0, 0, 64, 32, 32, 0, 64, 32, 64, 0, 64, 32, 96, 0, 
		64, 32, 128, 0, 64, 32, 160, 0, 64, 32, 192, 0, 64, 32, 224, 0, 
		64, 64, 0, 0, 64, 64, 32, 0, 64, 64, 64, 0, 64, 64, 96, 0, 
		64, 64, 128, 0, 64, 64, 160, 0, 64, 64, 192, 0, 64, 64, 224, 0, 
		64, 96, 0, 0, 64, 96, 32, 0, 64, 96, 64, 0, 64, 96, 96, 0, 
		64, 96, 128, 0, 64, 96, 160, 0, 64, 96, 192, 0, 64, 96, 224, 0, 
		64, 128, 0, 0, 64, 128, 32, 0, 64, 128, 64, 0, 64, 128, 96, 0, 
		64, 128, 128, 0, 64, 128, 160, 0, 64, 128, 192, 0, 64, 128, 224, 0, 
		64, 160, 0, 0, 64, 160, 32, 0, 64, 160, 64, 0, 64, 160, 96, 0, 
		64, 160, 128, 0, 64, 160, 160, 0, 64, 160, 192, 0, 64, 160, 224, 0, 
		64, 192, 0, 0, 64, 192, 32, 0, 64, 192, 64, 0, 64, 192, 96, 0, 
		64, 192, 128, 0, 64, 192, 160, 0, 64, 192, 192, 0, 64, 192, 224, 0, 
		64, 224, 0, 0, 64, 224, 32, 0, 64, 224, 64, 0, 64, 224, 96, 0, 
		64, 224, 128, 0, 64, 224, 160, 0, 64, 224, 192, 0, 64, 224, 224, 0, 
		128, 0, 0, 0, 128, 0, 32, 0, 128, 0, 64, 0, 128, 0, 96, 0, 
		128, 0, 128, 0, 128, 0, 160, 0, 128, 0, 192, 0, 128, 0, 224, 0, 
		128, 32, 0, 0, 128, 32, 32, 0, 128, 32, 64, 0, 128, 32, 96, 0, 
		128, 32, 128, 0, 128, 32, 160, 0, 128, 32, 192, 0, 128, 32, 224, 0, 
		128, 64, 0, 0, 128, 64, 32, 0, 128, 64, 64, 0, 128, 64, 96, 0, 
		128, 64, 128, 0, 128, 64, 160, 0, 128, 64, 192, 0, 128, 64, 224, 0, 
		128, 96, 0, 0, 128, 96, 32, 0, 128, 96, 64, 0, 128, 96, 96, 0, 
		128, 96, 128, 0, 128, 96, 160, 0, 128, 96, 192, 0, 128, 96, 224, 0, 
		128, 128, 0, 0, 128, 128, 32, 0, 128, 128, 64, 0, 128, 128, 96, 0, 
		128, 128, 128, 0, 128, 128, 160, 0, 128, 128, 192, 0, 128, 128, 224, 0, 
		128, 160, 0, 0, 128, 160, 32, 0, 128, 160, 64, 0, 128, 160, 96, 0, 
		128, 160, 128, 0, 128, 160, 160, 0, 128, 160, 192, 0, 128, 160, 224, 0, 
		128, 192, 0, 0, 128, 192, 32, 0, 128, 192, 64, 0, 128, 192, 96, 0, 
		128, 192, 128, 0, 128, 192, 160, 0, 128, 192, 192, 0, 128, 192, 224, 0, 
		128, 224, 0, 0, 128, 224, 32, 0, 128, 224, 64, 0, 128, 224, 96, 0, 
		128, 224, 128, 0, 128, 224, 160, 0, 128, 224, 192, 0, 128, 224, 224, 0, 
		192, 0, 0, 0, 192, 0, 32, 0, 192, 0, 64, 0, 192, 0, 96, 0, 
		192, 0, 128, 0, 192, 0, 160, 0, 192, 0, 192, 0, 192, 0, 224, 0, 
		192, 32, 0, 0, 192, 32, 32, 0, 192, 32, 64, 0, 192, 32, 96, 0, 
		192, 32, 128, 0, 192, 32, 160, 0, 192, 32, 192, 0, 192, 32, 224, 0, 
		192, 64, 0, 0, 192, 64, 32, 0, 192, 64, 64, 0, 192, 64, 96, 0, 
		192, 64, 128, 0, 192, 64, 160, 0, 192, 64, 192, 0, 192, 64, 224, 0, 
		192, 96, 0, 0, 192, 96, 32, 0, 192, 96, 64, 0, 192, 96, 96, 0, 
		192, 96, 128, 0, 192, 96, 160, 0, 192, 96, 192, 0, 192, 96, 224, 0, 
		192, 128, 0, 0, 192, 128, 32, 0, 192, 128, 64, 0, 192, 128, 96, 0, 
		192, 128, 128, 0, 192, 128, 160, 0, 192, 128, 192, 0, 192, 128, 224, 0, 
		192, 160, 0, 0, 192, 160, 32, 0, 192, 160, 64, 0, 192, 160, 96, 0, 
		192, 160, 128, 0, 192, 160, 160, 0, 192, 160, 192, 0, 192, 160, 224, 0, 
		192, 192, 0, 0, 192, 192, 32, 0, 192, 192, 64, 0, 192, 192, 96, 0, 
		192, 192, 128, 0, 192, 192, 160, 0, 240, 251, 255, 0, 164, 160, 160, 0, 
		128, 128, 128, 0, 0, 0, 255, 0, 0, 255, 0, 0, 0, 255, 255, 0, 
		255, 0, 0, 0, 255, 0, 255, 0, 255, 255, 0, 0, 255, 255, 255, 0};


rgb_conv::rgb_conv(void)
{
}

rgb_conv::~rgb_conv(void)
{
}

int rgb_conv::rgb32torgb8(TCHAR *rgb32_path,TCHAR *rgb8_path)
{
	FILE* in=NULL;
	FILE* out=NULL;
	unsigned char* buf=NULL;
	int size_per_line=0;
	int i=0, j=0;

	BITMAPFILEHEADER bmp_file_head;
	BITMAPINFOHEADER bmp_info_head;

	INDEX_TABLE_NODE* index_root = NULL;
	INDEX_TABLE_NODE* cur_index_node = NULL;

	INDEX_TABLE_NODE* free_temp = NULL;
	INDEX_TABLE_NODE* index_temp = NULL;

	/*-------------------打开源文件------------------------------------*/
	if((in = _wfopen(rgb32_path, L"rb")) == NULL)
	{
		return 1;
	}

	/*-------------------打开目标文件----------------------------------*/
	if((out = _wfopen(rgb8_path, L"wb")) == NULL)
	{
		return 1;
	}

	/*-------------------读源文件头------------------------------------*/
	if(fread(&bmp_file_head, 1, sizeof(BITMAPFILEHEADER), in) != sizeof(BITMAPFILEHEADER))
	{
		fclose(in);
		return 1;
	}
	if(fread((char*)&bmp_info_head, 1, sizeof(BITMAPINFOHEADER), in) != sizeof(BITMAPINFOHEADER))
	{
        fclose(in);
		return 1;
	}

	/*-------------------开始转换--------------------------------------*/

	/*--------------修改文件头-------------------*/
	size_per_line = bmp_info_head.biWidth*4;
	bmp_file_head.bfOffBits = 1078;

	bmp_info_head.biSizeImage = bmp_info_head.biWidth * bmp_info_head.biHeight;
	bmp_file_head.bfSize = bmp_info_head.biSizeImage + bmp_file_head.bfOffBits;
	bmp_info_head.biBitCount = 8;

	/*----------写目的文件头及调色板-------------*/
	if(fwrite((unsigned char*)&bmp_file_head, 1, sizeof(BITMAPFILEHEADER), out) != sizeof(BITMAPFILEHEADER))
	{
		return 1;
	}
	if(fwrite((unsigned char*)&bmp_info_head, 1, sizeof(BITMAPINFOHEADER), out) != sizeof(BITMAPINFOHEADER))
	{
		return 1;
	}
	if(fwrite((unsigned char*)rgb_quad, 1, sizeof(rgb_quad), out) != sizeof(rgb_quad))
	{
		return 1;
	}

	/*----读源文件数据信息,并将rgb值转换成相应调色板索引----*/
	buf = new unsigned char[size_per_line];
	if (NULL==buf)
	{
		return 1;
	}
	for(i = 0; i < bmp_info_head.biHeight; i++)
	{
		if(fread(buf, 1, size_per_line, in) != size_per_line)
		{
			return 1;
		}

		for(j = 0; j < bmp_info_head.biWidth; j++)
		{
			if(!index_root)
			{
				index_root = new INDEX_TABLE_NODE;

				index_root->node = get_index(*(buf + j*4), *(buf + j*4+1), *(buf + j*4+2));
				index_root->next = NULL;
				cur_index_node = index_root;
			}
			else
			{
				index_temp = new INDEX_TABLE_NODE;

				index_temp->node = get_index(*(buf + j*4), *(buf + j*4+1), *(buf + j*4+2));
				index_temp->next = NULL;

				cur_index_node->next = index_temp;
				cur_index_node = index_temp;
			}
		}
		index_temp = index_root;  
		while(index_temp)
		{
            fwrite((unsigned char*)&index_temp->node, 1, 1, out);
			free_temp = index_temp;
			index_temp = index_temp->next;
			delete free_temp;
			free_temp = NULL;
		}
		index_root = NULL;
	}
	delete []buf;
	buf = NULL;

	fclose(in);
	fclose(out);

	return 0;
}


unsigned char rgb_conv::get_index(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char min_index = 0;
	unsigned char temp_r = 0;
	unsigned char temp_g = 0;
	unsigned char temp_b = 0;

	unsigned int min_dist = 1000;
	unsigned int temp_dist = 0;

	int i;
	unsigned int temp = 0;
	temp_r = (r >> 6);
	temp_g = (g >> 5);
	temp_b = (b >> 5);
	temp = min_index = (temp_r << 6) + (temp_g << 3) + temp_b + 8;
	min_dist = abs(rgb_quad[min_index].r - r) + abs(rgb_quad[min_index].g - g) + abs(rgb_quad[min_index].b - b);
	for(i = 0; i < 10; i++)
	{
		temp_dist = abs(rgb_quad[i].r - r) + abs(rgb_quad[i].g - g) + abs(rgb_quad[i].b - b);
		if(min_dist >= temp_dist)
		{
			min_dist = temp_dist;
			min_index = i;
		}
		temp_dist = abs(rgb_quad[i + 246].r - r) + abs(rgb_quad[i + 246].g - g) + abs(rgb_quad[i + 246].b - b);
		if(min_dist >= temp_dist)
		{
			min_dist = temp_dist;
			min_index = 246 + i;
		}

	}

	return min_index;
}