#include<bits/stdc++.h>
#include<windows.h>
#define ll long long
using namespace std;

ll RAND_num = 0,random_seed = time(0),file_way = 0;		//������������룬������ӣ��ļ���ȡ��ʽ

FILE *f;
mt19937_64 rd(random_seed);
default_random_engine rd_1(random_seed);
bool ENDL;	//�����ļ�������з�'\n'��1Ϊ�����0Ϊ����� 

struct RAND_1{		//����ͬ������������� 
	ll last_rd_1 = rd();
	ll rnd(){
		ll A = 97,B = 59,P = LLONG_MAX;		//P == 10��63�η�-1��˫long�� 
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
struct RAND_2{		//ʱ��쳲����������������
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

ll RD_1(ll a_min,ll a_max){		//ԭ��������� mt19937_64 
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
ll RD_3(ll a_min,ll a_max){		//C++ԭ���� rand() 
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
			cout<<'\n'<<"��������������˳����޸Ĳ�����"<<'\n';
			while(1);
			break;
		}
	}
}

bool pd_Error(bool pd){
	if(pd){
		cout<<'\n'<<"�����������������"<<'\n'<<'\n';
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

void initialize(){		//��ʼ�� 
	
	//���á���BEGIN 
	f = fopen("����.ini","r");
	ll tmp = 114514;
	if(f == NULL){
		fclose(f);
		f = fopen("����.ini","w");
		fprintf(f,"0\n-1\n0");
		cout<<"���ڳ�ʼ���С���"<<'\n';
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
	//���á���END 
	
	srand(random_seed);
	
	string way;
	if(file_way){		//�Ը��ӷ�ʽ�򿪿ɶ�д���ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�󣬼��ļ�ԭ�ȵ����ݻᱻ��������ԭ����EOF����������
		way = "a+";
		ENDL = 1;
	}else{				//�򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
		way = "w+";
		ENDL = 0;
	}
	
	f = fopen("����ļ�.txt",way.c_str());
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"�ļ���ȡ����"<<'\n'<<'\n';
		cout<<"���ؽ���"; 
		while(1);
	}
	
	RAND(1,1);		//��ʼ������ 
} 

int main(){
	
	initialize();
	MAIN();
	
	fclose(f);
	return 0;
}

void MAIN(){
	system("cls");
	
	cout<<"�������������������"<<'\n';
	
	int zt;
	do{
		
		cout<<"0."<<"���沢�˳������ݼǵ�����awa��"<<'\n'
			<<"1."<<"��/��� �����"<<'\n'
			<<"2."<<"���������"<<'\n'
			<<"3."<<"����ַ���"<<'\n'
			<<"4."<<"������"<<'\n';
		
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
		
	}while(1 && cout<<"����Ҫ��ӵ������𣿣��ǵü�ʱȡ��Ŷawa��"<<'\n');
	
}

void F1(){
	
	ll num_1,num_2;
	vector<ll> a_min,a_max;
	bool zt,t = 0;
	char word;
	
	while(1){
		system("cls");
		
		cout<<"��Ҫ���������������0�˳�����" <<'\n';
		cin>>num_1;
		if(!num_1){
			ENDL = 0;
			return;
		}
		cout<<"ÿ�鼸���������" <<'\n';
		cin>>num_2;
		
		ll t;
		for(ll i = 1;i <= num_2;++i){
			cout<<"ÿ��"<<"�� "<<i<<" ��"<<"���֣�"<<'\n';
			cout<<"��Сֵ��"<<'\n';
			cin>>t;
			a_min.push_back(t);
			cout<<"���ֵ��"<<'\n';
			cin>>t;
			a_max.push_back(t);
			
			if(pd_Error(a_min[a_min.size()-1] > a_max[a_max.size()-1])){
				a_min.pop_back();
				a_max.pop_back();
				i--;
				continue;
			}
			
		}
		
		cout<<"�ÿո� ���������ǻ��С�\\n����0 or 1����"<<'\n'; 
		cin>>zt;
		
		cout<<"ȷ����1 or 0����"<<'\n';
		cin>>t;
		if(!t){
			a_min.clear();
			a_max.clear();
		}else break;
	}
	
	if(num_1*num_2 >= 1000000) cout<<'\n'<<"����ʱ������Գ��������ĵȴ�����"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	rand_num(num_1,num_2,word,a_min,a_max);
	
}

void S2(){
	int zt;
	
	do{
		system("cls");
		cout<<"0."<<"����������"<<'\n'
			<<"1."<<"���ظ����飨(max-min+1)������"<<'\n'
			<<"2."<<"���ظ����飨N������N <= (max-min+1)��"<<'\n';
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
		
		cout<<"��Сֵ��"<<'\n';
		cin>>a_min;
		cout<<"���ֵ��"<<'\n';
		cin>>a_max;
		
		if(pd_Error(a_min > a_max)) continue;
		
		cout<<"�ÿո� ���������ǻ��С�\\n����0 or 1����"<<'\n'; 
		cin>>zt;
		
		cout<<"ȷ����1 or 0����"<<'\n';
		cin>>ok;
		
	}
	
	if(a_max-a_min+1 >= 1000000) cout<<'\n'<<"����ʱ������Գ��������ĵȴ�����"<<'\n';
	
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
		
		cout<<"��Ҫ���ٸ��������"<<'\n';
		cin>>num;
		cout<<"��Сֵ��"<<'\n';
		cin>>a_min;
		cout<<"���ֵ��"<<'\n';
		cin>>a_max;
		
		if(pd_Error((a_max-a_min+1) < num) || num <= 0 || pd_Error(a_max < a_min)) continue;
		
		cout<<"�ÿո� ���������ǻ��С�\\n����0 or 1����"<<'\n'; 
		cin>>zt;
		
		cout<<"ȷ����1 or 0����"<<'\n';
		cin>>ok;
		
	}
	
	if(num >= 100000) cout<<'\n'<<"����ʱ������Գ��������ĵȴ�����"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	rand_no_repeat_vector_2(a_min,a_max,num,word);
	
}

void T3(){
	ll a_min,a_max,num;
	char word;
	bool zt,ok = 0;
	string rd_words;
	string words[4] = {"abcdefghijklmnopqrstuvwxyz",			//26�� 
					   "ABCDEFGHIJKLMNOPQRSTUVWXYZ",			//26�� 
					   "0123456789",							//10�� 
					   "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};	//32��
					   //�� 94 ��
	bool need_use[4] = {};
	
	while(!ok){
		system("cls");
		
		ll tmp;
		cout<<"�ַ�������Ҫ���������ַ�������0�˳���-1������ȡ����"<<'\n'
			<<"1."<<"Сд��ĸ"<<'\n'
			<<"2."<<"��д��ĸ"<<'\n'
			<<"3."<<"����"<<'\n'
			<<"4.�����ַ�������ַ��ҿɼ���"<<'\n'; 
		
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
		
		cout<<"�ַ�������С���ȣ�"<<'\n';
		cin>>a_min;
		cout<<"�ַ�������󳤶ȣ�"<<'\n';
		cin>>a_max;
		if( pd_Error( a_max < a_min || a_min<1 || a_max<1 ) ) continue;
		
		cout<<"��Ҫ�����������ַ�����"<<'\n';
		cin>>num;
		if( pd_Error(num < 1) ) continue;
		
		cout<<"�ÿո� ���������ǻ��С�\\n����0 or 1����"<<'\n'; 
		cin>>zt;
		
		
		rd_words = "";
		for(int i = 0; i < 4; ++i){
			if(need_use[i]) rd_words += words[i];
		}
		cout<<'\n'<<"�ܹ�Ϊ��Щ�ַ���"<<'\n';
		cout<<rd_words<<'\n';
		cout<<"ȷ����1 or 0����"<<'\n';
		cin>>ok;
		
	}
	
	if(zt) word = '\n';
	else word = ' ';
	
	rand_string(a_min,a_max,num,rd_words,word);
	
}

void F4(){
	fclose(f);
	f = fopen("����ļ�.txt","a+");
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"�ļ���ȡ����"<<'\n'<<'\n';
	}
	ENDL = 1;
}


//ע������Ϊ����������ɺ��� (rand_functions)

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

