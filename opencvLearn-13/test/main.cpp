//-----------------------------------【程序说明】----------------------------------------------  
//      程序名称:：《 【OpenCV入门教程之十三】OpenCV图像金字塔：高斯金字塔、拉普拉斯金字塔与图片尺寸缩放》 博文配套源码   
//      开发所用IDE版本：Visual Studio 2010  
//              开发所用OpenCV版本：   2.4.9  
//      2014年5月18日 Create by 浅墨  
//----------------------------------------------------------------------------------------------  
  
//-----------------------------------【头文件包含部分】---------------------------------------  
//      描述：包含程序所依赖的头文件  
//----------------------------------------------------------------------------------------------   
#include <iostream>
#include <opencv2/opencv.hpp>  

  
//-----------------------------------【宏定义部分】--------------------------------------------  
//  描述：定义一些辅助宏  
//------------------------------------------------------------------------------------------------  
#define WINDOW_NAME "【程序窗口】"        //为窗口标题定义的宏  
  
  
//-----------------------------------【命名空间声明部分】--------------------------------------  
//      描述：包含程序所使用的命名空间  
//-----------------------------------------------------------------------------------------------   
using namespace std;  
using namespace cv;  
  
  
//-----------------------------------【全局变量声明部分】--------------------------------------  
//      描述：全局变量声明  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage, g_dstImage, g_tmpImage;  
  
  
//-----------------------------------【全局函数声明部分】--------------------------------------  
//      描述：全局函数声明  
//-----------------------------------------------------------------------------------------------  
static void ShowHelpText();  
  
  
//-----------------------------------【ShowHelpText( )函数】----------------------------------  
//      描述：输出一些帮助信息  
//----------------------------------------------------------------------------------------------  
static void ShowHelpText()  
{  
    //输出一些帮助信息  
    printf("\n\n\n\t欢迎来到OpenCV图像金字塔和resize示例程序~\n\n");  
    printf( "\n\n\t按键操作说明: \n\n"  
        "\t\t键盘按键【ESC】或者【Q】- 退出程序\n"  
        "\t\t键盘按键【1】或者【W】- 进行基于【resize】函数的图片放大\n"  
        "\t\t键盘按键【2】或者【S】- 进行基于【resize】函数的图片缩小\n"  
        "\t\t键盘按键【3】或者【A】- 进行基于【pyrUp】函数的图片放大\n"  
        "\t\t键盘按键【4】或者【D】- 进行基于【pyrDown】函数的图片缩小\n" 
        );  
}  
  
//-----------------------------------【main( )函数】--------------------------------------------  
//      描述：控制台应用程序的入口函数，我们的程序从这里开始  
//-----------------------------------------------------------------------------------------------  
int main( )  
{  
    //改变console字体颜色  
    system("color 2F");    
  
    //显示帮助文字  
    ShowHelpText();  
  
    //载入原图  
    g_srcImage = imread("pic.jpg");//工程目录下需要有一张名为1.jpg的测试图像，且其尺寸需被2的N次方整除，N为可以缩放的次数  
    if( !g_srcImage.data ) { printf("读取srcImage错误！ \n"); return false; }  
  
    // 创建显示窗口  
    namedWindow( WINDOW_NAME, 0 );  
    imshow(WINDOW_NAME, g_srcImage);  
  
    //参数赋值  
    g_tmpImage = g_srcImage;  
    g_dstImage = g_tmpImage;  
  
     int key =0;  
  
    //轮询获取按键信息  
    while(1)  
    {  
        key=waitKey(9) ;//读取键值到key变量中  
  
        //根据key变量的值，进行不同的操作  
        switch(key)  
        {  
         //======================【程序退出相关键值处理】=======================    
        case 27://按键ESC  
            return 0;  
            break;   
  
        case 'q'://按键Q  
            return 0;  
            break;   
  
         //======================【图片放大相关键值处理】=======================    
        case 'a'://按键A按下，调用pyrUp函数  
            pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ) );  
            printf( ">检测到按键【A】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸×2 \n" );       
            break;   
  
        case 'w'://按键W按下，调用resize函数  
            resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));  
            printf( ">检测到按键【W】被按下，开始进行基于【resize】函数的图片放大：图片尺寸×2 \n" );          
            break;   
  
        case '1'://按键1按下，调用resize函数  
            resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));  
            printf( ">检测到按键【1】被按下，开始进行基于【resize】函数的图片放大：图片尺寸×2 \n" );  
            break;   
  
        case '3': //按键3按下，调用pyrUp函数  
            pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));  
            printf( ">检测到按键【3】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸×2 \n" );  
            break;   
        //======================【图片缩小相关键值处理】=======================    
        case 'd': //按键D按下，调用pyrDown函数  
            pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));  
            printf( ">检测到按键【D】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2\n" );  
            break;   
  
        case  's' : //按键S按下，调用resize函数  
            resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));  
            printf( ">检测到按键【S】被按下，开始进行基于【resize】函数的图片缩小：图片尺寸/2\n" );  
            break;   
  
        case '2'://按键2按下，调用resize函数  
            resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ),0,0,2);  
            printf( ">检测到按键【2】被按下，开始进行基于【resize】函数的图片缩小：图片尺寸/2\n" );  
            break;   
  
        case '4': //按键4按下，调用pyrDown函数  
            pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ) );  
            printf( ">检测到按键【4】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2\n" );  
            break;   
        }  
          
        //经过操作后，显示变化后的图  
        imshow( WINDOW_NAME, g_dstImage );  
  
        //将g_dstImage赋给g_tmpImage，方便下一次循环  
        g_tmpImage = g_dstImage;  
    }  
  
    return 0;  
}  