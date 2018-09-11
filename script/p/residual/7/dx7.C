{
//gPad->SetFixedAspectRatio(1);
//gStyle->SetOptTitle(kFALSE);
gStyle->SetOptStat(0);
//gStyle->SetPalette(53);
//define variables
float xpix;
float ypix;
float mag;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta = 0;

std::vector<TVector3>pmtList;	

ifstream myReadFile;
myReadFile.open("../../paras7.txt");
float para[7];
int ip=0;
if (myReadFile.is_open()) {
while (!myReadFile.eof()) {

   myReadFile >> para[ip];
   //cout<<para[ip]<<endl;
   ip++;
}
}
myReadFile.close();

float m1 = para[0];
TVector3 xcp(para[1],para[2],para[3]);
float angle = para[4];  
float rx =  para[5];
float ry = para[6];
//double m0 = para[7];double m2 = para[8];double m3 = para[9];
float d;
double deltax;

ifstream myReadFile2;
myReadFile2.open("../../cpmts.txt");
float xc[136], yc[136], zc[136];
int ip2=0;
TVector3 temp;
if (myReadFile2.is_open()) {
while (ip2<136) {

   myReadFile2 >> xc[ip2] >> yc[ip2] >> zc[ip2];
   //cout<<xc[ip2]<<" "<<yc[ip2]<<" "<<zc[ip2]<<endl;
   temp.SetX(xc[ip2]); temp.SetY(yc[ip2]); temp.SetZ(zc[ip2]);
   pmtList.push_back(temp);
   ip2++;
}
}myReadFile2.close();

ifstream myReadFile3;
myReadFile3.open("../../pos.txt");
std::string linep;
getline(myReadFile3,linep);
float number[136], xc2[136], yc2[136];
int ip3=0;
if (myReadFile3.is_open()) {
while (ip3<136.) {

   myReadFile3 >> number[ip3] >> xc2[ip3] >> yc2[ip3];
   //cout<<xc2[ip3]<<endl;

   ip3++;
}
}
myReadFile3.close();

//form the image            

TVector3 north(sin(angle),cos(angle),0);
TVector3 ko(xcp.Unit());
TVector3 io(north-(ko * north) * ko); io=io.Unit();
TVector3 jo(ko.Cross(io));

TVector3 k(ko + tan(rx)*io + tan(ry)*jo); k = k.Unit();
TVector3 i(north-(k * north) * k); i=i.Unit();
TVector3 j(k.Cross(i));

//TH2F *h = new TH2F ("HPicture","calculated",4310,-2155,2155,4310,-2155,2155);
int bin = 100;
TH2D* h = new TH2D("h","histogram",bin,-2155,2155,bin,-1434,1434);
//h->SetMarkerStyle(8);
h->SetMarkerSize(2);
double r;
int q = 0;
while (q<136) {
  pmt = pmtList[q];
  TVector3 kp(-pmt.Unit());
  TVector3 ip3(north-(kp * north) * kp); ip3=ip3.Unit();
  TVector3 jp(kp.Cross(ip3));
  TVector3 xprime((pmt-xcp) * i,(pmt-xcp) * j, (pmt-xcp) * k);
  theta = abs(atan(sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2)))/(xprime.Z())));
  d = (sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2))));
  //mag = m0 + m1*theta/d + m2*TMath::Power(theta,2)/d + m3*TMath::Power(theta,3)/d;
  mag = m1*theta/d;
  xpix = xprime.X()*mag;
  ypix = xprime.Y()*mag;


   //h->Fill(ypix,yc2[q]);
   deltax = xpix - xc2[q];  cout<<xc2[q]<<" "<<yc2[q]<<" "<<deltax<<endl;
   r = sqrt((TMath::Power((xc2[q]-xpix),2))+(TMath::Power((yc2[q]-ypix),2))); 
   h->SetBinContent((xc2[q]+2155)/(4310/bin),(yc2[q]+1434)/(2868/bin),deltax);   
   q++;
}

h->Draw("colz");

c1->SetCanvasSize(4310*0.2,2868*0.2);
h->GetXaxis()->SetTitle("x pixel position");
h->GetYaxis()->SetTitle("y pixel position");
h->SetTitle("7 parameters delta x");


//TF1*f = new TH1("func","y",-2000.,2000);
//f->Draw("same");








c1->SaveAs("./plots/dx7.pdf");














}
