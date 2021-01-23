/*
 * VTFEdit
 * Copyright (C) 2005-2010 Neil Jedrzejewski & Ryan Gregg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#pragma once

#include "stdafx.h"
#include "VTFOptions.h"
#include "VMTFileUtility.h"
#include "VTFFileUtility.h"
#include "IL/il.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace VTFEdit
{
	public ref class CBatchConvert : public System::Windows::Forms::Form
	{
	private:
		CVTFOptions^ Options;

	public: 
		CBatchConvert(CVTFOptions^ Options)
		{
			this->Options = Options;

			this->InitializeComponent();
		}
        
	protected: 
		private: System::Windows::Forms::Button^ btnOptions;
	private: System::Windows::Forms::GroupBox^  grpProgress;
	private: System::Windows::Forms::ProgressBar^  barProgress;
	private: System::Windows::Forms::Button^  btnClose;
	private: System::Windows::Forms::Button^  btnConvert;
	private: System::Windows::Forms::GroupBox^  grpOptions;
	private: System::Windows::Forms::CheckBox^  chkCreateVMTFiles;
	private: System::Windows::Forms::Button^  btnOutputFolderBrowse;
	private: System::Windows::Forms::TextBox^  txtOutputFolder;
	private: System::Windows::Forms::Label^  lblOutputFolder;
	private: System::Windows::Forms::Label^  lblWADFile;
	private: System::Windows::Forms::GroupBox^  grpLog;
	private: System::Windows::Forms::RichTextBox^  txtLog;
	private: System::Windows::Forms::Button^  btnInputFolderBrowse;
	private: System::Windows::Forms::TextBox^  txtInputFolder;
	private: System::Windows::Forms::FolderBrowserDialog^  dlgOpenFolder;
	private: System::Windows::Forms::CheckBox^  chkRecursive;
	private: System::Windows::Forms::ToolTip^  tipMain;
	private: System::Windows::Forms::TextBox^  txtToVTFFilter;
	private: System::Windows::Forms::RadioButton^  radToVTF;
	private: System::Windows::Forms::ComboBox^  cboFromVTFFormat;
	private: System::Windows::Forms::RadioButton^  radFromVTF;
	private: System::Windows::Forms::TextBox^  txtFromVTFFilter;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(CBatchConvert::typeid);
			this->btnOptions = gcnew System::Windows::Forms::Button();
			this->grpProgress = gcnew System::Windows::Forms::GroupBox();
			this->barProgress = gcnew System::Windows::Forms::ProgressBar();
			this->btnClose = gcnew System::Windows::Forms::Button();
			this->btnConvert = gcnew System::Windows::Forms::Button();
			this->grpOptions = gcnew System::Windows::Forms::GroupBox();
			this->cboFromVTFFormat = gcnew System::Windows::Forms::ComboBox();
			this->radFromVTF = gcnew System::Windows::Forms::RadioButton();
			this->txtFromVTFFilter = gcnew System::Windows::Forms::TextBox();
			this->radToVTF = gcnew System::Windows::Forms::RadioButton();
			this->txtToVTFFilter = gcnew System::Windows::Forms::TextBox();
			this->chkRecursive = gcnew System::Windows::Forms::CheckBox();
			this->chkCreateVMTFiles = gcnew System::Windows::Forms::CheckBox();
			this->btnOutputFolderBrowse = gcnew System::Windows::Forms::Button();
			this->txtOutputFolder = gcnew System::Windows::Forms::TextBox();
			this->lblOutputFolder = gcnew System::Windows::Forms::Label();
			this->btnInputFolderBrowse = gcnew System::Windows::Forms::Button();
			this->txtInputFolder = gcnew System::Windows::Forms::TextBox();
			this->lblWADFile = gcnew System::Windows::Forms::Label();
			this->grpLog = gcnew System::Windows::Forms::GroupBox();
			this->txtLog = gcnew System::Windows::Forms::RichTextBox();
			this->dlgOpenFolder = gcnew System::Windows::Forms::FolderBrowserDialog();
			this->tipMain = gcnew System::Windows::Forms::ToolTip(this->components);
			this->grpProgress->SuspendLayout();
			this->grpOptions->SuspendLayout();
			this->grpLog->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnOptions
			// 
			this->btnOptions->Anchor = (System::Windows::Forms::AnchorStyles)(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left);
			this->btnOptions->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnOptions->Location = System::Drawing::Point(8, 344);
			this->btnOptions->Name = "btnOptions";
			this->btnOptions->Size = System::Drawing::Size(80, 23);
			this->btnOptions->TabIndex = 5;
			this->btnOptions->Text = "&Options";
			this->btnOptions->Click += gcnew System::EventHandler(this, &CBatchConvert::btnOptions_Click);
			// 
			// grpProgress
			// 
			this->grpProgress->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpProgress->Controls->Add(this->barProgress);
			this->grpProgress->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpProgress->Location = System::Drawing::Point(8, 160);
			this->grpProgress->Name = "grpProgress";
			this->grpProgress->Size = System::Drawing::Size(360, 48);
			this->grpProgress->TabIndex = 3;
			this->grpProgress->TabStop = false;
			this->grpProgress->Text = "Progress:";
			// 
			// barProgress
			// 
			this->barProgress->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->barProgress->Location = System::Drawing::Point(8, 16);
			this->barProgress->Name = "barProgress";
			this->barProgress->Size = System::Drawing::Size(344, 23);
			this->barProgress->TabIndex = 0;
			// 
			// btnClose
			// 
			this->btnClose->Anchor = (System::Windows::Forms::AnchorStyles)(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right);
			this->btnClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnClose->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnClose->Location = System::Drawing::Point(288, 344);
			this->btnClose->Name = "btnClose";
			this->btnClose->Size = System::Drawing::Size(80, 23);
			this->btnClose->TabIndex = 1;
			this->btnClose->Text = "&Close";
			this->btnClose->Click += gcnew System::EventHandler(this, &CBatchConvert::btnClose_Click);
			// 
			// btnConvert
			// 
			this->btnConvert->Anchor = (System::Windows::Forms::AnchorStyles)(System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right);
			this->btnConvert->Enabled = false;
			this->btnConvert->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnConvert->Location = System::Drawing::Point(200, 344);
			this->btnConvert->Name = "btnConvert";
			this->btnConvert->Size = System::Drawing::Size(80, 23);
			this->btnConvert->TabIndex = 0;
			this->btnConvert->Text = "Con&vert";
			this->btnConvert->Click += gcnew System::EventHandler(this, &CBatchConvert::btnConvert_Click);
			// 
			// grpOptions
			// 
			this->grpOptions->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpOptions->Controls->Add(this->cboFromVTFFormat);
			this->grpOptions->Controls->Add(this->radFromVTF);
			this->grpOptions->Controls->Add(this->txtFromVTFFilter);
			this->grpOptions->Controls->Add(this->radToVTF);
			this->grpOptions->Controls->Add(this->txtToVTFFilter);
			this->grpOptions->Controls->Add(this->chkRecursive);
			this->grpOptions->Controls->Add(this->chkCreateVMTFiles);
			this->grpOptions->Controls->Add(this->btnOutputFolderBrowse);
			this->grpOptions->Controls->Add(this->txtOutputFolder);
			this->grpOptions->Controls->Add(this->lblOutputFolder);
			this->grpOptions->Controls->Add(this->btnInputFolderBrowse);
			this->grpOptions->Controls->Add(this->txtInputFolder);
			this->grpOptions->Controls->Add(this->lblWADFile);
			this->grpOptions->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpOptions->Location = System::Drawing::Point(8, 8);
			this->grpOptions->Name = "grpOptions";
			this->grpOptions->Size = System::Drawing::Size(360, 144);
			this->grpOptions->TabIndex = 2;
			this->grpOptions->TabStop = false;
			this->grpOptions->Text = "Options:";
			// 
			// cboFromVTFFormat
			// 
			this->cboFromVTFFormat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboFromVTFFormat->Enabled = false;
			array<System::Object^>^ __mcTemp__1 = gcnew array<System::Object^>(4);
			__mcTemp__1[0] = "bmp";
			__mcTemp__1[1] = "jpg";
			__mcTemp__1[2] = "png";
			__mcTemp__1[3] = "tga";
			this->cboFromVTFFormat->Items->AddRange(__mcTemp__1);
			this->cboFromVTFFormat->Location = System::Drawing::Point(48, 88);
			this->cboFromVTFFormat->Name = "cboFromVTFFormat";
			this->cboFromVTFFormat->Size = System::Drawing::Size(48, 21);
			this->cboFromVTFFormat->TabIndex = 9;
			// 
			// radFromVTF
			// 
			this->radFromVTF->Location = System::Drawing::Point(8, 88);
			this->radFromVTF->Name = "radFromVTF";
			this->radFromVTF->Size = System::Drawing::Size(40, 24);
			this->radFromVTF->TabIndex = 8;
			this->radFromVTF->Text = "To";
			this->radFromVTF->CheckedChanged += gcnew System::EventHandler(this, &CBatchConvert::radToFormat_CheckedChanged);
			// 
			// txtFromVTFFilter
			// 
			this->txtFromVTFFilter->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->txtFromVTFFilter->Location = System::Drawing::Point(104, 88);
			this->txtFromVTFFilter->Name = "txtFromVTFFilter";
			this->txtFromVTFFilter->ReadOnly = true;
			this->txtFromVTFFilter->Size = System::Drawing::Size(216, 20);
			this->txtFromVTFFilter->TabIndex = 10;
			this->txtFromVTFFilter->Text = "*.vtf";
			this->tipMain->SetToolTip(this->txtFromVTFFilter, "Wildcard filter.  Examples include *.* or *.vtf.");
			// 
			// radToVTF
			// 
			this->radToVTF->Checked = true;
			this->radToVTF->Location = System::Drawing::Point(8, 64);
			this->radToVTF->Name = "radToVTF";
			this->radToVTF->Size = System::Drawing::Size(80, 24);
			this->radToVTF->TabIndex = 6;
			this->radToVTF->TabStop = true;
			this->radToVTF->Text = "To VTF";
			this->radToVTF->CheckedChanged += gcnew System::EventHandler(this, &CBatchConvert::radToFormat_CheckedChanged);
			// 
			// txtToVTFFilter
			// 
			this->txtToVTFFilter->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->txtToVTFFilter->Location = System::Drawing::Point(104, 64);
			this->txtToVTFFilter->Name = "txtToVTFFilter";
			this->txtToVTFFilter->Size = System::Drawing::Size(216, 20);
			this->txtToVTFFilter->TabIndex = 7;
			this->txtToVTFFilter->Text = "*.tga";
			this->tipMain->SetToolTip(this->txtToVTFFilter, "Wildcard filter.  Examples include *.* or *.tga or *.bmp;*.tga.");
			// 
			// chkRecursive
			// 
			this->chkRecursive->Checked = true;
			this->chkRecursive->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkRecursive->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkRecursive->Location = System::Drawing::Point(104, 112);
			this->chkRecursive->Name = "chkRecursive";
			this->chkRecursive->Size = System::Drawing::Size(96, 24);
			this->chkRecursive->TabIndex = 11;
			this->chkRecursive->Text = "&Recursive";
			this->tipMain->SetToolTip(this->chkRecursive, "Include subdirectories.");
			// 
			// chkCreateVMTFiles
			// 
			this->chkCreateVMTFiles->Checked = true;
			this->chkCreateVMTFiles->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkCreateVMTFiles->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->chkCreateVMTFiles->Location = System::Drawing::Point(208, 112);
			this->chkCreateVMTFiles->Name = "chkCreateVMTFiles";
			this->chkCreateVMTFiles->Size = System::Drawing::Size(112, 24);
			this->chkCreateVMTFiles->TabIndex = 12;
			this->chkCreateVMTFiles->Text = "Create &VMT Files";
			this->tipMain->SetToolTip(this->chkCreateVMTFiles, "Generate .vmt files for .vtf files. Ouput folder should be a material folder.");
			// 
			// btnOutputFolderBrowse
			// 
			this->btnOutputFolderBrowse->Anchor = (System::Windows::Forms::AnchorStyles)(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right);
			this->btnOutputFolderBrowse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnOutputFolderBrowse->Location = System::Drawing::Point(328, 40);
			this->btnOutputFolderBrowse->Name = "btnOutputFolderBrowse";
			this->btnOutputFolderBrowse->Size = System::Drawing::Size(20, 20);
			this->btnOutputFolderBrowse->TabIndex = 5;
			this->btnOutputFolderBrowse->Text = "...";
			this->btnOutputFolderBrowse->Click += gcnew System::EventHandler(this, &CBatchConvert::btnOutputFolderBrowse_Click);
			// 
			// txtOutputFolder
			// 
			this->txtOutputFolder->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->txtOutputFolder->Location = System::Drawing::Point(104, 40);
			this->txtOutputFolder->Name = "txtOutputFolder";
			this->txtOutputFolder->ReadOnly = false;
			this->txtOutputFolder->Size = System::Drawing::Size(216, 20);
			this->txtOutputFolder->TabIndex = 4;
			this->txtOutputFolder->Text = "";
			this->tipMain->SetToolTip(this->txtOutputFolder, "Destination image folder.");
			// 
			// lblOutputFolder
			// 
			this->lblOutputFolder->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblOutputFolder->Location = System::Drawing::Point(8, 40);
			this->lblOutputFolder->Name = "lblOutputFolder";
			this->lblOutputFolder->Size = System::Drawing::Size(80, 23);
			this->lblOutputFolder->TabIndex = 3;
			this->lblOutputFolder->Text = "Output Folder:";
			// 
			// btnInputFolderBrowse
			// 
			this->btnInputFolderBrowse->Anchor = (System::Windows::Forms::AnchorStyles)(System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right);
			this->btnInputFolderBrowse->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnInputFolderBrowse->Location = System::Drawing::Point(328, 16);
			this->btnInputFolderBrowse->Name = "btnInputFolderBrowse";
			this->btnInputFolderBrowse->Size = System::Drawing::Size(20, 20);
			this->btnInputFolderBrowse->TabIndex = 2;
			this->btnInputFolderBrowse->Text = "...";
			this->btnInputFolderBrowse->Click += gcnew System::EventHandler(this, &CBatchConvert::btnInputFolderBrowse_Click);
			// 
			// txtInputFolder
			// 
			this->txtInputFolder->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->txtInputFolder->Location = System::Drawing::Point(104, 16);
			this->txtInputFolder->Name = "txtInputFolder";
			this->txtInputFolder->ReadOnly = false;
			this->txtInputFolder->Size = System::Drawing::Size(216, 20);
			this->txtInputFolder->TabIndex = 1;
			this->txtInputFolder->Text = "";
			this->tipMain->SetToolTip(this->txtInputFolder, "Source image folder.");
			this->txtInputFolder->TextChanged += gcnew System::EventHandler(this, &CBatchConvert::txtInputFolder_TextChanged);
			// 
			// lblWADFile
			// 
			this->lblWADFile->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->lblWADFile->Location = System::Drawing::Point(8, 16);
			this->lblWADFile->Name = "lblWADFile";
			this->lblWADFile->Size = System::Drawing::Size(80, 23);
			this->lblWADFile->TabIndex = 0;
			this->lblWADFile->Text = "Input Folder:";
			// 
			// grpLog
			// 
			this->grpLog->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpLog->Controls->Add(this->txtLog);
			this->grpLog->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpLog->Location = System::Drawing::Point(8, 216);
			this->grpLog->Name = "grpLog";
			this->grpLog->Size = System::Drawing::Size(360, 120);
			this->grpLog->TabIndex = 4;
			this->grpLog->TabStop = false;
			this->grpLog->Text = "Log:";
			// 
			// txtLog
			// 
			this->txtLog->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right);
			this->txtLog->DetectUrls = false;
			this->txtLog->Location = System::Drawing::Point(8, 16);
			this->txtLog->Name = "txtLog";
			this->txtLog->ReadOnly = true;
			this->txtLog->Size = System::Drawing::Size(344, 96);
			this->txtLog->TabIndex = 0;
			this->txtLog->Text = "";
			// 
			// dlgOpenFolder
			// 
			this->dlgOpenFolder->Description = "Select a folder:";
			// 
			// tipMain
			// 
			this->tipMain->AutoPopDelay = 10000;
			this->tipMain->InitialDelay = 500;
			this->tipMain->ReshowDelay = 100;
			// 
			// CBatchConvert
			// 
			this->AcceptButton = this->btnConvert;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->CancelButton = this->btnClose;
			this->ClientSize = System::Drawing::Size(376, 376);
			this->Controls->Add(this->btnOptions);
			this->Controls->Add(this->grpProgress);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->btnConvert);
			this->Controls->Add(this->grpOptions);
			this->Controls->Add(this->grpLog);
			this->Icon = (safe_cast<System::Drawing::Icon^>(resources->GetObject("$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = "CBatchConvert";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = "Batch Convert";
			this->Load += gcnew System::EventHandler(this, &CBatchConvert::CBatchConvert_Load);
			this->grpProgress->ResumeLayout(false);
			this->grpOptions->ResumeLayout(false);
			this->grpLog->ResumeLayout(false);
			this->ResumeLayout(false);
		}

		public: property System::String^ InputFolder
		{
			System::String^ get() { return this->txtInputFolder->Text; }
			void set(System::String^ sInputFolder)
			{
				if ( System::IO::Directory::Exists( sInputFolder ) )
				{
					this->txtInputFolder->Text = sInputFolder;
				}
			}
		}

		public: property System::String^ OutputFolder
		{
			System::String^ get() { return this->txtOutputFolder->Text; }
			void set(System::String^ sOutputFolder )
			{
				if ( System::IO::Directory::Exists( sOutputFolder ) )
				{
					this->txtOutputFolder->Text = sOutputFolder;
				}
			}
		}

		property bool ToVTF
		{
			bool get() { return this->radToVTF->Checked; }
			void set(bool bToVTF)
			{
				this->radToVTF->Checked = bToVTF;
			}
		}

		property System::String^ ToVTFFilter
		{
			System::String^ get() { return this->txtToVTFFilter->Text; }
			void set(System::String^ sFilter) { this->txtToVTFFilter->Text = sFilter; }
		}

		property System::String^ FromVTFFormat
		{
			System::String^ get() { return this->cboFromVTFFormat->Text; }
			void set(System::String^ sFormat)
			{
				this->cboFromVTFFormat->Text = sFormat;
				if(this->cboFromVTFFormat->SelectedIndex == -1)
				{
					this->cboFromVTFFormat->SelectedIndex = 3;
				}
			}
		}

		property System::String^ FromVTFFilter
		{
			System::String^ get() { return this->txtFromVTFFilter->Text; }
			void set(System::String^ sFilter) { this->txtFromVTFFilter->Text = sFilter; }
		}

		property bool Recurse
		{
			bool get() { return this->chkRecursive->Checked == true; }
			void set(bool bRecurse) { this->chkRecursive->Checked = bRecurse; }
		}

		property bool CreateVMTFiles
		{
			bool get() { return this->chkCreateVMTFiles->Checked == true; }
			void set(bool bCreateVMTFiles) { this->chkCreateVMTFiles->Checked = bCreateVMTFiles; }
		}

		private: System::Void CBatchConvert_Load(System::Object^  sender, System::EventArgs^  e)
		{
			if(this->cboFromVTFFormat->SelectedIndex == -1)
			{
				this->cboFromVTFFormat->SelectedIndex = 3;
			}
		}

		private: System::Void btnInputFolderBrowse_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->dlgOpenFolder->SelectedPath = this->txtInputFolder->Text;
			if(this->dlgOpenFolder->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->txtInputFolder->Text = this->dlgOpenFolder->SelectedPath;
			}
		}

		private: System::Void btnOutputFolderBrowse_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->dlgOpenFolder->SelectedPath = this->txtOutputFolder->Text;
			if(this->dlgOpenFolder->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->txtOutputFolder->Text = this->dlgOpenFolder->SelectedPath;
			}
		}

		private: System::Void txtInputFolder_TextChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->btnConvert->Enabled = System::IO::Directory::Exists(this->txtInputFolder->Text);
		}

		private: System::Void radToFormat_CheckedChanged(System::Object^  sender, System::EventArgs^  e)
		{
			this->txtToVTFFilter->ReadOnly = !this->radToVTF->Checked;
			this->cboFromVTFFormat->Enabled = this->radFromVTF->Checked;
			this->txtFromVTFFilter->ReadOnly = !this->radFromVTF->Checked;
		}

		private: int CountFiles(System::String^ sInputFolder, System::String^ sFilter, bool bRecursive)
		{
			int count = 0;

			System::IO::DirectoryInfo^ Folder = gcnew System::IO::DirectoryInfo(sInputFolder);

			if (bRecursive)
			{
				auto Folders = Folder->GetDirectories();

				for(int i = 0; i < Folders->Length; i++)
				{
					count += this->CountFiles(Folders[i]->FullName, sFilter, bRecursive);
				}
			}

			auto Filters = sFilter->Split(L';');

			for(int i = 0; i < Filters->Length; i++)
			{
				auto Files = Folder->GetFiles(Filters[i]);
				count += Files->Length;
			}

			return count;
		}

		private: System::Void ConvertFolder(System::String^ sInputFolder, System::String^ sOutputFolder, System::String^ sFilter, bool bRecursive, SVTFCreateOptions &VTFCreateOptions)
		{
			VTFLib::CVTFFile VTFFile;

			System::IO::DirectoryInfo^ Folder = gcnew System::IO::DirectoryInfo(sInputFolder);

			this->Log(String::Concat("Entering ", sInputFolder, "..."), System::Drawing::Color::Green);

			if (bRecursive)
			{
				auto Folders = Folder->GetDirectories();

				for(int i = 0; i < Folders->Length; i++)
				{
					this->ConvertFolder(String::Concat(sInputFolder, "\\", Folders[i]->Name), String::Concat(sOutputFolder, "\\", Folders[i]->Name), sFilter, bRecursive, VTFCreateOptions);
				}
			}

			auto Filters = sFilter->Split(L';');

			for(int i = 0; i < Filters->Length; i++)
			{
				auto Files = Folder->GetFiles(Filters[i]);

				for(int j = 0; j < Files->Length; j++)
				{
					bool bIsVTF = String::Compare(Files[j]->Extension, ".vtf", true) == 0;

					this->Log(String::Concat("Processing ", Files[j]->Name, "..."), System::Drawing::Color::Gray);

					if(this->radToVTF->Checked && !bIsVTF) // Convert to .vtf.
					{
						String^ sVTFName = Files[j]->Name->Substring(0, Files[j]->Name->Length - Files[j]->Extension->Length);
						String^ sVTFFile = String::Concat(sOutputFolder, "\\", sVTFName, ".vtf");
						String^ sVMTFile = String::Concat(sOutputFolder, "\\", sVTFName, ".vmt");

						char *cFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Files[j]->FullName)).ToPointer();

						// Load the image and convert it to RGBA.
						if(ilLoadImage(cFile))
						{
							bool bHasAlpha = ilGetInteger(IL_IMAGE_FORMAT) == IL_RGBA || ilGetInteger(IL_IMAGE_FORMAT) == IL_BGRA || ilGetInteger(IL_IMAGE_FORMAT) == IL_LUMINANCE_ALPHA;

							if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
							{
								VTFCreateOptions.ImageFormat = bHasAlpha ? Options->AlphaFormat : Options->NormalFormat;

								if(VTFFile.Create((vlUInt)ilGetInteger(IL_IMAGE_WIDTH), (vlUInt)ilGetInteger(IL_IMAGE_HEIGHT), ilGetData(), VTFCreateOptions) != vlFalse && CVTFFileUtility::CreateResources(Options, &VTFFile))
								{
									if(!System::IO::Directory::Exists(sOutputFolder))
									{
										try
										{
											System::IO::Directory::CreateDirectory(sOutputFolder);
										}
										catch(Exception^)
										{

										}
									}

									char *cVTFFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sVTFFile)).ToPointer();
									if(VTFFile.Save(cVTFFile))
									{
										this->Log(String::Concat("Wrote ", sVTFFile, "."), System::Drawing::Color::Green);
										if(this->chkCreateVMTFiles->Checked && CVMTFileUtility::CreateDefaultMaterial(sVTFFile, "LightmappedGeneric", bHasAlpha))
										{
											this->Log(String::Concat("Wrote ", sVMTFile, "."), System::Drawing::Color::Green);
										}
									}
									else
									{
										this->Log(String::Concat("Error writing ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
									}
									System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cVTFFile);
								}
								else
								{
									this->Log(String::Concat("Error creating ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
								}
							}
							else
							{
								this->Log(String::Concat("Error converting ", Files[j]->Name, "."), System::Drawing::Color::Red);
							}
						}
						else
						{
							this->Log(String::Concat("Error loading ", Files[j]->Name, ". ", ilGetError()), System::Drawing::Color::Red);
						}

						System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cFile);

						this->Log(String::Concat(Files[j]->Name, " processed."), System::Drawing::Color::Gray);
					}
					else if(bIsVTF)  // Convert from .vtf.
					{
						String^ sOtherName = Files[j]->Name->Substring(0, Files[j]->Name->Length - Files[j]->Extension->Length);
						String^ sOtherFile = String::Concat(sOutputFolder, "\\", sOtherName, ".", this->cboFromVTFFormat->Text);

						char *cFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(Files[j]->FullName)).ToPointer();

						if(VTFFile.Load(cFile))
						{
							vlUInt uiWidth = VTFFile.GetWidth(), uiHeight = VTFFile.GetHeight();
				
							vlByte *lpImageData = new vlByte[VTFFile.ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)];

							if(VTFFile.ConvertToRGBA8888(VTFFile.GetData(0, 0, 0, 0), lpImageData, uiWidth, uiHeight, VTFFile.GetFormat()))
							{
								// DevIL likes image data upside down...
								VTFFile.FlipImage(lpImageData, uiWidth, uiHeight);

								if(ilTexImage(uiWidth, uiHeight, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, lpImageData))
								{
									if(!System::IO::Directory::Exists(sOutputFolder))
									{
										try
										{
											System::IO::Directory::CreateDirectory(sOutputFolder);
										}
										catch(Exception^)
										{

										}
									}

									char *cOtherFile = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sOtherFile)).ToPointer();
									if(ilSaveImage(cOtherFile))
									{
										this->Log(String::Concat("Wrote ", sOtherFile, "."), System::Drawing::Color::Green);
									}
									else
									{
										this->Log(String::Concat("Error writing ", Files[j]->Name, "."), System::Drawing::Color::Red);
									}
									System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cOtherFile);
								}
								else
								{
									this->Log(String::Concat("Error creating ", Files[j]->Name, "."), System::Drawing::Color::Red);
								}
							}
							else
							{
								this->Log(String::Concat("Error converting ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
							}

							delete []lpImageData;
						}
						else
						{
							this->Log(String::Concat("Error loading ", Files[j]->Name, ".", (gcnew String(vlGetLastError()))->Replace("\n", " ")), System::Drawing::Color::Red);
						}

						System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cFile);

						this->Log(String::Concat(Files[j]->Name, " processed."), System::Drawing::Color::Gray);
					}
					else
					{
						this->Log(String::Concat(Files[j]->Name, " skipped."), System::Drawing::Color::Gray);
					}

					this->barProgress->Value++;
					this->barProgress->Refresh();
				}
			}

			this->Log(String::Concat("Exiting ", sInputFolder, "."), System::Drawing::Color::Green);
		}

		private: System::Void btnConvert_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->Cursor = System::Windows::Forms::Cursors::WaitCursor;

			String^ sFilter = this->radToVTF->Checked ? this->txtToVTFFilter->Text : this->txtFromVTFFilter->Text;
			if(sFilter->Length == 0)
			{
				sFilter = "*";
			}

			this->barProgress->Value = 0;
			this->barProgress->Maximum = this->CountFiles(this->txtInputFolder->Text, sFilter, this->chkRecursive->Checked);
			this->txtLog->Clear();

			SVTFCreateOptions VTFCreateOptions = CVTFFileUtility::GetCreateOptions(this->Options);

			
			this->ConvertFolder(this->txtInputFolder->Text, this->txtOutputFolder->Text->Length == 0 ? this->txtInputFolder->Text : this->txtOutputFolder->Text, sFilter, this->chkRecursive->Checked, VTFCreateOptions);

			this->Cursor = System::Windows::Forms::Cursors::Default;
		}

		private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		}

		private: System::Void btnOptions_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->Options->ShowDialog();
		}

		private: void Log(String^ sString, System::Drawing::Color cColor)
		{
			this->txtLog->Focus();
			this->txtLog->SelectionStart = this->txtLog->TextLength;
			this->txtLog->SelectionColor = cColor;
			this->txtLog->AppendText(String::Concat(sString, "\n"));
			this->txtLog->Refresh();
		}
	};
}