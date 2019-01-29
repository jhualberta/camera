{
double n1 = 1.0; double n2 = 1.0; double n3 = 1.0; //refraction indexes
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
double aob2;
float xpix;
float ypix;
float magx; float magy;
float view = (TMath::Pi()/2.118);
TVector3 pmt;
double theta = 0;
float pp[12][4]; 
float pmt_3dx[200][4]; float pmt_3dy[200][4]; float pmt_3dz[200][4];
float number[200][4]; float pmt_pixx[200][4]; float pmt_pixy[200][4];
double theta_cam[4]; double phi_cam[4]; double r_cam[4];//{8438, 8558, 8399.44, 8401.64};
TVector3 xcp[4]; 
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
TVector3 north[4];
TVector3 ko[4];
TVector3 io[4];
TVector3 jo[4];
TVector3 k[4];
TVector3 ispace[4];
TVector3 j[4];
TVector3 kp[4];
TVector3 ip[4];
TVector3 jp[4];
TVector3 disp;
TVector3 pprime;
TVector3 xprime;
TVector3 ks;
TVector3 is;
TVector3 js;
TVector3 p2D;
int in;


//read the parameters
cout<<"start"<<endl;
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
	 //cout<<pp[in][i]<<" "<<"pp[in][i]"<<endl;
     cout<<"pp[in][i]"<<" "<<pp[in][i]<<endl;
     in++;
  }
  }
  myReadFile.close();

  theta_cam[i] = pp[0][i];
  phi_cam[i] = pp[1][i];
  r_cam[i] = pp[11][i];
  xcp[i].SetX(r_cam[i]*sin(theta_cam[i])*cos(phi_cam[i]));
  xcp[i].SetY(r_cam[i]*sin(theta_cam[i])*sin(phi_cam[i]));
  xcp[i].SetZ(r_cam[i]*cos(theta_cam[i])); 
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
  //cout<<"i"<<endl;
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
     myReadFile3 >> number[in][i] >> pmt_pixx[in][i] >> pmt_pixy[in][i];
     in++;
  }
  }
  myReadFile3.close();

cout<<"angel[i]"<<" "<<angle[i]<<endl;
north[i].SetXYZ(sin(angle[i]),cos(angle[i]),0);
}
}
