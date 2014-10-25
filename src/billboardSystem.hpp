#ifndef __BILLBOARD_SYSTEM_H__
#define __BILLBOARD_SYSTEM_H__
#include <vector>
namespace xishanju{
  class Billboard{
  private:
    float x;
    float y;
    float z;
    
    float x_width;
    float y_width;

  public:
    explicit Billboard(float x, float y, float z, float x_width = 106.0, float y_width = 43.0);
    ~Billboard();

    void drawBillboard();
  };
  class BillboardSystem{
  private:
    std::vector<xishanju::Billboard> billboards_;
  public:
    BillboardSystem();
    ~BillboardSystem();

    bool initBillboards();
    void drawBillboards();

  private:
    
  };
}

#endif
