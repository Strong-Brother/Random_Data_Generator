/*

������Ҫ��һЩȫ�ֱ������ļ����� 

*/
#include<bits/stdc++.h>
#include<windows.h>
#define ll long long
using namespace std;

//�ļ�ָ�� 
FILE *file_f;

//��Ҫ��ȡ���ļ�����(����) 
const ll FILE_NUM = 5;

//������������룬�������
ll RAND_num = 0, random_seed = time(0);

//�ļ���ȡ��ʽ���ļ��� 
bool FILE_way = 0;
string FILE_name = "����ļ�.txt";

//�������Ƿ���Ҫ��ͣ��������������
bool AnyKey = 1; 

//��������� 
mt19937_64 rd(random_seed);
default_random_engine rd_1(random_seed);


struct IorS{	//�洢�������ַ��� 
	ll a_int = 114514;
	string a_str = "ERROR";
	bool zt;		//0Ϊ������1Ϊ�ַ��� 
};
void SET_file_values( vector<IorS>values, string file_name ){		//����������д���ļ�����
	fclose(file_f);
	file_f = fopen(file_name.c_str(),"w");
	bool endl = 0;
	
	for(auto value : values){
		if(endl) fprintf(file_f,"\n");
		else endl = 1;
		
		if(value.zt){
			fprintf(file_f,"%s",value.a_str.c_str());
		}else{
			fprintf(file_f,"%lld",value.a_int);
		}
	}
	
	fclose(file_f);
} 
vector<IorS> GET_file_values(){		//��ȡ�ļ�����,���ļ����������Զ�����̶����� 
	
	file_f = fopen("����.ini","r");
	
	vector<IorS> values;
	
	ll tmp = 114514;
	string tmp_s;
	tmp_s.resize(1000);		//�ļ������1000���ַ� 
	
	//��������趨�� 
	bool IorS_in[ FILE_NUM ] = {0,0,0,1,0};		//�ж϶���������ͣ�0Ϊ������1Ϊ�ַ��� 
	ll I[ FILE_NUM ] = {0,-1,0,INT_MIN,1};
	string S[ FILE_NUM ] = {"","","","����ļ�.txt",""};
	
	if(file_f == NULL){
		
		for(ll i = 0; i < FILE_NUM; i++){		//���̶��Ĳ����洢���ļ��� 
			
			IorS t;
			t.zt = IorS_in[i];
			if(t.zt){
				t.a_str = S[i];
			}
			else{
				t.a_int = I[i];
			}
			values.push_back(t);
			
		}
		SET_file_values( values,"����.ini" );
		
		system("cls");
		cout<<"���ڳ�ʼ���С���"<<'\n';
		Sleep(500);
		
	}else{
		
		for(ll i = 0; i < FILE_NUM; ++i){
			if( IorS_in[i] ) fscanf(file_f,"%s", &tmp_s[0] );
			else fscanf(file_f,"%lld",&tmp);
			
			IorS t;
			t.zt = IorS_in[i];
			if(t.zt) t.a_str = tmp_s;
			else t.a_int = tmp;
			
			values.push_back(t);
		}
		
	}
	
	fclose(file_f);
	return values; 
	
}
void SET_seed(ll random_seed){		//��������� ����
	if(random_seed == -1) random_seed = time(0);
	rd.seed( random_seed );
	rd_1.seed( random_seed );
	srand( random_seed );
}

void FILE_INI(){			//��ʼ��
	
	vector<IorS> values = GET_file_values();
	for(ll i = 0; i < FILE_NUM; i++){
		switch(i){
			case 0:{
				RAND_num = values[i].a_int;
				break;
			}
			case 1:{
				random_seed = values[i].a_int;
				break;
			}
			case 2:{
				if(values[i].a_int) values[i].a_int = 1;
				FILE_way = values[i].a_int;
				break;
			}
			case 3:{
				FILE_name = values[i].a_str;
				break;
			}
			case 4:{
				if(values[i].a_int) values[i].a_int = 1;
				AnyKey = values[i].a_int;
				break;
			}
		}
	}
	
	SET_seed(random_seed);
}


vector<int> commands;		//ָ����� 

void SET_cmds( vector<int>cmds ){
	for(auto i : cmds){
		commands.push_back(i);
	}
}
bool SET_FILE_cmds( string CmdsFileName ){
	if(commands.size() == 0) return 0;
	
	file_f = fopen( CmdsFileName.c_str(), "w" );
	if(file_f == NULL){
		fclose(file_f);
		return 0;
	}
	
	for(auto cmd : commands){
		fprintf(file_f,"%d",cmd);
		fprintf(file_f,"\n");
	}
	
	fclose(file_f);
	return 1;
}
vector<int> GET_FILE_cmds( string CmdsFileName ){
	vector<int> cmds;
	
	file_f = fopen( CmdsFileName.c_str(), "r" );
	if(file_f == NULL){
		fclose(file_f);
		return cmds;
	}
	
	int cmd;
	while(fscanf( file_f, "%d", &cmd ) == 1){
		cmds.push_back(cmd);
	}
	
	return cmds;
}


#undef ll
