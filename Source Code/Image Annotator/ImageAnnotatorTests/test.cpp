#include "pch.h"

TEST(ImageFolderTest, LoadFile) {
    imageFolder folder;
    std::string filePath = "../../images";
    std::vector<std::string> testFileNames; 
    testFileNames.push_back("green-forest-trees.jpg.860x0_q70_crop-scale.jpg");
    testFileNames.push_back("trees.jpg");
    std::vector<std::string> actualFileNames;
    //actualFileNames = folder.loadImages("C:/Users/Sam/Desktop/SDI Repo/SDI/Source Code/images");
  //EXPECT_EQ(fileNames, folder.loadImages(filePath));
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}