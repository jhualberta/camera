{


double p2d[2];
double cam3[3];
double cam[2];  //2D coordiante of camera
double a[2];  double b[2]; double c[2]; double d[2];
double ain1;   //angle of first incidence ray wrt x axis
double lap; double lop; double lba; double lob = 6000; 
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
double n1 = 1.3; double n2 = 1.5; double n3 = 1.3; //refraction indexes
double aopm;
double aoa; double aob;
double loa = 6052; double loc = 6000; double lod = 6052;
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





double angle = 20;

p2d[0] = 8319; p2d[1] = -655;
//cam3[0] = 7289.7; cam3[1] = 193.5; cam3[2] = 4246.6;
cam3[0] = 6552.11; cam3[1] = 87.0668; cam3[2] = 3854.31;
//p2d[0] = cos(angle/180*TMath::Pi())*8293; p2d[1] = sin(angle/180*TMath::Pi())*8293;  //this is known

//cam3 = {p2d[1], p2d[2], p2d[3]};
cam[1] = -sqrt(cam3[0]*cam3[0] + cam3[1]*cam3[1] + cam3[2]*cam3[2]);



es = 0; //set a initial error
esn = 1;
n = 0;
while(esn>0.0000000001){
n = n + 1;
if(n>20){
break;
}
cout<<"                     into the loop number"<<n<<endl;

if(p2d[0]<0){
	ain1 = atan((cam[1]-p2d[1])/(cam[0]-est-p2d[0]));  
}
else{
	ain1 = atan((cam[1]-p2d[1])/(cam[0]-est-p2d[0])) - TMath::Pi();
}

//the first triangle
aopm = abs(atan(p2d[1]/p2d[0]));
cout<<"ain1"<<" "<<ain1<<endl;
cout<<"aopm"<<" "<<aopm<<endl;
lop = sqrt(p2d[0]*p2d[0]+p2d[1]*p2d[1]);
//ain1 = atan(p2d[0]/p2d[1])+theta1 - (TMath::Pi()/2);

if (p2d[0] > 0){
theta1 = (TMath::Pi())-abs(ain1)-aopm;
}
else{
theta1 = abs(ain1) - aopm;
}

cout<<"theta1"<<" "<<theta1<<endl;
cout<<"lop"<<" "<<lop<<endl;
cout<<"loa"<<" "<<loa<<endl;
//lap = lop*cos(theta1) + sqrt(loa*loa+lop*lop*(cos(theta1)*cos(theta1)-1)); //or
lap =lop*cos(theta1) - sqrt(loa*loa+lop*lop*(cos(theta1)*cos(theta1)-1));
cout<<"lap"<<" "<<lap<<endl;
a[0] = p2d[0] + cos(ain1)*lap; 
a[1] = p2d[1] + sin(ain1)*lap;
cout<<"coordinate of a"<<" "<<a[0]<<" "<<a[1]<<endl;
theta2 = acos((lop*lop+loa*loa-lap*lap)/(2*lop*loa));
cout<<"theta2"<<" "<<theta2<<endl;
theta3 = theta1 +theta2;
cout<<"theta3"<<" "<<theta3<<endl;
theta4 = asin((sin(theta3)*n1)/(n2));  //apply snell's law
cout<<"theta4"<<" "<<theta4<<endl;
if (theta4<asin(lob/loa)){        //check if the light go into the ball
// the second triangle
lba = loa*cos(theta4) - sqrt(lob*lob+loa*loa*(cos(theta4)*cos(theta4)-1));  //apply cosine rule
cout<<"lba"<<" "<<lba<<endl;
theta5 = acos((loa*loa+lob*lob-lba*lba)/(2*loa*lob));  //apply cosine rule
cout<<"theta5"<<" "<<theta5<<endl;
theta6 = theta4 + theta5;
cout<<"theta6"<<" "<<theta6<<endl;
theta7 = asin((sin(theta6)*n2)/(n3)); 
cout<<"theta7"<<" "<<theta7<<endl;
 //inner radius of sphere
loa = 6052;
aoa = asin(a[1]/loa);
aob = aoa - theta5;
cout<<"aob"<<" "<<aob<<endl;
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
cout<<"coordinate of b"<<" "<<b[0]<<" "<<b[1]<<endl; 
cout<<"ain2"<<" "<<ain2<<endl; 
aboc = (TMath::Pi()) - theta7-theta7;
cout<<"aboc"<<" "<<aboc<<endl;
lbc = sqrt(lob*lob+loc*loc-2*lob*loc*cos(aboc));
cout<<"lbc"<<" "<<lbc<<endl;
c[0] = b[0] + cos(ain2)*lbc; c[1] = b[1] + sin(ain2)*lbc;
cout<<"coordinate of c"<<" "<<c[0]<<" "<<c[1]<<endl;
theta8 = asin(sin(theta7)*(n3/n2));
aocd = (TMath::Pi()) - theta8;
lcd = sqrt(lod*lod+loc*loc*(cos(aocd)*cos(aocd)-1)) + loc*cos(aocd);
cout<<"lcd"<<" "<<lcd<<endl;
theta9 = acos((loc*loc+lod*lod-lcd*lcd)/(2*loc*lod));
cout<<"theta9"<<" "<<theta9<<endl;

aoc = -acos(c[0]/loc);

if (p2d[0]>0){	
	aod = aoc-theta9;  //angle of od wrt x axis	
	}
else{
	aod = aoc + theta9;	
}  

cout<<"aoc"<<" "<<aoc<<endl;
theta10 = theta8 - theta9;


}
else{
	theta10 = theta4;
	if(p2d[0]>0){
		aod = -(TMath::Pi()-theta4-theta10)-aoa;
	}
	else{
		aod = aoa + (TMath::Pi()-theta4-theta10);
	}
	
	
		
}	
d[0] = cos(aod)*lod; d[1] = sin(aod)*lod;
cout<<"aoc"<<" "<<aoc<<endl;
cout<<"coordinate of d"<<" "<<d[0]<<" "<<d[1]<<endl;
//the last refraction

theta11 = asin(sin(theta10)*(n2/n1));
cout<<"theta11"<<" "<<theta11<<endl;
//the camera
aode = (TMath::Pi()) - theta11;
ados = abs((TMath::Pi()/2) - abs(aod));
cout<<"ados"<<" "<<ados<<endl;
if(p2d[0]>0){
	out = -((TMath::Pi()) - abs(aode) - abs(ados))-(TMath::Pi()/2);
}
else{
	out = -(TMath::Pi()/2) + ((TMath::Pi()) - abs(aode) - abs(ados));
}
cout<<"out"<<" "<<out<<endl;
es = (1/(tan(out)))  *  (cam[1]-d[1])  +d[0];
cout<<"es"<<" "<<es<<endl;
esn = abs(es);
//cout<<"esn"<<" "<<esn<<endl;
est = est + es;

}
cout<<"est"<<" "<<est<<endl;
cout<<"cam[1]"<<" "<<cam[0]<<" "<<cam[1]<<endl;
}






















