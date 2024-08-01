#include<bits/stdc++.h>
#define ll long long
using namespace std;

FILE *f;
mt19937_64 rd(time(0));
bool ENDL = 0,OK = 1;

ll RAND(ll a_min,ll a_max){
	ll a = rd();
	a = a % (a_max-a_min+1);
	a = abs(a);
	a += a_min;
	return a;
}

void MAIN();
void F1();
void S2();
void S2_1(),S2_2();
void T3();

int main(){
	
	f = fopen("输出文件.txt","w+");

	//cout<<rd()<<' '<<rd()<<' '<<rd()<<'\n';
	//cout<<RAND(1,50000)<<' '<<RAND(1,9000000000000000000)<<'\n';
	
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
			<<"3."<<"随机字符串"<<'\n';
		
		cin>>zt;
		
		if(ENDL && OK && zt >= 1 && zt <= 3) fprintf(f,"\n");
		else{
			ENDL = 1;
			OK = 1;
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
		if(!num_1) return;
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
	
	if(zt) word = '\n';
	else word = ' ';
	
	do{
		fprintf(f,"%lld",RAND(a_min[0],a_max[0]));
		for(ll i = 1;i < num_2;++i) fprintf(f," %lld",RAND(a_min[i],a_max[i]));
	}while(--num_1 && fprintf(f,"%c",word));
	
}

void S2(){
	int zt;
	
	do{
		system("cls");
		cout<<"0."<<"返回主界面"<<'\n'
			<<"1."<<"不重复数组（(max-min+1)个数）"<<'\n'
			<<"2."<<"不重复数组（N个数）"<<'\n';
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
				OK = 0;
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
	vector<ll>a;
	bool zt,ok = 0;
	
	while(!ok){
		system("cls");
		
		cout<<"最小值："<<'\n';
		cin>>a_min;
		cout<<"最大值："<<'\n';
		cin>>a_max;
		cout<<"用空格“ ”隔开还是换行“\\n”（0 or 1）："<<'\n'; 
		cin>>zt;
		
		cout<<"确认吗（1 or 0）？"<<'\n';
		cin>>ok;
		
	}
	
	if(zt) word = '\n';
	else word = ' ';
	
	for(ll i = a_min; i <= a_max; ++i) a.push_back(i);
	shuffle(a.begin(),a.end(),rd);
	
	fprintf(f,"%lld",a[0]);
	for(ll i = 1; i < a.size(); ++i) fprintf(f,"%c%lld",word,a[i]);
	
}

void S2_2(){
	
}

void T3(){
	cout<<"子界面3"<<'\n';
}
