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
#include "About.h"
#include "VTFOptions.h"
#include "VMTCreate.h"
#include "BatchConvert.h"
#include "WADConvert.h"
#include "DirectoryItemInfoManager.h"
#include "Utility.h"

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
	ref class CVTFEdit : public System::Windows::Forms::Form
	{
	private:
		String^ sFileName;

		bool bVMTFile;
		VTFLib::CVTFFile* VTFFile;

		bool bHDRReseting;
		float fImageScale;
		unsigned char *ucImageData;

		unsigned int uiMaximumRecentFiles;
		System::Collections::Generic::List<System::String^>^ RecentFiles;

		bool bFormRestoring;
		System::Drawing::Point FormSaveLocation;
		System::Drawing::Size FormSaveSize;
		FormWindowState FormSaveWindowState;
		int iFormSaveSidebarSplitPosition;

		CDirectoryItemInfoManager^ DirectoryItemInfoManager;
		CVTFOptions^ Options;
		CVMTCreate^ VMTCreate;
		CBatchConvert^ BatchConvert;
		CWADConvert^ WADConvert;
		CAbout^ About;

		HWND hWndNewViewer;

	public:
		CVTFEdit()
		{
			this->bHDRReseting = false;
			this->ucImageData = 0;

			this->uiMaximumRecentFiles = 8;
			this->RecentFiles = gcnew System::Collections::Generic::List<String^>();

			this->bFormRestoring = false;

			this->DirectoryItemInfoManager = gcnew CDirectoryItemInfoManager();
			this->Options = gcnew CVTFOptions();
			this->VMTCreate = gcnew CVMTCreate();
			this->BatchConvert = gcnew CBatchConvert(this->Options);
			this->WADConvert = gcnew CWADConvert(this->Options);
			this->About = gcnew CAbout();

			this->hWndNewViewer = 0;

			this->InitializeComponent();

			this->treFileSystem->ImageList = this->DirectoryItemInfoManager->SmallImageList;
		}

	protected:
	private: System::Windows::Forms::TabPage^  tabResources;
	private: System::Windows::Forms::GroupBox^  grpResourceInfo;
	private: System::Windows::Forms::Label^  lblResourceCount;
	private: System::Windows::Forms::Label^  lblResourceCountLabel;
	private: System::Windows::Forms::GroupBox^  grpResources;
	private: System::Windows::Forms::TreeView^  treResources;
	private: System::Windows::Forms::ContextMenu^  mnuHDR;
	private: System::Windows::Forms::MenuItem^  btnHDRReset;
	private: System::Windows::Forms::StatusBarPanel^  pnlInfo1;
	private: System::Windows::Forms::StatusBarPanel^  pnlInfo2;
	private: System::Windows::Forms::Label^ lblHDRShift;
	private: System::Windows::Forms::TrackBar^  trkHDRShift;
	private: System::Windows::Forms::Label^  lblHDRGamma;
	private: System::Windows::Forms::TrackBar^  trkHDRGamma;
	private: System::Windows::Forms::MenuItem^  btnExportAll;
	private: System::Windows::Forms::TrackBar^  trkHDRKey;
	private: System::Windows::Forms::Label^  lblHDRKey;
	private: System::Windows::Forms::Label^  lblSlice;
	private: System::Windows::Forms::NumericUpDown^  numSlice;
	private: System::Windows::Forms::Label^  lblImageSlices;
	private: System::Windows::Forms::Label^  lblImageSlicesLabel;
	private: System::Windows::Forms::StatusBarPanel^  pnlFileName;
	private: System::Windows::Forms::MenuItem^  btnFileSystemSpace2;
	private: System::Windows::Forms::MenuItem^  btnFileSystemDelete;
	private: System::Windows::Forms::MenuItem^  btnNew;
	private: System::Windows::Forms::ContextMenu^  mnuVMTFile;
	private: System::Windows::Forms::MenuItem^  btnVMTFileUndo;
	private: System::Windows::Forms::MenuItem^  btnVMTFileSpace1;
	private: System::Windows::Forms::MenuItem^  btnVMTFileCut;
	private: System::Windows::Forms::MenuItem^  btnVMTFileCopy;
	private: System::Windows::Forms::MenuItem^  btnVMTFilePaste;
	private: System::Windows::Forms::MenuItem^  btnVMTFileDelete;
	private: System::Windows::Forms::MenuItem^  btnVMTFileSpace2;
	private: System::Windows::Forms::MenuItem^  btnVMTFileSelectAll;
	private: System::Windows::Forms::MenuItem^  btnConvertFolder;
	private: FastColoredTextBoxNS::FastColoredTextBox^  txtVMTFile;
	private: System::Windows::Forms::MenuItem^  btnOptionsSpace1;
	private: System::Windows::Forms::MenuItem^  btnAutoCreateVMTFile;
	private: System::Windows::Forms::MenuItem^  btnConvertWADFile;
	private: System::Windows::Forms::MenuItem^  btnFileSpace4;
	private: System::Windows::Forms::MenuItem^  btnCreateVMTFile;
	private: System::Windows::Forms::MenuItem^  btnToolsMenu;
	private: System::Windows::Forms::GroupBox^  grpFileInfo;
	private: System::Windows::Forms::Label^  lblFileSize;
	private: System::Windows::Forms::Label^  lblFileSizeLabel;
	private: System::Windows::Forms::Label^  lblFileVersion;
	private: System::Windows::Forms::Label^  lblFileVersionLabel;
	private: System::Windows::Forms::MenuItem^  btnFileSpace3;
	private: System::Windows::Forms::MenuItem^  btnVTFFileZoomIn;
	private: System::Windows::Forms::MenuItem^  btnVTFFileZoomOut;
	private: System::Windows::Forms::MenuItem^  btnVTFFileSpace1;
	private: System::Windows::Forms::MenuItem^  btnVTFFileZoomReset;
	private: System::Windows::Forms::MenuItem^  btnVTFFileSpace2;
	private: System::Windows::Forms::MenuItem^  btnVTFFileCopy;
	private: System::Windows::Forms::ContextMenu^  mnuVTFFile;
	private: System::Windows::Forms::PictureBox^  picVTFFileTL;
	private: System::Windows::Forms::PictureBox^  picVTFFileTR;
	private: System::Windows::Forms::PictureBox^  picVTFFileBL;
	private: System::Windows::Forms::PictureBox^  picVTFFileBR;
	private: System::Windows::Forms::MenuItem^  btnTile;
	private: System::Windows::Forms::MenuItem^  btnFileSystemAddGoto;
	private: System::Windows::Forms::MenuItem^  btnFileSystemSpace1;
	private: System::Windows::Forms::ContextMenu^  mnuGoto;
	private: System::Windows::Forms::MenuItem^  btnGotoRemove;
	private: System::Windows::Forms::MenuItem^  btnGotoClear;
	private: System::Windows::Forms::MenuItem^  btnOptionsMenu;
	private: System::Windows::Forms::MenuItem^  btnFileMapping;
	private: System::Windows::Forms::MenuItem^  btnVolatileAccess;
	private: System::Windows::Forms::ContextMenu^  mnuFileSystem;
	private: System::Windows::Forms::MenuItem^  btnFileSystemExpandAll;
	private: System::Windows::Forms::MenuItem^  btnFileSystemCollapseAll;
	private: System::Windows::Forms::MenuItem^  btnFileSystemOpen;
	private: System::Windows::Forms::MenuItem^  btnFileSystemShellExecute;
	private: System::Windows::Forms::MenuItem^  btnFileSystemExtract;
	private: System::Windows::Forms::FolderBrowserDialog^  dlgExtractDirectoryItem;
	private: System::Windows::Forms::MenuItem^  btnFileSystemMount;
	private: System::Windows::Forms::GroupBox^  grpGoto;
	private: System::Windows::Forms::ComboBox^  cboGoto;
	private: System::Windows::Forms::MenuItem^  btnMask;
	private: System::Windows::Forms::TabPage^  tabFileSystem;
	private: System::Windows::Forms::GroupBox^  grpFileSystem;
	private: System::Windows::Forms::TreeView^  treFileSystem;
	private: System::Windows::Forms::Splitter^  splSidebar;
	private: System::Windows::Forms::StatusBar^  barStatus;
	private: System::Windows::Forms::ToolBar^  barTool;
	private: System::Windows::Forms::ImageList^  imgTool;
	private: System::Windows::Forms::ToolBarButton^  btnToolImport;
	private: System::Windows::Forms::ToolBarButton^  btnToolOpen;
	private: System::Windows::Forms::ToolBarButton^  btnToolSave;
	private: System::Windows::Forms::ToolBarButton^  btnSeparator1;
	private: System::Windows::Forms::ToolBarButton^  btnToolCopy;
	private: System::Windows::Forms::ToolBarButton^  btnToolPaste;
	private: System::Windows::Forms::MenuItem^  btnPaste;
	private: System::Windows::Forms::NumericUpDown^  numImageStartFrame;
	private: System::Windows::Forms::NumericUpDown^  numImageBumpmapScale;
	private: System::Windows::Forms::MenuItem^  btnRecentFiles;
	private: System::Windows::Forms::OpenFileDialog^  dlgImportFile;
	private: System::Windows::Forms::MenuItem^  btnFileSpace1;
	private: System::Windows::Forms::MenuItem^  btnImport;
	private: System::Windows::Forms::MenuItem^  btnExport;
	private: System::Windows::Forms::SaveFileDialog^  dlgExportFile;
	private: System::Windows::Forms::MenuItem^  btnViewMenu;
	private: System::Windows::Forms::MenuItem^  btnChannelMenu;
	private: System::Windows::Forms::MenuItem^  btnChannelRGB;
	private: System::Windows::Forms::MenuItem^  btnChannelR;
	private: System::Windows::Forms::MenuItem^  btnChannelG;
	private: System::Windows::Forms::MenuItem^  btnChannelB;
	private: System::Windows::Forms::MenuItem^  btnChannelA;
	private: System::Windows::Forms::TabControl^  tabSidebar;
	private: System::Windows::Forms::TabPage^  tabImage;
	private: System::Windows::Forms::TabPage^  tabInfo;
	private: System::Windows::Forms::Label^  lblImageFrames;
	private: System::Windows::Forms::Label^  lblImageFramesLabel;
	private: System::Windows::Forms::Label^  lblImageFaces;
	private: System::Windows::Forms::Label^  lblImageFacesLabel;
	private: System::Windows::Forms::Label^  lblImageMipmaps;
	private: System::Windows::Forms::Label^  lblImageMipmapsLabel;
	private: System::Windows::Forms::Label^  lblImageStartFrameLabel;
	private: System::Windows::Forms::Label^  lblImageBumpmapScaleLabel;
	private: System::Windows::Forms::Label^  lblImageReflectivity;
	private: System::Windows::Forms::Label^  lblImageReflectivityLabel;
	private: System::Windows::Forms::MenuItem^  btnEditMenu;
	private: System::Windows::Forms::MenuItem^  btnCopy;
	private: System::Windows::Forms::Panel^  pnlMain;
	private: System::Windows::Forms::SaveFileDialog^  dlgSaveVTFFile;
	private: System::Windows::Forms::SaveFileDialog^  dlgSaveVMTFile;
	private: System::Windows::Forms::MenuItem^  btnFileSpace2;
	private: System::Windows::Forms::MenuItem^  btnSave;
	private: System::Windows::Forms::MenuItem^  btnSaveAs;
	private: System::Windows::Forms::MenuItem^  btnFileMenu;
	private: System::Windows::Forms::MenuItem^  btnHelpMenu;
	private: System::Windows::Forms::MenuItem^  btnAbout;
	private: System::Windows::Forms::GroupBox^  grpImageInfo;
	private: System::Windows::Forms::Label^  lblImageWidthLabel;
	private: System::Windows::Forms::Label^  lblImageWidth;
	private: System::Windows::Forms::Label^  lblImageHeight;
	private: System::Windows::Forms::Label^  lblImageHeightLabel;
	private: System::Windows::Forms::Label^  lblImageFormat;
	private: System::Windows::Forms::Label^  lblImageFormatLabel;
	private: System::Windows::Forms::GroupBox^  grpThumbnailInfo;
	private: System::Windows::Forms::Label^  lblThumbnailFormat;
	private: System::Windows::Forms::Label^  lblThumbnailFormatLabel;
	private: System::Windows::Forms::Label^  lblThumbnailHeight;
	private: System::Windows::Forms::Label^  lblThumbnailHeightLabel;
	private: System::Windows::Forms::Label^  lblThumbnailWidth;
	private: System::Windows::Forms::Label^  lblThumbnailWidthLabel;
	private: System::Windows::Forms::Button^  btnAnimate;
	private: System::Windows::Forms::Timer^  tmrAnimate;
	private: System::Windows::Forms::GroupBox^  grpImage;
	private: System::Windows::Forms::GroupBox^  grpFlags;
	private: System::Windows::Forms::CheckedListBox^  lstFlags;
	private: System::Windows::Forms::MainMenu^  mnuMain;
	private: System::Windows::Forms::MenuItem^  btnOpen;
	private: System::Windows::Forms::MenuItem^  btnExit;
	private: System::Windows::Forms::OpenFileDialog^  dlgOpenFile;
	private: System::Windows::Forms::Panel^  pnlSidebar;
	private: System::Windows::Forms::Label^  lblFrame;
	private: System::Windows::Forms::NumericUpDown^  numFrame;
	private: System::Windows::Forms::Label^  lblFace;
	private: System::Windows::Forms::NumericUpDown^  numFace;
	private: System::Windows::Forms::Label^  lblMipmap;
	private: System::Windows::Forms::NumericUpDown^  numMipmap;
	private: System::ComponentModel::IContainer^  components;
	private:

		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			System::Resources::ResourceManager^ resources = gcnew System::Resources::ResourceManager(CVTFEdit::typeid);
			this->mnuMain = gcnew System::Windows::Forms::MainMenu();
			this->btnFileMenu = gcnew System::Windows::Forms::MenuItem();
			this->btnNew = gcnew System::Windows::Forms::MenuItem();
			this->btnOpen = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSpace1 = gcnew System::Windows::Forms::MenuItem();
			this->btnSave = gcnew System::Windows::Forms::MenuItem();
			this->btnSaveAs = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSpace2 = gcnew System::Windows::Forms::MenuItem();
			this->btnImport = gcnew System::Windows::Forms::MenuItem();
			this->btnExport = gcnew System::Windows::Forms::MenuItem();
			this->btnExportAll = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSpace3 = gcnew System::Windows::Forms::MenuItem();
			this->btnRecentFiles = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSpace4 = gcnew System::Windows::Forms::MenuItem();
			this->btnExit = gcnew System::Windows::Forms::MenuItem();
			this->btnEditMenu = gcnew System::Windows::Forms::MenuItem();
			this->btnCopy = gcnew System::Windows::Forms::MenuItem();
			this->btnPaste = gcnew System::Windows::Forms::MenuItem();
			this->btnViewMenu = gcnew System::Windows::Forms::MenuItem();
			this->btnChannelMenu = gcnew System::Windows::Forms::MenuItem();
			this->btnChannelRGB = gcnew System::Windows::Forms::MenuItem();
			this->btnChannelR = gcnew System::Windows::Forms::MenuItem();
			this->btnChannelG = gcnew System::Windows::Forms::MenuItem();
			this->btnChannelB = gcnew System::Windows::Forms::MenuItem();
			this->btnChannelA = gcnew System::Windows::Forms::MenuItem();
			this->btnMask = gcnew System::Windows::Forms::MenuItem();
			this->btnTile = gcnew System::Windows::Forms::MenuItem();
			this->btnToolsMenu = gcnew System::Windows::Forms::MenuItem();
			this->btnCreateVMTFile = gcnew System::Windows::Forms::MenuItem();
			this->btnConvertFolder = gcnew System::Windows::Forms::MenuItem();
			this->btnConvertWADFile = gcnew System::Windows::Forms::MenuItem();
			this->btnOptionsMenu = gcnew System::Windows::Forms::MenuItem();
			this->btnAutoCreateVMTFile = gcnew System::Windows::Forms::MenuItem();
			this->btnOptionsSpace1 = gcnew System::Windows::Forms::MenuItem();
			this->btnFileMapping = gcnew System::Windows::Forms::MenuItem();
			this->btnVolatileAccess = gcnew System::Windows::Forms::MenuItem();
			this->btnHelpMenu = gcnew System::Windows::Forms::MenuItem();
			this->btnAbout = gcnew System::Windows::Forms::MenuItem();
			this->dlgOpenFile = gcnew System::Windows::Forms::OpenFileDialog();
			this->barStatus = gcnew System::Windows::Forms::StatusBar();
			this->pnlFileName = gcnew System::Windows::Forms::StatusBarPanel();
			this->pnlInfo1 = gcnew System::Windows::Forms::StatusBarPanel();
			this->pnlInfo2 = gcnew System::Windows::Forms::StatusBarPanel();
			this->pnlSidebar = gcnew System::Windows::Forms::Panel();
			this->tabSidebar = gcnew System::Windows::Forms::TabControl();
			this->tabFileSystem = gcnew System::Windows::Forms::TabPage();
			this->grpGoto = gcnew System::Windows::Forms::GroupBox();
			this->cboGoto = gcnew System::Windows::Forms::ComboBox();
			this->mnuGoto = gcnew System::Windows::Forms::ContextMenu();
			this->btnGotoRemove = gcnew System::Windows::Forms::MenuItem();
			this->btnGotoClear = gcnew System::Windows::Forms::MenuItem();
			this->grpFileSystem = gcnew System::Windows::Forms::GroupBox();
			this->treFileSystem = gcnew System::Windows::Forms::TreeView();
			this->mnuFileSystem = gcnew System::Windows::Forms::ContextMenu();
			this->btnFileSystemOpen = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemShellExecute = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemExtract = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemExpandAll = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemCollapseAll = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemMount = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemSpace1 = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemAddGoto = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemSpace2 = gcnew System::Windows::Forms::MenuItem();
			this->btnFileSystemDelete = gcnew System::Windows::Forms::MenuItem();
			this->tabImage = gcnew System::Windows::Forms::TabPage();
			this->grpImage = gcnew System::Windows::Forms::GroupBox();
			this->lblHDRGamma = gcnew System::Windows::Forms::Label();
			this->trkHDRGamma = gcnew System::Windows::Forms::TrackBar();
			this->mnuHDR = gcnew System::Windows::Forms::ContextMenu();
			this->btnHDRReset = gcnew System::Windows::Forms::MenuItem();
			this->lblHDRShift = gcnew System::Windows::Forms::Label();
			this->trkHDRShift = gcnew System::Windows::Forms::TrackBar();
			this->lblHDRKey = gcnew System::Windows::Forms::Label();
			this->trkHDRKey = gcnew System::Windows::Forms::TrackBar();
			this->lblSlice = gcnew System::Windows::Forms::Label();
			this->numSlice = gcnew System::Windows::Forms::NumericUpDown();
			this->lblMipmap = gcnew System::Windows::Forms::Label();
			this->numMipmap = gcnew System::Windows::Forms::NumericUpDown();
			this->numFace = gcnew System::Windows::Forms::NumericUpDown();
			this->lblFace = gcnew System::Windows::Forms::Label();
			this->numFrame = gcnew System::Windows::Forms::NumericUpDown();
			this->lblFrame = gcnew System::Windows::Forms::Label();
			this->btnAnimate = gcnew System::Windows::Forms::Button();
			this->grpFlags = gcnew System::Windows::Forms::GroupBox();
			this->lstFlags = gcnew System::Windows::Forms::CheckedListBox();
			this->tabInfo = gcnew System::Windows::Forms::TabPage();
			this->grpImageInfo = gcnew System::Windows::Forms::GroupBox();
			this->lblImageSlices = gcnew System::Windows::Forms::Label();
			this->lblImageSlicesLabel = gcnew System::Windows::Forms::Label();
			this->numImageBumpmapScale = gcnew System::Windows::Forms::NumericUpDown();
			this->numImageStartFrame = gcnew System::Windows::Forms::NumericUpDown();
			this->lblImageReflectivity = gcnew System::Windows::Forms::Label();
			this->lblImageReflectivityLabel = gcnew System::Windows::Forms::Label();
			this->lblImageBumpmapScaleLabel = gcnew System::Windows::Forms::Label();
			this->lblImageStartFrameLabel = gcnew System::Windows::Forms::Label();
			this->lblImageMipmaps = gcnew System::Windows::Forms::Label();
			this->lblImageMipmapsLabel = gcnew System::Windows::Forms::Label();
			this->lblImageFaces = gcnew System::Windows::Forms::Label();
			this->lblImageFacesLabel = gcnew System::Windows::Forms::Label();
			this->lblImageFrames = gcnew System::Windows::Forms::Label();
			this->lblImageFramesLabel = gcnew System::Windows::Forms::Label();
			this->lblImageFormat = gcnew System::Windows::Forms::Label();
			this->lblImageFormatLabel = gcnew System::Windows::Forms::Label();
			this->lblImageHeight = gcnew System::Windows::Forms::Label();
			this->lblImageHeightLabel = gcnew System::Windows::Forms::Label();
			this->lblImageWidth = gcnew System::Windows::Forms::Label();
			this->lblImageWidthLabel = gcnew System::Windows::Forms::Label();
			this->grpThumbnailInfo = gcnew System::Windows::Forms::GroupBox();
			this->lblThumbnailFormat = gcnew System::Windows::Forms::Label();
			this->lblThumbnailFormatLabel = gcnew System::Windows::Forms::Label();
			this->lblThumbnailHeight = gcnew System::Windows::Forms::Label();
			this->lblThumbnailHeightLabel = gcnew System::Windows::Forms::Label();
			this->lblThumbnailWidth = gcnew System::Windows::Forms::Label();
			this->lblThumbnailWidthLabel = gcnew System::Windows::Forms::Label();
			this->grpFileInfo = gcnew System::Windows::Forms::GroupBox();
			this->lblFileSize = gcnew System::Windows::Forms::Label();
			this->lblFileSizeLabel = gcnew System::Windows::Forms::Label();
			this->lblFileVersion = gcnew System::Windows::Forms::Label();
			this->lblFileVersionLabel = gcnew System::Windows::Forms::Label();
			this->tabResources = gcnew System::Windows::Forms::TabPage();
			this->grpResources = gcnew System::Windows::Forms::GroupBox();
			this->treResources = gcnew System::Windows::Forms::TreeView();
			this->grpResourceInfo = gcnew System::Windows::Forms::GroupBox();
			this->lblResourceCount = gcnew System::Windows::Forms::Label();
			this->lblResourceCountLabel = gcnew System::Windows::Forms::Label();
			this->tmrAnimate = gcnew System::Windows::Forms::Timer(this->components);
			this->dlgSaveVTFFile = gcnew System::Windows::Forms::SaveFileDialog();
			this->dlgSaveVMTFile = gcnew System::Windows::Forms::SaveFileDialog();
			this->pnlMain = gcnew System::Windows::Forms::Panel();
			this->picVTFFileBR = gcnew System::Windows::Forms::PictureBox();
			this->mnuVTFFile = gcnew System::Windows::Forms::ContextMenu();
			this->btnVTFFileZoomIn = gcnew System::Windows::Forms::MenuItem();
			this->btnVTFFileZoomOut = gcnew System::Windows::Forms::MenuItem();
			this->btnVTFFileSpace1 = gcnew System::Windows::Forms::MenuItem();
			this->btnVTFFileZoomReset = gcnew System::Windows::Forms::MenuItem();
			this->btnVTFFileSpace2 = gcnew System::Windows::Forms::MenuItem();
			this->btnVTFFileCopy = gcnew System::Windows::Forms::MenuItem();
			this->picVTFFileBL = gcnew System::Windows::Forms::PictureBox();
			this->picVTFFileTR = gcnew System::Windows::Forms::PictureBox();
			this->picVTFFileTL = gcnew System::Windows::Forms::PictureBox();
			this->txtVMTFile = gcnew FastColoredTextBoxNS::FastColoredTextBox();
			this->mnuVMTFile = gcnew System::Windows::Forms::ContextMenu();
			this->btnVMTFileUndo = gcnew System::Windows::Forms::MenuItem();
			this->btnVMTFileSpace1 = gcnew System::Windows::Forms::MenuItem();
			this->btnVMTFileCut = gcnew System::Windows::Forms::MenuItem();
			this->btnVMTFileCopy = gcnew System::Windows::Forms::MenuItem();
			this->btnVMTFilePaste = gcnew System::Windows::Forms::MenuItem();
			this->btnVMTFileDelete = gcnew System::Windows::Forms::MenuItem();
			this->btnVMTFileSpace2 = gcnew System::Windows::Forms::MenuItem();
			this->btnVMTFileSelectAll = gcnew System::Windows::Forms::MenuItem();
			this->dlgImportFile = gcnew System::Windows::Forms::OpenFileDialog();
			this->dlgExportFile = gcnew System::Windows::Forms::SaveFileDialog();
			this->barTool = gcnew System::Windows::Forms::ToolBar();
			this->btnToolImport = gcnew System::Windows::Forms::ToolBarButton();
			this->btnToolOpen = gcnew System::Windows::Forms::ToolBarButton();
			this->btnToolSave = gcnew System::Windows::Forms::ToolBarButton();
			this->btnSeparator1 = gcnew System::Windows::Forms::ToolBarButton();
			this->btnToolCopy = gcnew System::Windows::Forms::ToolBarButton();
			this->btnToolPaste = gcnew System::Windows::Forms::ToolBarButton();
			this->imgTool = gcnew System::Windows::Forms::ImageList(this->components);
			this->splSidebar = gcnew System::Windows::Forms::Splitter();
			this->dlgExtractDirectoryItem = gcnew System::Windows::Forms::FolderBrowserDialog();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->pnlFileName))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->pnlInfo1))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->pnlInfo2))->BeginInit();
			this->pnlSidebar->SuspendLayout();
			this->tabSidebar->SuspendLayout();
			this->tabFileSystem->SuspendLayout();
			this->grpGoto->SuspendLayout();
			this->grpFileSystem->SuspendLayout();
			this->tabImage->SuspendLayout();
			this->grpImage->SuspendLayout();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->trkHDRGamma))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->trkHDRShift))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->trkHDRKey))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numSlice))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numMipmap))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFace))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFrame))->BeginInit();
			this->grpFlags->SuspendLayout();
			this->tabInfo->SuspendLayout();
			this->grpImageInfo->SuspendLayout();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numImageBumpmapScale))->BeginInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numImageStartFrame))->BeginInit();
			this->grpThumbnailInfo->SuspendLayout();
			this->grpFileInfo->SuspendLayout();
			this->tabResources->SuspendLayout();
			this->grpResources->SuspendLayout();
			this->grpResourceInfo->SuspendLayout();
			this->pnlMain->SuspendLayout();
			this->SuspendLayout();
			//
			// mnuMain
			//
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__1 = gcnew array<System::Windows::Forms::MenuItem^>(6);
			__mcTemp__1[0] = this->btnFileMenu;
			__mcTemp__1[1] = this->btnEditMenu;
			__mcTemp__1[2] = this->btnViewMenu;
			__mcTemp__1[3] = this->btnToolsMenu;
			__mcTemp__1[4] = this->btnOptionsMenu;
			__mcTemp__1[5] = this->btnHelpMenu;
			this->mnuMain->MenuItems->AddRange(__mcTemp__1);
			//
			// btnFileMenu
			//
			this->btnFileMenu->Index = 0;
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__2 = gcnew array<System::Windows::Forms::MenuItem^>(13);
			__mcTemp__2[0] = this->btnNew;
			__mcTemp__2[1] = this->btnOpen;
			__mcTemp__2[2] = this->btnFileSpace1;
			__mcTemp__2[3] = this->btnSave;
			__mcTemp__2[4] = this->btnSaveAs;
			__mcTemp__2[5] = this->btnFileSpace2;
			__mcTemp__2[6] = this->btnImport;
			__mcTemp__2[7] = this->btnExport;
			__mcTemp__2[8] = this->btnExportAll;
			__mcTemp__2[9] = this->btnFileSpace3;
			__mcTemp__2[10] = this->btnRecentFiles;
			__mcTemp__2[11] = this->btnFileSpace4;
			__mcTemp__2[12] = this->btnExit;
			this->btnFileMenu->MenuItems->AddRange(__mcTemp__2);
			this->btnFileMenu->Text = "&File";
			//
			// btnNew
			//
			this->btnNew->Index = 0;
			this->btnNew->Shortcut = System::Windows::Forms::Shortcut::CtrlN;
			this->btnNew->Text = "&New";
			this->btnNew->Click += gcnew System::EventHandler(this, &CVTFEdit::btnNew_Click);
			//
			// btnOpen
			//
			this->btnOpen->Index = 1;
			this->btnOpen->Shortcut = System::Windows::Forms::Shortcut::CtrlO;
			this->btnOpen->Text = "&Open";
			this->btnOpen->Click += gcnew System::EventHandler(this, &CVTFEdit::btnOpen_Click);
			//
			// btnFileSpace1
			//
			this->btnFileSpace1->Index = 2;
			this->btnFileSpace1->Text = "-";
			//
			// btnSave
			//
			this->btnSave->Enabled = false;
			this->btnSave->Index = 3;
			this->btnSave->Shortcut = System::Windows::Forms::Shortcut::CtrlS;
			this->btnSave->Text = "&Save";
			this->btnSave->Click += gcnew System::EventHandler(this, &CVTFEdit::btnSave_Click);
			//
			// btnSaveAs
			//
			this->btnSaveAs->Enabled = false;
			this->btnSaveAs->Index = 4;
			this->btnSaveAs->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftS;
			this->btnSaveAs->Text = "Save &As...";
			this->btnSaveAs->Click += gcnew System::EventHandler(this, &CVTFEdit::btnSaveAs_Click);
			//
			// btnFileSpace2
			//
			this->btnFileSpace2->Index = 5;
			this->btnFileSpace2->Text = "-";
			//
			// btnImport
			//
			this->btnImport->Index = 6;
			this->btnImport->Shortcut = System::Windows::Forms::Shortcut::CtrlI;
			this->btnImport->Text = "&Import";
			this->btnImport->Click += gcnew System::EventHandler(this, &CVTFEdit::btnImport_Click);
			//
			// btnExport
			//
			this->btnExport->Enabled = false;
			this->btnExport->Index = 7;
			this->btnExport->Shortcut = System::Windows::Forms::Shortcut::CtrlE;
			this->btnExport->Text = "&Export";
			this->btnExport->Click += gcnew System::EventHandler(this, &CVTFEdit::btnExport_Click);
			//
			// btnExportAll
			//
			this->btnExportAll->Enabled = false;
			this->btnExportAll->Index = 8;
			this->btnExportAll->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftE;
			this->btnExportAll->Text = "&Export All";
			this->btnExportAll->Click += gcnew System::EventHandler(this, &CVTFEdit::btnExportAll_Click);
			//
			// btnFileSpace3
			//
			this->btnFileSpace3->Index = 9;
			this->btnFileSpace3->Text = "-";
			//
			// btnRecentFiles
			//
			this->btnRecentFiles->Index = 10;
			this->btnRecentFiles->Text = "&Recent Files";
			this->btnRecentFiles->Visible = false;
			//
			// btnFileSpace4
			//
			this->btnFileSpace4->Index = 11;
			this->btnFileSpace4->Text = "-";
			this->btnFileSpace4->Visible = false;
			//
			// btnExit
			//
			this->btnExit->Index = 12;
			this->btnExit->Shortcut = System::Windows::Forms::Shortcut::AltF4;
			this->btnExit->Text = "E&xit";
			this->btnExit->Click += gcnew System::EventHandler(this, &CVTFEdit::btnExit_Click);
			//
			// btnEditMenu
			//
			this->btnEditMenu->Index = 1;
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__3 = gcnew array<System::Windows::Forms::MenuItem^>(2);
			__mcTemp__3[0] = this->btnCopy;
			__mcTemp__3[1] = this->btnPaste;
			this->btnEditMenu->MenuItems->AddRange(__mcTemp__3);
			this->btnEditMenu->Text = "&Edit";
			//
			// btnCopy
			//
			this->btnCopy->Enabled = false;
			this->btnCopy->Index = 0;
			this->btnCopy->Shortcut = System::Windows::Forms::Shortcut::CtrlC;
			this->btnCopy->Text = "&Copy";
			this->btnCopy->Click += gcnew System::EventHandler(this, &CVTFEdit::btnCopy_Click);
			//
			// btnPaste
			//
			this->btnPaste->Enabled = false;
			this->btnPaste->Index = 1;
			this->btnPaste->Shortcut = System::Windows::Forms::Shortcut::CtrlV;
			this->btnPaste->Text = "&Paste";
			this->btnPaste->Click += gcnew System::EventHandler(this, &CVTFEdit::btnPaste_Click);
			//
			// btnViewMenu
			//
			this->btnViewMenu->Index = 2;
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__4 = gcnew array<System::Windows::Forms::MenuItem^>(3);
			__mcTemp__4[0] = this->btnChannelMenu;
			__mcTemp__4[1] = this->btnMask;
			__mcTemp__4[2] = this->btnTile;
			this->btnViewMenu->MenuItems->AddRange(__mcTemp__4);
			this->btnViewMenu->Text = "&View";
			//
			// btnChannelMenu
			//
			this->btnChannelMenu->Index = 0;
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__5 = gcnew array<System::Windows::Forms::MenuItem^>(5);
			__mcTemp__5[0] = this->btnChannelRGB;
			__mcTemp__5[1] = this->btnChannelR;
			__mcTemp__5[2] = this->btnChannelG;
			__mcTemp__5[3] = this->btnChannelB;
			__mcTemp__5[4] = this->btnChannelA;
			this->btnChannelMenu->MenuItems->AddRange(__mcTemp__5);
			this->btnChannelMenu->Text = "&Channel";
			//
			// btnChannelRGB
			//
			this->btnChannelRGB->Checked = true;
			this->btnChannelRGB->Index = 0;
			this->btnChannelRGB->RadioCheck = true;
			this->btnChannelRGB->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftC;
			this->btnChannelRGB->Text = "RGB";
			this->btnChannelRGB->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannel_Click);
			//
			// btnChannelR
			//
			this->btnChannelR->Index = 1;
			this->btnChannelR->RadioCheck = true;
			this->btnChannelR->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftR;
			this->btnChannelR->Text = "R";
			this->btnChannelR->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannel_Click);
			//
			// btnChannelG
			//
			this->btnChannelG->Index = 2;
			this->btnChannelG->RadioCheck = true;
			this->btnChannelG->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftG;
			this->btnChannelG->Text = "G";
			this->btnChannelG->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannel_Click);
			//
			// btnChannelB
			//
			this->btnChannelB->Index = 3;
			this->btnChannelB->RadioCheck = true;
			this->btnChannelB->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftB;
			this->btnChannelB->Text = "B";
			this->btnChannelB->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannel_Click);
			//
			// btnChannelA
			//
			this->btnChannelA->Index = 4;
			this->btnChannelA->RadioCheck = true;
			this->btnChannelA->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftA;
			this->btnChannelA->Text = "A";
			this->btnChannelA->Click += gcnew System::EventHandler(this, &CVTFEdit::btnChannel_Click);
			//
			// btnMask
			//
			this->btnMask->Index = 1;
			this->btnMask->Shortcut = System::Windows::Forms::Shortcut::CtrlM;
			this->btnMask->Text = "&Mask";
			this->btnMask->Click += gcnew System::EventHandler(this, &CVTFEdit::btnMask_Click);
			//
			// btnTile
			//
			this->btnTile->Index = 2;
			this->btnTile->Shortcut = System::Windows::Forms::Shortcut::CtrlT;
			this->btnTile->Text = "&Tile";
			this->btnTile->Click += gcnew System::EventHandler(this, &CVTFEdit::btnTile_Click);
			//
			// btnToolsMenu
			//
			this->btnToolsMenu->Index = 3;
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__6 = gcnew array<System::Windows::Forms::MenuItem^>(3);
			__mcTemp__6[0] = this->btnCreateVMTFile;
			__mcTemp__6[1] = this->btnConvertFolder;
			__mcTemp__6[2] = this->btnConvertWADFile;
			this->btnToolsMenu->MenuItems->AddRange(__mcTemp__6);
			this->btnToolsMenu->Text = "&Tools";
			//
			// btnCreateVMTFile
			//
			this->btnCreateVMTFile->Index = 0;
			this->btnCreateVMTFile->Text = "Create &VMT File";
			this->btnCreateVMTFile->Click += gcnew System::EventHandler(this, &CVTFEdit::btnCreateVMTFile_Click);
			//
			// btnConvertFolder
			//
			this->btnConvertFolder->Index = 1;
			this->btnConvertFolder->Text = "Convert &Folder";
			this->btnConvertFolder->Click += gcnew System::EventHandler(this, &CVTFEdit::btnConvertFolder_Click);
			//
			// btnConvertWADFile
			//
			this->btnConvertWADFile->Index = 2;
			this->btnConvertWADFile->Text = "Convert &WAD File";
			this->btnConvertWADFile->Click += gcnew System::EventHandler(this, &CVTFEdit::btnConvertWADFile_Click);
			//
			// btnOptionsMenu
			//
			this->btnOptionsMenu->Index = 4;
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__7 = gcnew array<System::Windows::Forms::MenuItem^>(4);
			__mcTemp__7[0] = this->btnAutoCreateVMTFile;
			__mcTemp__7[1] = this->btnOptionsSpace1;
			__mcTemp__7[2] = this->btnFileMapping;
			__mcTemp__7[3] = this->btnVolatileAccess;
			this->btnOptionsMenu->MenuItems->AddRange(__mcTemp__7);
			this->btnOptionsMenu->Text = "&Options";
			//
			// btnAutoCreateVMTFile
			//
			this->btnAutoCreateVMTFile->Index = 0;
			this->btnAutoCreateVMTFile->Text = "&Auto Create VMT File";
			this->btnAutoCreateVMTFile->Click += gcnew System::EventHandler(this, &CVTFEdit::btnAutoCreateVMTFile_Click);
			//
			// btnOptionsSpace1
			//
			this->btnOptionsSpace1->Index = 1;
			this->btnOptionsSpace1->Text = "-";
			//
			// btnFileMapping
			//
			this->btnFileMapping->Index = 2;
			this->btnFileMapping->Text = "File &Mapping";
			this->btnFileMapping->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileMapping_Click);
			//
			// btnVolatileAccess
			//
			this->btnVolatileAccess->Index = 3;
			this->btnVolatileAccess->Text = "&Volatile Access";
			this->btnVolatileAccess->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVolatileAccess_Click);
			//
			// btnHelpMenu
			//
			this->btnHelpMenu->Index = 5;
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__8 = gcnew array<System::Windows::Forms::MenuItem^>(1);
			__mcTemp__8[0] = this->btnAbout;
			this->btnHelpMenu->MenuItems->AddRange(__mcTemp__8);
			this->btnHelpMenu->Text = "&Help";
			//
			// btnAbout
			//
			this->btnAbout->Index = 0;
			this->btnAbout->Text = "&About";
			this->btnAbout->Click += gcnew System::EventHandler(this, &CVTFEdit::btnAbout_Click);
			//
			// dlgOpenFile
			//
			this->dlgOpenFile->Filter = "Supported Files (*.vmt;*.vtf)|*.vmt;*.vtf|VMT Files (*.vmt)|*.vmt|VTF File (*.vtf"
				")|*.vtf";
			this->dlgOpenFile->Title = "Open File";
			//
			// barStatus
			//
			this->barStatus->Location = System::Drawing::Point(0, 563);
			this->barStatus->Name = "barStatus";
			array<System::Windows::Forms::StatusBarPanel^>^ __mcTemp__9 = gcnew array<System::Windows::Forms::StatusBarPanel^>(3);
			__mcTemp__9[0] = this->pnlFileName;
			__mcTemp__9[1] = this->pnlInfo1;
			__mcTemp__9[2] = this->pnlInfo2;
			this->barStatus->Panels->AddRange(__mcTemp__9);
			this->barStatus->ShowPanels = true;
			this->barStatus->Size = System::Drawing::Size(752, 22);
			this->barStatus->TabIndex = 3;
			//
			// pnlFileName
			//
			this->pnlFileName->AutoSize = System::Windows::Forms::StatusBarPanelAutoSize::Spring;
			this->pnlFileName->MinWidth = 100;
			this->pnlFileName->Width = 586;
			//
			// pnlInfo1
			//
			this->pnlInfo1->AutoSize = System::Windows::Forms::StatusBarPanelAutoSize::Contents;
			this->pnlInfo1->MinWidth = 75;
			this->pnlInfo1->Width = 75;
			//
			// pnlInfo2
			//
			this->pnlInfo2->AutoSize = System::Windows::Forms::StatusBarPanelAutoSize::Contents;
			this->pnlInfo2->MinWidth = 75;
			this->pnlInfo2->Width = 75;
			//
			// pnlSidebar
			//
			this->pnlSidebar->BackColor = System::Drawing::SystemColors::Control;
			this->pnlSidebar->Controls->Add(this->tabSidebar);
			this->pnlSidebar->Dock = System::Windows::Forms::DockStyle::Left;
			this->pnlSidebar->Location = System::Drawing::Point(0, 28);
			this->pnlSidebar->Name = "pnlSidebar";
			this->pnlSidebar->Size = System::Drawing::Size(232, 535);
			this->pnlSidebar->TabIndex = 0;
			//
			// tabSidebar
			//
			this->tabSidebar->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->tabSidebar->Controls->Add(this->tabFileSystem);
			this->tabSidebar->Controls->Add(this->tabImage);
			this->tabSidebar->Controls->Add(this->tabInfo);
			this->tabSidebar->Controls->Add(this->tabResources);
			this->tabSidebar->Location = System::Drawing::Point(8, 8);
			this->tabSidebar->Name = "tabSidebar";
			this->tabSidebar->SelectedIndex = 0;
			this->tabSidebar->Size = System::Drawing::Size(216, 516);
			this->tabSidebar->TabIndex = 2;
			//
			// tabFileSystem
			//
			this->tabFileSystem->Controls->Add(this->grpGoto);
			this->tabFileSystem->Controls->Add(this->grpFileSystem);
			this->tabFileSystem->Location = System::Drawing::Point(4, 22);
			this->tabFileSystem->Name = "tabFileSystem";
			this->tabFileSystem->Size = System::Drawing::Size(208, 490);
			this->tabFileSystem->TabIndex = 2;
			this->tabFileSystem->Text = "File System";
			//
			// grpGoto
			//
			this->grpGoto->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpGoto->Controls->Add(this->cboGoto);
			this->grpGoto->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpGoto->Location = System::Drawing::Point(8, 8);
			this->grpGoto->Name = "grpGoto";
			this->grpGoto->Size = System::Drawing::Size(192, 48);
			this->grpGoto->TabIndex = 1;
			this->grpGoto->TabStop = false;
			this->grpGoto->Text = "Goto:";
			//
			// cboGoto
			//
			this->cboGoto->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->cboGoto->ContextMenu = this->mnuGoto;
			this->cboGoto->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cboGoto->Location = System::Drawing::Point(8, 16);
			this->cboGoto->Name = "cboGoto";
			this->cboGoto->Size = System::Drawing::Size(176, 21);
			this->cboGoto->TabIndex = 0;
			this->cboGoto->SelectedIndexChanged += gcnew System::EventHandler(this, &CVTFEdit::cboGoto_SelectedIndexChanged);
			//
			// mnuGoto
			//
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__10 = gcnew array<System::Windows::Forms::MenuItem^>(2);
			__mcTemp__10[0] = this->btnGotoRemove;
			__mcTemp__10[1] = this->btnGotoClear;
			this->mnuGoto->MenuItems->AddRange(__mcTemp__10);
			this->mnuGoto->Popup += gcnew System::EventHandler(this, &CVTFEdit::mnuGoto_Popup);
			//
			// btnGotoRemove
			//
			this->btnGotoRemove->Index = 0;
			this->btnGotoRemove->Text = "&Remove";
			this->btnGotoRemove->Click += gcnew System::EventHandler(this, &CVTFEdit::btnGotoRemove_Click);
			//
			// btnGotoClear
			//
			this->btnGotoClear->Index = 1;
			this->btnGotoClear->Text = "&Clear";
			this->btnGotoClear->Click += gcnew System::EventHandler(this, &CVTFEdit::btnGotoClear_Click);
			//
			// grpFileSystem
			//
			this->grpFileSystem->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpFileSystem->Controls->Add(this->treFileSystem);
			this->grpFileSystem->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpFileSystem->Location = System::Drawing::Point(8, 64);
			this->grpFileSystem->Name = "grpFileSystem";
			this->grpFileSystem->Size = System::Drawing::Size(192, 416);
			this->grpFileSystem->TabIndex = 0;
			this->grpFileSystem->TabStop = false;
			this->grpFileSystem->Text = "File System:";
			//
			// treFileSystem
			//
			this->treFileSystem->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->treFileSystem->ContextMenu = this->mnuFileSystem;
			this->treFileSystem->HideSelection = false;
			this->treFileSystem->ImageIndex = -1;
			this->treFileSystem->Location = System::Drawing::Point(8, 16);
			this->treFileSystem->Name = "treFileSystem";
			this->treFileSystem->SelectedImageIndex = -1;
			this->treFileSystem->Size = System::Drawing::Size(176, 392);
			this->treFileSystem->TabIndex = 0;
			this->treFileSystem->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::treFileSystem_MouseDown);
			this->treFileSystem->AfterExpand += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CVTFEdit::treFileSystem_AfterExpand);
			this->treFileSystem->AfterCollapse += gcnew System::Windows::Forms::TreeViewEventHandler(this, &CVTFEdit::treFileSystem_AfterCollapse);
			this->treFileSystem->DoubleClick += gcnew System::EventHandler(this, &CVTFEdit::treFileSystem_DoubleClick);
			this->treFileSystem->BeforeExpand += gcnew System::Windows::Forms::TreeViewCancelEventHandler(this, &CVTFEdit::treFileSystem_BeforeExpand);
			//
			// mnuFileSystem
			//
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__11 = gcnew array<System::Windows::Forms::MenuItem^>(10);
			__mcTemp__11[0] = this->btnFileSystemOpen;
			__mcTemp__11[1] = this->btnFileSystemShellExecute;
			__mcTemp__11[2] = this->btnFileSystemExtract;
			__mcTemp__11[3] = this->btnFileSystemExpandAll;
			__mcTemp__11[4] = this->btnFileSystemCollapseAll;
			__mcTemp__11[5] = this->btnFileSystemMount;
			__mcTemp__11[6] = this->btnFileSystemSpace1;
			__mcTemp__11[7] = this->btnFileSystemAddGoto;
			__mcTemp__11[8] = this->btnFileSystemSpace2;
			__mcTemp__11[9] = this->btnFileSystemDelete;
			this->mnuFileSystem->MenuItems->AddRange(__mcTemp__11);
			this->mnuFileSystem->Popup += gcnew System::EventHandler(this, &CVTFEdit::mnuFileSystem_Popup);
			//
			// btnFileSystemOpen
			//
			this->btnFileSystemOpen->DefaultItem = true;
			this->btnFileSystemOpen->Index = 0;
			this->btnFileSystemOpen->Text = "&Open";
			this->btnFileSystemOpen->Visible = false;
			this->btnFileSystemOpen->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileSystemOpen_Click);
			//
			// btnFileSystemShellExecute
			//
			this->btnFileSystemShellExecute->Index = 1;
			this->btnFileSystemShellExecute->Text = "&Shell Execute";
			this->btnFileSystemShellExecute->Visible = false;
			this->btnFileSystemShellExecute->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileSystemShellExecute_Click);
			//
			// btnFileSystemExtract
			//
			this->btnFileSystemExtract->Index = 2;
			this->btnFileSystemExtract->Text = "&Extract";
			this->btnFileSystemExtract->Visible = false;
			this->btnFileSystemExtract->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileSystemExtract_Click);
			//
			// btnFileSystemExpandAll
			//
			this->btnFileSystemExpandAll->Index = 3;
			this->btnFileSystemExpandAll->Text = "&Expand All";
			this->btnFileSystemExpandAll->Visible = false;
			this->btnFileSystemExpandAll->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileSystemExpandAll_Click);
			//
			// btnFileSystemCollapseAll
			//
			this->btnFileSystemCollapseAll->Index = 4;
			this->btnFileSystemCollapseAll->Text = "&Collapse All";
			this->btnFileSystemCollapseAll->Visible = false;
			this->btnFileSystemCollapseAll->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileSystemCollapseAll_Click);
			//
			// btnFileSystemMount
			//
			this->btnFileSystemMount->Index = 5;
			this->btnFileSystemMount->Text = "&Mount";
			this->btnFileSystemMount->Visible = false;
			this->btnFileSystemMount->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileSystemMount_Click);
			//
			// btnFileSystemSpace1
			//
			this->btnFileSystemSpace1->Index = 6;
			this->btnFileSystemSpace1->Text = "-";
			this->btnFileSystemSpace1->Visible = false;
			//
			// btnFileSystemAddGoto
			//
			this->btnFileSystemAddGoto->Index = 7;
			this->btnFileSystemAddGoto->Text = "Add &Goto";
			this->btnFileSystemAddGoto->Visible = false;
			this->btnFileSystemAddGoto->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileSystemAddGoto_Click);
			//
			// btnFileSystemSpace2
			//
			this->btnFileSystemSpace2->Index = 8;
			this->btnFileSystemSpace2->Text = "-";
			this->btnFileSystemSpace2->Visible = false;
			//
			// btnFileSystemDelete
			//
			this->btnFileSystemDelete->Index = 9;
			this->btnFileSystemDelete->Text = "&Delete";
			this->btnFileSystemDelete->Visible = false;
			this->btnFileSystemDelete->Click += gcnew System::EventHandler(this, &CVTFEdit::btnFileSystemDelete_Click);
			//
			// tabImage
			//
			this->tabImage->Controls->Add(this->grpImage);
			this->tabImage->Controls->Add(this->grpFlags);
			this->tabImage->Location = System::Drawing::Point(4, 22);
			this->tabImage->Name = "tabImage";
			this->tabImage->Size = System::Drawing::Size(208, 490);
			this->tabImage->TabIndex = 0;
			this->tabImage->Text = "Image";
			//
			// grpImage
			//
			this->grpImage->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpImage->Controls->Add(this->lblHDRGamma);
			this->grpImage->Controls->Add(this->trkHDRGamma);
			this->grpImage->Controls->Add(this->lblHDRShift);
			this->grpImage->Controls->Add(this->trkHDRShift);
			this->grpImage->Controls->Add(this->lblHDRKey);
			this->grpImage->Controls->Add(this->trkHDRKey);
			this->grpImage->Controls->Add(this->lblSlice);
			this->grpImage->Controls->Add(this->numSlice);
			this->grpImage->Controls->Add(this->lblMipmap);
			this->grpImage->Controls->Add(this->numMipmap);
			this->grpImage->Controls->Add(this->numFace);
			this->grpImage->Controls->Add(this->lblFace);
			this->grpImage->Controls->Add(this->numFrame);
			this->grpImage->Controls->Add(this->lblFrame);
			this->grpImage->Controls->Add(this->btnAnimate);
			this->grpImage->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpImage->Location = System::Drawing::Point(8, 8);
			this->grpImage->Name = "grpImage";
			this->grpImage->Size = System::Drawing::Size(192, 224);
			this->grpImage->TabIndex = 0;
			this->grpImage->TabStop = false;
			this->grpImage->Text = "Image:";
			//
			// lblHDRGamma
			//
			this->lblHDRGamma->Location = System::Drawing::Point(8, 168);
			this->lblHDRGamma->Name = "lblHDRGamma";
			this->lblHDRGamma->Size = System::Drawing::Size(48, 23);
			this->lblHDRGamma->TabIndex = 12;
			this->lblHDRGamma->Text = "Gamma:";
			//
			// trkHDRGamma
			//
			this->trkHDRGamma->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->trkHDRGamma->AutoSize = false;
			this->trkHDRGamma->ContextMenu = this->mnuHDR;
			this->trkHDRGamma->Location = System::Drawing::Point(56, 168);
			this->trkHDRGamma->Name = "trkHDRGamma";
			this->trkHDRGamma->Size = System::Drawing::Size(128, 16);
			this->trkHDRGamma->TabIndex = 13;
			this->trkHDRGamma->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::trkHDRGamma_ValueChanged);
			//
			// mnuHDR
			//
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__12 = gcnew array<System::Windows::Forms::MenuItem^>(1);
			__mcTemp__12[0] = this->btnHDRReset;
			this->mnuHDR->MenuItems->AddRange(__mcTemp__12);
			//
			// btnHDRReset
			//
			this->btnHDRReset->Index = 0;
			this->btnHDRReset->Text = "&Reset";
			this->btnHDRReset->Click += gcnew System::EventHandler(this, &CVTFEdit::btnHDRReset_Click);
			//
			// lblHDRShift
			//
			this->lblHDRShift->Location = System::Drawing::Point(8, 144);
			this->lblHDRShift->Name = "lblHDRShift";
			this->lblHDRShift->Size = System::Drawing::Size(48, 23);
			this->lblHDRShift->TabIndex = 10;
			this->lblHDRShift->Text = "Shift:";
			//
			// trkHDRShift
			//
			this->trkHDRShift->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->trkHDRShift->AutoSize = false;
			this->trkHDRShift->ContextMenu = this->mnuHDR;
			this->trkHDRShift->Location = System::Drawing::Point(56, 144);
			this->trkHDRShift->Name = "trkHDRShift";
			this->trkHDRShift->Size = System::Drawing::Size(128, 16);
			this->trkHDRShift->TabIndex = 11;
			this->trkHDRShift->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::trkHDRShift_ValueChanged);
			//
			// lblHDRKey
			//
			this->lblHDRKey->Location = System::Drawing::Point(8, 120);
			this->lblHDRKey->Name = "lblHDRKey";
			this->lblHDRKey->Size = System::Drawing::Size(48, 23);
			this->lblHDRKey->TabIndex = 8;
			this->lblHDRKey->Text = "Key:";
			//
			// trkHDRKey
			//
			this->trkHDRKey->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->trkHDRKey->AutoSize = false;
			this->trkHDRKey->ContextMenu = this->mnuHDR;
			this->trkHDRKey->Location = System::Drawing::Point(56, 120);
			this->trkHDRKey->Name = "trkHDRKey";
			this->trkHDRKey->Size = System::Drawing::Size(128, 16);
			this->trkHDRKey->TabIndex = 9;
			this->trkHDRKey->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::trkHDRKey_ValueChanged);
			//
			// lblSlice
			//
			this->lblSlice->Location = System::Drawing::Point(8, 72);
			this->lblSlice->Name = "lblSlice";
			this->lblSlice->Size = System::Drawing::Size(48, 23);
			this->lblSlice->TabIndex = 4;
			this->lblSlice->Text = "Slice:";
			//
			// numSlice
			//
			this->numSlice->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->numSlice->Location = System::Drawing::Point(56, 72);
			array<System::Int32>^ __mcTemp__13 = { 0, 0, 0, 0};
			this->numSlice->Maximum = System::Decimal(__mcTemp__13);
			this->numSlice->Name = "numSlice";
			this->numSlice->Size = System::Drawing::Size(128, 20);
			this->numSlice->TabIndex = 5;
			this->numSlice->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numVTFFile_ValueChanged);
			//
			// lblMipmap
			//
			this->lblMipmap->Location = System::Drawing::Point(8, 96);
			this->lblMipmap->Name = "lblMipmap";
			this->lblMipmap->Size = System::Drawing::Size(48, 23);
			this->lblMipmap->TabIndex = 6;
			this->lblMipmap->Text = "Mipmap:";
			//
			// numMipmap
			//
			this->numMipmap->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->numMipmap->Location = System::Drawing::Point(56, 96);
			array<System::Int32>^ __mcTemp__14 = { 0, 0, 0, 0 };
			this->numMipmap->Maximum = System::Decimal(__mcTemp__14);
			this->numMipmap->Name = "numMipmap";
			this->numMipmap->Size = System::Drawing::Size(128, 20);
			this->numMipmap->TabIndex = 7;
			this->numMipmap->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numVTFFile_ValueChanged);
			//
			// numFace
			//
			this->numFace->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->numFace->Location = System::Drawing::Point(56, 48);
			array<System::Int32>^ __mcTemp__15 = { 0, 0, 0, 0 };
			this->numFace->Maximum = System::Decimal(__mcTemp__15);
			this->numFace->Name = "numFace";
			this->numFace->Size = System::Drawing::Size(128, 20);
			this->numFace->TabIndex = 3;
			this->numFace->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numVTFFile_ValueChanged);
			//
			// lblFace
			//
			this->lblFace->Location = System::Drawing::Point(8, 48);
			this->lblFace->Name = "lblFace";
			this->lblFace->Size = System::Drawing::Size(48, 23);
			this->lblFace->TabIndex = 2;
			this->lblFace->Text = "Face:";
			//
			// numFrame
			//
			this->numFrame->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->numFrame->Location = System::Drawing::Point(56, 24);
			array<System::Int32>^ __mcTemp__16 = { 0, 0, 0, 0 };
			this->numFrame->Maximum = System::Decimal(__mcTemp__16);
			this->numFrame->Name = "numFrame";
			this->numFrame->Size = System::Drawing::Size(128, 20);
			this->numFrame->TabIndex = 1;
			this->numFrame->ValueChanged += gcnew System::EventHandler(this, &CVTFEdit::numVTFFile_ValueChanged);
			//
			// lblFrame
			//
			this->lblFrame->Location = System::Drawing::Point(8, 24);
			this->lblFrame->Name = "lblFrame";
			this->lblFrame->Size = System::Drawing::Size(48, 23);
			this->lblFrame->TabIndex = 0;
			this->lblFrame->Text = "Frame:";
			//
			// btnAnimate
			//
			this->btnAnimate->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->btnAnimate->Enabled = false;
			this->btnAnimate->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->btnAnimate->Location = System::Drawing::Point(56, 192);
			this->btnAnimate->Name = "btnAnimate";
			this->btnAnimate->Size = System::Drawing::Size(128, 23);
			this->btnAnimate->TabIndex = 14;
			this->btnAnimate->Click += gcnew System::EventHandler(this, &CVTFEdit::btnAnimate_Click);
			//
			// grpFlags
			//
			this->grpFlags->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpFlags->Controls->Add(this->lstFlags);
			this->grpFlags->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpFlags->Location = System::Drawing::Point(8, 240);
			this->grpFlags->Name = "grpFlags";
			this->grpFlags->Size = System::Drawing::Size(192, 240);
			this->grpFlags->TabIndex = 1;
			this->grpFlags->TabStop = false;
			this->grpFlags->Text = "Flags:";
			//
			// lstFlags
			//
			this->lstFlags->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lstFlags->CheckOnClick = true;
			this->lstFlags->Location = System::Drawing::Point(8, 16);
			this->lstFlags->Name = "lstFlags";
			this->lstFlags->Size = System::Drawing::Size(176, 214);
			this->lstFlags->TabIndex = 3;
			this->lstFlags->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &CVTFEdit::lstFlags_ItemCheck);
			//
			// tabInfo
			//
			this->tabInfo->Controls->Add(this->grpImageInfo);
			this->tabInfo->Controls->Add(this->grpThumbnailInfo);
			this->tabInfo->Controls->Add(this->grpFileInfo);
			this->tabInfo->Location = System::Drawing::Point(4, 22);
			this->tabInfo->Name = "tabInfo";
			this->tabInfo->Size = System::Drawing::Size(208, 490);
			this->tabInfo->TabIndex = 1;
			this->tabInfo->Text = "Info";
			//
			// grpImageInfo
			//
			this->grpImageInfo->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpImageInfo->Controls->Add(this->lblImageSlices);
			this->grpImageInfo->Controls->Add(this->lblImageSlicesLabel);
			this->grpImageInfo->Controls->Add(this->numImageBumpmapScale);
			this->grpImageInfo->Controls->Add(this->numImageStartFrame);
			this->grpImageInfo->Controls->Add(this->lblImageReflectivity);
			this->grpImageInfo->Controls->Add(this->lblImageReflectivityLabel);
			this->grpImageInfo->Controls->Add(this->lblImageBumpmapScaleLabel);
			this->grpImageInfo->Controls->Add(this->lblImageStartFrameLabel);
			this->grpImageInfo->Controls->Add(this->lblImageMipmaps);
			this->grpImageInfo->Controls->Add(this->lblImageMipmapsLabel);
			this->grpImageInfo->Controls->Add(this->lblImageFaces);
			this->grpImageInfo->Controls->Add(this->lblImageFacesLabel);
			this->grpImageInfo->Controls->Add(this->lblImageFrames);
			this->grpImageInfo->Controls->Add(this->lblImageFramesLabel);
			this->grpImageInfo->Controls->Add(this->lblImageFormat);
			this->grpImageInfo->Controls->Add(this->lblImageFormatLabel);
			this->grpImageInfo->Controls->Add(this->lblImageHeight);
			this->grpImageInfo->Controls->Add(this->lblImageHeightLabel);
			this->grpImageInfo->Controls->Add(this->lblImageWidth);
			this->grpImageInfo->Controls->Add(this->lblImageWidthLabel);
			this->grpImageInfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpImageInfo->Location = System::Drawing::Point(8, 96);
			this->grpImageInfo->Name = "grpImageInfo";
			this->grpImageInfo->Size = System::Drawing::Size(192, 272);
			this->grpImageInfo->TabIndex = 1;
			this->grpImageInfo->TabStop = false;
			this->grpImageInfo->Text = "Image Info:";
			//
			// lblImageSlices
			//
			this->lblImageSlices->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblImageSlices->Location = System::Drawing::Point(72, 168);
			this->lblImageSlices->Name = "lblImageSlices";
			this->lblImageSlices->Size = System::Drawing::Size(112, 23);
			this->lblImageSlices->TabIndex = 13;
			//
			// lblImageSlicesLabel
			//
			this->lblImageSlicesLabel->Location = System::Drawing::Point(8, 168);
			this->lblImageSlicesLabel->Name = "lblImageSlicesLabel";
			this->lblImageSlicesLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageSlicesLabel->TabIndex = 12;
			this->lblImageSlicesLabel->Text = "Slices:";
			//
			// numImageBumpmapScale
			//
			this->numImageBumpmapScale->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->numImageBumpmapScale->Location = System::Drawing::Point(72, 216);
			this->numImageBumpmapScale->Name = "numImageBumpmapScale";
			this->numImageBumpmapScale->Size = System::Drawing::Size(112, 20);
			this->numImageBumpmapScale->TabIndex = 17;
			//
			// numImageStartFrame
			//
			this->numImageStartFrame->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->numImageStartFrame->Location = System::Drawing::Point(72, 120);
			array<System::Int32>^ __mcTemp__18 = { 0, 0, 0, 0 };
			this->numImageStartFrame->Maximum = System::Decimal(__mcTemp__18);
			this->numImageStartFrame->Name = "numImageStartFrame";
			this->numImageStartFrame->Size = System::Drawing::Size(112, 20);
			this->numImageStartFrame->TabIndex = 9;
			//
			// lblImageReflectivity
			//
			this->lblImageReflectivity->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblImageReflectivity->Location = System::Drawing::Point(72, 240);
			this->lblImageReflectivity->Name = "lblImageReflectivity";
			this->lblImageReflectivity->Size = System::Drawing::Size(112, 23);
			this->lblImageReflectivity->TabIndex = 19;
			//
			// lblImageReflectivityLabel
			//
			this->lblImageReflectivityLabel->Location = System::Drawing::Point(8, 240);
			this->lblImageReflectivityLabel->Name = "lblImageReflectivityLabel";
			this->lblImageReflectivityLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageReflectivityLabel->TabIndex = 18;
			this->lblImageReflectivityLabel->Text = "Reflectivity:";
			//
			// lblImageBumpmapScaleLabel
			//
			this->lblImageBumpmapScaleLabel->Location = System::Drawing::Point(8, 216);
			this->lblImageBumpmapScaleLabel->Name = "lblImageBumpmapScaleLabel";
			this->lblImageBumpmapScaleLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageBumpmapScaleLabel->TabIndex = 16;
			this->lblImageBumpmapScaleLabel->Text = "Bumpmap:";
			//
			// lblImageStartFrameLabel
			//
			this->lblImageStartFrameLabel->Location = System::Drawing::Point(8, 120);
			this->lblImageStartFrameLabel->Name = "lblImageStartFrameLabel";
			this->lblImageStartFrameLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageStartFrameLabel->TabIndex = 8;
			this->lblImageStartFrameLabel->Text = "Start:";
			//
			// lblImageMipmaps
			//
			this->lblImageMipmaps->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblImageMipmaps->Location = System::Drawing::Point(72, 192);
			this->lblImageMipmaps->Name = "lblImageMipmaps";
			this->lblImageMipmaps->Size = System::Drawing::Size(112, 23);
			this->lblImageMipmaps->TabIndex = 15;
			//
			// lblImageMipmapsLabel
			//
			this->lblImageMipmapsLabel->Location = System::Drawing::Point(8, 192);
			this->lblImageMipmapsLabel->Name = "lblImageMipmapsLabel";
			this->lblImageMipmapsLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageMipmapsLabel->TabIndex = 14;
			this->lblImageMipmapsLabel->Text = "Mipmaps:";
			//
			// lblImageFaces
			//
			this->lblImageFaces->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblImageFaces->Location = System::Drawing::Point(72, 144);
			this->lblImageFaces->Name = "lblImageFaces";
			this->lblImageFaces->Size = System::Drawing::Size(112, 23);
			this->lblImageFaces->TabIndex = 11;
			//
			// lblImageFacesLabel
			//
			this->lblImageFacesLabel->Location = System::Drawing::Point(8, 144);
			this->lblImageFacesLabel->Name = "lblImageFacesLabel";
			this->lblImageFacesLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageFacesLabel->TabIndex = 10;
			this->lblImageFacesLabel->Text = "Faces:";
			//
			// lblImageFrames
			//
			this->lblImageFrames->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblImageFrames->Location = System::Drawing::Point(72, 96);
			this->lblImageFrames->Name = "lblImageFrames";
			this->lblImageFrames->Size = System::Drawing::Size(112, 23);
			this->lblImageFrames->TabIndex = 7;
			//
			// lblImageFramesLabel
			//
			this->lblImageFramesLabel->Location = System::Drawing::Point(8, 96);
			this->lblImageFramesLabel->Name = "lblImageFramesLabel";
			this->lblImageFramesLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageFramesLabel->TabIndex = 6;
			this->lblImageFramesLabel->Text = "Frames:";
			//
			// lblImageFormat
			//
			this->lblImageFormat->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblImageFormat->Location = System::Drawing::Point(72, 72);
			this->lblImageFormat->Name = "lblImageFormat";
			this->lblImageFormat->Size = System::Drawing::Size(112, 23);
			this->lblImageFormat->TabIndex = 5;
			//
			// lblImageFormatLabel
			//
			this->lblImageFormatLabel->Location = System::Drawing::Point(8, 72);
			this->lblImageFormatLabel->Name = "lblImageFormatLabel";
			this->lblImageFormatLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageFormatLabel->TabIndex = 4;
			this->lblImageFormatLabel->Text = "Format:";
			//
			// lblImageHeight
			//
			this->lblImageHeight->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblImageHeight->Location = System::Drawing::Point(72, 48);
			this->lblImageHeight->Name = "lblImageHeight";
			this->lblImageHeight->Size = System::Drawing::Size(112, 23);
			this->lblImageHeight->TabIndex = 3;
			//
			// lblImageHeightLabel
			//
			this->lblImageHeightLabel->Location = System::Drawing::Point(8, 48);
			this->lblImageHeightLabel->Name = "lblImageHeightLabel";
			this->lblImageHeightLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageHeightLabel->TabIndex = 2;
			this->lblImageHeightLabel->Text = "Height:";
			//
			// lblImageWidth
			//
			this->lblImageWidth->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblImageWidth->Location = System::Drawing::Point(72, 24);
			this->lblImageWidth->Name = "lblImageWidth";
			this->lblImageWidth->Size = System::Drawing::Size(112, 23);
			this->lblImageWidth->TabIndex = 1;
			//
			// lblImageWidthLabel
			//
			this->lblImageWidthLabel->Location = System::Drawing::Point(8, 24);
			this->lblImageWidthLabel->Name = "lblImageWidthLabel";
			this->lblImageWidthLabel->Size = System::Drawing::Size(64, 23);
			this->lblImageWidthLabel->TabIndex = 0;
			this->lblImageWidthLabel->Text = "Width:";
			//
			// grpThumbnailInfo
			//
			this->grpThumbnailInfo->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpThumbnailInfo->Controls->Add(this->lblThumbnailFormat);
			this->grpThumbnailInfo->Controls->Add(this->lblThumbnailFormatLabel);
			this->grpThumbnailInfo->Controls->Add(this->lblThumbnailHeight);
			this->grpThumbnailInfo->Controls->Add(this->lblThumbnailHeightLabel);
			this->grpThumbnailInfo->Controls->Add(this->lblThumbnailWidth);
			this->grpThumbnailInfo->Controls->Add(this->lblThumbnailWidthLabel);
			this->grpThumbnailInfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpThumbnailInfo->Location = System::Drawing::Point(8, 376);
			this->grpThumbnailInfo->Name = "grpThumbnailInfo";
			this->grpThumbnailInfo->Size = System::Drawing::Size(192, 104);
			this->grpThumbnailInfo->TabIndex = 2;
			this->grpThumbnailInfo->TabStop = false;
			this->grpThumbnailInfo->Text = "Thumbnail Info:";
			//
			// lblThumbnailFormat
			//
			this->lblThumbnailFormat->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblThumbnailFormat->Location = System::Drawing::Point(72, 72);
			this->lblThumbnailFormat->Name = "lblThumbnailFormat";
			this->lblThumbnailFormat->Size = System::Drawing::Size(112, 23);
			this->lblThumbnailFormat->TabIndex = 5;
			//
			// lblThumbnailFormatLabel
			//
			this->lblThumbnailFormatLabel->Location = System::Drawing::Point(8, 72);
			this->lblThumbnailFormatLabel->Name = "lblThumbnailFormatLabel";
			this->lblThumbnailFormatLabel->Size = System::Drawing::Size(64, 23);
			this->lblThumbnailFormatLabel->TabIndex = 4;
			this->lblThumbnailFormatLabel->Text = "Format:";
			//
			// lblThumbnailHeight
			//
			this->lblThumbnailHeight->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblThumbnailHeight->Location = System::Drawing::Point(72, 48);
			this->lblThumbnailHeight->Name = "lblThumbnailHeight";
			this->lblThumbnailHeight->Size = System::Drawing::Size(112, 23);
			this->lblThumbnailHeight->TabIndex = 3;
			//
			// lblThumbnailHeightLabel
			//
			this->lblThumbnailHeightLabel->Location = System::Drawing::Point(8, 48);
			this->lblThumbnailHeightLabel->Name = "lblThumbnailHeightLabel";
			this->lblThumbnailHeightLabel->Size = System::Drawing::Size(64, 23);
			this->lblThumbnailHeightLabel->TabIndex = 2;
			this->lblThumbnailHeightLabel->Text = "Height:";
			//
			// lblThumbnailWidth
			//
			this->lblThumbnailWidth->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblThumbnailWidth->Location = System::Drawing::Point(72, 24);
			this->lblThumbnailWidth->Name = "lblThumbnailWidth";
			this->lblThumbnailWidth->Size = System::Drawing::Size(112, 23);
			this->lblThumbnailWidth->TabIndex = 1;
			//
			// lblThumbnailWidthLabel
			//
			this->lblThumbnailWidthLabel->Location = System::Drawing::Point(8, 24);
			this->lblThumbnailWidthLabel->Name = "lblThumbnailWidthLabel";
			this->lblThumbnailWidthLabel->Size = System::Drawing::Size(64, 23);
			this->lblThumbnailWidthLabel->TabIndex = 0;
			this->lblThumbnailWidthLabel->Text = "Width:";
			//
			// grpFileInfo
			//
			this->grpFileInfo->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpFileInfo->Controls->Add(this->lblFileSize);
			this->grpFileInfo->Controls->Add(this->lblFileSizeLabel);
			this->grpFileInfo->Controls->Add(this->lblFileVersion);
			this->grpFileInfo->Controls->Add(this->lblFileVersionLabel);
			this->grpFileInfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpFileInfo->Location = System::Drawing::Point(8, 8);
			this->grpFileInfo->Name = "grpFileInfo";
			this->grpFileInfo->Size = System::Drawing::Size(192, 80);
			this->grpFileInfo->TabIndex = 0;
			this->grpFileInfo->TabStop = false;
			this->grpFileInfo->Text = "File Info:";
			//
			// lblFileSize
			//
			this->lblFileSize->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblFileSize->Location = System::Drawing::Point(72, 48);
			this->lblFileSize->Name = "lblFileSize";
			this->lblFileSize->Size = System::Drawing::Size(112, 23);
			this->lblFileSize->TabIndex = 3;
			//
			// lblFileSizeLabel
			//
			this->lblFileSizeLabel->Location = System::Drawing::Point(8, 48);
			this->lblFileSizeLabel->Name = "lblFileSizeLabel";
			this->lblFileSizeLabel->Size = System::Drawing::Size(64, 23);
			this->lblFileSizeLabel->TabIndex = 2;
			this->lblFileSizeLabel->Text = "Size:";
			//
			// lblFileVersion
			//
			this->lblFileVersion->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblFileVersion->Location = System::Drawing::Point(72, 24);
			this->lblFileVersion->Name = "lblFileVersion";
			this->lblFileVersion->Size = System::Drawing::Size(112, 23);
			this->lblFileVersion->TabIndex = 1;
			//
			// lblFileVersionLabel
			//
			this->lblFileVersionLabel->Location = System::Drawing::Point(8, 24);
			this->lblFileVersionLabel->Name = "lblFileVersionLabel";
			this->lblFileVersionLabel->Size = System::Drawing::Size(64, 23);
			this->lblFileVersionLabel->TabIndex = 0;
			this->lblFileVersionLabel->Text = "Version:";
			//
			// tabResources
			//
			this->tabResources->Controls->Add(this->grpResources);
			this->tabResources->Controls->Add(this->grpResourceInfo);
			this->tabResources->Location = System::Drawing::Point(4, 22);
			this->tabResources->Name = "tabResources";
			this->tabResources->Size = System::Drawing::Size(208, 476);
			this->tabResources->TabIndex = 3;
			this->tabResources->Text = "Resources";
			//
			// grpResources
			//
			this->grpResources->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpResources->Controls->Add(this->treResources);
			this->grpResources->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpResources->Location = System::Drawing::Point(8, 72);
			this->grpResources->Name = "grpResources";
			this->grpResources->Size = System::Drawing::Size(192, 394);
			this->grpResources->TabIndex = 2;
			this->grpResources->TabStop = false;
			this->grpResources->Text = "Resources:";
			//
			// treResources
			//
			this->treResources->Anchor = (System::Windows::Forms::AnchorStyles)(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->treResources->ImageIndex = -1;
			this->treResources->Location = System::Drawing::Point(8, 16);
			this->treResources->Name = "treResources";
			this->treResources->SelectedImageIndex = -1;
			this->treResources->Size = System::Drawing::Size(176, 370);
			this->treResources->TabIndex = 0;
			//
			// grpResourceInfo
			//
			this->grpResourceInfo->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->grpResourceInfo->Controls->Add(this->lblResourceCount);
			this->grpResourceInfo->Controls->Add(this->lblResourceCountLabel);
			this->grpResourceInfo->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->grpResourceInfo->Location = System::Drawing::Point(8, 8);
			this->grpResourceInfo->Name = "grpResourceInfo";
			this->grpResourceInfo->Size = System::Drawing::Size(192, 56);
			this->grpResourceInfo->TabIndex = 1;
			this->grpResourceInfo->TabStop = false;
			this->grpResourceInfo->Text = "Resource Info:";
			//
			// lblResourceCount
			//
			this->lblResourceCount->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right);
			this->lblResourceCount->Location = System::Drawing::Point(72, 24);
			this->lblResourceCount->Name = "lblResourceCount";
			this->lblResourceCount->Size = System::Drawing::Size(112, 23);
			this->lblResourceCount->TabIndex = 1;
			//
			// lblResourceCountLabel
			//
			this->lblResourceCountLabel->Location = System::Drawing::Point(8, 24);
			this->lblResourceCountLabel->Name = "lblResourceCountLabel";
			this->lblResourceCountLabel->Size = System::Drawing::Size(64, 23);
			this->lblResourceCountLabel->TabIndex = 0;
			this->lblResourceCountLabel->Text = "Resources:";
			//
			// tmrAnimate
			//
			this->tmrAnimate->Interval = 42;
			this->tmrAnimate->Tick += gcnew System::EventHandler(this, &CVTFEdit::tmrAnimate_Tick);
			//
			// dlgSaveVTFFile
			//
			this->dlgSaveVTFFile->Filter = "VTF Files (*.vtf)|*.vtf";
			this->dlgSaveVTFFile->Title = "Save VTF File";
			//
			// dlgSaveVMTFile
			//
			this->dlgSaveVMTFile->Filter = "VMT Files (*.vmt)|*.vmt";
			this->dlgSaveVMTFile->Title = "Save VMT File";
			//
			// pnlMain
			//
			this->pnlMain->AllowDrop = true;
			this->pnlMain->AutoScroll = true;
			this->pnlMain->Controls->Add(this->picVTFFileBR);
			this->pnlMain->Controls->Add(this->picVTFFileBL);
			this->pnlMain->Controls->Add(this->picVTFFileTR);
			this->pnlMain->Controls->Add(this->picVTFFileTL);
			this->pnlMain->Controls->Add(this->txtVMTFile);
			this->pnlMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pnlMain->Location = System::Drawing::Point(235, 28);
			this->pnlMain->Name = "pnlMain";
			this->pnlMain->Size = System::Drawing::Size(517, 535);
			this->pnlMain->TabIndex = 2;
			this->pnlMain->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->pnlMain->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			//
			// picVTFFileBR
			//
			this->picVTFFileBR->ContextMenu = this->mnuVTFFile;
			this->picVTFFileBR->Location = System::Drawing::Point(32, 32);
			this->picVTFFileBR->Name = "picVTFFileBR";
			this->picVTFFileBR->Size = System::Drawing::Size(32, 32);
			this->picVTFFileBR->TabIndex = 4;
			this->picVTFFileBR->TabStop = false;
			this->picVTFFileBR->Visible = false;
			this->picVTFFileBR->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->picVTFFileBR->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->picVTFFileBR->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::picVTFFile_MouseMove);
			//
			// mnuVTFFile
			//
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__19 = gcnew array<System::Windows::Forms::MenuItem^>(6);
			__mcTemp__19[0] = this->btnVTFFileZoomIn;
			__mcTemp__19[1] = this->btnVTFFileZoomOut;
			__mcTemp__19[2] = this->btnVTFFileSpace1;
			__mcTemp__19[3] = this->btnVTFFileZoomReset;
			__mcTemp__19[4] = this->btnVTFFileSpace2;
			__mcTemp__19[5] = this->btnVTFFileCopy;
			this->mnuVTFFile->MenuItems->AddRange(__mcTemp__19);
			//
			// btnVTFFileZoomIn
			//
			this->btnVTFFileZoomIn->Index = 0;
			this->btnVTFFileZoomIn->Text = "Zoom &In";
			this->btnVTFFileZoomIn->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVTFFileZoomIn_Click);
			//
			// btnVTFFileZoomOut
			//
			this->btnVTFFileZoomOut->Index = 1;
			this->btnVTFFileZoomOut->Text = "Zoom &Out";
			this->btnVTFFileZoomOut->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVTFFileZoomOut_Click);
			//
			// btnVTFFileSpace1
			//
			this->btnVTFFileSpace1->Index = 2;
			this->btnVTFFileSpace1->Text = "-";
			//
			// btnVTFFileZoomReset
			//
			this->btnVTFFileZoomReset->Index = 3;
			this->btnVTFFileZoomReset->Text = "&Reset";
			this->btnVTFFileZoomReset->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVTFFileZoomReset_Click);
			//
			// btnVTFFileSpace2
			//
			this->btnVTFFileSpace2->Index = 4;
			this->btnVTFFileSpace2->Text = "-";
			//
			// btnVTFFileCopy
			//
			this->btnVTFFileCopy->Index = 5;
			this->btnVTFFileCopy->Text = "&Copy";
			this->btnVTFFileCopy->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVTFFileCopy_Click);
			//
			// picVTFFileBL
			//
			this->picVTFFileBL->ContextMenu = this->mnuVTFFile;
			this->picVTFFileBL->Location = System::Drawing::Point(0, 32);
			this->picVTFFileBL->Name = "picVTFFileBL";
			this->picVTFFileBL->Size = System::Drawing::Size(32, 32);
			this->picVTFFileBL->TabIndex = 3;
			this->picVTFFileBL->TabStop = false;
			this->picVTFFileBL->Visible = false;
			this->picVTFFileBL->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->picVTFFileBL->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->picVTFFileBL->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::picVTFFile_MouseMove);
			//
			// picVTFFileTR
			//
			this->picVTFFileTR->ContextMenu = this->mnuVTFFile;
			this->picVTFFileTR->Location = System::Drawing::Point(32, 0);
			this->picVTFFileTR->Name = "picVTFFileTR";
			this->picVTFFileTR->Size = System::Drawing::Size(32, 32);
			this->picVTFFileTR->TabIndex = 2;
			this->picVTFFileTR->TabStop = false;
			this->picVTFFileTR->Visible = false;
			this->picVTFFileTR->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->picVTFFileTR->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->picVTFFileTR->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::picVTFFile_MouseMove);
			//
			// picVTFFileTL
			//
			this->picVTFFileTL->ContextMenu = this->mnuVTFFile;
			this->picVTFFileTL->Location = System::Drawing::Point(0, 0);
			this->picVTFFileTL->Name = "picVTFFileTL";
			this->picVTFFileTL->Size = System::Drawing::Size(32, 32);
			this->picVTFFileTL->TabIndex = 0;
			this->picVTFFileTL->TabStop = false;
			this->picVTFFileTL->Visible = false;
			this->picVTFFileTL->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->picVTFFileTL->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);
			this->picVTFFileTL->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &CVTFEdit::picVTFFile_MouseMove);
			//
			// txtVMTFile
			//
			this->txtVMTFile->AcceptsTab = true;
			this->txtVMTFile->AllowDrop = true;
			this->txtVMTFile->ContextMenu = this->mnuVMTFile;
			//this->txtVMTFile->DetectUrls = false;
			this->txtVMTFile->Dock = System::Windows::Forms::DockStyle::Fill;
			this->txtVMTFile->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->txtVMTFile->Location = System::Drawing::Point(0, 0);
			this->txtVMTFile->Name = "txtVMTFile";
			this->txtVMTFile->Size = System::Drawing::Size(517, 535);
			this->txtVMTFile->TabIndex = 5;
			this->txtVMTFile->Text = "";
			this->txtVMTFile->Visible = false;
			this->txtVMTFile->WordWrap = false;
			this->txtVMTFile->LeftBracket = L'[';
			this->txtVMTFile->RightBracket = L']';
			this->txtVMTFile->LeftPadding = 17;
			this->txtVMTFile->DelayedTextChangedInterval = 1000;
			this->txtVMTFile->DelayedEventsInterval = 500;
			this->txtVMTFile->ShowFoldingLines = true;
			this->txtVMTFile->HighlightingRangeType = FastColoredTextBoxNS::HighlightingRangeType::VisibleRange;
			this->txtVMTFile->AddStyle( gcnew FastColoredTextBoxNS::MarkerStyle( gcnew System::Drawing::SolidBrush( System::Drawing::Color::FromArgb( 50, System::Drawing::Color::Gray ) ) ) );
			this->txtVMTFile->Font = gcnew System::Drawing::Font( "Courier New", 9.75f );
			this->txtVMTFile->TextChanged += gcnew System::EventHandler<FastColoredTextBoxNS::TextChangedEventArgs^>(this, &CVTFEdit::txtVMTFile_TextChanged);
			this->txtVMTFile->SelectionChanged += gcnew System::EventHandler(this, &CVTFEdit::txtVMTFile_SelectionChanged);
			auto popupMenu = gcnew FastColoredTextBoxNS::AutocompleteMenu( txtVMTFile );
			popupMenu->ForeColor = Color::Black;
			popupMenu->BackColor = Color::WhiteSmoke;
			popupMenu->SelectedColor = Color::CadetBlue;
			popupMenu->SearchPattern = R"([\$\%\w\.])";
			popupMenu->AllowTabKey = true;
			popupMenu->AlwaysShowTooltip = true;
			auto highlightCompleter = gcnew VMTSyntaxHighlighter( this->txtVMTFile, popupMenu );
			popupMenu->Items->SetAutocompleteItems( highlightCompleter );
			this->txtVMTFile->SyntaxHighlighter = highlightCompleter;
			//
			// mnuVMTFile
			//
			array<System::Windows::Forms::MenuItem^>^ __mcTemp__20 = gcnew array<System::Windows::Forms::MenuItem^>(8);
			__mcTemp__20[0] = this->btnVMTFileUndo;
			__mcTemp__20[1] = this->btnVMTFileSpace1;
			__mcTemp__20[2] = this->btnVMTFileCut;
			__mcTemp__20[3] = this->btnVMTFileCopy;
			__mcTemp__20[4] = this->btnVMTFilePaste;
			__mcTemp__20[5] = this->btnVMTFileDelete;
			__mcTemp__20[6] = this->btnVMTFileSpace2;
			__mcTemp__20[7] = this->btnVMTFileSelectAll;
			this->mnuVMTFile->MenuItems->AddRange(__mcTemp__20);
			//
			// btnVMTFileUndo
			//
			this->btnVMTFileUndo->Enabled = false;
			this->btnVMTFileUndo->Index = 0;
			this->btnVMTFileUndo->Text = "&Undo";
			this->btnVMTFileUndo->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileUndo_Click);
			//
			// btnVMTFileSpace1
			//
			this->btnVMTFileSpace1->Index = 1;
			this->btnVMTFileSpace1->Text = "-";
			//
			// btnVMTFileCut
			//
			this->btnVMTFileCut->Enabled = false;
			this->btnVMTFileCut->Index = 2;
			this->btnVMTFileCut->Text = "&Cut";
			this->btnVMTFileCut->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileCut_Click);
			//
			// btnVMTFileCopy
			//
			this->btnVMTFileCopy->Enabled = false;
			this->btnVMTFileCopy->Index = 3;
			this->btnVMTFileCopy->Text = "&Copy";
			this->btnVMTFileCopy->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileCopy_Click);
			//
			// btnVMTFilePaste
			//
			this->btnVMTFilePaste->Enabled = false;
			this->btnVMTFilePaste->Index = 4;
			this->btnVMTFilePaste->Text = "&Paste";
			this->btnVMTFilePaste->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFilePaste_Click);
			//
			// btnVMTFileDelete
			//
			this->btnVMTFileDelete->Enabled = false;
			this->btnVMTFileDelete->Index = 5;
			this->btnVMTFileDelete->Text = "&Delete";
			this->btnVMTFileDelete->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileDelete_Click);
			//
			// btnVMTFileSpace2
			//
			this->btnVMTFileSpace2->Index = 6;
			this->btnVMTFileSpace2->Text = "-";
			//
			// btnVMTFileSelectAll
			//
			this->btnVMTFileSelectAll->Enabled = false;
			this->btnVMTFileSelectAll->Index = 7;
			this->btnVMTFileSelectAll->Text = "Select &All";
			this->btnVMTFileSelectAll->Click += gcnew System::EventHandler(this, &CVTFEdit::btnVMTFileSelectAll_Click);
			//
			// dlgImportFile
			//
			this->dlgImportFile->Filter = "Supported Files (*.bmp;*.dds;*.gif;*.jpg;*.jpeg;*.png;*.tga)|*.bmp;*.dds;*.gif;*."
				"jpg;*.jpeg;*.png;*.tga|BMP Files (*.bmp)|*.bmp|DDS Files (*.dds)|*.dds|GIF Files"
				" (*.gif)|*.gif|JPEG Files (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Files (*.png)|*.png|TG"
				"A Files (*.tga)|*.tga|All Files (*.*)|*.*";
			this->dlgImportFile->Multiselect = true;
			this->dlgImportFile->Title = "Import File";
			//
			// dlgExportFile
			//
			this->dlgExportFile->Filter = "BMP Files (*.bmp)|*.bmp|JPEG Files (*.jpg;*.jpeg)|*.jpg;*.jpeg|PNG Files (*.png)|"
				"*.png|TGA Files (*.tga)|*.tga";
			this->dlgExportFile->FilterIndex = 4;
			this->dlgExportFile->Title = "Export File";
			//
			// barTool
			//
			array<System::Windows::Forms::ToolBarButton^>^ __mcTemp__22 = gcnew array<System::Windows::Forms::ToolBarButton^>(6);
			__mcTemp__22[0] = this->btnToolImport;
			__mcTemp__22[1] = this->btnToolOpen;
			__mcTemp__22[2] = this->btnToolSave;
			__mcTemp__22[3] = this->btnSeparator1;
			__mcTemp__22[4] = this->btnToolCopy;
			__mcTemp__22[5] = this->btnToolPaste;
			this->barTool->Buttons->AddRange(__mcTemp__22);
			this->barTool->DropDownArrows = true;
			this->barTool->ImageList = this->imgTool;
			this->barTool->Location = System::Drawing::Point(0, 0);
			this->barTool->Name = "barTool";
			this->barTool->ShowToolTips = true;
			this->barTool->Size = System::Drawing::Size(752, 28);
			this->barTool->TabIndex = 4;
			this->barTool->Wrappable = false;
			this->barTool->ButtonClick += gcnew System::Windows::Forms::ToolBarButtonClickEventHandler(this, &CVTFEdit::barTool_ButtonClick);
			//
			// btnToolImport
			//
			this->btnToolImport->ImageIndex = 0;
			this->btnToolImport->ToolTipText = "Import";
			//
			// btnToolOpen
			//
			this->btnToolOpen->ImageIndex = 1;
			this->btnToolOpen->ToolTipText = "Open";
			//
			// btnToolSave
			//
			this->btnToolSave->Enabled = false;
			this->btnToolSave->ImageIndex = 2;
			this->btnToolSave->ToolTipText = "Save";
			//
			// btnSeparator1
			//
			this->btnSeparator1->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			//
			// btnToolCopy
			//
			this->btnToolCopy->Enabled = false;
			this->btnToolCopy->ImageIndex = 3;
			this->btnToolCopy->ToolTipText = "Copy";
			//
			// btnToolPaste
			//
			this->btnToolPaste->Enabled = false;
			this->btnToolPaste->ImageIndex = 4;
			this->btnToolPaste->ToolTipText = "Paste";
			//
			// imgTool
			//
			this->imgTool->ColorDepth = System::Windows::Forms::ColorDepth::Depth24Bit;
			this->imgTool->ImageSize = System::Drawing::Size(16, 16);
			this->imgTool->ImageStream = (safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject("imgTool.ImageStream")));
			this->imgTool->TransparentColor = System::Drawing::Color::Fuchsia;
			//
			// splSidebar
			//
			this->splSidebar->BackColor = System::Drawing::SystemColors::Control;
			this->splSidebar->Location = System::Drawing::Point(232, 28);
			this->splSidebar->MinExtra = 96;
			this->splSidebar->MinSize = 96;
			this->splSidebar->Name = "splSidebar";
			this->splSidebar->Size = System::Drawing::Size(3, 535);
			this->splSidebar->TabIndex = 5;
			this->splSidebar->TabStop = false;
			this->splSidebar->SplitterMoved += gcnew System::Windows::Forms::SplitterEventHandler(this, &CVTFEdit::splSidebar_SplitterMoved);
			//
			// dlgExtractDirectoryItem
			//
			this->dlgExtractDirectoryItem->Description = "Extract directory item to:";
			//
			// CVTFEdit
			//
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(752, 585);
			this->Controls->Add(this->pnlMain);
			this->Controls->Add(this->splSidebar);
			this->Controls->Add(this->pnlSidebar);
			this->Controls->Add(this->barTool);
			this->Controls->Add(this->barStatus);
			this->Icon = (safe_cast<System::Drawing::Icon^>(resources->GetObject("$this.Icon")));
			this->Menu = this->mnuMain;
			this->Name = "CVTFEdit";
			this->Text = "VTFEdit";
			this->Resize += gcnew System::EventHandler(this, &CVTFEdit::CVTFEdit_Resize);
			this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &CVTFEdit::CVTFEdit_Closing);
			this->Load += gcnew System::EventHandler(this, &CVTFEdit::CVTFEdit_Load);
			this->Move += gcnew System::EventHandler(this, &CVTFEdit::CVTFEdit_Move);
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->pnlFileName))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->pnlInfo1))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->pnlInfo2))->EndInit();
			this->pnlSidebar->ResumeLayout(false);
			this->tabSidebar->ResumeLayout(false);
			this->tabFileSystem->ResumeLayout(false);
			this->grpGoto->ResumeLayout(false);
			this->grpFileSystem->ResumeLayout(false);
			this->tabImage->ResumeLayout(false);
			this->grpImage->ResumeLayout(false);
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->trkHDRGamma))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->trkHDRShift))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->trkHDRKey))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numSlice))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numMipmap))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFace))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numFrame))->EndInit();
			this->grpFlags->ResumeLayout(false);
			this->tabInfo->ResumeLayout(false);
			this->grpImageInfo->ResumeLayout(false);
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numImageBumpmapScale))->EndInit();
			(safe_cast<System::ComponentModel::ISupportInitialize^>(this->numImageStartFrame))->EndInit();
			this->grpThumbnailInfo->ResumeLayout(false);
			this->grpFileInfo->ResumeLayout(false);
			this->tabResources->ResumeLayout(false);
			this->grpResources->ResumeLayout(false);
			this->grpResourceInfo->ResumeLayout(false);
			this->pnlMain->ResumeLayout(false);
			this->ResumeLayout(false);

		}
		//
		// CVMTTreeNode
		// VMT node tree view class.
		//
		/*private: __gc class CVMTTreeNode : public System::Windows::Forms::TreeNode
		{
		public:
			CVMTTreeNode(VTFLib::Nodes::CVMTNode *Node) : System::Windows::Forms::TreeNode(new String(Node->GetName()))
			{
				if(Node->GetType() == NODE_TYPE_GROUP)
				{
					VTFLib::Nodes::CVMTGroupNode *Group = static_cast<VTFLib::Nodes::CVMTGroupNode *>(Node);
					for(vlUInt i = 0; i < Group->GetNodeCount(); i++)
					{
						this->Nodes->Add(new CVMTTreeNode(Group->GetNode(i)));
					}
				}
				else if(Node->GetType() == NODE_TYPE_STRING)
				{
					VTFLib::Nodes::CVMTStringNode *String = static_cast<VTFLib::Nodes::CVMTStringNode *>(Node);
					this->Nodes->Add(new System::Windows::Forms::TreeNode(new System::String(String->GetValue())));
				}
				else if(Node->GetType() == NODE_TYPE_INTEGER)
				{
					VTFLib::Nodes::CVMTIntegerNode *Integer = static_cast<VTFLib::Nodes::CVMTIntegerNode *>(Node);
					this->Nodes->Add(new System::Windows::Forms::TreeNode(Integer->GetValue().ToString()));
				}
				else if(Node->GetType() == NODE_TYPE_SINGLE)
				{
					VTFLib::Nodes::CVMTSingleNode *Single = static_cast<VTFLib::Nodes::CVMTSingleNode *>(Node);
					this->Nodes->Add(new System::Windows::Forms::TreeNode(Single->GetValue().ToString("0.00000000")));
				}
			}
		};*/

		//
		// CFileSystemTreeNode
		// File system tree node base class.
		//
		private: ref class CFileSystemTreeNode abstract : public System::Windows::Forms::TreeNode
		{
		protected:
			CVTFEdit^ VTFEdit;
			CDirectoryItemInfoManager^ DirectoryItemInfoManager;

		public:
			CFileSystemTreeNode(CVTFEdit^ VTFEdit, CDirectoryItemInfoManager^ DirectoryItemInfoManager)
			{
				this->VTFEdit = VTFEdit;
				this->DirectoryItemInfoManager = DirectoryItemInfoManager;
			}

		public:
			// Called when node is expanded.  Should build the node's children.
			virtual void BuildChildren() = 0;

			// Called after a node is collapsed.  Should change image index.
			virtual void AfterCollapse() = 0;

			// Called after a node is expanded.  Should change image index.
			virtual void AfterExpand() = 0;

			virtual property String^ ItemPath
			{
				String^ get() = 0;
			}
		};

		//
		// CDirectoryItemFileSystemTreeNode
		// A file system node implimentation for HLLib CDirectroyItem objects.
		//
		private: ref class CDirectoryItemFileSystemTreeNode : public CFileSystemTreeNode
		{
		private:
			HLLib::CPackage *Package;
			HLLib::CDirectoryItem *DirectoryItem;
			bool bTreeBuilt;

		public:
			CDirectoryItemFileSystemTreeNode(HLLib::CPackage *Package, HLLib::CDirectoryItem *DirectoryItem, CVTFEdit^ VTFEdit, CDirectoryItemInfoManager^ DirectoryItemInfoManager) : CFileSystemTreeNode(VTFEdit, DirectoryItemInfoManager)
			{
				this->Package = Package;
				this->DirectoryItem = DirectoryItem;

				if(this->DirectoryItem->GetType() == HL_ITEM_FOLDER)
				{
					this->bTreeBuilt = false;

					this->Text = gcnew String(DirectoryItem->GetName());

					this->ImageIndex = this->DirectoryItemInfoManager->GetFolderTypeInfo("Folder")->IconIndex;
					this->SelectedImageIndex = this->ImageIndex;

					// Add a dummy node so we can expand the node.
					this->Nodes->Add(gcnew System::Windows::Forms::TreeNode());
				}
				else
				{
					this->bTreeBuilt = true;

					this->Text = gcnew String(DirectoryItem->GetName());

					this->ImageIndex = this->DirectoryItemInfoManager->GetFileTypeInfo(gcnew String(DirectoryItem->GetName()))->IconIndex;
					this->SelectedImageIndex = this->ImageIndex;
				}
			}

		public:
			void BuildChildren() override
			{
				if(bTreeBuilt)
					return;

				// Remove dummy node.
				this->Nodes->Clear();

				if(this->DirectoryItem->GetType() == HL_ITEM_FOLDER)
				{
					HLLib::CDirectoryFolder *Folder = static_cast<HLLib::CDirectoryFolder *>(this->DirectoryItem);

					for(DWORD i = 0; i < Folder->GetCount(); i++)
					{
						this->Nodes->Add(gcnew CDirectoryItemFileSystemTreeNode(this->Package, Folder->GetItem(i), this->VTFEdit, this->DirectoryItemInfoManager));
					}
				}

				this->bTreeBuilt = true;
			}

			void AfterCollapse() override
			{
				this->ImageIndex--;
				this->SelectedImageIndex--;
			}

			void AfterExpand() override
			{
				this->ImageIndex++;
				this->SelectedImageIndex++;
			}

			//
			// Extract()
			// Extract the item, if it is a file, to sPath.
			//
			bool Extract(String^sPath)
			{
				if(this->DirectoryItem->GetType() == HL_ITEM_FILE)
				{
					char *cPath = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sPath)).ToPointer();

					hlBool bResult = static_cast<HLLib::CDirectoryFile *>(this->DirectoryItem)->Extract(cPath);

					System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cPath);

					return bResult != hlFalse;
				}

				return false;
			}

			property String^ ItemPath
			{
				String^ get() override
				{
					String^ sTempPath = System::IO::Path::GetTempPath();

					if ( this->Extract( sTempPath ) )
					{
						return String::Concat( sTempPath, gcnew String( this->DirectoryItem->GetName() ) );
					}

					return String::Empty;
				}
			}

			property HLDirectoryItemType DirectoryItemType
			{
				HLDirectoryItemType get() { return this->DirectoryItem->GetType(); }
			}
		};

		//
		// CPackageFileSystemTreeNode
		// A file system node implimentation for HLLib CPackage objects.
		// This node loads them on expansion.
		//
		private: ref class CPackageFileSystemTreeNode : public CFileSystemTreeNode
		{
		private:
			String^ sMoutPointPath;

		private:
			HLLib::CPackage *Package;
			bool bTreeBuilt;

		public:
			CPackageFileSystemTreeNode(System::IO::FileInfo^ FileInfo, CVTFEdit^ VTFEdit, CDirectoryItemInfoManager^ DirectoryItemInfoManager) : CFileSystemTreeNode(VTFEdit, DirectoryItemInfoManager)
			{
				this->Package = 0;
				this->bTreeBuilt = false;

				this->sMoutPointPath = FileInfo->FullName;
				this->Text = FileInfo->Name;

				this->ImageIndex = this->DirectoryItemInfoManager->GetFileTypeInfo(FileInfo->Name)->IconIndex;
				this->SelectedImageIndex = this->ImageIndex;

				// Add a dummy node so we can expand the node.
				this->Nodes->Add(gcnew System::Windows::Forms::TreeNode());
			}

			~CPackageFileSystemTreeNode()
			{
				delete this->Package;
			}

		public:
			void BuildChildren() override
			{
				if(bTreeBuilt)
					return;

				this->Mount();
			}

			void AfterCollapse() override {}
			void AfterExpand() override {}

			//
			// Mount()
			// Load the package.
			//
			bool Mount()
			{
				if(this->Package != 0)
					return true;

				// Remove dummy node.
				this->Nodes->Clear();

				char *cMountPointPath = (char *)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->sMoutPointPath)).ToPointer();

				HLPackageType ePackageType = hlGetPackageTypeFromName(cMountPointPath);

				if(ePackageType == HL_PACKAGE_NONE)
				{
					HLLib::Streams::CFileStream FileStream = HLLib::Streams::CFileStream(cMountPointPath);
					ePackageType = hlGetPackageTypeFromStream(&FileStream);
				}

				switch(ePackageType)
				{
				case HL_PACKAGE_BSP:
					this->Package = new HLLib::CBSPFile();
					break;
				case HL_PACKAGE_GCF:
					this->Package = new HLLib::CGCFFile();
					break;
				case HL_PACKAGE_NCF:
					this->Package = new HLLib::CNCFFile();
					break;
				case HL_PACKAGE_PAK:
					this->Package = new HLLib::CPAKFile();
					break;
				case HL_PACKAGE_VBSP:
					this->Package = new HLLib::CVBSPFile();
					break;
				case HL_PACKAGE_VPK:
					this->Package = new HLLib::CVPKFile();
					break;
				case HL_PACKAGE_WAD:
					this->Package = new HLLib::CWADFile();
					break;
				case HL_PACKAGE_XZP:
					this->Package = new HLLib::CXZPFile();
					break;
				case HL_PACKAGE_ZIP:
					this->Package = new HLLib::CZIPFile();
					break;
				case HL_PACKAGE_SGA:
					this->Package = new HLLib::CSGAFile();
					break;
				}

				hlUInt uiMode = HL_MODE_READ;
				uiMode |= !this->DirectoryItemInfoManager->FileMapping ? HL_MODE_NO_FILEMAPPING : 0;
				uiMode |= this->DirectoryItemInfoManager->VolatileAccess ? HL_MODE_VOLATILE : 0;

				if(this->Package != 0 && this->Package->Open(cMountPointPath, uiMode))
				{
					HLLib::CDirectoryFolder *Root = this->Package->GetRoot();

					for(hlUInt i = 0; i < Root->GetCount(); i++)
					{
						this->Nodes->Add(gcnew CDirectoryItemFileSystemTreeNode(this->Package, Root->GetItem(i), this->VTFEdit, this->DirectoryItemInfoManager));
					}
				}
				else
				{
					delete this->Package;
					this->Package = 0;
				}

				System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cMountPointPath);

				this->bTreeBuilt = true;

				return this->Package != 0;
			}

			property bool Mounted
			{
				bool get() { return this->Package != 0; }
			}

			virtual property String^ ItemPath
			{
				String^ get() override { return this->sMoutPointPath; };
			}
		};

		private: delegate void AddDirectoryTreeNodeEventHandler(System::Windows::Forms::TreeNode^ Node, System::IO::DirectoryInfo^ DirectoryInfo);

		private: void AddDirectoryTreeNode(System::Windows::Forms::TreeNode^ Node, System::IO::DirectoryInfo^ DirectoryInfo)
		{
			Node->Nodes->Add(gcnew CDirectoryFileSystemTreeNode(DirectoryInfo, this, this->DirectoryItemInfoManager));
		}

		private: delegate void AddFileTreeNodeEventHandler(System::Windows::Forms::TreeNode^ Node, System::IO::FileInfo^ FileInfo);

		private: void AddFileTreeNode(System::Windows::Forms::TreeNode^ Node, System::IO::FileInfo^ FileInfo)
		{
			Node->Nodes->Add(gcnew CDirectoryFileSystemTreeNode(FileInfo, this, this->DirectoryItemInfoManager));
		}

		private: delegate void AddPackageTreeNodeEventHandler(System::Windows::Forms::TreeNode^ Node, System::IO::FileInfo^ FileInfo);

		private: void AddPackageTreeNode(System::Windows::Forms::TreeNode^ Node, System::IO::FileInfo^ FileInfo)
		{
			Node->Nodes->Add(gcnew CPackageFileSystemTreeNode(FileInfo, this, this->DirectoryItemInfoManager));
		}

		//
		// CDirectoryFileSystemTreeNode
		// A file system node implimentation for Window's files and folders.
		//
		private: ref class CDirectoryFileSystemTreeNode : public CFileSystemTreeNode
		{
		private:
			static System::Text::RegularExpressions::Regex^ vpkRegex;
			HLDirectoryItemType eDirectoryItemType;
			String^sItemPath;

		private:
			System::IO::FileSystemWatcher^ Watcher;
			bool bTreeBuilt;

			static constexpr System::IO::FileAttributes ZeroAttribute = ( System::IO::FileAttributes )0;

			static CDirectoryFileSystemTreeNode()
			{
				vpkRegex = gcnew System::Text::RegularExpressions::Regex( R"X(_\d\d\d\.vpk)X" );
			}

		public:
			CDirectoryFileSystemTreeNode(System::IO::DirectoryInfo^ DirectoryInfo, CVTFEdit^ VTFEdit, CDirectoryItemInfoManager^ DirectoryItemInfoManager) : CFileSystemTreeNode(VTFEdit, DirectoryItemInfoManager)
			{
				this->bTreeBuilt = false;

				this->eDirectoryItemType = HL_ITEM_FOLDER;
				this->sItemPath = DirectoryInfo->FullName;
				this->Text = DirectoryInfo->Name;

				if(String::Compare(DirectoryInfo->Root->FullName, DirectoryInfo->FullName, true) == 0)
				{
					this->ImageIndex = this->DirectoryItemInfoManager->GetFolderTypeInfo(DirectoryInfo->FullName, DirectoryInfo->FullName)->IconIndex;
				}
				else
				{
					this->ImageIndex = this->DirectoryItemInfoManager->GetFolderTypeInfo("Folder")->IconIndex;
				}
				this->SelectedImageIndex = this->ImageIndex;

				// Add a dummy node so we can expand the node.
				this->Nodes->Add(gcnew System::Windows::Forms::TreeNode());
			}

			CDirectoryFileSystemTreeNode(System::IO::FileInfo^ FileInfo, CVTFEdit^ VTFEdit, CDirectoryItemInfoManager^ DirectoryItemInfoManager) : CFileSystemTreeNode(VTFEdit, DirectoryItemInfoManager)
			{
				this->bTreeBuilt = true;

				this->eDirectoryItemType = HL_ITEM_FILE;
				this->sItemPath = FileInfo->FullName;
				this->Text = FileInfo->Name;

				this->ImageIndex = this->DirectoryItemInfoManager->GetFileTypeInfo(FileInfo->Name)->IconIndex;
				this->SelectedImageIndex = this->ImageIndex;
			}

		public:
			void BuildChildren() override
			{
				if(bTreeBuilt)
					return;

				// Remove dummy node.
				this->Nodes->Clear();

				try
				{
					System::IO::DirectoryInfo^ DirectoryInfo = gcnew System::IO::DirectoryInfo(this->sItemPath);

					auto SubDirectoryInfos = DirectoryInfo->GetDirectories();

					for(int i = 0; i < SubDirectoryInfos->Length; i++)
					{
						System::IO::DirectoryInfo^ SubDirectoryInfo = SubDirectoryInfos[i];

						if ( ( SubDirectoryInfo->Attributes & ( System::IO::FileAttributes::Hidden | System::IO::FileAttributes::System ) ) == ZeroAttribute )
						{
							this->Nodes->Add(gcnew CDirectoryFileSystemTreeNode(SubDirectoryInfo, VTFEdit, this->DirectoryItemInfoManager));
						}
					}

					auto SubFileInfos = DirectoryInfo->GetFiles();

					for(int i = 0; i < SubFileInfos->Length; i++)
					{
						System::IO::FileInfo^ SubFileInfo = SubFileInfos[i];

						if ( ( SubFileInfo->Attributes & ( System::IO::FileAttributes::Hidden | System::IO::FileAttributes::System ) ) == ZeroAttribute )
						{
							const bool isVpk = String::Compare(SubFileInfo->Extension, ".vpk", true) == 0 && !vpkRegex->Match(SubFileInfo->Name)->Success;
							if(String::Compare(SubFileInfo->Extension, ".bsp", true) == 0 ||
								String::Compare(SubFileInfo->Extension, ".gcf", true) == 0 ||
								String::Compare(SubFileInfo->Extension, ".pak", true) == 0 ||
								String::Compare(SubFileInfo->Extension, ".wad", true) == 0 ||
								isVpk ||
								String::Compare(SubFileInfo->Extension, ".xzp", true) == 0)
							{
								this->Nodes->Add(gcnew CPackageFileSystemTreeNode(SubFileInfo, VTFEdit, this->DirectoryItemInfoManager));
							}
							else if ( !isVpk )
							{
								this->Nodes->Add(gcnew CDirectoryFileSystemTreeNode(SubFileInfo, VTFEdit, this->DirectoryItemInfoManager));
							}
						}
					}

					if (this->eDirectoryItemType == HL_ITEM_FOLDER)
					{
						this->Watcher = gcnew System::IO::FileSystemWatcher(this->sItemPath);
						this->Watcher->IncludeSubdirectories = false;
						//this->Watcher->NotifyFilter = System::IO::NotifyFilters::FileName | System::IO::NotifyFilters::DirectoryName;

						this->Watcher->Created += gcnew System::IO::FileSystemEventHandler(this, &CDirectoryFileSystemTreeNode::OnCreated);
						this->Watcher->Renamed += gcnew System::IO::RenamedEventHandler(this, &CDirectoryFileSystemTreeNode::OnRenamed);
						this->Watcher->Deleted += gcnew System::IO::FileSystemEventHandler(this, &CDirectoryFileSystemTreeNode::OnDeleted);

						this->Watcher->EnableRaisingEvents = true;
					}
				}
				catch(Exception^)
				{

				}

				this->bTreeBuilt = true;
			}
		protected:
			void OnCreated(Object^ s, System::IO::FileSystemEventArgs^ e)
			{
				if(System::IO::Directory::Exists(e->FullPath))
				{
					auto SubDirectoryInfo = gcnew System::IO::DirectoryInfo(e->FullPath);

					if ( ( SubDirectoryInfo->Attributes & ( System::IO::FileAttributes::Hidden | System::IO::FileAttributes::System ) ) == ZeroAttribute )
					{
						array<Object^>^ oArgumentst = gcnew array<Object^>( 2 );
						oArgumentst[0] = this;
						oArgumentst[1] = SubDirectoryInfo;

						VTFEdit->Invoke(gcnew AddDirectoryTreeNodeEventHandler(this->VTFEdit, &CVTFEdit::AddDirectoryTreeNode), oArgumentst);
					}
				}
				else if(System::IO::File::Exists(e->FullPath))
				{
					System::IO::FileInfo^ SubFileInfo = gcnew System::IO::FileInfo(e->FullPath);

					if ( ( SubFileInfo->Attributes & ( System::IO::FileAttributes::Hidden | System::IO::FileAttributes::System ) ) == ZeroAttribute )
					{
						const bool isVpk = String::Compare( SubFileInfo->Extension, ".vpk", true ) == 0 && !vpkRegex->Match( SubFileInfo->Name )->Success;
						if( String::Compare(SubFileInfo->Extension, ".bsp", true) == 0 ||
							String::Compare(SubFileInfo->Extension, ".gcf", true) == 0 ||
							String::Compare(SubFileInfo->Extension, ".pak", true) == 0 ||
							isVpk ||
							String::Compare(SubFileInfo->Extension, ".wad", true) == 0)
						{
							array<Object^>^ oArgumentst = gcnew array<Object^>( 2 );
							oArgumentst[0] = this;
							oArgumentst[1] = SubFileInfo;

							VTFEdit->Invoke(gcnew AddPackageTreeNodeEventHandler(this->VTFEdit, &CVTFEdit::AddPackageTreeNode), oArgumentst);
						}
						else if ( !isVpk )
						{
							array<Object^>^ oArgumentst = gcnew array<Object^>( 2 );
							oArgumentst[0] = this;
							oArgumentst[1] = SubFileInfo;

							VTFEdit->Invoke(gcnew AddFileTreeNodeEventHandler(this->VTFEdit, &CVTFEdit::AddFileTreeNode), oArgumentst);
						}
					}
				}
			}

			void OnRenamed(Object^ s, System::IO::RenamedEventArgs^ e)
			{
				for(int i = 0; i < this->Nodes->Count; i++)
				{
					System::Windows::Forms::TreeNode^ Node = this->Nodes[i];
					if(String::Compare(Node->Text, e->OldName) == 0)
					{
						this->Nodes->RemoveAt(i);

						if(System::IO::Directory::Exists(e->FullPath))
						{
							System::IO::DirectoryInfo^ SubDirectoryInfo = gcnew System::IO::DirectoryInfo(e->FullPath);

							if ( ( SubDirectoryInfo->Attributes & ( System::IO::FileAttributes::Hidden | System::IO::FileAttributes::System ) ) == ZeroAttribute )
							{
								array<Object^>^ oArgumentst = gcnew array<Object^>( 2 );
								oArgumentst[0] = this;
								oArgumentst[1] = SubDirectoryInfo;

								VTFEdit->Invoke(gcnew AddDirectoryTreeNodeEventHandler(this->VTFEdit, &CVTFEdit::AddDirectoryTreeNode), oArgumentst);
							}
						}
						else if(System::IO::File::Exists(e->FullPath))
						{
							System::IO::FileInfo^ SubFileInfo = gcnew System::IO::FileInfo(e->FullPath);

							if ( ( SubFileInfo->Attributes & ( System::IO::FileAttributes::Hidden | System::IO::FileAttributes::System ) ) == ZeroAttribute )
							{
								const bool isVpk = String::Compare( SubFileInfo->Extension, ".vpk", true ) == 0 && !vpkRegex->Match( SubFileInfo->Name )->Success;
								if( String::Compare(SubFileInfo->Extension, ".bsp", true) == 0 ||
									String::Compare(SubFileInfo->Extension, ".gcf", true) == 0 ||
									String::Compare(SubFileInfo->Extension, ".pak", true) == 0 ||
									isVpk ||
									String::Compare(SubFileInfo->Extension, ".wad", true) == 0)
								{
									array<Object^>^ oArgumentst = gcnew array<Object^>( 2 );
									oArgumentst[0] = this;
									oArgumentst[1] = SubFileInfo;

									VTFEdit->Invoke(gcnew AddPackageTreeNodeEventHandler(this->VTFEdit, &CVTFEdit::AddPackageTreeNode), oArgumentst);
								}
								else if ( !isVpk )
								{
									array<Object^>^ oArgumentst = gcnew array<Object^>( 2 );
									oArgumentst[0] = this;
									oArgumentst[1] = SubFileInfo;

									VTFEdit->Invoke(gcnew AddFileTreeNodeEventHandler(this->VTFEdit, &CVTFEdit::AddFileTreeNode), oArgumentst);
								}
							}
						}

						break;
					}
				}
			}

			void OnDeleted(Object^ s, System::IO::FileSystemEventArgs^ e)
			{
				for(int i = 0; i < this->Nodes->Count; i++)
				{
					System::Windows::Forms::TreeNode^ Node = this->Nodes[i];
					if(String::Compare(Node->Text, e->Name) == 0)
					{
						this->Nodes->RemoveAt(i);
						break;
					}
				}
			}

		public:
			void AfterCollapse() override
			{
				this->ImageIndex--;
				this->SelectedImageIndex--;
			}

			void AfterExpand() override
			{
				this->ImageIndex++;
				this->SelectedImageIndex++;
			}

			property String^ ItemPath
			{
				String^ get() override { return this->sItemPath; }
			}

			property HLDirectoryItemType DirectoryItemType
			{
				HLDirectoryItemType get() { return this->eDirectoryItemType; }
			}
		};

		//
		// Form events.
		//

		public: property System::String^ FileName
		{
			String^ get() { return this->sFileName; }
			void set(String^ sFileName)
			{
				this->sFileName = sFileName;
				this->pnlFileName->Text = this->sFileName;

				if(sFileName)
				{
					if(sFileName->LastIndexOf('\\') != -1)
					{
						this->Text = String::Concat(sFileName->Substring(sFileName->LastIndexOf('\\') + 1), " - ", Application::ProductName);
					}
					else
					{
						this->Text = String::Concat(sFileName, " - ", Application::ProductName);
					}
				}
				else
				{
					if(this->VTFFile)
					{
						this->Text = "untitled.vtf - ", Application::ProductName;
					}
					else if(this->bVMTFile)
					{
						this->Text = "untitled.vmt - ", Application::ProductName;
					}
					else
					{
						this->Text = Application::ProductName;
					}
				}
			}
		}

		private: String^ GetAppDataFolder()
		{
			String^ pDirectory = Environment::GetFolderPath(Environment::SpecialFolder::LocalApplicationData);
			pDirectory = IO::Path::Combine(pDirectory, "Nem's Tools", Application::ProductName);

			if(!IO::Directory::Exists(pDirectory))
			{
				try
				{
					IO::Directory::CreateDirectory(pDirectory);
				}
				catch(Exception^ )
				{
				}
			}

			return pDirectory;
		}

		private: System::Void CVTFEdit_Load(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->picVTFFileTL->AllowDrop = true;
			this->picVTFFileTR->AllowDrop = true;
			this->picVTFFileBL->AllowDrop = true;
			this->picVTFFileBR->AllowDrop = true;

			this->txtVMTFile->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragEnter);
			this->txtVMTFile->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &CVTFEdit::Control_DragDrop);

			// "Hide" the tab pages.
			if(this->tabSidebar->TabPages->Contains(this->tabResources))
			{
				this->tabSidebar->TabPages->Remove(this->tabResources);
			}
			if(this->tabSidebar->TabPages->Contains(this->tabInfo))
			{
				this->tabSidebar->TabPages->Remove(this->tabInfo);
			}
			if(this->tabSidebar->TabPages->Contains(this->tabImage))
			{
				this->tabSidebar->TabPages->Remove(this->tabImage);
			}

			this->numImageBumpmapScale->DecimalPlaces = 2;
			this->numImageBumpmapScale->Increment = (Decimal)0.01;
			this->numImageBumpmapScale->Minimum = -100;
			this->numImageBumpmapScale->Maximum = 100;
			this->numImageBumpmapScale->Value = 0;
			this->btnHDRReset_Click(this, System::EventArgs::Empty);

			// Restore options.
			this->BackupForm();
			bool bHasConfig = false;
			String^pNewConfigFile = IO::Path::Combine(GetAppDataFolder(), String::Concat(Application::ProductName, ".ini"));
			String^pOldConfigFile = IO::Path::Combine(Application::StartupPath, String::Concat(Application::ProductName, ".ini"));
			if(IO::File::Exists(pNewConfigFile))
			{
				bHasConfig = this->ReadConfigFile(pNewConfigFile);
			}
			else if(IO::File::Exists(pOldConfigFile))
			{
				bHasConfig = this->ReadConfigFile(pOldConfigFile);
			}
			this->RestoreForm();

			this->btnFileMapping->Checked = this->DirectoryItemInfoManager->FileMapping;
			this->btnVolatileAccess->Checked = this->DirectoryItemInfoManager->VolatileAccess;

			// If we were pased a file, load it.
			array<String^>^ CommandLineArgs = System::Environment::GetCommandLineArgs();

			if(CommandLineArgs->Length >= 2)
			{
				String^sFilePath = CommandLineArgs[1];

				if(System::IO::File::Exists(sFilePath))
				{
					if(sFilePath->ToLower()->EndsWith(".vtf") || sFilePath->ToLower()->EndsWith(".vmt"))
					{
						this->Open(sFilePath, false);
					}
					else
					{
						array<String^>^ sFileNames = gcnew array<String^>(1);
						sFileNames[0] = sFilePath;
						this->Import(sFileNames);
					}
				}
			}

			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				// Set intitial clipboard state.
				this->btnToolPaste->Enabled = System::Windows::Forms::Clipboard::GetDataObject()->GetDataPresent(System::Windows::Forms::DataFormats::Bitmap);
				this->btnPaste->Enabled = this->btnToolPaste->Enabled;

				// Add ourselves to clipboard notification chain.
				if(this->hWndNewViewer == 0)
				{
					this->hWndNewViewer = SetClipboardViewer((HWND)this->Handle.ToPointer());
				}
			}
			else
			{	// Set intitial clipboard state.
				this->btnToolPaste->Enabled = true;
				this->btnPaste->Enabled = this->btnToolPaste->Enabled;
			}

			// Populate drive list.
			array<String^>^ LogicalDrives = System::Environment::GetLogicalDrives();

			for(int i = 0; i < LogicalDrives->Length; i++)
			{
				try
				{
					this->treFileSystem->Nodes->Add(gcnew CDirectoryFileSystemTreeNode(gcnew System::IO::DirectoryInfo(LogicalDrives[i]), this, this->DirectoryItemInfoManager));
				}
				catch(Exception^)
				{

				}
			}

			if(!bHasConfig)
			{
				Microsoft::Win32::RegistryKey^ Steam = Microsoft::Win32::Registry::CurrentUser->OpenSubKey("Software\\Valve\\Steam");

				if(Steam != nullptr)
				{
					System::IO::DirectoryInfo^ DirectoryInfo;
					Object^ oSourceModInstallPath = Steam->GetValue("SourceModInstallPath");

					if(oSourceModInstallPath->GetType()->Equals(String::typeid))
					{
						String^sSourceModInstallPath = safe_cast<String^>(oSourceModInstallPath);
						if(sSourceModInstallPath->LastIndexOf("\\") != -1)
						{
							try
							{
								DirectoryInfo = gcnew System::IO::DirectoryInfo(sSourceModInstallPath->Substring(0, sSourceModInstallPath->LastIndexOf("\\")));
								this->cboGoto->Items->Add(DirectoryInfo->FullName);
							}
							catch(Exception^)
							{

							}
							//this->cboGoto->Items->Add(sSourceModInstallPath);
						}
					}

					Steam->Close();
				}
			}
		}

		private: System::Void CVTFEdit_Closing(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
		{
			//Causes crah when more than once instance of VTFEdit is open.  WM_DESTROY is all that is needed?
			//ChangeClipboardChain((HWND)this->Handle.ToPointer(), this->hWndNewViewer);

			String^ pNewConfigFile = IO::Path::Combine(GetAppDataFolder(), String::Concat(Application::ProductName, ".ini"));
			String^ pOldConfigFile = IO::Path::Combine(Application::StartupPath, String::Concat(Application::ProductName, ".ini"));
			if(this->WriteConfigFile(pNewConfigFile))
			{
				if(IO::File::Exists(pOldConfigFile))
				{
					try
					{
						IO::File::Delete(pOldConfigFile);
					}
					catch(Exception^)
					{
					}
				}
			}
		}

		private: System::Void CVTFEdit_Move(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->BackupForm();
		}

		private: System::Void CVTFEdit_Resize(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->BackupForm();
		}

		private: System::Void splSidebar_SplitterMoved(System::Object ^  sender, System::Windows::Forms::SplitterEventArgs ^  e)
		{
			this->BackupForm();
		}

		private: void BackupForm()
		{
			if(!this->bFormRestoring && this->WindowState != FormWindowState::Minimized)
			{
				if(this->WindowState != FormWindowState::Maximized)
				{
					this->FormSaveLocation = Location;
					this->FormSaveSize = Size;
					this->iFormSaveSidebarSplitPosition = this->splSidebar->SplitPosition;
				}
				this->FormSaveWindowState = this->WindowState;
			}
		}

		private: void RestoreForm()
		{
			this->bFormRestoring = true;
			try
			{
				this->Location = this->FormSaveLocation;
				this->Size = this->FormSaveSize;
				this->WindowState = this->FormSaveWindowState;
				this->splSidebar->SplitPosition = this->iFormSaveSidebarSplitPosition;
			}
			catch(Exception^)
			{

			}
			this->bFormRestoring = false;
		}

		//
		// WndProc()
		// Override default WndProc to process clipboard messages.
		//
		protected: System::Void WndProc(Message% e) override
		{
			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				switch(e.Msg)
				{
				case WM_CHANGECBCHAIN:
					// Store the changed handle of the next item in the clipboard chain.
					this->hWndNewViewer = (HWND)e.LParam.ToPointer();

					if(this->hWndNewViewer != 0)
					{
						::SendMessage(this->hWndNewViewer, e.Msg, (WPARAM)e.WParam.ToPointer(), (LPARAM)e.LParam.ToPointer());
					}

					// We have processed this message.
					e.Result = System::IntPtr::Zero;
					break;
				case WM_DRAWCLIPBOARD:
				{
					try
					{
						this->btnPaste->Enabled = System::Windows::Forms::Clipboard::GetDataObject()->GetDataPresent(System::Windows::Forms::DataFormats::Bitmap);
					}
					catch(Exception^)
					{
						this->btnPaste->Enabled = false;
					}
					this->btnToolPaste->Enabled = this->btnPaste->Enabled;

					this->btnVMTFilePaste->Enabled = false;
					try
					{
						array<String^>^ Formats = System::Windows::Forms::Clipboard::GetDataObject()->GetFormats();
						for(int i = 0; i < Formats->Length; i++)
						{
							if(System::Windows::Forms::DataFormats::GetFormat(Formats[i])->Name->Equals("Text"))
							{
								this->btnVMTFilePaste->Enabled = true;
								break;
							}
						}
					}
					catch(Exception^)
					{
						this->btnVMTFilePaste->Enabled = false;
					}

					// Pass the message on.
					if(this->hWndNewViewer != 0)
					{
						::SendMessage(this->hWndNewViewer, e.Msg, (WPARAM)e.WParam.ToPointer(), (LPARAM)e.LParam.ToPointer());
					}

					// We have processed this message.
					e.Result = System::IntPtr::Zero;
					break;
				}
				case WM_DESTROY:
					ChangeClipboardChain((HWND)this->Handle.ToPointer(), this->hWndNewViewer);

					__super::WndProc(e);
					break;
				default:
					__super::WndProc(e);
					break;
				}
			}
			else
			{
				__super::WndProc(e);
			}
		}

		//
		// VTF and VMT routines.
		//

		private: void UpdateVTFFile()
		{
			if(this->VTFFile == 0)
				return;

			static bool bUpdating = false;
			if(bUpdating)
				return;

			bUpdating = true;

			this->picVTFFileTL->Visible = true;
			this->picVTFFileTR->Visible = this->btnTile->Checked;
			this->picVTFFileBL->Visible = this->btnTile->Checked;
			this->picVTFFileBR->Visible = this->btnTile->Checked;

			this->picVTFFileTL->Image = nullptr;
			this->picVTFFileTR->Image = nullptr;
			this->picVTFFileBL->Image = nullptr;
			this->picVTFFileBR->Image = nullptr;

			delete []this->ucImageData;
			this->ucImageData = 0;

			vlUInt uiFrame = (vlUInt)Convert::ToUInt32(this->numFrame->Value);
			vlUInt uiFace = (vlUInt)Convert::ToUInt32(this->numFace->Value);
			vlUInt uiSlice = (vlUInt)Convert::ToUInt32(this->numSlice->Value);
			vlUInt uiMipmap = (vlUInt)Convert::ToUInt32(this->numMipmap->Value);
			vlSingle sHDRKey = (vlSingle)Convert::ToSingle(this->trkHDRKey->Value) / 100.0f;
			vlSingle sHDRShift = (vlSingle)Convert::ToSingle(this->trkHDRShift->Value) / 100.0f;
			vlSingle sHDRGamma = (vlSingle)Convert::ToSingle(this->trkHDRGamma->Value) / 100.0f;

			vlUInt uiWidth = 0;
			vlUInt uiHeight = 0;
			vlUInt uiDepth = 0;

			vlUInt uiScaledWidth = 0;
			vlUInt uiScaledHeight = 0;

			vlByte *lpBuffer = 0;
			vlUInt uiBufferSize = 0;

			this->VTFFile->ComputeMipmapDimensions(this->VTFFile->GetWidth(), this->VTFFile->GetHeight(), this->VTFFile->GetDepth(), uiMipmap, uiWidth, uiHeight, uiDepth);

			if(uiSlice >= uiDepth)
				uiSlice = uiDepth - 1;

			this->numSlice->Value = uiSlice;
			this->numSlice->Maximum = uiDepth;

			// Don't let the rescaled image get larger than 4096x4096.  .NET crashes...
			while(true)
			{
				uiScaledWidth = (vlUInt)((float)uiWidth * this->fImageScale);
				uiScaledHeight = (vlUInt)((float)uiHeight * this->fImageScale);

				if(uiScaledWidth <= 4096 && uiScaledHeight <= 4096)
				{
					break;
				}

				this->fImageScale *= 0.5f;
			}

			// Don't let it get smaller than 1 either.
			if(uiScaledWidth < 1)
				uiScaledWidth = 1;

			if(uiScaledHeight < 1)
				uiScaledHeight = 1;

			// Allocate buffer to decode image data to.
			uiBufferSize = this->VTFFile->ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888);

			lpBuffer = new vlByte[uiBufferSize];

			// Decode image data.
			vlSetFloat(VTFLIB_FP16_HDR_KEY, sHDRKey);
			vlSetFloat(VTFLIB_FP16_HDR_SHIFT, sHDRShift);
			vlSetFloat(VTFLIB_FP16_HDR_GAMMA, sHDRGamma);
			this->VTFFile->ConvertToRGBA8888(this->VTFFile->GetData(uiFrame, uiFace, uiSlice, uiMipmap), lpBuffer, uiWidth, uiHeight, this->VTFFile->GetFormat());

			float fInverseImageScale = 1.0f / this->fImageScale;

			vlUInt uiScaledStride = (uiScaledWidth + 3) / 4 * 4;

			// Allocate buffer for bitmap image data.
			this->ucImageData = new unsigned char[uiScaledStride * uiScaledHeight * 3];

			vlUInt uiR, uiG, uiB;

			// Pick R, G, B and A indicies.
			if(this->btnChannelRGB->Checked)
			{
				uiR = 0;
				uiG = 1;
				uiB = 2;
			}
			else if(this->btnChannelR->Checked)
			{
				uiR = 0;
				uiG = 0;
				uiB = 0;
			}
			else if(this->btnChannelG->Checked)
			{
				uiR = 1;
				uiG = 1;
				uiB = 1;
			}
			else if(this->btnChannelB->Checked)
			{
				uiR = 2;
				uiG = 2;
				uiB = 2;
			}
			else if(this->btnChannelA->Checked)
			{
				uiR = 3;
				uiG = 3;
				uiB = 3;
			}

			if(this->btnMask->Checked)// && (this->VTFFile->GetFlag(TEXTUREFLAGS_ONEBITALPHA) || this->VTFFile->GetFlag(TEXTUREFLAGS_EIGHTBITALPHA)))
			{
				// Generate checkered mask and alpha blend texture with it.
				for(vlUInt i = 0; i < uiScaledWidth; i++)
				{
					for(vlUInt j = 0; j < uiScaledHeight; j++)
					{
						vlUInt uiSrcIndex = ((vlUInt)((float)i * fInverseImageScale) + (vlUInt)((float)j * fInverseImageScale) * uiWidth) * 4;
						vlUInt uiDstIndex = (i + j * uiScaledStride) * 3;

						float fAlpha = (float)lpBuffer[uiSrcIndex + 3] / (float)255.0f;
						float fOneMinusAlpha = 1.0f - fAlpha;
						float fBlend = (i / 8 % 2 == j / 8 % 2) ? 255.0f : 191.25f;	// Blend color.

						this->ucImageData[uiDstIndex + 2] = (unsigned char)(fAlpha * (float)lpBuffer[uiSrcIndex + uiR] + fOneMinusAlpha * fBlend);
						this->ucImageData[uiDstIndex + 1] = (unsigned char)(fAlpha * (float)lpBuffer[uiSrcIndex + uiG] + fOneMinusAlpha * fBlend);
						this->ucImageData[uiDstIndex + 0] = (unsigned char)(fAlpha * (float)lpBuffer[uiSrcIndex + uiB] + fOneMinusAlpha * fBlend);
					}
				}
			}
			else
			{
				// Don't generate checkered mask.
				for(vlUInt i = 0; i < uiScaledWidth; i++)
				{
					for(vlUInt j = 0; j < uiScaledHeight; j++)
					{
						vlUInt uiSrcIndex = ((vlUInt)((float)i * fInverseImageScale) + (vlUInt)((float)j * fInverseImageScale) * uiWidth) * 4;
						vlUInt uiDstIndex = (i + j * uiScaledStride) * 3;

						this->ucImageData[uiDstIndex + 2] = lpBuffer[uiSrcIndex + uiR];
						this->ucImageData[uiDstIndex + 1] = lpBuffer[uiSrcIndex + uiG];
						this->ucImageData[uiDstIndex + 0] = lpBuffer[uiSrcIndex + uiB];
					}
				}
			}

			delete []lpBuffer;

			this->picVTFFileTL->Size = System::Drawing::Size(uiScaledWidth, uiScaledHeight);
			this->picVTFFileTL->Image = gcnew System::Drawing::Bitmap(uiScaledWidth, uiScaledHeight, uiScaledStride * 3, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (IntPtr)this->ucImageData);

			this->picVTFFileTL->Visible = true;

			if(this->btnTile->Checked)
			{
				this->picVTFFileTR->Location = System::Drawing::Point(this->picVTFFileTL->Location.X + uiScaledWidth, this->picVTFFileTL->Location.Y);
				this->picVTFFileTR->Size = System::Drawing::Size(uiScaledWidth, uiScaledHeight);
				this->picVTFFileTR->Image = gcnew System::Drawing::Bitmap(uiScaledWidth, uiScaledHeight, uiScaledStride * 3, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (IntPtr)this->ucImageData);

				this->picVTFFileBL->Location = System::Drawing::Point(this->picVTFFileTL->Location.X, this->picVTFFileTL->Location.Y + uiScaledHeight);
				this->picVTFFileBL->Size = System::Drawing::Size(uiScaledWidth, uiScaledHeight);
				this->picVTFFileBL->Image = gcnew System::Drawing::Bitmap(uiScaledWidth, uiScaledHeight, uiScaledStride * 3, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (IntPtr)this->ucImageData);

				this->picVTFFileBR->Location = System::Drawing::Point(this->picVTFFileTL->Location.X + uiScaledWidth, this->picVTFFileTL->Location.Y + uiScaledHeight);
				this->picVTFFileBR->Size = System::Drawing::Size(uiScaledWidth, uiScaledHeight);
				this->picVTFFileBR->Image = gcnew System::Drawing::Bitmap(uiScaledWidth, uiScaledHeight, uiScaledStride * 3, System::Drawing::Imaging::PixelFormat::Format24bppRgb, (IntPtr)this->ucImageData);

				this->picVTFFileTR->Visible = true;
				this->picVTFFileBL->Visible = true;
				this->picVTFFileBR->Visible = true;
			}

			this->pnlInfo1->Text = String::Concat((this->fImageScale * 100.0f).ToString(), "%");

			bUpdating = false;
		}

		//private: void UpdateVTFFileScale()
		//{
		//	if(this->VTFFile == 0)
		//		return;

		//	vlUInt uiMipmap = (vlUInt)Convert::ToUInt32(this->numMipmap->Value);

		//	vlUInt uiWidth = 0;
		//	vlUInt uiHeight = 0;

		//	this->VTFFile->ComputeMipmapDimensions(this->VTFFile->GetWidth(), this->VTFFile->GetHeight(), uiMipmap, uiWidth, uiHeight);

		//	while(true)
		//	{
		//		if((int)((float)uiWidth * this->fImageScale) > 4096 || (int)((float)uiHeight * this->fImageScale) > 4096)
		//		{
		//			this->fImageScale *= 0.5f;
		//		}
		//		else
		//		{
		//			break;
		//		}
		//	}

		//	this->picVTFFile->Size = System::Drawing::Size((int)((float)uiWidth * this->fImageScale), (int)((float)uiHeight * this->fImageScale));
		//}

		private: void SetVTFFile(VTFLib::CVTFFile *VTFFile)
		{
			this->numFrame->Value = 0;
			this->numFace->Value = 0;
			this->numSlice->Value = 0;
			this->numMipmap->Value = 0;

			this->numFrame->Maximum = VTFFile->GetFrameCount() - 1;
			this->numFace->Maximum = VTFFile->GetFaceCount() - 1;
			this->numSlice->Maximum = VTFFile->GetDepth() - 1;
			this->numMipmap->Maximum = VTFFile->GetMipmapCount() - 1;

			if(VTFFile->GetStartFrame() < VTFFile->GetFrameCount())
			{
				this->numFrame->Value = VTFFile->GetStartFrame();
			}

			if(VTFFile->GetFrameCount() > 1)
			{
				this->btnAnimate->Enabled = true;
			}

			if(VTFFile->GetFormat() == IMAGE_FORMAT_RGBA16161616F)
			{
				this->trkHDRKey->Enabled = true;
				this->trkHDRShift->Enabled = true;
				this->trkHDRGamma->Enabled = true;
			}

			vlUInt uiFlags = VTFFile->GetFlags();

			this->lstFlags->BeginUpdate();
			this->lstFlags->Items->Clear();

			#pragma warning(disable: 4800)
			this->lstFlags->Items->Add("Point Sample", uiFlags & TEXTUREFLAGS_POINTSAMPLE);
			this->lstFlags->Items->Add("Trilinear", uiFlags & TEXTUREFLAGS_TRILINEAR);
			this->lstFlags->Items->Add("Clamp ", uiFlags & TEXTUREFLAGS_CLAMPS);
			this->lstFlags->Items->Add("Clamp T", uiFlags & TEXTUREFLAGS_CLAMPT);
			this->lstFlags->Items->Add("Anisotropic", uiFlags & TEXTUREFLAGS_ANISOTROPIC);
			this->lstFlags->Items->Add("Hint DXT5", uiFlags & TEXTUREFLAGS_HINT_DXT5);
			this->lstFlags->Items->Add("SRGB", uiFlags & TEXTUREFLAGS_SRGB);
			this->lstFlags->Items->Add("Normal Map", uiFlags & TEXTUREFLAGS_NORMAL);
			this->lstFlags->Items->Add("No Mipmap", uiFlags & TEXTUREFLAGS_NOMIP);
			this->lstFlags->Items->Add("No Level Of Detail", uiFlags & TEXTUREFLAGS_NOLOD);
			this->lstFlags->Items->Add("No Minimum Mipmap", uiFlags & TEXTUREFLAGS_MINMIP);
			this->lstFlags->Items->Add("Procedural", uiFlags & TEXTUREFLAGS_PROCEDURAL);
			this->lstFlags->Items->Add("One Bit Alpha (Format Specific)", uiFlags & TEXTUREFLAGS_ONEBITALPHA);
			this->lstFlags->Items->Add("Eight Bit Alpha (Format Specific)", uiFlags & TEXTUREFLAGS_EIGHTBITALPHA);
			this->lstFlags->Items->Add("Enviroment Map (Format Specific)", uiFlags & TEXTUREFLAGS_ENVMAP);
			this->lstFlags->Items->Add("Render Target", uiFlags & TEXTUREFLAGS_RENDERTARGET);
			this->lstFlags->Items->Add("Depth Render Target", uiFlags & TEXTUREFLAGS_DEPTHRENDERTARGET);
			this->lstFlags->Items->Add("No Debug Override", uiFlags & TEXTUREFLAGS_NODEBUGOVERRIDE);
			this->lstFlags->Items->Add("Single Copy", uiFlags & TEXTUREFLAGS_SINGLECOPY);
			this->lstFlags->Items->Add("Unused", uiFlags & TEXTUREFLAGS_UNUSED0);
			this->lstFlags->Items->Add("Unused", uiFlags & TEXTUREFLAGS_UNUSED1);
			this->lstFlags->Items->Add("Unused", uiFlags & TEXTUREFLAGS_UNUSED2);
			this->lstFlags->Items->Add("Unused", uiFlags & TEXTUREFLAGS_UNUSED3);
			this->lstFlags->Items->Add("No Depth Buffer", uiFlags & TEXTUREFLAGS_NODEPTHBUFFER);
			this->lstFlags->Items->Add("Unused", uiFlags & TEXTUREFLAGS_UNUSED4);
			this->lstFlags->Items->Add("Clamp U", uiFlags & TEXTUREFLAGS_CLAMPU);
			this->lstFlags->Items->Add("Vertex Texture", uiFlags & TEXTUREFLAGS_VERTEXTEXTURE);
			this->lstFlags->Items->Add("SSBump", uiFlags & TEXTUREFLAGS_SSBUMP);
			this->lstFlags->Items->Add("Unused", uiFlags & TEXTUREFLAGS_UNUSED5);
			this->lstFlags->Items->Add("Clamp All", uiFlags & TEXTUREFLAGS_BORDER);
			#pragma warning(default: 4800)

			this->lstFlags->EndUpdate();

			this->lblFileVersion->Text = String::Concat(VTFFile->GetMajorVersion().ToString(), ".", VTFFile->GetMinorVersion().ToString());
			this->lblFileSize->Text = String::Concat(((float)VTFFile->GetSize() / 1024.0f).ToString("#,##0.000"), " KB");

			this->lblImageWidth->Text = VTFFile->GetWidth().ToString();
			this->lblImageHeight->Text = VTFFile->GetHeight().ToString();
			this->lblImageFormat->Text = this->GetImageFormatString(VTFFile->GetFormat());
			this->lblImageFrames->Text = VTFFile->GetFrameCount().ToString();
			//this->lblImageStartFrame->Text = VTFFile->GetStartFrame().ToString();
			this->numImageStartFrame->Maximum = VTFFile->GetFrameCount() - 1;
			this->numImageStartFrame->Value = VTFFile->GetStartFrame() == 0xffff ? 0 : VTFFile->GetStartFrame();
			this->lblImageFaces->Text = VTFFile->GetFaceCount().ToString();
			this->lblImageSlices->Text = VTFFile->GetDepth().ToString();
			this->lblImageMipmaps->Text = VTFFile->GetMipmapCount().ToString();
			//this->lblImageBumpmapScale->Text = VTFFile->GetBumpmapScale().ToString("0.00");
			this->numImageBumpmapScale->Value = (Decimal)VTFFile->GetBumpmapScale();

			vlSingle sX, sY, sZ;
			VTFFile->GetReflectivity(sX, sY, sZ);

			this->lblImageReflectivity->Text = String::Concat(sX.ToString("0.000"), ", ", sY.ToString("0.000"), ", ", sZ.ToString("0.000"));

			this->lblThumbnailWidth->Text = VTFFile->GetThumbnailWidth().ToString();
			this->lblThumbnailHeight->Text = VTFFile->GetThumbnailHeight().ToString();
			this->lblThumbnailFormat->Text = this->GetImageFormatString(VTFFile->GetThumbnailFormat());

			this->lblResourceCount->Text = VTFFile->GetResourceCount().ToString();

			this->treResources->BeginUpdate();
			this->treResources->Nodes->Clear();

			for(vlUInt i = 0; i < VTFFile->GetResourceCount(); i++)
			{
				vlUInt uiResource = VTFFile->GetResourceType(i);

				String^sName = "Unknown";
				switch(uiResource)
				{
				case VTF_LEGACY_RSRC_LOW_RES_IMAGE:
					sName = "Thumbnail Image";
					break;
				case VTF_LEGACY_RSRC_IMAGE:
					sName = "Image";
					break;
				case VTF_RSRC_SHEET:
					sName = "Sheet";
					break;
				case VTF_RSRC_CRC:
					sName = "Cyclic Redundancy Check";
					break;
				case VTF_RSRC_TEXTURE_LOD_SETTINGS:
					sName = "LOD Settings";
					break;
				case VTF_RSRC_TEXTURE_SETTINGS_EX:
					sName = "Extended Texture Settings";
					break;
				case VTF_RSRC_KEY_VALUE_DATA:
					sName = "Key/Value Data";
					break;
				default:
					sName = "Unknown";
					break;
				}

				System::Windows::Forms::TreeNode^ pNode = gcnew System::Windows::Forms::TreeNode(sName);

				vlUInt uiSize = 0;
				vlVoid *lpData = VTFFile->GetResourceData(uiResource, uiSize);

				switch(uiResource)
				{
				case VTF_RSRC_CRC:
					pNode->Nodes->Add(String::Concat("Checksum: 0x", (*(vlUInt *)lpData).ToString("X8")));
					break;
				case VTF_RSRC_TEXTURE_LOD_SETTINGS:
					if(lpData && uiSize == sizeof(SVTFTextureLODControlResource))
					{
						SVTFTextureLODControlResource *pLODControl = (SVTFTextureLODControlResource *)lpData;
						pNode->Nodes->Add(String::Concat("Clamp U: ", pLODControl->ResolutionClampU.ToString()));
						pNode->Nodes->Add(String::Concat("Clamp V: ", pLODControl->ResolutionClampV.ToString()));
						break;
					}
				case VTF_RSRC_KEY_VALUE_DATA:
					if(lpData && uiSize)
					{
						VTFLib::CVMTFile *pVMTFile = new VTFLib::CVMTFile();

						if(pVMTFile->Load(lpData, uiSize))
						{
							pNode->Text = gcnew String(pVMTFile->GetRoot()->GetName());
							this->SetInformation(pNode, pVMTFile->GetRoot());
						}
					}
				default:
					if(lpData && uiSize == sizeof(vlUInt))
					{
						pNode->Nodes->Add(String::Concat("Data: 0x", (*(vlUInt *)lpData).ToString("X8")));
					}
					else
					{
						pNode->Nodes->Add(String::Concat("Size: ", uiSize.ToString("#,##0"), " B"));
					}
					break;
				}

				this->treResources->Nodes->Add(pNode);
				pNode->Expand();
			}

			this->treResources->EndUpdate();

			this->VTFFile = VTFFile;

			this->fImageScale = 1.0f;
			this->UpdateVTFFile();

			// "Show" the tab pages.
			if(!this->tabSidebar->TabPages->Contains(this->tabImage))
			{
				this->tabSidebar->TabPages->Add(this->tabImage);
			}
			if(!this->tabSidebar->TabPages->Contains(this->tabInfo))
			{
				this->tabSidebar->TabPages->Add(this->tabInfo);
			}
			if(!this->tabSidebar->TabPages->Contains(this->tabResources))
			{
				this->tabSidebar->TabPages->Add(this->tabResources);
			}

			this->tabSidebar->SelectedTab = this->tabImage;
		}

		private: void SetInformation(System::Windows::Forms::TreeNode^ pNode, VTFLib::Nodes::CVMTGroupNode *pVMTNode)
		{
			for(vlUInt i = 0; i < pVMTNode->GetNodeCount(); i++)
			{
				VTFLib::Nodes::CVMTNode *pVMTChild = pVMTNode->GetNode(i);
				switch(pVMTChild->GetType())
				{
					case NODE_TYPE_GROUP:
					{
						System::Windows::Forms::TreeNode^ pChild = gcnew System::Windows::Forms::TreeNode(gcnew String(pVMTChild->GetName()));
						this->SetInformation(pChild, static_cast<VTFLib::Nodes::CVMTGroupNode *>(pVMTChild));
						pNode->Nodes->Add(pChild);
						break;
					}
					case NODE_TYPE_STRING:
					{
						System::Windows::Forms::TreeNode^ pChild = gcnew System::Windows::Forms::TreeNode(gcnew String(pVMTChild->GetName()));
						pChild->Nodes->Add(gcnew System::Windows::Forms::TreeNode(gcnew String(static_cast<VTFLib::Nodes::CVMTStringNode *>(pVMTChild)->GetValue())));
						pNode->Nodes->Add(pChild);
						break;
					}
					case NODE_TYPE_INTEGER:
					{
						System::Windows::Forms::TreeNode^ pChild = gcnew System::Windows::Forms::TreeNode(gcnew String(pVMTChild->GetName()));
						pChild->Nodes->Add(gcnew System::Windows::Forms::TreeNode(static_cast<VTFLib::Nodes::CVMTIntegerNode *>(pVMTChild)->GetValue().ToString()));
						pNode->Nodes->Add(pChild);
						break;
					}
					case NODE_TYPE_SINGLE:
					{
						System::Windows::Forms::TreeNode^ pChild = gcnew System::Windows::Forms::TreeNode(gcnew String(pVMTChild->GetName()));
						pChild->Nodes->Add(gcnew System::Windows::Forms::TreeNode(static_cast<VTFLib::Nodes::CVMTSingleNode *>(pVMTChild)->GetValue().ToString()));
						pNode->Nodes->Add(pChild);
						break;
					}
				}
			}
		}

		private: bool GetVTFFile()
		{
			this->VTFFile->SetFlags(0);
			for(vlUInt i = 0, j = 0x00000001; i < (vlUInt)this->lstFlags->Items->Count; i++, j <<= 1)
			{
				this->VTFFile->SetFlag((VTFImageFlag)j, this->lstFlags->GetItemChecked(i));
			}

			this->VTFFile->SetStartFrame(Convert::ToUInt32(this->numImageStartFrame->Value));

			VTFFile->SetBumpmapScale(Convert::ToSingle(this->numImageBumpmapScale->Value));

			return true;
		}

		private: void SetVMTFile()
		{
			this->bVMTFile = true;

			this->EnableVMTContextMenuItems();

			this->txtVMTFile->Visible = true;
		}

		private: System::Void barTool_ButtonClick(System::Object^ sender, System::Windows::Forms::ToolBarButtonClickEventArgs^ e)
		{
			if(e->Button == this->btnToolImport)
			{
				this->btnImport_Click(this->btnImport, System::EventArgs::Empty);
			}
			else if(e->Button == this->btnToolOpen)
			{
				this->btnOpen_Click(this->btnOpen, System::EventArgs::Empty);
			}
			else if(e->Button == this->btnToolSave)
			{
				this->btnSave_Click(this->btnSave, System::EventArgs::Empty);
			}
			else if(e->Button == this->btnToolCopy)
			{
				this->btnCopy_Click(this->btnCopy, System::EventArgs::Empty);
			}
			else if(e->Button == this->btnToolPaste)
			{
				this->btnPaste_Click(this->btnPaste, System::EventArgs::Empty);
			}
		}

		private: void New()
		{
			this->Close();

			this->txtVMTFile->Text = "\"LightmappedGeneric\"\n{\n}";
			this->txtVMTFile->SelectionStart = 1;
			this->txtVMTFile->SelectionLength = 18;

			this->SetVMTFile();

			this->FileName = nullptr;

			this->btnSave->Enabled = true;
			this->btnToolSave->Enabled = true;
			this->btnSaveAs->Enabled = true;

			this->txtVMTFile->Focus();
		}

		private: void Open(String^sFileName, bool bTemp)
		{
			this->Close();

			char cPath[512];
			CUtility::StringToCharPointer(sFileName, cPath);

			if(sFileName->ToLower()->EndsWith(".vtf"))
			{
				VTFLib::CVTFFile *VTFFile = new VTFLib::CVTFFile();

				if(VTFFile->Load(cPath))
				{
					this->SetVTFFile(VTFFile);

					if(!bTemp)
					{
						this->FileName = sFileName;

						this->AddRecentFile(this->FileName);
					}
					else
					{
						this->FileName = nullptr;
					}

					this->btnSave->Enabled = true;
					this->btnToolSave->Enabled = true;
					this->btnSaveAs->Enabled = true;

					this->btnExport->Enabled = true;
					this->btnExportAll->Enabled = true;

					this->btnToolCopy->Enabled = true;
					this->btnCopy->Enabled = true;
				}
				else
				{
					delete VTFFile;

					MessageBox::Show(String::Concat("Error loading VTF texture:\n\n", gcnew String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			else if(sFileName->ToLower()->EndsWith(".vmt"))
			{
				this->txtVMTFile->OpenFile(sFileName);

				this->SetVMTFile();

				if(!bTemp)
				{
					this->FileName = sFileName;

					this->AddRecentFile(this->FileName);
				}
				else
				{
					this->FileName = nullptr;
				}

				this->btnSave->Enabled = true;
				this->btnToolSave->Enabled = true;
				this->btnSaveAs->Enabled = true;

				this->txtVMTFile->Focus();
			}
		}

		private: void Save(String^sFileName)
		{
			if(sFileName == nullptr)
				return;

			if(this->VTFFile != 0)
			{
				char cPath[512];
				CUtility::StringToCharPointer(sFileName, cPath);

				if (!this->GetVTFFile())
				{
					return;
				}

				if(this->VTFFile->Save(cPath))
				{
					this->FileName = sFileName;

					this->AddRecentFile(this->FileName);

					if(this->btnAutoCreateVMTFile->Checked)
					{
						CVMTFileUtility::CreateDefaultMaterial(this->FileName, "LightmappedGeneric");
					}
				}
				else
				{
					MessageBox::Show(String::Concat("Error saving VTF texture:\n\n", gcnew String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			else if(this->bVMTFile)
			{
				try
				{
					this->txtVMTFile->SaveToFile( sFileName, gcnew System::Text::UTF8Encoding( false ) );

					this->FileName = sFileName;
				}
				catch(Exception^ e)
				{
					MessageBox::Show(String::Concat("Error saving VMT texture:\n\n", e->Message), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		private: void SaveAs()
		{
			if(this->VTFFile != 0)
			{
				if(this->dlgSaveVTFFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Save(this->dlgSaveVTFFile->FileName);
				}
			}
			else if(this->bVMTFile)
			{
				if(this->dlgSaveVMTFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					this->Save(this->dlgSaveVMTFile->FileName);
				}
			}
		}

		private: void Import(array<String^>^ sFileNames)
		{
			if(this->Options->ShowDialog() != System::Windows::Forms::DialogResult::OK)
			{
				return;
			}

			this->Close();

			char cPath[512];

			VTFLib::CVTFFile *VTFFile = new VTFLib::CVTFFile();

			// Initialize image data.
			vlUInt uiWidth = 0, uiHeight = 0;
			bool bHasAlpha = false;

			vlByte **lpImageData = new vlByte *[sFileNames->Length];
			memset(lpImageData, 0, sizeof(vlByte *) * sFileNames->Length);

			// Load each frame/face.
			for(int i = 0; i < sFileNames->Length; i++)
			{
				CUtility::StringToCharPointer(sFileNames[i], cPath);

				// Load the image and convert it to RGBA.
				if(ilLoadImage(cPath))
				{
					bHasAlpha |= ilGetInteger(IL_IMAGE_FORMAT) == IL_RGBA || ilGetInteger(IL_IMAGE_FORMAT) == IL_BGRA || ilGetInteger(IL_IMAGE_FORMAT) == IL_LUMINANCE_ALPHA;

					if(ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
					{
						// Get the size of the image and make sure it matches the other images.
						if(i == 0)
						{
							uiWidth = (vlUInt)ilGetInteger(IL_IMAGE_WIDTH);
							uiHeight = (vlUInt)ilGetInteger(IL_IMAGE_HEIGHT);
						}
						else
						{
							if(uiWidth != (vlUInt)ilGetInteger(IL_IMAGE_WIDTH) || uiHeight != (vlUInt)ilGetInteger(IL_IMAGE_HEIGHT))
							{
								delete VTFFile;
								VTFFile = 0;

								MessageBox::Show("Error loading image:\n\nAll frames and faces must be the same size.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);

								break;
							}
						}

						// Copy the image data.
						lpImageData[i] = new vlByte[uiWidth * uiHeight * 4];
						memcpy(lpImageData[i], ilGetData(), uiWidth * uiHeight * 4);
					}
					else
					{
						delete VTFFile;
						VTFFile = 0;

						MessageBox::Show("Error converting image.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);

						break;
					}
				}
				else
				{
					delete VTFFile;
					VTFFile = 0;

					MessageBox::Show("Error loading image.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);

					break;
				}
			}

			// Check that we loaded all images.
			if(VTFFile != 0)
			{
				vlUInt uiFrames = this->Options->TextureType == 0 ? sFileNames->Length : 1;
				vlUInt uiFaces = this->Options->TextureType == 1 ? sFileNames->Length : 1;
				vlUInt uiSlices = this->Options->TextureType == 2 ? sFileNames->Length : 1;

				SVTFCreateOptions VTFCreateOptions = CVTFFileUtility::GetCreateOptions(this->Options);

				VTFCreateOptions.ImageFormat = bHasAlpha ? Options->AlphaFormat : Options->NormalFormat;

				// Create the .vtf file.
				if(VTFFile->Create(uiWidth, uiHeight, uiFrames, uiFaces, uiSlices, lpImageData, VTFCreateOptions) != vlFalse && CVTFFileUtility::CreateResources(Options, VTFFile))
				{
					this->SetVTFFile(VTFFile);

					this->FileName = nullptr;

					this->btnSave->Enabled = true;
					this->btnToolSave->Enabled = true;
					this->btnSaveAs->Enabled = true;

					this->btnExport->Enabled = true;
					this->btnExportAll->Enabled = true;

					this->btnToolCopy->Enabled = true;
					this->btnCopy->Enabled = true;
				}
				else
				{
					delete VTFFile;

					MessageBox::Show(String::Concat("Error creating VTF texture:\n\n", gcnew String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}

			// Delete all image data.
			for(int i = 0; i < sFileNames->Length; i++)
			{
				delete []lpImageData[i];
			}
			delete []lpImageData;
		}

		private: void Export(String^sFileName)
		{
			if(this->VTFFile == 0)
				return;

			char cPath[512];
			CUtility::StringToCharPointer(sFileName, cPath);

			//ILuint uiImage;

			//ilInit();

			//ilEnable(IL_ORIGIN_SET);
			//ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

			//ilGenImages(1, &uiImage);
			//ilBindImage(uiImage);

			vlUInt uiWidth, uiHeight, uiDepth;
			this->VTFFile->ComputeMipmapDimensions(this->VTFFile->GetWidth(), this->VTFFile->GetHeight(), this->VTFFile->GetDepth(), (vlUInt)this->numMipmap->Value, uiWidth,  uiHeight, uiDepth);

			vlByte *lpImageData = new vlByte[this->VTFFile->ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)];

			VTFFile->ConvertToRGBA8888(this->VTFFile->GetData((vlUInt)this->numFrame->Value, (vlUInt)this->numFace->Value, (vlUInt)this->numSlice->Value, (vlUInt)this->numMipmap->Value), lpImageData, uiWidth, uiHeight, this->VTFFile->GetFormat());

			// DevIL likes image data upside down...
			VTFFile->FlipImage(lpImageData, uiWidth, uiHeight);

			if(!(ilTexImage(uiWidth, uiHeight, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, lpImageData) && ilSaveImage(cPath)))
			{
				MessageBox::Show("Error saving image.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			delete []lpImageData;

			//ilDeleteImages(1, &uiImage);
			//ilShutDown();
		}

		private: void ExportAll(String^sFileName)
		{
			if(this->VTFFile == 0)
				return;

			char cPath[512];
			char cExt[512] = "";

			CUtility::StringToCharPointer(sFileName, cPath);
			char* cInsert = strrchr(cPath, '.');
			if(cInsert)
			{
				strcpy_s(cExt, cInsert);
			}
			else
			{
				cInsert = cPath + strlen(cPath);
			}

			//ILuint uiImage;

			//ilInit();

			//ilEnable(IL_ORIGIN_SET);
			//ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

			//ilGenImages(1, &uiImage);
			//ilBindImage(uiImage);

			vlUInt uiWidth, uiHeight, uiDepth;
			this->VTFFile->ComputeMipmapDimensions(this->VTFFile->GetWidth(), this->VTFFile->GetHeight(), this->VTFFile->GetDepth(), (vlUInt)this->numMipmap->Value, uiWidth,  uiHeight, uiDepth);

			vlByte *lpImageData = new vlByte[this->VTFFile->ComputeImageSize(uiWidth, uiHeight, 1, IMAGE_FORMAT_RGBA8888)];

			for(vlUInt i = 0; i < this->VTFFile->GetFrameCount(); i++)
			{
				for(vlUInt j = 0; j < this->VTFFile->GetFaceCount(); j++)
				{
					for(vlUInt k = 0; k < this->VTFFile->GetDepth(); k++)
					{
						VTFFile->ConvertToRGBA8888(this->VTFFile->GetData(i, j, k, (vlUInt)this->numMipmap->Value), lpImageData, uiWidth, uiHeight, this->VTFFile->GetFormat());

						// DevIL likes image data upside down...
						VTFFile->FlipImage(lpImageData, uiWidth, uiHeight);

						sprintf_s(cInsert, 512 - ( cInsert - cPath ), "_%.2u_%.2u_%.2u%s", i, j, k, cExt);
						if(!(ilTexImage(uiWidth, uiHeight, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, lpImageData) && ilSaveImage(cPath)))
						{
							MessageBox::Show("Error saving image.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
						}
					}
				}
			}

			delete []lpImageData;

			//ilDeleteImages(1, &uiImage);
			//ilShutDown();
		}

		private: void Close()
		{
			this->btnToolSave->Enabled = false;
			this->btnSave->Enabled = false;
			this->btnSaveAs->Enabled = false;

			this->btnExport->Enabled = false;
			this->btnExportAll->Enabled = false;

			this->btnToolCopy->Enabled = false;
			this->btnCopy->Enabled = false;

			this->trkHDRKey->Enabled = false;
			this->trkHDRShift->Enabled = false;
			this->trkHDRGamma->Enabled = false;

			this->btnAnimate->Text = "&Play";
			this->btnAnimate->Enabled = false;
			this->tmrAnimate->Enabled = false;

			// "Hide" the tab pages.
			if(this->tabSidebar->TabPages->Contains(this->tabResources))
			{
				this->tabSidebar->TabPages->Remove(this->tabResources);
			}
			if(this->tabSidebar->TabPages->Contains(this->tabInfo))
			{
				this->tabSidebar->TabPages->Remove(this->tabInfo);
			}
			if(this->tabSidebar->TabPages->Contains(this->tabImage))
			{
				this->tabSidebar->TabPages->Remove(this->tabImage);
			}

			this->picVTFFileTL->Visible = false;
			this->picVTFFileTR->Visible = false;
			this->picVTFFileBL->Visible = false;
			this->picVTFFileBR->Visible = false;

			this->picVTFFileTL->Image = nullptr;
			this->picVTFFileTR->Image = nullptr;
			this->picVTFFileBL->Image = nullptr;
			this->picVTFFileBR->Image = nullptr;

			//this->treVMTFile->Visible = false;
			//this->treVMTFile->Nodes->Clear();

			this->txtVMTFile->Visible = false;
			this->txtVMTFile->Clear();
			this->txtVMTFile->ClearUndo();

			this->bVMTFile = false;

			delete this->VTFFile;
			this->VTFFile = 0;

			delete []this->ucImageData;
			this->ucImageData = 0;

			this->FileName = nullptr;
			this->pnlInfo1->Text = nullptr;
			this->pnlInfo2->Text = nullptr;
		}

		//
		// Main menu.
		//

		private: System::Void btnNew_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->New();
		}

		private: System::Void btnOpen_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->dlgOpenFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->Open(this->dlgOpenFile->FileName, false);
			}
		}

		private: System::Void btnSave_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->FileName != nullptr)
				this->Save(this->FileName);
			else
				this->SaveAs();
		}

		private: System::Void btnSaveAs_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->SaveAs();
		}

		private: System::Void btnImport_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->dlgImportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->Import(this->dlgImportFile->FileNames);
			}
		}

		private: System::String^RemoveExtension(System::String^sFileName)
		{
			if(sFileName == nullptr)
			{
				return "";
			}
			return IO::Path::GetFileNameWithoutExtension( sFileName );
		}

		private: System::Void btnExport_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->dlgExportFile->FileName = this->RemoveExtension(this->FileName);

			if(this->dlgExportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->Export(this->dlgExportFile->FileName);
			}
		}

		private: System::Void btnExportAll_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->dlgExportFile->FileName = this->RemoveExtension(this->FileName);

			if(this->dlgExportFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->ExportAll(this->dlgExportFile->FileName);
			}
		}

		private: System::Void btnCreateVMTFile_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile != 0 && this->FileName != nullptr && (this->FileName->Length >= 4 && String::Compare(this->FileName, this->FileName->Length - 4, ".vtf", 0, 4, true) == 0))
			{
				this->VMTCreate->Create(this->FileName, *this->VTFFile);
			}
			this->VMTCreate->ShowDialog();
		}

		private: System::Void btnConvertFolder_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->BatchConvert->ShowDialog();
		}

		private: System::Void btnConvertWADFile_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->WADConvert->ShowDialog();
		}

		private: System::Void btnRecentFile_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->Open(this->RecentFiles[safe_cast<MenuItem^>(sender)->Index], false);
		}

		private: System::Void btnExit_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			__super::Close();
		}

		private: System::Void btnCopy_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				if(this->picVTFFileTL->Image != nullptr)
				{
					System::Windows::Forms::Clipboard::SetDataObject(this->picVTFFileTL->Image, true);
				}
			}
			else
			{
				MessageBox::Show("Operation not supported.\n\nVTFEdit has determined that the current thread apartment state does not\nsupport this operation. This is a .NET design flaw.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		private: System::Void btnPaste_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				System::Windows::Forms::IDataObject^ Data = System::Windows::Forms::Clipboard::GetDataObject();

				if(!Data->GetDataPresent(System::Windows::Forms::DataFormats::Bitmap))
				{
					return;
				}

				System::Drawing::Bitmap^ Bitmap = safe_cast<System::Drawing::Bitmap^>(Data->GetData(System::Windows::Forms::DataFormats::Bitmap));

				if(this->Options->ShowDialog() != System::Windows::Forms::DialogResult::OK)
				{
					return;
				}

				this->Close();

				VTFLib::CVTFFile *VTFFile = new VTFLib::CVTFFile();

				// Initialize image data.
				vlUInt uiWidth = (vlUInt)Bitmap->Width, uiHeight = (vlUInt)Bitmap->Height;

				vlByte *lpImageData = new vlByte[uiWidth * uiHeight * 4];
				vlByte *lpPointer = lpImageData;

				for(int j = 0; j < Bitmap->Height; j++)
				{
					for(int i = 0; i < Bitmap->Width; i++)
					{
						System::Drawing::Color Pixel = Bitmap->GetPixel(i, j);

						*(lpPointer++) = (vlByte)Pixel.R;
						*(lpPointer++) = (vlByte)Pixel.G;
						*(lpPointer++) = (vlByte)Pixel.B;
						*(lpPointer++) = (vlByte)Pixel.A;
					}
				}

				SVTFCreateOptions VTFCreateOptions = CVTFFileUtility::GetCreateOptions(this->Options);

				// Create the .vtf file.
				if(VTFFile->Create(uiWidth, uiHeight, lpImageData, VTFCreateOptions) != vlFalse && CVTFFileUtility::CreateResources(Options, VTFFile))
				{
					this->SetVTFFile(VTFFile);

					this->btnToolSave->Enabled = true;
					this->btnSaveAs->Enabled = true;

					this->btnExport->Enabled = true;
					this->btnExportAll->Enabled = true;

					this->btnToolCopy->Enabled = true;
					this->btnCopy->Enabled = true;
				}
				else
				{
					delete VTFFile;

					MessageBox::Show(String::Concat("Error creating VTF texture:\n\n", gcnew String(vlGetLastError())), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}

				delete []lpImageData;
			}
			else
			{
				MessageBox::Show("Operation not supported.\n\nVTFEdit has determined that the current thread apartment state does not\nsupport this operation. This is a .NET design flaw.", Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		private: System::Void btnChannel_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnChannelRGB->Checked = false;
			this->btnChannelR->Checked = false;
			this->btnChannelG->Checked = false;
			this->btnChannelB->Checked = false;
			this->btnChannelA->Checked = false;

			safe_cast<System::Windows::Forms::MenuItem^>(sender)->Checked = true;

			this->UpdateVTFFile();
		}

		private: System::Void btnMask_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnMask->Checked = !this->btnMask->Checked;

			this->UpdateVTFFile();
		}

		private: System::Void btnTile_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnTile->Checked = !this->btnTile->Checked;

			this->UpdateVTFFile();
		}

		private: System::Void btnAutoCreateVMTFile_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnAutoCreateVMTFile->Checked = !this->btnAutoCreateVMTFile->Checked;
		}

		private: System::Void btnFileMapping_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnFileMapping->Checked = !this->btnFileMapping->Checked;

			this->DirectoryItemInfoManager->FileMapping = this->btnFileMapping->Checked;
		}

		private: System::Void btnVolatileAccess_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnVolatileAccess->Checked = !this->btnVolatileAccess->Checked;

			this->DirectoryItemInfoManager->VolatileAccess = this->btnVolatileAccess->Checked;
		}

		private: System::Void btnAbout_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->About->ShowDialog();
		}

		private: System::Void numVTFFile_ValueChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(!this->bHDRReseting)
			{
				this->UpdateVTFFile();
			}
		}

		private: System::Void trkHDRKey_ValueChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(!this->bHDRReseting)
			{
				this->UpdateVTFFile();
			}
		}

		private: System::Void trkHDRShift_ValueChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(!this->bHDRReseting)
			{
				this->UpdateVTFFile();
			}
		}

		private: System::Void trkHDRGamma_ValueChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->UpdateVTFFile();
		}

		//
		// Animation.
		//

		private: System::Void btnAnimate_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->tmrAnimate->Enabled)
			{
				this->tmrAnimate->Enabled = false;
				this->btnAnimate->Text = "&Play";
			}
			else
			{
				this->tmrAnimate->Enabled = true;
				this->btnAnimate->Text = "&Stop";
			}
		}

		private: System::Void tmrAnimate_Tick(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(System::Windows::Forms::Form::ActiveForm != this)
				return;

			int iValue = (int)this->numFrame->Value + 1;

			if(iValue > this->numFrame->Maximum)
				iValue = (int)this->numFrame->Minimum;

			this->numFrame->Value = iValue;
		}

		private: System::Void lstFlags_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e)
		{
			if(this->VTFFile == 0)
				return;

			if(e->Index == 12 || e->Index == 13 || e->Index == 14 || static_cast<String^>(this->lstFlags->Items[e->Index]) == "Unused")
			{
				e->NewValue = e->CurrentValue;
			}
		}

		//
		// HDR context.
		//

		private: System::Void btnHDRReset_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->bHDRReseting = true;

			this->trkHDRKey->LargeChange = 1;
			this->trkHDRKey->Minimum = 0;
			this->trkHDRKey->Maximum = 800;
			this->trkHDRKey->Value = 125;
			this->trkHDRKey->TickFrequency = 80;

			this->trkHDRShift->LargeChange = 1;
			this->trkHDRShift->Minimum = -100;
			this->trkHDRShift->Maximum = 100;
			this->trkHDRShift->Value = 40;
			this->trkHDRShift->TickFrequency = 20;

			this->trkHDRGamma->LargeChange = 1;
			this->trkHDRGamma->Minimum = 0;
			this->trkHDRGamma->Maximum = 1600;
			this->trkHDRGamma->Value = 400;
			this->trkHDRGamma->TickFrequency = 160;

			this->bHDRReseting = false;

			this->UpdateVTFFile();
		}

		//
		// VTF context.
		//

		private: System::Void picVTFFile_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			int iX = (int)((float)e->X / this->fImageScale) + 1;
			int iY = (int)((float)e->Y / this->fImageScale) + 1;

			this->pnlInfo2->Text = String::Concat(iX.ToString(), ", ", iY.ToString());
		}

		private: System::Void btnVTFFileZoomIn_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile == 0 || this->picVTFFileTL->Width == 4096 || this->picVTFFileTL->Height == 4096)
				return;

			this->fImageScale *= 2.0f;
			//this->UpdateVTFFileScale();
			this->UpdateVTFFile();
		}

		private: System::Void btnVTFFileZoomOut_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile == 0 || this->picVTFFileTL->Width == 1 || this->picVTFFileTL->Height == 1)
				return;

			this->fImageScale *= 0.5f;
			//this->UpdateVTFFileScale();
			this->UpdateVTFFile();
		}

		private: System::Void btnVTFFileZoomReset_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile == 0)
				return;

			this->fImageScale = 1.0f;
			//this->UpdateVTFFileScale();
			this->UpdateVTFFile();
		}

		private: System::Void btnVTFFileCopy_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->VTFFile == 0)
				return;

			this->btnCopy_Click(this->btnCopy, System::EventArgs::Empty);
		}

		//
		// VMT context.
		//

		private: System::Void EnableVMTContextMenuItems()
		{
			this->btnVMTFileUndo->Enabled = this->txtVMTFile->UndoEnabled;
			this->btnVMTFileCut->Enabled = this->txtVMTFile->SelectedText->Length > 0;
			this->btnVMTFileCopy->Enabled = this->txtVMTFile->SelectedText->Length > 0;
			if(System::Threading::Thread::CurrentThread->ApartmentState == System::Threading::ApartmentState::STA)
			{
				this->btnVMTFilePaste->Enabled = false;
				try
				{
					array<String^>^ Formats = System::Windows::Forms::Clipboard::GetDataObject()->GetFormats();
					for ( int i = 0; i < Formats->Length; i++ )
					{
						if ( System::Windows::Forms::DataFormats::GetFormat( Formats[i] )->Name->Equals( "Text" ) )
						{
							this->btnVMTFilePaste->Enabled = true;
							break;
						}
					}
				}
				catch ( Exception^ )
				{
				}
			}
			else
			{
				this->btnVMTFilePaste->Enabled = true;
			}
			this->btnVMTFileDelete->Enabled = this->txtVMTFile->SelectedText->Length > 0;
			this->btnVMTFileSelectAll->Enabled = this->txtVMTFile->Text->Length > 0;

			const int line = this->txtVMTFile->Selection->Start.iLine;
			const int column = this->txtVMTFile->Selection->Start.iChar;

			this->pnlInfo2->Text = String::Concat("Ln ", (line + 1).ToString(), ", Col ", (column + 1).ToString());
		}

		private: System::Void btnVMTFileUndo_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->Undo();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileCut_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->Cut();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileCopy_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->Copy();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFilePaste_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			//this->txtVMTFile->Paste(System::Windows::Forms::DataFormats::GetFormat(System::Windows::Forms::DataFormats::Text));
			this->txtVMTFile->Paste();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileDelete_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->SelectedText = "";
			this->EnableVMTContextMenuItems();
		}

		private: System::Void btnVMTFileSelectAll_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->txtVMTFile->SelectAll();
			this->EnableVMTContextMenuItems();
		}

		private: System::Void txtVMTFile_SelectionChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->EnableVMTContextMenuItems();
		}

		private: System::Void txtVMTFile_TextChanged(System::Object ^  sender, FastColoredTextBoxNS::TextChangedEventArgs^  e)
		{
			this->EnableVMTContextMenuItems();
		}

		//
		// VMT context.
		//

		/*private: System::Void treVMTFile_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		{
			if(e->Button == MouseButtons::Left || e->Button == MouseButtons::Right)
			{
				this->treVMTFile->SelectedNode = this->treVMTFile->GetNodeAt(e->X, e->Y);
			}
		}

		private: System::Void mnuVMTFile_Popup(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnVMTFileCopy->Visible = false;

			if(this->treVMTFile->SelectedNode == 0)
				return;

			this->btnVMTFileCopy->Visible = true;
		}

		private: System::Void btnVMTFileCopy_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treVMTFile->SelectedNode == 0)
				return;

			System::Windows::Forms::Clipboard::SetDataObject(this->treVMTFile->SelectedNode->Text, true);
		}*/

		//
		// Goto
		//

		private: System::Void cboGoto_SelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->cboGoto->SelectedIndex == -1)
				return;

			this->Goto(this->cboGoto->Text);
		}

		//
		// Goto()
		// Go to the specified path in the file system tree.
		//
		private: void Goto(String^sPath)
		{
			array<wchar_t>^ lpSplit = { '\\', '/' };

			array<String^>^ lpPath = sPath->Split(lpSplit);

			if(lpPath->Length == 0)
				return;

			lpPath[0] = String::Concat(lpPath[0], "\\");

			auto Nodes = this->treFileSystem->Nodes;

			this->treFileSystem->BeginUpdate();
			for(int i = 0; i < lpPath->Length; i++)
			{
				for(int j = 0; j < Nodes->Count; j++)
				{
					TreeNode^ Node = Nodes[j];

					if(String::Compare(lpPath[i], Node->Text, true) == 0)
					{
						if(i == lpPath->Length)
						{
							Node->EnsureVisible();
							this->treFileSystem->SelectedNode = Node;
							break;
						}
						else
						{
							Node->Expand();
							Nodes = Node->Nodes;
							break;
						}
					}
				}
			}
			this->treFileSystem->EndUpdate();
		}

		private: System::Void btnFileSystemAddGoto_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryFileSystemTreeNode::typeid) || this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryItemFileSystemTreeNode::typeid))
			{
				//if(static_cast<CDirectoryFileSystemTreeNode *>(this->treFileSystem->SelectedNode)->DirectoryItemType == DirectoryItemFolder)
				{
					TreeNode^ Node = this->treFileSystem->SelectedNode;
					String^sGoto = Node->Text;

					while(Node->Parent != nullptr)
					{
						Node = Node->Parent;
						sGoto = String::Concat(Node->Text, Node->Parent != nullptr ? "\\" : "", sGoto);
					}

					this->cboGoto->Items->Add(sGoto);
				}
			}
		}

		private: System::Void mnuGoto_Popup(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnGotoRemove->Enabled = this->cboGoto->SelectedIndex != -1;
			this->btnGotoClear->Enabled = this->cboGoto->Items->Count > 0;
		}

		private: System::Void btnGotoRemove_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->cboGoto->SelectedIndex != -1)
			{
				this->cboGoto->Items->Remove(this->cboGoto->SelectedItem);
			}
		}

		private: System::Void btnGotoClear_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->cboGoto->Items->Clear();
		}

		//
		// Filesystem
		//

		private: System::Void treFileSystem_DoubleClick(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnFileSystemOpen_Click(this->btnFileSystemOpen, System::EventArgs::Empty);
		}

		private: System::Void treFileSystem_AfterCollapse(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e)
		{
			static_cast<CFileSystemTreeNode^>(e->Node)->AfterCollapse();
		}

		private: System::Void treFileSystem_AfterExpand(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e)
		{
			static_cast<CFileSystemTreeNode^>(e->Node)->AfterExpand();
		}

		private: System::Void treFileSystem_BeforeExpand(System::Object^ sender, System::Windows::Forms::TreeViewCancelEventArgs^ e)
		{
			static_cast<CFileSystemTreeNode^>(e->Node)->BuildChildren();
		}

		private: System::Void treFileSystem_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{
			if(e->Button == System::Windows::Forms::MouseButtons::Left || e->Button == System::Windows::Forms::MouseButtons::Right)
			{
				this->treFileSystem->SelectedNode = this->treFileSystem->GetNodeAt(e->X, e->Y);
			}
		}

		private: System::Void mnuFileSystem_Popup(System::Object ^  sender, System::EventArgs ^  e)
		{
			this->btnFileSystemOpen->Visible = false;
			this->btnFileSystemShellExecute->Visible = false;
			this->btnFileSystemExtract->Visible = false;
			this->btnFileSystemExpandAll->Visible = false;
			this->btnFileSystemCollapseAll->Visible = false;
			this->btnFileSystemMount->Visible = false;
			this->btnFileSystemSpace1->Visible = false;
			this->btnFileSystemAddGoto->Visible = false;
			this->btnFileSystemSpace2->Visible = false;
			this->btnFileSystemDelete->Visible = false;

			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryFileSystemTreeNode::typeid))
			{
				if(static_cast<CDirectoryFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->DirectoryItemType == HL_ITEM_FOLDER)
				{
					this->btnFileSystemShellExecute->Visible = true;
					this->btnFileSystemSpace1->Visible = true;
					this->btnFileSystemAddGoto->Visible = true;
				}
				else
				{
					this->btnFileSystemOpen->Visible = true;
					this->btnFileSystemShellExecute->Visible = true;
					this->btnFileSystemSpace2->Visible = true;
					this->btnFileSystemDelete->Visible = true;
				}
			}
			else if(this->treFileSystem->SelectedNode->GetType()->Equals(CPackageFileSystemTreeNode::typeid))
			{
				this->btnFileSystemMount->Visible = true;
				this->btnFileSystemMount->Enabled = !static_cast<CPackageFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->Mounted;
			}
			else if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryItemFileSystemTreeNode::typeid))
			{
				if(static_cast<CDirectoryItemFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->DirectoryItemType == HL_ITEM_FOLDER)
				{
					this->btnFileSystemExpandAll->Visible = true;
					this->btnFileSystemCollapseAll->Visible = true;
					this->btnFileSystemSpace1->Visible = true;
					this->btnFileSystemAddGoto->Visible = true;
				}
				else
				{
					this->btnFileSystemOpen->Visible = true;
					this->btnFileSystemShellExecute->Visible = true;
					this->btnFileSystemExtract->Visible = true;
				}
			}
		}

		private: System::Void btnFileSystemOpen_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryFileSystemTreeNode::typeid) || this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryItemFileSystemTreeNode::typeid))
			{
				String^sItemPath = static_cast<CFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->ItemPath;

				if(!System::IO::File::Exists(sItemPath))
					return;

				String^ ext = sItemPath->ToLower();
				if(ext->EndsWith(".vtf") || ext->EndsWith(".vmt"))
				{
					this->Open(sItemPath, this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryItemFileSystemTreeNode::typeid));

					this->tabSidebar->SelectedTab = this->tabFileSystem;
				}
				else if ( ext->EndsWith(".bmp") || ext->EndsWith(".dds") || ext->EndsWith(".gif") || ext->EndsWith(".jpg") || ext->EndsWith(".jpeg") || ext->EndsWith(".png") || ext->EndsWith(".tga") )
				{
					this->Import( gcnew array<String^> { sItemPath } );
				}
			}
		}

		private: System::Void btnFileSystemShellExecute_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryFileSystemTreeNode::typeid) || this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryItemFileSystemTreeNode::typeid))
			{
				String^sItemPath = static_cast<CFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->ItemPath;

				if(!System::IO::File::Exists(sItemPath) && !System::IO::Directory::Exists(sItemPath))
					return;

				try
				{
					System::Diagnostics::Process::Start(sItemPath);
				}
				catch(Exception^ ex)
				{
					MessageBox::Show(String::Concat("Error shell executing directory item:\n\n", ex->Message), Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}

		private: System::Void btnFileSystemExtract_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryItemFileSystemTreeNode::typeid))
			{
				if(this->dlgExtractDirectoryItem->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					static_cast<CDirectoryItemFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->Extract(this->dlgExtractDirectoryItem->SelectedPath);
				}
			}
		}

		private: System::Void btnFileSystemExpandAll_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryItemFileSystemTreeNode::typeid))
			{
				if(static_cast<CDirectoryItemFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->DirectoryItemType == HL_ITEM_FOLDER)
				{
					this->treFileSystem->BeginUpdate();
					this->treFileSystem->SelectedNode->ExpandAll();
					this->treFileSystem->EndUpdate();
				}
			}
		}

		private: System::Void btnFileSystemCollapseAll_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryItemFileSystemTreeNode::typeid))
			{
				if(static_cast<CDirectoryItemFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->DirectoryItemType == HL_ITEM_FOLDER)
				{
					this->treFileSystem->BeginUpdate();
					this->treFileSystem->SelectedNode->Collapse();
					this->treFileSystem->EndUpdate();
				}
			}
		}

		private: System::Void btnFileSystemMount_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CPackageFileSystemTreeNode::typeid))
			{
				static_cast<CPackageFileSystemTreeNode^>(this->treFileSystem->SelectedNode)->Mount();
			}
		}

		private: System::Void btnFileSystemDelete_Click(System::Object ^  sender, System::EventArgs ^  e)
		{
			if(this->treFileSystem->SelectedNode == nullptr)
				return;

			if(this->treFileSystem->SelectedNode->GetType()->Equals(CDirectoryFileSystemTreeNode::typeid))
			{
				CDirectoryFileSystemTreeNode^ Node = static_cast<CDirectoryFileSystemTreeNode^>(this->treFileSystem->SelectedNode);

				try
				{
					if(MessageBox::Show(String::Concat("Are you sure you want to permanently delete '", Node->Text, "'?"), Application::ProductName, System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
					{
						System::IO::File::Delete(Node->ItemPath);
					}
				}
				catch(Exception^ e)
				{
					MessageBox::Show(String::Concat("Error deleting '", Node->Text, "':\n\n", e->Message), Application::ProductName, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				}
			}
		}

		//
		// Helper functions.
		//

		private: String^GetImageFormatString(VTFImageFormat ImageFormat)
		{
			SVTFImageFormatInfo ImageFormatInfo;
			if(vlImageGetImageFormatInfoEx(ImageFormat, &ImageFormatInfo))
			{
				return gcnew String(ImageFormatInfo.lpName);
			}
			return "";
		}

		//
		// Recent menu.
		//

		private: void AddRecentFile(String^sFileName)
		{
			for(int i = 0; i < this->RecentFiles->Count; i++)
			{
				if(String::Compare(this->RecentFiles[i], sFileName, true) == 0)
				{
					if(i == 0)
					{
						return;
					}
					else
					{
						this->RecentFiles->RemoveAt(i);
						this->RecentFiles->Insert(0, sFileName);

						this->UpdateRecentFiles();

						return;
					}
				}
			}

			this->RecentFiles->Insert(0, sFileName);

			while(this->RecentFiles->Count > (int)this->uiMaximumRecentFiles)
			{
				this->RecentFiles->RemoveAt(this->RecentFiles->Count - 1);
			}

			this->UpdateRecentFiles();
		}

		private: void UpdateRecentFiles()
		{
			this->btnRecentFiles->MenuItems->Clear();

			for(int i = 0; i < this->RecentFiles->Count; i++)
			{
				MenuItem^ RecentFile = gcnew MenuItem(this->RecentFiles[i]);
				RecentFile->Click += gcnew EventHandler(this, &CVTFEdit::btnRecentFile_Click);
				this->btnRecentFiles->MenuItems->Add(RecentFile);
			}

			this->btnRecentFiles->Visible = RecentFiles->Count != 0;
			this->btnFileSpace4->Visible = RecentFiles->Count != 0;
		}

		//
		// Configuration
		//

		private: bool WriteConfigFile(String^sConfigFile)
		{
			System::IO::StreamWriter^ ConfigFile;

			try
			{
				ConfigFile = gcnew System::IO::StreamWriter(sConfigFile, false, System::Text::Encoding::ASCII);
			}
			catch(Exception^)
			{
				return false;
			}

			//try
			//{
				ConfigFile->WriteLine("[VTFEdit]");
				ConfigFile->WriteLine("");

				ConfigFile->WriteLine(String::Concat("VTFEdit.AnimationFrameInterval = ", this->tmrAnimate->Interval.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFEdit.Mask = ", this->btnMask->Checked.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFEdit.Tile = ", this->btnTile->Checked.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFEdit.AutoCreateVMTFile = ", this->btnAutoCreateVMTFile->Checked.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFEdit.FileMapping = ", this->DirectoryItemInfoManager->FileMapping.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFEdit.VolatileAccess = ", this->DirectoryItemInfoManager->VolatileAccess.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFEdit.ExtractDirectory = ", this->dlgExtractDirectoryItem->SelectedPath));
				for(int i = 0; i < this->cboGoto->Items->Count; i++)
				{
					ConfigFile->WriteLine(String::Concat("VTFEdit.Goto = ", static_cast<String^>(this->cboGoto->Items[i])));
				}

				ConfigFile->WriteLine("");
				ConfigFile->WriteLine("[Forms]");
				ConfigFile->WriteLine("");

				ConfigFile->WriteLine(String::Concat("Forms.VTFEdit.Location.X = ", this->FormSaveLocation.X.ToString()));
				ConfigFile->WriteLine(String::Concat("Forms.VTFEdit.Location.Y = ", this->FormSaveLocation.Y.ToString()));
				ConfigFile->WriteLine(String::Concat("Forms.VTFEdit.Size.Width = ", this->FormSaveSize.Width.ToString()));
				ConfigFile->WriteLine(String::Concat("Forms.VTFEdit.Size.Height = ", this->FormSaveSize.Height.ToString()));
				if(this->FormSaveWindowState == FormWindowState::Maximized)
				{
					ConfigFile->WriteLine("Forms.VTFEdit.WindowState = Maximized");
				}
				else
				{
					ConfigFile->WriteLine("Forms.VTFEdit.WindowState = Normal");
				}
				ConfigFile->WriteLine(String::Concat("Forms.VTFEdit.Sidebar.SplitPosition = ", this->iFormSaveSidebarSplitPosition.ToString()));

				ConfigFile->WriteLine(String::Concat("Forms.BatchConvert.InputFolder = ", this->BatchConvert->InputFolder));
				ConfigFile->WriteLine(String::Concat("Forms.BatchConvert.OutputFolder = ", this->BatchConvert->OutputFolder));
				ConfigFile->WriteLine(String::Concat("Forms.BatchConvert.ToVTF = ", this->BatchConvert->ToVTF.ToString()));
				ConfigFile->WriteLine(String::Concat("Forms.BatchConvert.ToVTFFilter = ", this->BatchConvert->ToVTFFilter));
				ConfigFile->WriteLine(String::Concat("Forms.BatchConvert.FromVTFFormat = ", this->BatchConvert->FromVTFFormat));
				ConfigFile->WriteLine(String::Concat("Forms.BatchConvert.FromVTFFilter = ", this->BatchConvert->FromVTFFilter));
				ConfigFile->WriteLine(String::Concat("Forms.BatchConvert.Recurse = ", this->BatchConvert->Recurse.ToString()));
				ConfigFile->WriteLine(String::Concat("Forms.BatchConvert.CreateVMTFiles = ", this->BatchConvert->CreateVMTFiles.ToString()));

				ConfigFile->WriteLine(String::Concat("Forms.WADConvert.WADFile = ", this->WADConvert->WADFile));
				ConfigFile->WriteLine(String::Concat("Forms.WADConvert.OutputFolder = ", this->WADConvert->OutputFolder));
				ConfigFile->WriteLine(String::Concat("Forms.WADConvert.CreateVMTFiles = ", this->WADConvert->CreateVMTFiles.ToString()));

				ConfigFile->WriteLine("");
				ConfigFile->WriteLine("[VTF Options]");
				ConfigFile->WriteLine("");

				ConfigFile->WriteLine(String::Concat("VTFOptions.NormalFormat = ", Convert::ToInt32(this->Options->NormalFormat).ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.AlphaFormat = ", Convert::ToInt32(this->Options->AlphaFormat).ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.TextureType = ", this->Options->TextureType.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.Resize = ", this->Options->ResizeImage.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.ResizeMethod = ", Convert::ToInt32(this->Options->ResizeMethod).ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.ResizeFilter = ", Convert::ToInt32(this->Options->ResizeFilter).ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.ResizeClamp = ", this->Options->ResizeClamp.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.ResizeClampWidth = ", this->Options->ResizeClampWidth.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.ResizeClampHeight = ", this->Options->ResizeClampHeight.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.GenerateMipmaps = ", this->Options->GenerateMipmaps.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.MipmapFilter = ", Convert::ToInt32(this->Options->MipmapFilter).ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.GenerateNormalMap = ", this->Options->ConvertToNormalMap.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.HeightConversionMethod = ", Convert::ToInt32(this->Options->HeightConversionMethod).ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.AlphaResult = ", Convert::ToInt32(this->Options->AlphaResult).ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.NormalWrap = ", this->Options->NormalWrap.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.Version = ", this->Options->Version));

				ConfigFile->WriteLine(String::Concat("VTFOptions.ComputeReflectivity = ", this->Options->ComputeReflectivity.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.GenerateThumbnail = ", this->Options->GenerateThumbnail.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.GenerateSphereMap = ", this->Options->GenerateSphereMap.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.DXTQuality = ", Convert::ToInt32(this->Options->DXTQuality).ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.CorrectGamma = ", this->Options->CorrectGamma.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.GammaCorrection = ", this->Options->GammaCorrection.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.LuminanceWeightR = ", this->Options->LuminanceWeightR.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.LuminanceWeightG = ", this->Options->LuminanceWeightG.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.LuminanceWeightB = ", this->Options->LuminanceWeightB.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.UnsharpenMaskRadius = ", this->Options->UnsharpenMaskRadius.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.UnsharpenMaskAmount = ", this->Options->UnsharpenMaskAmount.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.UnsharpenMaskThreshold = ", this->Options->UnsharpenMaskThreshold.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.XSharpenStrength = ", this->Options->XSharpenStrength.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.XSharpenThreshold = ", this->Options->XSharpenThreshold.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.CreateLODControlResource = ", this->Options->CreateLODControlResource.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.LODControlClampU = ", this->Options->LODControlClampU.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.LODControlClampV = ", this->Options->LODControlClampV.ToString()));

				ConfigFile->WriteLine(String::Concat("VTFOptions.CreateInformationResource = ", this->Options->CreateInformationResource.ToString()));
				ConfigFile->WriteLine(String::Concat("VTFOptions.InformationAuthor = ", this->Options->InformationAuthor));
				ConfigFile->WriteLine(String::Concat("VTFOptions.InformationContact = ", this->Options->InformationContact));
				ConfigFile->WriteLine(String::Concat("VTFOptions.InformationVersion = ", this->Options->InformationVersion));
				ConfigFile->WriteLine(String::Concat("VTFOptions.InformationModification = ", this->Options->InformationModification));
				ConfigFile->WriteLine(String::Concat("VTFOptions.InformationDescription = ", this->Options->InformationDescription));
				ConfigFile->WriteLine(String::Concat("VTFOptions.InformationComments = ", this->Options->InformationComments));

				ConfigFile->WriteLine("");
				ConfigFile->WriteLine("[Recent Files]");
				ConfigFile->WriteLine("");

				ConfigFile->WriteLine(String::Concat("RecentFiles.Maximum = ", this->uiMaximumRecentFiles.ToString()));

				for(int i = this->RecentFiles->Count - 1; i >= 0; i--)
				{
					ConfigFile->WriteLine(String::Concat("RecentFiles.File = ", this->RecentFiles[i]));
				}
			//}
			//catch(Exception *)
			//{
				//ConfigFile->Close();
				//return false;
			//}

			ConfigFile->Close();

			return true;
		}

		private: bool ReadConfigFile(String^sConfigFile)
		{
			System::IO::StreamReader^ ConfigFile;

			try
			{
				ConfigFile = gcnew System::IO::StreamReader(sConfigFile, System::Text::Encoding::ASCII);
			}
			catch(Exception^)
			{
				return false;
			}

			try
			{
				String^ sLine, ^sArg, ^sVal;

				while((sLine = ConfigFile->ReadLine()) != nullptr)
				{
					int iIndex = sLine->IndexOf("=");

					if(iIndex == -1)
						continue;

					sArg = sLine->Substring(0, iIndex)->Trim();
					sVal = sLine->Substring(iIndex + 1)->Trim();

					try
					{
						if(String::Compare(sArg, "VTFEdit.AnimationFrameInterval", true) == 0)
						{
							this->tmrAnimate->Interval = Convert::ToUInt32(sVal);

							if(this->tmrAnimate->Interval < 10)
							{
								this->tmrAnimate->Interval = 10;
							}
							else if(this->tmrAnimate->Interval > 1000)
							{
								this->tmrAnimate->Interval = 1000;
							}
						}
						else if(String::Compare(sArg, "VTFEdit.Mask", true) == 0)
						{
							this->btnMask->Checked = Convert::ToBoolean(sVal);
						}
						else if(String::Compare(sArg, "VTFEdit.Tile", true) == 0)
						{
							this->btnTile->Checked = Convert::ToBoolean(sVal);
						}
						else if(String::Compare(sArg, "VTFEdit.AutoCreateVMTFile", true) == 0)
						{
							this->btnAutoCreateVMTFile->Checked = Convert::ToBoolean(sVal);
						}
						else if(String::Compare(sArg, "VTFEdit.FileMapping", true) == 0)
						{
							this->DirectoryItemInfoManager->FileMapping = Convert::ToBoolean(sVal);
						}
						else if(String::Compare(sArg, "VTFEdit.VolatileAccess", true) == 0)
						{
							this->DirectoryItemInfoManager->VolatileAccess = Convert::ToBoolean(sVal);
						}
						else if(String::Compare(sArg, "VTFEdit.ExtractDirectory", true) == 0)
						{
							this->dlgExtractDirectoryItem->SelectedPath = sVal;;
						}
						else if(String::Compare(sArg, "VTFEdit.Goto", true) == 0)
						{
							this->cboGoto->Items->Add(sVal);
						}

						else if(String::Compare(sArg, "Forms.VTFEdit.Location.X", true) == 0)
						{
							this->FormSaveLocation.X = Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "Forms.VTFEdit.Location.Y", true) == 0)
						{
							this->FormSaveLocation.Y = Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "Forms.VTFEdit.Size.Width", true) == 0)
						{
							this->FormSaveSize.Width = Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "Forms.VTFEdit.Size.Height", true) == 0)
						{
							this->FormSaveSize.Height = Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "Forms.VTFEdit.WindowState", true) == 0)
						{
							if(String::Compare(sVal, "Normal", true) == 0)
							{
								this->FormSaveWindowState = FormWindowState::Normal;
							}
							else if(String::Compare(sVal, "Maximized", true) == 0)
							{
								this->FormSaveWindowState = FormWindowState::Maximized;
							}
						}
						else if(String::Compare(sArg, "Forms.VTFEdit.Sidebar.SplitPosition", true) == 0)
						{
							this->iFormSaveSidebarSplitPosition = Convert::ToInt32(sVal);
						}

						else if(String::Compare(sArg, "Forms.BatchConvert.InputFolder", true) == 0)
						{
							this->BatchConvert->InputFolder = sVal;
						}
						else if(String::Compare(sArg, "Forms.BatchConvert.OutputFolder", true) == 0)
						{
							this->BatchConvert->OutputFolder = sVal;
						}
						else if(String::Compare(sArg, "Forms.BatchConvert.ToVTF", true) == 0)
						{
							this->BatchConvert->ToVTF = Convert::ToBoolean(sVal);
						}
						else if(String::Compare(sArg, "Forms.BatchConvert.ToVTFFilter", true) == 0)
						{
							this->BatchConvert->ToVTFFilter = sVal;
						}
						else if(String::Compare(sArg, "Forms.BatchConvert.FromVTFFormat", true) == 0)
						{
							this->BatchConvert->FromVTFFormat = sVal;
						}
						else if(String::Compare(sArg, "Forms.BatchConvert.FromVTFFilter", true) == 0)
						{
							this->BatchConvert->FromVTFFilter = sVal;
						}
						else if(String::Compare(sArg, "Forms.BatchConvert.Recurse", true) == 0)
						{
							this->BatchConvert->Recurse = Convert::ToBoolean(sVal);
						}
						else if(String::Compare(sArg, "Forms.BatchConvert.CreateVMTFiles", true) == 0)
						{
							this->BatchConvert->CreateVMTFiles = Convert::ToBoolean(sVal);
						}

						else if(String::Compare(sArg, "Forms.WADConvert.WADFile", true) == 0)
						{
							this->WADConvert->WADFile = sVal;
						}
						else if(String::Compare(sArg, "Forms.WADConvert.OutputFolder", true) == 0)
						{
							this->WADConvert->OutputFolder = sVal;
						}
						else if(String::Compare(sArg, "Forms.WADConvert.CreateVMTFiles", true) == 0)
						{
							this->WADConvert->CreateVMTFiles = Convert::ToBoolean(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.NormalFormat", true) == 0)
						{
							this->Options->NormalFormat = (VTFImageFormat)Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.AlphaFormat", true) == 0)
						{
							this->Options->AlphaFormat = (VTFImageFormat)Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.TextureType", true) == 0)
						{
							this->Options->TextureType = Convert::ToInt32(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.Resize", true) == 0)
						{
							this->Options->ResizeImage = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.ResizeMethod", true) == 0)
						{
							this->Options->ResizeMethod = (VTFResizeMethod)Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.ResizeFilter", true) == 0)
						{
							this->Options->ResizeFilter = (VTFResizeFilter)Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.ResizeClamp", true) == 0)
						{
							this->Options->ResizeClamp = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.ResizeClampWidth", true) == 0)
						{
							this->Options->ResizeClampWidth = Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.ResizeClampHeight", true) == 0)
						{
							this->Options->ResizeClampHeight = Convert::ToInt32(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.GenerateMipmaps", true) == 0)
						{
							this->Options->GenerateMipmaps = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.MipmapFilter", true) == 0)
						{
							this->Options->MipmapFilter = (VTFMipmapFilter)Convert::ToInt32(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.GenerateNormalMap", true) == 0)
						{
							this->Options->ConvertToNormalMap = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.HeightConversionMethod", true) == 0)
						{
							this->Options->HeightConversionMethod = (VTFHeightConversionMethod)Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.AlphaResult", true) == 0)
						{
							this->Options->AlphaResult = (VTFNormalAlphaResult)Convert::ToInt32(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.NormalWrap", true) == 0)
						{
							this->Options->NormalWrap = Convert::ToByte(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.Version", true) == 0)
						{
							this->Options->Version = sVal;
						}

						else if(String::Compare(sArg, "VTFOptions.ComputeReflectivity", true) == 0)
						{
							this->Options->ComputeReflectivity = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.GenerateThumbnail", true) == 0)
						{
							this->Options->GenerateThumbnail = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.GenerateSphereMap", true) == 0)
						{
							this->Options->GenerateSphereMap = Convert::ToByte(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.DXTQuality", true) == 0)
						{
							this->Options->DXTQuality = (VTFDXTQuality)Convert::ToInt32(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.CorrectGamma", true) == 0)
						{
							this->Options->CorrectGamma = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.GammaCorrection", true) == 0)
						{
							this->Options->GammaCorrection = Convert::ToSingle(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.LuminanceWeightR", true) == 0)
						{
							this->Options->LuminanceWeightR = Convert::ToSingle(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.LuminanceWeightG", true) == 0)
						{
							this->Options->LuminanceWeightG = Convert::ToSingle(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.LuminanceWeightB", true) == 0)
						{
							this->Options->LuminanceWeightB = Convert::ToSingle(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.UnsharpenMaskRadius", true) == 0)
						{
							this->Options->UnsharpenMaskRadius = Convert::ToSingle(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.UnsharpenMaskAmount", true) == 0)
						{
							this->Options->UnsharpenMaskAmount = Convert::ToSingle(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.UnsharpenMaskThreshold", true) == 0)
						{
							this->Options->UnsharpenMaskThreshold = Convert::ToSingle(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.XSharpenStrength", true) == 0)
						{
							this->Options->XSharpenStrength = Convert::ToSingle(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.XSharpenThreshold", true) == 0)
						{
							this->Options->XSharpenThreshold = Convert::ToSingle(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.CreateLODControlResource", true) == 0)
						{
							this->Options->CreateLODControlResource = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.LODControlClampU", true) == 0)
						{
							this->Options->LODControlClampU = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.LODControlClampV", true) == 0)
						{
							this->Options->LODControlClampV = Convert::ToByte(sVal);
						}

						else if(String::Compare(sArg, "VTFOptions.CreateInformationResource", true) == 0)
						{
							this->Options->CreateInformationResource = Convert::ToByte(sVal);
						}
						else if(String::Compare(sArg, "VTFOptions.InformationAuthor", true) == 0)
						{
							this->Options->InformationAuthor = sVal;
						}
						else if(String::Compare(sArg, "VTFOptions.InformationContact", true) == 0)
						{
							this->Options->InformationContact = sVal;
						}
						else if(String::Compare(sArg, "VTFOptions.InformationVersion", true) == 0)
						{
							this->Options->InformationVersion = sVal;
						}
						else if(String::Compare(sArg, "VTFOptions.InformationModification", true) == 0)
						{
							this->Options->InformationModification = sVal;
						}
						else if(String::Compare(sArg, "VTFOptions.InformationDescription", true) == 0)
						{
							this->Options->InformationDescription = sVal;
						}
						else if(String::Compare(sArg, "VTFOptions.InformationComments", true) == 0)
						{
							this->Options->InformationComments = sVal;
						}

						else if(String::Compare(sArg, "RecentFiles.Maximum", true) == 0)
						{
							this->uiMaximumRecentFiles = Convert::ToUInt32(sVal);

							if(this->uiMaximumRecentFiles > 16)
							{
								this->uiMaximumRecentFiles = 16;
							}
						}
						else if(String::Compare(sArg, "RecentFiles.File", true) == 0 && System::IO::File::Exists(sVal))
						{
							this->AddRecentFile(sVal);
						}
					}
					catch(Exception^)
					{
						continue;
					}
				}
			}
			catch(Exception^)
			{
				ConfigFile->Close();
				return false;
			}

			ConfigFile->Close();

			return true;
		}

		private: System::Void Control_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e)
		{
			array<String^>^ lpFiles = safe_cast<array<String^>^>(e->Data->GetData(System::Windows::Forms::DataFormats::FileDrop));
			if( lpFiles && lpFiles->Length > 0)
			{
				this->Open(lpFiles[0], false);
			}
		}

		private: System::Void Control_DragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e)
		{
			if(e->Data->GetDataPresent(System::Windows::Forms::DataFormats::FileDrop, false))
			{
				array<String^>^ lpFiles = safe_cast<array<String^>^>(e->Data->GetData(System::Windows::Forms::DataFormats::FileDrop));
				if(lpFiles->Length > 0)
				{
					if(!System::IO::Directory::Exists(lpFiles[0]))
					{
						if(lpFiles[0]->ToLower()->EndsWith(".vmt") ||
							lpFiles[0]->ToLower()->EndsWith(".vtf"))
						{
							e->Effect = System::Windows::Forms::DragDropEffects::All;
						}
					}
				}
			}
		}
	};
}