#include "savespot.h"



//模板函数：将string类型变量转换为常用的数值类型
template <class Type>
Type stringToNum(const string& str)
{
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}


saveSpot::saveSpot()
{
    digitalFlag = 0;
    count=0;
    //get=rand()%482+1;
    get=rand()%25+1;


    string temp[31]={"255,255,255","72,77,64","76,81,69","77,88,69","83,91,74","80,95,61","99,106,74","96,99,76","109,111,64","87,81,74","98,81,65",
                     "105,93,71","105,94,72","110,94,87","139,110,86","129,115,94","117,84,63","134,92,75","123,111,78","162,125,95",
                     "170,136,99","184,146,99","202,150,96","146,123,87","146,127,104","136,134,127","158,137,108","166,155,138",
                     "182,166,141","69,68,68","236,235,233"};
    for(int i=0;i<31;i++){
        iconColor[i]=temp[i];
    }
}
void saveSpot::readBigSpotPoint(int *num, float readP[300][2],int mark){
    if(mark==0)
        srand(time(0));
    //********get=get%25+1;
    get=get%189+1;
    //qDebug("ran:%d",ran);
    //readNum=25;
    //float tempGet;
    ifstream fin;
    //*******string head("dataBig/");
    string head("dataBig/");
    string mid;
    string tail(".txt");
    string all;
    string numS;
    char tempMid[10];
    //char tempSI[30];

    sprintf(tempMid,"%d",get);
    mid.assign(tempMid);
    all=head+mid+tail;
    fin.open(all.c_str());

    //sprintf(tempSI,"%d",num);
    //numS.assign(tempSI);

    //按行读文件
    getline(fin,numS);
    *num=stringToNum<int>(numS);
    //qDebug("~~~~~~~~~~~%d",*num);

    for(int i=1;i<*num+1;i++){
        float tempSX;
        float tempSY;
        string s[2];

        //tempSave=saveP[i][0];
        getline(fin,s[0]);
        tempSX=stringToNum<float>(s[0]);

        //tempSave=saveP[i][1];
        getline(fin,s[1]);
        tempSY=stringToNum<float>(s[1]);

        readP[i][0]=tempSX;
        readP[i][1]=tempSY;
        //qDebug("@@@@@%f   %f",tempSX,tempSY);
    }
    fin.close();
    //qDebug("xian zai shi:%d",get);
    //qDebug("@@@@%d",i);
    get++;
}

void saveSpot::saveCanvas(spot *tempSave,QString fileName){
    //从程序序列化到文件
    int drawOk;
    float drawX;
    float drawY;
    float drawZ;
    float width;
    float height;
    float midWidth;
    float midHeight;
    float preMidWidth;
    float preMidHeight;
    float windowScale;
    int backGroundColorIndex;
    float spotOriginX[maxSize];
    float spotOriginY[maxSize];
    float spotOriginOX[maxSize];
    float spotOriginOY[maxSize];
    float spotOriginPOX[maxSize];
    float spotOriginPOY[maxSize];
    int spotNum[maxSize];
    float stretch[maxSize];
    float rotation[maxSize];
    spotColorAll allColor;
    list<QPointF*>oPointAll;//用户画的原点
    list<QPointF*>handlePointAll;





    drawOk=tempSave->getDrawOk();
    tempSave->getWidHei(width,height);
    tempSave->getSpotNum(spotNum);
    tempSave->getSpotOrigin(spotOriginX,spotOriginY,spotOriginOX,spotOriginOY,spotOriginPOX,spotOriginPOY);
    tempSave->getCenter(midWidth,midHeight,preMidWidth,preMidHeight);
    tempSave->getStretch(stretch);
    tempSave->getRotation(rotation);
    tempSave->getOpointAll(oPointAll);
    tempSave->getHandlePointAll(handlePointAll);
    tempSave->getAllColorIndex(allColor.index,backGroundColorIndex);
    //tempSave->getAllPath(allPath);
    //tempSave->getAllColor(allColor);
    tempSave->getCanvas(drawX,drawY,drawZ);
    tempSave->getWindowScale(windowScale);

    list<float> v;
    v.push_back(drawOk);
    v.push_back(drawX);
    v.push_back(drawY);
    v.push_back(drawZ);
    v.push_back(width);
    v.push_back(height);
    v.push_back(midWidth);
    v.push_back(midHeight);
    v.push_back(preMidWidth);
    v.push_back(preMidHeight);
    v.push_back(windowScale);
    v.push_back(backGroundColorIndex);
    //////////////////////////////////////////
    for(int i=1;i<drawOk+1;i++){
        v.push_back(spotOriginX[i]);
    }
    for(int i=1;i<drawOk+1;i++){
        v.push_back(spotOriginY[i]);
    }
    //////////////////////////////////////////
    for(int i=1;i<drawOk+1;i++){
        v.push_back(spotOriginOX[i]);
    }
    for(int i=1;i<drawOk+1;i++){
        v.push_back(spotOriginOY[i]);
    }
    //////////////////////////////////////////
    for(int i=1;i<drawOk+1;i++){
        v.push_back(spotOriginPOX[i]);
    }
    for(int i=1;i<drawOk+1;i++){
        v.push_back(spotOriginPOY[i]);
    }
    //////////////////////////////////////////
    for(int i=1;i<drawOk+1;i++){
        v.push_back(spotNum[i]);
    }
    //////////////////////////////////////////
    for(int i=1;i<drawOk+1;i++){
        v.push_back(stretch[i]);
    }
    //////////////////////////////////////////
    for(int i=1;i<drawOk+1;i++){
        v.push_back(rotation[i]);
    }
    //////////////////////////////////////////
    for(int i=1;i<drawOk+1;i++){
        v.push_back(allColor.index[i]);
    }
    //////////////////////////////////////////
    list<QPointF*>::iterator oP = oPointAll.begin();
    for(;oP!=oPointAll.end();oP++){
        v.push_back((**oP).x());
        v.push_back((**oP).y());
    }

    list<QPointF*>::iterator oPH = handlePointAll.begin();
    for(;oPH!=handlePointAll.end();oPH++){
        v.push_back((**oPH).x());
        v.push_back((**oPH).y());
    }

    string tempS=fileName.toStdString();
    ofstream out(tempS.c_str());//生成文件输出流
    copy(v.begin(),v.end(),ostream_iterator<float>(out," "));
}
void saveSpot::readCanvas(spot *temp,QString fileName){
    list<float> v;
    string tempS=fileName.toStdString();
    ifstream in(tempS.c_str());//建立输入流
    copy(istream_iterator<float>(in),istream_iterator<float>(),back_inserter(v));
    list<float>::iterator op=v.begin();

    int drawOk;
    float drawX;
    float drawY;
    float drawZ;
    float width;
    float height;
    float midWidth;
    float midHeight;
    float preMidWidth;
    float preMidHeight;
    float windowScale;
    int backGroundColorIndex;
    float spotOriginX[maxSize];
    float spotOriginY[maxSize];
    float spotOriginOX[maxSize];
    float spotOriginOY[maxSize];
    float spotOriginPOX[maxSize];
    float spotOriginPOY[maxSize];
    int spotNum[maxSize];
    float stretch[maxSize];
    float rotation[maxSize];
    spotColorAll allColor;
    list<QPointF*>oPointAll;//用户画的原点
    list<QPointF*>handlePointAll;

    /////////////////////////////

    ////////////////////////////
    drawOk=*op;op++;
    drawX=*op;op++;
    drawY=*op;op++;
    drawZ=*op;op++;
    width=*op;op++;
    height=*op;op++;
    midWidth=*op;op++;
    midHeight=*op;op++;
    preMidWidth=*op;op++;
    preMidHeight=*op;op++;
    windowScale=*op;op++;
    backGroundColorIndex=*op;op++;
    for(int i=1;i<drawOk+1;i++){
        spotOriginX[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        spotOriginY[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        spotOriginOX[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        spotOriginOY[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        spotOriginPOX[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        spotOriginPOY[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        spotNum[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        stretch[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        rotation[i]=*op;
        op++;
    }
    for(int i=1;i<drawOk+1;i++){
        allColor.index[i]=*op;
        //qDebug("........:%f",*op);
        op++;
    }
    //list<QPointF*>oPointAll;//用户画的原点
    for(int i=1;i<drawOk+1;i++){
        for(int j=1;j<spotNum[i]+1;j++){
            QPointF *tempPoint=new QPointF;
            tempPoint->setX(*op);
            op++;
            tempPoint->setY(*op);
            op++;
            oPointAll.push_back(tempPoint);
        }
    }
    //list<QPointF*>handlePointAll;
    for(int i=1;i<drawOk+1;i++){
        for(int j=1;j<2*spotNum[i]+1;j++){
            QPointF *tempPoint=new QPointF;
            tempPoint->setX(*op);
            op++;
            tempPoint->setY(*op);
            op++;
            handlePointAll.push_back(tempPoint);
        }
    }


    temp->setDrawOk(drawOk);
    temp->setSpotOrigin(spotOriginX,spotOriginY,spotOriginOX,spotOriginOY,spotOriginPOX,spotOriginPOY);
    temp->setCenter(midWidth,midHeight,preMidWidth,preMidHeight);
    temp->setWidHei(width,height);
    temp->setSpotNum(spotNum);
    temp->setStretch(stretch);
    temp->setRotation(rotation);
    temp->setOpointAll(oPointAll);
    temp->setHandlePointAll(handlePointAll);
    temp->setAllColorIndex(allColor.index,backGroundColorIndex);
    //tempSave->setAllPath(allPath);
    //tempSave->setAllColor(allColor);
    temp->setCanvas(drawX,drawY,drawZ);
    temp->setWindowScale(windowScale);

}

void saveSpot::saveSpotPoint(int num,float saveP[300][2]){
    count++;
    float tempSave;
    ofstream fout;
    string head("data/");
    string mid;
    string tail(".txt");
    string all;
    string numS;
    char tempMid[10];
    char tempSI[30];

    sprintf(tempMid,"%d",count);
    mid.assign(tempMid);
    all=head+mid+tail;
    fout.open(all.c_str());

    sprintf(tempSI,"%d",num);
    numS.assign(tempSI);

    fout<<numS<<endl;
    for(int i=1;i<num+1;i++){
        char tempSX[30];
        char tempSY[30];
        string s[2];

        tempSave=saveP[i][0];
        sprintf(tempSX,"%.5f",tempSave);
        s[0].assign(tempSX);

        tempSave=saveP[i][1];
        sprintf(tempSY,"%.5f",tempSave);
        s[1].assign(tempSY);

        fout<<s[0]<<endl<<s[1]<<endl;
    }
    fout.close();
}

void saveSpot::strToIntArray(QString str, int temp[10][10], int t){
    QStringList list = str.split(",");
    for(int i=0;i<list.length();i++){
        temp[t][i] = list.at(i).toInt(0,10);
    }
}

//-------xiaotian    测试读取数码迷彩单个斑点
string saveSpot::readDigitalSpotPoint(int edge[10][10],int &readNum,int mark){
    if(mark==0) srand(time(0));
    //对5进行取余  --------xiaotian
    get=rand()%5+1;
    readNum=get;
    //-----------------xiaotian  修改了路径，原值为data,改为digitaldata
    string head("digitaljzdata/");
    string mid="";
    string tail(".txt");
    string all;
    char tempMid[10];
    //char tempSI[30];
    sprintf(tempMid,"%d",get);
    mid.assign(tempMid);
    //添加的测试代码 --------------------------xiaotian
    //mid = "2";
    all=head+mid+tail;

    //初始化
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            edge[i][j] = 0;
        }
    }
//    int rowNum = 0;
//    int colNum = 0;

//    QFile f1(all.c_str());
//    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        qDebug("open fail  xiaotian");
//        //return -1;
//    }else{
//        QTextStream txtInput(&f1);
//        QString lineStr;
//        while(!txtInput.atEnd())
//        {
//            lineStr = txtInput.readLine();
//            rowNum++;
//        }

//        QStringList list = lineStr.split(",");
//        colNum = list.size();
//    }
//    f1.close();

    QFile f(all.c_str());
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("open fail");
    }
    QTextStream txtInput(&f);
    QString lineStr;

    int i = 0;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        strToIntArray(lineStr,edge,i);
        i++;
    }
    cout<<"=================================================="<<endl;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            cout<<edge[i][j]<<',';
        }
        cout<<endl;
    }
    f.close();
    return mid;
}


//计算当前准备插入的斑点的宽度和高度
list<QString> saveSpot::readOrig(float *width,float *height,string mid){
//    ifstream fin;
    list<QString> stringlists;
    //-----------------xiaotian  修改了路径，原值为data,改为digitaldata
    string head("digitaljzdata/");
    //string mid;
    string tail(".txt");
    string all;
    char tempMid[10];
    //char tempSI[30];

    sprintf(tempMid,"%d",get);
    // mid.assign(tempMid);
    //添加的测试代码 --------------------------xiaotian
    //mid = "4";
    all=head+mid+tail;
    int rowNum = 0;
    int colNum = 0;
    /*
    fin.open(all.c_str());
    string line;

    while(getline(fin,line)){
        colNum++;
    }

    QString lineStr = QString::fromStdString(line);
    QStringList list = lineStr.split(",");
    rowNum = list.size();

    *width = colNum * 10;
    *height = rowNum * 10;
    fin.close();
*/


    QFile f(all.c_str());
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("open fail  xiaotian");
        //return -1;
    }else{
        QTextStream txtInput(&f);
        QString lineStr;
        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            stringlists.push_back(lineStr);
            //rowNum
            rowNum++;
        }

        QStringList list = lineStr.split(",");
        colNum = list.size();

        *width = colNum * 10;
        *height = rowNum * 10;

        f.close();
    }


    return stringlists;


}

string saveSpot::readSpotPoint(int &readNum,int *num,float readP[300][2],int mark){
    if(mark==0)
        srand(time(0));
    //对5进行取余  --------xiaotian
    if(digitalFlag == 1){
        get=rand()%5+1;
    }else{
        get=rand()%482+1;
    }

    //qDebug("CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC%d",get);
    readNum=get;
    //qDebug("ran:%d",readNum);
    //readNum=25;
    //float tempGet;
    ifstream fin;

    //-----------------xiaotian  修改了路径，原值为data,改为digitaldata

    //string head("digitaldata/");
    string head("data/");
    if(digitalFlag == 1){
        head = "digitaldata/";
    }
    string mid;
    string tail(".txt");
    string all;
    string numS;
    char tempMid[10];
    //char tempSI[30];

    sprintf(tempMid,"%d",get);
    mid.assign(tempMid);


    //添加的测试代码 --------------------------xiaotian
    //mid = "2";


    all=head+mid+tail;

    fin.open(all.c_str());

    //sprintf(tempSI,"%d",num);
    //numS.assign(tempSI);

    getline(fin,numS);
    *num=stringToNum<int>(numS);
    //qDebug("~~~~~~~~~~~%d",*num);

    for(int i=1;i<*num+1;i++){
        float tempSX;
        float tempSY;
        string s[2];

        //tempSave=saveP[i][0];
        getline(fin,s[0]);
        tempSX=stringToNum<float>(s[0]);




        //tempSave=saveP[i][1];
        getline(fin,s[1]);
        tempSY=stringToNum<float>(s[1]);

        //都乘以4  -------------------测试  xiaotian 画的时候压缩了4
        if(digitalFlag == 1){
            tempSX*=4;
            tempSY*=4;
        }
        readP[i][0]=tempSX;
        readP[i][1]=tempSY;
        //qDebug("@@@@@%f   %f",tempSX,tempSY);
    }
    fin.close();

    //qDebug("@@@@%d",i);
    get++;
    return mid;
}

//void saveSpot::getAutoCAD(int hasNum,int spotNum[maxSize],int colorIndex[maxSize],int (*num)[100],QPointF (*tempP)[100],int area,float width,float height){
void saveSpot::getAutoCAD(int hasNum,int spotNum[maxSize],int colorIndex[maxSize],int (*num)[1000],QPointF *tempP[5000][100],int area,float width,float height){




    ofstream fout;//定义文件对象
    //合成文件路径
    string head("AutoCAD/");//定义头
    string mid;//定义中间
    string tail(".txt");//定义尾
    string all;
    char tmp[20];//用来浮点数转字符串
    string sX,sY;
    char tempMid[10];




    sprintf(tempMid,"%d",area);
    mid.assign(tempMid);
    all=head+mid+tail;
    fout.open(all.c_str());

    fout<<"REC"<<endl;

    //    string rX,rY;
    //    sprintf(tempMid,"%d",80);
    //    rX.assign(tempMid);
    //    sprintf(tempMid,"%d",0);
    //    rY.assign(tempMid);
    fout<<"0,0"<<endl;
    //fout<<rX<<","<<rY<<endl;



    fout<<"D"<<endl;
    sprintf(tmp,"%.5f",width);
    sX.assign(tmp);
    sprintf(tmp,"%.5f",height);
    sY.assign(tmp);
    fout<<sX<<endl;
    fout<<sY<<endl;
    fout<<sX<<","<<sY<<endl;

    int index=0;
    for(int a=0;a<hasNum;a++){
        index=colorIndex[num[area][a]]+1;
        fout<<"-color"<<endl;
        fout<<"t"<<endl;
        fout<<iconColor[index]<<endl;


        fout<<"SPL"<<endl;

        //qDebug("    %d",index);
        for(int j=1;j<spotNum[num[area][a]]+1;j++){
            sprintf(tmp,"%.5f",tempP[a][j]->x());
            sX.assign(tmp);

            sprintf(tmp,"%.5f",tempP[a][j]->y());
            sY.assign(tmp);
            fout<<sX<<","<<sY<<endl;
        }
        fout<<"C"<<endl<<endl;
    }
}
void saveSpot::getAutoCADAll(int hasNum,int spotNum[maxSize],int colorIndex[maxSize],int (*num)[1000],QPointF *tempP[5000][100],int area,int x,int y,int z){




    ofstream fout;//定义文件对象
    //合成文件路径
    string head("AutoCAD/");//定义头
    string mid;//定义中间
    string tail(".txt");//定义尾
    string all;
    char tmp[20];//用来浮点数转字符串
    string sX,sY;
    char tempMid[10];




    sprintf(tempMid,"%d",area+6);
    mid.assign(tempMid);
    all=head+mid+tail;
    //qDebug("!!!!!!!!!!!!!!!!%d",area+6);
    fout.open(all.c_str());

    fout<<"REC"<<endl;

    string rX,rY;
    //    sprintf(tempMid,"%d",z);
    //    rX.assign(tempMid);
    //    sprintf(tempMid,"%d",y+z);
    //    rY.assign(tempMid);
    //    //fout<<"0,0"<<endl;
    //    fout<<rX<<","<<rY<<endl;



    //fout<<"D"<<endl;

    switch(area+6)
    {
    case 6:
        sprintf(tempMid,"%d",z);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",y+z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;

        sprintf(tempMid,"%d",z+x);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",y+2*z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;
        break;

    case 7:
        sprintf(tempMid,"%d",0);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;

        sprintf(tempMid,"%d",z);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",y+z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;
        break;

    case 8:
        sprintf(tempMid,"%d",z);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;

        sprintf(tempMid,"%d",z+x);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",y+z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;
        break;

    case 9:
        sprintf(tempMid,"%d",z+x);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;

        sprintf(tempMid,"%d",2*z+x);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",y+z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;
        break;

    case 10:
        sprintf(tempMid,"%d",z);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",0);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;

        sprintf(tempMid,"%d",z+x);
        rX.assign(tempMid);
        sprintf(tempMid,"%d",z);
        rY.assign(tempMid);
        fout<<rX<<","<<rY<<endl;
        break;
    }



    //    fout<<"D"<<endl;
    //    sprintf(tmp,"%.5f",width);
    //    sX.assign(tmp);
    //    sprintf(tmp,"%.5f",height);
    //    sY.assign(tmp);
    //    fout<<sX<<endl;
    //    fout<<sY<<endl;
    //    fout<<sX<<","<<sY<<endl;

    int index=0;
    for(int a=0;a<hasNum;a++){
        index=colorIndex[num[area][a]]+1;
        fout<<"-color"<<endl;
        fout<<"t"<<endl;
        fout<<iconColor[index]<<endl;


        fout<<"SPL"<<endl;

        //qDebug("    %d",index);
        for(int j=1;j<spotNum[num[area][a]]+1;j++){
            sprintf(tmp,"%.5f",tempP[a][j]->x());
            sX.assign(tmp);

            sprintf(tmp,"%.5f",tempP[a][j]->y());
            sY.assign(tmp);
            fout<<sX<<","<<sY<<endl;
        }
        fout<<"C"<<endl<<endl;
    }
}

void saveSpot::autoCADAll(){
    int i;
    char filename[100],line[1001];
    ifstream File[20];
    ofstream File2;
    File2.open("..\\draw\\AutoCAD\\5.txt",ios::out);
    for(i=6;i<11;i++)  {
        sprintf(filename,"..\\draw\\AutoCAD\\%d.txt",i);
        File[i].open(filename,ios::in);
        while(!File[i].eof())  {
            File[i].getline(line,1000);
            File2<<line;
            if(!File[i].eof())
                File2<<endl;
        }
        File[i].close();
    }
    File2.close();
}
