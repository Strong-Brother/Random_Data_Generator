/*

这里主要放一些全局变量和文件函数 

*/
#include<bits/stdc++.h>
#include<windows.h>
#define ll long long
using namespace std;

//文件指针 
FILE *file_f;

//需要读取的文件数量(行数) 
const ll FILE_NUM = 5;

//随机生成器编码，随机种子
ll RAND_num = 0, random_seed = time(0);

//文件读取方式，文件名 
bool FILE_way = 0;
string FILE_name = "输出文件.txt";

//操作后是否需要暂停（任意键后继续）
bool AnyKey = 1; 

//随机生成器 
mt19937_64 rd(random_seed);
default_random_engine rd_1(random_seed);


struct IorS{	//存储整数或字符串 
	ll a_int = 114514;
	string a_str = "ERROR";
	bool zt;		//0为整数，1为字符串 
};
void SET_file_values( vector<IorS>values, string file_name ){		//根据数组来写入文件内容
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
vector<IorS> GET_file_values(){		//读取文件内容,若文件不存在则自动读入固定数据 
	
	file_f = fopen("设置.ini","r");
	
	vector<IorS> values;
	
	ll tmp = 114514;
	string tmp_s;
	tmp_s.resize(1000);		//文件名最多1000个字符 
	
	//最初设置设定： 
	bool IorS_in[ FILE_NUM ] = {0,0,0,1,0};		//判断读入变量类型，0为整数，1为字符串 
	ll I[ FILE_NUM ] = {0,-1,0,INT_MIN,1};
	string S[ FILE_NUM ] = {"","","","输出文件.txt",""};
	
	if(file_f == NULL){
		
		for(ll i = 0; i < FILE_NUM; i++){		//将固定的参数存储进文件里 
			
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
		SET_file_values( values,"设置.ini" );
		
		system("cls");
		cout<<"正在初始化中……"<<'\n';
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
void SET_seed(ll random_seed){		//随机数种子 设置
	if(random_seed == -1) random_seed = time(0);
	rd.seed( random_seed );
	rd_1.seed( random_seed );
	srand( random_seed );
}

void FILE_INI(){			//初始化
	
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


vector<int> commands;		//指令操作 

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
