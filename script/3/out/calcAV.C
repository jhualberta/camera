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
double n;
double sp[2];
double asp;
double dix; double diy;
//double i2d, j2d, k2d;
double aob2;

//define variables
float xpix[36000];
float ypix[36000];
float magx; float magy;
float dis = 0;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
TVector3 av_pos;
double theta;
double thetax; double thetay;
double phi;
float distance;

//read the chosen pmts location
std::vector<TVector3>pmtList;	
std::vector<TVector3>avList;
float xc[48], yc[48], zc[48];
float number[4], xm[4], ym[4];
int iii;
double calcAV(double *x, double *p){
  int iq=floor(x[0]);
  int q=iq/2;
  double av1 = p[0];
  double av2 = p[1];
  double av3 = p[2];

ifstream myReadFilep;
myReadFilep.open("paras11.txt");
float pp[11];
int in=0;
if (myReadFilep.is_open()) {
while (!myReadFilep.eof()) {

   myReadFilep >> pp[in];
   in++;
}
}
myReadFilep.close();


  double theta_cam; double phi_cam; double r_cam = 8399.44;
  theta_cam = pp[0];
  phi_cam = pp[1];
  TVector3 xcp(r_cam*sin(theta_cam)*cos(phi_cam),r_cam*sin(theta_cam)*sin(phi_cam),r_cam*cos(theta_cam)); 
  double angle = pp[2];                 //angle of rotation of the camera with respect to the vertical up
  double rx = pp[3];                    //angle of roation of k on x and y direction
  double ry = pp[4];
  double mx1 = pp[5];
  double my1 = pp[6]==0?pp[5]:pp[6];
  double mx2 = pp[7]; 
  double mx3 = pp[8];
  double my2 = pp[9]; 
  double my3 = pp[10];

//cout<<"loaded parameters"<<endl;

  TVector3 north(sin(angle),cos(angle),0);
  TVector3 ko(xcp.Unit());
  TVector3 io(north-(ko * north) * ko); io=io.Unit();
  TVector3 jo(ko.Cross(io));
  TVector3 k(ko + tan(rx)*io + tan(ry)*jo); k = k.Unit();
  TVector3 i(north-(k * north) * k); i=i.Unit();
  TVector3 j(k.Cross(i));
  pmt = pmtList[q];
  av_pos = avList[q];


float check;
float sxa;
float sx;
float irad;
float aq;
float sdis = 1000;

double rad = 6060;
TVector3 av(av1,av2,av3);
TVector3 ap(xcp-av);
sxa = asin(rad/(ap.Mag()));
sx = sqrt(((ap.Mag())*(ap.Mag()))-rad*rad);
irad = sin(sxa)*sx;
aq = ap.Mag() - cos(sxa)*sx;
TVector3 qq(av+aq*(ap.Unit()));

TVector3 kp((av-qq).Unit());
TVector3 ip(north-(kp * north) * kp); ip=ip.Unit();
TVector3 jp(kp.Cross(ip));

  for(int ii=0;ii<36000;ii++){
   TVector3 avline(cos(0.01*ii/180*TMath::Pi())*(irad),sin(0.01*ii/180*TMath::Pi())*(irad),0);
   TVector3 avcircle(avline.X()*ip+avline.Y()*jp+qq);
   check = (xcp-avcircle).Dot(avcircle-av);
   TVector3 avprime((avcircle-xcp) * i,(avcircle-xcp) * j, (avcircle-xcp) * k);
   theta = abs(atan(sqrt((TMath::Power(avprime.X(),2))+(TMath::Power(avprime.Y(),2)))/(-avprime.Z())));
   TVector3 sub(avprime.X(), avprime.Y(),0);
   thetax = theta*(sub.Unit().X()); thetay = theta*(sub.Unit().Y());
   xpix[ii] = thetax*mx1 + mx2*thetax*thetax + mx3*thetax*thetax*thetax;
   ypix[ii] = thetay*my1 + my2*thetay*thetay + my3*thetay*thetay*thetay;
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
   if(iq%2==0)return xpix[iii];
   else return ypix[iii];
   cout<<"xpix"<<xpix[iii]<<"ypix"<<ypix[iii]<<endl;
}
void myfunc()
{
	ifstream myReadFile;
	myReadFile.open("pmt_xyz.txt");
	int ip=0;
	TVector3 temp;
	if (myReadFile.is_open()) {
	while (!myReadFile.eof()) {
	
	   myReadFile >> xc[ip] >> yc[ip] >> zc[ip];
	   //cout<<xc[ip]<<" "<<yc[ip]<<" "<<zc[ip]<<endl;
	   temp.SetX(xc[ip]); temp.SetY(yc[ip]); temp.SetZ(zc[ip]);
	   pmtList.push_back(temp);
	   ip++;
	}
	}
	myReadFile.close();
	//read the corresponding pixal location
	ifstream myReadFile2;
	myReadFile2.open("av_pos.txt");
	std::string linep;
	getline(myReadFile2,linep);
	ip=0;
	if (myReadFile2.is_open()) {
	while (!myReadFile2.eof()) {

       myReadFile2 >> number[ip] >> xm[ip] >> ym[ip];
	   temp.SetX(number[ip]); temp.SetY(xm[ip]); temp.SetZ(ym[ip]);
	   avList.push_back(temp);
   	   ip++;
	}	
	}
	myReadFile2.close();


   TCanvas *c1=new TCanvas("CC","CC",1200,800);
   c1->Divide(1,2);
   c1->cd(1);
   TF1 *f1 = new TF1("calcA",calcAV,0,8,3);
   f1->SetNpx(8);
   double p[3]={0,0,0};
   f1->SetParameters(p);
 

   f1->Draw();
   TH1F *h1=new TH1F("h1","test",8,0,8);
   for(int i=0;i<4;i++){
      h1->SetBinContent(2*i+1,xm[i]); h1->SetBinContent(2*i+2,ym[i]);
   }
   for(int i=1;i<=8;i++)h1->SetBinError(i,30);
   h1->Fit("calcA");

  

   TH1F *h2=new TH1F("h2","residual",8,0,8);
   for(int i=0;i<8;i++)h2->SetBinContent(i+1,h1->GetBinContent(i+1)-f1->Eval(i));
   c1->cd(2); h2->Draw();


}













