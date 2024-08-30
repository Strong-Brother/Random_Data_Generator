/*

这里主要放 随机生成器 和 随机函数

*/
#include "FILE.h" 
#define ll long long
using namespace std;

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

RAND_1 RAND_1;
RAND_2 RAND_2;

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



//注：以下为随机数据生成函数 (rand_functions)

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

vector<ll> rand_sort_vector(ll a_min,ll a_max,ll num, bool repeat,bool sort_way = 0){	//repeat:数字是否可以重复；sort_way:0为升序，1为降序
	vector<ll>a;
	if(repeat){		//可以重复
		for(int i=1;i<=num;++i){
			a.push_back( RAND(a_min,a_max) );
		}
		sort(a.begin(),a.end());
		if(sort_way) reverse(a.begin(),a.end());	//如果为降序，则反转该数组
	}else{			//不可以重复
		a = rand_no_repeat_vector(a_min,a_max,num);
		sort(a.begin(),a.end());
		if(sort_way) reverse(a.begin(),a.end());	//同上
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
