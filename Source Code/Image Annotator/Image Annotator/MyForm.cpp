#include "MyForm.h"
#include "Shape.h"
#include <iostream>
#include <vector>
#include <initializer_list>
#include <iostream>

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
//std::vector<Drawing::Rectangle> rectangles;
auto rectangles = gcnew List<System::Drawing::Rectangle>();



void MyForm::shapePoint1() {
	timer1->Enabled = true;
	shapeStartPos = PointToClient(System::Windows::Forms::Cursor::Position);
	picBoxLoc = pictureBox1->Location;
	shapeStartPos.X = shapeStartPos.X - picBoxLoc.X;
	shapeStartPos.Y = shapeStartPos.Y - picBoxLoc.Y;;
}

void MyForm::shapePoint2() {
	timer1->Enabled = false;
}

void MyForm::paintShapes(PaintEventArgs^ e) {
	Graphics^ g = e->Graphics;

	Color transYellow = Color::FromArgb(100, Color::Yellow);
	SolidBrush^ tYBrush = gcnew SolidBrush(transYellow);
	/*
	for (size_t i = 0; i < rectangles.size(); ++i) {
		g->FillRectangle(tYBrush, rectangles[i]);
		g->DrawRectangle(Pens::Yellow, rectangles[i]);
	}*/

	if (Control::MouseButtons == System::Windows::Forms::MouseButtons::Left) {
		Point shapeEndPos = PointToClient(System::Windows::Forms::Cursor::Position);
		shapeEndPos.X = shapeEndPos.X - picBoxLoc.X;
		shapeEndPos.Y = shapeEndPos.Y - picBoxLoc.Y;
		Drawing::Rectangle currentRectangle = Drawing::Rectangle(shapeStartPos.X, shapeStartPos.Y, shapeEndPos.X - shapeStartPos.X, shapeEndPos.Y - shapeStartPos.Y);
		g->FillRectangle(tYBrush, currentRectangle);
		g->DrawRectangle(Pens::Yellow, currentRectangle);
		//rectangles.push_back(currentRectangle);
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
	System::String^ filePathS = openFileDialog1->SelectedPath;
	textBox1->Text = filePathS;
	std::vector <std::string> fileNames = imageFolder.loadImages(msclr::interop::marshal_as<std::string>(filePathS));
	for (int i = 0; i < fileNames.size(); i++) {
		listBox2->Items->Add(gcnew String(fileNames[i].c_str()));
	}
}
