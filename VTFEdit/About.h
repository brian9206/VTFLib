/*
 * VTFEdit
 * Copyright (C) 2005-2011 Neil Jedrzejewski & Ryan Gregg
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

#include "VTFLib.h"
#include "HLLib.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace VTFEdit
{
	public ref class CAbout : public System::Windows::Forms::Form
	{
	public:
		CAbout(void)
		{
			this->InitializeComponent();

			this->lblVTFLibVersion->Text = String::Concat("VTFLib Version: ", gcnew String(vlGetVersionString()));
		}

	protected:
	private: System::Windows::Forms::Button^ btnOK;
	private: System::Windows::Forms::GroupBox^  grpAbout;
	private: System::Windows::Forms::Label^  lblLines;
	private: System::Windows::Forms::Label^  lblLanguage;
	private: System::Windows::Forms::Label^  lblDate;
	private: System::Windows::Forms::Label^  lblAuthor;
	private: System::Windows::Forms::LinkLabel^  lnkNemsTools;
	private: System::Windows::Forms::PictureBox^  picIcon;
	private: System::Windows::Forms::LinkLabel^  lnkWunderboy;
	private: System::Windows::Forms::Label^  lblVTFLibVersion;
	private: System::Windows::Forms::Label^  lblVTFEditVersion;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(CAbout::typeid);
			this->btnOK = gcnew System::Windows::Forms::Button();
			this->grpAbout = gcnew System::Windows::Forms::GroupBox();
			this->lblVTFLibVersion = gcnew System::Windows::Forms::Label();
			this->lnkWunderboy = gcnew System::Windows::Forms::LinkLabel();
			this->lblLines = gcnew System::Windows::Forms::Label();
			this->lblLanguage = gcnew System::Windows::Forms::Label();
			this->lblDate = gcnew System::Windows::Forms::Label();
			this->lblAuthor = gcnew System::Windows::Forms::Label();
			this->lblVTFEditVersion = gcnew System::Windows::Forms::Label();
			this->lnkNemsTools = gcnew System::Windows::Forms::LinkLabel();
			this->picIcon = gcnew System::Windows::Forms::PictureBox();
			this->grpAbout->SuspendLayout();
			this->SuspendLayout();
			//
			// btnOK
			//
			this->btnOK->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnOK->Location = System::Drawing::Point(104, 200);
			this->btnOK->Name = "btnOK";
			this->btnOK->Size = System::Drawing::Size(80, 23);
			this->btnOK->TabIndex = 0;
			this->btnOK->Text = "&OK";
			this->btnOK->Click += gcnew System::EventHandler(this, &CAbout::btnOK_Click);
			//
			// grpAbout
			//
			this->grpAbout->Controls->Add(this->lblVTFLibVersion);
			this->grpAbout->Controls->Add(this->lnkWunderboy);
			this->grpAbout->Controls->Add(this->lblLines);
			this->grpAbout->Controls->Add(this->lblLanguage);
			this->grpAbout->Controls->Add(this->lblDate);
			this->grpAbout->Controls->Add(this->lblAuthor);
			this->grpAbout->Controls->Add(this->lblVTFEditVersion);
			this->grpAbout->Controls->Add(this->lnkNemsTools);
			this->grpAbout->Controls->Add(this->picIcon);
			this->grpAbout->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpAbout->Location = System::Drawing::Point(8, 8);
			this->grpAbout->Name = "grpAbout";
			this->grpAbout->Size = System::Drawing::Size(272, 184);
			this->grpAbout->TabIndex = 1;
			this->grpAbout->TabStop = false;
			//
			// lblVTFLibVersion
			//
			this->lblVTFLibVersion->Location = System::Drawing::Point(68, 40);
			this->lblVTFLibVersion->Name = "lblVTFLibVersion";
			this->lblVTFLibVersion->Size = System::Drawing::Size(136, 16);
			this->lblVTFLibVersion->TabIndex = 0;
			//
			// lnkWunderboy
			//
			this->lnkWunderboy->LinkColor = System::Drawing::Color::Black;
			this->lnkWunderboy->Location = System::Drawing::Point(16, 160);
			this->lnkWunderboy->Name = "lnkWunderboy";
			this->lnkWunderboy->Size = System::Drawing::Size(88, 16);
			this->lnkWunderboy->TabIndex = 6;
			this->lnkWunderboy->TabStop = true;
			this->lnkWunderboy->Text = "wunderboy.org";
			this->lnkWunderboy->VisitedLinkColor = System::Drawing::Color::Black;
			this->lnkWunderboy->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &CAbout::lnkWunderboy_LinkClicked);
			//
			// lblLines
			//
			this->lblLines->Location = System::Drawing::Point(68, 136);
			this->lblLines->Name = "lblLines";
			this->lblLines->Size = System::Drawing::Size(136, 16);
			this->lblLines->TabIndex = 5;
			this->lblLines->Text = "Lines: 9,003";
			//
			// lblLanguage
			//
			this->lblLanguage->Location = System::Drawing::Point(68, 120);
			this->lblLanguage->Name = "lblLanguage";
			this->lblLanguage->Size = System::Drawing::Size(136, 16);
			this->lblLanguage->TabIndex = 4;
			this->lblLanguage->Text = "Written In: C++";
			//
			// lblDate
			//
			this->lblDate->Location = System::Drawing::Point(68, 104);
			this->lblDate->Name = "lblDate";
			this->lblDate->Size = System::Drawing::Size(136, 16);
			this->lblDate->TabIndex = 3;
			this->lblDate->Text = "Date: " __DATE__;
			//
			// lblAuthor
			//
			this->lblAuthor->Location = System::Drawing::Point(68, 72);
			this->lblAuthor->Name = "lblAuthor";
			this->lblAuthor->Size = System::Drawing::Size(136, 32);
			this->lblAuthor->TabIndex = 2;
			this->lblAuthor->Text = "Author: Neil Jedrzejewski && Ryan Gregg";
			//
			// lblVTFEditVersion
			//
			this->lblVTFEditVersion->Location = System::Drawing::Point(68, 56);
			this->lblVTFEditVersion->Name = "lblVTFEditVersion";
			this->lblVTFEditVersion->Size = System::Drawing::Size(136, 16);
			this->lblVTFEditVersion->TabIndex = 1;
			this->lblVTFEditVersion->Text = "VTFEdit Version: " VL_VERSION_STRING;
			//
			// lnkNemsTools
			//
			this->lnkNemsTools->LinkColor = System::Drawing::Color::Black;
			this->lnkNemsTools->Location = System::Drawing::Point(176, 160);
			this->lnkNemsTools->Name = "lnkNemsTools";
			this->lnkNemsTools->Size = System::Drawing::Size(88, 16);
			this->lnkNemsTools->TabIndex = 7;
			this->lnkNemsTools->TabStop = true;
			this->lnkNemsTools->Text = "nemesis.twl.net";
			this->lnkNemsTools->VisitedLinkColor = System::Drawing::Color::Black;
			this->lnkNemsTools->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &CAbout::lnkNemsTools_LinkClicked);
			//
			// picIcon
			//
			this->picIcon->Image = (safe_cast<System::Drawing::Image^>(resources->GetObject("picIcon.Image")));
			this->picIcon->Location = System::Drawing::Point(8, 16);
			this->picIcon->Name = "picIcon";
			this->picIcon->Size = System::Drawing::Size(32, 32);
			this->picIcon->TabIndex = 0;
			this->picIcon->TabStop = false;
			//
			// CAbout
			//
			this->AcceptButton = this->btnOK;
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(288, 232);
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->grpAbout);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (safe_cast<System::Drawing::Icon^>(resources->GetObject("$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = "CAbout";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = "About VTFEdit";
			this->grpAbout->ResumeLayout(false);
			this->ResumeLayout(false);

		}

		private: System::Void lnkWunderboy_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e)
		{
			try
			{
				System::Diagnostics::Process::Start("http://www.wunderboy.org/");
			}
			catch(Exception^)
			{

			}
		}

		private: System::Void lnkNemsTools_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e)
		{
			try
			{
				System::Diagnostics::Process::Start("http://nemesis.thewavelength.net/");
			}
			catch(Exception^)
			{

			}
		}

		private: System::Void btnOK_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->Close();
		}
	};
}