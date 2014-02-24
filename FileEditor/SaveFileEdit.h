#pragma once

#include "Environment.h"

namespace FileEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for SaveFileEdit
	/// </summary>
	public ref class SaveFileEdit : public System::Windows::Forms::Form
	{
	public:
		SaveFileEdit(void) : _envData(nullptr)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SaveFileEdit()
		{
			if (components)
			{
				delete components;
			}
			
			if(_envData)
			{
				delete _envData;
				_envData = nullptr;
			}
		}
	private: System::Windows::Forms::Button^  OpenButton;



	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::TextBox^  MaxXField;
	private: System::Windows::Forms::TextBox^  MaxYField;
	private: System::Windows::Forms::Label^  XLabel;
	private: System::Windows::Forms::Button^  SaveButton;

	protected: 

	protected: 


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::ComboBox^  ObjSelectField;

	private: System::Windows::Forms::TextBox^  ObjPosXField;
	private: System::Windows::Forms::TextBox^  ObjPosYField;
	private: System::Windows::Forms::TextBox^  ObjSizeYField;
	private: System::Windows::Forms::TextBox^  ObjSizeXField;
	private: System::Windows::Forms::Label^  ObjPosLabel;
	private: System::Windows::Forms::Label^  ObjSizeLabel;
	private: System::Windows::Forms::Label^  MaxDimensionLabel;
	private: System::Windows::Forms::Button^  ObjAddButton;
	private: System::Windows::Forms::Button^  RemoveObjButton;


		::Environment* _envData;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->OpenButton = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->MaxXField = (gcnew System::Windows::Forms::TextBox());
			this->MaxYField = (gcnew System::Windows::Forms::TextBox());
			this->XLabel = (gcnew System::Windows::Forms::Label());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->ObjSelectField = (gcnew System::Windows::Forms::ComboBox());
			this->ObjPosXField = (gcnew System::Windows::Forms::TextBox());
			this->ObjPosYField = (gcnew System::Windows::Forms::TextBox());
			this->ObjSizeYField = (gcnew System::Windows::Forms::TextBox());
			this->ObjSizeXField = (gcnew System::Windows::Forms::TextBox());
			this->ObjPosLabel = (gcnew System::Windows::Forms::Label());
			this->ObjSizeLabel = (gcnew System::Windows::Forms::Label());
			this->MaxDimensionLabel = (gcnew System::Windows::Forms::Label());
			this->ObjAddButton = (gcnew System::Windows::Forms::Button());
			this->RemoveObjButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// OpenButton
			// 
			this->OpenButton->Location = System::Drawing::Point(12, 12);
			this->OpenButton->Name = L"OpenButton";
			this->OpenButton->Size = System::Drawing::Size(75, 23);
			this->OpenButton->TabIndex = 1;
			this->OpenButton->Text = L"Open";
			this->OpenButton->UseVisualStyleBackColor = true;
			this->OpenButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::LoadFile);
			// 
			// MaxXField
			// 
			this->MaxXField->Location = System::Drawing::Point(13, 54);
			this->MaxXField->Name = L"MaxXField";
			this->MaxXField->Size = System::Drawing::Size(50, 20);
			this->MaxXField->TabIndex = 5;
			this->MaxXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::MaxXChanged);
			// 
			// MaxYField
			// 
			this->MaxYField->Location = System::Drawing::Point(87, 54);
			this->MaxYField->Name = L"MaxYField";
			this->MaxYField->Size = System::Drawing::Size(50, 20);
			this->MaxYField->TabIndex = 6;
			this->MaxYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::MaxYChanged);
			// 
			// XLabel
			// 
			this->XLabel->AutoSize = true;
			this->XLabel->Location = System::Drawing::Point(69, 60);
			this->XLabel->Name = L"XLabel";
			this->XLabel->Size = System::Drawing::Size(12, 13);
			this->XLabel->TabIndex = 7;
			this->XLabel->Text = L"x";
			// 
			// SaveButton
			// 
			this->SaveButton->Location = System::Drawing::Point(94, 13);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(75, 23);
			this->SaveButton->TabIndex = 8;
			this->SaveButton->Text = L"Save";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::SaveFile);
			// 
			// ObjSelectField
			// 
			this->ObjSelectField->FormattingEnabled = true;
			this->ObjSelectField->Location = System::Drawing::Point(14, 80);
			this->ObjSelectField->Name = L"ObjSelectField";
			this->ObjSelectField->Size = System::Drawing::Size(121, 21);
			this->ObjSelectField->TabIndex = 9;
			this->ObjSelectField->SelectedValueChanged += gcnew System::EventHandler(this, &SaveFileEdit::ObjSelectedChanged);
			// 
			// ObjPosXField
			// 
			this->ObjPosXField->Location = System::Drawing::Point(40, 120);
			this->ObjPosXField->Name = L"ObjPosXField";
			this->ObjPosXField->Size = System::Drawing::Size(100, 20);
			this->ObjPosXField->TabIndex = 10;
			this->ObjPosXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjPosYField
			// 
			this->ObjPosYField->Location = System::Drawing::Point(146, 120);
			this->ObjPosYField->Name = L"ObjPosYField";
			this->ObjPosYField->Size = System::Drawing::Size(100, 20);
			this->ObjPosYField->TabIndex = 12;
			this->ObjPosYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjSizeYField
			// 
			this->ObjSizeYField->Location = System::Drawing::Point(146, 159);
			this->ObjSizeYField->Name = L"ObjSizeYField";
			this->ObjSizeYField->Size = System::Drawing::Size(100, 20);
			this->ObjSizeYField->TabIndex = 14;
			this->ObjSizeYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjSizeXField
			// 
			this->ObjSizeXField->Location = System::Drawing::Point(40, 159);
			this->ObjSizeXField->Name = L"ObjSizeXField";
			this->ObjSizeXField->Size = System::Drawing::Size(100, 20);
			this->ObjSizeXField->TabIndex = 13;
			this->ObjSizeXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjPosLabel
			// 
			this->ObjPosLabel->AutoSize = true;
			this->ObjPosLabel->Location = System::Drawing::Point(37, 104);
			this->ObjPosLabel->Name = L"ObjPosLabel";
			this->ObjPosLabel->Size = System::Drawing::Size(103, 13);
			this->ObjPosLabel->TabIndex = 15;
			this->ObjPosLabel->Text = L"Object Position (x, y)";
			// 
			// ObjSizeLabel
			// 
			this->ObjSizeLabel->AutoSize = true;
			this->ObjSizeLabel->Location = System::Drawing::Point(37, 143);
			this->ObjSizeLabel->Name = L"ObjSizeLabel";
			this->ObjSizeLabel->Size = System::Drawing::Size(86, 13);
			this->ObjSizeLabel->TabIndex = 16;
			this->ObjSizeLabel->Text = L"Object Size (x, y)";
			// 
			// MaxDimensionLabel
			// 
			this->MaxDimensionLabel->AutoSize = true;
			this->MaxDimensionLabel->Location = System::Drawing::Point(10, 38);
			this->MaxDimensionLabel->Name = L"MaxDimensionLabel";
			this->MaxDimensionLabel->Size = System::Drawing::Size(114, 13);
			this->MaxDimensionLabel->TabIndex = 17;
			this->MaxDimensionLabel->Text = L"Environment Size (x, y)";
			// 
			// ObjAddButton
			// 
			this->ObjAddButton->Location = System::Drawing::Point(222, 80);
			this->ObjAddButton->Name = L"ObjAddButton";
			this->ObjAddButton->Size = System::Drawing::Size(75, 23);
			this->ObjAddButton->TabIndex = 18;
			this->ObjAddButton->Text = L"Add";
			this->ObjAddButton->UseVisualStyleBackColor = true;
			this->ObjAddButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::ObjAddButton_Click);
			// 
			// RemoveObjButton
			// 
			this->RemoveObjButton->Location = System::Drawing::Point(141, 80);
			this->RemoveObjButton->Name = L"RemoveObjButton";
			this->RemoveObjButton->Size = System::Drawing::Size(75, 23);
			this->RemoveObjButton->TabIndex = 19;
			this->RemoveObjButton->Text = L"Delete";
			this->RemoveObjButton->UseVisualStyleBackColor = true;
			this->RemoveObjButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::RemoveObjButton_Click);
			// 
			// SaveFileEdit
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(307, 693);
			this->Controls->Add(this->RemoveObjButton);
			this->Controls->Add(this->ObjAddButton);
			this->Controls->Add(this->MaxDimensionLabel);
			this->Controls->Add(this->ObjSizeLabel);
			this->Controls->Add(this->ObjPosLabel);
			this->Controls->Add(this->ObjSizeYField);
			this->Controls->Add(this->ObjSizeXField);
			this->Controls->Add(this->ObjPosYField);
			this->Controls->Add(this->ObjPosXField);
			this->Controls->Add(this->ObjSelectField);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->XLabel);
			this->Controls->Add(this->MaxYField);
			this->Controls->Add(this->MaxXField);
			this->Controls->Add(this->OpenButton);
			this->Name = L"SaveFileEdit";
			this->Text = L"File Editor";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void LoadFile(System::Object^  sender, System::EventArgs^  e) {
				 Stream^ myStream;
				 OpenFileDialog^ openFileDB = gcnew OpenFileDialog;

				 openFileDB->InitialDirectory = "C:\\Users\\rick\\Documents\\Development\\Graphics\\resources\\environments";
				 openFileDB->Filter = "Environment files|*.env|Save files|*.dat|All files|*.*";
				 openFileDB->FilterIndex = 0;
				 openFileDB->RestoreDirectory = true;

				 if(openFileDB->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 _envData = new ::Environment("start", 0);
					 MaxXField->Text = _envData->MaxX().ToString();
					 MaxYField->Text = _envData->MaxY().ToString();

					 for(unsigned int i=0; i<_envData->ObjList().size(); ++i)
						 ObjSelectField->Items->Add("Object " + i.ToString());

					 if((myStream = openFileDB->OpenFile()) != nullptr)
					 {
						 myStream->Close();
					 }
				 }
			 }
	private: System::Void SaveFile(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->Write();
				 }
			 }
	private: System::Void MaxXChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
					 _envData->MaxX((float)Convert::ToDouble(MaxXField->Text));
			 }
	private: System::Void MaxYChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
					 _envData->MaxY((float)Convert::ToDouble(MaxYField->Text));
			 }
	private: System::Void ObjSelectedChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 auto curObj = _envData->ObjList()[ObjSelectField->SelectedIndex];
					 ObjPosXField->Text = curObj._pos.x.ToString();
					 ObjPosYField->Text = curObj._pos.y.ToString();
					 ObjSizeXField->Text = curObj._size.x.ToString();
					 ObjSizeYField->Text = curObj._size.y.ToString();
				 }
			 }
	private: System::Void CurObjChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(ObjPosXField->Text != "" && ObjPosYField->Text != "" && ObjSizeXField->Text != "" && ObjSizeYField->Text != "" && _envData)
				 {
					 auto curObj = _envData->ObjList()[ObjSelectField->SelectedIndex];
					 ::Object::Core changedObj(curObj._type, 
						 glm::vec3((float)Convert::ToDouble(ObjPosXField->Text), (float)Convert::ToDouble(ObjPosYField->Text), curObj._pos.z),
						 glm::vec3((float)Convert::ToDouble(ObjSizeXField->Text), (float)Convert::ToDouble(ObjSizeYField->Text), curObj._size.z));
					 _envData->UpdateObj(changedObj, ObjSelectField->SelectedIndex);
				 }
			 }
	private: System::Void ObjAddButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->AddObj();
					 ObjSelectField->Items->Add("Object " + (_envData->ObjList().size()-1).ToString());
				 }
			 }
	private: System::Void RemoveObjButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->RemoveObj(ObjSelectField->SelectedIndex);
					 ObjSelectField->Items->RemoveAt(ObjSelectField->SelectedIndex);
					 ObjPosXField->Text = "";
					 ObjPosYField->Text = "";
					 ObjSizeXField->Text = "";
					 ObjSizeYField->Text = "";
				 }
			 }
};
}
