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


ifstream myReadFile2;
myReadFile2.open("paras10.txt");
float para[10];
int in=0;
if (myReadFile2.is_open()) {
while (!myReadFile2.eof()) {

   myReadFile2 >> para[in];
   in++;
}
}
myReadFile2.close();

float m1 = para[0];
TVector3 xcp(para[1],para[2],para[3]);
float angle = para[4];  
float rx =  para[5]+1.0/180*TMath::Pi();
float ry = para[6]+1.0/180*TMath::Pi();
double m0 = para[7];double m2 = para[8];double m3 = para[9];
float d2;



int tnumber = 21;
ofstream output("chosen_pmts7.txt");
ifstream myReadFile;
myReadFile.open("pos7.txt");
std::string linep;
getline(myReadFile,linep);
float number[21], xc[21], yc[21];
int ip=0;
if (myReadFile.is_open()) {
while (!myReadFile.eof()) {

   myReadFile >> number[ip] >> xc[ip] >> yc[ip];
   cout<<number[ip]<<" "<<xc[ip]<<" "<<yc[ip]<<endl;
   ip++;
}
}
myReadFile.close();


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
   d2 = (sqrt((TMath::Power(xprimeo.X(),2))+(TMath::Power(xprimeo.Y(),2))));
   mago = m0 + m1*thetao/d2 + m2*TMath::Power(thetao,2)/d2 + m3*TMath::Power(thetao,3)/d2;

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
   d2 = (sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2))));
   mag = m0 + m1*theta/d2 + m2*TMath::Power(theta,2)/d2 + m3*TMath::Power(theta,3)/d2;
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
