#include "RAND.h"

#define ll long long
using namespace std;

FILE *f;
const int vd_num = 7;		//�����ĸ��� 
bool ENDL;	//�����ļ�������з�'\n'��1Ϊ�����0Ϊ����� 
bool FIRST_ENDL;	//���Ƶ�һ���ļ����� 

bool pd_Error(bool pd){
	if(pd){
		cout<<'\n'<<"�����������������"<<'\n'<<'\n';
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

void INI(){		//��ʼ�� 
	
	FILE_INI();
	
	string way;
	if(FILE_way){		//�Ը��ӷ�ʽ�򿪿ɶ�д���ļ������ļ������ڣ���Ὠ�����ļ�������ļ����ڣ�д������ݻᱻ�ӵ��ļ�β�󣬼��ļ�ԭ�ȵ����ݻᱻ��������ԭ����EOF����������
		way = "a+";
		FIRST_ENDL = 1;
	}else{				//�򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ���
		way = "w+";
		FIRST_ENDL = 0;
	}
	
	f = fopen( FILE_name.c_str() ,way.c_str());
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"�ļ���ȡ����"<<'\n'<<'\n';
		cout<<"���ؽ���"; 
		while(1) Sleep(1);
	}
	
	RAND(1,1);		//��ʼ������ 
}

void (*vd[ vd_num+1 ])() = {INI,F1,S2,T3,F4,F5,S6,S7};

int main(){
	
	INI();
	MAIN();
	
	return 0;
}

void MAIN(){
	system("cls");
	
	cout<<"�������������������"<<"\n\n";
	
	ll zt;
	do{
		
		cout<<"0."<<"���沢�˳������ݼǵ�����awa��"<<'\n'
			<<'\n'
			<<"1."<<"��/��� �����"<<'\n'
			<<'\n'
			<<"2."<<"���������"<<'\n'
			<<'\n'
			<<"3."<<"����ַ���"<<'\n'
			<<'\n'
			<<"4."<<"������"<<'\n'
			<<'\n'
			<<"5."<<"ɾ���ļ����ݣ�����ʹ�ã�"<<'\n'
			<<'\n'
			<<"6."<<"����"<<'\n'
			<<'\n'
			<<"7."<<"ָ���"<<'\n'
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
		
		if( AnyKey ) system("pause");		//�ж��Ƿ���Ҫ��ͣ��������� 
		
		system("cls");
		
	}while(1 && cout<<"����Ҫ��ӵ������𣿣��ǵü�ʱȡ��Ŷawa��"<<"\n\n");
	
	fclose(f);
}

void F1(){
	
	ll groups_num,num;
	vector<ll> a_min,a_max;
	bool zt,t = 0;
	char word;
	
	while(1){
		system("cls");
		
		cout<<"��Ҫ���������������0�˳�����" <<'\n';
		cin>>groups_num;
		if(!groups_num){
			ENDL = 0;
			return;
		}
		cout<<"ÿ�鼸���������" <<'\n';
		cin>>num;
		
		ll t;
		for(ll i = 1;i <= num;++i){
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
	
	if(groups_num*num >= 1e6) cout<<'\n'<<"����ʱ������Գ��������ĵȴ�����"<<'\n';
	
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
	
	/*---------ָ����---------*/
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
		cout<<"0."<<"����������"<<'\n'
			<<'\n'
			<<"1."<<"���ظ�����"<<'\n'
			<<'\n'
			<<"2."<<"�����������"<<'\n'
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
		
		cout<<"��Ҫ���ٸ��������-1Ĭ��Ϊ(max-min+1)��������"<<'\n';
		cin>>num; 
		cout<<"��Сֵ��"<<'\n';
		cin>>a_min;
		cout<<"���ֵ��"<<'\n';
		cin>>a_max;
		
		if(num == -1) num = a_max-a_min+1;
		if(pd_Error((a_max-a_min+1) < num) || num <= 0 || pd_Error(a_max < a_min)) continue;
		
		cout<<"�ÿո� ���������ǻ��С�\\n����0 or 1����"<<'\n'; 
		cin>>zt;
		
		cout<<"ȷ����1 or 0����"<<'\n';
		cin>>ok;
		
	}
	
	if(num >= 1e5) cout<<'\n'<<"����ʱ������Գ��������ĵȴ�����"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	SET_ENDL();
	
	vector<ll> a = rand_no_repeat_vector(a_min,a_max,num);
	fprintf(f,"%lld",a[0]);
	for(ll i = 1; i < num; ++i) fprintf(f,"%c%lld",word,a[i]);
	
	/*---------ָ����---------*/
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
	bool repeat, sort_way;	//�Ƿ��ظ�������ʽ��0Ϊ����1Ϊ����
	char word;
	bool zt,ok = 0;
	
	while(!ok){
		system("cls");
		
		cout<<"����ʽΪ��0Ϊ����1Ϊ���򣩣�"<<'\n';
		cin>>sort_way;
		cout<<"�Ƿ����������ظ���1 or 0����"<<'\n';
		cin>>repeat;
		cout<<"��Ҫ���ٸ��������"<<'\n';
		cin>>num;
		cout<<"��Сֵ��"<<'\n';
		cin>>a_min;
		cout<<"���ֵ��"<<'\n';
		cin>>a_max;
		
		if( pd_Error(!repeat && (a_max-a_min+1)<num) || num <= 0 || pd_Error(a_max < a_min)) continue;
		
		cout<<"�ÿո� ���������ǻ��С�\\n����0 or 1����"<<'\n'; 
		cin>>zt;
		
		cout<<"ȷ����1 or 0����"<<'\n';
		cin>>ok;
		
	}
	
	if(num >= 1e6) cout<<'\n'<<"����ʱ������Գ��������ĵȴ�����"<<'\n';
	
	if(zt) word = '\n';
	else word = ' ';
	
	SET_ENDL();
	
	vector<ll> a = rand_sort_vector(a_min,a_max,num,repeat,sort_way);
	fprintf(f,"%lld",a[0]);
	for(int i=1;i<a.size();++i) fprintf(f,"%c%lld",word,a[i]); 
	
	/*---------ָ����---------*/
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
	string words[4] = {"abcdefghijklmnopqrstuvwxyz",			//26�� 
					   "ABCDEFGHIJKLMNOPQRSTUVWXYZ",			//26�� 
					   "0123456789",							//10�� 
					   "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"};	//32��
					   //�� 94 ��
	bool need_use[4] = {};
	
	while(!ok){
		system("cls");
		
		ll tmp;
		memset(need_use,0,sizeof(need_use));
		
		cout<<"�ַ�������Ҫ���������ַ�������0�˳���-1������ȡ����"<<'\n'
			<<'\n'
			<<"1."<<"Сд��ĸ"<<'\n'
			<<'\n'
			<<"2."<<"��д��ĸ"<<'\n'
			<<'\n'
			<<"3."<<"����"<<'\n'
			<<'\n'
			<<"4.�����ַ�������ַ��ҿɼ���"<<'\n'
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
	
	SET_ENDL();
	
	vector<string> a = rand_strings(a_min,a_max,num,rd_words);
	fprintf(f,"%s",a[0].c_str());
	for(ll i = 1; i < num; ++i) fprintf(f,"%c%s",word,a[i].c_str());
	
	/*---------ָ����---------*/
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
		cout<<"ERROR!!!"<<'\n'<<"�ļ���ȡ����"<<'\n'<<'\n';
		while(1) Sleep(500);
	}
}

void F5(){
	
	bool zt;
	cout<<"ȷ����(�����޼ۣ�����˼������)��1 or 0����"<<'\n';
	cin>>zt;
	if(!zt){
		ENDL = 0;
		return;
	}
	
	fclose(f);
	f = fopen( FILE_name.c_str() ,"w+");
	if(f == NULL){
		cout<<"ERROR!!!"<<'\n'<<"�ļ���ȡ����"<<'\n'<<'\n';
		while(1) Sleep(500);
	}
}

void S6(){
	
	vector<IorS> values = GET_file_values();
	
	int zt = 114514;
	int word_len = 20;	//�ַ�������� 
	while(zt){
		
		system("cls");
		cout<<"����ѡ�"<<'\n'
			<<'\n'
			<<"0."<<"��������&&�˳�"<<'\n'
			<<'\n'
			<<"1."<<"�������������" <<'\t'<<  setw( word_len )  <<"��ǰ״̬��" << values[0].a_int <<'\n'
			<<'\n'
			<<"2."<<"�������" <<'\t'<<'\t'<<  setw( word_len )  <<"��ǰ״̬��" << values[1].a_int << "��-1��ʾΪ��ǰʱ��time(0)��" << '\n'
			<<'\n'
			<<"3."<<"�ļ���ȡ��ʽ" <<'\t'<<'\t'<< setw( word_len )  <<"��ǰ״̬��" << values[2].a_int <<'\n'
			<<'\n'
			<<"4."<<"�ļ���" <<'\t'<<'\t'<<  setw( word_len )  <<"��ǰ״̬��" << values[3].a_str <<'\n'
			<<'\n'
			<<"5."<<"�������Ƿ���ͣ" <<'\t'<<  setw( word_len )  <<"��ǰ״̬��" << values[4].a_int <<'\n'
			<<'\n';
		
		cin>>zt;
		if(zt == 0) break;
		
		switch(zt){
			case 1:{
				int tmp;
				cout<<"Ҫ�ı���ֵΪ��";
				cin>>tmp;
				if( pd_Error(tmp<0 || tmp>6) ) break;
				values[0].a_int = tmp;
				break;
			}
			case 2:{
				ll tmp;
				cout<<"Ҫ�ı���ֵΪ��";
				cin>>tmp;
				values[1].a_int = tmp;
				break;
			}
			case 3:{
				bool tmp;
				cout<<"Ҫ�ı���״̬��1 or 0����";
				cin>>tmp;
				
				if(tmp) values[2].a_int = !values[2].a_int;
				
				break;
			}
			case 4:{
				string tmp;
				cout<<"Ҫ���ļ�������Ϊ��ֱ�ӻس���Ϊ�˳�����";
				getline(cin,tmp);	//ȥ�������Ļس���'\n' 
				getline(cin,tmp);
				if(tmp == "" || tmp == "\n") break;
				
				if(tmp[ tmp.size()-1 ] == '\n') tmp = tmp.substr(0,tmp.size()-1);	//ȥĩβ�س���'\n' 
				values[3].a_str = tmp;
				
				break;
			}
			case 5:{
				bool tmp;
				cout<<"Ҫ�ı���״̬��1 or 0����";
				cin>>tmp;
				
				if(tmp) values[4].a_int = !values[4].a_int;
				
				break;
			} 
		}
		
		cout<<'\n';
		if(AnyKey) system("pause");
		
	}
	
	//��������_����
	SET_file_values( values,"����.ini" );
	//ˢ������
	FILE_INI();
	
	ENDL = 0;
	
}

void S7(){
	
	int zt;
	do{
		system("cls");
		
		cout<<"ָ��ܣ�"<<'\n'
			<<'\n'
			<<"0."<<"�˳�"<<'\n'
			<<'\n'
			<<"1."<<"��ȡָ��"<<'\n'
			<<'\n'
			<<"2."<<"����ָ��"<<'\n'
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
		cout<<"��ȡ�ɹ�������"<<'\n'
			<<"�뼰ʱ����cmds.txt����ȡָ��awa��"<<'\n';
		Sleep(1500);
		return; 
	}else{
		cout<<"EMPTY!!"<<'\n';
		cout<<"������˼������ʲôҲû��Ŷ������ȥ���������awa��"<<'\n';
		Sleep(1000);
		return;
	}
}

void S7_2(){
	cout<<"������δ����awa"<<'\n';
	Sleep(1000);
}
