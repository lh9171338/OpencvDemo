//-----------------------------------������˵����----------------------------------------------  
//      ��������:������OpenCV���Ž̳�֮ʮһ����̬ѧͼ������һ���������븯ʴ  �� ��������Դ��   
//      ��������IDE�汾��Visual Studio 2010  
//      <span style="white-space:pre">  </span>��������OpenCV�汾��    2.4.8  
//      2014��4��25�� Create by ǳī  
//----------------------------------------------------------------------------------------------  
  
//-----------------------------------��ͷ�ļ��������֡�---------------------------------------  
//      ����������������������ͷ�ļ�  
//----------------------------------------------------------------------------------------------   
#include <iostream>
#include <opencv2/opencv.hpp>  

  
//-----------------------------------�������ռ��������֡�--------------------------------------  
//      ����������������ʹ�õ������ռ�  
//-----------------------------------------------------------------------------------------------   
using namespace std;  
using namespace cv;  
  
  
//-----------------------------------��ȫ�ֱ����������֡�--------------------------------------  
//      ������ȫ�ֱ�������  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage, g_dstImage;//ԭʼͼ��Ч��ͼ  
int g_nElementShape = MORPH_RECT;//Ԫ�ؽṹ����״  
  
//�������յ�TrackBarλ�ò���  
int g_nMaxIterationNum = 10;  
int g_nOpenCloseNum = 0;  
int g_nErodeDilateNum = 0;  
int g_nTopBlackHatNum = 0;  
  
  
  
//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------  
//      ������ȫ�ֺ�������  
//-----------------------------------------------------------------------------------------------  
static void on_OpenClose(int, void*);//�ص�����  
static void on_ErodeDilate(int, void*);//�ص�����  
static void on_TopBlackHat(int, void*);//�ص�����  
static void ShowHelpText();//����������ʾ  
  
  
//-----------------------------------��main( )������--------------------------------------------  
//      ����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ  
//-----------------------------------------------------------------------------------------------  
int main( )  
{  
    //�ı�console������ɫ  
    system("color 2F");    
  
    ShowHelpText();  
  
    //����ԭͼ  
    g_srcImage = imread("pic.jpg");		//����Ŀ¼����Ҫ��һ����Ϊpic1.jpg���ز�ͼ  
    if( !g_srcImage.data ) { printf("��ȡsrcImage���� \n"); return false; }  
  
    //��ʾԭʼͼ  
    namedWindow("��ԭʼͼ��");  
    imshow("��ԭʼͼ��", g_srcImage);  
  
    //������������  
    namedWindow("��������/�����㡿",1);  
    namedWindow("����ʴ/���͡�",1);  
    namedWindow("����ñ/��ñ��",1);  
  
    //������ֵ  
    g_nOpenCloseNum=9;  
    g_nErodeDilateNum=9;  
    g_nTopBlackHatNum=2;  
  
    //�ֱ�Ϊ�������ڴ���������  
    createTrackbar("����ֵ", "��������/�����㡿",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);  
    createTrackbar("����ֵ", "����ʴ/���͡�",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);  
    createTrackbar("����ֵ", "����ñ/��ñ��",&g_nTopBlackHatNum,g_nMaxIterationNum*2+1,on_TopBlackHat);  
  
    //��ѯ��ȡ������Ϣ  
    while(1)  
    {  
        int c;  
  
        //ִ�лص�����  
        on_OpenClose(g_nOpenCloseNum, 0);  
        on_ErodeDilate(g_nErodeDilateNum, 0);  
        on_TopBlackHat(g_nTopBlackHatNum,0);  
  
        //��ȡ����  
        c = waitKey(0);  
  
        //���¼��̰���Q����ESC�������˳�  
        if( (char)c == 'q'||(char)c == 27 )  
            break;  
        //���¼��̰���1��ʹ����Բ(Elliptic)�ṹԪ�ؽṹԪ��MORPH_ELLIPSE  
        if( (char)c == 49 )//���̰���1��ASII��Ϊ49  
            g_nElementShape = MORPH_ELLIPSE;  
        //���¼��̰���2��ʹ�þ���(Rectangle)�ṹԪ��MORPH_RECT  
        else if( (char)c == 50 )//���̰���2��ASII��Ϊ50  
            g_nElementShape = MORPH_RECT;  
        //���¼��̰���3��ʹ��ʮ����(Cross-shaped)�ṹԪ��MORPH_CROSS  
        else if( (char)c == 51 )//���̰���3��ASII��Ϊ51  
            g_nElementShape = MORPH_CROSS;  
        //���¼��̰���space���ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��  
        else if( (char)c == ' ' )  
            g_nElementShape = (g_nElementShape + 1) % 3;  
    }  
  
    return 0;  
}  
  
  
//-----------------------------------��on_OpenClose( )������----------------------------------  
//      ��������������/�����㡿���ڵĻص�����  
//-----------------------------------------------------------------------------------------------  
static void on_OpenClose(int, void*)  
{  
    //ƫ�����Ķ���  
    int offset = g_nOpenCloseNum - g_nMaxIterationNum;//ƫ����  
    int Absolute_offset = offset > 0 ? offset : -offset;//ƫ��������ֵ  
    //�Զ����  
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );  
    //���в���  
    if( offset < 0 )  
        morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
    else  
        morphologyEx(g_srcImage, g_dstImage, MORPH_CLOSE, element);
    //��ʾͼ��  
    imshow("��������/�����㡿",g_dstImage);  
}  
  
  
//-----------------------------------��on_ErodeDilate( )������----------------------------------  
//      ����������ʴ/���͡����ڵĻص�����  
//-----------------------------------------------------------------------------------------------  
static void on_ErodeDilate(int, void*)  
{  
    //ƫ�����Ķ���  
    int offset = g_nErodeDilateNum - g_nMaxIterationNum;    //ƫ����  
    int Absolute_offset = offset > 0 ? offset : -offset;//ƫ��������ֵ  
    //�Զ����  
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );  
    //���в���  
    if( offset < 0 )  
        erode(g_srcImage, g_dstImage, element);  
    else  
        dilate(g_srcImage, g_dstImage, element);  
    //��ʾͼ��  
    imshow("����ʴ/���͡�",g_dstImage);  
}  
  
  
//-----------------------------------��on_TopBlackHat( )������--------------------------------  
//      ����������ñ����/��ñ���㡿���ڵĻص�����  
//----------------------------------------------------------------------------------------------  
static void on_TopBlackHat(int, void*)  
{  
    //ƫ�����Ķ���  
    int offset = g_nTopBlackHatNum - g_nMaxIterationNum;//ƫ����  
    int Absolute_offset = offset > 0 ? offset : -offset;//ƫ��������ֵ  
    //�Զ����  
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1, Absolute_offset*2+1), Point(Absolute_offset, Absolute_offset) );  
    //���в���  
    if( offset < 0 )  
        morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT , element);  
    else  
        morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);  
    //��ʾͼ��  
    imshow("����ñ/��ñ��",g_dstImage);  
}  
  
//-----------------------------------��ShowHelpText( )������----------------------------------  
//      ���������һЩ������Ϣ  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
//���һЩ������Ϣ  
    printf("\n\n\n\t������������۲�ͼ��Ч��~\n\n");  
    printf( "\n\n\t��������˵��: \n\n"  
        "\t\t���̰�����ESC�����ߡ�Q��- �˳�����\n"  
        "\t\t���̰�����1��- ʹ����Բ(Elliptic)�ṹԪ��\n"  
        "\t\t���̰�����2��- ʹ�þ���(Rectangle )�ṹԪ��\n"  
        "\t\t���̰�����3��- ʹ��ʮ����(Cross-shaped)�ṹԪ��\n"  
        "\t\t���̰������ո�SPACE��- �ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��\n"
        );  
}  