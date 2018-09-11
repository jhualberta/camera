{




double p = [px py];  //this is known
double a;  double b;
//double px; double py;
double in1 = [inx iny];   //this is kown
//double iny; double inx;
double lap; double lop; double loa;
double lba; double lob; double loa;

double theta1;  //angle apo
double theta2;  //first incidence angle
double theta3;  //first refraction angle
double theta4; 
double theta5;
double theta6;
double theta7;
double theta8;
double theta9;
double theta10;
double theta11;


double in2; //coordinate of first and second incidece ray 
double ain1; double ain2  //their angles withe respect to x aixis

double n1 = 1.3; double n2 = 1.5; double n3 = 1.3; //refraction indexes

//the first triangle
double aopm = atan(py/px);
ain1 = atan(iny/inx)
loa = 6052;
lop = sqrt(px*px+py*py);

ain1 = atan(px/py)+theta1 - 90;
theta1 = 180-abs(ain1)-aopm;

lap =lop*cos(theta1) + sqrt(loa*loa+lop*lop*(cos(theta1)*cos(theta1)-1)); //or
//lap =lop*cos(theta1) - sqrt(loa*loa+lop*lop*(cos(theta1)*cos(theta1)-1));
double ax = px + cos(ain1)*lap; 
double ay = py + sin(ain1)*lap;
a = [ax ay]; //coordinate of a
theta2 = acos((lop*lop+loa*loa-lap*lap)/(2*lop*loa))
theta3 = theta1 +theta2;
theta4 = asin((sin(theta2)*n1)/(n2));  //apply snell's law


// the second triangle
lba = lob*cos(theta4) + sqrt(loa*loa+lob*lob*(cos(theta4)*cos(theta4)-1));  //apply cosine rule
theta5 = acos((loa*loa+lob*lob-lba*lba)/(2*loa*lob))  //apply cosine rule
theta6 = theta4 + theta5;
theta7 = asin((sin(theta2)*n2)/(n1)); 
lob = ???;  //inner radius of sphere
loa = 6052;
double axoa; double axob;
axoa = atan(ay/ax);
axob = axoa - theta5;
double bx; double by;
bx = cos(axob)*lob;
by = sin(axob)*lob
b = [bx by]; 


// the other interface
double loc = ???; double lod = 6052;
in2 = (theta7 + axob)-180; //second incidence angle
double aboc;
aboc = 180 - theta7-theta7;
double lbc;
lbc = sqrt(lob*lob+loc*loc-2*lob*loc*cos(aboc));
double cx; double cy;
cx = bx + cos(in2)*lbc; cy = by + cos(in2)*lbc
double c = [cx cy];
theta8 = asin(sin(theta7)*(n3/n2));
double aocd; aocd = 180 - theta8;
double lcd;
lcd = sqrt(lod*lod+loc*loc*(cos(aocd)*cos(aocd)-1)) + loc*cos(aocd)
theta9 = acos((loc*loc+lod*lod-lcd*lcd)/(2*loc*lod));
double axoc;  //angle of oc wrt x axisi
axoc = acos(cx/cy);
double axod;
axod = axoc-theta9;  //angle of od wrt x axis
double dx; double dy;
dx = cos(axod)*lod; dy = sin(axod)*lod;
double d = [dx dy];
//the last refraction
theta10 = theta8 - theta9;
theta11 = asin(theta10)*(n2/n1);


//the camera
double cam = ???; //z coordinate if camera 
double aode;
aode = 180 - theta11;
double ados;
ados = 90 + axod;
double ade; //angle of de wrt x axis
ade = -((180 - abs(aode) - abs(ados))+90);
double es; //error from camera
es = cot(ade)*cam;























