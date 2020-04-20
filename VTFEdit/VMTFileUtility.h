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

#include "VTFLib.h"

using namespace System;

enum EToken
{
	TOKEN_EOF = 0,			// No more tokens to read.
	TOKEN_NEWLINE,			// Token is a newline (\n).
	TOKEN_WHITESPACE,		// Token is any whitespace other than a newline.
	TOKEN_FORWARD_SLASH,	// Token is a forward slash (/).
	TOKEN_QUOTE,			// Token is a quote (").
	TOKEN_OPEN_BRACE,		// Token is an open brace ({).
	TOKEN_CLOSE_BRACE,		// Token is a close brace (}).
	TOKEN_CHAR,				// Token is a char (any char).  Use GetChar().
	TOKEN_STRING,			// Token is a string.  Use GetString().
	TOKEN_SPECIAL			// Token is a specified special char.
};

namespace VTFEdit
{
	ref class CVMTFileUtility
	{
	public:
		static System::String^ GetTexturePathFromSystemPath(System::String^ sTexture)
		{
			if(sTexture->Length == 0)
				return "";

			System::String^ sExtension = ".vtf";
			System::String^ sMaterials = "materials";

			sTexture = sTexture->Trim();
			sTexture = sTexture->Replace("\\", "/");
			sTexture = sTexture->Replace("//", "/");
			if(sTexture->Length >= 4 && String::Compare(sTexture, sTexture->Length - sExtension->Length, sExtension, 0, sExtension->Length, true) == 0)
			{
				sTexture = sTexture->Substring(0, sTexture->Length - sExtension->Length);
				sTexture = sTexture->Trim();
			}

			int index = sTexture->IndexOf(":");
			if(index != -1)
			{
				sTexture = sTexture->Substring(index + 1);
			}

			for(int i = 0; i <= sTexture->Length - sMaterials->Length; i++)
			{
				if(String::Compare(sTexture, i, sMaterials, 0, sMaterials->Length, true) == 0)
				{
					sTexture = sTexture->Substring(i + sMaterials->Length);
					i = 0;
				}
			}

			while(sTexture->StartsWith("/"))
			{
				sTexture = sTexture->Substring(1);
			}

			while(sTexture->EndsWith("/"))
			{
				sTexture = sTexture->Substring(0, sTexture->Length - 1);
			}

			return sTexture;
		}

		static bool CreateDefaultMaterial(System::String^ sVTFFile, System::String^ sShader)
		{
			return CreateDefaultMaterial(sVTFFile, sShader, false);
		}

		static bool CreateDefaultMaterial(System::String^ sVTFFile, System::String^ sShader, bool bHasAlpha)
		{
			System::String^ sVMTFile = sVTFFile;

			if(sVMTFile->Length < 4 || String::Compare(sVMTFile, sVMTFile->Length - 4, ".vtf", 0, 4, true) != 0)
			{
				return false;
			}

			sVMTFile = String::Concat(sVMTFile->Substring(0, sVMTFile->Length - 4), ".vmt");

			if(System::IO::File::Exists(sVMTFile))
			{
				return false;
			}

			vlBool bResult;
			char *cTemp0, *cTemp1;
			VTFLib::CVMTFile VMTFile;

			cTemp0 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sShader).ToPointer();
			VMTFile.Create(cTemp0);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp0);

			cTemp0 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi("$basetexture").ToPointer();
			cTemp1 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(CVMTFileUtility::GetTexturePathFromSystemPath(sVTFFile)).ToPointer();
			VMTFile.GetRoot()->AddStringNode(cTemp0, cTemp1);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp1);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp0);

			if(bHasAlpha)
			{
				cTemp0 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi("$translucent").ToPointer();
				VMTFile.GetRoot()->AddIntegerNode(cTemp0, 1);
				System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp0);
			}

			cTemp0 = (char *)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(sVMTFile).ToPointer();
			bResult = VMTFile.Save(cTemp0);
			System::Runtime::InteropServices::Marshal::FreeHGlobal((IntPtr)cTemp0);

			return bResult != 0;
		}
	};

	ref class VMTSyntaxHighlighter sealed : FastColoredTextBoxNS::SyntaxHighlighter
	{
	public:
		explicit VMTSyntaxHighlighter( FastColoredTextBoxNS::FastColoredTextBox^ currentTb ) : SyntaxHighlighter( currentTb ) {}

	};
}