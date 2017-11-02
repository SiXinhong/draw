#ifndef CACULATE_H
#define CACULATE_H
#include<stdio.h>
#include <fstream>
            /***************************************
            *       改进版k-means处理函数所需头文件      *
             ***************************************/
#include "cxcore.h"
#include "highgui.h"
#include "cvaux.h"
#include "D:\OpenCV\opencv\modules\core\src\precomp.hpp"

//using namespace cv;
/********************************
*      对图片中的颜色进行排序        *
 ********************************/
typedef struct _user_color{
        float r;
        float g;
        float b;
}user_color;

typedef struct head{
        head *next;
        user_color data;
        int _num;
        head(){
                next = NULL;
                data.r = 0;
                data.g = 0;
                data.b = 0;
                _num = 1;
        }
}user_head;

typedef struct _sort_color{
        _sort_color *next;
        int color_num;
        user_color data;
}sort_color;

extern int color_count;
extern int tmp_count;
void insert(float ,float ,float ,user_head **);
void sortcolor(float ,float ,float ,int ,sort_color **);

           /*******************************
           *       改进版k-means处理函数      *
            ******************************/
CV_IMPL int
cvKMeans_3( const CvArr* _samples, int cluster_count, CvArr* _labels,
           CvTermCriteria termcrit, int attempts, CvRNG*,
           int flags, CvArr* _centers, double* _compactness ,std::ofstream &);

double kmeans_3( cv::InputArray _data, int K,
                   cv::InputOutputArray _bestLabels,
                   cv::TermCriteria criteria, int attempts,
                   int flags, cv::OutputArray _centers ,std::ofstream &);
/*******************************
*       改进版k-means处理函数      *
 ******************************/
CV_IMPL int
new_cvKMeans_3( const CvArr* _samples, int cluster_count, CvArr* _labels,
CvTermCriteria termcrit, int attempts, CvRNG*,
int flags, CvArr* _centers, double* _compactness ,std::ofstream &,int *,int*);

double new_kmeans_3( cv::InputArray _data, int K,
        cv::InputOutputArray _bestLabels,
        cv::TermCriteria criteria, int attempts,
        int flags, cv::OutputArray _centers ,std::ofstream &,int *,int *);
/*static */void new_generateRandomCenter(const cv::vector<cv::Vec2f>& box, float* center, cv::RNG& rng,std::ofstream &);
/*static */inline float new_distance(const float* a, const float* b, int n);

void k_best(float (*Disdance)[300],int *center_result,int *index,int mem[][300],int *mem_num,
            int nClusters,int new_nClusters,float &sum,int *num,int layer,std::ofstream &out);
void initialization(float Disdance[][300],user_color* color,int mem[][300],int *mem_num,
                    int nClusters,int new_nClusters,std::ofstream &out);
float distribute(float Disdance[][300],int (*mem)[300],int *mem_num,
                 int *index,int new_nClusters,int nClusters,int *num,std::ofstream &out);
#endif // CACULATE_H

