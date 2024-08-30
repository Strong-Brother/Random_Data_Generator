/*

������Ҫ�� ��������� �� �������

*/
#include "FILE.h" 
#define ll long long
using namespace std;

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

RAND_1 RAND_1;
RAND_2 RAND_2;

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



//ע������Ϊ����������ɺ��� (rand_functions)

vector< vector<ll> > rand_num(ll groups_num, ll num, vector<ll> a_min, vector<ll> a_max){
	vector< vector<ll> > a;
	
	for(ll i = 0; i < groups_num; ++i){
		vector<ll> tmp;
		for(ll j = 0; j < num; ++j){
			
			tmp.push_back( RAND(a_min[j],a_max[j]) );
			
		}
		a.push_back(tmp);
	}
	
	return a;
}

vector<ll> rand_no_repeat_vector(ll a_min,ll a_max,ll num = -1){
	if(num == -1) num = a_max-a_min+1;
	
	vector<ll>a;
	for(ll i = a_min; i <= a_max; ++i) a.push_back(i);
	shuffle(a.begin(),a.end(),rd);
	
	ll tmp = a.size();
	while(num < tmp){
		tmp--;
		a.pop_back();
	}
	
	return a;
}

vector<ll> rand_sort_vector(ll a_min,ll a_max,ll num, bool repeat,bool sort_way = 0){	//repeat:�����Ƿ�����ظ���sort_way:0Ϊ����1Ϊ����
	vector<ll>a;
	if(repeat){		//�����ظ�
		for(int i=1;i<=num;++i){
			a.push_back( RAND(a_min,a_max) );
		}
		sort(a.begin(),a.end());
		if(sort_way) reverse(a.begin(),a.end());	//���Ϊ������ת������
	}else{			//�������ظ�
		a = rand_no_repeat_vector(a_min,a_max,num);
		sort(a.begin(),a.end());
		if(sort_way) reverse(a.begin(),a.end());	//ͬ��
	}
	
	return a; 
}

vector<string> rand_strings(ll s_min,ll s_max,ll num,string rd_words){
	vector<string> a;
	string s;
	ll len,rd_len = rd_words.size();
	
	s = "";
	len = RAND(s_min,s_max);
	while(len--) s += rd_words[ RAND(0,rd_len-1) ];
	a.push_back(s);
	for(ll i = 1; i < num; ++i){
		s = "";
		len = RAND(s_min,s_max);
		while(len--) s += rd_words[ RAND(0,rd_len-1) ];
		a.push_back(s);
	}
	
	return a;
}


#undef ll
