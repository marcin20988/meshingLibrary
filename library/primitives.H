#ifndef primitives_H
#define primitives_H
#include <iostream>
#include <string>
#include <sstream>

namespace meshing
{

class constant
{
 public:
    static double tolerance;
};

enum coordinate {x,y,z,r,theta};
enum patchType {w, p};
enum rounding {oneSided, twoSided};
enum coords { xyz, rThetaZ, zzz };

class point
{
 protected:
  double x_;
  double y_;
  double z_;

 public:
  point(double x, double y, double z);
  point();

  double x() const;
  double y() const;
  double z() const;

  point& operator=(const point&);
  bool operator==(const point&);
};

class face
{
 protected:
 protected:
  int label1_;
  int label2_;
  int label3_;
  int label4_;

 public:
  face(
      const int l1,
      const int l2,
      const int l3,
      const int l4
  );

  face();
  face& operator=(const face& F);
  std::string write();

  int label(const int i) const
  {
     int value = -1;
     switch(i)
     {
         case 0:
             value = label1_;
             break;
         case 1:
             value = label2_;
             break;
         case 2:
             value = label3_;
             break;
         case 3:
             value = label4_;
             break;
     }

     return value;
  };

};

class arc
{
 protected:
  point arcPoint_;
  point p1_;
  point p2_;

  int pointLabel1_;
  int pointLabel2_;

 public:
  arc();
  arc(int, int, point);
  arc(point, point, point);
  bool operator==(const arc) const;
  int label1() const
  {
      return pointLabel1_;
  }
  int label2() const
  {
      return pointLabel2_;
  }

  void label(const point *pList, const int pListLength);

  void label(int l1, int l2)
  {
      pointLabel1_ = l1;
      pointLabel2_ = l2;
  }
  
  std::string write();
};


class hex
{
 protected:
    point pointList_[8];
    int labelList_[8];
    int cells[3];
    int grading[3];
 public:

    hex();
    hex(point,point,point,point,point,point,point,point);
  
    int assignLabels(point *& pList, int &pListLength);
    void nCell(int nX, int nY, int nZ){
        cells[0] = nX;
        cells[1] = nY;
        cells[2] = nZ;
    }
    void nGrading(int nX, int nY, int nZ){
        grading[0] = nX;
        grading[1] = nY;
        grading[2] = nZ;
    }
    std::string write();

    face findFace(coordinate axis, double value) const;

};

class patch
{
 protected:
    std::string name_;
    int numberOfFaces_;
    face *faceList_;
    patchType type_;

 public:
    patch(std::string name="xxx", patchType pType = p)
    {
        name_ = name;
        numberOfFaces_ = 0;
        faceList_ = new face[0];
        type_ = pType;
    };

    void addFace(const face F);

    std::string write();

    std::string name()
    {
        return name_;
    };
};

}//end namespace meshing
#endif

