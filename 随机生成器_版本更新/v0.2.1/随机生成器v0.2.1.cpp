#include<bits/stdc++.h>
#include<windows.h>
#define ll long long
using namespace std;

ll RAND_num = 0,random_seed = time(0),file_way = 0;		//随机生成器号码，随机种子，文件读取方式

FILE *f;
mt19937_64 rd(random_seed);
default_random_engine rd_1(random_seed);
bool ENDL;	//控制文件输出换行符'\n'，1为输出，0为不输出 

struct RAND_1{		//线性同余随机数生成器 
	ll last_rd_1 = rd();
	ll rnd(){
		ll A = 97,B = 59,P = LLONG_MAX;		//P == 10的63次方-1（双long） 
		last_rd_1 = (last_rd_1 * A + B) % P;
		return last_rd_1;
	}
	ll rd_1(ll a_min,ll a_max){
		ll a = rnd();
		a = a % (a_max-a_min+1);
		a = abs(a);
		a += a_min;
		return a;
	}
};
struct RAND_2{		//时滞斐波那契随机数生成器
	ll l,j,k;
	ll now,ans;
	vector<ll>v;
	
	RAND_2(){
		j = 11;
		l = 45;
		k = 14;
		for(ll i = 0;i < l;++i) v.push_back(rd());
		now = max(j,k)+1;
	}
	
	ll rnd(){
		ans = (v[now-j] * v[now-k]) % LLONG_MAX;
		v.push_back(ans);
		++now;
		
		if(rd() % 15 == 0){
			v.clear();
			j = rd()%50+1;
			k = rd()%50+1;
			l = (j+k) + (rd()%50+1);
			for(ll i = 0;i < l;++i) v.push_back(rd());
			now = max(j,k)+1;
		}
		
		return ans;
	}
	
	ll rd_2(ll a_min,ll a_max){
		ll a = rnd();
		a = a % (a_max-a_min+1);
		a = abs(a);
		a += a_min;
		return a;
	}
	
};

ll RD_1(ll a_min,ll a_max){		//原随机生成器 mt19937_64 
	ll a = rd();
	a = a % (a_max-a_min+1);
	a = abs(a);
	a += a_min;
	return a;
}
ll RD_2(ll a_min,ll a_max){		//default_random_engine
	ll a = rd_1();
	a = a % (a_max-a_min+1);
	a = abs(a);
	a += a_min;
	return a;
}
ll RD_3(ll a_min,ll a_max){		//C++原函数 rand() 
	ll a = rand();
	a = a % (a_max-a_min+1);
	a = abs(a);
	a += a_min;
	return a;
}
ll RD_4(ll a_min,ll a_max){		//uniform_int_distribution + mt19937_64
	uniform_int_distribution<ll> a(a_min,a_max);
	return a(rd);
}
ll RD_5(ll a_min,ll a_max){		//uniform_int_distribution + default_random_engine
	uniform_int_distribution<ll> a(a_min,a_max);
	return a(rd_1);
}

RAND_1 RAND_1;
RAND_2 RAND_2;

ll RAND(auto a_min,auto a_max,int rand_num = RAND_num){
	
	switch(rand_num){
		case 0:{
			return RD_1(a_min,a_max);
		}
		case 1:{
			return RD_2(a_min,a_max);
		}
		case 2:{
			return RD_3(a_min,a_max);
		}
		case 3:{
			return RD_4(a_min,a_max);
		}
		case 4:{
			return RD_5(a_min,a_max);
		}
		case 5:{
			return RAND_1.rd_1(a_min,a_max);
		}
		case 6:{
			return RAND_2.rd_2(a_min,a_max); 
		}
		default:{
			cout<<'\n'<<"传入参数错误，请退出并修改参数。"<<'\n';
			while(1);
			break;
		}
	}
}

bool pd_Error(bool pd){
	if(pd){
		cout<<'\n'<<"输入错误，请重新输入"<<'\n'<<'\n';
		Sleep(500);
		return 1;
	}
	return 0;
	
}

void MAIN();
void F1();
void S2();
void S2_1(),S2_2();
void T3();
void F4();

void rand_num(ll,ll,char,vector<ll>,vector<ll>);
void rand_no_repeat_vector_1(ll,ll,char);
void rand_no_repeat_vector_2(ll,ll,ll,char);
void rand_string(ll,ll,ll,string,char);

void initialize(){		//初始化 
	
	//设置——BEGIN 
	f = fopen("设置.ini","r");
	ll tmp = 114514;
	if(f == NULL){
		fclose(f);
		f = fopen("设置.ini","w");
		fprintf(f,"0\n-1\n0");
		cout<<"正在初始化中……"<<'\n';
		Sleep(500);
	}
	else for(ll i = 1; i <= 3; ++i){
		
		fscanf(f,"%lld",&tmp);
		cout<<tmp<<' '; 
		
		switch(i){
			case 1:{
				RAND_num = tmp;
				break;
			}
			case 2:{
				if(tmp == -1) random_seed = time(0);
				else random_seed = tmp;
				break;
			}
			case 3:{
				if(tmp) tmp = 1;
				file_way = tmp;
				break;
			}
		}
		
	}
	fclose(f);
	//设置——END 
	
	srand(random_seed);
	
	string way;
	if(file_way){		//以附加方式打开可读写的文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾后，即文件原先的内容会被保留。（原来的EOF符不保留）
		way = "a+";
		ENDL = 1;
	}else{				//打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
		way = "w+";
		ENDL = 0;
	}
	
	f = fopen("输出文件.txt",way.c_str());
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"文件读取错误！"<<'\n'<<'\n';
		cout<<"请重进。"; 
		while(1);
	}
	
	RAND(1,1);		//初始化编码 
} 

int main(){
	
	initialize();
	MAIN();
	
	fclose(f);
	return 0;
}

void MAIN(){
	system("cls");
	
	cout<<"随机数据生成器！！！"<<'\n';
	
	int zt;
	do{
		
		cout<<"0."<<"保存并退出（数据记得拿走awa）"<<'\n'
			<<"1."<<"单/多个 随机数"<<'\n'
			<<"2."<<"随机数数组"<<'\n'
			<<"3."<<"随机字符串"<<'\n'
			<<"4."<<"仅保存"<<'\n';
		
		cin>>zt;
		
		if(ENDL && zt >= 1 && zt <= 3) fprintf(f,"\n");
		else{
			ENDL = 1;
		}
		
		switch(zt){
			case 1:{
				F1();
				break;
			}
			case 2:{
				S2();
				break;
			}
			case 3:{
				T3();
				break;
			}
			case 4:{
				F4();
				break;
			}
			case 0:{
				return;
			}
			default:{
				zt = 0;
				break;
			}
		}
		
		cout<<'\n';
		system("pause");
		system("cls");
		
	}while(1 && cout<<"还有要添加的数据吗？（记得及时取走哦awa）"<<'\n');
	
}

void F1(){
	
	ll num_1,num_2;
	vector<ll> a_min,a_max;
	bool zt,t = 0;
	char word;
	
	while(1){
		system("cls");
		
		cout<<"需要几组随机数（输入0退出）：" <<'\n';
		cin>>num_1;
		if(!num_1){
			ENDL = 0;
			return;
		}
		cout<<"每组几个随机数：" <<'\n';
		cin>>num_2;
		
		ll t;
		for(ll i = 1;i <= num_2;++i){
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
	
	if(num_1*num_2 >= 1000000) cout<<'\n'<<"——时间可能略长，请耐心等待——"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	rand_num(num_1,num_2,word,a_min,a_max);
	
}

void S2(){
	int zt;
	
	do{
		system("cls");
		cout<<"0."<<"返回主界面"<<'\n'
			<<"1."<<"不重复数组（(max-min+1)个数）"<<'\n'
			<<"2."<<"不重复数组（N个数，N <= (max-min+1)）"<<'\n';
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
	ll a_min,a_max;
	char word;
	bool zt,ok = 0;
	
	while(!ok){
		system("cls");
		
		cout<<"最小值："<<'\n';
		cin>>a_min;
		cout<<"最大值："<<'\n';
		cin>>a_max;
		
		if(pd_Error(a_min > a_max)) continue;
		
		cout<<"用空格“ ”隔开还是换行“\\n”（0 or 1）："<<'\n'; 
		cin>>zt;
		
		cout<<"确认吗（1 or 0）？"<<'\n';
		cin>>ok;
		
	}
	
	if(a_max-a_min+1 >= 1000000) cout<<'\n'<<"——时间可能略长，请耐心等待——"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	rand_no_repeat_vector_1(a_min,a_max,word);
	
}

void S2_2(){
	ll a_max = 11,a_min = 45,num = 14;
	bool zt,ok = 0;
	char word;
	
	while(!ok){
		system("cls");
		
		cout<<"需要多少个随机数："<<'\n';
		cin>>num;
		cout<<"最小值："<<'\n';
		cin>>a_min;
		cout<<"最大值："<<'\n';
		cin>>a_max;
		
		if(pd_Error((a_max-a_min+1) < num) || num <= 0 || pd_Error(a_max < a_min)) continue;
		
		cout<<"用空格“ ”隔开还是换行“\\n”（0 or 1）："<<'\n'; 
		cin>>zt;
		
		cout<<"确认吗（1 or 0）？"<<'\n';
		cin>>ok;
		
	}
	
	if(num >= 100000) cout<<'\n'<<"——时间可能略长，请耐心等待——"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	rand_no_repeat_vector_2(a_min,a_max,num,word);
	
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
		cout<<"字符串里需要包含哪种字符（输入0退出，-1结束读取）："<<'\n'
			<<"1."<<"小写字母"<<'\n'
			<<"2."<<"大写字母"<<'\n'
			<<"3."<<"数字"<<'\n'
			<<"4.特殊字符（半角字符且可见）"<<'\n'; 
		
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
	
	rand_string(a_min,a_max,num,rd_words,word);
	
}

void F4(){
	fclose(f);
	f = fopen("输出文件.txt","a+");
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"文件读取错误！"<<'\n'<<'\n';
	}
	ENDL = 1;
}


//注：以下为随机数据生成函数 (rand_functions)

void rand_num(ll groups_num,ll num,char word,vector<ll> a_min,vector<ll> a_max){
	do{
		fprintf(f,"%lld",RAND(a_min[0],a_max[0]));
		for(ll i = 1; i < num; ++i) fprintf(f," %lld",RAND(a_min[i],a_max[i]));
	}while(--groups_num && fprintf(f,"%c",word));
}

void rand_no_repeat_vector_1(ll a_min,ll a_max,char word){
	vector<ll>a;
	for(ll i = a_min; i <= a_max; ++i) a.push_back(i);
	shuffle(a.begin(),a.end(),rd);
	
	fprintf(f,"%lld",a[0]);
	for(ll i = 1; i < a.size(); ++i) fprintf(f,"%c%lld",word,a[i]);
}
void rand_no_repeat_vector_2(ll a_min,ll a_max,ll num,char word){
	vector<ll>a;
	ll tmp;
	for(ll i = a_min; i <= a_max; ++i) a.push_back(i);
	
	tmp = RAND(0,a.size()-1);
	fprintf(f,"%lld",a[tmp]);
	a.erase( a.begin()+tmp );
	for(ll i = 1; i < num; ++i){
		tmp = RAND(0,a.size()-1);
		fprintf(f,"%c%lld",word,a[tmp]);
		a.erase( a.begin()+tmp );
	}
}

void rand_string(ll a_min,ll a_max,ll num,string rd_words,char word){
	string a;
	ll len,rd_len = rd_words.size();
	
	a = "";
	len = RAND(a_min,a_max);
	while(len--) a += rd_words[ RAND(0,rd_len-1) ];
	fprintf(f,"%s",a.c_str());
	for(ll i = 1; i < num; ++i){
		a = "";
		len = RAND(a_min,a_max);
		while(len--) a += rd_words[ RAND(0,rd_len-1) ];
		fprintf(f,"%c%s",word,a.c_str());
	}
}

