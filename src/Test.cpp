#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include "opencv2/opencv.hpp"
#include "Caster.h"
#include <vector>
#include "Utils.h"
#include "Quaternion.h"

using namespace std;
using namespace pcl;
using namespace cv;

//#define TRANS_MATRIX //PASSED
//#define QUAT //FFAILED
//#define CLOUD_CAST //PASSED

//#define POINT_PARALLEL

void out(vector<PointXYZ> v) {
	for (int i = 0; i < v.size(); i++)
		cout << v[i].x << "\t" << v[i].y << "\t" << v[i].z << endl;
}



int main() {
	Caster cast = Caster();

	cast.centerSphere = PointXYZ(0, -2, -7);
	cast.radius = 26;

#ifdef POINT_PARALLEL
	cast.tangentialPoint = PointXYZ(0, -2, 19);
#else
	cast.tangentialPoint = PointXYZ(0, 24, -7);
#endif

//	PointXYZ A = PointXYZ(19, -13, 6);
//	PointXYZ B = PointXYZ(-19, 10, -4);
//	PointXYZ C = PointXYZ(-5, -20, -11);
//	PointXYZ D = PointXYZ(14, 4, -9);
//	PointXYZ E = PointXYZ(-9, 9, -17);
//	cast.calculateTangentialPlaneCoeff();
//	vector<PointXYZ> v;
//	v.push_back(A);
//	v.push_back(B);
//	v.push_back(C);
//	v.push_back(D);
//	v.push_back(E);
	PointXYZ p = PointXYZ(7,9,8);
	PointXYZ p2=PointXYZ(20,18,10);
	PointXYZ s =PointXYZ(7,9,5);
//	Quaternion v = Quaternion(0, p.x, p.y, p.z);

	PointXYZ I=p, C=p2;
			I=Utils::normalizeVector(I);
			C=Utils::normalizeVector(C);
			double angle = acos(Utils::dotProduct(I,C));
			cout<<angle<<endl;

//	Quaternion q = Quaternion(0.70711,0,-0.70711,0);
	Quaternion q = Quaternion(1.57,PointXYZ(0,1,0));
//	Quaternion q=Quaternion(2,4,6,4);
//	Quaternion temp2 = q.inv();
//	q.normalize();
//	Quaternion temp = (q*v);
//	temp.out();
//	cout<<Quaternion::rotate(p,q,PointXYZ(7,9,5));
//	q.out();



#ifdef CLOUD_CAST
	vector<PointXYZ> a = cast.castCloudPoints(v);
#endif

#ifdef TRANS_MATRIX
#ifdef POINT_PARALLEL
	PointXYZ A2 = PointXYZ(2.15,7-2,19);
	PointXYZ B2 = PointXYZ(-2.47,-9.07,19);
	PointXYZ C2 = PointXYZ(6.22,-2.27,19);
	PointXYZ D2 = PointXYZ(-3,2.1,19);
	PointXYZ E2 = PointXYZ(-2.9,-5.75,19);
#else
	PointXYZ A2 = PointXYZ(-3.52, 24, 45.91 - 7);
	PointXYZ B2 = PointXYZ(-24.2, 24, -29.91 - 7);
	PointXYZ C2 = PointXYZ(1.93, 24, -12.66 - 7);
	PointXYZ D2 = PointXYZ(17.46, 24, 22.25 - 7);
	PointXYZ E2 = PointXYZ(8.32, 24, -25.59 - 7);
#endif
	vector<PointXYZ> v1, v2;
	v2.push_back(A2);
	v2.push_back(B2);
	v2.push_back(C2);
	v2.push_back(D2);
	v2.push_back(E2);
	out(v2);
	out(a);
	cout << cast.calculateTransformationMatrix(v2, a) << endl;
#endif

#ifdef QUAT
#ifdef POINT_PARALLEL
	Point2f A2 = Point2f(2.15,7-2);
	Point2f B2 = Point2f(-2.47,-9.07);
	Point2f C2 = Point2f(6.22,-2.27);
	Point2f D2 = Point2f(-3,2.1);
	Point2f E2 = Point2f(-2.9,-5.75);
#else
//	Point2f A2 = Point2f(-3.52, 45.91);
//	Point2f B2 = Point2f(-24.2, -29.91);
//	Point2f C2 = Point2f(1.93, -12.66);
//	Point2f D2 = Point2f(17.46, 22.25);
//	Point2f E2 = Point2f(8.32, -25.59);
	Point2f A2 = Point2f(6, 9);
	Point2f B2 = Point2f(3, 1);
	Point2f C2 = Point2f(3, 5);
	Point2f D2 = Point2f(8, 3);
	Point2f E2 = Point2f(0, 8);
#endif
	vector<Point2f> v3;
	v3.push_back(A2);
	v3.push_back(B2);
	v3.push_back(C2);
	v3.push_back(D2);
	v3.push_back(E2);
//	out(v);cout<<endl;
	cout << v3 << endl << endl;

//	vector<PointXYZ> v2 = Caster::imageOnPlane(0, 3, 0, -27, PointXYZ(5, 9, 9), v);
	vector<PointXYZ> outq = Caster::imageOnPlane(cast.A, cast.B, cast.C, cast.D,
			cast.tangentialPoint, v3);
	out(outq);
//	for (int i = 0; i < v2.size();i++)
//	cout << v2[i] << endl;
#endif

	return 0;
}
