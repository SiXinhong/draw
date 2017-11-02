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
*  ��ͼƬ�е���ɫ��������  *
 *********************/
user_head *_head = NULL;
sort_color *sort_head = NULL;
int tmp_count = 0;

int main(int argc, char *argv[]){
    IplImage* img=cvLoadImage("img\\1.jpg");//����ͼ��ͼ�����Debug�ļ�������������·��
    IplImage *pResult=cvCreateImage(cvSize(img->width,img->height),IPL_DEPTH_8U,3);//����������ʾ��ͼ�񣬶�ֵͼ��

    char outimg[] = "data\\out_img.txt"; // �˴�д���ļ���
    char str_time[] = "data\\time.txt"; // �˴�д���ļ���
    char _statistics[] = "data\\statistics.txt"; // �˴�д���ļ���
    char _statistics_end[] = "data\\_statistics_af_caculate.txt"; // �˴�д���ļ���

    //ofstream or_imag(original);
    ofstream out_img(outimg);
    ofstream out_time(str_time);
    ofstream statistics(_statistics);
    ofstream statistics_af_caculate(_statistics_end);
    ofstream out("data\\color.txt");
    ofstream statistics_af_caculate_end("data\\statistics_af_caculate_end.txt");

    int i,j;
    CvMat*samples=cvCreateMat((img->width)*(img->height),1,CV_32FC3);//������������CV_32FC3����λ����ͨ������ɫͼ��
    CvMat*clusters=cvCreateMat((img->width)*(img->height),1,CV_32SC1);//��������Ǿ���CV_32SF1����λ����ͨ��
    CvMat*centers=cvCreateMat(nClusters,1,CV_32FC3);//��������Ǿ���CV_32SF1����λ����ͨ��

           int k=0;
           for (i=0;i<img->width;i++)
           {
                  for(j=0;j<img->height;j++)
                  {
                         CvScalar s;
                         //��ȡͼ��������ص����ͨ��ֵ��RGB��
                         s.val[0]=(float)cvGet2D(img,j,i).val[0];
                         s.val[1]=(float)cvGet2D(img,j,i).val[1];
                         s.val[2]=(float)cvGet2D(img,j,i).val[2];

                         //����ɫ���������
//                         insert(s.val[0],s.val[1],s.val[2],&_head);

////                         //sdnxq
//                         or_imag<< k+1 << " "
//                                << s.val[0] << " "
//                                << s.val[1] << " "
//                                << s.val[2] << " "
//                                <<endl; // fout�÷���coutһ��, ������д���ļ�����ȥ
                         cvSet2D(samples,k++,0,s);//�����ص���ͨ����ֵ��˳��������������
                  }
           }
                        /******************************
                        *  ��ԭʼ��ɫ��������ͬʱ������ı�  *
                         ******************************/
//           user_head *_tmp = _head;//��ʼ����¼����
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

//           statistics << "��ɫ����:" << tmp_count << endl;

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
//           *      �ڴ��ͷ�     *
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
                            * ͳ�ƾ������ɫ���� *
                             ****************/
/*****************
*  �����������ʱ��  *
 ****************/
           clock_t start,finish;
           double totaltime;
           start=clock();
           cvKMeans_3(samples,nClusters,clusters,cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,100,1.0),1, (CvRNG *)0,0, centers,0,out);//��ʼ���࣬�����Σ���ֹ���.0
                      /********************************
                      *          �����������ʱ��         *
                       ********************************/
           finish=clock();
           totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
           out_time << "\n�˳��������ʱ��Ϊ" << totaltime << " �룡" << endl;
                    /*********************************
                    * ��ͼƬ��ԭ������ɫ�滻Ϊ��ȡ�������ɫ *
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
                          *   ����ɫ���뵽�µ����������п�Ч��   *
                           ********************************/
                          CvScalar s;
                          //��ȡͼ��������ص����ͨ��ֵ��RGB��
                          s.val[0]=cvGet2D(centers,index,0).val[0];
                          s.val[1]=cvGet2D(centers,index,0).val[1];
                          s.val[2]=cvGet2D(centers,index,0).val[2];
                          cvSet2D(samples,k,0,s);
                            /**************************
                            *   ��ͼƬ��ԭ������ɫ�����滻  *
                            **************************/
                          cvSet2D(img,j,i,cvGet2D(centers,index,0));
                          cvSet2D(pResult,j,i,cvGet2D(centers,index,0));
                          k++;
                      }
                  }
                   /********************************
                   *  �Դ����ͼƬ��ɫ����ͬʱ������ı�  *
                    ********************************/
                      float a,b,c;
                      user_head *_tmp= _head;//��ʼ����¼����;
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
                      *  �°汾�����㷨�õ��ı���  *
                       ***********************/
     CvMat*new_samples=cvCreateMat(tmp_count,1,CV_32FC3);//������������CV_32FC3����λ����ͨ������ɫͼ��
     CvMat*new_clusters=cvCreateMat(tmp_count,1,CV_32SC1);//��������Ǿ���CV_32SF1����λ����ͨ��
     CvMat*new_centers=cvCreateMat(new_nClusters,1,CV_32FC3);//��������Ǿ���CV_32SF1����λ����ͨ��
                      statistics << "�������ɫ������" << tmp_count << endl;

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
                          //��ȡͼ��������ص����ͨ��ֵ(RGB)ͼƬ�д�ŵ�ΪBGR����RGB��������ط�Ҫ��һ��˳��
                          s.val[0]=/*(int)*/a;
                          s.val[1]=/*(int)*/b;
                          s.val[2]=/*(int)*/c;
                          allColor[k].setRed(tmp_color->data.b);
                          allColor[k].setGreen(tmp_color->data.g);
                          allColor[k].setBlue(tmp_color->data.r);
                          cvSet2D(new_samples,k++,0,s);//�����ص���ͨ����ֵ��˳��������������
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
                         *  �°汾�����㷨  *
                          ***************/
                      int center_or_label[30];
                      for(int i = 0;i < 30;i++){
                          center_or_label[i] = -1;
                      }
           new_cvKMeans_3(new_samples,new_nClusters,new_clusters,
                      cvTermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.01),20000/*attemps*/, (CvRNG *)0,0,
                      new_centers,0,out,num,center_or_label);//��ʼ���࣬�����Σ���ֹ���.0


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

           _tmp = _head;//��ʼ����¼����
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


           IplImage* img_original=cvLoadImage("img\\1.jpg");//����ͼ��ͼ�����Debug�ļ�������������·��
           cvNamedWindow( "ԭʼͼ��", 1 ); //��������
           cvShowImage( "ԭʼͼ��", img_original  ); //��ʾͼ��

           QApplication showColorExe(argc, argv);
           QWidget *parent = 0;
           MainWindow w(parent,ca[0],ca[1],ca[2],ca[3]);
           w.show();

           return showColorExe.exec();

}
