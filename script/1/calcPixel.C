using namespace std;
#include "TVector3.h"
#include "TF1.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <ios>
#include <fstream>

//define variables
float xpix;
float ypix;
float mag;
float dis = 0;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta = 0;

//read the chosen pmts location
std::vector<TVector3>pmtList;	
float xc[99], yc[99], zc[99];
float number[99], xm[99], ym[99];
int number = 99;
double calcPixel(double *x, double *p){
  int iq=floor(x[0]);
  int q=iq/2;
  double  alpha = p[0];                           //magnification constant
  TVector3 xcp(p[1],p[2],p[3]); //7289.7,193.5,4246.6);              //camera position
  double angle = p[4];  //15.5/180*TMath::Pi();             //angle of rotation of the camera with respect to the vertical up
  double rx = p[5]; //6.75/180*TMath::Pi();                //angle of roation of k on x and y direction
  double ry = p[6]; //1.5/180*TMath::Pi();

  TVector3 north(sin(angle),cos(angle),0);
  TVector3 ko(xcp.Unit());
  TVector3 io(north-(ko * north) * ko); io=io.Unit();
  TVector3 jo(ko.Cross(io));
  TVector3 k(ko + tan(rx)*io + tan(ry)*jo); k = k.Unit();
  TVector3 i(north-(k * north) * k); i=i.Unit();
  TVector3 j(k.Cross(i));
   
//for (Int_t q=0;q<pmtList.size(); q++) {
  pmt = pmtList[q];
  TVector3 kp(-pmt.Unit());
  TVector3 ip(north-(kp * north) * kp); ip=ip.Unit();
  TVector3 jp(kp.Cross(ip));
  TVector3 xprime((pmt-xcp) * i,(pmt-xcp) * j, (pmt-xcp) * k);
  theta = abs(atan(sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2)))/(xprime.Z())));
  mag = alpha*theta/(sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2))));
  xpix = xprime.X()*mag;
  ypix = xprime.Y()*mag;
  if(iq%2==0)return xpix;
  else return ypix;
}

void myfunc()
{
	ifstream myReadFile;
	myReadFile.open("cpmts_xyz.txt");
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
	myReadFile2.open("cpix_pos.txt");
	std::string linep;
	getline(myReadFile2,linep);
	ip=0;
	if (myReadFile2.is_open()) {
	while (!myReadFile2.eof()) {

   	myReadFile2 >> number[ip] >> xm[ip] >> ym[ip];
   	//cout<<number[im]<<" "<<xm[im]<<" "<<ym[im]<<endl;
   	ip++;
	}	
	}
	myReadFile.close();


   TCanvas *c=new TCanvas("CC","CC",1200,800);
   c->Divide(1,2);
   c->cd(1);
   TF1 *f1 = new TF1("calcP",calcPixel,0,number*2,7);
   f1->SetNpx(number*2);
   f1->SetParameters(1.95e3,7289.7,193.5,4246.6,15.5*TMath::Pi()/180, 6.75*TMath::Pi()/180, 1.5*TMath::Pi()/180);
//   f1->SetParNames("constant","coefficient",);
   f1->Draw();
   TH1F *h1=new TH1F("h1","test",number*2,0,number*2);
   for(int i=0;i<number*2;i++){
      h1->SetBinContent(2*i+1,xm[i]); h1->SetBinContent(2*i+2,ym[i]);
   }
   for(int i=1;i<=number*2;i++)h1->SetBinError(i,1);
   h1->Fit("calcP");
   TH1F *h2=new TH1F("h2","residual",number*2,0,number*2);
   for(int i=0;i<number*2;i++)h2->SetBinContent(i+1,h1->GetBinContent(i+1)-f1->Eval(i));
   c->cd(2); h2->Draw();


}



















