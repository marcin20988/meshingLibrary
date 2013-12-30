#ifndef primitives_H
#define primitives_H
#include <iostream>
#include <string>
#include <sstream>


namespace meshing
{

/**
 * \brief
 * container for different constants with static members only.  
 */
class constant
{
 public:
  /**
   * \brief
   * controls maximum distance at which two points are considered to be located
   * in the same place
   */
    static double tolerance;
};

/**
 * \brief
 * used to choose an axis
 */
enum coordinate {x,y,z,r,theta};

/**
 * \brief
 * w - wall; p - patch
 */
enum patchType {w, p};

/**
 * \brief
 * element rounding
 */
enum rounding {oneSided, twoSided};

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

  /**
   * \brief 
   * point are considered to be equal when all coordinates are the same within
   * tolerance given in constant class.
   */
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

  /**
   * \brief
   * point faces are equal if they consist of the same set of point labels (not
   * necessarily in the same order).
   */
  bool operator==(const face& F);

  /**
   * \brief
   * returns string in format \t\t( int int int int)\n
   */
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

/**
 * \brief
 * class for arc object 
 *
 * They are defined with point in instances of class
 * element and in class mesh they are assigned labels from the global point list
 */
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

  /**
   * \brief
   * assign labels for arc points
   *
   * Find arc points on the global list of points (pList) and assign their
   * position in the list (labels) to current arc instance
   */
  void label(const point *pList, const int pListLength);

  /**
   * \brief
   * set labels manualy
   *
   * Instead of finding arc points in the global point list assign labels
   * manualy
   */
  void label(int l1, int l2)
  {
      pointLabel1_ = l1;
      pointLabel2_ = l2;
  }
  
  /**
   * \brief
   * returns string in the format: \t\t arc int int (float float float)\n
   */
  std::string write();
};


/**
 * \brief
 * class for hex obejcts
 *
 * This class contains both list of point and list of labels. List of point
 * stores coordinates of every vertice in the hex and list of labels contains
 * their label on the global list. This way every instance of the hex class
 * contains full information about hex geometry and at the same time it can be
 * used to create a list of unique vertices needed for the final blockMeshDict
 */
class hex
{
 protected:
    point pointList_[8];
    int labelList_[8];
    int cells[3];
    double grading[3];
 public:

    hex();

    /**
     * \brief
     * create a hex with a set of 8 points
     *
     * Vertices numbering is consistent with standard OF convention
     */
    hex(point,point,point,point,point,point,point,point);
  
    /**
     * \brief
     * assign labels from the global point list
     *
     * Find hex points on the global list of points (pList) and assign their
     * position in the list (labels) to current hex instance.
     * If a particular point is not in the list it is appended to the list,
     * otherwise point is label of previously defined point is uded.
     */
    int assignLabels(point *& pList, int &pListLength);

    /**
     * \brief
     * number of cells in x,y and z directions
     */
    void nCell(int nX, int nY, int nZ){
        cells[0] = nX;
        cells[1] = nY;
        cells[2] = nZ;
    }

    /**
     * \brief
     * cell grading in the x,y and z directions
     */
    void nGrading(double nX, double nY, double nZ){
        grading[0] = nX;
        grading[1] = nY;
        grading[2] = nZ;
    }

    /**
     * \brief
     * return a string formated as hex entry for blockMeshDict
     */
    std::string write();

    /**
     * \brief
     * return a face on a given plane
     *
     * Plane is defined wit an axis entry {x,y,z,r,theta} and a value which
     * means that findFace(x,2.0) will try to find a face located on a plane
     * with x=2.0
     * Function always return a face. For every point with a desired coordinate
     * one of the face labels is defined, is less than four point are found
     * function use -1 as point label for returned face.
     */
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
    /**
     * \brief 
     * create an empty patch with a given name and type (p for 'patch', w for
     * 'wall')
     */
    patch(std::string name="xxx", patchType pType = p)
    {
        name_ = name;
        numberOfFaces_ = 0;
        faceList_ = new face[0];
        type_ = pType;
    };

    /**
     * \brief
     * append face to patch
     */
    void addFace(const face F);

    /**
     * \brief
     * return string formated as a single patch entry for blockMeshDict
     */
    std::string write();

    std::string name()
    {
        return name_;
    };
  
    /**
     * \brief
     * remove internal faces from patch
     *
     * algorythm is very simple - if there are two entries for the same face it
     * means that it is an internal face and should be removed from the list
     */
    int removeInternalFaces();
};

}//end namespace meshing
#endif

