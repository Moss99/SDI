#include "MyForm.h"
#include "Shape.h"
#include "imageFolder.h"
#include "Annotation.h"
#include "linkedList.h"
#include "searchSort.h";
#include <iostream>
#include <vector>
#include <initializer_list>
#include <exception>
#include <thread>
#include <chrono>
#include <fstream>

using namespace System;
using namespace System::Windows::Forms;
using namespace Image_Annotator;
using namespace System::Collections::Generic;

Point shapeStartPos = Point(0, 0);
std::vector<std::vector<int>> shapes;
linkedList<std::string> classTexts;
linkedList<Point> classPoints;
std::vector<int> polyDrawing;
Drawing::Rectangle polyStart;
std::vector <std::string> imageFileNames;
std::string folderFilePath = "";
std::string classPath;
std::string classSelected;
std::string shapeSelected;
int selectedImage;

void autosave() {
	Annotation annotation;
	while (true) {
		annotation.save(shapes);
		std::this_thread::sleep_for(std::chrono::seconds(60));
	}
}

void MyForm::shapePoint1() {

	// For custom polgon only
	if (timer1->Enabled == true && freeDraw) {
		Point lineEndPos = PointToClient(System::Windows::Forms::Cursor::Position);
		lineEndPos = centerPointer(lineEndPos, true);

		// Check for new polygon and set return location
		if (polyDrawing.size() == 0) {
			polyStart = Drawing::Rectangle(shapeStartPos.X-10, shapeStartPos.Y-10, 20, 20);
		}
		
		// check for polygon return to start
		if (polyStart.Contains(lineEndPos) && polyDrawing.size() >= (4*2)) {
			shapes.push_back(polyDrawing);
			polyDrawing.clear();
			polyStart = Drawing::Rectangle();

			classTexts.addBack(classSelected);
			classPoints.addBack(Point(lineEndPos.X, lineEndPos.Y - 20));

			timer1->Enabled = false;
		}
		else {
			polyDrawing.push_back(shapeStartPos.X);
			polyDrawing.push_back(shapeStartPos.Y);
			polyDrawing.push_back(lineEndPos.X);
			polyDrawing.push_back(lineEndPos.Y);
		}
		pictureBox1->Invalidate();
	}
	else {
		timer1->Enabled = true;
	}

	shapeStartPos = PointToClient(System::Windows::Forms::Cursor::Position);
	shapeStartPos = centerPointer(shapeStartPos, true);
	
}

void MyForm::shapePoint2() {
	if (!freeDraw) {
		timer1->Enabled = false;
		Point shapeEndPos = PointToClient(System::Windows::Forms::Cursor::Position);
		shapeEndPos = centerPointer(shapeEndPos, false);

		std::vector<int> currShape = { shapeStartPos.X, shapeStartPos.Y, shapeEndPos.X, shapeEndPos.Y };
		shapes.push_back(currShape);

		classTexts.addBack(classSelected);
		classPoints.addBack(Point(shapeStartPos.X, shapeStartPos.Y-20));

		pictureBox1->Invalidate();
	}
}

void MyForm::paintShapes(PaintEventArgs^ e) {
	Graphics^ g = e->Graphics;
	
	Color transYellow = Color::FromArgb(100, Color::Yellow);
	SolidBrush^ tYBrush = gcnew SolidBrush(transYellow);
	Pen^ yellowPen = gcnew Pen(Brushes::Yellow);
	yellowPen->Width = 3.0F;
	yellowPen->LineJoin = System::Drawing::Drawing2D::LineJoin::Bevel;

	Drawing::Rectangle currentRectangle;

	// Draw Shapes
	for (int i = 0; i < static_cast<int>(shapes.size()); i++) {
		std::vector<int> shape = shapes[i];

		// check for custom shape
		if (shape.size() > 4) {
			array<Point>^ polyPoints = gcnew array<Point>(shape.size()/2);
			int count = 0;
			for (int i = 0; i < (static_cast<int>(shape.size()) - 1); i += 2) {
				polyPoints[count] = Point(shape[i], shape[i+1]);
				count++;
			}
			Drawing::Drawing2D::GraphicsPath^ path = gcnew Drawing::Drawing2D::GraphicsPath();
			path->AddPolygon(polyPoints);
			Drawing::Region^ region = gcnew Drawing::Region(path);
			//g->FillRegion(tYBrush, region);
			g->DrawPath(yellowPen, path);
		}
		else {
			currentRectangle = Drawing::Rectangle(shape[0], shape[1], shape[2], shape[3]);
			//g->FillRectangle(tYBrush, currentRectangle);
			g->DrawRectangle(yellowPen, currentRectangle);
		}
	}


	// Draw Class Names
	for (int i = 0; i < static_cast<int>(classTexts.size()); i++) {
		FontFamily^ fontFamily = gcnew FontFamily("Arial");
		Drawing::Font^ font = gcnew Drawing::Font(fontFamily, 15, Drawing::FontStyle::Bold, Drawing::GraphicsUnit::Pixel);
		SolidBrush^ solidBrush = gcnew SolidBrush(Color::FromArgb(255, 255, 255, 0));

		g->DrawString(gcnew String(classTexts.get(i).c_str()), font, solidBrush, Drawing::Rectangle(classPoints.get(i), Drawing::Size(200, 20)));
	}

	// Rectangle Preview
	if (Control::MouseButtons == System::Windows::Forms::MouseButtons::Left && !freeDraw) {
		Point shapeEndPos = PointToClient(System::Windows::Forms::Cursor::Position);
		shapeEndPos = centerPointer(shapeEndPos, false);
		Drawing::Size CurRecSize = Drawing::Size(shapeEndPos);
		currentRectangle = Drawing::Rectangle(shapeStartPos, CurRecSize);
		g->FillRectangle(tYBrush, currentRectangle);
		g->DrawRectangle(yellowPen, currentRectangle);
	}

	// Custom Polygon Preview
	if (freeDraw && timer1->Enabled == true) {
		for (int i = 0; i < static_cast<int>(polyDrawing.size()-3); i += 4) {
			g->DrawLine(yellowPen, polyDrawing[i], polyDrawing[i+1], polyDrawing[i+2], polyDrawing[i+3]);
		}
		Point lineEndPos = PointToClient(System::Windows::Forms::Cursor::Position);
		lineEndPos = centerPointer(lineEndPos, true);
		g->DrawLine(yellowPen, shapeStartPos.X, shapeStartPos.Y, lineEndPos.X, lineEndPos.Y);
		g->DrawRectangle(Pens::Green, polyStart);

	}
}

Point MyForm::centerPointer(Point pos, bool isStart) {
	Point picBoxLoc;
	picBoxLoc = pictureBox1->Location;
	if (isStart) {
		pos.X -= picBoxLoc.X;
		pos.Y -= picBoxLoc.Y;
	}
	else { // gets size instead
		pos.X -= picBoxLoc.X + shapeStartPos.X;
		pos.Y -= picBoxLoc.Y + shapeStartPos.Y;
	}
	return pos;
}

void MyForm::saveAnnotations() {
	if (shapes.size() > 0) {
		Annotation annotation;
		annotation.save(shapes);
	}
}

void MyForm::loadImages() {
	imageFolder imageFolder;
	openFileDialog1->ShowDialog();
	try {
		System::String^ filePathS = openFileDialog1->SelectedPath;
		folderFilePath = msclr::interop::marshal_as<std::string>(filePathS);
		textBox1->Text = filePathS;
		imageFileNames = imageFolder.loadImages(folderFilePath);
		listBox2->Items->Clear();
		for (int i = 0; i < imageFileNames.size(); i++) {
			listBox2->Items->Add(gcnew String(imageFileNames[i].c_str()));
		}
	}
	catch (const std::exception & exp) {
		//catch no folder selected
	}
}

void MyForm::loadAnnotations() {
	Annotation annotation;
	openFileDialog2->ShowDialog();
	try {
		System::String^ filePathS = openFileDialog2->FileName;
		std::string filePath = msclr::interop::marshal_as<std::string>(filePathS);
		textBox3->Text = filePathS;
		classTexts.clear();
		classPoints.clear();
		shapes = annotation.open(filePath);
		pictureBox1->Invalidate();
	}
	catch (const std::exception& exp) {
		//catch no file selected
	}
}

void MyForm::setImage() {
	shapes.clear();
	classTexts.clear();
	classPoints.clear();

	imageFolder image;
	selectedImage = listBox2->SelectedIndex;
	std::string fullPath = image.fullPath(folderFilePath, imageFileNames[selectedImage]);
	System::String^ fullPathS = gcnew String(fullPath.c_str());
	if (pictureBox1->Image) {
		delete pictureBox1->Image;  // Prevent memory leak
	}
	pictureBox1->Image = pictureBox1->Image->FromFile(fullPathS);
}

void MyForm::resetShapeSelection() {
	delete selectSquare->Image;
	selectSquare->Load("square.PNG");

	delete selectPolygon->Image;
	selectPolygon->Load("polygon.PNG");
}

void MyForm::openClass() {
	openFileDialog3->Filter = "class files (*.names)|*.names|txt files (*.txt)|*.txt";
	
	if (openFileDialog3->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		try {
			System::String^ filePathS = openFileDialog3->FileName;
			classPath = msclr::interop::marshal_as<std::string>(filePathS);
			listBox1->Items->Clear();

			std::string currClass;
			std::ifstream infile;
			infile.open(classPath);
			while (!infile.eof()) // get all lines.
			{
				getline(infile, currClass); // Saves the line in currClass.
				listBox1->Items->Add(gcnew String(currClass.c_str()));
			}
			infile.close();
		}
		catch (const std::exception & exp) {
			//catch no file selected
		}
	}
}

void MyForm::addClass() {
	if (classPath != "" && !textBox2->Text->IsNullOrEmpty(textBox2->Text)) {
		std::ofstream myfile;
		myfile.open(classPath, std::ofstream::out | std::ofstream::app);

		std::string className = msclr::interop::marshal_as<std::string>(textBox2->Text);
		myfile << "\n" + className;
		listBox1->Items->Add(textBox2->Text);

		myfile.close();
	}
}

void MyForm::removeClass() {
	if (classPath != "" && (!textBox2->Text->IsNullOrEmpty(textBox2->Text) || listBox1->SelectedItem->ToString() != nullptr)) {

		std::string removeClass;
		if (textBox2->Text->IsNullOrEmpty(textBox2->Text)) {
			removeClass = msclr::interop::marshal_as<std::string>(listBox1->SelectedItem->ToString());
		}
		else {
			removeClass = msclr::interop::marshal_as<std::string>(textBox2->Text);
		}

		listBox1->Items->Clear();
		std::string currClass;
		linkedList<std::string> allClasses;
		std::ifstream infile;
		infile.open(classPath);
		while (!infile.eof()) // get all lines.
		{
			getline(infile, currClass); // Saves the line in currClass.
			if (currClass != removeClass) {
				allClasses.addBack(currClass);
				listBox1->Items->Add(gcnew String(currClass.c_str()));
			}
		}
		infile.close();

		std::ofstream myfile;
		myfile.open(classPath, std::ofstream::out | std::ofstream::trunc);

		for (int i = 0; i < allClasses.size(); i++) {
			if (i != allClasses.size() - 1) {
				myfile << allClasses.get(i) + "\n";
			}
			else {
				myfile << allClasses.get(i);
			}
		}

		myfile.close();
	}
}

void MyForm::changeSelectedClass() {
	classSelected = msclr::interop::marshal_as<std::string>(listBox1->SelectedItem->ToString());
}


[STAThread]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Image_Annotator::MyForm form;
	Application::Run(% form);
	//std::thread th1(autosave);
}