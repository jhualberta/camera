{
//gPad->SetFixedAspectRatio(1);

//define variables
float xpix;
float ypix;
float mag;
float alpha = 1.95e3;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta = 0;
TVector3 xcp(7289.7,193.5,4246.6);






std::vector<TVector3>pmtList;	

ifstream myReadFile;
myReadFile.open("chosen_pmts.txt");


float xc[24], yc[24], zc[24];
int ip=0;
TVector3 temp;
if (myReadFile.is_open()) {
while (!myReadFile.eof()) {

   myReadFile >> xc[ip] >> yc[ip] >> zc[ip];
   cout<<xc[ip]<<" "<<yc[ip]<<" "<<zc[ip]<<endl;
   temp.SetX(xc[ip]); temp.SetY(yc[ip]); temp.SetZ(zc[ip]);
   pmtList.push_back(temp);
   ip++;
}
}
myReadFile.close();




//form the image
float angle = 15.5/180*TMath::Pi();             //angle of rotation of the camera with respect to the vertical up
TVector3 north(sin(angle),cos(angle),0);
TVector3 ko(xcp.Unit());
TVector3 io(north-(ko * north) * ko); io=io.Unit();
TVector3 jo(ko.Cross(io));
//angle of roation of k on x and y direction
float rx = 6.75/180*TMath::Pi();
float ry = 1.5/180*TMath::Pi();
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

picture.Draw("SAME");
//picture.Draw();
c1->SetCanvasSize(4310*0.3,2868*0.3);
//c1->SaveAs("../plot/mix_p.png");
}

