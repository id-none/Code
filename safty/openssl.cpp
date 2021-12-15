#include <iostream>
#include <fstream>
#include <cstring>
#include <openssl/aes.h>

#define MINGWEN "This is a top secret."

using namespace std;

string chooseArmFile(string filename)
{
	ifstream in(filename);
	string line;
	string arm = "";
	if (in)
	{
		while (getline(in, line))
			arm += line;
	}
	else
	{
		cout << "NO SUCH FILE!";
	}
	return arm;
}
//unsigned char ת ʮ�������ַ���
void byte_to_hexstr(const unsigned char *source, char *dest, int sourceLen)
{
	short i;
	unsigned char highByte, lowByte;
	for (i = 0; i < sourceLen; i++)
	{
		highByte = source[i] >> 4;
		lowByte = source[i] & 0x0f;

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
	return;
}

unsigned char hex_to_int(const char ch)
{
	if (ch >= 'a' && ch <= 'f')
		return ch - 'a' + 10;
	else if (ch >= 'A' && ch <= 'F')
		return ch - 'A' + 10;
	else
		return ch - '0';
}

void hex_to_str(char *out_string, int length, const unsigned char *in_string)
{
	int i, j;
	unsigned char temp = '\0';

	for (i = 0, j = 0; i < length; i += 2, j++)
	{
		temp = (hex_to_int(in_string[i]) << 4) + hex_to_int(in_string[i + 1]);
		out_string[j] = temp;
	}
	// return (length<<1);
}

string burpit2(string armCode, string vi, string dic)
{
	char current_dic[17];  //��ǰ�ֵ�����
	unsigned char out[33]; //���������ں����ıȽ�
	char armcode[65];	   //��������
	int num = 0;		   //��¼��ȡ�ֵ�����
	strcpy(armcode, armCode.c_str());
	armcode[64] = '\0';
	AES_KEY de_key;
	ifstream in(dic);
	string line;

	if (in)
	{ //����ļ�����
		while (getline(in, line))
		{									   //ֻҪ�ֵ�û����
			num++;							   //��ȡ��һ��
			unsigned char plain[33] = MINGWEN; //��ʼ���ƽ�����
			//ƫ��������ʼ��
			int i = 0;

			//��ǰ�ֵ���������ת������䡮#����16�ֽ�
			strcpy(current_dic, line.c_str());
			unsigned char *dic = (unsigned char *)current_dic;
			int length = 0;
			for (; length < 16; length++)
			{
				if (dic[length] != '\0')
					continue;
				else
				{
					dic[length] = '#';
					dic[length + 1] = '\0';
				}
			}
			//ͨ���ֵ��������ɶ�Ӧ��en_key
			AES_set_decrypt_key(dic, 128, &de_key);
			//��������
			//��������תascii
			unsigned char armcode_[65];
			hex_to_str((char *)armcode_, 64, (unsigned char *)armcode);
			unsigned char vivi_[33] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};
			//��������
			AES_cbc_encrypt(armcode_, out, 32, &de_key, vivi_, AES_DECRYPT);
			out[21] = '\0';
			plain[21] = '\0';

			if (strcmp((char *)out, (char *)plain) == 0)
			{
				cout << "success "
					 << "��ԿΪ��" << line << endl;
				break;
			}
		}
	}
	else
	{
		cout << "NO SUCH FILE!";
	}
	cout << "��ȡ������" << num << endl;
	return line;
}
int main()
{
	string armCodeFilename = "key2.txt"; //�����ļ�
	string armCode = chooseArmFile(armCodeFilename);
	string armViFilename = "vi.txt"; //�����ļ�
	string armVi = chooseArmFile(armViFilename);
	//cout<<"�������ģ�"<<armCode<<endl;
	//cout<<"����������"<<armVi<<endl;
	string dic = "words.txt";
	//���ܱ���
	//burpit2(armCode,armVi,dic);
	//���ܱ���
	burpit2(armCode, armVi, dic);
	return 0;
}
