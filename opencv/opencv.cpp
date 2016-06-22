//g++ -I/usr/local -L/usr/local -lopencv_core -lopencv_imgcodecs -lopencv_imgproc *.cpp -o opencv.linux
#include <cstdio>

#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {

  std::string srcImagePath("../EmacsIcon400x400.png");
  std::string dstImagePath("../EmacsIcon400x400.dst.png");
  
  cv::Mat srcImage, dstImage;
  std::string srcTitle("Src Pic");
  std::string dstTitle("Dst Pic");

  if(2 != argc) {    
    srcImage = cv::imread(srcImagePath, 1);
  } else {
    srcImage = cv::imread(argv[1], 1);
  }
  
  cv::cvtColor(srcImage, dstImage, cv::COLOR_BGR2GRAY);
  
  if(!srcImage.data || !dstImage.data) {    
    std::cerr << "Image data error" << std::endl;
    std::cout << argv[0] << std::endl;
    return EXIT_FAILURE;
  }

   
  cv::namedWindow(srcTitle.c_str(), cv::WINDOW_AUTOSIZE);
  cv::imshow(srcTitle, srcImage);

  cv::imwrite(dstImagePath.c_str(), dstImage);
  cv::namedWindow(dstTitle.c_str(), cv::WINDOW_AUTOSIZE);
  cv::imshow(dstTitle, dstImage);
  
  cv::waitKey(0);
  
  return EXIT_SUCCESS;
}
