#ifndef primitives_H
#define primitives_H
#include <iostream>
#include <string>
#include <sstream>

class point{
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

class face{
 protected:
  point point1_;
  point point2_;
  point point3_;
  point point4_;

 public:
  face(
      const point, 
      const point, 
      const point, 
      const point
  );

  face();
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


class hex{
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
};

#endif
