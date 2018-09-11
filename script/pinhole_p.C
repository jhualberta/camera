{
//gPad->SetFixedAspectRatio(1);

//define variables
float xpix;
float ypix;
float mag;
float alpha = 1.5e3;
float view = (TMath::Pi()/4);
TVector3 pmt;
double theta = 0;
TVector3 xcp(7289.7,193.5,4246.6);




//load the PMTs position
std::vector<TVector3>pmtList;	
FILE *stream=fopen("../data/database20040923b.dat","r");
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
TVector3 north(0,1,0);
TVector3 k(xcp.Unit());
TVector3 i(north-(k * north) * k); i=i.Unit();
TVector3 j(k.Cross(i));
TH2F picture("HPicture","PMTs as circle (camera P)",4096,-2048,2048,4096,-2048,2048);
picture.SetMarkerStyle(8);
picture.SetMarkerSize(0.1);
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
   mag = alpha/(xprime.Z());
   xpix = xprime.X()*mag;
   ypix = xprime.Y()*mag;
   //test if thepoint is in the angle of view
   theta = abs(atan(sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2)))/(xprime.Z())));
    if(theta<view){
     if(xprime.Z()>0){
      picture.Fill(xpix,ypix);
     }
    }
   }
}

picture.Draw();
//c1->SaveAs("../plot/points.pdf");

}
