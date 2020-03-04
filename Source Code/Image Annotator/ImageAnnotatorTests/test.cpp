#include "pch.h"

TEST(ImageFolderTest, LoadFile) { //First test
    imageFolder folder;
    std::string filePath = "C:\\Users\\Sam\\Desktop\\SDI Repo\\SDI\\Source Code\\images";
    std::vector<std::string> testFileNames; 
    testFileNames.push_back("forest.jpg");
    testFileNames.push_back("trees.jpg"); 
    testFileNames.push_back("wp4676578.png");
    std::vector<std::string> actualFileNames = folder.loadImages(filePath);

    for (size_t i = 0; i < actualFileNames.size(); i++) {
        actualFileNames[i].resize(actualFileNames[i].size() - 1);
    }

  EXPECT_EQ(testFileNames, actualFileNames);
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(TestCaseName, Test) { //test template
    
}