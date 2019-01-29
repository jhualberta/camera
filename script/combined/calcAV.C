using namespace std;
#include "TVector3.h"
#include "TF1.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <ios>
#include <fstream>
//for the refraction sphere*********************************************
double n1 = 1.3; double n2 = 1.5; double n3 = 1.3; //refraction indexes
double loa = 6052; double loc = 6000; double lod = 6052; double lob = 6000; 
double p2d[2];
double cam3[3];
double cam[2];  //2D coordiante of camera
double a[2];  double b[2]; double c[2]; double d[2];
double ain1;   //angle of first incidence ray wrt x axis
double lap; double lop; double lba;
double theta1; 
double theta2; 
double theta3; 
double theta4; 
double theta5;
double theta6;
double theta7;
double theta8;
double theta9;
double theta10;
double theta11;
double ain2; //their angles withe respect to x aixis
double aopm;
double aoa; double aob;
double aboc;
double lbc;
double aocd; 
double lcd;
double aoc;  //angle of oc wrt x axisi
double ratio; 
double aod;
double aode;
double ados;
double out; //angle of de wrt x axis
double es; //error from camera
double esn;
double est; //total adjustment
int n=0;
double sp[2];
double asp;
double dix; double diy;
//double i2d, j2d, k2d;
double aob2;

//define variables
float xpix[3600];
float ypix[3600];
float magx; float magy;
float dis = 0;
float view = (TMath::Pi()/2.118);
TVector3 av_pos;
double theta;
double thetax; double thetay;double phi;
float distance;

//read the chosen pmts location
	
std::vector<TVector3>avList;

int iii;
double xpixf; double ypixf;
float pp[12][4];
double theta_cam[4]; double phi_cam[4]; double r_cam[4];//{8438, 8558, 8399.44, 8401.64};
TVector3 xcp[4]; 
double angle[4];                 //angle of rotation of the camera with respect to the vertical up
double rx[4];                    //angle of roation of k on x and y direction
double ry[4];
double mx1[4];
double my1[4];
double mx2[4]; 
double mx3[4];
double my2[4]; 
double my3[4];
float check;
float sxa;
float sx;
float irad;
float aq;
float sdis = 1000;
double rad = 6060;
int tp[4] = {20,20,20,20};  //number of manually selected points
int ttp = 80; //total number of manually selected points
int ic;
int in=0;

double calcAV(double *x, double *p){
  int iq=floor(x[0]);
  int q=iq/2;
  double av1 = p[0];
  double av2 = p[1];
  double av3 = p[2];
TVector3 av(av1,av2,av3);
TVector3 ap;
if(q<tp[0]){ic=0;}
else if(q<tp[0]+tp[1]){ic=1;}
else if(q<tp[0]+tp[1]+tp[2]){ic=2;}
else if(q<ttp){ic = 3;}

//cout<<"angle[ic]"<<" "<<angle[ic]<<endl;
//cout<<"xcp[ic].X()"<<" "<<xcp[ic].X()<<endl;
//cout<<"xcp[ic].Y()"<<" "<<xcp[ic].Y()<<endl;
//cout<<"xcp[ic].Z()"<<" "<<xcp[ic].Z()<<endl;

  TVector3 north(sin(angle[ic]),cos(angle[ic]),0);
  TVector3 ko(xcp[ic].Unit());
  TVector3 io(north-(ko * north) * ko); io=io.Unit();
  TVector3 jo(ko.Cross(io));
  TVector3 k(ko + tan(rx[ic])*io + tan(ry[ic])*jo); k = k.Unit();
  TVector3 i(north-(k * north) * k); i=i.Unit();
  TVector3 j(k.Cross(i));
  av_pos = avList[q];

ap = xcp[ic] - av;
sxa = asin(rad/(ap.Mag()));
sx = sqrt(((ap.Mag())*(ap.Mag()))-rad*rad);
irad = sin(sxa)*sx;
aq = ap.Mag() - cos(sxa)*sx;
TVector3 qq(av+aq*(ap.Unit()));

TVector3 kp((av-qq).Unit());
TVector3 ip(north-(kp * north) * kp); ip=ip.Unit();
TVector3 jp(kp.Cross(ip));
iii = 0;
sdis = 100000;
  for(int ii=0;ii<3600;ii++){
   TVector3 avline(cos(0.1*ii/180*TMath::Pi())*(irad),sin(0.1*ii/180*TMath::Pi())*(irad),0);
   TVector3 avcircle(avline.X()*ip+avline.Y()*jp+qq);
   check = (xcp[ic]-avcircle).Dot(avcircle-av);
   TVector3 avprime((avcircle-xcp[ic]) * i,(avcircle-xcp[ic]) * j, (avcircle-xcp[ic]) * k);
   theta = abs(atan(sqrt((TMath::Power(avprime.X(),2))+(TMath::Power(avprime.Y(),2)))/(-avprime.Z())));
   TVector3 sub(avprime.X(), avprime.Y(),0);
   thetax = theta*(sub.Unit().X()); thetay = theta*(sub.Unit().Y());
   xpix[ii] = thetax*mx1[ic] + mx2[ic]*thetax*thetax + mx3[ic]*thetax*thetax*thetax;
   ypix[ii] = thetay*my1[ic] + my2[ic]*thetay*thetay + my3[ic]*thetay*thetay*thetay;
     if(theta<view){
      if(avprime.Z()<0){
       //picture.Fill(xpix,ypix); 
       //av1   
       dis = (av_pos.Y()-xpix[ii])*(av_pos.Y()-xpix[ii])+(av_pos.Z()-ypix[ii])*(av_pos.Z()-ypix[ii]);
       if(dis<sdis){
         sdis = dis;
         iii = ii;
       }
      }
     }
   }
   //cout<<"xpix"<<xpix[iii]<<"ypix"<<ypix[iii]<<endl;
   if(iq%2==0)return xpix[iii];
   else return ypix[iii];
}


void myfunc()
{

for (int i=0; i<4;i++){
in = 0;
ifstream myReadFilep;
//cout<<"i"<<endl;
  if (i==0){myReadFilep.open("paras/together/p.txt");}
  if (i==1){myReadFilep.open("paras/together/1.txt");}
  if (i==2){myReadFilep.open("paras/together/3.txt");}
  if (i==3){myReadFilep.open("paras/together/5.txt");}
  if (myReadFilep.is_open()) {
  while (!myReadFilep.eof()) {
     myReadFilep >> pp[in][i];
	 //cout<<pp[in][i]<<" "<<"pp[in][i]"<<endl;
     in++;
  }
  }
  myReadFilep.close();
  theta_cam[i] = pp[0][i];
  phi_cam[i] = pp[1][i];
  r_cam[i] = pp[11][i];
  xcp[i].SetX(r_cam[i]*sin(theta_cam[i])*cos(phi_cam[i]));
  xcp[i].SetY(r_cam[i]*sin(theta_cam[i])*sin(phi_cam[i]));
  xcp[i].SetZ(r_cam[i]*cos(theta_cam[i])); 
  angle[i] = pp[2][i];                 //angle of rotation of the camera with respect to the vertical up
  rx[i] = pp[3][i];                    //angle of roation of k on x and y direction
  ry[i] = pp[4][i];
  mx1[i] = pp[5][i];
  my1[i] = pp[6][i];
  mx2[i] = pp[7][i]; 
  mx3[i] = pp[8][i];
  my2[i] = pp[9][i]; 
  my3[i] = pp[10][i];
}



 int ip;
 int n=0; 
 int tp[4]={20,20,20,20};  //number of manually selected points
 int ttp = 80; //total number of manually selected points'
 int number[100] = { }; float xm[100] = { }; float ym[100] = { };
 TVector3 temp;
 ifstream myReadFile2;
 for (int i=0;i<4;i++){
  if(i==0){
	myReadFile2.open("av_pos/p.txt");
	}
  if(i==1){
	myReadFile2.open("av_pos/1.txt");
	n = n + tp[i-1];
	//cout<<"n"<<" "<<n<<endl;
	}
  if(i==2){
	myReadFile2.open("av_pos/3.txt"); 
	n = n + tp[i-1];
	}
  if(i==3){
	myReadFile2.open("av_pos/5.txt");
	n = n + tp[i-1];
	}

	std::string linep;
    ip = 0;
	if (myReadFile2.is_open()) {
	while (!myReadFile2.eof()) {

       myReadFile2 >> number[ip+n] >> xm[ip+n] >> ym[ip+n];
	   temp.SetX(number[ip+n]); temp.SetY(xm[ip+n]); temp.SetZ(ym[ip+n]);
	   if(number[ip+n]!=0){
	     avList.push_back(temp);
cout<<number[ip+n] <<" "<< xm[ip+n] <<" "<< ym[ip+n]<<" "<<"number, x, y"<<endl;
	   }
   	   ip++;
	}	
	}
	  //tp[i] = sizeof(number)/sizeof(*number);
//	  for(int ii=0; ii<100;ii++){
//	   if(number[ii]!=0){
//		tp[i] = tp[i]+1;
//cout<<tp[i]<<" "<<"tp[i]"<<endl;
//cout<<number[ii]<<" "<<"number[ii]"<<endl;
//		}
//	  }
//    if(i!=0){tp[i] = tp[i]-ttp;}
//	ttp = ttp + tp[i];
	myReadFile2.close();

}
cout<<"start fit"<<endl;
cout<<"ttp"<<" "<<ttp<<endl;
   TCanvas *c1=new TCanvas("CC","CC",1200,800);
   c1->Divide(1,2);
   c1->cd(1); 
   TF1 *f1 = new TF1("calcA",calcAV,0,ttp*2,3);
cout<<"initialize fit"<<endl;
   f1->SetNpx(ttp*2);
   double p[3]={0,0,0};
   f1->SetParameters(p);
   f1->Draw();
   TH1F *h1=new TH1F("h1","test",ttp*2,0,ttp*2);
cout<<"1"<<endl;
   for(int i=0;i<ttp;i++){
      h1->SetBinContent(2*i+1,xm[i]); h1->SetBinContent(2*i+2,ym[i]);
	//  cout<<"xm, ym"<<" "<<xm[i]<<" "<<ym[i]<<endl;
   }
cout<<"2"<<endl;
   for(int i=1;i<=ttp;i++)h1->SetBinError(i,30);
cout<<"3"<<endl;
   h1->Fit("calcA");
cout<<"4"<<endl;
  

   TH1F *h2=new TH1F("h2","residual",ttp*2,0,ttp*2);
cout<<"5"<<endl;
   for(int i=0;i<ttp*2;i++)h2->SetBinContent(i+1,h1->GetBinContent(i+1)-f1->Eval(i));
cout<<"6"<<endl;
   c1->cd(2); h2->Draw();


}













