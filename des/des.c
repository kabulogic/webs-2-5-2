/*-------------------------------------------------------
      Data Encryption Standard  56位密钥加密64位数据 
				  2011.10
--------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tables.h"

/*-------------------------------
 把DatIn开始的长度位Len位的二进制
 复制到DatOut后
--------------------------------*/
extern void BitsCopy(bool *DatOut,bool *DatIn,int Len)     // 数组复制 OK 
{
	int i=0;
	for(i=0;i<Len;i++)
	{
		DatOut[i]=DatIn[i];
	}
}

/*-------------------------------
 字节转换成位函数 
 每8次换一个字节 每次向右移一位
 和1与取最后一位 共64位 
--------------------------------*/
extern void ByteToBit(bool *DatOut,char *DatIn,int Num)       // OK
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatOut[i]=(((unsigned int)(DatIn[i/8]))>>(7 - i%8))&0x01;   
	}                 
}

extern void bytetobit(bool *DatOut,char *DatIn,int Num)       // OK
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatOut[i]=((*DatIn)>>(3-i%Num))&0x01;   
	}                 
}
/*-------------------------------
 位转换成字节函数
 字节数组每8次移一位
 位每次向左移 与上一次或   
---------------------------------*/
extern void BitToByte(char *DatOut,bool *DatIn,int Num)        // OK
{
	int i=0;
	for(i=0;i<(Num/8);i++)
	{
		DatOut[i]=0;
	} 
	for(i=0;i<Num;i++)
	{
		DatOut[i/8]|=DatIn[i]<<(7-(i%8));	
	}		
}


/*----------------------------------
 二进制密文转换为十六进制
 需要16个字符表示
-----------------------------------*/
extern void BitToHex(char *DatOut,bool *DatIn,int Num)
{
	int i=0;
	//将输出的数组16位清零
	for(i=0;i<Num/4;i++)
	{
		DatOut[i]=0;
	}
	for(i=0;i<Num/4;i++)
	{
		DatOut[i] = (DatIn[i*4]<<3)+(DatIn[i*4+1]<<2)
					+(DatIn[i*4+2]<<1)+(DatIn[i*4+3]);
		if((DatOut[i]%16)>9)
		{
			DatOut[i]=DatOut[i]%16+'7';       //  余数大于9时处理 10-15 to A-F
		}                                     //  输出字符 
		else
		{
			DatOut[i]=DatOut[i]%16+'0';       //  输出字符	   
		}
	}
	
}

/*---------------------------------------------
 十六进制字符转二进制
----------------------------------------------*/
extern void HexToBit(bool *DatOut,char *DatIn,int Num)
{
	int i=0;                        // 字符型输入 
	for(i=0;i<Num;i++)
	{
		if((DatIn[i/4])>'9')         //  大于9 
		{
			DatOut[i]=((DatIn[i/4]-'7')>>(3-i%4))&0x01;   			
		}
		else
		{
			DatOut[i]=((DatIn[i/4]-'0')>>(3-i%4))&0x01; 	
		} 
	}	
}

// 表置换函数  OK
extern void TablePermute(bool *DatOut,bool *DatIn,const char *Table,int Num)  
{
	int i=0, j=0, k=0;
	static bool Temp[256]={0};
	for(i=0;i<Num;i++)                // Num为置换的长度 
	{
		Temp[i]=DatIn[Table[i]-1];  // 原来的数据按对应的表上的位置排列 
	}
	BitsCopy(DatOut,Temp,Num);       // 把缓存Temp的值输出 
	
} 

// 子密钥的移位
extern void LoopMove(bool *DatIn,int Len,int Num) // 循环左移 Len数据长度 Num移动位数
{
	static bool Temp[256]={0};    // 缓存   OK
	BitsCopy(Temp,DatIn,Num);       // 将数据最左边的Num位(被移出去的)存入Temp 
	BitsCopy(DatIn,DatIn+Num,Len-Num); // 将数据左边开始的第Num移入原来的空间
	BitsCopy(DatIn+Len-Num,Temp,Num);  // 将缓存中移出去的数据加到最右边 
} 

// 按位异或
extern void Xor(bool *DatA,bool *DatB,int Num)           // 异或函数
{
	int i=0;
	for(i=0;i<Num;i++)
	{
		DatA[i]=DatA[i]^DatB[i];                  // 异或 
	}
} 

// 输入48位 输出32位 与Ri异或
extern void S_Change(bool DatOut[32],bool DatIn[48])     // S盒变换
{
	int i,X,Y,j;									// i为8个S盒 
	bool* pOut = DatOut;
	bool* pIn = DatIn;
	for(i=0,Y=0,X=0;i<8;i++,pIn+=6/*,DatOut+=4*/)   // 每执行一次,输入数据偏移6位 
	{    										  // 每执行一次,输出数据偏移4位
		Y=(pIn[0]<<1)+pIn[5];                          // af代表第几行
		X=(pIn[1]<<3)+(pIn[2]<<2)+(pIn[3]<<1)+pIn[4]; // bcde代表第几列
//		printf("Y=%d,X=%d,i=%d,SBOX=%d\n",Y,X,i,S_Box[i][Y][X]);
		for(j=0;j<4;j++){
			*pOut++ = ((unsigned int)S_Box[i][Y][X] >> (3-j))&0x01;
		}

	}
}

// F函数
extern void F_Change(bool DatIn[32],bool DatKi[48])       // F函数
{
	int i;
	static bool MiR[48]={0};             // 输入32位通过E选位变为48位
	//传进来的右边32bit数据
/*	printf("ipRight=");
	for(i=0;i<32;i++){
		printf("%d",DatIn[i]);
	}
	printf("\n");
*/
	TablePermute(MiR,DatIn,E_Table,48); 
	//初次置换后变成48bit数据
/*	printf("datexp=");
	for(i=0; i<48; i++){
		printf("%d",MiR[i]);
	}
	printf("\n");
*/
	Xor(MiR,DatKi,48);                   // 和子密钥异或
	//和子密钥异或后的值
/*	printf("datxor=");
	for(i=0; i<48; i++){
		printf("%d",MiR[i]);
	}
	printf("\n");
*/
	S_Change(DatIn,MiR);                 // S盒变换
	//S变化后 6bit*8 -> 4bit*8
/*	printf("datsp=");
	for(i=0; i<32; i++){
		printf("%d",DatIn[i]);
	}
	printf("\n");
*/
	TablePermute(DatIn,DatIn,P_Table,32);   // P置换后输出
	//P置换后的值
/*	printf("datpp=");
	for(i=0; i<32; i++){
		printf("%d",DatIn[i]);
	}
	printf("\n");
*/
}



extern void SetKey(char KeyIn[8])               // 设置密钥 获取子密钥Ki 
{
	int i=0;
	static bool KeyBit[64]={0};                // 密钥二进制存储空间 
	static bool KeyAfter[56] = {0};			//保存可用的密钥
	static bool *KiL=&KeyAfter[0],*KiR=&KeyAfter[28];  // 前28,后28共56
	ByteToBit(KeyBit,KeyIn,64);                    // 把密钥转为二进制存入KeyBit 
	int k=0;
/*	printf("key:");
	for(k=0; k<64; k++)
	{
		printf("%d,",KeyBit[k]);
	}
	printf("\n");
*/
	//PC1表置换
//	PcPermute(KeyAfter, KeyBit);
	TablePermute(KeyAfter,KeyBit,PC1_Table,56);      // PC1表置换 56次
/*	printf("keypc1:");
	for(k=0; k<56; k++)
	{
		printf("%d,",KeyAfter[k]);
	}
	printf("\n");
*/
	for(i=0;i<16;i++)
	{
		LoopMove(KiL,28,Move_Table[i]);       // 前28位左移 
		LoopMove(KiR,28,Move_Table[i]);	      // 后28位左移 
	 	TablePermute(SubKey[i],KeyAfter,PC2_Table,48); 
	 	// 二维数组 SubKey[i]为每一行起始地址 
	 	// 每移一次位进行PC2置换得 Ki 48位 
	}		
}

extern void PlayDes(char MesOut[8],char MesIn[8])  // 执行DES加密
{                                           // 字节输入 Bin运算 Hex输出 
	int i=0;
	static bool MesBit[64]={0};        // 明文二进制存储空间 64位
	static bool Temp[32]={0};
	static bool *MiL=&MesBit[0],*MiR=&MesBit[32]; // 前32位 后32位 
	ByteToBit(MesBit,MesIn,64);                 // 把明文换成二进制存入MesBit
/*	printf("abcdefgh:");
	int k = 0;
	for(k=0;k<64;k++)
	{
		printf("%d,",MesBit[k]);
	}
	printf("\n");
*/
	TablePermute(MesBit,MesBit,IP_Table,64);    // IP置换 
/*	printf("ipbit:");
	for(k=0;k<64;k++)
	{
		printf("%d,",MesBit[k]);
	}
	printf("\n");
*/
	for(i=0;i<16;i++)                       // 迭代16次 
	{
		BitsCopy(Temp,MiR,32);// 临时存储
/*		printf("SubKey[%d]:\n",i);
		for(k=0; k<48; k++)
		{
			printf("%d",SubKey[i][k]);
		}
		printf("\n");
*/
		F_Change(MiR,SubKey[i]);           // F函数变换
		Xor(MiR,MiL,32);                  // 得到Ri 
/*		printf("tempRight=");
		int e=0;
		for(e=0;e<32;e++){
			printf("%d",MiR[e]);
		}
		printf("\n");
		printf("\n");
*/
		BitsCopy(MiL,Temp,32);            // 得到Li 
	}					
/*	printf("MesBit_forward:");
	for(i=0; i<64; i++)
	{
		printf("%d,",MesBit[i]);
	}
	printf("\n");
*/
	TablePermute(MesBit,MesBit,IPR_Table,64);
/*	printf("MesBit_after:");
	for(i=0; i<64; i++)
	{
		printf("%d,",MesBit[i]);
	}
	printf("\n");
*/
	BitToHex(MesOut,MesBit,64);
}

extern void KickDes(char MesOut[8],char MesIn[8])       // 执行DES解密
{												// Hex输入 Bin运算 字节输出 
	int i=0;
	static bool MesBit[64]={0};        // 密文二进制存储空间 64位
	static bool Temp[32]={0};
	static bool *MiL=&MesBit[0],*MiR=&MesBit[32]; // 前32位 后32位
	HexToBit(MesBit,MesIn,64);                 // 把密文换成二进制存入MesBit
	TablePermute(MesBit,MesBit,IP_Table,64);    // IP置换 
	for(i=15;i>=0;i--)
	{
		BitsCopy(Temp,MiL,32);
		F_Change(MiL,SubKey[i]);
		Xor(MiL,MiR,32);
		BitsCopy(MiR,Temp,32);
	}	
	TablePermute(MesBit,MesBit,IPR_Table,64);
/*	for(i=0; i<64; i++)
	{
		printf("%d",MesBit[i]);
	}
	printf("\n");
*/
	BitToByte(MesOut,MesBit,64);		
} 








