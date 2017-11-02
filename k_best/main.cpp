#include "cxcore.h"
#include "highgui.h"
#include "cvaux.h"
#include <fstream>
#include<stdio.h>
#include <iomanip>
#include<QDebug>
#include "caculate.h"
#include "RGB2LAB.h"

#include <QtGui/QApplication>
#include "showcolor.h"


/********************
**  caculate time  **
********************/
#include<time.h>
using namespace std;

#define nClusters 300
#define new_nClusters 3
#define MY_FELEM(mat, i, j) CV_MAT_ELEM(*(mat), float, i, j)
#define MY_BELEM(mat, i, j) CV_MAT_ELEM(*(mat), BYTE, i, j)
#define MY_SELEM(mat, i, j) CV_MAT_ELEM(*(mat), short, i, j)
#define MY_LELEM(mat, i, j) CV_MAT_ELEM(*(mat), long, i, j)
#define MY_DELEM(mat, i, j) CV_MAT_ELEM(*(mat), double, i, j)

/**********************
*  对图片中的颜色进行排序  *
 *********************/
user_head *_head = NULL;
sort_color *sort_head = NULL;
int tmp_count = 0;


int main(int argc, char *argv[]){
    IplImage* img=cvLoadImage("img\\1.jpg");//加载图像，图像放在Debug文件夹里，这里是相对路径
    IplImage *pResult=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,3);//创建用于显示的图像，二值图像

    char outimg[] = "data\\out_img.txt"; // 此处写入文件名
    char str_time[] = "data\\time.txt"; // 此处写入文件名
    char _statistics[] = "data\\statistics.txt"; // 此处写入文件名
    char _statistics_end[] = "data\\_statistics_af_caculate.txt"; // 此处写入文件名

    ofstream out_img(outimg);
    ofstream out_time(str_time);
    ofstream statistics(_statistics);
    ofstream statistics_af_caculate(_statistics_end);
    ofstream out("data\\color.txt");

    int i,j;
    CvMat*samples=cvCreateMat((img->width)*(img->height),1,CV_32FC3);//创建样本矩阵，CV_32FC3代表位浮点通道（彩色图像）
    CvMat*clusters=cvCreateMat((img->width)*(img->height),1,CV_32SC1);//创建类别标记矩阵，CV_32SF1代表位整型通道
    CvMat*centers=cvCreateMat(nClusters,1,CV_32FC3);//创建类别标记矩阵，CV_32SF1代表位整型通道

           int k=0;
           for (i=0;i<img->width;i++)
           {
                  for(j=0;j<img->height;j++)
                  {
                         CvScalar s;
                         //获取图像各个像素点的三通道值（RGB）
                         s.val[0]=(float)cvGet2D(img,j,i).val[0];
                         s.val[1]=(float)cvGet2D(img,j,i).val[1];
                         s.val[2]=(float)cvGet2D(img,j,i).val[2];
                         cvSet2D(samples,k++,0,s);//将像素点三通道的值按顺序排入样本矩阵
                  }
           }
                            /*****************
                            * 统计聚类后颜色分类 *
                             ****************/
/*****************
*  计算程序运行时间  *
 ****************/
           clock_t start,finish;
           double totaltime;
           start=clock();
           cvKMeans_3(samples,nClusters,clusters,cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,100,1.0),1, (CvRNG *)0,0, centers,0,out);//开始聚类，迭代次，终止误差.0
                      /********************************
                      *          计算程序运行时间         *
                       ********************************/
                    /*********************************
                    * 将图片中原来的颜色替换为提取过后的颜色 *
                     ********************************/
           float a,b,c;
           sort_color* tmp_color;
           tmp_count = 0;
           k = 0;
           for (i=0;i<img->width;i++){
                      for(j=0;j<img->height;j++)
                      {
                          int index =cvGet2D(clusters,k,0).val[0];
                          float need_color = 0;
                          need_color = cvGet2D(centers,index,0).val[0]*0.072169
                                  + cvGet2D(centers,index,0).val[1]*0.715160
                                  + cvGet2D(centers,index,0).val[2]*0.212671;
                          if(need_color < 230){
                                  insert(cvGet2D(centers,index,0).val[0],
                                         cvGet2D(centers,index,0).val[1],
                                         cvGet2D(centers,index,0).val[2],
                                         &_head);
                                  }
                          cvSet2D(pResult,j,i,cvGet2D(centers,index,0));
                          k++;
                      }
                  }
//                   /********************************
//                   *  对处理后图片颜色排序同时输出到文本  *
//                    ********************************/
                      user_head *_tmp = _head;//初始化记录链表
                      _tmp = _head;//初始化记录链表
                      tmp_count = 0;
                      while(_tmp != NULL){
                          tmp_count += 1;
                          a = _tmp->data.r;
                          b = _tmp->data.g;
                          c = _tmp->data.b;
                          out_img << _tmp->_num << endl;
                          sortcolor(a,b,c,_tmp->_num,&sort_head);
                          _tmp = _tmp->next;
                      }
                      /***********************
                      *  新版本聚类算法用到的变量  *
                       ***********************/
                      statistics << "处理后颜色总数：" << tmp_count << endl;
                      tmp_color = sort_head;

                      int num[nClusters];
                      for(int i =0;i < nClusters;i++){
                          num[i] = 0;
                      }

                      user_color color[nClusters];
                      int index = 0;
                      QColor allColor[nClusters];
                      while(tmp_color != NULL){
                          RGB2LAB(tmp_color->data.b,
                                  tmp_color->data.g,
                                  tmp_color->data.r,
                                  a,b,c/*(float)s.val[0],(float)s.val[1],(float)s.val[2]*/);
                          //获取图像各个像素点的三通道值(RGB)图片中存放的为BGR不是RGB，所以这地方要换一下顺序
                          color[index].r = (int)a;
                          color[index].g = (int)b;
                          color[index].b = (int)c;

                          num[index] = tmp_color->color_num;
                          //out << "color_num: " << num[index] << endl;

                          allColor[index].setRed(tmp_color->data.b);
                          allColor[index].setGreen(tmp_color->data.g);
                          allColor[index].setBlue(tmp_color->data.r);

                          statistics_af_caculate << left << index << ","
                                                 << tmp_color->data.b << ","
                                                 << tmp_color->data.g << ","
                                                 << tmp_color->data.r << ","
                                                 << setw(3) <<
                                                    tmp_color->color_num
                                                 <<endl;
                          tmp_color = tmp_color->next;

                          index ++;
                      }

                      float Disdance[nClusters][nClusters];
                      int mem[new_nClusters][nClusters];
                      int mem_num[new_nClusters];
                      initialization(Disdance,color,mem,mem_num,index,new_nClusters,out);
                      int center_result[new_nClusters],index_k_best[nClusters+1];
                      float sum = 0;
                      out << "index: " << index << endl;
                      k_best(Disdance,center_result,index_k_best,mem,
                             mem_num,index,new_nClusters,sum,num,0,out);
//                        /*********************
//                        *  index记录颜色总个数  *
//                         *********************/
                      out << "end sum:" << sum << endl;
                      QColor ca[new_nClusters];
                      for(int i = 0;i < new_nClusters;i++){
                          out << center_result[i] -1<< " ";
                          ca[i] = allColor[center_result[i] -1];
                      }
                      out << endl;

//                      for(int i =0;i < index;i++){
//                          out << "num:" << num[i] << endl;
//                      }



                  finish=clock();
                  totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
                  out_time << "\n此程序的运行时间为" << totaltime << " 秒！" << endl;

                  IplImage* img_original=cvLoadImage("img\\1.jpg");//加载图像，图像放在Debug文件夹里，这里是相对路径
                  cvNamedWindow( "原始图像", 1 ); //创建窗口
                  cvShowImage( "原始图像", img_original  ); //显示图像


    QApplication showColorExe(argc, argv);
    QWidget *parent = 0;
    showColor w(parent,ca[0],ca[1],ca[2]);
    w.show();

    return showColorExe.exec();

}
