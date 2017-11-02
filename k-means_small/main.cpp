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
#include "mainwindow.h"

/********************
**  caculate time  **
********************/
#include<time.h>
using namespace std;

#define nClusters 300
#define new_nClusters 4
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

    //ofstream or_imag(original);
    ofstream out_img(outimg);
    ofstream out_time(str_time);
    ofstream statistics(_statistics);
    ofstream statistics_af_caculate(_statistics_end);
    ofstream out("data\\color.txt");
    ofstream statistics_af_caculate_end("data\\statistics_af_caculate_end.txt");

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

                         //对颜色进行排序等
//                         insert(s.val[0],s.val[1],s.val[2],&_head);

////                         //sdnxq
//                         or_imag<< k+1 << " "
//                                << s.val[0] << " "
//                                << s.val[1] << " "
//                                << s.val[2] << " "
//                                <<endl; // fout用法和cout一致, 不过是写到文件里面去
                         cvSet2D(samples,k++,0,s);//将像素点三通道的值按顺序排入样本矩阵
                  }
           }
                        /******************************
                        *  对原始颜色进行排序同时输出到文本  *
                         ******************************/
//           user_head *_tmp = _head;//初始化记录链表
//           float a,b,c;
//           tmp_count = 0;
//           while(_tmp != NULL){
//               tmp_count += 1;
//               a = _tmp->data.r;
//               b = _tmp->data.g;
//               c = _tmp->data.b;

////               //sdnxq
////               or_imag << a << " "
////                       << b << " "
////                       << c << " "
////                       << _tmp->_num
////                       << endl;

//               sortcolor(a,b,c,_tmp->_num,&sort_head);
//               _tmp = _tmp->next;
//           }

//           statistics << "颜色总数:" << tmp_count << endl;

//           sort_color* tmp_color = sort_head;
//           k = 0;
//           while(tmp_color != NULL){
//               a = tmp_color->data.r;
//               b = tmp_color->data.g;
//               c = tmp_color->data.b;
//               statistics << left << ++k << " "
//                          << setw(3) << a << " "
//                          << setw(3) << b << " "
//                          << setw(3) << c << " "
//                          << setw(3) <<
//                             tmp_color->color_num
//                          <<endl;
//               tmp_color = tmp_color->next;
//           }

//           /*****************
//           *      内存释放     *
//            ****************/
//           _tmp = _head;
//           user_head *nex;
//           if(_tmp != NULL)
//               nex = _tmp->next;
//           while(_tmp != NULL){
//               free(_tmp);
//               _tmp = nex;
//               if(_tmp != NULL)
//                   nex = _tmp->next;
//           }

//           tmp_color = sort_head;
//           sort_color *nex_color;
//           if(tmp_color != NULL)
//               nex_color = tmp_color->next;
//           while(tmp_color != NULL){
//               free(tmp_color);
//               tmp_color = nex_color;
//               if(tmp_color != NULL)
//                   nex_color = tmp_color->next;
//           }
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
           finish=clock();
           totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
           out_time << "\n此程序的运行时间为" << totaltime << " 秒！" << endl;
                    /*********************************
                    * 将图片中原来的颜色替换为提取过后的颜色 *
                     ********************************/
           _head = NULL;
           sort_head = NULL;
           tmp_count = 0;
           k = 0;
           for (i=0;i<img->width;i++){
                      for(j=0;j<img->height;j++)
                      {
                          int index =cvGet2D(clusters,k,0).val[0];
                          //or_imag <<index<<endl;
//                          out_img << k+1 << " " << index << " "
//                                  << cvGet2D(centers,index,0).val[0]<<" "
//                                  << cvGet2D(centers,index,0).val[1]<<" "
//                                  << cvGet2D(centers,index,0).val[2]<<" "
//                                  <<endl;
                          float need_color = 0;
                          need_color = cvGet2D(centers,index,0).val[0]*0.072169
                                  + cvGet2D(centers,index,0).val[1]*0.715160
                                  + cvGet2D(centers,index,0).val[2]*0.212671;
                          if(need_color < 230 && need_color > 40){
                                  insert(cvGet2D(centers,index,0).val[0],
                                         cvGet2D(centers,index,0).val[1],
                                         cvGet2D(centers,index,0).val[2],
                                         &_head);
                                  }

                          /********************************
                          *   把颜色导入到新的样本矩阵中看效果   *
                           ********************************/
                          CvScalar s;
                          //获取图像各个像素点的三通道值（RGB）
                          s.val[0]=cvGet2D(centers,index,0).val[0];
                          s.val[1]=cvGet2D(centers,index,0).val[1];
                          s.val[2]=cvGet2D(centers,index,0).val[2];
                          cvSet2D(samples,k,0,s);
                            /**************************
                            *   把图片中原来的颜色进行替换  *
                            **************************/
                          cvSet2D(img,j,i,cvGet2D(centers,index,0));
                          cvSet2D(pResult,j,i,cvGet2D(centers,index,0));
                          k++;
                      }
                  }
                   /********************************
                   *  对处理后图片颜色排序同时输出到文本  *
                    ********************************/
                      float a,b,c;
                      user_head *_tmp= _head;//初始化记录链表;
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
     CvMat*new_samples=cvCreateMat(tmp_count,1,CV_32FC3);//创建样本矩阵，CV_32FC3代表位浮点通道（彩色图像）
     CvMat*new_clusters=cvCreateMat(tmp_count,1,CV_32SC1);//创建类别标记矩阵，CV_32SF1代表位整型通道
     CvMat*new_centers=cvCreateMat(new_nClusters,1,CV_32FC3);//创建类别标记矩阵，CV_32SF1代表位整型通道
                      statistics << "处理后颜色总数：" << tmp_count << endl;

                      sort_color* tmp_color;
                      tmp_color = sort_head;
                      k = 0;
                      int num[1200];
                      for(int i =0;i < 1000;i++){
                          num[i] = 0;
                      }

                      QColor allColor[nClusters];
                      while(tmp_color != NULL){
                          CvScalar s;
                          RGB2LAB(tmp_color->data.b,
                                  tmp_color->data.g,
                                  tmp_color->data.r,
                                  a,b,c/*(float)s.val[0],(float)s.val[1],(float)s.val[2]*/);
                          //获取图像各个像素点的三通道值(RGB)图片中存放的为BGR不是RGB，所以这地方要换一下顺序
                          s.val[0]=/*(int)*/a;
                          s.val[1]=/*(int)*/b;
                          s.val[2]=/*(int)*/c;
                          allColor[k].setRed(tmp_color->data.b);
                          allColor[k].setGreen(tmp_color->data.g);
                          allColor[k].setBlue(tmp_color->data.r);
                          cvSet2D(new_samples,k++,0,s);//将像素点三通道的值按顺序排入样本矩阵
                          num[k] = tmp_color->color_num;
                          statistics_af_caculate << left << k << ","
                                                 << tmp_color->data.b << ","
                                                 << tmp_color->data.g << ","
                                                 << tmp_color->data.r << ","
                                                 << setw(3) <<
                                                    tmp_color->color_num
                                                 <<endl;
                          tmp_color = tmp_color->next;
                      }

                         /****************
                         *  新版本聚类算法  *
                          ***************/
                      int center_or_label[30];
                      for(int i = 0;i < 30;i++){
                          center_or_label[i] = -1;
                      }
           new_cvKMeans_3(new_samples,new_nClusters,new_clusters,
                      cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.01),20000/*attemps*/, (CvRNG *)0,0,
                      new_centers,0,out,num,center_or_label);//开始聚类，迭代次，终止误差.0


           for(int i = 0;i < new_nClusters;i++){
               statistics_af_caculate << "index:" << center_or_label[i]+1 << endl;
           }


           _head = NULL;
           sort_head = NULL;
           int end_count = 0;
           for(int i = 0;i < tmp_count;i++){
               int index =cvGet2D(new_clusters,i,0).val[0];
               if(index > -1){
                   insert(cvGet2D(new_centers,index,0).val[0],
                          cvGet2D(new_centers,index,0).val[1],
                          cvGet2D(new_centers,index,0).val[2],
                          &_head);
               }
           }

           _tmp = _head;//初始化记录链表
           while(_tmp != NULL){
               end_count += 1;
               a = _tmp->data.r;
               b = _tmp->data.g;
               c = _tmp->data.b;
               sortcolor(a,b,c,_tmp->_num,&sort_head);
               _tmp = _tmp->next;
           }

           tmp_color = sort_head;
           k = 0;

           QColor ca[new_nClusters];


           while(tmp_color != NULL){
               statistics_af_caculate_end << left << k++ << ","
                                      << tmp_color->data.r << ","
                                      << tmp_color->data.g << ","
                                      << tmp_color->data.b << ","
                                      << setw(3) <<
                                         tmp_color->color_num
                                      <<endl;

               tmp_color = tmp_color->next;
           }
           for(int i = 0;i < new_nClusters;i++){
               ca[i] = allColor[center_or_label[i]];
               statistics_af_caculate << "index111:" << center_or_label[i]<< endl;
           }


           IplImage* img_original=cvLoadImage("img\\1.jpg");//加载图像，图像放在Debug文件夹里，这里是相对路径
           cvNamedWindow( "原始图像", 1 ); //创建窗口
           cvShowImage( "原始图像", img_original  ); //显示图像

           QApplication showColorExe(argc, argv);
           QWidget *parent = 0;
           MainWindow w(parent,ca[0],ca[1],ca[2],ca[3]);
           w.show();

           return showColorExe.exec();

}
