#include<iostream>
#include<fstream>
#include <cstring>
#include<openssl/aes.h>

#define MINGWEN "This is a top secret."

using namespace std;

string chooseArmFile(string filename){
	cout<<"start"<<endl;
	ifstream in(filename);
	string line;
	string arm="";
	if(in){
		while(getline(in,line))
			arm+=line;
	}else{
		cout<<"NO SUCH FILE!";
	}
	return arm;

}
//unsigned char 转 十六进制字符串
void byte_to_hexstr( const unsigned char* source, char* dest, int sourceLen ){
	short i;
	unsigned char highByte, lowByte;
	for (i = 0; i < sourceLen; i++)
	{
		highByte = source[i] >> 4;
		lowByte = source[i] & 0x0f ;
 
		highByte += 0x30;
 
		if (highByte > 0x39)
			dest[i * 2] = highByte + 0x07;
		else
			dest[i * 2] = highByte;
 
		lowByte += 0x30;
		if (lowByte > 0x39)
			dest[i * 2 + 1] = lowByte + 0x07;
		else
			dest[i * 2 + 1] = lowByte;
	}
	return ;
}


unsigned char hex_to_int(const char ch)
{
	if(ch >='a' && ch <='f')
		return ch - 'a' + 10;
	else if(ch >='A' && ch <='F')
		return ch - 'A' + 10;
	else
		return ch - '0';
}

void hex_to_str(char *out_string, int length, const unsigned char *in_string)
{
    int i, j;
    unsigned char temp='\0';

    for(i = 0, j = 0; i < length; i += 2, j++)
    {
        temp = (hex_to_int(in_string[i]) << 4) + hex_to_int(in_string[i+1]);
        out_string[j] = temp;
    }
    // return (length<<1);
}





string burpit(string armCode,string vi,string dic){
	char current_dic[17];//当前字典密码
	char out[128];//字典密码加密密文
	char iv[128];//向量
	char armcode[128];//破译密文
	int num=0;//记录读取字典行数
	strcpy(armcode,armCode.c_str());
	strcpy(iv,vi.c_str());
	unsigned char *vivi= new unsigned char[strlen(iv)+1];//偏移向量
	for(int i=0;i<strlen(iv);i++)
		vivi[i]=iv[i];	
	AES_KEY  en_key;
	ifstream in(dic);
	string line;

	if(in){//如果文件存在
		while(getline(in,line)){//只要字典没读完
			num++;//读取第一行
			unsigned char plain[33]="This is a top secret.";//初始化破解密文
			//偏移向量初始化		
			for(int i=0;i<strlen(iv);i++)
				vivi[i]=iv[i];	
			//当前字典明文类型转换并填充‘#’至16字节
			strcpy(current_dic,line.c_str());
			unsigned char * dic=(unsigned char *)current_dic;
			int length=0;
			for(;length<16;length++){
				if(dic[length]!='\0') continue;
				else{
					dic[length]='#';
					dic[length+1]='\0';				
				}
			}
			//通过字典明文生成对应的en_key
			AES_set_encrypt_key(dic,128,&en_key);
			//加密明文
			unsigned char vivi_[33];//={ 0xaa ,0xbb ,0xcc ,0xdd ,0xee ,0xff ,0x00 ,0x99 ,0x88 ,0x77 ,0x66 ,0x55 ,0x44 ,0x33 ,0x22 ,0x11 };
			hex_to_str((char*)vivi_,32,(unsigned char*)vivi);
			
			AES_cbc_encrypt(plain,(unsigned char *)out,21,&en_key,vivi_,AES_ENCRYPT);
			//将加密明文转化为16进制格式
			char hex_[100];
			byte_to_hexstr((unsigned char *)out,hex_,strlen(out));
			hex_[64]='\0';
			//打印测试
			if(hex_[0]=='7'&&hex_[1]=='6'&&hex_[2]=='4'&&hex_[3]=='A'){
				cout<<(char*)hex_<<' '<<(char*)armcode<<endl;

			}

		}
	}else{
		cout<<"NO SUCH FILE!";
	}
	cout<<"读取行数："<<num<<endl;
	return line;
}
string burpit2(string armCode,string vi,string dic){
	char current_dic[17];//当前字典密码
	unsigned char out[33];//输出结果用于和明文比较
	char iv[128];//向量
	char armcode[65];//破译密文
	int num=0;//记录读取字典行数
	strcpy(armcode,armCode.c_str());
	armcode[64]='\0';
	strcpy(iv,vi.c_str());
	unsigned char *vivi= new unsigned char[strlen(iv)+1];//偏移向量
	AES_KEY  de_key;
	ifstream in(dic);
	string line;

	if(in){//如果文件存在
		while(getline(in,line)){//只要字典没读完
			num++;//读取第一行
			unsigned char plain[33]=MINGWEN;//初始化破解密文
			//偏移向量初始化
			int i=0;		
			for(;i<strlen(iv);i++)
				vivi[i]=iv[i];	
			vivi[i]='\0';
			//当前字典明文类型转换并填充‘#’至16字节
			strcpy(current_dic,line.c_str());
			unsigned char * dic=(unsigned char *)current_dic;
			int length=0;
			for(;length<16;length++){
				if(dic[length]!='\0') continue;
				else{
					dic[length]='#';
					dic[length+1]='\0';				
				}
			}
			//通过字典明文生成对应的en_key
			AES_set_decrypt_key(dic,128,&de_key);
			//解密密文
			//条件密文转ascii
			unsigned char armcode_[65];
			hex_to_str((char*)armcode_,64,(unsigned char*)armcode);
			unsigned char vivi_[33];//={ 0xaa ,0xbb ,0xcc ,0xdd ,0xee ,0xff ,0x00 ,0x99 ,0x88 ,0x77 ,0x66 ,0x55 ,0x44 ,0x33 ,0x22 ,0x11 };
			hex_to_str((char*)vivi_,32,(unsigned char*)vivi);
			//cout<<vivi<<"   "<<strlen((char*)vivi_);
			//解密密文
			AES_cbc_encrypt(armcode_,out,32,&de_key,vivi_,AES_DECRYPT);
			out[21]='\0';
			plain[21]='\0';
			

			if(strcmp((char*)out,(char*)plain)==0){
				cout<<"success "<<"密钥为："<<line<<endl;
				break;
			}
				
		}
	}else{
		cout<<"NO SUCH FILE!";
	}
	cout<<"读取行数："<<num<<endl;
	return line;
}
int main(){
	string armCodeFilename="armc2.txt";//密文文件
	string armCode=chooseArmFile(armCodeFilename);
	string armViFilename="vi.txt";//向量文件
	string armVi=chooseArmFile(armViFilename);
	//cout<<"破译密文："<<armCode<<endl;
	//cout<<"加密向量："<<armVi<<endl;
	string dic="dic.txt";
	//解密爆破
	burpit2(armCode,armVi,dic);
	//加密爆破	
	//burpit(armCode,armVi,dic);
	return 0;
}

