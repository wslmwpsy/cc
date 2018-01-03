#ifndef _SINGER_VARIABLE_H_
#define _SINGER_VARIABLE_H_

//#define SINGER_PAGE_SHOW_ROW_COUNT 8

#ifdef DON_GUAN_K_PLUS
static int singer_page_show_row_count = 8; 
#else
static int singer_page_show_row_count = 10; 
#endif // DON_GUAN_K_PLUS

#define SINGER_PAGE_SHOW_ROW_COUNT_MAX 10

//歌星显示的页数
#define SINGER_SCREEN_SHOW_PAGE_COUNT 3

//符合条件的有多少页数据
enum SINGER_PAGE_FLAG
{
	SINGER_NO_PAGE=0,           //没有查询到符合条件的数据
	SINGER_ONE_PAGE,          //只有一页数据
	SINGER_TWO_PAGE,          //两页数据
	SINGER_THREE_PAGE,       //三页数据
};

//歌星的归属地
enum SINGER_REGION
{
	MAINLAND_MALE=1,  //大陆男歌星
	MAINLAND_FEMALE,//大陆女歌星
	HK_TAIWAN_MALE, //港台男歌星
	HK_TAIWAN_FEMALE,//港台女歌星
	CONCERT_PORTFOLIO,//演唱组合
	FOREIGN_SINGER,  //外国歌手
	POPULAR_SINGER, //热门歌手
	ALL_SINGER,     //全部歌手
	// -- add by cai : 增加华人、欧美、韩国、日本、其他、全部(华人、欧美、韩国、日本、其他) [9/24/2014 syrusn]
	CHINESE,		//华人
	EUROPE_AMERICA, //欧美
	KOREA,			//韩国
	JAPAN,			//日本
	OTHER,			//其他
};

#endif