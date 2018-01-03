#ifndef _PAGEVARIABLE_H_
#define _PAGEVARIABLE_H_


//页面调用时，返回flash的参数，和 PAGE_CHANGE_PARA 的顺序对应




//列表的




const TCHAR *page_call_para[PAGE_MAX_NUMBER] = {
	L"page_homepage",       //首页
	L"page_title",          //歌名点歌
	L"page_singer",         //歌星点歌
	L"page_lyric",          //歌词点歌
	L"page_theme",          //主题点歌
	L"page_top_song",       //金曲排行
	L"page_new_song",       //新歌推荐
	L"page_opera",          //经典戏曲
	L"page_assist",         //辅助功能
	L"page_introduce",      //场所介绍
	L"page_selected",       //已选歌曲




	L"page_singed",         //已唱歌曲
	L"page_game",           //娱乐游戏
	L"page_movie",          //电影欣赏
	L"page_recording",      //录音管理
	L"page_video",          //视频转播
	L"page_U_disk",         //U盘播歌




	L"page_proposal",       //意见调查
	L"page_member_manager", //会员管理
	L"page_member_song",    //会员歌曲
	L"page_painting",       //绘画
	L"page_system_manager", //系统管理
	L"page_preview",        //预览视频
	L"page_singer_song",    //具体歌星的歌曲列表页面




	L"page_screen_show",    //屏切页面
	L"page_change_skin",    //换肤页面
	L"page_system_info",    //系统信息
	L"page_class",          //分类点歌
	L"page_language",       //语种点歌
	L"page_movie_song",     //影视金曲
	L"page_era_song",       //年代金曲
	L"page_number_song",    //编号点歌
	L"page_custom_singer",  //客户定义的歌星




	L"page_earth",          //导航页面
	L"page_drinks",         //酒水
	L"page_secondary_song", //歌曲二级页面
	L"page_search_song",    //搜歌页面
	L"page_write",          //手写页面
	L"page_theme_song",     //主题歌曲
	L"page_movieMeun",      //电影二级页面
	L"page_place_video",    //场所视频
	L"page_concert",        //演唱会




	L"page_ktvExplain",     //场所攻略
	L"page_room",           //包厢使用手册
	L"page_fire",           //消防图解
	L"page_guide",          //消防指南
	L"page_pk_manager",     //pk登录
	L"page_pk",             //pk邀请页面



	L"page_pk_receive",     //pk接收邀请页面



	L"page_pkjx",           //pk精选



	L"page_encode",         //二维码页面



	L"page_custom_song",    //定制歌曲页面
	L"page_karaoke_home",   //卡拉OK首页
	L"page_word_count",     //字数点歌
	L"page_jewel_box",		//百宝箱



	L"page_hdmi",     //高清专区
	L"page_kalaok_pk", //麦霸pk
	L"page_kala_share", //麦霸pk
	L"page_dekaron_maiba", //麦霸pk
	L"page_find_maiba", //麦霸pk
	L"page_help", //麦霸pk
	L"page_maiba_login", //麦霸注册、登录页面



	L"page_consumer",  //消费查询
	L"page_wechat",  //消费查询,  //
	L"page_maiba_register",  //麦霸注册
	L"page_home_song",   //首页的点播歌曲

	L"page_enterainment", //首页的娱乐互动

	L"page_place_raiders", //首页的场所攻

	L"page_aider_function", //首页的辅助功能

	L"page_fast_songs_slow_dance", //劲曲.漫舞
	L"page_music_enjoy", //音乐欣赏
	L"page_home_theme_song", //首页主题点歌
	L"page_baidu_music", //百度音乐
	L"page_qq_music", //QQ音乐
	L"page_kugou_music", //酷狗音乐
	L"page_kuwo_music", //酷我音乐
	L"page_yule_news", //娱乐新闻
	L"page_language_change", //语言切换
	L"page_video_dating",	//视频交友
	L"page_singing_contest", //演唱比赛
	L"page_sb_ranking_polite", //我要参加-上榜有礼
	L"page_sb_free_pk",		//我要参加-自由PK
	L"page_sb_challenge_pk",	//我要参加-擂台PK
	L"page_free_pk_view_list",			//查看榜单 - 自由PK
	L"page_challenge_pk_view_list", //查看榜单 - 擂台PK
	L"page_new_theme_song", //新主题点歌

	L"page_close_clear_msg",		//关房时，跳到清理界面
	L"page_voice_china",   //好声音

	L"page_yunadd_song",		//云加歌歌曲

	L"page_phone_push",			//手机推送

	L"page_phone_push_preview", //手机推送预览

	L"page_movie_detail",		//电影详情页

	L"page_voice_china_singer",  //好声音下显示歌星
	L"page_trend_list",			//潮流榜单
	L"page_challenge_star",					//挑战大咖
	L"page_across_pass",			//百秒夺奖
	L"page_video_show",			//视频秀场

	L"page_listen_knowledge_song", //听音识曲
	L"page_picture_mv",				//秀秀mv
	L"page_active_game",				//互动游戏
	L"page_entertainment_programme",	//娱乐节目
	L"page_wechat_barrage",				//微信互动-弹幕
};

//卡片的




const TCHAR *page_call_para_card[PAGE_MAX_NUMBER] = {
	L"page_homepage",		  //首页
	L"page_title_card",       //歌名点歌
	L"page_singer",           //歌星点歌
	L"page_lyric_card",       //歌词点歌
	L"page_theme_card",       //主题点歌
	L"page_top_song_card",    //金曲排行
	L"page_new_song_card",    //新歌推荐
	L"page_opera_card",       //经典戏曲
	L"page_assist",           //辅助功能
	L"page_introduce",        //场所介绍
	L"page_selected_card",    //已选歌曲




	L"page_singed_card",      //已唱歌曲
	L"page_game",             //娱乐游戏
	L"page_movie",            //电影欣赏
	L"page_recording_card",   //录音管理
	L"page_video",            //视频转播
	L"page_U_disk",           //U盘播歌




	L"page_proposal",         //意见调查
	L"page_member_manager",   //会员管理
	L"page_member_song_card", //会员歌曲
	L"page_painting",         //绘画
	L"page_system_manager",   //系统管理
	L"page_preview_card",     //预览视频
	L"page_singer_song_card", //具体歌星的歌曲列表页面




	L"page_screen_show",      //屏切页面
	L"page_change_skin",      //换肤页面
	L"page_system_info",      //系统信息
	L"page_class_card",       //分类点歌
	L"page_language_card",    //语种点歌
	L"page_movie_song_card",  //影视金曲
	L"page_era_song_card",    //年代金曲
	L"page_number_song_card", //编号点歌
	L"page_custom_singer",    //客户定义的歌星




	L"page_earth",            //导航页面
	L"page_drinks",           //酒水
	L"page_secondary_song",   //歌曲二级页面
	L"page_search_song",      //搜歌页面
	L"page_write",            //手写页面
	L"page_theme_song",       //主题歌曲
	L"page_movieMeun",        //电影二级页面
	L"page_place_video",      //场所视频
	L"page_concert",          //演唱会



	L"page_ktvExplain",       //场所攻略
	L"page_room",             //包厢使用手册
	L"page_fire",             //消防图解
	L"page_guide",            //消防指南
	L"page_pk_manager",       //pk登录
	L"page_pk",               //pk邀请页面



	L"page_pk_receive",        //pk接收邀请页面



	L"page_pkjx",              //pk精选



	L"page_encode",            //二维码页面



	L"page_custom_song",       //定制歌曲
	L"page_karaoke_home",      //卡拉OK首页
	L"page_word_count",        //字数点歌
	L"page_jewel_box",		//百宝箱



	L"page_hdmi",           //高清专区
	L"page_kalaok_pk", //麦霸pk
	L"page_kala_share", //K歌分享



	L"page_dekaron_maiba", //挑战麦霸
	L"page_find_maiba", //发现麦霸
	L"page_help", //帮助
	L"page_maiba_login", //k有登录 
	L"page_consumer", //消费查询
	L"page_wechat", //消费查询
	L"page_voice_china",  //好声音

	L"page_trend_list",		//潮流榜单93
	L"page_challenge_star",					//挑战大咖94
	L"page_cross_pass",			//百秒夺奖95
	L"page_video_show",			//视频秀场

	L"page_listen_knowledge_song", //听音识曲
	L"page_picture_mv",				//秀秀mv
	L"page_active_game",				//互动游戏
	L"page_entertainment_programme",	//娱乐节目
	L"page_wechat_barrage",				//微信互动-弹幕
};

//每个页面的名称和上面的对应,可以支持多语言，最多五种



wstring g_page_name[PAGE_MAX_NUMBER] = {
	L"首页",          //首页
	L"拼音点歌",      //歌名点歌
	L"歌星点歌",      //歌星点歌
	L"歌词点歌",      //歌词点歌
	L"主题点歌",	  //主题点歌
	L"金曲排行",      //金曲排行
	L"新歌推荐",      //新歌推荐
	L"经典戏曲",      //经典戏曲
	L"辅助功能",      //辅助功能
	L"场所介绍",      //场所介绍
	L"已选歌曲",      //已选歌曲




	L"已唱歌曲",      //已唱歌曲
	L"娱乐游戏",      //娱乐游戏
	L"电影欣赏",      //电影欣赏
	L"录音管理",      //录音管理
	L"电视转播",      //视频转播
	L"U盘播歌",       //U盘播歌




	L"投诉意见",      //意见调查
	L"会员管理",      //会员管理
	L"会员歌曲",      //会员歌曲
	L"娱乐绘画",      //绘画
	L"系统设置",      //系统管理
	L"歌曲预览",      //预览视频
	L"歌星歌曲",      //具体歌星的歌曲列表页面




	L"视频转播",      //屏切页面
	L"百变换肤",      //换肤页面
	L"系统信息",      //系统信息
	L"分类点歌",      //分类点歌
	L"语种点歌",      //语种点歌
	L"影视金曲",      //影视金曲
	L"年代金曲",      //年代金曲
	L"编号点歌",
	L"场所歌星",
	L"页面导航",
	L"酒水点单",
	L"点播歌曲",
	L"搜索歌曲",
	L"手写点歌",      //手写页面
	L"主题歌曲",
	L"电影欣赏",      //电影二级页面
	L"场所视频",      //场所视频
	L"演唱会",        //演唱会




	L"场所攻略",      //场所攻略
	L"使用手册",      //包厢使用手册
	L"消防图解",      //消防图解
	L"消费指南",      //消防指南
	L"pk登录",        //pk登录
	L"互动交友",         //pk邀请页
	L"pk接收邀请",     //pk接收邀请页面




	L"pk精选",       //pk精选



	L"移动点歌",   //移动点歌
	L"缺歌登记",   //定制歌曲
	L"卡拉OK",     //卡拉OK首页
	L"字数点歌",
	L"百宝箱",		//百宝箱



	L"高清专区",
	L"麦霸pk",
	L"K歌分享",
	L"挑战麦霸",
	L"发现麦霸",
	L"使用帮助",
	L"K友登录",
	L"消费查询",
	L"微信点歌",
	L"麦霸注册",
	L"点播歌曲",
	L"娱乐互动",
	L"场所攻略",
	L"辅助功能",
	L"劲曲·漫舞",
	L"音乐欣赏",
	L"主题点歌",
	L"百度音乐-TOP100", 
	L"QQ音乐-TOP100", 
	L"酷狗音乐-TOP100", 
	L"酷我音乐-TOP100", 
	L"娱乐新闻",
	L"语言切换",
	L"视频交友",
	L"演唱比赛",
	L"我要参加-上榜有礼", //我要参加-上榜有礼
	L"我要参加-自由PK",		//我要参加-自由PK
	L"我要参加-擂台PK",	//我要参加-擂台PK
	L"查看榜单-自由PK",			//查看榜单 - 自由PK
	L"查看榜单-擂台PK", //查看榜单 - 擂台PK
	L"主题歌曲", //新主题点歌

	L"清理中",		//关房时，跳到清理界面
	L"秀立方",  //中国好声音

	L"云加歌",
	L"手机推送",
	L"手机推送预览",
    L"电影",
	L"好声音",
	L"潮流榜单",				//93
	L"挑战大咖",			//94
	L"百秒夺奖",			//95
	L"爱秀直播",			//96
	L"听音识曲",			//97
	L"秀秀MV",				//98
	L"互动游戏",			//99
	L"娱乐节目",			//100
	L"弹幕",			//101
};

#endif