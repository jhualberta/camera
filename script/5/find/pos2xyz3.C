{
//gPad->SetFixedAspectRatio(1);
using namespace std;
//define variables
float xpix;
float ypix;
float xo;
float yo;
float mag;
float mago;
float thetao;
float d;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta = 0;
TVector3 pmtc;
std::vector<TVector3>cpmt;	
float odis;
float ndis;

float alpha = 1.93e3;
TVector3 xcp(-2194.6,6952.5,4175.4);

float angle = -120./180*TMath::Pi();             //angle of rotation of the camera with respect to the vertical up 
float rx = -6.8/180*TMath::Pi();
float ry = 15.2/180*TMath::Pi();

int tnumber = 18;
ofstream output("../pmt_3d/pmt_3d3.txt");
ifstream myReadFile;
myReadFile.open("../pos/pos3.txt");
std::string linep;
getline(myReadFile,linep);
float number[18], xc[18], yc[18];
int ip=0;
if (myReadFile.is_open()) {
//while (!myReadFile.eof()) {

//   myReadFile >> number[ip] >> xc[ip] >> yc[ip];
//   cout<<number[ip]<<" "<<xc[ip]<<" "<<yc[ip]<<endl;
//   ip++;
//   cout<<"1"<<endl;
//}
while (ip<tnumber){
   myReadFile >> number[ip] >> xc[ip] >> yc[ip];
   cout<<number[ip]<<" "<<xc[ip]<<" "<<yc[ip]<<endl;
   ip++;
   cout<<"1"<<endl;
}
}
cout<<"out"<<endl;
myReadFile.close();


//load the PMTs position
std::vector<TVector3>pmtList;	
cout<<"start"<<endl;
FILE *stream=fopen("../../../data/database20040923b.dat","r");
cout<<"LOADED"<<endl;
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

TVector3 north(sin(angle),cos(angle),0);
TVector3 ko(xcp.Unit());
TVector3 io(north-(ko * north) * ko); io=io.Unit();
TVector3 jo(ko.Cross(io));
TVector3 k(ko + tan(rx)*io + tan(ry)*jo); k = k.Unit();
TVector3 i(north-(k * north) * k); i=i.Unit();
TVector3 j(k.Cross(i));
TH2F picture("HPicture","PMTs in fish eye lens (angle of view 85)(camera P)",4310,-2155,2155,2868,-1434,1434);
picture.SetMarkerStyle(8);
picture.SetMarkerSize(0.05);

//mark the closes pmt
for (Int_t l=0;l<sizeof(xc)/sizeof(*xc); l++){
ndis = 6000;
for (Int_t q=0;q<pmtList.size(); q++) {
  pmt = pmtList[q]*10;

  TVector3 xprimeo((pmt-xcp) * i,(pmt-xcp) * j, (pmt-xcp) * k);
  thetao = abs(atan(sqrt((TMath::Power(xprimeo.X(),2))+(TMath::Power(xprimeo.Y(),2)))/(xprimeo.Z())));
  mago = alpha*thetao/(sqrt((TMath::Power(xprimeo.X(),2))+(TMath::Power(xprimeo.Y(),2))));
  xo = xprimeo.X()*mago;
  yo = xprimeo.Y()*mago; 
  d = sqrt(TMath::Power(xo-xc[l],2)+TMath::Power(yo-yc[l],2));
  if(d<ndis){
   ndis = d;
   pmtc = pmt;
   }
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
   mag = alpha*theta/(sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2))));
   xpix = xprime.X()*mag;
   ypix = xprime.Y()*mag;
   //test if thepoint is in the angle of view
    if(theta<view){
     if(xprime.Z()<0){
      picture.Fill(xpix,ypix);
     }
    }
   }
}
cpmt.push_back(pmtc);
cpmt[l].Print();
output<<cpmt[l].X()<<" "<<cpmt[l].Y()<<" "<<cpmt[l].Z()<<endl;
}
}
