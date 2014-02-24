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
			this->MaxXField->Location = System::Drawing::Point(12, 41);
			this->MaxXField->Name = L"MaxXField";
			this->MaxXField->Size = System::Drawing::Size(100, 20);
			this->MaxXField->TabIndex = 5;
			// 
			// MaxYField
			// 
			this->MaxYField->Location = System::Drawing::Point(136, 41);
			this->MaxYField->Name = L"MaxYField";
			this->MaxYField->Size = System::Drawing::Size(100, 20);
			this->MaxYField->TabIndex = 6;
			// 
			// XLabel
			// 
			this->XLabel->AutoSize = true;
			this->XLabel->Location = System::Drawing::Point(118, 48);
			this->XLabel->Name = L"XLabel";
			this->XLabel->Size = System::Drawing::Size(12, 13);
			this->XLabel->TabIndex = 7;
			this->XLabel->Text = L"x";
			this->XLabel->Click += gcnew System::EventHandler(this, &SaveFileEdit::XLabel_Click);
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
			// SaveFileEdit
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 693);
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

					 if((myStream = openFileDB->OpenFile()) != nullptr)
					 {
						 myStream->Close();
					 }
				 }
			 }
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void XLabel_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void SaveFile(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 boost::format errorMsg;
					 //_envData->WriteInit("ENV0", errorMsg);
				 }
			 }
};
}
