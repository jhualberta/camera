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
//end for the refraction sphere******************************************


//define variables
float xpix;
float ypix;
float magx; float magy;
float dis = 0;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta;
double thetax; double thetay;
double phi;
float distance;

//read the chosen pmts location
std::vector<TVector3>pmtList;	
float xc[136], yc[136], zc[136];
float number[136], xm[136], ym[136];

double calcPixel(double *x, double *p){
  int iq=floor(x[0]);
  int q=iq/2;

  TVector3 xcp(p[0],p[1],p[2]);        //camera position  (7289.7,193.5,4246.6);
  double angle = p[3];                 //angle of rotation of the camera with respect to the vertical up
  double rx = p[4];                    //angle of roation of k on x and y direction
  double ry = p[5];

  double mx1 = p[6];
  double my1 = p[7];
  double mx2 = p[8]; 
  double mx3 = p[9];
  double my2 = p[10]; 
  double my3 = p[11];

  TVector3 north(sin(angle),cos(angle),0);
  TVector3 ko(xcp.Unit());
  TVector3 io(north-(ko * north) * ko); io=io.Unit();
  TVector3 jo(ko.Cross(io));
  TVector3 k(ko + tan(rx)*io + tan(ry)*jo); k = k.Unit();
  TVector3 i(north-(k * north) * k); i=i.Unit();
  TVector3 j(k.Cross(i));

  pmt = pmtList[q];
  TVector3 kp(-pmt.Unit());
  TVector3 ip(north-(kp * north) * kp); ip=ip.Unit();
  TVector3 jp(kp.Cross(ip));
  TVector3 xprime((pmt-xcp) * i,(pmt-xcp) * j, (pmt-xcp) * k);
//*****************************************************************************************************************************************
  TVector3 ks(xcp.Cross(pmt)); ks = ks.Unit();
  TVector3 js(-xcp.Unit());
  TVector3 is(js.Cross(ks)); is = is.Unit();
  TVector3 p2D(pmt*is, pmt*js, pmt*ks);
  p2d[0] = p2D.X(); p2d[1] = p2D.Y();
//cout<<"p2d"<<" "<<p2d[0]<<" "<<p2d[1]<<endl;
  cam3[0] = xcp.X(); cam3[1] = xcp.Y(); cam3[2] = xcp.Z();
  cam[1] = -sqrt(cam3[0]*cam3[0] + cam3[1]*cam3[1] + cam3[2]*cam3[2]);

  sp[0] = abs(p2d[0]); sp[1] = p2d[1] - cam[1];
  asp = atan(sp[0]/sp[1]);
//  cout<<asp<<endl;
//cout<<"pprime"<<" "<<pprime.X()<<" "<<pprime.Y()<<" "<<pprime.Z()<<endl;
  if ((sp[0]*-cam[1])/sqrt(sp[0]*sp[0]+sp[1]*sp[1])<loa){   //if condition checking if light need to be refracted


est = 0;
es = 0; //set a initial error
esn = 1;
n = 0;
while(esn>0.0000000001){
n = n + 1;
if(n>20){
break;
}
//cout<<"                     into the loop number"<<n<<endl;

if(p2d[0]<0){
	ain1 = atan((cam[1]-p2d[1])/(cam[0]-est-p2d[0]));  
}
else{
	ain1 = atan((cam[1]-p2d[1])/(cam[0]-est-p2d[0])) - TMath::Pi();
}

//the first triangle
aopm = abs(atan(p2d[1]/p2d[0]));
//cout<<"ain1"<<" "<<ain1<<endl;
//cout<<"aopm"<<" "<<aopm<<endl;
lop = sqrt(p2d[0]*p2d[0]+p2d[1]*p2d[1]);
//ain1 = atan(p2d[0]/p2d[1])+theta1 - (TMath::Pi()/2);

if (p2d[0] > 0){
theta1 = (TMath::Pi())-abs(ain1)-aopm;
}
else{
theta1 = abs(ain1) - aopm;
}

//cout<<"theta1"<<" "<<theta1<<endl;
//cout<<"lop"<<" "<<lop<<endl;
//cout<<"loa"<<" "<<loa<<endl;
//lap = lop*cos(theta1) + sqrt(loa*loa+lop*lop*(cos(theta1)*cos(theta1)-1)); //or
lap =lop*cos(theta1) - sqrt(loa*loa+lop*lop*(cos(theta1)*cos(theta1)-1));
//cout<<"lap"<<" "<<lap<<endl;
a[0] = p2d[0] + cos(ain1)*lap; 
a[1] = p2d[1] + sin(ain1)*lap;
//cout<<"coordinate of a"<<" "<<a[0]<<" "<<a[1]<<endl;
theta2 = acos((lop*lop+loa*loa-lap*lap)/(2*lop*loa));
//cout<<"theta2"<<" "<<theta2<<endl;
theta3 = theta1 +theta2;
if(theta3<0){
//cout<<"theta3"<<" "<<theta3<<endl;
}
theta4 = asin((sin(theta3)*n1)/(n2));  //apply snell's law
aoa = asin(a[1]/loa);
//cout<<"aoa"<<" "<<aob<<endl;
if (theta4>1.04848){
//cout<<"theta4"<<" "<<theta4<<endl;
//break;
}

if (theta4<asin(lob/loa)){        //check if the light go into the ball

  // the second triangle
  lba = loa*cos(theta4) - sqrt(lob*lob+loa*loa*(cos(theta4)*cos(theta4)-1));  //apply cosine rule
  //cout<<"lba"<<" "<<lba<<endl;
  theta5 = acos((loa*loa+lob*lob-lba*lba)/(2*loa*lob));  //apply cosine rule
  //cout<<"theta5"<<" "<<theta5<<endl;
  theta6 = theta4 + theta5;
  //cout<<"theta6"<<" "<<theta6<<endl;
  theta7 = asin((sin(theta6)*n2)/(n3)); 
  //cout<<"theta7"<<" "<<theta7<<endl;
  //inner radius of sphere
  aoa = asin(a[1]/loa);
  aob = aoa - theta5;

  if(p2d[0]>0){
    b[0] = cos(aob)*lob;
    b[1] = sin(aob)*lob;
    ain2 = (theta7 + aob) -(TMath::Pi());  //second incidence angle wrt x axis 
  }
  else{
    b[0] = -cos(aob)*lob;
    b[1] = sin(aob)*lob;
    //ain2 = -(theta7 + aob);   //second incidence angle wrt x axis 
    ain2 = -(theta7 + aob);
  }
  //cout<<"coordinate of b"<<" "<<b[0]<<" "<<b[1]<<endl; 
  ///cout<<"ain2"<<" "<<ain2<<endl; 
  aboc = (TMath::Pi()) - theta7-theta7;
  //cout<<"aboc"<<" "<<aboc<<endl;
  lbc = sqrt(lob*lob+loc*loc-2*lob*loc*cos(aboc));
  //cout<<"lbc"<<" "<<lbc<<endl;
  c[0] = b[0] + cos(ain2)*lbc; c[1] = b[1] + sin(ain2)*lbc;
  //cout<<"coordinate of c"<<" "<<c[0]<<" "<<c[1]<<endl;
  theta8 = asin(sin(theta7)*(n3/n2));
  aocd = (TMath::Pi()) - theta8;
  lcd = sqrt(lod*lod+loc*loc*(cos(aocd)*cos(aocd)-1)) + loc*cos(aocd);
  //cout<<"lcd"<<" "<<lcd<<endl;
  theta9 = acos((loc*loc+lod*lod-lcd*lcd)/(2*loc*lod));
  //cout<<"theta9"<<" "<<theta9<<endl;
  aoc = -acos(c[0]/loc);
  if (p2d[0]>0){	
    aod = aoc-theta9;  //angle of od wrt x axis	
  }
  else{
    aod = aoc + theta9;	
  }  

  //cout<<"aod"<<" "<<aod<<endl;
  theta10 = theta8 - theta9;
  d[0] = cos(aod)*lod; d[1] = sin(aod)*lod;
  //cout<<"coordinate of d"<<" "<<d[0]<<" "<<d[1]<<endl;
}

else{                //light does not go into the cavity
  theta10 = theta4;
  if(p2d[0]>0){
    aod = -(TMath::Pi()-theta4-theta10)+aoa;
    //cout<<"theta4"<<" "<<theta4<<endl;
    //cout<<"aoa"<<" "<<aoa<<endl;
    //cout<<"aod+"<<" "<<aod<<endl;
    
  }
  else{
    aod = aoa + (TMath::Pi()-theta4-theta10);
    //cout<<"theta4"<<" "<<theta4<<endl;
    //cout<<"aoa"<<" "<<aoa<<endl;
    //cout<<"aod-"<<" "<<aod<<endl;
  }	
  d[0] = cos(aod)*lod; d[1] = sin(aod)*lod;
  //cout<<"coordinate of d"<<" "<<d[0]<<" "<<d[1]<<endl;
}	


//cout<<"aoc"<<" "<<aoc<<endl;
//cout<<"coordinate of d"<<" "<<d[0]<<" "<<d[1]<<endl;
//the last refraction

theta11 = asin(sin(theta10)*(n2/n1));
//cout<<"theta11"<<" "<<theta11<<endl;
//the camera
aode = (TMath::Pi()) - theta11;
ados = abs((TMath::Pi()/2) - abs(aod));
//cout<<"ados"<<" "<<ados<<endl;
if(p2d[0]>0){
	out = -((TMath::Pi()) - abs(aode) - abs(ados))-(TMath::Pi()/2);
}
else{
	out = -(TMath::Pi()/2) + ((TMath::Pi()) - abs(aode) - abs(ados));
}

es = (1/(tan(out)))  *  (cam[1]-d[1])  +d[0];
//cout<<"es"<<" "<<es<<endl;
esn = abs(es);
//cout<<"esn"<<" "<<esn<<endl;
est = est + es;
} //out of the minimizing loop
//cout<<"out"<<" "<<out<<endl;

 TVector3 ob(-cos(out), -sin(out), 0); 
 aob2 = abs(abs(out)-TMath::Pi()/2);
 //aob2 = atan(abs(ob.X()/abs(ob.Y())));
 // cout<<"aob2"<<" "<<aob2<<endl;
  //if (sin(aob2)*abs(cam[1])>loa){ 
  if (aob2>asin(loa/-cam[1])){ 
  //cout<<"aob2"<<aob2<<endl;
  //break;
  }
  TVector3 i2d(i*is, i*js, i*ks); i2d = i2d.Unit();
  TVector3 j2d(j*is, j*js, j*ks); j2d = j2d.Unit();
  TVector3 k2d(k*is, k*js, k*ks); k2d = k2d.Unit();
   //cout<<"k2d"<<" "<<k2d.X()<<" "<<k2d.Y()<<" "<<k2d.Z()<<" "<<endl;
  theta = abs(ob.Angle(-k2d));
  TVector3 obxy(ob-k2d*(ob*k2d)); obxy = obxy.Unit();
  //if (obxy.Angle(j2d) < TMath::Pi()/2){

  //}
  //else{

  //}
  //dix =  theta*mx1 + mx2*theta*theta + mx3*theta*theta*theta;
  //diy =  theta*my1 + my2*theta*theta + my3*theta*theta*theta;
  //xpix = dix*(obxy*i2d);
  //ypix = diy*(obxy*j2d);
  //phi = atan((ob*j2d)/(ob*i2d));
  //thetax = theta*cos(phi); thetay = theta*sin(phi);


  thetax = theta*(obxy*i2d); thetay = theta*(obxy*j2d);
  xpix = thetax*mx1 + mx2*thetax*thetax + mx3*thetax*thetax*thetax;
  ypix = thetay*my1 + my2*thetay*thetay + my3*thetay*thetay*thetay;
  //xpix = thetax*mx1;
  //ypix = thetay*mx1;

  if(iq%2==0)return xpix;
  else return ypix;



  } //end of the if condition checking if light need to be refracted
//************************************************************************************************************************************************************************************************
  else{ //the light does not go through the AV
  theta = abs(atan(sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2)))/(xprime.Z())));

  //dix =  theta*mx1 + mx2*theta*theta + mx3*theta*theta*theta;
  //diy =  theta*my1 + my2*theta*theta + my3*theta*theta*theta;

  //xpix = dix*(xprime.X()/sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2))));
  //ypix = diy*(xprime.Y()/sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2))));

  //phi = atan((xprime.Y())/(xprime.X()));
  //thetax = theta*cos(phi); thetay = theta*sin(phi);
  TVector3 sub(xprime.X(), xprime.Y(),0);
  thetax = theta*(sub.Unit().X()); thetay = theta*(sub.Unit().Y());
  xpix = thetax*mx1 + mx2*thetax*thetax + mx3*thetax*thetax*thetax;
  ypix = thetay*my1 + my2*thetay*thetay + my3*thetay*thetay*thetay;
  //xpix = thetax*mx1;
  //ypix = thetay*mx1;




  //cout<<"xpix"<<" "<<xpix<<endl;
  //cout<<"ypix"<<" "<<ypix<<endl;
  if(iq%2==0)return xpix;
  else return ypix;
  } //light does not go through AV
}
void myfunc()
{
	ifstream myReadFile;
	myReadFile.open("cpmts.txt");
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
	myReadFile2.open("pos.txt");
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


   TCanvas *c1=new TCanvas("CC","CC",1200,800);
   c1->Divide(1,2);
   c1->cd(1);
   TF1 *f1 = new TF1("calcP",calcPixel,0,272,12);
   f1->SetNpx(272);
   double p[12]={7289.7, 193.5, 4246.6, 0.272524, 0.127128, 0.027407, 1900, 1900, 0, 0, 0, 0};
   f1->SetParameters(p);
   //f1->FixParameter(3,0.272821);f1->FixParameter(4,0.121987);f1->FixParameter(5,0.0251177);
   //f1->FixParameter(3,0);f1->FixParameter(4,0);f1->FixParameter(5,0);
   //for (int ii=7;ii<12;ii++)f1->FixParameter(ii,0); 




   //f1->SetParameters(1.95e3,7289.7,193.5,4246.6,15.5*TMath::Pi()/180, 6.75*TMath::Pi()/180, 1.5*TMath::Pi()/180,0,0,0,1.95e3,0,0,0);
   //f1->SetParameters(1.95e3,7289.7,193.5,4246.6,15.5*TMath::Pi()/180, 6.75*TMath::Pi()/180, 1.5*TMath::Pi()/180,0,0,0,1.95e3);
//   f1->SetParNames("constant","coefficient",);
   f1->Draw();
   TH1F *h1=new TH1F("h1","test",272,0,272);
   for(int i=0;i<136;i++){
      h1->SetBinContent(2*i+1,xm[i]); h1->SetBinContent(2*i+2,ym[i]);
      //cout<<"xm"<<i<<" "<<xm[i]<<endl;
      //cout<<"ym"<<i<<" "<<ym[i]<<endl;
   }
   for(int i=1;i<=272;i++)h1->SetBinError(i,30);
   h1->Fit("calcP");
   TH1F *h2=new TH1F("h2","residual",272,0,272);
   for(int i=0;i<272;i++)h2->SetBinContent(i+1,h1->GetBinContent(i+1)-f1->Eval(i));
   c1->cd(2); h2->Draw();


}













