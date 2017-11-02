#include "caculate.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "CIEDE2000.h"
#include "D:\OpenCV\opencv\modules\core\src\matrix.cpp"
using namespace cv;
using namespace std;

//#define random(x) (rand()%x)

//ofstream out("C:\\Users\\9i\\Desktop\\test_result\\color.txt");
void insert(float _r,float _g,float _b,/*int &tmp_count,*/user_head **_head){
//        tmp_count ++;
        user_head *_p = NULL;
        if (*_head == NULL){
                _p = new(user_head);
                _p->data.r = _r;
                _p->data.g = _g;
                _p->data.b = _b;
                _p->next = NULL;
                _p->_num = 1;
                *_head = _p;
                return;
        }


        bool _has_flag = false;
        user_head *tmp = *_head;
        while(tmp != NULL){
//            out << "差值为：" << (fabs(tmp->data.r-_r))
//                << endl;
                if (fabs(tmp->data.r-_r)<0.001&&fabs(tmp->data.g-_g)<0.001&&fabs(tmp->data.b-_b)<0.001){
                        tmp->_num++;
//                        out <<
//                               (unsigned int)tmp->data.r << " " <<
//                               (unsigned int)tmp->data.g << " " <<
//                               (unsigned int)tmp->data.b << " " <<
//                               tmp->_num << endl;
//                        tmp = tmp->next;
                        _has_flag = true;
                        return;
                }
                tmp = tmp->next;
        }
        if (!_has_flag){
                _p = new(user_head);
                _p->data.r = _r;
                _p->data.g = _g;
                _p->data.b = _b;
                _p->_num = 1;
                _p->next = *_head;
                (*_head) = _p;
        }
}

void sortcolor(float a,float b,float c,int num,sort_color **sort_head){
        sort_color *tmp_head = *sort_head;
        sort_color *pre_node = tmp_head ;
        sort_color * add = new(sort_color);

        add->data.r = a;
        add->data.g = b;
        add->data.b = c;
        add->color_num = num;

//        sort_color * tt = *sort_head;
//        while (tt != NULL){
//            out << tt->color_num << " ";
//            tt = tt->next;
//        }
//        out << endl;

        if(*sort_head == NULL){
            //out << "head:" << num << endl;
                (*sort_head) = add;
                (*sort_head)->next = NULL;
                return;
        }

        while(tmp_head != NULL){
                if(num > tmp_head->color_num){
                        if(tmp_head == *sort_head){
                            //out << "头节点" << num << endl;
                                add->next = *sort_head;
                                (*sort_head) = add;
                        }else{
                                add->next = pre_node->next;
                                pre_node->next = add;
                        }
                        return;
                }else{
                    pre_node = tmp_head;
                    tmp_head = tmp_head->next;
                }
        }
        //out << "最后插入" << num << endl;
        add->next = NULL;
        pre_node->next = add;
}

            /*******************************
            *       改进版k-means处理函数      *
             *******************************/

////////////////////////////////////////// kmeans ////////////////////////////////////////////


double kmeans_3( InputArray _data, int K,
                   InputOutputArray _bestLabels,
                   TermCriteria criteria, int attempts,
                   int flags, OutputArray _centers ,ofstream &out)
{
    //ofstream out("C:\\Users\\9i\\Desktop\\test_result\\color.txt");
    const int SPP_TRIALS = 3;
    Mat data = _data.getMat();
    int N = data.rows > 1 ? data.rows : data.cols;
    int dims = (data.rows > 1 ? data.cols : 1)*data.channels();
    //sdnxq out << "dims:" << dims << endl;
    int type = data.depth();
    //sdnxq out << "type:" << type << endl;
    attempts = std::max(attempts, 1);
    CV_Assert( data.dims <= 2 && type == CV_32F && K > 0 );

    _bestLabels.create(N, 1, CV_32S, -1, true);

    Mat _labels, best_labels = _bestLabels.getMat();
    if( flags & CV_KMEANS_USE_INITIAL_LABELS )
    {
        CV_Assert( (best_labels.cols == 1 || best_labels.rows == 1) &&
                  best_labels.cols*best_labels.rows == N &&
                  best_labels.type() == CV_32S &&
                  best_labels.isContinuous());
        best_labels.copyTo(_labels);
    }
    else
    {
        if( !((best_labels.cols == 1 || best_labels.rows == 1) &&
             best_labels.cols*best_labels.rows == N &&
            best_labels.type() == CV_32S &&
            best_labels.isContinuous()))
            best_labels.create(N, 1, CV_32S);
        _labels.create(best_labels.size(), best_labels.type());
    }
    int* labels = _labels.ptr<int>();

    Mat centers(K, dims, type), old_centers(K, dims, type);
    vector<int> counters(K);
    vector<Vec2f> _box(dims);
    Vec2f* box = &_box[0];

    double best_compactness = DBL_MAX, compactness = 0;
    RNG& rng = theRNG();
    int a, iter, i, j, k;

    if( criteria.type & TermCriteria::EPS )
        criteria.epsilon = std::max(criteria.epsilon, 0.);
    else
        criteria.epsilon = FLT_EPSILON;
    criteria.epsilon *= criteria.epsilon;

    if( criteria.type & TermCriteria::COUNT )
        criteria.maxCount = std::min(std::max(criteria.maxCount, 2), 100);
    else
        criteria.maxCount = 100;

    if( K == 1 )
    {
        attempts = 1;
        criteria.maxCount = 2;
    }

    const float* sample = data.ptr<float>(0);
    for( j = 0; j < dims; j++ ){
        //sdnxq
        box[j] = Vec2f(sample[j], sample[j]);
        //out << "box:" << box[j][0] << " " << box[j][1] <<endl;
    }

    for( i = 1; i < N; i++ )
    {
        sample = data.ptr<float>(i);
        for( j = 0; j < dims; j++ )
        {
            float v = sample[j];
            //sdnxq
//            out << "v:" << v << endl;
//            out << "pre_box:" << box[j][0] << " " << box[j][1] <<endl;
            box[j][0] = std::min(box[j][0], v);
            box[j][1] = std::max(box[j][1], v);
            //sdnxq
//            out << "box:" << box[j][0] << " " << box[j][1] <<endl;
        }
    }

    for( a = 0; a < attempts; a++ )
    {

        int t =0;double shift = 0;double shift1 = 0;
        double max_center_shift = DBL_MAX;
        double max_center_shift1 = 0;
        int maxCount1 = 0;
        int use_count = 0 , s_count = 0;
        for( iter = 0; iter < criteria.maxCount && max_center_shift > criteria.epsilon; iter++ )
        {
            //sdnxq
            //t++;
            //out << "criteria.epsilon:" << criteria.epsilon << endl;
            shift = max_center_shift;
            shift1 = criteria.epsilon;
            swap(centers, old_centers);
            use_count = iter;
            s_count = criteria.maxCount;

            if( iter == 0 && (a > 0 || !(flags & KMEANS_USE_INITIAL_LABELS)) )
            {
                if( flags & KMEANS_PP_CENTERS )
                    generateCentersPP(data, centers, K, rng, SPP_TRIALS);
                else
                {
                    //sdnxq out << "random center" << endl;
                    //算法中用的随机中心点
                    for( k = 0; k < K; k++ ){
                        generateRandomCenter(_box, centers.ptr<float>(k), rng);
//                        out << "box_end_v :"
//                            << _box[0][0] << " " << _box[0][1] << endl
//                            << _box[1][0] << " " << _box[1][1] << endl
//                            << _box[2][0] << " " << _box[2][1] << endl;

                    }
                }
            }
            else
            {
                if( iter == 0 && a == 0 && (flags & KMEANS_USE_INITIAL_LABELS) )
                {
                    for( i = 0; i < N; i++ )
                        CV_Assert( (unsigned)labels[i] < (unsigned)K );
                }

                // compute centers
                centers = Scalar(0);//初始化centers为r、g、b全为0
                for( k = 0; k < K; k++ )
                    counters[k] = 0;

                for( i = 0; i < N; i++ )
                {
                    sample = data.ptr<float>(i);
                    k = labels[i];//初始labels在下边计算的
                    //sdnxq out << "labels:" << k << endl;
                    float* center = centers.ptr<float>(k);
                    for( j = 0; j <= dims - 4; j += 4 )//没有走进来
                    {
                        float t0 = center[j] + sample[j];
                        float t1 = center[j+1] + sample[j+1];

                        center[j] = t0;
                        center[j+1] = t1;

                        t0 = center[j+2] + sample[j+2];
                        t1 = center[j+3] + sample[j+3];

                        center[j+2] = t0;
                        center[j+3] = t1;
                    }
                    for( ; j < dims; j++ )
                        center[j] += sample[j];//求属于某个聚类中心的总和，下边取平均值作为新的聚类中心
                    counters[k]++;//累加属于某个聚类中心点的个数
                }

                if( iter > 0 )
                    max_center_shift = 0;

                //用求平均值的方法得到聚类中心，如果类中的元素个数为0，则重新随机聚类中心
                for( k = 0; k < K; k++ )
                {
                    float* center = centers.ptr<float>(k);
                    if( counters[k] != 0 )
                    {
                        float scale = 1.f/counters[k];
                        for( j = 0; j < dims; j++ )
                            center[j] *= scale;
                    }
                    else{
                        generateRandomCenter(_box, center, rng);
                        //sdnxq
                        //out << "center contain 0 elem" << endl;
                    }

                    if( iter > 0 )
                    {
                        double dist = 0;
                        const float* old_center = old_centers.ptr<float>(k);
                        for( j = 0; j < dims; j++ )
                        {
                            double t = center[j] - old_center[j];
                            dist += t*t;
                        }
                        //计算前后两次中心偏移的最大值，这个值会影到最终结果
                        max_center_shift = std::max(max_center_shift, dist);
                        //sdnxq
                        //out << "max_center_shift:" << max_center_shift << endl;
                        max_center_shift1 = max_center_shift;
                    }
                }
            }

            // assign labels,在这个地方那个用新的颜色相似度算法分类
            compactness = 0;
            for( i = 0; i < N; i++ )//遍历所有的点，与哪个中心点距离最小就归到哪个中心中去
            {
                sample = data.ptr<float>(i);
                int k_best = 0;
                double min_dist = DBL_MAX;

                for( k = 0; k < K; k++ )
                {
                    t ++;
                    const float* center = centers.ptr<float>(k);
                    double dist = distance(sample, center, dims);//用新的颜色相似度算法替换

                    if( min_dist > dist )
                    {
                        min_dist = dist;
                        k_best = k;
                    }
                }

                compactness += min_dist;
                labels[i] = k_best;
            }
            //sdnxq
            //out << compactness << endl;
            //out << "max_center_shift last:" << max_center_shift << endl;
            maxCount1 = iter;
        }
        //sndxq
        //out << "max_center_shift1 last:" << max_center_shift1 << endl;
        //out << "maxCount1:" << maxCount1 <<endl;
        //out << t << "  " <<shift << "biaozhun:" << shift1
            //<< "use_count:"<< use_count << "s_  count:" << s_count <<endl;

        if( compactness < best_compactness )
        {
            best_compactness = compactness;
            if( _centers.needed() )
                centers.copyTo(_centers);
            _labels.copyTo(best_labels);
        }
    }
    for(int i = 0; i < N;i++){
        //如果是在最后一次标签归类中，归类了一个点，那counter计数器不会加1，所以会有bug
        out << " " <<labels[i] << endl;
    }
        int count = 0;
        for( int k = 0; k < K; k++ )
        {
            //float* center = centers.ptr<float>(k);

            if( counters[k] == 0 )
            {
//                out << "kong dian index:"
//                    << k << " "
//                << centers.ptr<float>(k)[0]<<" "
//                << centers.ptr<float>(k)[1]<<" "
//                << centers.ptr<float>(k)[2]<<" "
//                <<endl;
                count ++;
            }
        }
        //out << "kong dian:" << count << endl;

    //out << "best_compactness:" << best_compactness << endl;
    return best_compactness;
}


CV_IMPL int
cvKMeans_3( const CvArr* _samples, int cluster_count, CvArr* _labels,
           CvTermCriteria termcrit, int attempts, CvRNG*,
           int flags, CvArr* _centers, double* _compactness ,ofstream &out)
{
    cv::Mat data = cv::cvarrToMat(_samples), labels = cv::cvarrToMat(_labels), centers;
    if( _centers )
    {
        centers = cv::cvarrToMat(_centers);
        centers = centers.reshape(1);
    }
    CV_Assert( labels.isContinuous() && labels.type() == CV_32S &&
        (labels.cols == 1 || labels.rows == 1) &&
        labels.cols + labels.rows - 1 == data.rows );

    double compactness = kmeans_3(data, cluster_count, labels, termcrit, attempts,
                                    flags, _centers ? cv::_OutputArray(centers) : cv::_OutputArray() ,out);
    if( _compactness )
        *_compactness = compactness;
    return 1;
}
/*******************************
*       改进版k-means处理函数      *
 ******************************/
double new_kmeans_3( InputArray _data, int K,
                   InputOutputArray _bestLabels,
                   TermCriteria criteria, int attempts,
                   int flags, OutputArray _centers ,ofstream &out,int *color_num,int *center_index)
{
    /***********************
    *       测试随机中心      *
     ***********************/
    //ofstream out("C:\\Users\\9i\\Desktop\\test_result\\color.txt");
    CV_Assert(  K < 300 );

    const int SPP_TRIALS = 3;
    Mat data = _data.getMat();
    int N = data.rows > 1 ? data.rows : data.cols;
    int dims = (data.rows > 1 ? data.cols : 1)*data.channels();
    //sdnxq out << "dims:" << dims << endl;
    int type = data.depth();
    //sdnxq out << "type:" << type << endl;
    attempts = std::max(attempts, 1);
    CV_Assert( data.dims <= 2 && type == CV_32F && K > 0 );

    _bestLabels.create(N, 1, CV_32S, -1, true);

    Mat _labels, best_labels = _bestLabels.getMat();
    if( flags & CV_KMEANS_USE_INITIAL_LABELS )
    {
        CV_Assert( (best_labels.cols == 1 || best_labels.rows == 1) &&
                  best_labels.cols*best_labels.rows == N &&
                  best_labels.type() == CV_32S &&
                  best_labels.isContinuous());
        best_labels.copyTo(_labels);
    }
    else
    {
        if( !((best_labels.cols == 1 || best_labels.rows == 1) &&
             best_labels.cols*best_labels.rows == N &&
            best_labels.type() == CV_32S &&
            best_labels.isContinuous()))
            best_labels.create(N, 1, CV_32S);
        _labels.create(best_labels.size(), best_labels.type());
    }
    int* labels = _labels.ptr<int>();

    Mat centers(K, dims, type), old_centers(K, dims, type);
    vector<int> counters(K);
    vector<Vec2f> _box(dims);
    Vec2f* box = &_box[0];

    double best_compactness = DBL_MAX, compactness = 0;
    RNG& rng = theRNG();
    int a, iter, i, j, k;

    if( criteria.type & TermCriteria::EPS )
        criteria.epsilon = std::max(criteria.epsilon, 0.);
    else
        criteria.epsilon = FLT_EPSILON;
    criteria.epsilon *= criteria.epsilon;

    if( criteria.type & TermCriteria::COUNT )
        criteria.maxCount = std::min(std::max(criteria.maxCount, 2), 100);
    else
        criteria.maxCount = 100;

    if( K == 1 )
    {
        attempts = 1;
        criteria.maxCount = 2;
    }

    const float* sample = data.ptr<float>(0);
    for( j = 0; j < dims; j++ ){
        //sdnxq
        box[j] = Vec2f(sample[j], sample[j]);
        //out << "box:" << box[j][0] << " " << box[j][1] <<endl;
    }

    for( i = 1; i < N; i++ )
    {
        sample = data.ptr<float>(i);
        for( j = 0; j < dims; j++ )
        {
            float v = sample[j];
            //sdnxq
//            out << "v:" << v << endl;
//            out << "pre_box:" << box[j][0] << " " << box[j][1] <<endl;
            //计算颜色的取值区间，颜色随机用
            box[j][0] = std::min(box[j][0], v);
            box[j][1] = std::max(box[j][1], v);
            //sdnxq
//            out << "box:" << box[j][0] << " " << box[j][1] <<endl;
        }
    }
    srand((unsigned)time( 0 ));
    /**************************************
    *       新版add,新版最多有50个聚类中心      *
     **************************************/
    //用来存放已计算过的点之间的距离
    float color_data[N][N];
    for(int set_i = 0; set_i < N;set_i++){
        for(int set_j = 0; set_j < N;set_j++){
            color_data[set_i][set_j] = -1;
        }
    }

//    //中心在原数据中的位置
//    int old_center_index[K];
//    for(int i = 0;i < K;i++){
//        center_index[i] = -1;
//    }
//    for(int i = 0;i < K;i++){
//        old_center_index[i] = -1;
//    }
//    //某个点是否已成为中心
//    bool whe_center[N];
//    for(int i = 0;i < N;i++){
//        whe_center[i] =false;
//        labels[i] = -1;
//    }
//    //标记属于某个聚类中心都有哪些点
//    int center_contain[50][N];
//    for(int i =0;i < 50;i++){
//        for(int j =0; j< N;j++){
//            center_contain[i][j] = -1;
//            //out << random(300) << endl;
//        }
//    }
//    float center_dist[50];
//    for(int i = 0;i < 50;i ++){
//        center_dist[i] = 0;
//    }
    /*********************************************
    * center_index存放中心在原数据中的索引           *
    * whe_center标识该点是否已在原数据中存在          *
    * labels[i]标识每个点属于哪个中心                *
    * centers.ptr<float>(k)[j],k中心颜色数据       *
    * center_dist[k]某个聚类中心的颜色总距离         *
    * counters[k]为第k个聚类中点的个数               *
     ********************************************/
    /*****************
    *  计算程序运行时间  *
     ****************/
               clock_t start,finish;
               double totaltime;
               start=clock();

    for( a = 0; a < attempts; a++ )
    {
        /**************************************
        *       除了颜色距离保留，其余重新赋值       *
         **************************************/
        centers = Scalar(0);//初始化centers为r、g、b全为0
        old_centers = Scalar(0);
        //中心在原数据中的位置
        int old_center_index[K];
        for(int i = 0;i < K;i++){
            center_index[i] = -1;
        }
        for(int i = 0;i < K;i++){
            old_center_index[i] = -1;
        }
        //某个点是否已成为中心
        bool whe_center[N];
        for(int i = 0;i < N;i++){
            whe_center[i] =false;
            labels[i] = -1;
        }
        //标记属于某个聚类中心都有哪些点
        int center_contain[50][N];
        for(int i =0;i < 50;i++){
            for(int j =0; j< N;j++){
                center_contain[i][j] = -1;
                //out << random(300) << endl;
            }
        }
        float center_dist[50];
        for(int i = 0;i < 50;i ++){
            center_dist[i] = 0;
        }
        int t =0;//double shift = 0;//double shift1 = 0;
        double max_center_shift = DBL_MAX;

        //int use_count = 0 , s_count = 0;
        for( iter = 0; iter < criteria.maxCount && max_center_shift > criteria.epsilon; iter++ )
        {
            //shift = max_center_shift;
            //将centers赋值给old_centers
                for(int swap_i = 0;swap_i < K;swap_i++){
                    old_center_index[swap_i] = center_index[swap_i];
                    for( j = 0; j < 3; j++ ){
                        old_centers.ptr<float>(swap_i)[j] = centers.ptr<float>(swap_i)[j];
                    }
                }
            //use_count = iter;
            //s_count = criteria.maxCount;
            //out << "ci_shu:" << iter << endl;

            if( iter == 0 && (a > 0 || !(flags & KMEANS_USE_INITIAL_LABELS)) )
            {
                if( flags & KMEANS_PP_CENTERS )
                    generateCentersPP(data, centers, K, rng, SPP_TRIALS);
                else
                {
                    //sdnxq out << "random center" << endl;
                    //算法中用的随机中心点
                    for( k = 0; k < K; k++ ){
                        int tmp_center = rand()%N;//random(N);
                        //out << "get_center: " << tmp_center << " all_point_num: " << N << endl;
                        while(whe_center[tmp_center]/*&&color_num[tmp_center]*/){
                            tmp_center = rand()%N;//random(N);
                        }
                        //labels[tmp_center] = -1;
                        whe_center[tmp_center] = true;
                        center_index[k] = tmp_center;
                        sample = data.ptr<float>(tmp_center);
                        for( j = 0; j < 3; j++ ){
                            centers.ptr<float>(k)[j] = sample[j];
                        }
//                        for(int i =0;i < 3;i++){
//                            out << "center-----:"
//                                <<centers.ptr<float>(i)[0]
//                                <<centers.ptr<float>(i)[1]
//                                << endl;

//                        }
                        //out << endl;
                        //out << "index:" << center_index[k] <<endl;
                    }
                }
            }
            else
            {
                if( iter == 0 && a == 0 && (flags & KMEANS_USE_INITIAL_LABELS) )
                {
                    for( i = 0; i < N; i++ )
                        CV_Assert( (unsigned)labels[i] < (unsigned)K );
                }
                // compute centers
                //centers = Scalar(0);//初始化centers为r、g、b全为0
//                for( k = 0; k < K; k++ )
//                    counters[k] = 0;
//                for( i = 0; i < N; i++ )
//                {
//                    //sample = data.ptr<float>(i);
//                    k = labels[i];//初始labels在下边计算的
//                    if(!whe_center[i]){//因为聚类中心的此值为-1，只有非中心参与计算
//                        //out << k << endl;
//                        center_contain[k][counters[k]] = i;
//                        counters[k]++;//累加属于某个聚类中心点的个数
//                        //out << "add" << k << endl;
//                    }
//                }

//                //debug
//                for(int i_debug = 0;i_debug < K;i_debug++){
//                    out <<"center_cotain:"<< i_debug << " " <<counters[i_debug] << endl;
//                }

//                for(int i =0;i < 3;i++){
//                    out << "center-----:"
//                        <<centers.ptr<float>(0)[0]
//                        <<centers.ptr<float>(0)[1]
//                        << endl;
//                }
                //打印每次计算详细数据
//                int sum_center = 0;
//                for(k = 0;k < K;k++){
//                    sum_center = 0;
//                    out << "befor:";
//                        for(int j = 0; j < counters[k];j++){
//                            sample = data.ptr<float>(center_contain[k][j]);
//                            const float* center = centers.ptr<float>(labels[center_contain[k][j]]);
//                            sum_center += new_distance(sample, center, dims);
//                            out << labels[center_contain[k][j]]
//                                << ":" << sample[0]
//                                << ":" << sample[1]
//                                << ":" << sample[2]
//                                << "@" << center[0]
//                                << ":" << center[1]
//                                << ":" << center[2]
//                                << "@" <<new_distance(sample, center, dims)
//                                << " ";
//                        }
//                    out << endl
//                        << "before get center:"
//                        << k << ":num " << counters[k]
//                        << " " << sum_center << endl;
//                }
                //out << "0-point:" << counters[0] << endl;
                if( iter > 0 )
                    max_center_shift = 0;

                //将旧的聚类中心保存下来，因为下边会改聚类中心
                //得到聚类中心，如果类中的元素个数为0，则重新随机聚类中心
                compactness = 0;
                for( k = 0; k < K; k++ )
                {
                    //out << "in_get_center:" << k << endl;
                    if( counters[k] != 0 )//如果有点，则center_dist肯定不可能为0
                    {
                        //out << k << "point_num:" << counters[k]<<endl;
                        double dist;
                        for(int i = 0;i < counters[k];i ++){
                            //out << "index:" << i << endl;
                            dist = 0;
                            //const float* sample1 = data.ptr<float>(center_contain[k][i]);
                            float* sample1;
                            float* sample2;
                            sample1 = data.ptr<float>(center_contain[k][i]);//外层点
                            for(int j = 0;j < counters[k];j ++){
                                sample2 = data.ptr<float>(center_contain[k][j]);//内层点
                                double tmp_dist = 0;
                                if(color_data[center_contain[k][i]][center_contain[k][j]] > 0){
                                    dist +=
                                    color_data[center_contain[k][i]][center_contain[k][j]]*
                                    color_num[center_contain[k][j]];
                                }
                                else{
                                    tmp_dist = new_distance(sample1, sample2, dims);
                                    color_data[center_contain[k][i]][center_contain[k][j]]= tmp_dist;
                                    color_data[center_contain[k][j]][center_contain[k][i]]= tmp_dist;
                                    dist += tmp_dist*color_num[center_contain[k][j]];
                                    t++;
                                }
                            }

                            //加上与原来中心点的距离
                            sample2 = old_centers.ptr<float>(k);
                            double tmp_dist = 0;
                            if(color_data[center_contain[k][i]][old_center_index[k]] > 0){
                                dist +=
                                color_data[center_contain[k][i]][old_center_index[k]]*
                                        color_num[old_center_index[k]];
                            }
                            else{
                                tmp_dist =  new_distance(sample1, sample2, dims);
                                color_data[center_contain[k][i]][old_center_index[k]]= tmp_dist;
                                color_data[old_center_index[k]][center_contain[k][i]]= tmp_dist;
                                dist += tmp_dist*
                                        color_num[old_center_index[k]];
                            }
                            //dist += new_distance(sample1, sample2, dims)*color_num[old_center_index[k]];
                            /*********************************************
                            * center_index存放中心在原数据中的索引           *
                            * whe_center标识该点是否已在原数据中存在          *
                            * labels[i]标识每个点属于哪个中心                *
                            * centers.ptr<float>(k)[j],k中心颜色数据       *
                            * center_dist[k]某个聚类中心的颜色总距离         *
                            * counters[k]为第k个聚类中点的个数               *
                             ********************************************/
                            //out << "distance:" << dist << endl;
                            //表明第i个点为颜色距离最小点，i为类中序，非全局序
                            if(dist < center_dist[k]){
                                //中心的labels标为-1
                                labels[center_contain[k][i]] = -1;
                                labels[center_index[k]] = k;

                                center_dist[k] = dist;
                                //把原先标记聚类中心的标识，置：否
                                whe_center[center_index[k]] =false;
                                //重置第k个中心的全局序
                                center_index[k] = center_contain[k][i];
                                //把原先标记是否是聚类中心的标识，置：是
                                //out << "new center index:" << center_contain[k][i] << endl;
                                whe_center[center_contain[k][i]] =true;
                                //重置某个聚类中心的颜色数据，center_contain[k][i]为k类中，第i个点的全局序
                                sample = data.ptr<float>(center_contain[k][i]);
                                for(int t = 0; t < 3; t++ ){
                                    centers.ptr<float>(k)[t] = sample[t];
                                }
                            }
                        }
                        compactness += center_dist[k];
                    }
                    else{
                        /*********************************************
                        * center_index存放中心在原数据中的索引           *
                        * whe_center标识该点是否已在原数据中存在          *
                        * labels[i]标识每个点属于哪个中心,中心这---->
                        * 个值没有意义，中心通过center_index取值          *
                        * centers.ptr<float>(k)[j],k中心颜色数据       *
                        * center_dist[k]某个聚类中心的颜色总距离         *
                        * counters[k]为第k个聚类中点的个数               *
                        *  center_contain某个center包含的点             *
                         ********************************************/
                        //out << k << " no point" << endl;
                        //这地方要保证随机到的中心点不是原来的点也不是已有的中心点
                        //随机了中心之后，要把这个点的距离减去
                        int tmp_center = rand()%N;//random(N);
                        while(whe_center[tmp_center]/*&&color_num[tmp_center]*/){
                            tmp_center = rand()%N;//random(N);
                        }
                        if(labels[tmp_center] < k){
                            //out << "will minus:" << k << "from distance" << endl;

                            //这地方中心应该用新中心
                            double tmp_dist;
                            if(color_data[tmp_center][center_index[labels[tmp_center]]] > 0){
                                compactness -=
                                color_data[tmp_center][center_index[labels[tmp_center]]]*
                                        color_num[tmp_center];
                            }
                            else{
                                tmp_dist = new_distance(data.ptr<float>(tmp_center),
                                                        data.ptr<float>(center_index[labels[tmp_center]]),
                                                        dims);
                                color_data[tmp_center][center_index[labels[tmp_center]]] = tmp_dist;
                                color_data[center_index[labels[tmp_center]]][tmp_center] = tmp_dist;
                                compactness -= tmp_dist*color_num[tmp_center];
                            }

//                            compactness -= new_distance(data.ptr<float>(tmp_center),
//                                                        data.ptr<float>(center_index[labels[tmp_center]]),
//                                                        dims)*color_num[center_index[tmp_center]];
                        }
                        //重置label
                        labels[tmp_center] = -1;
                        labels[center_index[k]] = k;

                        whe_center[tmp_center] = true;
                        whe_center[center_index[k]] = false;
                        center_index[k] = tmp_center;
                        //counters[k] = 0;//不用重置，因为下边初始化了

                        sample = data.ptr<float>(tmp_center);
                        for( j = 0; j < 3; j++ ){
                            centers.ptr<float>(k)[j] = sample[j];
                        }
                        //out << new_center << endl;
                    }

                    //debug
//                    out << k <<" get_center_contains:" ;
//                    for(int debug_i = 0;debug_i < counters[k];debug_i++){
//                        out  << center_contain[k][debug_i] << " ";
//                    }
                    out << endl;

                    if( iter > 0 )
                    {
                        double dist = 0;
                        const float* old_center = old_centers.ptr<float>(k);
                        const float* center = centers.ptr<float>(k);
                        for( j = 0; j < dims; j++ )
                        {
                            double t = center[j] - old_center[j];
                            dist += t*t;
                        }
                        //计算前后两次中心偏移的最大值，这个值会影到最终结果，如果小于给定值则停止
                        max_center_shift = std::max(max_center_shift, dist);
                    }
                    out << "max_dist: " << max_center_shift << endl;
                }
//打印每次计算详细数据
//                for(k = 0;k < K;k++){
//                        out << "after:";
//                        sum_center = 0;
//                        for(int j = 0; j < counters[k];j++){
//                            sample = data.ptr<float>(center_contain[k][j]);
//                            const float* center = centers.ptr<float>(labels[center_contain[k][j]]);
//                            sum_center += new_distance(sample, center, dims);
//                            out << labels[center_contain[k][j]]
//                                << ":" << sample[0]
//                                << ":" << sample[1]
//                                << ":" << sample[2]
//                                << "@" << center[0]
//                                << ":" << center[1]
//                                << ":" << center[2]
//                                << "@" <<new_distance(sample, center, dims)
//                                << " ";
//                        }
//                    out << endl <<"after get center:" << k << ":num " << counters[k] << " " << sum_center << endl;
//                }
//                out << "center sum:" << compactness << " center: "
//                    << center_index[0] << " "
//                    << center_index[1] << " "
//                    << center_index[2] << " "
//                    <<endl;
            }

            // 根据中心，重新聚类其余点
            compactness = 0;
            for(int t_label = 0;t_label < K;t_label++)
            {
                center_dist[t_label] = 0;
                counters[t_label] = 0;
            }


            out << "                 " << iter << endl;
            out << "get_center :";
            double sum = 0;
            for(int i = 0;i < N;i++){
                if(!whe_center[i]&&iter > 0){
                sample = data.ptr<float>(i);
                const float* center = centers.ptr<float>(labels[i]);
//                out << i << ":"
//                    << new_distance(sample, center, dims)
//                    << ",";
                //out << " index: " << center_index[labels[i]] << " " ;
                double tmp_dist;
                if(color_data[i][center_index[labels[i]]] > 0){
                    sum += color_data[i][center_index[labels[i]]]*
                            color_num[i];//用新的颜色相似度算法替换
                }
                else{
                    tmp_dist = new_distance(sample, center, dims);
                    color_data[i][center_index[labels[i]]] = tmp_dist;
                    color_data[center_index[labels[i]]][i] = tmp_dist;
                    sum += tmp_dist*color_num[i];
                }
                //sum += new_distance(sample, center, dims)*color_num[i];
                }
            }
            out << sum << endl;

            out << "label      :";
            for( i = 0; i < N; i++ )//遍历所有的点，与哪个中心点距离最小就归到哪个中心中去
            {
                /* center_dist[k]某个聚类中心的颜色总距离         *
                * counters[k]为第k个聚类中点的个数*/
                sample = data.ptr<float>(i);
                int k_best = -1;
                double min_dist = DBL_MAX;
                bool flag = false;
                if(!whe_center[i]){//表明i这个点没有成为center点
                    for( k = 0; k < K; k++ )
                    {
                                const float* center = centers.ptr<float>(k);
//                                out << "---------"
//                                    << center[0] << " "
//                                    << center[1] << " "
//                                    << center[2] << " "
//                                    << endl;
                                t++;
                                double dist;
                                if(color_data[i][center_index[k]] > 0){
                                    dist = color_data[i][center_index[k]]*
                                            color_num[i];//用新的颜色相似度算法替换
                                }
                                else{
                                    dist = new_distance(sample, center, dims);
                                    color_data[i][center_index[k]] = dist;
                                    color_data[center_index[k]][i] = dist;
                                    dist *= color_num[i];
                                }
                                //double dist = new_distance(sample, center, dims)*color_num[i];//用新的颜色相似度算法替换
                                if( min_dist > dist )
                                {
                                    min_dist = dist;
                                    k_best = k;
                                    flag = true;
                                }
                    }
                }
                else{
                    labels[i] = -1;
                    //out << "cccccccc" << i << endl;
                }
                //点聚到哪个类中，就把距离加到哪个聚类中心的距离中。
                if(flag){
                    if(!whe_center[i]){
                    //out << "to center:" << k_best << endl;
                    center_dist[k_best] += min_dist;
                    center_contain[k_best][counters[k_best]++] = i;
                    compactness += min_dist;
                    labels[i] = k_best;
                    //out << i << ":" << min_dist << ",";
                    }
                }
            }
            //out << endl ;
            out << compactness << endl;
//            for(int k = 0;k < K;k++){
//                //debug
//                out << k <<":label_contains:" ;
//                for(int debug_i = 0;debug_i < counters[k];debug_i++){
//                    out << center_contain[k][debug_i] << " ";
//                }
//                out << endl;
//            }
            //out << "label sum:" << compactness << " time: " << iter << endl;

//            for(int i = 0;i < K;i++){
//                out << k << " num:" <<counters[i] << endl;
//            }
        }
        //out << "t is:" << t << endl;
        if( compactness < best_compactness )
        {
            best_compactness = compactness;
            if( _centers.needed() )
                centers.copyTo(_centers);
            _labels.copyTo(best_labels);
        }
out << endl;
    }
    out << "end--------:" << best_compactness << endl;

    int count = 0;
    for( int k = 0; k < K; k++ )
    {
        //float* center = centers.ptr<float>(k);
        if( counters[k] == 0 )
        {
            count ++;
            //out << "kong dian index:" << k << endl;
        }
        out << k << " color num: " << counters[k] << endl;
    }
    finish=clock();
    totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
    out << "\n此程序的运行时间为" << totaltime << " 秒！" << endl;
    out << "kong dian:" << count << endl;
    out << "best_compactness:" << best_compactness << endl;
    return best_compactness;
}

static void new_generateRandomCenter(const vector<Vec2f>& box, float* center, RNG& rng,ofstream &out)
{
    //ofstream out("C:\\Users\\9i\\Desktop\\test_result\\color.txt");
    //ofstream out(_out);
    //out << random(300) << endl;
    size_t j, dims = box.size();
    float margin = 1.f/dims;
    for( j = 0; j < dims; j++ ){
        center[j] = ((float)rng*(1.f+margin*2.f)-margin)*(box[j][1] - box[j][0]) + box[j][0];
        //out << center[j] << "   ";
    }
    //out << endl;
}
CV_IMPL int
new_cvKMeans_3( const CvArr* _samples, int cluster_count, CvArr* _labels,
           CvTermCriteria termcrit, int attempts, CvRNG*,
           int flags, CvArr* _centers, double* _compactness ,ofstream &out,int *color_num,int *center_or_label)
{
    cv::Mat data = cv::cvarrToMat(_samples), labels = cv::cvarrToMat(_labels), centers;
    if( _centers )
    {
        centers = cv::cvarrToMat(_centers);
        centers = centers.reshape(1);
    }
    CV_Assert( labels.isContinuous() && labels.type() == CV_32S &&
        (labels.cols == 1 || labels.rows == 1) &&
        labels.cols + labels.rows - 1 == data.rows );

    double compactness = new_kmeans_3(data, cluster_count, labels, termcrit, attempts,
                                    flags, _centers ? cv::_OutputArray(centers) : cv::_OutputArray() ,
                                    out,color_num,center_or_label);
    if( _compactness )
        *_compactness = compactness;
    return 1;
}

static inline float new_distance(const float* a, const float* b, int n)
{
    CIEDE2000::LAB lab1, lab2;
    lab1.l = a[0];lab1.a = a[1];lab1.b = a[2];
    lab2.l = b[0];lab2.a = b[1];lab2.b = b[2];
    return CIEDE2000::CIEDE2000(lab1, lab2);
}
