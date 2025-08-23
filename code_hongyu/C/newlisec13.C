#define NUM 1000 //入射粒子数,按师兄建议一般取十万，得到能量乘积图时为了图案清晰取一万
void openandreadandtest(TGraph *thepid,double se[4][NUM],int M,char str[50],char str1[50],int _thick); //模拟粒子入射，每块板上的能量沉积结果存在二维数组se中
int getit(TGraph *f,double se[4][NUM],int AA,int ZZ,int *I,int _thick); //将se中数据存进图里
void drawit(TGraph *f); 
void empty(double se[4][NUM]);//每种粒子入射模拟完毕，并将数据存入图后，清空数组待下一次模拟

void newlisec13(){
TGraph *thepid = new TGraph();
double se[4][NUM];
TGraph *f;
f=new TGraph;
int AA=0,ZZ=0,J=0,*I;  //M为质量数，*I指向J为图的计数顺序，因为所有的要画在一张图上，所以需要一个总的顺序，因此用指针以变在函数中能改变主函数的实变
I=&J;
char str_Si[50]="/home/zhuhy/zhuhy/pid/pid_s_c/13B-Si.txt";
char str_CsI[50]="/home/zhuhy/zhuhy/pid/pid_s_c/13B-Si.txt";
_thick=5500;
AA=13;ZZ=5; openandreadandtest(thepid,se,AA,str_Si,str_CsI,_thick); //getit(f,se,AA,ZZ,I,_thick);
empty(se);
thepid->SetMarkerStyle(6);
thepid->SetMarkerColor(4);
thepid->Draw("samep");


/*
char str1H[20]="1H-Si.txt";
char str2H[20]="2H-Si.txt";
char str3H[20]="3H-Si.txt";
char str3He[20]="3He-Si.txt";
char str4He[20]="4He-Si.txt";
char str6He[20]="6He-Si.txt";
char str7Li[20]="7Li-Si.txt";
char str8Li[20]="8Li-Si.txt";
char str9Li[20]="9Li-Si.txt";
char str7Be[20]="7Be-Si.txt";
char str9Be[20]="9Be-Si.txt";
char str10Be[20]="10Be-Si.txt";
char str8B[20]="8B-Si.txt";
char str10B[20]="10B-Si.txt";
char str11B[20]="11B-Si.txt";
AA=1;ZZ=1; openandreadandtest(se,AA,str1H); getit(f,se,AA,ZZ,I); empty(se);
AA=2;ZZ=1; openandreadandtest(se,AA,str2H); getit(f,se,AA,ZZ,I); empty(se);
AA=3;ZZ=1; openandreadandtest(se,AA,str3H); getit(f,se,AA,ZZ,I); empty(se);
AA=3;ZZ=2; openandreadandtest(se,AA,str3He); getit(f,se,AA,ZZ,I); empty(se);
AA=4;ZZ=2; openandreadandtest(se,AA,str4He); getit(f,se,AA,ZZ,I); empty(se);
AA=6;ZZ=2; openandreadandtest(se,AA,str6He); getit(f,se,AA,ZZ,I); empty(se);
AA=7;ZZ=3; openandreadandtest(se,AA,str7Li); getit(f,se,AA,ZZ,I); empty(se);
AA=8;ZZ=3; openandreadandtest(se,AA,str8Li); getit(f,se,AA,ZZ,I); empty(se);
AA=9;ZZ=3; openandreadandtest(se,AA,str9Li); getit(f,se,AA,ZZ,I); empty(se);
AA=7;ZZ=4; openandreadandtest(se,AA,str7Be); getit(f,se,AA,ZZ,I); empty(se);
AA=9;ZZ=4; openandreadandtest(se,AA,str9Be); getit(f,se,AA,ZZ,I); empty(se);
AA=10;ZZ=4; openandreadandtest(se,AA,str10Be); getit(f,se,AA,ZZ,I); empty(se);
AA=8;ZZ=5; openandreadandtest(se,AA,str8B); getit(f,se,AA,ZZ,I); empty(se);
AA=10;ZZ=5; openandreadandtest(se,AA,str10B); getit(f,se,AA,ZZ,I); empty(se);
AA=11;ZZ=5; openandreadandtest(se,AA,str11B); getit(f,se,AA,ZZ,I); empty(se);
*/
/*char str20Ne[20]="20Ne-Si.txt";
char str21Ne[20]="21Ne-Si.txt";
char str22Ne[20]="22Ne-Si.txt";
char str20Na[20]="20Na-Si.txt";
char str21Na[20]="21Na-Si.txt";
char str22Na[20]="22Na-Si.txt";
char str21Mg[20]="21Mg-Si.txt";
char str22Mg[20]="22Mg-Si.txt";
char str23Mg[20]="23Mg-Si.txt";
char str22Al[20]="22Al-Si.txt";
char str23Al[20]="23Al-Si.txt";
char str22Si[20]="22Si-Si.txt";
char str23Si[20]="23Si-Si.txt";
char str24Si[20]="24Si-Si.txt";
AA=20;ZZ=10; openandreadandtest(se,AA,str20Ne);   getit(f,se,AA,ZZ,I); empty(se);
AA=21;ZZ=10; openandreadandtest(se,AA,str21Ne);   getit(f,se,AA,ZZ,I); empty(se);
A=22;ZZ=10; openandreadandtest(se,AA,str22Ne);    getit(f,se,AA,ZZ,I); empty(se);
AA=20;ZZ=11; openandreadandtest(se,AA,str20Na); getit(f,se,AA,ZZ,I); empty(se);
AA=21;ZZ=11; openandreadandtest(se,AA,str21Na); getit(f,se,AA,ZZ,I); empty(se);
AA=22;ZZ=11; openandreadandtest(se,AA,str22Na); getit(f,se,AA,ZZ,I); empty(se);
AA=21;ZZ=12; openandreadandtest(se,AA,str21Mg); getit(f,se,AA,ZZ,I); empty(se);
AA=22;ZZ=12; openandreadandtest(se,AA,str22Mg); getit(f,se,AA,ZZ,I); empty(se);
AA=23;ZZ=12; openandreadandtest(se,AA,str23Mg); getit(f,se,AA,ZZ,I); empty(se);
AA=22;ZZ=13; openandreadandtest(se,AA,str22Al); getit(f,se,AA,ZZ,I); empty(se);
AA=23;ZZ=13; openandreadandtest(se,AA,str23Al); getit(f,se,AA,ZZ,I); empty(se);
AA=22;ZZ=14; openandreadandtest(se,AA,str22Si); getit(f,se,AA,ZZ,I); empty(se);
AA=23;ZZ=14; openandreadandtest(se,AA,str23Si); getit(f,se,AA,ZZ,I); empty(se);
AA=24;ZZ=14; openandreadandtest(se,AA,str24Si); getit(f,se,AA,ZZ,I); empty(se);*/
//drawit(f);
return 0;
}

void openandreadandtest(TGraph *thepid,double se[4][NUM],int M,char str[50],char str1[50],int _thick){
TGraph *g;
ifstream in(str);
string ss;
double a, b, e, dedx;
g=new TGraph;
if(in.is_open()){
    getline(in,ss);
    int i=0;
    while(!in.eof())
    {
      in>>a>>b>>e>>dedx>>a>>b>>a>>b>>a>>b>>a>>b;
      g->SetPoint(i++, e*M,dedx); 
	}
 }


TGraph *g1;
ifstream in1(str1);
g1=new TGraph;
if(in1.is_open()){
    getline(in1,ss);
    i=0;
    while(!in1.eof())
    {
      in1>>a>>b>>e>>dedx>>a>>b>>a>>b>>a>>b>>a>>b;
      g1->SetPoint(i++, e*M,dedx);  
        }
 } 
 in1.close();
 double E0=0,E1=0,Esmall=0,E2=0,E=0,dE=0,e1=0,e2=0,e3=0,x=0,dx=0.25;//E0为能量总值，E为能量实时记录值，E1为穿透第一块硅时的能量，E2为穿透第二块时的能量
 Double_t d[3]={1000.,1504.,10000};
 //d[0]=(Double_t)(_thick);
 for(i=1;i<=2;i++)d[i]=d[i]+d[i-1];
 for(i=-1;i<NUM;x=0)   //开始NUM次模拟
 {
 if(i%200==0)cout<<i<<":"<<NUM<<'\n';
 i++;
 x=0;
// Esmall=rand()%1000;  //初始能量小数部分
 E0=E=i*500./1000.;  //能量随机值为300+3位小数
 se[3][i]=E0; 
    while(1)   //while循环即模拟粒子入射，每一个循环行进dx个步长，当能量小于零或从最后一个板射出时退出循环，开始下一次模拟
    {
    if((fabs(x-d[0])<=(dx/2)||(x>=0&&x<d[0]))&&E<=0){se[0][i]=E0;se[1][i]=0;se[2][i]=0;break;} //如果在第一块板中任何地方能量小于零，则第一块板沉积能量就是总能量，并退出本次模拟
    else if(fabs(x-d[0])<=(dx/2)&&E>0){se[0][i]=E0-E;E1=E;}    //出射第一块板时，能量为初始能量减当前能量，并记录此时能量（亦即入射第二块硅的能量）
    else if((fabs(x-d[1])<=(dx/2)||(x>d[0]&&x<d[1]))&&E<=0){se[1][i]=E1;break;}  //如果在第二块板中...
    else if(fabs(x-d[1])<=(dx/2)&&E>0){se[1][i]=E1-E;E2=E;}    //出射第二块板时...
    else if((fabs(x-d[2])>(dx/2)&&x>d[1])&&E<=0){se[2][i]=E2;E1=E2=0;break;}  //如果在第三块板中.. 
    else if(fabs(x-d[2])<=(dx/2)&&E>0){se[2][i]=E2-E;E1=E2=0;break;}   //出射第三块板时记录沉积能量，退出本次模拟
    dE=g->Eval(E);
    if(se[1][i]>0)dE=g1->Eval(E);
    E=E-dE*dx;    //每一步长计算一次能损，改变一次能量
    x=x+dx;
    }
 thepid->SetPoint(i,se[1][i],se[0][i]);
 //if(i%100==0)cout<<i<<" E="<<E0<<"E1="<<se[0][i]<<"E2="<<se[1][i]<<"E3="<<se[2][i]<<'\n';
 } 
}

int getit(TGraph *f,double se[4][NUM],int AA,int ZZ,int *I,int _thick)
{
  int i=0,j=0,zz=0,aa=0;
  double sein[4];
  //TString tele=TString ::Format("tele%d.root",*I);
  TString tele=TString ::Format("/home/zhuhy/zhuhy/pid/pid_s_c/pid/ds1600_csi1d_pid_4He.root",_thick);
  TFile *opf=new TFile(tele,"recreate");
  TTree *opt=new TTree("tree","tree structure for analysis");
  opt->Branch("se",sein,"se[4]/D");
  opt->Branch("zz",&zz,"zz/I");
  opt->Branch("aa",&aa,"aa/I");
  for(i=0;i<NUM;i++)
  {
   while(j<4){sein[j]=se[j][i];j++;}
   aa=AA;
   zz=ZZ;
   opt->Fill();
   j=0;
  }
  opt->Write();
  opf->Close();
  (*I)++;
  cout<<*I<<'\n';
}
void drawit(TGraph *f)
{ 
  auto c1=new TCanvas("c1","c1");
  f->SetTitle("s0e*(s0e+s1e+s2e)");
  f->GetYaxis()->SetLimits(0,400*400+20);
  f->GetXaxis()->SetLimits(0,14*NUM+20);
  f->Draw("AP");
}
void empty(double se[4][NUM])
{
int i;
for(i=0;i<NUM;i++){se[0][i]=0;}
for(i=0;i<NUM;i++){se[1][i]=0;}
for(i=0;i<NUM;i++){se[2][i]=0;}
for(i=0;i<NUM;i++){se[3][i]=0;}
}
