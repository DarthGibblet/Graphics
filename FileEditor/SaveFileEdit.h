#pragma once

#include "Constants.h"
#include "Environment.h"

#include <msclr/marshal_cppstd.h>


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
	private: System::Windows::Forms::ComboBox^  ObjTypeField;
	private: System::Windows::Forms::Label^  ObjTypeLabel;
	private: System::Windows::Forms::Button^  RemoveEnemyButton;
	private: System::Windows::Forms::Button^  AddEnemyButton;
	private: System::Windows::Forms::ComboBox^  EnemySelectField;
	private: System::Windows::Forms::Label^  EnemyTypeLabel;
	private: System::Windows::Forms::ComboBox^  EnemyTypeField;
	private: System::Windows::Forms::Label^  EnemyPosLabel;



	private: System::Windows::Forms::TextBox^  EnemyPosYField;



	private: System::Windows::Forms::TextBox^  EnemyPosXField;
	private: System::Windows::Forms::Label^  UpgradeTypeLabel;
	private: System::Windows::Forms::ComboBox^  UpgradeTypeField;


	private: System::Windows::Forms::Button^  RemoveUpgradeButton;
	private: System::Windows::Forms::Button^  AddUpgradeButton;
	private: System::Windows::Forms::Label^  UpgradeSizeLabel;



	private: System::Windows::Forms::Label^  UpgradePosLabel;
	private: System::Windows::Forms::TextBox^  UpgradeSizeYField;


	private: System::Windows::Forms::TextBox^  UpgradeSizeXField;
	private: System::Windows::Forms::TextBox^  UpgradePosYField;


	private: System::Windows::Forms::TextBox^  UpgradePosXField;



	private: System::Windows::Forms::ComboBox^  UpgradeSelectField;
	private: System::Windows::Forms::Button^  RemoveEntranceButton;

	private: System::Windows::Forms::Button^  AddEntranceButton;
private: System::Windows::Forms::Label^  EntrancePosLabel;
private: System::Windows::Forms::TextBox^  EntrancePosYField;









private: System::Windows::Forms::TextBox^  EntrancePosXField;

	private: System::Windows::Forms::ComboBox^  EntranceSelectField;
private: System::Windows::Forms::Label^  ExitEndpointLabel;

private: System::Windows::Forms::ComboBox^  ExitEndpointEnvField;

private: System::Windows::Forms::Button^  RemoveExitButton;
private: System::Windows::Forms::Button^  AddExitButton;
private: System::Windows::Forms::Label^  ExitSizeLabel;




private: System::Windows::Forms::Label^  ExitPosLabel;
private: System::Windows::Forms::TextBox^  ExitSizeYField;


private: System::Windows::Forms::TextBox^  ExitSizeXField;

private: System::Windows::Forms::TextBox^  ExitPosYField;

private: System::Windows::Forms::TextBox^  ExitPosXField;

private: System::Windows::Forms::ComboBox^  ExitSelectField;
private: System::Windows::Forms::ComboBox^  ExitEndpointEntranceIDField;
private: System::Windows::Forms::Label^  ArchitectureGroupLabel;
private: System::Windows::Forms::Label^  EnemyGroupLabel;
private: System::Windows::Forms::Label^  UpgradeGroupLabel;
private: System::Windows::Forms::Label^  EntranceGroupLabel;
private: System::Windows::Forms::Label^  ExitGroupLabel;

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
			this->ObjTypeField = (gcnew System::Windows::Forms::ComboBox());
			this->ObjTypeLabel = (gcnew System::Windows::Forms::Label());
			this->RemoveEnemyButton = (gcnew System::Windows::Forms::Button());
			this->AddEnemyButton = (gcnew System::Windows::Forms::Button());
			this->EnemySelectField = (gcnew System::Windows::Forms::ComboBox());
			this->EnemyTypeLabel = (gcnew System::Windows::Forms::Label());
			this->EnemyTypeField = (gcnew System::Windows::Forms::ComboBox());
			this->EnemyPosLabel = (gcnew System::Windows::Forms::Label());
			this->EnemyPosYField = (gcnew System::Windows::Forms::TextBox());
			this->EnemyPosXField = (gcnew System::Windows::Forms::TextBox());
			this->UpgradeTypeLabel = (gcnew System::Windows::Forms::Label());
			this->UpgradeTypeField = (gcnew System::Windows::Forms::ComboBox());
			this->RemoveUpgradeButton = (gcnew System::Windows::Forms::Button());
			this->AddUpgradeButton = (gcnew System::Windows::Forms::Button());
			this->UpgradeSizeLabel = (gcnew System::Windows::Forms::Label());
			this->UpgradePosLabel = (gcnew System::Windows::Forms::Label());
			this->UpgradeSizeYField = (gcnew System::Windows::Forms::TextBox());
			this->UpgradeSizeXField = (gcnew System::Windows::Forms::TextBox());
			this->UpgradePosYField = (gcnew System::Windows::Forms::TextBox());
			this->UpgradePosXField = (gcnew System::Windows::Forms::TextBox());
			this->UpgradeSelectField = (gcnew System::Windows::Forms::ComboBox());
			this->RemoveEntranceButton = (gcnew System::Windows::Forms::Button());
			this->AddEntranceButton = (gcnew System::Windows::Forms::Button());
			this->EntrancePosLabel = (gcnew System::Windows::Forms::Label());
			this->EntrancePosYField = (gcnew System::Windows::Forms::TextBox());
			this->EntrancePosXField = (gcnew System::Windows::Forms::TextBox());
			this->EntranceSelectField = (gcnew System::Windows::Forms::ComboBox());
			this->ExitEndpointLabel = (gcnew System::Windows::Forms::Label());
			this->ExitEndpointEnvField = (gcnew System::Windows::Forms::ComboBox());
			this->RemoveExitButton = (gcnew System::Windows::Forms::Button());
			this->AddExitButton = (gcnew System::Windows::Forms::Button());
			this->ExitSizeLabel = (gcnew System::Windows::Forms::Label());
			this->ExitPosLabel = (gcnew System::Windows::Forms::Label());
			this->ExitSizeYField = (gcnew System::Windows::Forms::TextBox());
			this->ExitSizeXField = (gcnew System::Windows::Forms::TextBox());
			this->ExitPosYField = (gcnew System::Windows::Forms::TextBox());
			this->ExitPosXField = (gcnew System::Windows::Forms::TextBox());
			this->ExitSelectField = (gcnew System::Windows::Forms::ComboBox());
			this->ExitEndpointEntranceIDField = (gcnew System::Windows::Forms::ComboBox());
			this->ArchitectureGroupLabel = (gcnew System::Windows::Forms::Label());
			this->EnemyGroupLabel = (gcnew System::Windows::Forms::Label());
			this->UpgradeGroupLabel = (gcnew System::Windows::Forms::Label());
			this->EntranceGroupLabel = (gcnew System::Windows::Forms::Label());
			this->ExitGroupLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// OpenButton
			// 
			this->OpenButton->Location = System::Drawing::Point(15, 12);
			this->OpenButton->Name = L"OpenButton";
			this->OpenButton->Size = System::Drawing::Size(75, 23);
			this->OpenButton->TabIndex = 1;
			this->OpenButton->Text = L"Open";
			this->OpenButton->UseVisualStyleBackColor = true;
			this->OpenButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::LoadFile);
			// 
			// MaxXField
			// 
			this->MaxXField->Location = System::Drawing::Point(15, 54);
			this->MaxXField->Name = L"MaxXField";
			this->MaxXField->Size = System::Drawing::Size(50, 20);
			this->MaxXField->TabIndex = 5;
			this->MaxXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::MaxXChanged);
			// 
			// MaxYField
			// 
			this->MaxYField->Location = System::Drawing::Point(71, 54);
			this->MaxYField->Name = L"MaxYField";
			this->MaxYField->Size = System::Drawing::Size(50, 20);
			this->MaxYField->TabIndex = 6;
			this->MaxYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::MaxYChanged);
			// 
			// SaveButton
			// 
			this->SaveButton->Location = System::Drawing::Point(96, 12);
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
			this->ObjSelectField->Location = System::Drawing::Point(15, 97);
			this->ObjSelectField->Name = L"ObjSelectField";
			this->ObjSelectField->Size = System::Drawing::Size(120, 21);
			this->ObjSelectField->TabIndex = 9;
			this->ObjSelectField->SelectedIndexChanged += gcnew System::EventHandler(this, &SaveFileEdit::ObjSelectedChanged);
			// 
			// ObjPosXField
			// 
			this->ObjPosXField->Location = System::Drawing::Point(40, 177);
			this->ObjPosXField->Name = L"ObjPosXField";
			this->ObjPosXField->Size = System::Drawing::Size(50, 20);
			this->ObjPosXField->TabIndex = 10;
			this->ObjPosXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjPosYField
			// 
			this->ObjPosYField->Location = System::Drawing::Point(95, 177);
			this->ObjPosYField->Name = L"ObjPosYField";
			this->ObjPosYField->Size = System::Drawing::Size(50, 20);
			this->ObjPosYField->TabIndex = 12;
			this->ObjPosYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjSizeYField
			// 
			this->ObjSizeYField->Location = System::Drawing::Point(95, 216);
			this->ObjSizeYField->Name = L"ObjSizeYField";
			this->ObjSizeYField->Size = System::Drawing::Size(50, 20);
			this->ObjSizeYField->TabIndex = 14;
			this->ObjSizeYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjSizeXField
			// 
			this->ObjSizeXField->Location = System::Drawing::Point(40, 216);
			this->ObjSizeXField->Name = L"ObjSizeXField";
			this->ObjSizeXField->Size = System::Drawing::Size(50, 20);
			this->ObjSizeXField->TabIndex = 13;
			this->ObjSizeXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjPosLabel
			// 
			this->ObjPosLabel->AutoSize = true;
			this->ObjPosLabel->Location = System::Drawing::Point(40, 161);
			this->ObjPosLabel->Name = L"ObjPosLabel";
			this->ObjPosLabel->Size = System::Drawing::Size(103, 13);
			this->ObjPosLabel->TabIndex = 15;
			this->ObjPosLabel->Text = L"Object Position (x, y)";
			// 
			// ObjSizeLabel
			// 
			this->ObjSizeLabel->AutoSize = true;
			this->ObjSizeLabel->Location = System::Drawing::Point(37, 200);
			this->ObjSizeLabel->Name = L"ObjSizeLabel";
			this->ObjSizeLabel->Size = System::Drawing::Size(86, 13);
			this->ObjSizeLabel->TabIndex = 16;
			this->ObjSizeLabel->Text = L"Object Size (x, y)";
			// 
			// MaxDimensionLabel
			// 
			this->MaxDimensionLabel->AutoSize = true;
			this->MaxDimensionLabel->Location = System::Drawing::Point(15, 38);
			this->MaxDimensionLabel->Name = L"MaxDimensionLabel";
			this->MaxDimensionLabel->Size = System::Drawing::Size(114, 13);
			this->MaxDimensionLabel->TabIndex = 17;
			this->MaxDimensionLabel->Text = L"Environment Size (x, y)";
			// 
			// ObjAddButton
			// 
			this->ObjAddButton->Location = System::Drawing::Point(220, 97);
			this->ObjAddButton->Name = L"ObjAddButton";
			this->ObjAddButton->Size = System::Drawing::Size(75, 23);
			this->ObjAddButton->TabIndex = 18;
			this->ObjAddButton->Text = L"Add";
			this->ObjAddButton->UseVisualStyleBackColor = true;
			this->ObjAddButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::AddObj);
			// 
			// RemoveObjButton
			// 
			this->RemoveObjButton->Location = System::Drawing::Point(140, 97);
			this->RemoveObjButton->Name = L"RemoveObjButton";
			this->RemoveObjButton->Size = System::Drawing::Size(75, 23);
			this->RemoveObjButton->TabIndex = 19;
			this->RemoveObjButton->Text = L"Delete";
			this->RemoveObjButton->UseVisualStyleBackColor = true;
			this->RemoveObjButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::RemoveObj);
			// 
			// ObjTypeField
			// 
			this->ObjTypeField->FormattingEnabled = true;
			this->ObjTypeField->Location = System::Drawing::Point(40, 137);
			this->ObjTypeField->Name = L"ObjTypeField";
			this->ObjTypeField->Size = System::Drawing::Size(121, 21);
			this->ObjTypeField->TabIndex = 20;
			this->ObjTypeField->SelectedIndexChanged += gcnew System::EventHandler(this, &SaveFileEdit::CurObjChanged);
			// 
			// ObjTypeLabel
			// 
			this->ObjTypeLabel->AutoSize = true;
			this->ObjTypeLabel->Location = System::Drawing::Point(40, 121);
			this->ObjTypeLabel->Name = L"ObjTypeLabel";
			this->ObjTypeLabel->Size = System::Drawing::Size(65, 13);
			this->ObjTypeLabel->TabIndex = 21;
			this->ObjTypeLabel->Text = L"Object Type";
			// 
			// RemoveEnemyButton
			// 
			this->RemoveEnemyButton->Location = System::Drawing::Point(140, 255);
			this->RemoveEnemyButton->Name = L"RemoveEnemyButton";
			this->RemoveEnemyButton->Size = System::Drawing::Size(75, 23);
			this->RemoveEnemyButton->TabIndex = 24;
			this->RemoveEnemyButton->Text = L"Delete";
			this->RemoveEnemyButton->UseVisualStyleBackColor = true;
			this->RemoveEnemyButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::RemoveEnemy);
			// 
			// AddEnemyButton
			// 
			this->AddEnemyButton->Location = System::Drawing::Point(220, 255);
			this->AddEnemyButton->Name = L"AddEnemyButton";
			this->AddEnemyButton->Size = System::Drawing::Size(75, 23);
			this->AddEnemyButton->TabIndex = 23;
			this->AddEnemyButton->Text = L"Add";
			this->AddEnemyButton->UseVisualStyleBackColor = true;
			this->AddEnemyButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::AddEnemy);
			// 
			// EnemySelectField
			// 
			this->EnemySelectField->FormattingEnabled = true;
			this->EnemySelectField->Location = System::Drawing::Point(15, 255);
			this->EnemySelectField->Name = L"EnemySelectField";
			this->EnemySelectField->Size = System::Drawing::Size(120, 21);
			this->EnemySelectField->TabIndex = 22;
			this->EnemySelectField->SelectedIndexChanged += gcnew System::EventHandler(this, &SaveFileEdit::EnemySelectedChanged);
			// 
			// EnemyTypeLabel
			// 
			this->EnemyTypeLabel->AutoSize = true;
			this->EnemyTypeLabel->Location = System::Drawing::Point(40, 279);
			this->EnemyTypeLabel->Name = L"EnemyTypeLabel";
			this->EnemyTypeLabel->Size = System::Drawing::Size(66, 13);
			this->EnemyTypeLabel->TabIndex = 32;
			this->EnemyTypeLabel->Text = L"Enemy Type";
			// 
			// EnemyTypeField
			// 
			this->EnemyTypeField->FormattingEnabled = true;
			this->EnemyTypeField->Location = System::Drawing::Point(40, 295);
			this->EnemyTypeField->Name = L"EnemyTypeField";
			this->EnemyTypeField->Size = System::Drawing::Size(121, 21);
			this->EnemyTypeField->TabIndex = 31;
			this->EnemyTypeField->SelectedValueChanged += gcnew System::EventHandler(this, &SaveFileEdit::EnemyChanged);
			// 
			// EnemyPosLabel
			// 
			this->EnemyPosLabel->AutoSize = true;
			this->EnemyPosLabel->Location = System::Drawing::Point(40, 319);
			this->EnemyPosLabel->Name = L"EnemyPosLabel";
			this->EnemyPosLabel->Size = System::Drawing::Size(104, 13);
			this->EnemyPosLabel->TabIndex = 29;
			this->EnemyPosLabel->Text = L"Enemy Position (x, y)";
			// 
			// EnemyPosYField
			// 
			this->EnemyPosYField->Location = System::Drawing::Point(95, 335);
			this->EnemyPosYField->Name = L"EnemyPosYField";
			this->EnemyPosYField->Size = System::Drawing::Size(50, 20);
			this->EnemyPosYField->TabIndex = 26;
			this->EnemyPosYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::EnemyChanged);
			// 
			// EnemyPosXField
			// 
			this->EnemyPosXField->Location = System::Drawing::Point(40, 335);
			this->EnemyPosXField->Name = L"EnemyPosXField";
			this->EnemyPosXField->Size = System::Drawing::Size(50, 20);
			this->EnemyPosXField->TabIndex = 25;
			this->EnemyPosXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::EnemyChanged);
			// 
			// UpgradeTypeLabel
			// 
			this->UpgradeTypeLabel->AutoSize = true;
			this->UpgradeTypeLabel->Location = System::Drawing::Point(40, 398);
			this->UpgradeTypeLabel->Name = L"UpgradeTypeLabel";
			this->UpgradeTypeLabel->Size = System::Drawing::Size(75, 13);
			this->UpgradeTypeLabel->TabIndex = 43;
			this->UpgradeTypeLabel->Text = L"Upgrade Type";
			// 
			// UpgradeTypeField
			// 
			this->UpgradeTypeField->FormattingEnabled = true;
			this->UpgradeTypeField->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Wall Jump", L"Double Jump"});
			this->UpgradeTypeField->Location = System::Drawing::Point(40, 414);
			this->UpgradeTypeField->Name = L"UpgradeTypeField";
			this->UpgradeTypeField->Size = System::Drawing::Size(121, 21);
			this->UpgradeTypeField->TabIndex = 42;
			this->UpgradeTypeField->SelectedValueChanged += gcnew System::EventHandler(this, &SaveFileEdit::UpgradeChanged);
			// 
			// RemoveUpgradeButton
			// 
			this->RemoveUpgradeButton->Location = System::Drawing::Point(140, 374);
			this->RemoveUpgradeButton->Name = L"RemoveUpgradeButton";
			this->RemoveUpgradeButton->Size = System::Drawing::Size(75, 23);
			this->RemoveUpgradeButton->TabIndex = 41;
			this->RemoveUpgradeButton->Text = L"Delete";
			this->RemoveUpgradeButton->UseVisualStyleBackColor = true;
			this->RemoveUpgradeButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::RemoveUpgrade);
			// 
			// AddUpgradeButton
			// 
			this->AddUpgradeButton->Location = System::Drawing::Point(220, 374);
			this->AddUpgradeButton->Name = L"AddUpgradeButton";
			this->AddUpgradeButton->Size = System::Drawing::Size(75, 23);
			this->AddUpgradeButton->TabIndex = 40;
			this->AddUpgradeButton->Text = L"Add";
			this->AddUpgradeButton->UseVisualStyleBackColor = true;
			this->AddUpgradeButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::AddUpgrade);
			// 
			// UpgradeSizeLabel
			// 
			this->UpgradeSizeLabel->AutoSize = true;
			this->UpgradeSizeLabel->Location = System::Drawing::Point(40, 477);
			this->UpgradeSizeLabel->Name = L"UpgradeSizeLabel";
			this->UpgradeSizeLabel->Size = System::Drawing::Size(96, 13);
			this->UpgradeSizeLabel->TabIndex = 39;
			this->UpgradeSizeLabel->Text = L"Upgrade Size (x, y)";
			// 
			// UpgradePosLabel
			// 
			this->UpgradePosLabel->AutoSize = true;
			this->UpgradePosLabel->Location = System::Drawing::Point(40, 438);
			this->UpgradePosLabel->Name = L"UpgradePosLabel";
			this->UpgradePosLabel->Size = System::Drawing::Size(113, 13);
			this->UpgradePosLabel->TabIndex = 38;
			this->UpgradePosLabel->Text = L"Upgrade Position (x, y)";
			// 
			// UpgradeSizeYField
			// 
			this->UpgradeSizeYField->Location = System::Drawing::Point(95, 493);
			this->UpgradeSizeYField->Name = L"UpgradeSizeYField";
			this->UpgradeSizeYField->Size = System::Drawing::Size(50, 20);
			this->UpgradeSizeYField->TabIndex = 37;
			this->UpgradeSizeYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::UpgradeChanged);
			// 
			// UpgradeSizeXField
			// 
			this->UpgradeSizeXField->Location = System::Drawing::Point(40, 493);
			this->UpgradeSizeXField->Name = L"UpgradeSizeXField";
			this->UpgradeSizeXField->Size = System::Drawing::Size(50, 20);
			this->UpgradeSizeXField->TabIndex = 36;
			this->UpgradeSizeXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::UpgradeChanged);
			// 
			// UpgradePosYField
			// 
			this->UpgradePosYField->Location = System::Drawing::Point(95, 454);
			this->UpgradePosYField->Name = L"UpgradePosYField";
			this->UpgradePosYField->Size = System::Drawing::Size(50, 20);
			this->UpgradePosYField->TabIndex = 35;
			this->UpgradePosYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::UpgradeChanged);
			// 
			// UpgradePosXField
			// 
			this->UpgradePosXField->Location = System::Drawing::Point(40, 454);
			this->UpgradePosXField->Name = L"UpgradePosXField";
			this->UpgradePosXField->Size = System::Drawing::Size(50, 20);
			this->UpgradePosXField->TabIndex = 34;
			this->UpgradePosXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::UpgradeChanged);
			// 
			// UpgradeSelectField
			// 
			this->UpgradeSelectField->FormattingEnabled = true;
			this->UpgradeSelectField->Location = System::Drawing::Point(15, 374);
			this->UpgradeSelectField->Name = L"UpgradeSelectField";
			this->UpgradeSelectField->Size = System::Drawing::Size(120, 21);
			this->UpgradeSelectField->TabIndex = 33;
			this->UpgradeSelectField->SelectedIndexChanged += gcnew System::EventHandler(this, &SaveFileEdit::UpgradeSelectedChanged);
			// 
			// RemoveEntranceButton
			// 
			this->RemoveEntranceButton->Location = System::Drawing::Point(143, 532);
			this->RemoveEntranceButton->Name = L"RemoveEntranceButton";
			this->RemoveEntranceButton->Size = System::Drawing::Size(75, 23);
			this->RemoveEntranceButton->TabIndex = 52;
			this->RemoveEntranceButton->Text = L"Delete";
			this->RemoveEntranceButton->UseVisualStyleBackColor = true;
			this->RemoveEntranceButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::RemoveEntrance);
			// 
			// AddEntranceButton
			// 
			this->AddEntranceButton->Location = System::Drawing::Point(223, 532);
			this->AddEntranceButton->Name = L"AddEntranceButton";
			this->AddEntranceButton->Size = System::Drawing::Size(75, 23);
			this->AddEntranceButton->TabIndex = 51;
			this->AddEntranceButton->Text = L"Add";
			this->AddEntranceButton->UseVisualStyleBackColor = true;
			this->AddEntranceButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::AddEntrance);
			// 
			// EntrancePosLabel
			// 
			this->EntrancePosLabel->AutoSize = true;
			this->EntrancePosLabel->Location = System::Drawing::Point(40, 558);
			this->EntrancePosLabel->Name = L"EntrancePosLabel";
			this->EntrancePosLabel->Size = System::Drawing::Size(115, 13);
			this->EntrancePosLabel->TabIndex = 49;
			this->EntrancePosLabel->Text = L"Entrance Position (x, y)";
			// 
			// EntrancePosYField
			// 
			this->EntrancePosYField->Location = System::Drawing::Point(95, 574);
			this->EntrancePosYField->Name = L"EntrancePosYField";
			this->EntrancePosYField->Size = System::Drawing::Size(50, 20);
			this->EntrancePosYField->TabIndex = 46;
			this->EntrancePosYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::EntranceChanged);
			// 
			// EntrancePosXField
			// 
			this->EntrancePosXField->Location = System::Drawing::Point(40, 574);
			this->EntrancePosXField->Name = L"EntrancePosXField";
			this->EntrancePosXField->Size = System::Drawing::Size(50, 20);
			this->EntrancePosXField->TabIndex = 45;
			this->EntrancePosXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::EntranceChanged);
			// 
			// EntranceSelectField
			// 
			this->EntranceSelectField->FormattingEnabled = true;
			this->EntranceSelectField->Location = System::Drawing::Point(18, 532);
			this->EntranceSelectField->Name = L"EntranceSelectField";
			this->EntranceSelectField->Size = System::Drawing::Size(120, 21);
			this->EntranceSelectField->TabIndex = 44;
			this->EntranceSelectField->SelectedIndexChanged += gcnew System::EventHandler(this, &SaveFileEdit::EntranceSelectedChanged);
			// 
			// ExitEndpointLabel
			// 
			this->ExitEndpointLabel->AutoSize = true;
			this->ExitEndpointLabel->Location = System::Drawing::Point(41, 637);
			this->ExitEndpointLabel->Name = L"ExitEndpointLabel";
			this->ExitEndpointLabel->Size = System::Drawing::Size(94, 13);
			this->ExitEndpointLabel->TabIndex = 65;
			this->ExitEndpointLabel->Text = L"Opposite Endpoint";
			// 
			// ExitEndpointEnvField
			// 
			this->ExitEndpointEnvField->FormattingEnabled = true;
			this->ExitEndpointEnvField->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"start", L"one_zero"});
			this->ExitEndpointEnvField->Location = System::Drawing::Point(41, 653);
			this->ExitEndpointEnvField->Name = L"ExitEndpointEnvField";
			this->ExitEndpointEnvField->Size = System::Drawing::Size(121, 21);
			this->ExitEndpointEnvField->TabIndex = 64;
			this->ExitEndpointEnvField->SelectedIndexChanged += gcnew System::EventHandler(this, &SaveFileEdit::ExitChanged);
			// 
			// RemoveExitButton
			// 
			this->RemoveExitButton->Location = System::Drawing::Point(142, 613);
			this->RemoveExitButton->Name = L"RemoveExitButton";
			this->RemoveExitButton->Size = System::Drawing::Size(75, 23);
			this->RemoveExitButton->TabIndex = 63;
			this->RemoveExitButton->Text = L"Delete";
			this->RemoveExitButton->UseVisualStyleBackColor = true;
			this->RemoveExitButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::RemoveExit);
			// 
			// AddExitButton
			// 
			this->AddExitButton->Location = System::Drawing::Point(223, 613);
			this->AddExitButton->Name = L"AddExitButton";
			this->AddExitButton->Size = System::Drawing::Size(75, 23);
			this->AddExitButton->TabIndex = 62;
			this->AddExitButton->Text = L"Add";
			this->AddExitButton->UseVisualStyleBackColor = true;
			this->AddExitButton->Click += gcnew System::EventHandler(this, &SaveFileEdit::AddExit);
			// 
			// ExitSizeLabel
			// 
			this->ExitSizeLabel->AutoSize = true;
			this->ExitSizeLabel->Location = System::Drawing::Point(41, 716);
			this->ExitSizeLabel->Name = L"ExitSizeLabel";
			this->ExitSizeLabel->Size = System::Drawing::Size(96, 13);
			this->ExitSizeLabel->TabIndex = 61;
			this->ExitSizeLabel->Text = L"Upgrade Size (x, y)";
			// 
			// ExitPosLabel
			// 
			this->ExitPosLabel->AutoSize = true;
			this->ExitPosLabel->Location = System::Drawing::Point(41, 677);
			this->ExitPosLabel->Name = L"ExitPosLabel";
			this->ExitPosLabel->Size = System::Drawing::Size(89, 13);
			this->ExitPosLabel->TabIndex = 60;
			this->ExitPosLabel->Text = L"Exit Position (x, y)";
			// 
			// ExitSizeYField
			// 
			this->ExitSizeYField->Location = System::Drawing::Point(96, 732);
			this->ExitSizeYField->Name = L"ExitSizeYField";
			this->ExitSizeYField->Size = System::Drawing::Size(50, 20);
			this->ExitSizeYField->TabIndex = 59;
			this->ExitSizeYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::ExitChanged);
			// 
			// ExitSizeXField
			// 
			this->ExitSizeXField->Location = System::Drawing::Point(41, 732);
			this->ExitSizeXField->Name = L"ExitSizeXField";
			this->ExitSizeXField->Size = System::Drawing::Size(50, 20);
			this->ExitSizeXField->TabIndex = 58;
			this->ExitSizeXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::ExitChanged);
			// 
			// ExitPosYField
			// 
			this->ExitPosYField->Location = System::Drawing::Point(96, 693);
			this->ExitPosYField->Name = L"ExitPosYField";
			this->ExitPosYField->Size = System::Drawing::Size(50, 20);
			this->ExitPosYField->TabIndex = 57;
			this->ExitPosYField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::ExitChanged);
			// 
			// ExitPosXField
			// 
			this->ExitPosXField->Location = System::Drawing::Point(41, 693);
			this->ExitPosXField->Name = L"ExitPosXField";
			this->ExitPosXField->Size = System::Drawing::Size(50, 20);
			this->ExitPosXField->TabIndex = 56;
			this->ExitPosXField->TextChanged += gcnew System::EventHandler(this, &SaveFileEdit::ExitChanged);
			// 
			// ExitSelectField
			// 
			this->ExitSelectField->FormattingEnabled = true;
			this->ExitSelectField->Location = System::Drawing::Point(15, 613);
			this->ExitSelectField->Name = L"ExitSelectField";
			this->ExitSelectField->Size = System::Drawing::Size(121, 21);
			this->ExitSelectField->TabIndex = 55;
			this->ExitSelectField->SelectedIndexChanged += gcnew System::EventHandler(this, &SaveFileEdit::ExitSelectedChanged);
			// 
			// ExitEndpointEntranceIDField
			// 
			this->ExitEndpointEntranceIDField->FormattingEnabled = true;
			this->ExitEndpointEntranceIDField->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"0", L"1"});
			this->ExitEndpointEntranceIDField->Location = System::Drawing::Point(168, 653);
			this->ExitEndpointEntranceIDField->Name = L"ExitEndpointEntranceIDField";
			this->ExitEndpointEntranceIDField->Size = System::Drawing::Size(121, 21);
			this->ExitEndpointEntranceIDField->TabIndex = 66;
			this->ExitEndpointEntranceIDField->SelectedIndexChanged += gcnew System::EventHandler(this, &SaveFileEdit::ExitChanged);
			// 
			// ArchitectureGroupLabel
			// 
			this->ArchitectureGroupLabel->AutoSize = true;
			this->ArchitectureGroupLabel->Location = System::Drawing::Point(15, 81);
			this->ArchitectureGroupLabel->Name = L"ArchitectureGroupLabel";
			this->ArchitectureGroupLabel->Size = System::Drawing::Size(64, 13);
			this->ArchitectureGroupLabel->TabIndex = 67;
			this->ArchitectureGroupLabel->Text = L"Architecture";
			// 
			// EnemyGroupLabel
			// 
			this->EnemyGroupLabel->AutoSize = true;
			this->EnemyGroupLabel->Location = System::Drawing::Point(15, 239);
			this->EnemyGroupLabel->Name = L"EnemyGroupLabel";
			this->EnemyGroupLabel->Size = System::Drawing::Size(47, 13);
			this->EnemyGroupLabel->TabIndex = 68;
			this->EnemyGroupLabel->Text = L"Enemies";
			// 
			// UpgradeGroupLabel
			// 
			this->UpgradeGroupLabel->AutoSize = true;
			this->UpgradeGroupLabel->Location = System::Drawing::Point(15, 358);
			this->UpgradeGroupLabel->Name = L"UpgradeGroupLabel";
			this->UpgradeGroupLabel->Size = System::Drawing::Size(53, 13);
			this->UpgradeGroupLabel->TabIndex = 69;
			this->UpgradeGroupLabel->Text = L"Upgrades";
			// 
			// EntranceGroupLabel
			// 
			this->EntranceGroupLabel->AutoSize = true;
			this->EntranceGroupLabel->Location = System::Drawing::Point(15, 516);
			this->EntranceGroupLabel->Name = L"EntranceGroupLabel";
			this->EntranceGroupLabel->Size = System::Drawing::Size(55, 13);
			this->EntranceGroupLabel->TabIndex = 70;
			this->EntranceGroupLabel->Text = L"Entrances";
			// 
			// ExitGroupLabel
			// 
			this->ExitGroupLabel->AutoSize = true;
			this->ExitGroupLabel->Location = System::Drawing::Point(15, 597);
			this->ExitGroupLabel->Name = L"ExitGroupLabel";
			this->ExitGroupLabel->Size = System::Drawing::Size(29, 13);
			this->ExitGroupLabel->TabIndex = 71;
			this->ExitGroupLabel->Text = L"Exits";
			// 
			// SaveFileEdit
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(307, 776);
			this->Controls->Add(this->ExitGroupLabel);
			this->Controls->Add(this->EntranceGroupLabel);
			this->Controls->Add(this->UpgradeGroupLabel);
			this->Controls->Add(this->EnemyGroupLabel);
			this->Controls->Add(this->ArchitectureGroupLabel);
			this->Controls->Add(this->ExitEndpointEntranceIDField);
			this->Controls->Add(this->ExitEndpointLabel);
			this->Controls->Add(this->ExitEndpointEnvField);
			this->Controls->Add(this->RemoveExitButton);
			this->Controls->Add(this->AddExitButton);
			this->Controls->Add(this->ExitSizeLabel);
			this->Controls->Add(this->ExitPosLabel);
			this->Controls->Add(this->ExitSizeYField);
			this->Controls->Add(this->ExitSizeXField);
			this->Controls->Add(this->ExitPosYField);
			this->Controls->Add(this->ExitPosXField);
			this->Controls->Add(this->ExitSelectField);
			this->Controls->Add(this->RemoveEntranceButton);
			this->Controls->Add(this->AddEntranceButton);
			this->Controls->Add(this->EntrancePosLabel);
			this->Controls->Add(this->EntrancePosYField);
			this->Controls->Add(this->EntrancePosXField);
			this->Controls->Add(this->EntranceSelectField);
			this->Controls->Add(this->UpgradeTypeLabel);
			this->Controls->Add(this->UpgradeTypeField);
			this->Controls->Add(this->RemoveUpgradeButton);
			this->Controls->Add(this->AddUpgradeButton);
			this->Controls->Add(this->UpgradeSizeLabel);
			this->Controls->Add(this->UpgradePosLabel);
			this->Controls->Add(this->UpgradeSizeYField);
			this->Controls->Add(this->UpgradeSizeXField);
			this->Controls->Add(this->UpgradePosYField);
			this->Controls->Add(this->UpgradePosXField);
			this->Controls->Add(this->UpgradeSelectField);
			this->Controls->Add(this->EnemyTypeLabel);
			this->Controls->Add(this->EnemyTypeField);
			this->Controls->Add(this->EnemyPosLabel);
			this->Controls->Add(this->EnemyPosYField);
			this->Controls->Add(this->EnemyPosXField);
			this->Controls->Add(this->RemoveEnemyButton);
			this->Controls->Add(this->AddEnemyButton);
			this->Controls->Add(this->EnemySelectField);
			this->Controls->Add(this->ObjTypeLabel);
			this->Controls->Add(this->ObjTypeField);
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
				 OpenFileDialog^ openFileDB = gcnew OpenFileDialog;

				 openFileDB->InitialDirectory = "C:\\Users\\rick\\Documents\\Development\\Graphics\\resources\\environments";
				 openFileDB->Filter = "Environment files|*.env|Save files|*.dat|All files|*.*";
				 openFileDB->FilterIndex = 0;
				 openFileDB->RestoreDirectory = true;

				 if(openFileDB->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 msclr::interop::marshal_context context;
					 _envData = new ::Environment(msclr::interop::marshal_as<std::string>(openFileDB->FileName), 0, true);
					 MaxXField->Text = _envData->MaxX().ToString();
					 MaxYField->Text = _envData->MaxY().ToString();

					 ObjSelectField->Items->Clear();
					 for(size_t i=0; i<_envData->_architecture.Size(); ++i)
					 {
						 String^ objName = gcnew String((::Object::Type::ToString(_envData->_architecture.Get(i)._type) + " ").c_str());
						 ObjSelectField->Items->Add(objName + i.ToString());
					 }

					 ObjTypeField->Items->Clear();
					 for(unsigned int iType=::Object::Type::Generic; iType < ::Object::Type::END; ++iType)
						 ObjTypeField->Items->Add(gcnew String(::Object::Type::ToString(iType).c_str()));

					 EnemySelectField->Items->Clear();
					 for(size_t i=0; i<_envData->_enemies.Size(); ++i)
					 {
						 String^ enemyName = gcnew String((::Object::EnemyType::ToString(_envData->_enemies.Get(i).first) + " ").c_str());
						 EnemySelectField->Items->Add(enemyName + i.ToString());
					 }

					 EnemyTypeField->Items->Clear();
					 for(unsigned int iType = ::Object::EnemyType::Generic; iType < ::Object::EnemyType::END; ++iType)
						 EnemyTypeField->Items->Add(gcnew String(::Object::EnemyType::ToString(iType).c_str()));

					 UpgradeSelectField->Items->Clear();
					 for(size_t i=0; i<_envData->_upgrades.Size(); ++i)
						 UpgradeSelectField->Items->Add("Upgrade " + i.ToString());

					 EntranceSelectField->Items->Clear();
					 for(size_t i=0; i<_envData->_entrances.Size(); ++i)
						 EntranceSelectField->Items->Add("Entrance " + i.ToString());

					 ExitSelectField->Items->Clear();
					 for(size_t i=0; i<_envData->_exits.Size(); ++i)
						 ExitSelectField->Items->Add("Exit " + i.ToString());
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
					 auto curObj = _envData->_architecture.Get(ObjSelectField->SelectedIndex);
					 ObjTypeField->SelectedIndex = curObj._type;
					 ObjPosXField->Text = curObj._pos.x.ToString();
					 ObjPosYField->Text = curObj._pos.y.ToString();
					 ObjSizeXField->Text = curObj._size.x.ToString();
					 ObjSizeYField->Text = curObj._size.y.ToString();
				 }
			 }
	private: System::Void EnemySelectedChanged(System::Object^  sender, System::EventArgs^ e) {
				 if(_envData)
				 {
					 auto curEnemy = _envData->_enemies.Get(EnemySelectField->SelectedIndex);
					 EnemyTypeField->SelectedIndex = curEnemy.first;
					 EnemyPosXField->Text = curEnemy.second._pos.x.ToString();
					 EnemyPosYField->Text = curEnemy.second._pos.y.ToString();
				 }
			 }
	private: System::Void UpgradeSelectedChanged(System::Object^  sender, System::EventArgs^ e) {
				 if(_envData)
				 {
					 auto curUpgrade = _envData->_upgrades.Get(UpgradeSelectField->SelectedIndex);
					 switch(curUpgrade.first)
					 {
					 case ::Upgrade::Type::WALL_JUMP:
						 UpgradeTypeField->SelectedIndex = 0;
						 break;
					 case ::Upgrade::Type::DOUBLE_JUMP:
						 UpgradeTypeField->SelectedIndex = 1;
						 break;
					 }
					 UpgradePosXField->Text = curUpgrade.second._pos.x.ToString();
					 UpgradePosYField->Text = curUpgrade.second._pos.y.ToString();
					 UpgradeSizeXField->Text = curUpgrade.second._size.x.ToString();
					 UpgradeSizeYField->Text = curUpgrade.second._size.y.ToString();
				 }
			 }
	private: System::Void EntranceSelectedChanged(System::Object^  sender, System::EventArgs^ e) {
				 if(_envData)
				 {
					 auto curEntrance = _envData->_entrances.Get(EntranceSelectField->SelectedIndex);
					 EntrancePosXField->Text = curEntrance.x.ToString();
					 EntrancePosYField->Text = curEntrance.y.ToString();
				 }
			 }
	private: System::Void ExitSelectedChanged(System::Object^  sender, System::EventArgs^ e) {
				 if(_envData)
				 {
					 auto curExit = _envData->_exits.Get(ExitSelectField->SelectedIndex);
					 ExitEndpointEnvField->SelectedIndex = curExit._envId;
					 ExitEndpointEntranceIDField->SelectedIndex = curExit._entranceId;
					 ExitPosXField->Text = curExit._core._pos.x.ToString();
					 ExitPosYField->Text = curExit._core._pos.y.ToString();
					 ExitSizeXField->Text = curExit._core._size.x.ToString();
					 ExitSizeYField->Text = curExit._core._size.y.ToString();
				 }
			 }
	private: System::Void CurObjChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(ObjTypeField->SelectedItem != "" && ObjPosXField->Text != "" && ObjPosYField->Text != "" && ObjSizeXField->Text != "" && ObjSizeYField->Text != "" && _envData)
				 {
					 auto curObj = _envData->_architecture.Get(ObjSelectField->SelectedIndex);
					 ::Environment::arch_desc_t changedObj(static_cast<::Object::Type::E>(ObjTypeField->SelectedIndex), 
						 glm::vec3((float)Convert::ToDouble(ObjPosXField->Text), (float)Convert::ToDouble(ObjPosYField->Text), curObj._pos.z),
						 glm::vec3((float)Convert::ToDouble(ObjSizeXField->Text), (float)Convert::ToDouble(ObjSizeYField->Text), curObj._size.z));
					 _envData->_architecture.Update(changedObj, ObjSelectField->SelectedIndex);
				 }
			 }
	private: System::Void EnemyChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(EnemyTypeField->SelectedItem != "" && EnemyPosXField->Text != "" && EnemyPosYField->Text != "" && _envData)
				 {
					 auto curEnemy = _envData->_enemies.Get(EnemySelectField->SelectedIndex);
					 ::Environment::enemy_desc_t changedEnemy = std::make_pair(static_cast<::Object::EnemyType::E>(EnemyTypeField->SelectedIndex),
						 ::Object::Core(::Object::Type::Enemy,
							glm::vec3((float)Convert::ToDouble(EnemyPosXField->Text), (float)Convert::ToDouble(EnemyPosYField->Text), curEnemy.second._pos.z),
							glm::vec3()));
					 _envData->_enemies.Update(changedEnemy, EnemySelectField->SelectedIndex);
				 }
			 }
	private: System::Void UpgradeChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(UpgradeTypeField->SelectedItem != "" && UpgradePosXField->Text != "" && UpgradePosYField->Text != ""
					 && UpgradeSizeXField->Text != "" && UpgradeSizeYField->Text != "" && _envData)
				 {
					 auto curUpgrade = _envData->_upgrades.Get(UpgradeSelectField->SelectedIndex);
					 ::Upgrade::Type::E changedUpgradeType;
					 switch(UpgradeTypeField->SelectedIndex)
					 {
					 case 0:
						 changedUpgradeType = ::Upgrade::Type::WALL_JUMP;
						 break;
					 case 1:
						 changedUpgradeType = ::Upgrade::Type::DOUBLE_JUMP;
						 break;
					 }
					 ::Environment::upgrade_desc_t changedUpgrade = std::make_pair(changedUpgradeType,
						 ::Object::Core(::Object::Type::Upgrade,
							glm::vec3((float)Convert::ToDouble(UpgradePosXField->Text), (float)Convert::ToDouble(UpgradePosYField->Text), curUpgrade.second._pos.z),
							glm::vec3((float)Convert::ToDouble(UpgradeSizeXField->Text), (float)Convert::ToDouble(UpgradeSizeYField->Text), curUpgrade.second._size.z)));
					 _envData->_upgrades.Update(changedUpgrade, UpgradeSelectField->SelectedIndex);
				 }
			 }
	private: System::Void EntranceChanged(System::Object^  sender, System::EventArgs^  e) {
				if(EntrancePosXField->Text != "" && EntrancePosYField->Text != "" && _envData)
				{
					auto curEntrance = _envData->_entrances.Get(EntranceSelectField->SelectedIndex);
					::Environment::entrance_desc_t changedEntrance = ::Environment::entrance_desc_t(
						(float)Convert::ToDouble(EntrancePosXField->Text), (float)Convert::ToDouble(EntrancePosYField->Text), curEntrance.z);
					_envData->_entrances.Update(changedEntrance, EntranceSelectField->SelectedIndex);
				}
			 }
	private: System::Void ExitChanged(System::Object^  sender, System::EventArgs^  e) {
				 if(sender == ExitEndpointEnvField)
				 {
					 ExitEndpointEntranceIDField->Text = "";
					 ExitEndpointEntranceIDField->Items->Clear();
					 ::Environment endpointEnv(::GetEnvName(ExitEndpointEnvField->SelectedIndex), 0);
					 for(int i=0; i<endpointEnv._entrances.Size(); ++i)
						 ExitEndpointEntranceIDField->Items->Add(i.ToString());
				 }

				 if(ExitEndpointEnvField->Text != "" && ExitEndpointEntranceIDField->Text != "" && ExitPosXField->Text != "" && ExitPosYField->Text != "" &&
					 ExitSizeXField->Text != "" && ExitSizeYField->Text != "" && _envData)
				 {
					 auto curExit = _envData->_exits.Get(ExitSelectField->SelectedIndex);
					 ::Environment::exit_desc_t changedExit;
					 changedExit._envId = ExitEndpointEnvField->SelectedIndex;
					 changedExit._entranceId = ExitEndpointEntranceIDField->SelectedIndex;
					 changedExit._core = ::Object::Core(::Object::Type::Exit,
						 glm::vec3((float)Convert::ToDouble(ExitPosXField->Text), (float)Convert::ToDouble(ExitPosYField->Text), curExit._core._pos.z),
						 glm::vec3((float)Convert::ToDouble(ExitSizeXField->Text), (float)Convert::ToDouble(ExitSizeYField->Text), curExit._core._size.z));
					 _envData->_exits.Update(changedExit, ExitSelectField->SelectedIndex);
				 }
			 }
	private: System::Void AddObj(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_architecture.Add();
					 ObjSelectField->Items->Add("Object " + (_envData->_architecture.Size()-1).ToString());
				 }
			 }
	private: System::Void AddEnemy(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_enemies.Add();
					 EnemySelectField->Items->Add("Enemy " + (_envData->_enemies.Size()-1).ToString());
				 }
			 }
	private: System::Void AddUpgrade(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_upgrades.Add();
					 UpgradeSelectField->Items->Add("Upgrade " + (_envData->_upgrades.Size()-1).ToString());
				 }
			 }
	private: System::Void AddEntrance(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_entrances.Add();
					 EntranceSelectField->Items->Add("Entrance " + (_envData->_entrances.Size()-1).ToString());
				 }
			 }
	private: System::Void AddExit(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_exits.Add();
					 ExitSelectField->Items->Add("Exit " + (_envData->_exits.Size()-1).ToString());
				 }
			 }
	private: System::Void RemoveObj(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_architecture.Remove(ObjSelectField->SelectedIndex);
					 ObjSelectField->Items->RemoveAt(ObjSelectField->SelectedIndex);
					 ObjTypeField->Text = "";
					 ObjPosXField->Text = "";
					 ObjPosYField->Text = "";
					 ObjSizeXField->Text = "";
					 ObjSizeYField->Text = "";
				 }
			 }
	private: System::Void RemoveEnemy(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_enemies.Remove(EnemySelectField->SelectedIndex);
					 EnemySelectField->Items->RemoveAt(EnemySelectField->SelectedIndex);
					 EnemyTypeField->Text = "";
					 EnemyPosXField->Text = "";
					 EnemyPosYField->Text = "";
				 }
			 }
	private: System::Void RemoveUpgrade(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_upgrades.Remove(UpgradeSelectField->SelectedIndex);
					 UpgradeSelectField->Items->RemoveAt(UpgradeSelectField->SelectedIndex);
					 UpgradeTypeField->Text = "";
					 UpgradePosXField->Text = "";
					 UpgradePosYField->Text = "";
					 UpgradeSizeXField->Text = "";
					 UpgradeSizeYField->Text = "";
				 }
			 }
	private: System::Void RemoveEntrance(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_entrances.Remove(EntranceSelectField->SelectedIndex);
					 EntranceSelectField->Items->RemoveAt(EntranceSelectField->SelectedIndex);
					 EntrancePosXField->Text = "";
					 EntrancePosYField->Text = "";
				 }
			 }
	private: System::Void RemoveExit(System::Object^  sender, System::EventArgs^  e) {
				 if(_envData)
				 {
					 _envData->_exits.Remove(ExitSelectField->SelectedIndex);
					 ExitSelectField->Items->RemoveAt(ExitSelectField->SelectedIndex);
					 ExitEndpointEnvField->Text = "";
					 ExitEndpointEntranceIDField->Text = "";
					 ExitPosXField->Text = "";
					 ExitPosYField->Text = "";
					 ExitSizeXField->Text = "";
					 ExitSizeYField->Text = "";
				 }
			 }
};
}
