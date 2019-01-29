{
using namespace std;
gStyle->SetOptStat("0");
double n1 = 1.0; double n2 = 1.0; double n3 = 1.0; //refraction indexes
double loa = 6052; double loc = 6000; double lod = 6052; double lob = 6000; 
int bin = 100;
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
double aob2;
float xpix;
float ypix;
float magx; float magy;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta = 0;
float pp[12][4]; 
float pmt_3dx[1000][4]; float pmt_3dy[1000][4]; float pmt_3dz[1000][4];
float number[1000][4]; float pmt_pixxr[1000][4]; float pmt_pixyr[1000][4];
float pmt_pixx[1000]; float pmt_pixy[1000];
double theta_cam[4]; double phi_cam[4]; double r_cam[4];//{8438, 8558, 8399.44, 8401.64};
TVector3 xcpp[4]; 
TVector3 xcp;
double angle[4];                 //angle of rotation of the camera with respect to the vertical up
double rx[4];                    //angle of roation of k on x and y direction
double ry[4];
double mx1[4];
double my1[4];
double mx2[4]; 
double mx3[4];
double my2[4]; 
double my3[4];
std::vector<TVector3>pmtList;	
std::vector<TVector3>pmtList_p;	
std::vector<TVector3>pmtList_1;	
std::vector<TVector3>pmtList_3;	
std::vector<TVector3>pmtList_5;	
std::vector<TVector3>dataList;
TVector3 north;
TVector3 ko;
TVector3 io;
TVector3 jo;
TVector3 k;
TVector3 ispace;
TVector3 j;
TVector3 kp;
TVector3 ip;
TVector3 jp;
TVector3 disp;
TVector3 pprime;
TVector3 xprime;
TVector3 ks;
TVector3 is;
TVector3 js;
TVector3 p2D;
TVector3 ob;
TVector3 i2d;
TVector3 j2d;
TVector3 k2d;
TVector3 obxy;
TVector3 sub;
double deltax;
double deltay;
double thetax;
double thetay;
int in;
TVector3 temp;

//read the parameters
cout<<"start"<<endl;
//residual x plot
TH2D* residualpx = new TH2D("rxp","Residual in x of camera p",bin,-2155,2155,bin,-1434,1434);
TH2D* residual1x = new TH2D("rx1","Residual in x of camera 1",bin,-2155,2155,bin,-1434,1434);
TH2D* residual3x = new TH2D("rx3","Residual in x of camera 3",bin,-1434,1434,bin,-2155,2155);
TH2D* residual5x = new TH2D("rx5","Residual in x of camera 5",bin,-2155,2155,bin,-1434,1434);
//residual y plot
TH2D* residualpy = new TH2D("ryp","Residual in y of camera p",bin,-2155,2155,bin,-1434,1434);
TH2D* residual1y = new TH2D("ry1","Residual in y of camera 1",bin,-2155,2155,bin,-1434,1434);
TH2D* residual3y = new TH2D("ry3","Residual in y of camera 3",bin,-1434,1434,bin,-2155,2155);
TH2D* residual5y = new TH2D("ry5","Residual in y of camera 5",bin,-2155,2155,bin,-1434,1434);

residualpx->SetMarkerSize(2);
residualpy->SetMarkerSize(2);
residual1x->SetMarkerSize(2);
residual1y->SetMarkerSize(2);
residual3x->SetMarkerSize(2);
residual3y->SetMarkerSize(2);
residual5x->SetMarkerSize(2);
residual5y->SetMarkerSize(2);


//book the picture for all cameras
TH2F picturep("Camera_p","PMTs in fish eye lens (angle of view 85)(camera P)",4310,-2155,2155,2868,-1434,1434);
TH2F picture1("Camera_1","PMTs in fish eye lens (angle of view 85)(camera P)",4310,-2155,2155,2868,-1434,1434);
TH2F picture3("Camera_3","PMTs in fish eye lens (angle of view 85)(camera P)",2868,-1434,1434,4310,-2155,2155);
TH2F picture5("Camera_5","PMTs in fish eye lens (angle of view 85)(camera P)",4310,-2155,2155,2868,-1434,1434);

picturep.SetMarkerStyle(8);
picturep.SetMarkerSize(0.05);
picture1.SetMarkerStyle(8);
picture1.SetMarkerSize(0.05);
picture3.SetMarkerStyle(8);
picture3.SetMarkerSize(0.05);
picture5.SetMarkerStyle(8);
picture5.SetMarkerSize(0.05);



for(int i=0;i<4;i++){
in = 0;
ifstream myReadFile;
cout<<"i"<<" "<<i<<endl;
  if (i==0){myReadFile.open("paras/together/p.txt");}
  if (i==1){myReadFile.open("paras/together/1.txt");}
  if (i==2){myReadFile.open("paras/together/3.txt");}
  if (i==3){myReadFile.open("paras/together/5.txt");}
  if (myReadFile.is_open()) {
  while (!myReadFile.eof()) {
     myReadFile >> pp[in][i];
	 cout<<"pp[in][i]="<<pp[in][i]<<endl;
     in++;
  }
  }
  myReadFile.close();

  theta_cam[i] = pp[0][i];
  phi_cam[i] = pp[1][i];
  r_cam[i] = pp[11][i];
  xcpp[i].SetX(r_cam[i]*sin(theta_cam[i])*cos(phi_cam[i]));
  xcpp[i].SetY(r_cam[i]*sin(theta_cam[i])*sin(phi_cam[i]));
  xcpp[i].SetZ(r_cam[i]*cos(theta_cam[i])); 
  angle[i] = pp[2][i];                 //angle of rotation of the camera with respect to the vertical up
  rx[i] = pp[3][i];                    //angle of roation of k on x and y direction
  ry[i] = pp[4][i];
  mx1[i] = pp[5][i];
  my1[i] = pp[6][i];
  mx2[i] = pp[7][i]; 
  mx3[i] = pp[8][i];
  my2[i] = pp[9][i]; 
  my3[i] = pp[10][i];

  ifstream myReadFile2;
  in = 0;
  if (i==0){myReadFile2.open("pmt_3d/p/all.txt");}
  if (i==1){myReadFile2.open("pmt_3d/1/all.txt");}
  if (i==2){myReadFile2.open("pmt_3d/3/all.txt");}
  if (i==3){myReadFile2.open("pmt_3d/5/all.txt");}
  if (myReadFile2.is_open()) {
  while (!myReadFile2.eof()) {
     myReadFile2 >> pmt_3dx[in][i] >> pmt_3dy[in][i] >> pmt_3dz[in][i];
     if (i==0){pmtList_p.push_back(TVector3(pmt_3dx[in][i],pmt_3dy[in][i],pmt_3dz[in][i]));}
     if (i==1){pmtList_1.push_back(TVector3(pmt_3dx[in][i],pmt_3dy[in][i],pmt_3dz[in][i]));}
     if (i==2){pmtList_3.push_back(TVector3(pmt_3dx[in][i],pmt_3dy[in][i],pmt_3dz[in][i]));}
     if (i==3){pmtList_5.push_back(TVector3(pmt_3dx[in][i],pmt_3dy[in][i],pmt_3dz[in][i]));}
     //cout<<"x = "<<pmt_3dx[in][i]<<" y = "<<pmt_3dy[in][i]<<" z = "<<pmt_3dz[in][i]<<" in = "<<in<<endl;
     in++;
  }
  }
  myReadFile2.close();

  ifstream myReadFile3;
  //cout<<"i"<<endl;
  if (i==0){myReadFile3.open("pmt_pix/p/all.txt");}
  if (i==1){myReadFile3.open("pmt_pix/1/all.txt");}
  if (i==2){myReadFile3.open("pmt_pix/3/all.txt");}
  if (i==3){myReadFile3.open("pmt_pix/5/all.txt");}
  if (myReadFile3.is_open()) {
  in = 0;
  while (!myReadFile3.eof()) {
     myReadFile3 >> number[in][i] >> pmt_pixxr[in][i] >> pmt_pixyr[in][i];
     pmt_pixx[in] = pmt_pixxr[in][i];
     pmt_pixy[in] = pmt_pixyr[in][i];
     //cout<<"pos "<<pmt_pixx[in]<<" "<<pmt_pixy[in]<<" in = "<<in<<endl; 
     in++;
  }
  }
  myReadFile3.close();


//form the image

north.SetXYZ(sin(angle[i]),cos(angle[i]),0);
xcp = xcpp[i];
ko = xcp.Unit();
io = (north-(ko * north) * ko); io = io.Unit();
jo = ko.Cross(io);
k = ko + tan(rx[i])*io + tan(ry[i])*jo;k = k.Unit();
ispace = (north-(k * north) * k); 
ispace = ispace.Unit();
j = k.Cross(ispace);
if(i==0){pmtList = pmtList_p;}
if(i==1){pmtList = pmtList_1;}
if(i==2){pmtList = pmtList_3;}
if(i==3){pmtList = pmtList_5;}
for (Int_t q=0;q<pmtList.size(); q++) {
  pmt = pmtList[q];
  kp = -pmt.Unit();
  ip = north-(kp * north) * kp; ip = ip.Unit();
  jp = kp.Cross(ip);
  pprime = (pmt);
   //form image on camera
   xprime.SetXYZ((pprime-xcp) * ispace,(pprime-xcp) * j, (pprime-xcp) * k);
//******************************************************************************************************
  ks = (xcp.Cross(pprime)); ks = ks.Unit();
  js = (-xcp.Unit());
  is = (js.Cross(ks)); is = is.Unit();
  p2D.SetXYZ(pprime*is, pprime*js, pprime*ks);
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

 ob.SetXYZ(-cos(out), -sin(out), 0); 
 aob2 = abs(abs(out)-TMath::Pi()/2);
 //aob2 = atan(abs(ob.X()/abs(ob.Y())));
 // cout<<"aob2"<<" "<<aob2<<endl;
  //if (sin(aob2)*abs(cam[1])>loa){ 
  if (aob2>asin(loa/-cam[1])){ 
  //cout<<"aob2"<<aob2<<endl;
  //break;
  }
  i2d.SetXYZ(ispace*is, ispace*js, ispace*ks); i2d = i2d.Unit();
  j2d.SetXYZ(j*is, j*js, j*ks); j2d = j2d.Unit();
  k2d.SetXYZ(k*is, k*js, k*ks); k2d = k2d.Unit();
   //cout<<"k2d"<<" "<<k2d.X()<<" "<<k2d.Y()<<" "<<k2d.Z()<<" "<<endl;
  theta = abs(ob.Angle(-k2d));
  obxy = (ob-k2d*(ob*k2d)); obxy = obxy.Unit();

  //if (obxy.Angle(j2d) < TMath::Pi()/2){
  thetax = theta*(obxy*i2d); thetay = theta*(obxy*j2d);
  xpix = thetax*mx1[i] + mx2[i]*thetax*thetax + mx3[i]*thetax*thetax*thetax;
  ypix = thetay*my1[i] + my2[i]*thetay*thetay + my3[i]*thetay*thetay*thetay;
  deltax = (xpix - pmt_pixx[q]);  
  deltay = (ypix - pmt_pixy[q]);  
  } //end of the if condition checking if light need to be refracted


//******************************************************************************************************
   else{ //the light does not go through the AV
 	  theta = abs(atan(sqrt((TMath::Power(xprime.X(),2))+(TMath::Power(xprime.Y(),2)))/(-xprime.Z())));
	  sub.SetXYZ(xprime.X(), xprime.Y(),0);
	  thetax = theta*(sub.Unit().X()); thetay = theta*(sub.Unit().Y());
	  xpix = thetax*mx1[i] + mx2[i]*thetax*thetax + mx3[i]*thetax*thetax*thetax;
	  ypix = thetay*my1[i] + my2[i]*thetay*thetay + my3[i]*thetay*thetay*thetay;
	  deltax = (xpix - pmt_pixx[q]);  
	  deltay = (ypix - pmt_pixy[q]);  
	  //cout<<"fill at i="<<i<<" "<<"xpix="<<xpix<<" "<<"ypix="<<ypix<<"  outside AV"<<" theta="<<theta<<" "<<endl;
  }//end of if the light go through AV




    if(i==0){residualpx->SetBinContent((pmt_pixx[q]+2155)/(4310/bin),(pmt_pixy[q]+1434)/(2868/bin),deltax);}
    if(i==1){residual1x->SetBinContent((pmt_pixx[q]+2155)/(4310/bin),(pmt_pixy[q]+1434)/(2868/bin),deltax);}
    if(i==2){residual3x->SetBinContent((pmt_pixx[q]+1434)/(2868/bin),(pmt_pixy[q]+2155)/(4310/bin),deltax);}
    if(i==3){residual5x->SetBinContent((pmt_pixx[q]+2155)/(4310/bin),(pmt_pixy[q]+1434)/(2868/bin),deltax);}

    if(i==0){residualpy->SetBinContent((pmt_pixy[q]+2155)/(4310/bin),(pmt_pixy[q]+1434)/(2868/bin),deltay);}
    if(i==1){residual1y->SetBinContent((pmt_pixy[q]+2155)/(4310/bin),(pmt_pixy[q]+1434)/(2868/bin),deltay);}
    if(i==2){residual3y->SetBinContent((pmt_pixy[q]+1434)/(2868/bin),(pmt_pixy[q]+2155)/(4310/bin),deltay);}
    if(i==3){residual5y->SetBinContent((pmt_pixy[q]+2155)/(4310/bin),(pmt_pixy[q]+1434)/(2868/bin),deltay);}
	//cout<<"deltax="<<deltax<<" deltay="<<deltay<<endl;
	//cout<<"pos x="<<(pmt_pixx[q]+2155)/(4310/bin)<<" y="<<(pmt_pixy[q]+1434)/(2868/bin)<<endl;

      if(theta<view){
       if(xprime.Z()<0){
        if(i==0){picturep.Fill(xpix,ypix);}
        if(i==1){picture1.Fill(xpix,ypix);}
        if(i==2){picture3.Fill(xpix,ypix);}
        if(i==3){picture5.Fill(xpix,ypix);}
       
      }
    }

   }//end for all pmts
}//end of loop over 4 cameras
residual5x->Draw("colz");
//picture3.Draw();
}//end of the file









