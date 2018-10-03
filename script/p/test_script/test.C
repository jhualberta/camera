{
//gPad->SetFixedAspectRatio(1);
//gStyle->SetOptTitle(kFALSE);

gStyle->SetOptStat("n");
//define variables
float xpix;
float ypix;
float mag;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta = 0;


std::vector<TVector3>pmtList;	


ifstream myReadFile;
myReadFile.open("paras10.txt");
float para[10];
int ip=0;
if (myReadFile.is_open()) {
while (!myReadFile.eof()) {

   myReadFile >> para[ip];
   cout<<para[ip]<<endl;
   ip++;
}
}
myReadFile.close();



float m1 = para[0];
TVector3 xcp(para[1],para[2],para[3]);
float angle = para[4];  
float rx =  para[5]+0.3/180*TMath::Pi();
float ry = para[6]+0.3/180*TMath::Pi();
double m0 = para[7];double m2 = para[8];double m3 = para[9];
float d;




ifstream myReadFile2;
myReadFile2.open("cpmts.txt");
float xc[186], yc[186], zc[186];
int ip2=0;
TVector3 temp;
if (myReadFile2.is_open()) {
while (ip2<186) {

   myReadFile2 >> xc[ip2] >> yc[ip2] >> zc[ip2];
   //cout<<xc[ip2]<<" "<<yc[ip2]<<" "<<zc[ip2]<<endl;
   temp.SetX(xc[ip2]); temp.SetY(yc[ip2]); temp.SetZ(zc[ip2]);
   pmtList.push_back(temp);
   ip2++;
}
}myReadFile2.close();


//form the image            

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
  pmt = pmtList[q];
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
   mag = m0 + m1*theta/d + m2*TMath::Power(theta,2)/d + m3*TMath::Power(theta,3)/d;
   xpix = xprime.X()*mag;
   ypix = xprime.Y()*mag;
   //cout<<xpix<<" "<<ypix<<endl;
   //test if thepoint is in the angle of view
    if(theta<view){
     if(xprime.Z()<0){
      picture.Fill(xpix,ypix);
     }
    }
   }
}



TH2F* picture2 = new TH2F("picture2","measured",4310,-2155,2155,2868,-1434,1434);
//TH2F picture2("HPicture","PMTs in fish eye lens (angle of view 85)(camera P)",4310,-2155,2155,2868,-1434,1434);
picture2->SetMarkerStyle(8);
picture2->SetMarkerColor(2);
picture2->SetMarkerSize(0.5);
ifstream myReadFile3;
myReadFile3.open("pos.txt");
std::string linep;
getline(myReadFile3,linep);
float number[186], xc2[186], yc2[186];
int ip3=0;
if (myReadFile3.is_open()) {
while (ip3<186) {

   myReadFile3 >> number[ip3] >> xc2[ip3] >> yc2[ip3];
   //cout<<xc2[ip3]<<" "<<yc2[ip3]<<endl;
   picture2->Fill(xc2[ip3],yc2[ip3]);
   ip3++;
}
}
myReadFile3.close();
picture.Draw();
picture2->Draw("SAME");
c1->SetCanvasSize(4310*0.3,2868*0.3);
  auto legend = new TLegend(0.7,0.8,0.9,0.9);
   //legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
   //legend->AddEntry(h1,"Histogram filled with random numbers","f");
   legend->AddEntry("picture","calculated","l");
   legend->AddEntry("picture2","measured","lep");
   legend->Draw();

c1->SaveAs("../../plot/test10.png");
}

