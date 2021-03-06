/************************************************************************/
/*字数:134*/
/************************************************************************/
#ifndef _VIDEO_FONT_CN_
#define _VIDEO_FONT_CN_

#define VIDEO_FONT_CN_CHARS 147
#define VIDEO_FONT_CN_WIDTH	16
#define VIDEO_FONT_CN_HEIGHT	16
#define VIDEO_FONT_CN_SIZE		((VIDEO_FONT_CN_CHARS+1) * VIDEO_FONT_CN_HEIGHT*VIDEO_FONT_CN_WIDTH/8)

static unsigned char gbindex[VIDEO_FONT_CN_CHARS+1][2] = {
			{0xff,0xff},
/*1:。*/	{0xa1,0xa3},
/*2:→*/	{0xa1,0xfa},
/*3:←*/	{0xa1,0xfb},
/*4:↑*/	{0xa1,0xfc},
/*5:↓*/	{0xa1,0xfd},
/*6:；*/	{0xa3,0xbb},
/*7:按*/	{0xb0,0xb4},
/*8:败*/	{0xb0,0xdc},
/*9:保*/	{0xb1,0xa3},
/*136:备*/  {0xb1,0xb8},
/*10:本*/	{0xb1,0xbe},
/*11:变*/	{0xb1,0xe4},
/*12:并*/	{0xb2,0xa2},
/*139:参*/  {0xb2,0xce},
/*13:车*/	{0xb3,0xb5},
/*14:称*/	{0xb3,0xc6},
/*15:成*/	{0xb3,0xc9},
/*16:出*/	{0xb3,0xf6},
/*145:此*/  {0xb4,0xcb},
/*17:从*/	{0xb4,0xd3},
/*18:存*/	{0xb4,0xe6},
/*19:当*/	{0xb5,0xb1},
/*20:到*/	{0xb5,0xbd},
/*21:的*/	{0xb5,0xc4},
/*22:地*/	{0xb5,0xd8},
/*23:动*/	{0xb6,0xaf},
/*24:对*/	{0xb6,0xd4},
/*25:二*/	{0xb6,0xfe},
/*26:返*/	{0xb7,0xb5},
/*27:方*/	{0xb7,0xbd},
/*28:分*/	{0xb7,0xd6},
/*29:否*/	{0xb7,0xf1},
/*30:服*/	{0xb7,0xfe},
/*31:改*/	{0xb8,0xc4},
/*32:告*/	{0xb8,0xe6},
/*33:更*/	{0xb8,0xfc},
/*34:功*/	{0xb9,0xa6},
/*146:关*/  {0xb9,0xd8},
/*35:核*/	{0xba,0xcb},
/*36:和*/	{0xba,0xcd},
/*143:忽*/  {0xba,0xf6},
/*37:缓*/	{0xbb,0xba},
/*38:换*/	{0xbb,0xbb},
/*39:回*/	{0xbb,0xd8},
/*40:或*/	{0xbb,0xf2},
/*41:基*/	{0xbb,0xf9},
/*147:机*/  {0xbb,0xfa},
/*42:即*/	{0xbc,0xb4},
/*43:级*/	{0xbc,0xb6},
/*44:既*/	{0xbc,0xc8},
/*45:间*/	{0xbc,0xe4},
/*46:键*/	{0xbc,0xfc},
/*47:件*/	{0xbc,0xfe},
/*48:接*/	{0xbd,0xd3},
/*49:界*/	{0xbd,0xe7},
/*50:进*/	{0xbd,0xf8},
/*51:警*/	{0xbe,0xaf},
/*52:径*/	{0xbe,0xb6},
/*53:据*/	{0xbe,0xdd},
/*54:卡*/	{0xbf,0xa8},
/*55:可*/	{0xbf,0xc9},
/*56:控*/	{0xbf,0xd8},
/*137:类*/  {0xc0,0xe0},
/*57:量*/	{0xc1,0xbf},
/*58:令*/	{0xc1,0xee},
/*59:龙*/	{0xc1,0xfa},
/*60:路*/	{0xc2,0xb7},
/*144:略*/  {0xc2,0xd4},
/*61:络*/	{0xc2,0xe7},
/*62:面*/	{0xc3,0xe6},
/*63:秒*/	{0xc3,0xeb},
/*64:名*/	{0xc3,0xfb},
/*65:命*/	{0xc3,0xfc},
/*66:内*/	{0xc4,0xda},
/*67:年*/	{0xc4,0xea},
/*68:盘*/	{0xc5,0xcc},
/*69:配*/	{0xc5,0xe4},
/*70:期*/	{0xc6,0xda},
/*71:启*/	{0xc6,0xf4},
/*140:器*/  {0xc6,0xf7},
/*72:前*/	{0xc7,0xb0},
/*73:切*/	{0xc7,0xd0},
/*74:确*/	{0xc8,0xb7},
/*75:认*/	{0xc8,0xcf},
/*76:日*/	{0xc8,0xd5},
/*77:容*/	{0xc8,0xdd},
/*78:入*/	{0xc8,0xeb},
/*79:若*/	{0xc8,0xf4},
/*80:色*/	{0xc9,0xab},
/*81:上*/	{0xc9,0xcf},
/*82:设*/	{0xc9,0xe8},
/*83:失*/	{0xca,0xa7},
/*84:时*/	{0xca,0xb1},
/*85:使*/	{0xca,0xb9},
/*86:示*/	{0xca,0xbe},
/*87:是*/	{0xca,0xc7},
/*88:输*/	{0xca,0xe4},
/*89:数*/	{0xca,0xfd},
/*134:所*/  {0xcb,0xf9},
/*90:台*/	{0xcc,0xa8},
/*91:提*/	{0xcc,0xe1},
/*92:题*/	{0xcc,0xe2},
/*93:统*/	{0xcd,0xb3},
/*94:退*/	{0xcd,0xcb},
/*95:网*/	{0xcd,0xf8},
/*96:为*/	{0xce,0xaa},
/*97:文*/	{0xce,0xc4},
/*98:务*/	{0xce,0xf1},
/*99:息*/	{0xcf,0xa2},
/*100:系*/	{0xcf,0xb5},
/*101:下*/	{0xcf,0xc2},
/*102:项*/	{0xcf,0xee},
/*103:向*/	{0xcf,0xf2},
/*104:小*/	{0xd0,0xa1},
/*105:芯*/	{0xd0,0xbe},
/*106:新*/	{0xd0,0xc2},
/*107:信*/	{0xd0,0xc5},
/*138:型*/  {0xd0,0xcd},
/*108:行*/	{0xd0,0xd0},
/*109:修*/	{0xd0,0xde},
/*110:需*/	{0xd0,0xe8},
/*111:选*/	{0xd1,0xa1},
/*112:颜*/	{0xd1,0xd5},
/*113:要*/	{0xd2,0xaa},
/*114:页*/	{0xd2,0xb3},
/*115:一*/	{0xd2,0xbb},
/*116:以*/	{0xd2,0xd4},
/*117:意*/	{0xd2,0xe2},
/*118:用*/	{0xd3,0xc3},
/*119:月*/	{0xd4,0xc2},
/*142:载*/  {0xd4,0xd8},
/*135:在*/  {0xd4,0xda},
/*120:择*/	{0xd4,0xf1},
/*121:则*/	{0xd4,0xf2},
/*122:直*/	{0xd6,0xb1},
/*123:执*/	{0xd6,0xb4},
/*124:址*/	{0xd6,0xb7},
/*125:指*/	{0xd6,0xb8},
/*126:至*/	{0xd6,0xc1},
/*127:置*/	{0xd6,0xc3},
/*128:制*/	{0xd6,0xc6},
/*129:钟*/	{0xd6,0xd3},
/*130:重*/	{0xd6,0xd8},
/*131:主*/	{0xd6,0xf7},
/*132:注*/	{0xd7,0xa2},
/*141:装*/  {0xd7,0xb0},
/*133:字*/	{0xd7,0xd6}
#if 0
/*134:所*/  {0xcb,0xf9},
/*135:在*/  {0xd4,0xda}
#endif
};
static unsigned char video_fontcndata[VIDEO_FONT_CN_SIZE] = {
	/* 0 0x00 NULL 字库中没有的汉字由此符号代替*/
	0x00,0x00,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x7f,0xfe,
	0x00,0x00,

	/* 1 0x01 "。" 机内码:0xa1a3 */
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x3c,0x00,
	0x66,0x00,
	0x66,0x00,
	0x66,0x00,
	0x3c,0x00,
	0x00,0x00,

	/* 2 0x02 "→" 机内码:0xa1fa */
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x40,
	0x00,0x30,
	0x00,0x3c,
	0x3f,0xfe,
	0x00,0x3c,
	0x00,0x30,
	0x00,0x40,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,

	/* 3 0x03 "←" 机内码:0xa1fb */
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x01,0x00,
	0x06,0x00,
	0x1e,0x00,
	0x3f,0xfe,
	0x1e,0x00,
	0x06,0x00,
	0x01,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,

	/* 4 0x04 "↑" 机内码:0xa1fc */
	0x00,0x00,
	0x00,0x80,
	0x01,0xc0,
	0x01,0xc0,
	0x03,0xe0,
	0x03,0xe0,
	0x04,0x90,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x00,

	/* 5 0x05 "↓" 机内码:0xa1fd */
	0x00,0x00,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x00,0x80,
	0x04,0x90,
	0x03,0xe0,
	0x03,0xe0,
	0x01,0xc0,
	0x01,0xc0,
	0x00,0x80,
	0x00,0x00,

	/* 6 0x06 "；" 机内码:0xa3bb */
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x0c,0x00,
	0x1e,0x00,
	0x1e,0x00,
	0x0c,0x00,
	0x00,0x00,
	0x0c,0x00,
	0x1e,0x00,
	0x1e,0x00,
	0x0c,0x00,
	0x0c,0x00,
	0x18,0x00,

	/* 7 0x07 "按" 机内码:0xb0b4 */
	0x10,0x40,
	0x10,0x20,
	0x10,0x00,
	0x13,0xfe,
	0xfa,0x02,
	0x14,0x44,
	0x10,0x40,
	0x3f,0xfe,
	0xd0,0x88,
	0x10,0x88,
	0x11,0x08,
	0x10,0x90,
	0x10,0x60,
	0x10,0x50,
	0x50,0x8c,
	0x23,0x04,

	/* 8 0x08 "败" 机内码:0xb0dc */
	0x04,0x40,
	0x7e,0x40,
	0x44,0x44,
	0x54,0x7e,
	0x54,0x88,
	0x55,0x08,
	0x54,0x48,
	0x54,0x48,
	0x54,0x48,
	0x54,0x50,
	0x54,0x50,
	0x10,0x20,
	0x28,0x50,
	0x24,0x8e,
	0x45,0x04,
	0x82,0x00,

	/* 9 0x09 "保" 机内码:0xb1a3 */
	0x08,0x08,
	0x0b,0xfc,
	0x0a,0x08,
	0x12,0x08,
	0x12,0x08,
	0x33,0xf8,
	0x32,0x40,
	0x50,0x44,
	0x9f,0xfe,
	0x10,0x40,
	0x10,0xe0,
	0x11,0x50,
	0x12,0x48,
	0x14,0x4e,
	0x18,0x44,
	0x10,0x40,
	
	/* 136 0x09 "备" 机内码:0xb1b8 */
    0x04,0x00,
    0x07,0xF0,
    0x08,0x20,
    0x14,0x40,
    0x23,0x80,
    0x02,0x80,
    0x0C,0x60,
    0x30,0x1E,
    0xDF,0xF4,
    0x11,0x10,
    0x11,0x10,
    0x1F,0xF0,
    0x11,0x10,
    0x11,0x10,
    0x1F,0xF0,
    0x10,0x10,
    
	/* 10 0x0a "本" 机内码:0xb1be */
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x08,
	0x7f,0xfc,
	0x05,0x40,
	0x05,0x40,
	0x05,0x40,
	0x09,0x20,
	0x09,0x20,
	0x11,0x10,
	0x2f,0xee,
	0xc1,0x04,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,

	/* 11 0x0b "变" 机内码:0xb1e4 */
	0x02,0x00,
	0x01,0x08,
	0x7f,0xfc,
	0x04,0x40,
	0x14,0x50,
	0x14,0x48,
	0x24,0x4c,
	0x44,0x44,
	0x1f,0xf0,
	0x08,0x20,
	0x04,0x40,
	0x02,0x80,
	0x01,0x00,
	0x02,0xc0,
	0x0c,0x3c,
	0x30,0x08,

	/* 12 0x0c "并" 机内码:0xb2a2 */
	0x10,0x10,
	0x0c,0x30,
	0x04,0x40,
	0x3f,0xfc,
	0x04,0x20,
	0x04,0x20,
	0x04,0x20,
	0x04,0x24,
	0xff,0xfe,
	0x04,0x20,
	0x04,0x20,
	0x04,0x20,
	0x08,0x20,
	0x08,0x20,
	0x10,0x20,
	0x20,0x20,

	/* 139 0x0c "参" 机内码:0xb2ce */
    0x02 ,0x00 ,
    0x02 ,0x40 ,
    0x04 ,0x20 ,
    0x1F ,0xF0, 
    0x02 ,0x04 ,
    0xFF ,0xFE ,
    0x04 ,0x40 ,
    0x08 ,0xA0 ,
    0x13 ,0x10 ,
    0x2C ,0x4E ,
    0xC1 ,0x84 ,
    0x0E ,0x10 ,
    0x00 ,0x60 ,
    0x01 ,0x80 ,
    0x0E ,0x00 ,
    0x70 ,0x00 ,

    
	/* 13 0x0d "车" 机内码:0xb3b5 */
	0x02,0x00,
	0x02,0x08,
	0x7f,0xfc,
	0x04,0x00,
	0x09,0x00,
	0x11,0x00,
	0x21,0x20,
	0x3f,0xf0,
	0x01,0x00,
	0x01,0x04,
	0xff,0xfe,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,

	/* 14 0x0e "称" 机内码:0xb3c6 */
	0x04,0x40,
	0x0e,0x40,
	0x78,0x80,
	0x08,0x80,
	0x09,0xfe,
	0xfe,0x04,
	0x08,0x28,
	0x1c,0x20,
	0x1a,0xa8,
	0x28,0xa4,
	0x29,0x26,
	0x49,0x22,
	0x8a,0x20,
	0x08,0x20,
	0x08,0xa0,
	0x08,0x40,

	/* 15 0x0f "成" 机内码:0xb3c9 */
	0x00,0x80,
	0x00,0xa0,
	0x00,0x90,
	0x3f,0xfc,
	0x20,0x80,
	0x20,0x80,
	0x20,0x84,
	0x3e,0x44,
	0x22,0x48,
	0x22,0x48,
	0x22,0x30,
	0x2a,0x20,
	0x24,0x62,
	0x40,0x92,
	0x81,0x0a,
	0x00,0x06,

	/* 16 0x10 "出" 机内码:0xb3f6 */
	0x01,0x00,
	0x01,0x00,
	0x21,0x08,
	0x21,0x08,
	0x21,0x08,
	0x21,0x08,
	0x3f,0xf8,
	0x21,0x08,
	0x01,0x00,
	0x41,0x04,
	0x41,0x04,
	0x41,0x04,
	0x41,0x04,
	0x41,0x04,
	0x7f,0xfc,
	0x40,0x04,

	/* 145 0x10 "此" 机内码:0xb4cb */
    0x04 ,0x40 ,
    0x04 ,0x40 ,
    0x04 ,0x40 ,
    0x24 ,0x44 ,
    0x24 ,0x4C ,
    0x24 ,0x50 ,
    0x27 ,0x60 ,
    0x24 ,0x40 ,
    0x24 ,0x40 ,
    0x24 ,0x40 ,
    0x24 ,0x40 ,
    0x24 ,0x40 ,
    0x27 ,0x42 ,
    0xF8 ,0x42 ,
    0x40 ,0x3E ,
    0x00 ,0x00 ,
    
	/* 17 0x11 "从" 机内码:0xb4d3 */
	0x00,0x00,
	0x08,0x20,
	0x08,0x20,
	0x08,0x20,
	0x08,0x20,
	0x08,0x20,
	0x08,0x20,
	0x08,0x50,
	0x08,0x50,
	0x08,0x50,
	0x14,0x50,
	0x12,0x88,
	0x21,0x88,
	0x21,0x0c,
	0x42,0x06,
	0x84,0x04,

	/* 18 0x12 "存" 机内码:0xb4e6 */
	0x02,0x00,
	0x02,0x04,
	0xff,0xfe,
	0x04,0x00,
	0x08,0x00,
	0x0b,0xf8,
	0x10,0x10,
	0x10,0x20,
	0x30,0x44,
	0x5f,0xfe,
	0x90,0x40,
	0x10,0x40,
	0x10,0x40,
	0x10,0x40,
	0x11,0x40,
	0x10,0x80,

	/* 19 0x13 "当" 机内码:0xb5b1 */
	0x01,0x00,
	0x21,0x08,
	0x19,0x18,
	0x09,0x20,
	0x01,0x00,
	0x01,0x08,
	0x7f,0xfc,
	0x00,0x08,
	0x00,0x08,
	0x00,0x08,
	0x3f,0xf8,
	0x00,0x08,
	0x00,0x08,
	0x00,0x08,
	0x7f,0xf8,
	0x00,0x08,

	/* 20 0x14 "到" 机内码:0xb5bd */
	0x01,0x04,
	0x7f,0x84,
	0x08,0x04,
	0x10,0x24,
	0x22,0x24,
	0x41,0x24,
	0x7f,0xa4,
	0x08,0xa4,
	0x0a,0x24,
	0x7f,0x24,
	0x08,0x24,
	0x08,0x24,
	0x08,0x04,
	0x0f,0x84,
	0xf8,0x14,
	0x00,0x08,

	/* 21 0x15 "的" 机内码:0xb5c4 */
	0x10,0x40,
	0x10,0x40,
	0x22,0x44,
	0x7f,0x7e,
	0x42,0x84,
	0x43,0x04,
	0x42,0x04,
	0x42,0x84,
	0x7e,0x64,
	0x42,0x24,
	0x42,0x04,
	0x42,0x04,
	0x42,0x04,
	0x7e,0x04,
	0x42,0x28,
	0x00,0x10,

	/* 22 0x16 "地" 机内码:0xb5d8 */
	0x00,0x40,
	0x20,0x40,
	0x22,0x40,
	0x22,0x40,
	0x22,0x48,
	0x22,0x7c,
	0xfb,0xc8,
	0x26,0x48,
	0x22,0x48,
	0x22,0x48,
	0x22,0x68,
	0x22,0x50,
	0x3a,0x42,
	0xe2,0x02,
	0x41,0xfe,
	0x00,0x00,

	/* 23 0x17 "动" 机内码:0xb6af */
	0x00,0x40,
	0x08,0x40,
	0x7c,0x40,
	0x00,0x44,
	0x05,0xfe,
	0xfe,0x44,
	0x10,0x44,
	0x10,0x44,
	0x20,0x44,
	0x24,0x44,
	0x42,0x84,
	0xfe,0x84,
	0x41,0x04,
	0x01,0x04,
	0x02,0x28,
	0x04,0x10,

	/* 24 0x18 "对" 机内码:0xb6d4 */
	0x00,0x10,
	0x00,0x10,
	0x00,0x10,
	0xfc,0x14,
	0x07,0xfe,
	0x04,0x10,
	0x48,0x10,
	0x29,0x10,
	0x10,0x90,
	0x10,0x90,
	0x28,0x10,
	0x24,0x10,
	0x44,0x10,
	0x80,0x10,
	0x00,0x50,
	0x00,0x20,

	/* 25 0x19 "二" 机内码:0xb6fe */
	0x00,0x00,
	0x00,0x00,
	0x00,0x10,
	0x3f,0xf8,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x04,
	0xff,0xfe,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,

	/* 26 0x1a "返" 机内码:0xb7b5 */
	0x00,0x08,
	0x40,0x1c,
	0x33,0xe0,
	0x12,0x00,
	0x02,0x00,
	0x02,0xf8,
	0xf2,0x08,
	0x12,0x90,
	0x12,0x50,
	0x12,0x20,
	0x12,0x50,
	0x14,0x8c,
	0x15,0x04,
	0x28,0x00,
	0x44,0x06,
	0x03,0xfc,

	/* 27 0x1b "方" 机内码:0xb7bd */
	0x04,0x00,
	0x03,0x00,
	0x01,0x00,
	0x00,0x04,
	0xff,0xfe,
	0x04,0x00,
	0x04,0x10,
	0x07,0xf8,
	0x04,0x10,
	0x04,0x10,
	0x04,0x10,
	0x08,0x10,
	0x08,0x10,
	0x10,0x10,
	0x20,0xa0,
	0x40,0x40,

	/* 28 0x1c "分" 机内码:0xb7d6 */
	0x00,0x80,
	0x04,0x80,
	0x04,0x40,
	0x08,0x40,
	0x08,0x20,
	0x10,0x10,
	0x20,0x08,
	0x4f,0xee,
	0x84,0x24,
	0x04,0x20,
	0x04,0x20,
	0x04,0x20,
	0x04,0x20,
	0x08,0x20,
	0x11,0x40,
	0x20,0x80,

	/* 29 0x1d "否" 机内码:0xb7f1 */
	0x00,0x04,
	0xff,0xfe,
	0x00,0x80,
	0x01,0x00,
	0x03,0x00,
	0x05,0x60,
	0x09,0x18,
	0x31,0x06,
	0xc1,0x12,
	0x1f,0xf8,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,

	/* 30 0x1e "服" 机内码:0xb7fe */
	0x02,0x08,
	0x3f,0xfc,
	0x22,0x88,
	0x22,0x88,
	0x22,0x88,
	0x3e,0x98,
	0x22,0x80,
	0x22,0xfc,
	0x22,0xa4,
	0x3e,0xa4,
	0x22,0xa8,
	0x22,0x90,
	0x22,0xa8,
	0x22,0xa8,
	0x4a,0xc6,
	0x84,0x84,

	/* 31 0x1f "改" 机内码:0xb8c4 */
	0x00,0x80,
	0x04,0x80,
	0xfe,0x80,
	0x04,0x84,
	0x04,0xfe,
	0x05,0x08,
	0x7e,0x88,
	0x44,0x88,
	0x40,0x88,
	0x40,0x50,
	0x40,0x50,
	0x40,0x20,
	0x4c,0x50,
	0x70,0x88,
	0x41,0x0e,
	0x06,0x04,

	/* 32 0x20 "告" 机内码:0xb8e6 */
	0x01,0x00,
	0x11,0x00,
	0x11,0x10,
	0x1f,0xf8,
	0x11,0x00,
	0x21,0x00,
	0x01,0x04,
	0xff,0xfe,
	0x00,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,

	/* 33 0x21 "更" 机内码:0xb8fc */
	0x00,0x04,
	0xff,0xfe,
	0x01,0x08,
	0x3f,0xfc,
	0x21,0x08,
	0x21,0x08,
	0x3f,0xf8,
	0x21,0x08,
	0x21,0x08,
	0x3f,0xf8,
	0x29,0x08,
	0x05,0x00,
	0x02,0x00,
	0x05,0x80,
	0x18,0x70,
	0xe0,0x0e,

	/* 34 0x22 "功" 机内码:0xb9a6 */
	0x00,0x80,
	0x00,0x80,
	0x08,0x80,
	0xfc,0x80,
	0x10,0x84,
	0x17,0xfe,
	0x10,0x84,
	0x10,0x84,
	0x10,0x84,
	0x10,0x84,
	0x1d,0x04,
	0xf1,0x04,
	0x41,0x04,
	0x02,0x44,
	0x04,0x28,
	0x08,0x10,

	/* 146 0x23 "关" 机内码:0xb9d8 */
    0x10 ,0x10 ,
    0x08 ,0x18 ,
    0x04 ,0x20 ,
    0x04 ,0x48 ,
    0x7F ,0xFC ,
    0x01 ,0x00 ,
    0x01 ,0x00 ,
    0x01 ,0x04 ,
    0xFF ,0xFE ,
    0x01 ,0x00 ,
    0x02 ,0x80 ,
    0x02 ,0x80 ,
    0x04 ,0x40 ,
    0x08 ,0x30 ,
    0x30 ,0x0E ,
    0xC0 ,0x04 ,


	/* 35 0x23 "核" 机内码:0xbacb */
	0x10,0x80,
	0x10,0x40,
	0x10,0x44,
	0x13,0xfe,
	0xfc,0x40,
	0x10,0x80,
	0x39,0x08,
	0x37,0xf8,
	0x55,0x10,
	0x50,0x24,
	0x90,0x4c,
	0x11,0x90,
	0x16,0x20,
	0x10,0x50,
	0x11,0x8c,
	0x16,0x04,

	/* 36 0x24 "和" 机内码:0xbacd */
	0x02,0x00,
	0x07,0x00,
	0x78,0x00,
	0x08,0x04,
	0x0a,0xfe,
	0xff,0x84,
	0x08,0x84,
	0x18,0x84,
	0x1c,0x84,
	0x2a,0x84,
	0x2a,0x84,
	0x48,0x84,
	0x88,0xfc,
	0x08,0x84,
	0x08,0x00,
	0x08,0x00,

	/* 143 0x24 "忽" 机内码:0xbaf6 */
    0x08 ,0x00 ,
    0x08 ,0x08 ,
    0x0F ,0xFC ,
    0x12 ,0x48 ,
    0x12 ,0x48 ,
    0x22 ,0x48 ,
    0x44 ,0x88 ,
    0x04 ,0x88 ,
    0x09 ,0x28 ,
    0x12 ,0x10 ,
    0x02 ,0x00 ,
    0x29 ,0x88 ,
    0x28 ,0xA4 ,
    0x48 ,0x24 ,
    0x07 ,0xE0 ,
    0x00 ,0x00 ,

	/* 37 0x25 "缓" 机内码:0xbbba */
	0x10,0x0c,
	0x13,0xf0,
	0x22,0x48,
	0x21,0x50,
	0x44,0x20,
	0xfb,0xfc,
	0x10,0x40,
	0x27,0xfe,
	0x40,0x80,
	0xfc,0xfc,
	0x01,0x88,
	0x01,0x50,
	0x1a,0x20,
	0xe4,0x50,
	0x49,0x8e,
	0x02,0x04,

	/* 38 0x26 "换" 机内码:0xbbbb */
	0x10,0x80,
	0x10,0x80,
	0x11,0xf0,
	0x12,0x20,
	0xfc,0x48,
	0x13,0xfc,
	0x12,0x48,
	0x1e,0x48,
	0x32,0x48,
	0xd2,0x48,
	0x1f,0xfe,
	0x10,0x40,
	0x10,0xa0,
	0x11,0x10,
	0x52,0x0e,
	0x2c,0x04,

	/* 39 0x27 "回" 机内码:0xbbd8 */
	0x00,0x00,
	0x00,0x04,
	0x7f,0xfe,
	0x40,0x04,
	0x40,0x44,
	0x47,0xe4,
	0x44,0x44,
	0x44,0x44,
	0x44,0x44,
	0x44,0x44,
	0x47,0xc4,
	0x44,0x44,
	0x40,0x04,
	0x7f,0xfc,
	0x40,0x04,
	0x00,0x00,

	/* 40 0x28 "或" 机内码:0xbbf2 */
	0x00,0x50,
	0x00,0x48,
	0x00,0x40,
	0xff,0xfe,
	0x00,0x40,
	0x02,0x40,
	0x3f,0x48,
	0x22,0x48,
	0x22,0x48,
	0x22,0x50,
	0x3e,0x50,
	0x20,0x20,
	0x07,0x22,
	0x78,0x52,
	0x00,0x8a,
	0x03,0x04,

	/* 41 0x29 "基" 机内码:0xbbf9 */
	0x08,0x20,
	0x08,0x28,
	0x7f,0xfc,
	0x08,0x20,
	0x0f,0xe0,
	0x08,0x20,
	0x0f,0xe0,
	0x08,0x24,
	0xff,0xfe,
	0x04,0x40,
	0x09,0x30,
	0x31,0x4e,
	0xcf,0xe4,
	0x01,0x00,
	0x01,0x10,
	0x3f,0xf8,

	/* 147 0x29 "机" 机内码:0xbbfa */
    0x10 ,0x00 ,
    0x10 ,0x10 ,
    0x11 ,0xF8 ,
    0x11 ,0x10 ,
    0xFD ,0x10 ,
    0x11 ,0x10 ,
    0x31 ,0x10 ,
    0x39 ,0x10 ,
    0x55 ,0x10 ,
    0x51 ,0x10 ,
    0x91 ,0x10 ,
    0x11 ,0x10 ,
    0x11 ,0x12 ,
    0x12 ,0x12 ,
    0x14 ,0x0E ,
    0x18 ,0x00 ,


	/* 42 0x2a "即" 机内码:0xbcb4 */
	0x00,0x04,
	0x7e,0xfe,
	0x42,0x84,
	0x42,0x84,
	0x7e,0x84,
	0x42,0x84,
	0x42,0x84,
	0x7e,0x84,
	0x40,0x84,
	0x44,0xa4,
	0x44,0x94,
	0x4a,0x88,
	0x72,0x80,
	0x40,0x80,
	0x00,0x80,
	0x00,0x80,

	/* 43 0x2b "级" 机内码:0xbcb6 */
	0x10,0x08,
	0x17,0xfc,
	0x21,0x08,
	0x21,0x08,
	0x49,0x10,
	0xf9,0x10,
	0x11,0x3c,
	0x21,0x84,
	0x41,0x88,
	0xf9,0x48,
	0x02,0x50,
	0x02,0x20,
	0x1a,0x50,
	0xe4,0x88,
	0x49,0x0e,
	0x02,0x04,

	/* 44 0x2c "既" 机内码:0xbcc8 */
	0x00,0x08,
	0x7d,0xfc,
	0x44,0x20,
	0x44,0x20,
	0x7d,0x20,
	0x45,0x20,
	0x45,0x24,
	0x45,0xfe,
	0x7c,0x20,
	0x40,0x20,
	0x48,0x50,
	0x44,0x50,
	0x5c,0x92,
	0x60,0x92,
	0x41,0x0e,
	0x06,0x00,

	/* 45 0x2d "间" 机内码:0xbce4 */
	0x20,0x04,
	0x1b,0xfe,
	0x08,0x04,
	0x40,0x24,
	0x4f,0xf4,
	0x48,0x24,
	0x48,0x24,
	0x48,0x24,
	0x4f,0xe4,
	0x48,0x24,
	0x48,0x24,
	0x48,0x24,
	0x4f,0xe4,
	0x48,0x24,
	0x40,0x14,
	0x40,0x08,

	/* 46 0x2e "键" 机内码:0xbcfc */
	0x20,0x10,
	0x27,0x10,
	0x39,0x7c,
	0x41,0x14,
	0x82,0xfe,
	0x7a,0x14,
	0x24,0x7c,
	0x27,0x10,
	0xf9,0x7c,
	0x21,0x10,
	0x25,0x14,
	0x22,0xfe,
	0x2a,0x10,
	0x35,0x10,
	0x28,0x96,
	0x00,0x7c,

	/* 47 0x2f "件" 机内码:0xbcfe */
	0x10,0x40,
	0x10,0x40,
	0x12,0x40,
	0x22,0x48,
	0x23,0xfc,
	0x64,0x40,
	0xa4,0x40,
	0x28,0x40,
	0x20,0x44,
	0x3f,0xfe,
	0x20,0x40,
	0x20,0x40,
	0x20,0x40,
	0x20,0x40,
	0x20,0x40,
	0x20,0x40,

	/* 48 0x30 "接" 机内码:0xbdd3 */
	0x10,0x80,
	0x10,0x48,
	0x17,0xfc,
	0x10,0x00,
	0xfd,0x10,
	0x10,0xa0,
	0x17,0xfc,
	0x18,0x80,
	0x30,0x84,
	0xdf,0xfe,
	0x10,0x90,
	0x11,0x10,
	0x10,0xa0,
	0x10,0x60,
	0x50,0x98,
	0x23,0x08,

	/* 49 0x31 "界" 机内码:0xbde7 */
	0x00,0x10,
	0x1f,0xf8,
	0x11,0x10,
	0x11,0x10,
	0x1f,0xf0,
	0x11,0x10,
	0x11,0x10,
	0x1f,0xf0,
	0x02,0x80,
	0x04,0x60,
	0x0c,0x50,
	0x34,0x4e,
	0xc4,0x44,
	0x04,0x40,
	0x08,0x40,
	0x10,0x40,

	/* 50 0x32 "进" 机内码:0xbdf8 */
	0x02,0x20,
	0x42,0x20,
	0x22,0x28,
	0x2f,0xfc,
	0x02,0x20,
	0x02,0x20,
	0xe2,0x20,
	0x22,0x28,
	0x2f,0xfc,
	0x22,0x20,
	0x22,0x20,
	0x22,0x20,
	0x24,0x20,
	0x50,0x26,
	0x8f,0xfc,
	0x00,0x00,

	/* 51 0x33 "警" 机内码:0xbeaf */
	0x14,0x40,
	0x7f,0x7c,
	0x10,0xc8,
	0x3f,0x28,
	0x55,0x10,
	0x1d,0x6e,
	0x03,0x04,
	0xff,0xfe,
	0x00,0x00,
	0x1f,0xf0,
	0x00,0x00,
	0x1f,0xf0,
	0x00,0x00,
	0x1f,0xf0,
	0x10,0x10,
	0x1f,0xf0,

	/* 52 0x34 "径" 机内码:0xbeb6 */
	0x08,0x00,
	0x0b,0xf8,
	0x10,0x10,
	0x20,0x20,
	0x40,0x60,
	0x08,0x98,
	0x11,0x0e,
	0x36,0x02,
	0x50,0x00,
	0x93,0xf8,
	0x10,0x40,
	0x10,0x40,
	0x10,0x40,
	0x10,0x44,
	0x17,0xfe,
	0x10,0x00,

	/* 53 0x35 "据" 机内码:0xbedd */
	0x10,0x04,
	0x13,0xfe,
	0x12,0x04,
	0x12,0x04,
	0xff,0xfc,
	0x12,0x20,
	0x16,0x24,
	0x1b,0xfe,
	0x32,0x20,
	0xd2,0x24,
	0x13,0xfe,
	0x15,0x04,
	0x15,0x04,
	0x15,0x04,
	0x59,0xfc,
	0x21,0x04,

	/* 54 0x36 "卡" 机内码:0xbfa8 */
	0x02,0x00,
	0x02,0x20,
	0x03,0xf0,
	0x02,0x00,
	0x02,0x00,
	0x02,0x04,
	0xff,0xfe,
	0x02,0x00,
	0x02,0x00,
	0x02,0x80,
	0x02,0x60,
	0x02,0x30,
	0x02,0x10,
	0x02,0x00,
	0x02,0x00,
	0x02,0x00,

	/* 55 0x37 "可" 机内码:0xbfc9 */
	0x00,0x04,
	0xff,0xfe,
	0x00,0x10,
	0x00,0x90,
	0x1f,0xd0,
	0x10,0x90,
	0x10,0x90,
	0x10,0x90,
	0x10,0x90,
	0x10,0x90,
	0x1f,0x90,
	0x10,0x90,
	0x00,0x10,
	0x00,0x10,
	0x00,0x50,
	0x00,0x20,

	/* 56 0x38 "控" 机内码:0xbfd8 */
	0x10,0x40,
	0x10,0x20,
	0x13,0xfe,
	0x12,0x02,
	0xfc,0x54,
	0x10,0x88,
	0x15,0x04,
	0x18,0x00,
	0x30,0x08,
	0xd3,0xfc,
	0x10,0x20,
	0x10,0x20,
	0x10,0x20,
	0x10,0x24,
	0x57,0xfe,
	0x20,0x00,
	
	/* 137 0x38 "类" 机内码:0xc0e0 */
    0x01,0x00,
    0x11,0x10,
    0x09,0x20,
    0x01,0x08,
    0x7F,0xFC,
    0x01,0x00,
    0x05,0x40,
    0x09,0x30,
    0x11,0x10,
    0x01,0x04,
    0xFF,0xFE,
    0x02,0x80,
    0x04,0x40,
    0x08,0x20,
    0x10,0x1C,
    0x60,0x08, 
    
	/* 57 0x39 "量" 机内码:0xc1bf */
	0x00,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x14,
	0xff,0xfe,
	0x00,0x00,
	0x1f,0xf0,
	0x11,0x10,
	0x1f,0xf0,
	0x11,0x10,
	0x1f,0xf0,
	0x01,0x00,
	0x1f,0xf0,
	0x01,0x00,
	0x7f,0xfc,

	/* 58 0x3a "令" 机内码:0xc1ee */
	0x01,0x00,
	0x01,0x00,
	0x02,0x80,
	0x04,0x40,
	0x0a,0x20,
	0x11,0x10,
	0x21,0x0e,
	0xc0,0x04,
	0x1f,0xf0,
	0x00,0x10,
	0x00,0x20,
	0x04,0x40,
	0x02,0x80,
	0x01,0x00,
	0x00,0x80,
	0x00,0x80,

	/* 59 0x3b "龙" 机内码:0xc1fa */
	0x02,0x00,
	0x02,0x40,
	0x02,0x20,
	0x02,0x04,
	0xff,0xfe,
	0x02,0x80,
	0x02,0x88,
	0x04,0x88,
	0x04,0x90,
	0x04,0xa0,
	0x08,0xc0,
	0x08,0x82,
	0x11,0x82,
	0x16,0x82,
	0x20,0x7e,
	0x40,0x00,

	/* 60 0x3c "路" 机内码:0xc2b7 */
	0x04,0x40,
	0x7e,0x40,
	0x44,0xfc,
	0x45,0x88,
	0x46,0x50,
	0x44,0x20,
	0x7c,0x50,
	0x50,0x8e,
	0x13,0x04,
	0x5d,0xfe,
	0x51,0x04,
	0x51,0x04,
	0x51,0x04,
	0x5d,0x04,
	0xe1,0xfc,
	0x01,0x04,

	/* 144 0x3c "略" 机内码:0xc2d4 */
    0x00 ,0x80 ,
    0x04 ,0x80 ,
    0x7E ,0xFC ,
    0x55 ,0x88 ,
    0x56 ,0x50 ,
    0x54 ,0x20 ,
    0x7C ,0x50 ,
    0x54 ,0x8E ,
    0x55 ,0x04 ,
    0x57 ,0xFE ,
    0x55 ,0x04 ,
    0x7D ,0x04 ,
    0x41 ,0x04 ,
    0x01 ,0x04 ,
    0x01 ,0xFC ,
    0x01 ,0x04 ,
    
	/* 61 0x3d "络" 机内码:0xc2e7 */
	0x10,0x80,
	0x10,0x80,
	0x20,0xfc,
	0x21,0x04,
	0x4a,0x88,
	0xf8,0x50,
	0x10,0x20,
	0x20,0x50,
	0x41,0x8e,
	0xfb,0xfc,
	0x05,0x04,
	0x01,0x04,
	0x19,0x04,
	0xe1,0x04,
	0x41,0xfc,
	0x01,0x04,

	/* 62 0x3e "面" 机内码:0xc3e6 */
	0x00,0x04,
	0xff,0xfe,
	0x02,0x00,
	0x04,0x04,
	0x7f,0xfe,
	0x44,0x44,
	0x44,0x44,
	0x47,0xc4,
	0x44,0x44,
	0x44,0x44,
	0x44,0x44,
	0x47,0xc4,
	0x44,0x44,
	0x44,0x44,
	0x7f,0xfc,
	0x40,0x04,

	/* 63 0x3f "秒" 机内码:0xc3eb */
	0x04,0x20,
	0x0e,0x20,
	0x78,0x20,
	0x08,0x20,
	0x08,0xa8,
	0xfe,0xa6,
	0x08,0xa2,
	0x1d,0x20,
	0x1a,0x24,
	0x28,0x24,
	0x28,0x28,
	0x48,0x10,
	0x88,0x20,
	0x08,0x40,
	0x08,0x80,
	0x0b,0x00,

	/* 64 0x40 "名" 机内码:0xc3fb */
	0x02,0x00,
	0x02,0x00,
	0x07,0xf0,
	0x04,0x10,
	0x0c,0x20,
	0x12,0x40,
	0x01,0x80,
	0x06,0x00,
	0x18,0x08,
	0xef,0xfc,
	0x08,0x08,
	0x08,0x08,
	0x08,0x08,
	0x08,0x08,
	0x0f,0xf8,
	0x08,0x08,

	/* 65 0x41 "命" 机内码:0xc3fc */
	0x01,0x00,
	0x01,0x00,
	0x02,0x80,
	0x04,0x40,
	0x08,0x30,
	0x3f,0xfe,
	0xc0,0x08,
	0x3e,0xfc,
	0x22,0x88,
	0x22,0x88,
	0x22,0x88,
	0x22,0xc8,
	0x3e,0xa8,
	0x22,0x90,
	0x00,0x80,
	0x00,0x80,

	/* 66 0x42 "内" 机内码:0xc4da */
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x04,
	0x7f,0xfe,
	0x41,0x04,
	0x41,0x04,
	0x42,0x04,
	0x42,0x84,
	0x44,0x64,
	0x48,0x34,
	0x50,0x14,
	0x40,0x04,
	0x40,0x04,
	0x40,0x14,
	0x40,0x08,

	/* 67 0x43 "年" 机内码:0xc4ea */
	0x08,0x00,
	0x08,0x08,
	0x1f,0xfc,
	0x11,0x00,
	0x21,0x00,
	0x41,0x10,
	0x1f,0xf8,
	0x11,0x00,
	0x11,0x00,
	0x11,0x04,
	0xff,0xfe,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,

	/* 68 0x44 "盘" 机内码:0xc5cc */
	0x02,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x12,0x10,
	0x11,0x14,
	0xff,0xfe,
	0x10,0x10,
	0x12,0x10,
	0x21,0x50,
	0x40,0x20,
	0x3f,0xf8,
	0x24,0x48,
	0x24,0x48,
	0x24,0x48,
	0xff,0xfe,
	0x00,0x00,

	/* 69 0x45 "配" 机内码:0xc5e4 */
	0x01,0x04,
	0xff,0xfe,
	0x14,0x04,
	0x14,0x04,
	0x7f,0x04,
	0x55,0x04,
	0x55,0x7c,
	0x55,0x44,
	0x55,0x40,
	0x63,0x40,
	0x41,0x40,
	0x7f,0x40,
	0x41,0x42,
	0x41,0x42,
	0x7f,0x3e,
	0x41,0x00,

	/* 70 0x46 "期" 机内码:0xc6da */
	0x22,0x04,
	0x22,0x7e,
	0x22,0x44,
	0x7f,0x44,
	0x22,0x44,
	0x3e,0x7c,
	0x22,0x44,
	0x3e,0x44,
	0x22,0x44,
	0x22,0x7c,
	0xff,0xc4,
	0x00,0x44,
	0x24,0x44,
	0x22,0x84,
	0x41,0x14,
	0x82,0x08,

	/* 71 0x47 "启" 机内码:0xc6f4 */
	0x01,0x00,
	0x00,0x84,
	0x1f,0xfe,
	0x10,0x04,
	0x10,0x04,
	0x10,0x04,
	0x1f,0xfc,
	0x10,0x00,
	0x10,0x04,
	0x1f,0xfe,
	0x18,0x04,
	0x28,0x04,
	0x28,0x04,
	0x48,0x04,
	0x8f,0xfc,
	0x08,0x04,
	
	/* 140 0x47 "器" 机内码:0xc6f7 */
    0x3E ,0xF8 ,
    0x22 ,0x88 ,
    0x22 ,0x88 ,
    0x22 ,0x88 ,
    0x3E ,0xF8 ,
    0x01 ,0x20 ,
    0x01 ,0x14 ,
    0xFF ,0xFE ,
    0x02 ,0x80 ,
    0x0C ,0x60 ,
    0x30 ,0x18 ,
    0xFE ,0xFE ,
    0x22 ,0x88 ,
    0x22 ,0x88 ,
    0x22 ,0x88 ,
    0x3E ,0xF8 ,

	/* 72 0x48 "前" 机内码:0xc7b0 */
	0x10,0x10,
	0x0c,0x30,
	0x04,0x44,
	0xff,0xfe,
	0x00,0x00,
	0x3e,0x08,
	0x22,0x48,
	0x22,0x48,
	0x3e,0x48,
	0x22,0x48,
	0x22,0x48,
	0x3e,0x48,
	0x22,0x08,
	0x22,0x08,
	0x2a,0x28,
	0x24,0x10,

	/* 73 0x49 "切" 机内码:0xc7d0 */
	0x10,0x00,
	0x10,0x04,
	0x11,0xfe,
	0x10,0x44,
	0x14,0x44,
	0x1e,0x44,
	0xf0,0x44,
	0x10,0x44,
	0x10,0x44,
	0x12,0x44,
	0x14,0x44,
	0x18,0x84,
	0x10,0x84,
	0x01,0x04,
	0x02,0x28,
	0x0c,0x10,

	/* 74 0x4a "确" 机内码:0xc8b7 */
	0x00,0x40,
	0x04,0x40,
	0xfe,0x78,
	0x10,0x90,
	0x11,0x24,
	0x23,0xfe,
	0x25,0x24,
	0x7d,0x24,
	0xa5,0xfc,
	0x25,0x24,
	0x25,0x24,
	0x25,0xfc,
	0x25,0x24,
	0x3d,0x24,
	0x22,0x24,
	0x04,0x0c,

	/* 75 0x4b "认" 机内码:0xc8cf */
	0x00,0x40,
	0x40,0x40,
	0x30,0x40,
	0x10,0x40,
	0x00,0x40,
	0x00,0x40,
	0xf0,0xa0,
	0x10,0xa0,
	0x10,0xa0,
	0x11,0x10,
	0x11,0x10,
	0x15,0x10,
	0x1a,0x08,
	0x12,0x08,
	0x04,0x06,
	0x08,0x04,

	/* 76 0x4c "日" 机内码:0xc8d5 */
	0x00,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x00,0x00,

	/* 77 0x4d "容" 机内码:0xc8dd */
	0x02,0x00,
	0x01,0x00,
	0x7f,0xfe,
	0x40,0x02,
	0x84,0x44,
	0x09,0x30,
	0x12,0x90,
	0x04,0x40,
	0x08,0x20,
	0x10,0x10,
	0x2f,0xee,
	0xc8,0x24,
	0x08,0x20,
	0x08,0x20,
	0x0f,0xe0,
	0x08,0x20,

	/* 78 0x4e "入" 机内码:0xc8eb */
	0x04,0x00,
	0x02,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x02,0x80,
	0x02,0x80,
	0x02,0x80,
	0x04,0x40,
	0x04,0x40,
	0x08,0x20,
	0x08,0x20,
	0x10,0x10,
	0x20,0x10,
	0x40,0x0e,
	0x80,0x04,

	/* 79 0x4f "若" 机内码:0xc8f4 */
	0x08,0x20,
	0x08,0x28,
	0x7f,0xfc,
	0x08,0x20,
	0x0a,0x20,
	0x02,0x04,
	0xff,0xfe,
	0x04,0x00,
	0x08,0x10,
	0x1f,0xf8,
	0x28,0x10,
	0x48,0x10,
	0x88,0x10,
	0x08,0x10,
	0x0f,0xf0,
	0x08,0x10,

	/* 80 0x50 "色" 机内码:0xc9ab */
	0x04,0x00,
	0x04,0x00,
	0x07,0xf0,
	0x08,0x20,
	0x08,0x48,
	0x1f,0xfc,
	0x28,0x88,
	0x48,0x88,
	0x08,0x88,
	0x0f,0xf8,
	0x08,0x08,
	0x08,0x00,
	0x08,0x02,
	0x08,0x02,
	0x07,0xfe,
	0x00,0x00,

	/* 81 0x51 "上" 机内码:0xc9cf */
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x10,
	0x01,0xf8,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x04,
	0xff,0xfe,
	0x00,0x00,

	/* 82 0x52 "设" 机内码:0xc9e8 */
	0x01,0xf0,
	0x21,0x10,
	0x11,0x10,
	0x11,0x10,
	0x01,0x10,
	0x02,0x0e,
	0xf4,0x00,
	0x13,0xf8,
	0x11,0x08,
	0x11,0x10,
	0x10,0x90,
	0x10,0xa0,
	0x14,0x40,
	0x18,0xb0,
	0x13,0x0e,
	0x0c,0x04,

	/* 83 0x53 "失" 机内码:0xcaa7 */
	0x01,0x00,
	0x11,0x00,
	0x11,0x00,
	0x11,0x10,
	0x1f,0xf8,
	0x21,0x00,
	0x41,0x00,
	0x01,0x04,
	0xff,0xfe,
	0x01,0x00,
	0x02,0x80,
	0x02,0x80,
	0x04,0x40,
	0x08,0x30,
	0x10,0x0e,
	0x60,0x04,

	/* 84 0x54 "时" 机内码:0xcab1 */
	0x00,0x08,
	0x04,0x08,
	0x7e,0x08,
	0x44,0x08,
	0x47,0xfe,
	0x44,0x08,
	0x44,0x08,
	0x7c,0x88,
	0x44,0x48,
	0x44,0x48,
	0x44,0x08,
	0x44,0x08,
	0x7c,0x08,
	0x44,0x48,
	0x00,0x28,
	0x00,0x10,

	/* 85 0x55 "使" 机内码:0xcab9 */
	0x10,0x40,
	0x10,0x44,
	0x1f,0xfe,
	0x20,0x40,
	0x27,0xfc,
	0x64,0x44,
	0xa4,0x44,
	0x24,0x44,
	0x27,0xfc,
	0x24,0x44,
	0x22,0x40,
	0x21,0x80,
	0x20,0xc0,
	0x21,0x30,
	0x26,0x0e,
	0x28,0x04,

	/* 86 0x56 "示" 机内码:0xcabe */
	0x00,0x10,
	0x3f,0xf8,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x04,
	0xff,0xfe,
	0x01,0x00,
	0x01,0x00,
	0x09,0x20,
	0x19,0x18,
	0x21,0x0c,
	0x41,0x04,
	0x01,0x00,
	0x05,0x00,
	0x02,0x00,

	/* 87 0x57 "是" 机内码:0xcac7 */
	0x0f,0xe0,
	0x08,0x20,
	0x08,0x20,
	0x0f,0xe0,
	0x08,0x20,
	0x08,0x20,
	0x0f,0xe0,
	0x00,0x04,
	0xff,0xfe,
	0x01,0x00,
	0x09,0x20,
	0x09,0xf0,
	0x09,0x00,
	0x15,0x00,
	0x23,0x06,
	0x40,0xfc,

	/* 88 0x58 "输" 机内码:0xcae4 */
	0x20,0x40,
	0x20,0xa0,
	0x28,0xa0,
	0xfd,0x10,
	0x22,0x0e,
	0x45,0xf4,
	0x50,0x00,
	0x93,0xc4,
	0xfa,0x54,
	0x13,0xd4,
	0x3a,0x54,
	0xd3,0xd4,
	0x12,0x54,
	0x12,0x44,
	0x12,0x44,
	0x12,0xcc,

	/* 89 0x59 "数" 机内码:0xcafd */
	0x08,0x40,
	0x49,0x40,
	0x2a,0x40,
	0x08,0x84,
	0xff,0xfe,
	0x19,0x08,
	0x2c,0x88,
	0x4a,0x88,
	0x10,0x88,
	0xfe,0x90,
	0x22,0x50,
	0x22,0x20,
	0x14,0x50,
	0x18,0x88,
	0x25,0x0e,
	0x42,0x04,

    /* 134 0x86 "所" 机内码:0xcbf9*/
    0x02,0x08,
    0x07,0x1C,
    0x38,0xE0,
    0x20,0x80,
    0x20,0x80,
    0x3E,0x84,
    0x22,0xFE,
    0x22,0x88,
    0x22,0x88,
    0x3E,0x88,
    0x22,0x88,
    0x20,0x88,
    0x21,0x08,
    0x42,0x08,
    0x84,0x08,
    0x00,0x08,
    
	/* 90 0x5a "台" 机内码:0xcca8 */
	0x02,0x00,
	0x02,0x00,
	0x04,0x00,
	0x08,0x20,
	0x10,0x10,
	0x20,0x08,
	0x7f,0xfc,
	0x00,0x04,
	0x00,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,

	/* 91 0x5b "提" 机内码:0xcce1 */
	0x10,0x08,
	0x11,0xfc,
	0x11,0x08,
	0x11,0x08,
	0xfd,0xf8,
	0x11,0x08,
	0x15,0x08,
	0x19,0xf8,
	0x30,0x00,
	0xd7,0xfe,
	0x10,0x20,
	0x11,0x28,
	0x11,0x3c,
	0x11,0x20,
	0x52,0xa6,
	0x24,0x7c,

	/* 92 0x5c "题" 机内码:0xcce2 */
	0x3e,0x04,
	0x23,0xfe,
	0x22,0x20,
	0x3e,0x44,
	0x22,0xfe,
	0x22,0x84,
	0x3e,0x94,
	0x00,0x94,
	0xff,0x94,
	0x08,0xa4,
	0x2a,0xa4,
	0x2f,0x20,
	0x28,0x58,
	0x58,0x84,
	0x49,0x06,
	0x87,0xfc,

	/* 93 0x5d "统" 机内码:0xcdb3 */
	0x10,0x80,
	0x10,0x40,
	0x20,0x48,
	0x27,0xfc,
	0x48,0x80,
	0xf9,0x10,
	0x12,0x08,
	0x27,0xfc,
	0x41,0x24,
	0xf9,0x20,
	0x41,0x20,
	0x01,0x20,
	0x1a,0x22,
	0xe2,0x22,
	0x44,0x1e,
	0x08,0x00,

	/* 94 0x5e "退" 机内码:0xcdcb */
	0x03,0xf8,
	0x42,0x08,
	0x32,0x08,
	0x13,0xf8,
	0x02,0x08,
	0x02,0x08,
	0xf3,0xfc,
	0x12,0x08,
	0x12,0xd0,
	0x12,0x20,
	0x12,0x90,
	0x13,0x0c,
	0x12,0x04,
	0x28,0x00,
	0x44,0x06,
	0x03,0xfc,

	/* 95 0x5f "网" 机内码:0xcdf8 */
	0x00,0x04,
	0x7f,0xfe,
	0x40,0x04,
	0x42,0x0c,
	0x62,0x8c,
	0x54,0x54,
	0x54,0x54,
	0x48,0x24,
	0x48,0x24,
	0x54,0x54,
	0x52,0x4c,
	0x62,0x8c,
	0x61,0x04,
	0x42,0x04,
	0x40,0x14,
	0x40,0x08,

	/* 96 0x60 "为" 机内码:0xceaa */
	0x00,0x80,
	0x10,0x80,
	0x0c,0x80,
	0x04,0x80,
	0x00,0x84,
	0xff,0xfe,
	0x01,0x04,
	0x01,0x04,
	0x02,0x04,
	0x02,0x84,
	0x04,0x64,
	0x08,0x24,
	0x10,0x04,
	0x20,0x04,
	0x40,0x28,
	0x00,0x10,

	/* 97 0x61 "文" 机内码:0xcec4 */
	0x02,0x00,
	0x01,0x00,
	0x01,0x04,
	0xff,0xfe,
	0x10,0x10,
	0x08,0x10,
	0x08,0x20,
	0x04,0x20,
	0x04,0x40,
	0x02,0x80,
	0x01,0x00,
	0x02,0x80,
	0x04,0x60,
	0x08,0x10,
	0x30,0x0e,
	0xc0,0x04,

	/* 98 0x62 "务" 机内码:0xcef1 */
	0x08,0x00,
	0x08,0x00,
	0x0f,0xf0,
	0x18,0x20,
	0x26,0xc0,
	0x41,0x00,
	0x06,0xc0,
	0x1a,0x30,
	0xe2,0x0e,
	0x1f,0xf4,
	0x02,0x10,
	0x02,0x10,
	0x04,0x10,
	0x04,0x10,
	0x08,0xa0,
	0x30,0x40,

	/* 99 0x63 "息" 机内码:0xcfa2 */
	0x02,0x00,
	0x04,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x10,0x10,
	0x1f,0xf0,
	0x02,0x00,
	0x51,0x84,
	0x50,0x92,
	0x90,0x12,
	0x0f,0xf0,

	/* 100 0x64 "系" 机内码:0xcfb5 */
	0x00,0x38,
	0x7f,0xc0,
	0x04,0x00,
	0x04,0x10,
	0x08,0x20,
	0x3f,0xc0,
	0x01,0x00,
	0x02,0x20,
	0x04,0x10,
	0x3f,0xf8,
	0x01,0x08,
	0x09,0x20,
	0x09,0x10,
	0x11,0x08,
	0x25,0x08,
	0x02,0x00,

	/* 101 0x65 "下" 机内码:0xcfc2 */
	0x00,0x04,
	0xff,0xfe,
	0x02,0x00,
	0x02,0x00,
	0x02,0x00,
	0x02,0x80,
	0x02,0x40,
	0x02,0x30,
	0x02,0x10,
	0x02,0x00,
	0x02,0x00,
	0x02,0x00,
	0x02,0x00,
	0x02,0x00,
	0x02,0x00,
	0x02,0x00,

	/* 102 0x66 "项" 机内码:0xcfee */
	0x00,0x04,
	0x0b,0xfe,
	0xfc,0x20,
	0x10,0x44,
	0x11,0xfe,
	0x11,0x04,
	0x11,0x24,
	0x11,0x24,
	0x11,0x24,
	0x11,0x24,
	0x1d,0x24,
	0xf1,0x24,
	0x41,0x24,
	0x00,0x58,
	0x00,0x84,
	0x03,0x02,

	/* 103 0x67 "向" 机内码:0xcff2 */
	0x02,0x00,
	0x04,0x00,
	0x08,0x04,
	0x7f,0xfe,
	0x40,0x04,
	0x40,0x24,
	0x4f,0xf4,
	0x48,0x24,
	0x48,0x24,
	0x48,0x24,
	0x48,0x24,
	0x4f,0xe4,
	0x48,0x24,
	0x40,0x04,
	0x40,0x14,
	0x40,0x08,

	/* 104 0x68 "小" 机内码:0xd0a1 */
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x05,0x40,
	0x05,0x20,
	0x09,0x10,
	0x09,0x08,
	0x11,0x04,
	0x21,0x04,
	0x41,0x00,
	0x01,0x00,
	0x01,0x00,
	0x05,0x00,
	0x02,0x00,

	/* 105 0x69 "芯" 机内码:0xd0be */
	0x08,0x20,
	0x08,0x24,
	0xff,0xfe,
	0x08,0x20,
	0x08,0x20,
	0x00,0x00,
	0x02,0x00,
	0x01,0x00,
	0x50,0x84,
	0x50,0x82,
	0x50,0x02,
	0x90,0x02,
	0x10,0x08,
	0x10,0x08,
	0x0f,0xf8,
	0x00,0x00,

	/* 106 0x6a "新" 机内码:0xd0c2 */
	0x10,0x08,
	0x0a,0x1c,
	0x7f,0x60,
	0x00,0x40,
	0x22,0x40,
	0x14,0x44,
	0xff,0xfe,
	0x0a,0x48,
	0x7f,0x48,
	0x08,0x48,
	0x0a,0x48,
	0x29,0x88,
	0x48,0x88,
	0x89,0x08,
	0x28,0x08,
	0x10,0x08,

	/* 107 0x6b "信" 机内码:0xd0c5 */
	0x08,0x80,
	0x08,0x44,
	0x0f,0xfe,
	0x10,0x00,
	0x10,0x08,
	0x37,0xfc,
	0x50,0x00,
	0x90,0x08,
	0x17,0xfc,
	0x10,0x00,
	0x13,0xf8,
	0x12,0x08,
	0x12,0x08,
	0x12,0x08,
	0x13,0xf8,
	0x12,0x08,

	/* 138 0x6b "型" 机内码:0xd0cd */
    0x01,0x04 ,
    0x7F ,0x84 ,
    0x12 ,0x24 ,
    0x12 ,0x24 ,
    0x12 ,0x24 ,
    0xFF ,0xA4 ,
    0x12 ,0x24 ,
    0x12 ,0x24 ,
    0x12 ,0x04 ,
    0x23 ,0x14 ,
    0x41 ,0x08 ,
    0x7F ,0xFC ,
    0x01 ,0x00 ,
    0x01 ,0x04 ,
    0xFF ,0xFE ,
    0x00 ,0x00 ,

	/* 108 0x6c "行" 机内码:0xd0d0 */
	0x08,0x08,
	0x0b,0xfc,
	0x10,0x00,
	0x20,0x00,
	0x40,0x00,
	0x08,0x04,
	0x17,0xfe,
	0x30,0x10,
	0x50,0x10,
	0x90,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x10,
	0x10,0x50,
	0x10,0x20,

	/* 109 0x6d "修" 机内码:0xd0de */
	0x11,0x00,
	0x11,0x00,
	0x11,0xf8,
	0x21,0x10,
	0x2a,0xa0,
	0x6c,0x40,
	0xa9,0xb0,
	0x2e,0x2e,
	0x28,0xc0,
	0x2b,0x10,
	0x28,0x60,
	0x28,0x88,
	0x23,0x10,
	0x20,0x60,
	0x21,0x80,
	0x26,0x00,

	/* 110 0x6e "需" 机内码:0xd0e8 */
	0x1f,0xf0,
	0x01,0x00,
	0x7f,0xfe,
	0x51,0x12,
	0x8d,0x64,
	0x11,0x10,
	0x01,0x04,
	0xff,0xfe,
	0x02,0x00,
	0x04,0x08,
	0x3f,0xfc,
	0x24,0x88,
	0x24,0x88,
	0x24,0x88,
	0x24,0xa8,
	0x20,0x10,

	/* 111 0x6f "选" 机内码:0xd1a1 */
	0x00,0x40,
	0x42,0x40,
	0x32,0x48,
	0x13,0xfc,
	0x02,0x40,
	0x04,0x44,
	0xf7,0xfe,
	0x10,0xa0,
	0x10,0xa0,
	0x10,0xa0,
	0x11,0x22,
	0x11,0x22,
	0x12,0x1e,
	0x2c,0x00,
	0x44,0x06,
	0x03,0xfc,

	/* 112 0x70 "颜" 机内码:0xd1d5 */
	0x10,0x04,
	0x09,0xfe,
	0x7f,0x20,
	0x22,0x44,
	0x14,0xfe,
	0x7f,0x84,
	0x44,0x94,
	0x48,0x94,
	0x52,0x94,
	0x44,0xa4,
	0x48,0xa4,
	0x52,0xa4,
	0x44,0xa4,
	0x48,0x48,
	0x90,0x86,
	0x21,0x02,

	/* 113 0x71 "要" 机内码:0xd2aa */
	0x00,0x08,
	0x7f,0xfc,
	0x04,0x40,
	0x3f,0xf8,
	0x24,0x48,
	0x24,0x48,
	0x3f,0xf8,
	0x02,0x00,
	0x02,0x04,
	0xff,0xfe,
	0x04,0x20,
	0x08,0x20,
	0x06,0x40,
	0x01,0x80,
	0x06,0x60,
	0x38,0x10,

	/* 114 0x72 "页" 机内码:0xd2b3 */
	0x00,0x04,
	0xff,0xfe,
	0x02,0x00,
	0x04,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x11,0x10,
	0x11,0x10,
	0x11,0x10,
	0x11,0x10,
	0x11,0x10,
	0x11,0x10,
	0x12,0x90,
	0x04,0x60,
	0x08,0x18,
	0x30,0x08,

	/* 115 0x73 "一" 机内码:0xd2bb */
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x04,
	0xff,0xfe,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,
	0x00,0x00,

	/* 116 0x74 "以" 机内码:0xd2d4 */
	0x00,0x00,
	0x04,0x08,
	0x42,0x08,
	0x43,0x08,
	0x41,0x08,
	0x40,0x08,
	0x40,0x08,
	0x40,0x08,
	0x41,0x10,
	0x42,0x10,
	0x44,0x10,
	0x48,0x20,
	0x50,0x30,
	0x60,0x48,
	0x01,0x84,
	0x06,0x04,

	/* 117 0x75 "意" 机内码:0xd2e2 */
	0x01,0x10,
	0x3f,0xf8,
	0x08,0x20,
	0x04,0x44,
	0xff,0xfe,
	0x00,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x1f,0xf0,
	0x02,0x00,
	0x51,0x84,
	0x50,0x92,
	0x90,0x12,
	0x0f,0xf0,

	/* 118 0x76 "用" 机内码:0xd3c3 */
	0x00,0x08,
	0x3f,0xfc,
	0x21,0x08,
	0x21,0x08,
	0x21,0x08,
	0x3f,0xf8,
	0x21,0x08,
	0x21,0x08,
	0x21,0x08,
	0x3f,0xf8,
	0x21,0x08,
	0x21,0x08,
	0x21,0x08,
	0x41,0x08,
	0x41,0x28,
	0x80,0x10,

	/* 119 0x77 "月" 机内码:0xd4c2 */
	0x00,0x10,
	0x0f,0xf8,
	0x08,0x10,
	0x08,0x10,
	0x08,0x10,
	0x0f,0xf0,
	0x08,0x10,
	0x08,0x10,
	0x08,0x10,
	0x0f,0xf0,
	0x08,0x10,
	0x08,0x10,
	0x10,0x10,
	0x10,0x10,
	0x20,0x50,
	0x40,0x20,

	/* 142 0x77 "载" 机内码:0xd4d8 */
    0x08 ,0x40 ,
    0x0A ,0x50 ,
    0x7F ,0x48 ,
    0x08 ,0x48 ,
    0x08 ,0x40 ,
    0xFF ,0xFE ,
    0x10 ,0x40 ,
    0xFF ,0x40 ,
    0x20 ,0x48 ,
    0x28 ,0x48 ,
    0x7E ,0x30 ,
    0x08 ,0x20 ,
    0x0F ,0x60 ,
    0xF8 ,0x92 ,
    0x09 ,0x0A ,
    0x0A ,0x06 ,
    
    /* 135 0x87 "在" 机内码:0xd4da*/
    0x02,0x00,
    0x02,0x00,
    0x02,0x04,
    0xFF,0xFE,
    0x04,0x00,
    0x04,0x40,
    0x08,0x40,
    0x08,0x50,
    0x13,0xF8,
    0x30,0x40,
    0x50,0x40,
    0x90,0x40,
    0x10,0x40,
    0x10,0x44,
    0x17,0xFE,
    0x10,0x00, 
	/* 120 0x78 "择" 机内码:0xd4f1 */
	0x10,0x00,
	0x13,0xf8,
	0x11,0x10,
	0x10,0xa0,
	0xfc,0x40,
	0x10,0xa0,
	0x15,0x10,
	0x1a,0x4e,
	0x35,0xf4,
	0xd0,0x40,
	0x10,0x48,
	0x17,0xfc,
	0x10,0x40,
	0x10,0x40,
	0x50,0x40,
	0x20,0x40,

	/* 121 0x79 "则" 机内码:0xd4f2 */
	0x01,0x04,
	0x7f,0x84,
	0x41,0x24,
	0x49,0x24,
	0x49,0x24,
	0x49,0x24,
	0x49,0x24,
	0x49,0x24,
	0x49,0x24,
	0x49,0x24,
	0x49,0x24,
	0x49,0x04,
	0x14,0x04,
	0x12,0x04,
	0x21,0x14,
	0xc1,0x08,

	/* 122 0x7a "直" 机内码:0xd6b1 */
	0x01,0x00,
	0x01,0x08,
	0x7f,0xfc,
	0x01,0x00,
	0x01,0x10,
	0x1f,0xf8,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x10,0x14,
	0xff,0xfe,
	0x00,0x00,

	/* 123 0x7b "执" 机内码:0xd6b4 */
	0x10,0x80,
	0x10,0x80,
	0x10,0x80,
	0x10,0x90,
	0xff,0xf8,
	0x10,0x90,
	0x14,0x90,
	0x18,0x90,
	0x31,0x90,
	0xd0,0x90,
	0x11,0x50,
	0x11,0x52,
	0x11,0x12,
	0x12,0x12,
	0x54,0x0e,
	0x28,0x00,

	/* 124 0x7c "址" 机内码:0xd6b7 */
	0x10,0x20,
	0x10,0x20,
	0x10,0x20,
	0x15,0x20,
	0xff,0x24,
	0x11,0x3e,
	0x11,0x20,
	0x11,0x20,
	0x11,0x20,
	0x11,0x20,
	0x11,0x20,
	0x13,0x20,
	0x1d,0x20,
	0xf1,0x24,
	0x47,0xfe,
	0x00,0x00,

	/* 125 0x7d "指" 机内码:0xd6b8 */
	0x11,0x00,
	0x11,0x08,
	0x11,0x1c,
	0x11,0xe0,
	0xfd,0x02,
	0x11,0x02,
	0x14,0xfe,
	0x18,0x04,
	0x31,0xfe,
	0xd1,0x04,
	0x11,0x04,
	0x11,0xfc,
	0x11,0x04,
	0x11,0x04,
	0x51,0xfc,
	0x21,0x04,

	/* 126 0x7e "至" 机内码:0xd6c1 */
	0x00,0x08,
	0x7f,0xfc,
	0x02,0x00,
	0x04,0x00,
	0x08,0x20,
	0x10,0x10,
	0x3f,0xf8,
	0x01,0x08,
	0x01,0x00,
	0x01,0x10,
	0x3f,0xf8,
	0x01,0x00,
	0x01,0x00,
	0x01,0x04,
	0xff,0xfe,
	0x00,0x00,

	/* 127 0x7f "置" 机内码:0xd6c3 */
	0x3f,0xf8,
	0x24,0x48,
	0x3f,0xf8,
	0x01,0x00,
	0x7f,0xfc,
	0x01,0x00,
	0x1f,0xf0,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x10,
	0x1f,0xf0,
	0x10,0x14,
	0xff,0xfe,
	0x00,0x00,

	/* 128 0x80 "制" 机内码:0xd6c6 */
	0x04,0x04,
	0x24,0x04,
	0x25,0x04,
	0x3f,0xa4,
	0x24,0x24,
	0x44,0xa4,
	0xff,0xe4,
	0x04,0x24,
	0x3f,0xa4,
	0x24,0xa4,
	0x24,0xa4,
	0x24,0x84,
	0x26,0x84,
	0x25,0x04,
	0x04,0x14,
	0x04,0x08,

	/* 129 0x81 "钟" 机内码:0xd6d3 */
	0x10,0x20,
	0x10,0x20,
	0x10,0x20,
	0x1c,0x24,
	0x21,0xfe,
	0x21,0x24,
	0x7d,0x24,
	0x91,0x24,
	0x11,0x24,
	0xfd,0xfc,
	0x11,0x24,
	0x10,0x20,
	0x14,0x20,
	0x18,0x20,
	0x10,0x20,
	0x00,0x20,

	/* 130 0x82 "重" 机内码:0xd6d8 */
	0x00,0x38,
	0x3f,0xc0,
	0x01,0x04,
	0xff,0xfe,
	0x01,0x10,
	0x1f,0xf8,
	0x11,0x10,
	0x1f,0xf0,
	0x11,0x10,
	0x1f,0xf0,
	0x01,0x00,
	0x3f,0xf8,
	0x01,0x00,
	0x01,0x04,
	0xff,0xfe,
	0x00,0x00,

	/* 131 0x83 "主" 机内码:0xd6f7 */
	0x02,0x00,
	0x01,0x00,
	0x01,0x08,
	0x7f,0xfc,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x10,
	0x3f,0xf8,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x04,
	0xff,0xfe,
	0x00,0x00,

	/* 132 0x84 "注" 机内码:0xd7a2 */
	0x00,0x80,
	0x40,0x40,
	0x30,0x44,
	0x17,0xfe,
	0x80,0x40,
	0x60,0x40,
	0x20,0x40,
	0x08,0x48,
	0x17,0xfc,
	0x20,0x40,
	0xe0,0x40,
	0x20,0x40,
	0x20,0x40,
	0x20,0x44,
	0x2f,0xfe,
	0x20,0x00,

	/* 141 0x84 "装" 机内码:0xd7b0 */
    0x08 ,0x40 ,
    0x48 ,0x48 ,
    0x2B ,0xFC ,
    0x08 ,0x40 ,
    0x18 ,0x50 ,
    0x29 ,0xF8 ,
    0x4A ,0x00 ,
    0x09 ,0x04 ,
    0xFF ,0xFE ,
    0x02 ,0x08 ,
    0x04 ,0x90 ,
    0x0C ,0xA0 ,
    0x14 ,0x40 ,
    0x65 ,0x30 ,
    0x06 ,0x0E ,
    0x04 ,0x04 ,

	/* 133 0x85 "字" 机内码:0xd7d6 */
	0x02,0x00,
	0x01,0x00,
	0x3f,0xfc,
	0x20,0x04,
	0x40,0x08,
	0x1f,0xe0,
	0x00,0x40,
	0x00,0x80,
	0x01,0x04,
	0xff,0xfe,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x01,0x00,
	0x05,0x00,
	0x02,0x00
#if 0
    /* 134 0x86 "所" 机内码:0xcbf9*/
    0x02,0x08,
    0x07,0x1C,
    0x38,0xE0,
    0x20,0x80,
    0x20,0x80,
    0x3E,0x84,
    0x22,0xFE,
    0x22,0x88,
    0x22,0x88,
    0x3E,0x88,
    0x22,0x88,
    0x20,0x88,
    0x21,0x08,
    0x42,0x08,
    0x84,0x08,
    0x00,0x08,

    /* 135 0x87 "在" 机内码:0xd4da*/
    0x02,0x00,
    0x02,0x00,
    0x02,0x04,
    0xFF,0xFE,
    0x04,0x00,
    0x04,0x40,
    0x08,0x40,
    0x08,0x50,
    0x13,0xF8,
    0x30,0x40,
    0x50,0x40,
    0x90,0x40,
    0x10,0x40,
    0x10,0x44,
    0x17,0xFE,
    0x10,0x00  
    #endif
};
#endif
