#define NUM 5000 //入射粒子数,按师兄建议一般取十万，得到能量乘积图时为了图案清晰取一万
#define _N 4
void openandreadandtest(double se[_N][NUM],int M,char str[3][20]); //模拟粒子入射，每块板上的能量沉积结果存在二维数组se中
int getit(TGraph *f,double se[_N][NUM],int AA,int ZZ,int *I); //将se中数据存进图里
void drawit(TGraph *f); 
void empty(double se[_N][NUM]);//每种粒子入射模拟完毕，并将数据存入图后，清空数组待下一次模拟
using namespace std;

void newlisec(){
double se[_N][NUM];
TGraph *f;
f=new TGraph;
int AA=0,ZZ=0,J=0,*I;  //M为质量数，*I指向J为图的计数顺序，因为所有的要画在一张图上，所以需要一个总的顺序，因此用指针以变在函数中能改变主函数的实变
I=&J;
char str3He[3][20]={"2H-Si.txt","2H-Al.txt","2H-Mylar.txt"};
AA=3;ZZ=1; openandreadandtest(se,AA,str3He);getit(f,se,AA,ZZ,I); empty(se);


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
}

void openandreadandtest(double se[_N][NUM],int M,char str[3][20]){
  TGraph *g[3];
  ifstream in(str[0]);
  string ss;
  double a, b, e, dedx;
  g[0]=new TGraph;//定义新的二维散点图(TGraph) g1
  if(in.is_open()){//检查文件是否存在
//    getline(in,ss);
    int i=0;
    while(!in.eof())
    {
      in>>a>>b>>e>>dedx>>a>>b>>a>>b>>a>>b>>a>>b;
      // 对照数据文件进行理解。一列一列地读入，提取第3、4列数据。
      g[0]->SetPoint(i++, e*M,dedx);//添加数据点到图中，能量单位为MeV/u，对C需乘以12.    
	}
  } 
  in.close();

  ifstream in1(str[1]);
  g[1]=new TGraph;
  if(in1.is_open()){
//    getline(in1,ss);
    i=0;
    while(!in1.eof())
    {
      in1>>a>>b>>e>>dedx>>a>>b>>a>>b>>a>>b>>a>>b;
      g[1]->SetPoint(i++, e*M,dedx);
        }
  } 
  in1.close();
  
  ifstream in2(str[2]);
  g[2]=new TGraph;
  if(in2.is_open()){
//    getline(in2,ss);
    i=0;
    while(!in2.eof())
    {
      in2>>a>>b>>e>>dedx>>a>>b>>a>>b>>a>>b>>a>>b;
      g[2]->SetPoint(i++, e*M,dedx);
        }
  } 
  in2.close();



 Double_t E0=0,Etem=0,Esmall=0,E2=0,E=0,dE=0,e1=0,e2=0,e3=0,x=0,dx=0.1;//E0为能量总值，E为能量实时记录值，E1为穿透第一块硅时的能量，E2为穿透第二块时的能量
 Double_t d[_N-1]={1.3,200,2.};
 Int_t k; //kind  0:Si 1:Al 2:Mylar
 for(i=1;i<(_N-1);i++)d[i]=d[i]+d[i-1];
 for(i=-1;i<NUM;x=0)   //开始NUM次模拟
  {
  if(i%5000==0)cout<<i<<":"<<NUM<<'\n';
  i++;
  if(i>=NUM)break;
  x=0;
  //Esmall=rand()%1000;  //初始能量小数部分
  E0=E=i*100/5000.;//+Esmall/1000;  
  //E0=E=rand()%300+Esmall/1000;  //能量随机值为300+3位小数
  se[_N-1][i]=E0;
  for(Int_t j=0;j<_N;j++)se[j][i]=0;
  se[_N-1][i]=E0;
  Etem=E0;
  k=1;
   
  while(1)   
    {
     if((fabs(x-d[0])<=(dx/100.)||(x>=0&&x<d[0]))&&E<=0){se[0][i]=Etem;Etem=0;break;} 
     else if(fabs(x-d[0])<=(dx/100.)&&E>0){if(k!=0){se[0][i]=E0-E;Etem=E;}k=0;}

     else if((fabs(x-d[1])<=(dx/2.)||(x>d[0]&&x<d[1]))&&E<=0){se[1][i]=Etem;Etem=0;break;}  
     else if(fabs(x-d[1])<=(dx/2.)&&E>0){if(k!=2){se[1][i]=Etem-E;Etem=E;}k=2;}  

     else if(((fabs(x-d[2])>(dx/100.)&&x>d[2])&&E<=0)){se[2][i]=Etem;Etem=0;break;}
     else if(((fabs(x-d[2])>(dx/100.)&&x>d[2])&&E>0)){se[2][i]=Etem-E;Etem=0;break;}
     else if(fabs(x-d[2])<=(dx/100.)&&E>0){if(k!=0){se[2][i]=Etem-E;Etem=E;}k=0;}
     dE=g[k]->Eval(E);
     if(k==0){
     E=E-dE*dx;    
     x=x+dx;
     }
     else {
     E=E-dE*dx/50.;
     x=x+dx/50.;
     }
    }
//if(i%10==0)    cout<<x<<'\t';
   
 // if(i%1==0)cout<<" i="<<i<<" E="<<E0<<" E1="<<se[0][i]<<" E2="<<se[1][i]<<" E3="<<se[2][i]<<" E4="<<se[3][i]<<" E5="<<se[4][i]<<" E6="<<se[5][i]<<" E7="<<se[6][i]<<" E="<<se[7][i]<<'\n';
  }
}

int getit(TGraph *f,double se[_N][NUM],int AA,int ZZ,int *I)
{
  int i=0,j=0,zz=0,aa=0;
  double sein[_N];
  //TString tele=TString ::Format("tele%d.root",*I);
  TString tele=TString ::Format("H3_150.root");
  TFile *opf=new TFile(tele,"recreate");
  TTree *opt=new TTree("tree","tree structure for analysis");
  opt->Branch("se",sein,"se[4]/D");
  opt->Branch("zz",&zz,"zz/I");
  opt->Branch("aa",&aa,"aa/I");
  for(i=0;i<NUM;i++)
  {
   while(j<_N){sein[j]=se[j][i];j++;}
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
void empty(double se[_N][NUM])
{
int i;
for(i=0;i<NUM;i++){se[0][i]=0;}
for(i=0;i<NUM;i++){se[1][i]=0;}
for(i=0;i<NUM;i++){se[2][i]=0;}
for(i=0;i<NUM;i++){se[3][i]=0;}
}
