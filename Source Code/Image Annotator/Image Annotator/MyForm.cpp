#include "MyForm.h"
#include "Shape.h"
#include <iostream>
#include <vector>
#include <initializer_list>
#include <iostream>
#include <exception>

using namespace System;
using namespace System::Windows::Forms;
using namespace Image_Annotator;
using namespace System::Collections::Generic;

[STAThread]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Image_Annotator::MyForm form;
	Application::Run(% form);
}

Point shapeStartPos;
Point picBoxLoc;
std::vector<int> rectangles;
std::vector <std::string> imageFileNames;
std::string folderFilePath;

void MyForm::shapePoint1() {
	timer1->Enabled = true;
	shapeStartPos = PointToClient(System::Windows::Forms::Cursor::Position);
	picBoxLoc = pictureBox1->Location;
	shapeStartPos.X -= picBoxLoc.X;
	shapeStartPos.Y -= picBoxLoc.Y;;
}

void MyForm::shapePoint2() {
	timer1->Enabled = false;
	Point shapeEndPos = PointToClient(System::Windows::Forms::Cursor::Position);
	shapeEndPos.X -= picBoxLoc.X + shapeStartPos.X;
	shapeEndPos.Y -= picBoxLoc.Y + shapeStartPos.Y;
	rectangles.push_back(shapeStartPos.X);
	rectangles.push_back(shapeStartPos.Y);
	rectangles.push_back(shapeEndPos.X);
	rectangles.push_back(shapeEndPos.Y);
	pictureBox1->Invalidate();
}

void MyForm::paintShapes(PaintEventArgs^ e) {
	Graphics^ g = e->Graphics;
	
	Color transYellow = Color::FromArgb(100, Color::Yellow);
	SolidBrush^ tYBrush = gcnew SolidBrush(transYellow);
	Drawing::Rectangle currentRectangle;

	for (int i = 0; i < (static_cast<int>(rectangles.size()) - 3); i += 4) {
		currentRectangle = Drawing::Rectangle(rectangles[i], rectangles[i+1], rectangles[i+2], rectangles[i+3]);
		g->FillRectangle(tYBrush, currentRectangle);
		g->DrawRectangle(Pens::Yellow, currentRectangle);
	}

	if (Control::MouseButtons == System::Windows::Forms::MouseButtons::Left) {
		Point shapeEndPos = PointToClient(System::Windows::Forms::Cursor::Position);
		shapeEndPos.X -= picBoxLoc.X + shapeStartPos.X;
		shapeEndPos.Y -= picBoxLoc.Y + shapeStartPos.Y;
		Drawing::Size CurRecSize = Drawing::Size(shapeEndPos);
		currentRectangle = Drawing::Rectangle(shapeStartPos, CurRecSize);
		g->FillRectangle(tYBrush, currentRectangle);
		g->DrawRectangle(Pens::Yellow, currentRectangle);
	}
}

void Image_Annotator::MyForm::savePic() {
	saveFileDialog1->Filter = "JPeg Image|*.jpg|Bitmap Image|*.bmp";
	saveFileDialog1->Title = "Save Image File";
	saveFileDialog1->ShowDialog();

	if (saveFileDialog1->FileName != "") {
		Bitmap^ bmp = gcnew Bitmap(pictureBox1->ClientSize.Width, pictureBox1->ClientSize.Height - 1);
		pictureBox1->DrawToBitmap(bmp, pictureBox1->ClientRectangle);

		System::IO::FileStream^ fs = (System::IO::FileStream^)saveFileDialog1->OpenFile();
		bmp->Save(fs, Drawing::Imaging::ImageFormat::Bmp);
		fs->Close();
	}
}

void MyForm::loadImages() {
	listBox2->Items->Clear();
	imageFolder imageFolder;
	openFileDialog1->ShowDialog();
	try {
		System::String^ filePathS = openFileDialog1->SelectedPath;
		folderFilePath = msclr::interop::marshal_as<std::string>(filePathS);
		textBox1->Text = filePathS;
		imageFileNames = imageFolder.loadImages(folderFilePath);
		for (int i = 0; i < imageFileNames.size(); i++) {
			listBox2->Items->Add(gcnew String(imageFileNames[i].c_str()));
		}
	}
	catch (const std::exception & exp) {
		//catch no folder selected
	}
}

void MyForm::setImage() {
	imageFolder image;
	int selectedImage = listBox2->SelectedIndex;
	std::string fullPath = image.fullPath(folderFilePath, imageFileNames[selectedImage]);
	System::String^ fullPathS = gcnew String(fullPath.c_str());
	pictureBox1->Image = pictureBox1->Image->FromFile(fullPathS);
}