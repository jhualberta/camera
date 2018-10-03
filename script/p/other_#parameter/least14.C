{
//gPad->SetFixedAspectRatio(1);
using namespace std;
//define variables
float xpix;
float ypix;
float magx;
float magy;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta = 0;



ifstream myReadFile;
myReadFile.open("paras14.txt");
float para[14];
int in=0;
if (myReadFile.is_open()) {
while (!myReadFile.eof()) {

   myReadFile >> para[in];
   in++;
}
}
myReadFile.close();

double mx1 = para[0];
TVector3 xcp(para[1],para[2],para[3]);
double angle = para[4];  
double rx =  para[5];
double ry = para[6];

  double mx0 = para[7]; double mx2=para[8]; double mx3 = para[9];      //adjustment to magnification for x
  double my1 = para[10]; 
  double my0 = para[11]; double my2=para[12]; double my3 = para[13];      //adjustment to magnification for y


float d;

//load the PMTs position
std::vector<TVector3>pmtList;	
FILE *stream=fopen("../../data/database20040923b.dat","r");
char *line=NULL;
size_t len=0;
int r=getline(&line,&len,stream);
r=getline(&line,&len,stream);
for(int iline=0;r>0;iline++){
  r=getline(&line,&len,stream);
  if(r==0)continue;
  if (TString(line,4)==TString("EOHV"))break;
  if(line[0]=='E'){
    double x=TString(line+31,8).Atof();
    double y=TString(line+40,8).Atof();
    double z=TString(line+49,8).Atof();
    pmtList.push_back(TVector3(x,y,z));
  }
}

//form the image
           //angle of rotation of the camera with respect to the vertical up
TVector3 north(sin(angle),cos(angle),0);
TVector3 ko(xcp.Unit());
TVector3 io(north-(ko * north) * ko); io=io.Unit();
TVector3 jo(ko.Cross(io));
//angle of roation of k on x and y direction

TVector3 k(ko + tan(rx)*io + tan(ry)*jo); k = k.Unit();
TVector3 i(north-(k * north) * k); i=i.Unit();
TVector3 j(k.Cross(i));

TH2F picture("HPicture","PMTs in fish eye lens (angle of view 85)(camera P)",4310,-2155,2155,2868,-1434,1434);
picture.SetMarkerStyle(8);
picture.SetMarkerSize(0.05);
for (Int_t q=0;q<pmtList.size(); q++) {
  pmt = pmtList[q]*10;
  TVector3 kp(-pmt.Unit());
  TVector3 ip(north-(kp * north) * kp); ip=ip.Unit();
  TVector3 jp(kp.Cross(ip));
  //build the PMTs as circle with 18 points
  for (float u=0;u<18;u++){
   TVector3 disp(cos(20*u/180*TMath::Pi())*137,sin(20*u/180*TMath::Pi())*137,0);
   TVector3 pprime(disp.X()*ip+disp.Y()*jp+pmt);
   //form image on camera
   TVector3 xprime((pprime-xcp) * i,(pprime-xcp) * j, (pprime-xcp) * k);
   theta = abs(atan(sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2)))/(xprime.Z())));
   d = (sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2))));
   magx = mx0 + mx1*theta/d + mx2*TMath::Power(theta,2)/d + mx3*TMath::Power(theta,3)/d;
   magy = my0 + my1*theta/d + my2*TMath::Power(theta,2)/d + my3*TMath::Power(theta,3)/d;
   xpix = xprime.X()*magx;
   ypix = xprime.Y()*magy;
   //test if thepoint is in the angle of view
    if(theta<view){
     if(xprime.Z()<0){
      picture.Fill(xpix,ypix);
     }
    }
   }
}

picture.Draw("SAME");
//picture.Draw();
c1->SetCanvasSize(4310*0.3,2868*0.3);
//c1->SaveAs("../../plot/mix_p.png");

}
