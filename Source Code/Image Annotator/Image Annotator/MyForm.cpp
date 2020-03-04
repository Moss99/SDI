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
std::vector<int> rectangles;

void MyForm::shapePoint1() {
	timer1->Enabled = true;
	shapeStartPos = PointToClient(System::Windows::Forms::Cursor::Position);
	shapeStartPos = centerPointer(shapeStartPos, true);
}

void MyForm::shapePoint2() {
	timer1->Enabled = false;
	Point shapeEndPos = PointToClient(System::Windows::Forms::Cursor::Position);
	shapeEndPos = centerPointer(shapeEndPos, false);
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
		shapeEndPos = centerPointer(shapeEndPos, false);
		Drawing::Size CurRecSize = Drawing::Size(shapeEndPos);
		currentRectangle = Drawing::Rectangle(shapeStartPos, CurRecSize);
		g->FillRectangle(tYBrush, currentRectangle);
		g->DrawRectangle(Pens::Yellow, currentRectangle);
	}
}

Point MyForm::centerPointer(Point pos, bool isStart) {
	Point picBoxLoc;
	picBoxLoc = pictureBox1->Location;
	if (isStart) {
		pos.X -= picBoxLoc.X;
		pos.Y -= picBoxLoc.Y;
	}
	else {
		pos.X -= picBoxLoc.X + shapeStartPos.X;
		pos.Y -= picBoxLoc.Y + shapeStartPos.Y;
	}
	return pos;
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


