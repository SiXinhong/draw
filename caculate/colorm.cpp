#include "colorm.h"
#include<QFile>

colorM::colorM()
{
}

void colorM::saveColorInfo(spotColorAll tempAll/*里边放name*/, int len,QColor*tempColor){
        ofstream outfile;
        outfile.open("colorTable/color.txt", ios::out);

        if(!outfile) //检查文件是否正常打开
        {
            cout<<"can't open"<<endl;
            return;
        }
        else
        {
            for(int i=1;i<len+1;i++){
                outfile <<tempAll.colorName[i].toStdString()<<" "<<tempColor[30+i].red()
                       <<" "<<tempColor[30+i].blue()<<" "<<tempColor[30+i].green()<<"\n"<<flush;
            }
            outfile.close();
        }
}
void colorM::getColorInfo(int&tempNum,QColor*tempColor,spotColorAll&tempColorAll){
    //std::ifstream  fin("C:\\Users\\9i\\Desktop\\split1.txt", std::ios::in);
    std::ifstream  fin("colorTable/color.txt", std::ios::in);
    char  line[1024]={0};
    string  name = "";
    string  R = "";
    string  G = "";
    string  B = "";

    int lineNum=0;
    //QTextCodec *code=QTextCodec::codecForName("gb18030");
    while(fin.getline(line, sizeof(line)))
    {
         lineNum++;
         std::stringstream  word(line);
         word >> name;
         word>>R;
         word>>G;
         word>>B;
         tempColor[30+lineNum].setRgb(atoi(R.c_str()),atoi(G.c_str()),atoi(B.c_str()));
         tempColorAll.colorName[lineNum]=QString::fromLocal8Bit(name.c_str());
         //qDebug()<<QString::fromLocal8Bit(name.c_str());
         //tempName=QString::fromStdString(name);
     }
    fin.close();
    tempNum=lineNum;
    //qDebug()<<lineNum;
}
