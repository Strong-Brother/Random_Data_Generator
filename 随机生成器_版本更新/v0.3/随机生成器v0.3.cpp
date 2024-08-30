#include "RAND.h"

#define ll long long
using namespace std;

FILE *f;
const int vd_num = 7;		//函数的个数 
bool ENDL;	//控制文件输出换行符'\n'，1为输出，0为不输出 
bool FIRST_ENDL;	//控制第一次文件换行 

bool pd_Error(bool pd){
	if(pd){
		cout<<'\n'<<"输入错误，请重新输入"<<'\n'<<'\n';
		Sleep(500);
		return 1;
	}
	return 0;
}
void SET_ENDL(){
	if(ENDL) fprintf(f,"\n");
}

void MAIN();
void F1();
void S2();
void S2_1(),S2_2(),S2_3(),S2_4(),S2_5(),S2_6();
void T3();
void F4();
void F5();
void S6();
void S7();
void S7_1(),S7_2();
void E8();

void INI(){		//初始化 
	
	FILE_INI();
	
	string way;
	if(FILE_way){		//以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。（原来的EOF符不保留）
		way = "a+";
		FIRST_ENDL = 1;
	}else{				//打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
		way = "w+";
		FIRST_ENDL = 0;
	}
	
	f = fopen( FILE_name.c_str() ,way.c_str());
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"文件读取错误！"<<'\n'<<'\n';
		cout<<"请重进。"; 
		while(1) Sleep(1);
	}
	
	RAND(1,1);		//初始化编码 
}

void (*vd[ vd_num+1 ])() = {INI,F1,S2,T3,F4,F5,S6,S7};

int main(){
	
	INI();
	MAIN();
	
	return 0;
}

void MAIN(){
	system("cls");
	
	cout<<"随机数据生成器！！！"<<"\n\n";
	
	ll zt;
	do{
		
		cout<<"0."<<"保存并退出（数据记得拿走awa）"<<'\n'
			<<'\n'
			<<"1."<<"单/多个 随机数"<<'\n'
			<<'\n'
			<<"2."<<"随机数数组"<<'\n'
			<<'\n'
			<<"3."<<"随机字符串"<<'\n'
			<<'\n'
			<<"4."<<"仅保存"<<'\n'
			<<'\n'
			<<"5."<<"删除文件内容（慎重使用）"<<'\n'
			<<'\n'
			<<"6."<<"设置"<<'\n'
			<<'\n'
			<<"7."<<"指令功能"<<'\n'
			<<'\n';
		
		cin>>zt;
		
		if(zt < 1 || zt > 3) ENDL = 0;
		else if(FIRST_ENDL){
			ENDL = 1;
		}else{
			FIRST_ENDL = 1;
		}
			
		
		if(zt == 0)
			return;
		else if( zt >= 1 && zt <= vd_num )
			vd[zt]();
		else
			ENDL = 0;
		
		cout<<'\n';
		
		if( AnyKey ) system("pause");		//判断是否需要暂停（任意键） 
		
		system("cls");
		
	}while(1 && cout<<"还有要添加的数据吗？（记得及时取走哦awa）"<<"\n\n");
	
	fclose(f);
}

void F1(){
	
	ll groups_num,num;
	vector<ll> a_min,a_max;
	bool zt,t = 0;
	char word;
	
	while(1){
		system("cls");
		
		cout<<"需要几组随机数（输入0退出）：" <<'\n';
		cin>>groups_num;
		if(!groups_num){
			ENDL = 0;
			return;
		}
		cout<<"每组几个随机数：" <<'\n';
		cin>>num;
		
		ll t;
		for(ll i = 1;i <= num;++i){
			cout<<"每组"<<"第 "<<i<<" 个"<<"数字："<<'\n';
			cout<<"最小值："<<'\n';
			cin>>t;
			a_min.push_back(t);
			cout<<"最大值："<<'\n';
			cin>>t;
			a_max.push_back(t);
			
			if(pd_Error(a_min[a_min.size()-1] > a_max[a_max.size()-1])){
				a_min.pop_back();
				a_max.pop_back();
				i--;
				continue;
			}
			
		}
		
		cout<<"用空格“ ”隔开还是换行“\\n”（0 or 1）："<<'\n'; 
		cin>>zt;
		
		cout<<"确定吗（1 or 0）？"<<'\n';
		cin>>t;
		if(!t){
			a_min.clear();
			a_max.clear();
		}else break;
	}
	
	if(groups_num*num >= 1e6) cout<<'\n'<<"——时间可能略长，请耐心等待——"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	SET_ENDL();
	
	vector< vector<ll> > a =  rand_num(groups_num,num,a_min,a_max);
	
	fprintf(f,"%lld",a[0][0]);
	for(ll j = 1; j < num; ++j) fprintf(f," %lld",a[0][j]);
	for(ll i = 1; i < groups_num; ++i){
		fprintf(f,"%c",word);
		fprintf(f,"%lld",a[i][0]);
		for(ll j = 1; j < num; ++j) fprintf(f," %lld",a[i][j]);
	}
	
	/*---------指令区---------*/
	vector<int> cmds;
	cmds.push_back(1);
	cmds.push_back(groups_num);
	cmds.push_back(num);
	
	for(int i=0;i<a_min.size();++i){
		cmds.push_back(a_min[i]);
		cmds.push_back(a_max[i]);
	}
	
	cmds.push_back(zt);
	cmds.push_back(1);
	
	SET_cmds( cmds );
	/*------------------------*/
}

void S2(){
	int zt;
	
	do{
		system("cls");
		cout<<"0."<<"返回主界面"<<'\n'
			<<'\n'
			<<"1."<<"不重复数组"<<'\n'
			<<'\n'
			<<"2."<<"随机有序数组"<<'\n'
			<<'\n';
		cin>>zt;
		
		switch(zt){
			case 1:{
				S2_1();
				return;
			}
			case 2:{
				S2_2();
				return;
			}
			case 0:{
				ENDL = 0;
				return;
			}
			default:{
				
				break;
			}
		}
	}while(1);
	
}

void S2_1(){
	ll a_max = 11,a_min = 45,num = 14;
	bool zt,ok = 0;
	char word;
	
	while(!ok){
		system("cls");
		
		cout<<"需要多少个随机数（-1默认为(max-min+1)个数）："<<'\n';
		cin>>num; 
		cout<<"最小值："<<'\n';
		cin>>a_min;
		cout<<"最大值："<<'\n';
		cin>>a_max;
		
		if(num == -1) num = a_max-a_min+1;
		if(pd_Error((a_max-a_min+1) < num) || num <= 0 || pd_Error(a_max < a_min)) continue;
		
		cout<<"用空格“ ”隔开还是换行“\\n”（0 or 1）："<<'\n'; 
		cin>>zt;
		
		cout<<"确认吗（1 or 0）？"<<'\n';
		cin>>ok;
		
	}
	
	if(num >= 1e5) cout<<'\n'<<"——时间可能略长，请耐心等待——"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	SET_ENDL();
	
	vector<ll> a = rand_no_repeat_vector(a_min,a_max,num);
	fprintf(f,"%lld",a[0]);
	for(ll i = 1; i < num; ++i) fprintf(f,"%c%lld",word,a[i]);
	
	/*---------指令区---------*/
	vector<int> cmds;
	cmds.push_back(2);
	cmds.push_back(1);
	
	cmds.push_back(num);
	cmds.push_back(a_min);
	cmds.push_back(a_max);
	
	cmds.push_back(zt);
	cmds.push_back(1);
	
	SET_cmds( cmds );
	/*------------------------*/
}

void S2_2(){
	ll a_min,a_max,num;
	bool repeat, sort_way;	//是否重复，排序方式（0为升序，1为降序）
	char word;
	bool zt,ok = 0;
	
	while(!ok){
		system("cls");
		
		cout<<"排序方式为（0为升序，1为降序）："<<'\n';
		cin>>sort_way;
		cout<<"是否允许数字重复（1 or 0）："<<'\n';
		cin>>repeat;
		cout<<"需要多少个随机数："<<'\n';
		cin>>num;
		cout<<"最小值："<<'\n';
		cin>>a_min;
		cout<<"最大值："<<'\n';
		cin>>a_max;
		
		if( pd_Error(!repeat && (a_max-a_min+1)<num) || num <= 0 || pd_Error(a_max < a_min)) continue;
		
		cout<<"用空格“ ”隔开还是换行“\\n”（0 or 1）："<<'\n'; 
		cin>>zt;
		
		cout<<"确认吗（1 or 0）？"<<'\n';
		cin>>ok;
		
	}
	
	if(num >= 1e6) cout<<'\n'<<"——时间可能略长，请耐心等待——"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	SET_ENDL();
	
	vector<ll> a = rand_sort_vector(a_min,a_max,num,repeat,sort_way);
	fprintf(f,"%lld",a[0]);
	for(int i=1;i<a.size();++i) fprintf(f,"%c%lld",word,a[i]); 
	
	/*---------指令区---------*/
	vector<int> cmds;
	cmds.push_back(2);
	cmds.push_back(2);
	 
	cmds.push_back(sort_way);
	cmds.push_back(repeat); 
	
	cmds.push_back(num);
	cmds.push_back(a_min);
	cmds.push_back(a_max);
	
	cmds.push_back(zt);
	cmds.push_back(1);
	
	SET_cmds( cmds );
	/*------------------------*/
}

void T3(){
	ll a_min,a_max,num;
	char word;
	bool zt,ok = 0;
	string rd_words;
	string words[4] = {"abcdefghijklmnopqrstuvwxyz",			//26个 
					   "ABCDEFGHIJKLMNOPQRSTUVWXYZ",			//26个 
					   "0123456789",							//10个 
					   "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};	//32个
					   //共 94 个
	bool need_use[4] = {};
	
	while(!ok){
		system("cls");
		
		ll tmp;
		memset(need_use,0,sizeof(need_use));
		
		cout<<"字符串里需要包含哪种字符（输入0退出，-1结束读取）："<<'\n'
			<<'\n'
			<<"1."<<"小写字母"<<'\n'
			<<'\n'
			<<"2."<<"大写字母"<<'\n'
			<<'\n'
			<<"3."<<"数字"<<'\n'
			<<'\n'
			<<"4.特殊字符（半角字符且可见）"<<'\n'
			<<'\n';
		
		while(cin>>tmp && tmp != -1){
			if(tmp == 0){
				ENDL = 0;
				return;
			}
			
			if( pd_Error( tmp < 1 || tmp > 4 ) ) continue;
			
			need_use[ tmp-1 ] = 1;
			ok = 1;
			
		}
		if(!ok){
			continue;
		}
		
		ok = 0;
		
		cout<<"字符串的最小长度："<<'\n';
		cin>>a_min;
		cout<<"字符串的最大长度："<<'\n';
		cin>>a_max;
		if( pd_Error( a_max < a_min || a_min<1 || a_max<1 ) ) continue;
		
		cout<<"需要几个这样的字符串："<<'\n';
		cin>>num;
		if( pd_Error(num < 1) ) continue;
		
		cout<<"用空格“ ”隔开还是换行“\\n”（0 or 1）："<<'\n'; 
		cin>>zt;
		
		
		rd_words = "";
		for(int i = 0; i < 4; ++i){
			if(need_use[i]) rd_words += words[i];
		}
		cout<<'\n'<<"总共为这些字符："<<'\n';
		cout<<rd_words<<'\n';
		cout<<"确定吗（1 or 0）？"<<'\n';
		cin>>ok;
		
	}
	
	if(zt) word = '\n';
	else word = ' ';
	
	SET_ENDL();
	
	vector<string> a = rand_strings(a_min,a_max,num,rd_words);
	fprintf(f,"%s",a[0].c_str());
	for(ll i = 1; i < num; ++i) fprintf(f,"%c%s",word,a[i].c_str());
	
	/*---------指令区---------*/
	vector<int> cmds;
	cmds.push_back(3);
	
	for(int i=0;i<4;++i){
		if(need_use[i]) cmds.push_back(i+1);
	}
	cmds.push_back(-1);
	
	cmds.push_back(a_min);
	cmds.push_back(a_max);
	cmds.push_back(num);
	
	cmds.push_back(zt);
	cmds.push_back(1);
	
	SET_cmds( cmds );
	/*------------------------*/
}

void F4(){
	fclose(f);
	f = fopen( FILE_name.c_str() ,"a+");
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"文件读取错误！"<<'\n'<<'\n';
		while(1) Sleep(500);
	}
}

void F5(){
	
	bool zt;
	cout<<"确定吗(数据无价，请三思！！！)（1 or 0）？"<<'\n';
	cin>>zt;
	if(!zt){
		ENDL = 0;
		return;
	}
	
	fclose(f);
	f = fopen( FILE_name.c_str() ,"w+");
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"文件读取错误！"<<'\n'<<'\n';
		while(1) Sleep(500);
	}
}

void S6(){
	
	vector<IorS> values = GET_file_values();
	
	int zt = 114514;
	int word_len = 20;	//字符间隔距离 
	while(zt){
		
		system("cls");
		cout<<"设置选项："<<'\n'
			<<'\n'
			<<"0."<<"保存设置&&退出"<<'\n'
			<<'\n'
			<<"1."<<"随机生成器编码" <<'\t'<<  setw( word_len )  <<"当前状态：" << values[0].a_int <<'\n'
			<<'\n'
			<<"2."<<"随机种子" <<'\t'<<'\t'<<  setw( word_len )  <<"当前状态：" << values[1].a_int << "（-1表示为当前时间time(0)）" << '\n'
			<<'\n'
			<<"3."<<"文件读取方式" <<'\t'<<'\t'<< setw( word_len )  <<"当前状态：" << values[2].a_int <<'\n'
			<<'\n'
			<<"4."<<"文件名" <<'\t'<<'\t'<<  setw( word_len )  <<"当前状态：" << values[3].a_str <<'\n'
			<<'\n'
			<<"5."<<"操作后是否暂停" <<'\t'<<  setw( word_len )  <<"当前状态：" << values[4].a_int <<'\n'
			<<'\n';
		
		cin>>zt;
		if(zt == 0) break;
		
		switch(zt){
			case 1:{
				int tmp;
				cout<<"要改变其值为：";
				cin>>tmp;
				if( pd_Error(tmp<0 || tmp>6) ) break;
				values[0].a_int = tmp;
				break;
			}
			case 2:{
				ll tmp;
				cout<<"要改变其值为：";
				cin>>tmp;
				values[1].a_int = tmp;
				break;
			}
			case 3:{
				bool tmp;
				cout<<"要改变其状态吗（1 or 0）：";
				cin>>tmp;
				
				if(tmp) values[2].a_int = !values[2].a_int;
				
				break;
			}
			case 4:{
				string tmp;
				cout<<"要将文件重命名为（直接回车视为退出）：";
				getline(cin,tmp);	//去缓冲区的回车符'\n' 
				getline(cin,tmp);
				if(tmp == "" || tmp == "\n") break;
				
				if(tmp[ tmp.size()-1 ] == '\n') tmp = tmp.substr(0,tmp.size()-1);	//去末尾回车符'\n' 
				values[3].a_str = tmp;
				
				break;
			}
			case 5:{
				bool tmp;
				cout<<"要改变其状态吗（1 or 0）：";
				cin>>tmp;
				
				if(tmp) values[4].a_int = !values[4].a_int;
				
				break;
			} 
		}
		
		cout<<'\n';
		if(AnyKey) system("pause");
		
	}
	
	//保存设置_代码
	SET_file_values( values,"设置.ini" );
	//刷新设置
	FILE_INI();
	
	ENDL = 0;
	
}

void S7(){
	
	int zt;
	do{
		system("cls");
		
		cout<<"指令功能："<<'\n'
			<<'\n'
			<<"0."<<"退出"<<'\n'
			<<'\n'
			<<"1."<<"提取指令"<<'\n'
			<<'\n'
			<<"2."<<"调用指令"<<'\n'
			<<'\n';
		cin>>zt;
		
		switch(zt){
			case 1:{
				S7_1(); 
				break;
			}
			case 2:{
				S7_2();
				break;
			}
			case 0:{
				return;
			}
		}
		
		
	}while(1);
	
	ENDL = 0;
	
}

void S7_1(){
	bool OK = SET_FILE_cmds( "cmds.txt" ); 
	if(OK){
		cout<<"提取成功！！！"<<'\n'
			<<"请及时到“cmds.txt”获取指令awa。"<<'\n';
		Sleep(1500);
		return; 
	}else{
		cout<<"EMPTY!!"<<'\n';
		cout<<"不好意思，您还什么也没做哦。尝试去做点事情吧awa！"<<'\n';
		Sleep(1000);
		return;
	}
}

void S7_2(){
	cout<<"功能暂未开发awa"<<'\n';
	Sleep(1000);
}
