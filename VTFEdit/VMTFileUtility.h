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

	ref class VMTSyntaxHighlighter sealed : FastColoredTextBoxNS::SyntaxHighlighter, System::Collections::Generic::IEnumerable<FastColoredTextBoxNS::AutocompleteItem^>
	{
		System::Text::RegularExpressions::Regex^ Comment;
		FastColoredTextBoxNS::Style^ CommentStyle;
		System::Text::RegularExpressions::Regex^ Error1;
		System::Text::RegularExpressions::Regex^ Error2;
		System::Text::RegularExpressions::Regex^ Number;
		System::Text::RegularExpressions::Regex^ Str;
		FastColoredTextBoxNS::Style^ ErrorStyle;
		System::Text::RegularExpressions::Regex^ ShaderKeyWords;
		FastColoredTextBoxNS::Style^ ShaderKeyWordsStyle;
		System::Text::RegularExpressions::Regex^ ShaderNames;
		FastColoredTextBoxNS::Style^ ShaderNamesStyle;
		System::Text::RegularExpressions::Regex^ ToolKeyWords;
		FastColoredTextBoxNS::Style^ ToolKeyWordsStyle;
		System::Text::RegularExpressions::Regex^ ProxyKeyWords;
		FastColoredTextBoxNS::Style^ ProxyStyle;

		value class KeyWord
		{
		public:
			KeyWord( String^ s, bool stat ) : isStatic( stat )
			{
				word = gcnew FastColoredTextBoxNS::AutocompleteItem( s );
			}
			FastColoredTextBoxNS::AutocompleteItem^ word;
			bool isStatic;
		};
		System::Collections::Generic::List<KeyWord>^ keyWords;

	public:
		explicit VMTSyntaxHighlighter( FastColoredTextBoxNS::FastColoredTextBox^ currentTb ) : SyntaxHighlighter( currentTb )
		{
			using namespace FastColoredTextBoxNS;
			using namespace System::Drawing;
			using namespace System::Collections::Generic;
			using namespace System::Text::RegularExpressions;

			keyWords = gcnew System::Collections::Generic::List<KeyWord>();

			Comment = gcnew Regex( R"X((?://)+.*)X", RegexOptions::Compiled );
			Number = gcnew Regex( R"X(\b\d+[\.]?\d*\b)X", RegexOptions::Compiled );
			Str = gcnew Regex( R"X("(?<range>.*?[^\\])")X", RegexOptions::Compiled );
			Error1 = gcnew Regex( R"X((?<=^|\s)(?=[^"])(?>[\$\%]?[\w_.\/\\]*)(?=["]))X", RegexOptions::Compiled );
			Error2 = gcnew Regex( R"X((?<=["])(?>[\$\%]?[\w_.\/\\]*)(?=([^"]|$))\b)X", RegexOptions::Compiled );

			String^ path = IO::Path::Combine( System::Windows::Forms::Application::StartupPath, "ShaderKeywords.ini" );
			if ( IO::File::Exists( path ) )
			{
				auto highlightFile = gcnew IO::StreamReader( path, true );
				auto words = gcnew List<String^>();
				String^ line;
				while ( ( line = highlightFile->ReadLine() ) )
					words->Add( line->Trim() );
				highlightFile->Close();
				auto w = String::Join( "|", words );
				ShaderKeyWords = gcnew Regex( String::Format( R"X(\B(?<range>\$({0}))\b)X", w ), RegexOptions::Compiled | RegexOptions::IgnoreCase );
				for each ( String^ s in words )
					keyWords->Add( KeyWord( String::Format( "${0}", s ), true ) );
			}

			path = IO::Path::Combine( System::Windows::Forms::Application::StartupPath, "ToolKeywords.ini" );
			if ( IO::File::Exists( path ) )
			{
				auto highlightFile = gcnew IO::StreamReader( path, true );
				auto words = gcnew List<String^>();
				String^ line;
				while ( ( line = highlightFile->ReadLine() ) )
					words->Add( line->Trim() );
				highlightFile->Close();
				auto w = String::Join( "|", words );
				ToolKeyWords = gcnew Regex( String::Format( R"X(\B(?<range>%({0}))\b)X", w ), RegexOptions::Compiled | RegexOptions::IgnoreCase );
				for each ( String^ s in words )
					keyWords->Add( KeyWord( String::Format( "%{0}", s ), true ) );
			}

			path = IO::Path::Combine( System::Windows::Forms::Application::StartupPath, "Proxies.ini" );
			if ( IO::File::Exists( path ) )
			{
				auto highlightFile = gcnew IO::StreamReader( path, true );
				auto words = gcnew List<String^>();
				String^ line;
				while ( ( line = highlightFile->ReadLine() ) )
					words->Add( line->Trim() );
				highlightFile->Close();
				auto w = String::Join( "|", words );
				ProxyKeyWords = gcnew Regex( String::Format( R"X(\b(?<range>({0}))\b)X", w ), RegexOptions::Compiled | RegexOptions::IgnoreCase );
				for each ( String^ s in words )
					keyWords->Add( KeyWord( s, true ) );
			}

			path = IO::Path::Combine( System::Windows::Forms::Application::StartupPath, "ShaderNames.ini" );
			if ( IO::File::Exists( path ) )
			{
				auto highlightFile = gcnew IO::StreamReader( path, true );
				auto words = gcnew List<String^>();
				String^ line;
				while ( ( line = highlightFile->ReadLine() ) )
					words->Add( line->Trim() );
				highlightFile->Close();
				auto w = String::Join( "|", words );
				ShaderNames = gcnew Regex( String::Format( R"X(\b(?<range>({0}))\b)X", w ), RegexOptions::Compiled | RegexOptions::IgnoreCase );
				for each ( String^ s in words )
					keyWords->Add( KeyWord( s, true ) );
			}

			auto colors = gcnew Dictionary<String^, Color>( StringComparer::InvariantCultureIgnoreCase );
			path = IO::Path::Combine( System::Windows::Forms::Application::StartupPath, "HighlightColors.ini" );
			if ( IO::File::Exists( path ) )
			{
				auto parseColor = gcnew Regex( R"X(^\s*(.*)\s*=\s*(\d{1,3}\s+\d{1,3}\s+\d{1,3})\s*$)X" );
				auto highlightFile = gcnew IO::StreamReader( path, true );
				String^ line;
				while ( ( line = highlightFile->ReadLine() ) )
				{
					auto match = parseColor->Match( line );
					if ( match->Groups->Count != 3 )
						continue;
					array<String^>^ s = { " " };
					auto val = match->Groups[2]->Value->Split( s, StringSplitOptions::RemoveEmptyEntries );
					if ( val->Length >= 3 )
						colors[match->Groups[1]->Value->Trim()] = Color::FromArgb( Int32::Parse( val[0] ), Int32::Parse( val[1] ), Int32::Parse( val[2] ) );
				}
			}

			Color clr;

			if ( colors->TryGetValue( "Comment", clr ) )
				CommentStyle = gcnew TextStyle( gcnew SolidBrush( clr ), nullptr, FontStyle::Italic );
			else
				CommentStyle = GreenStyle;

			if ( colors->TryGetValue( "ShaderParam", clr ) )
				ShaderKeyWordsStyle = gcnew TextStyle( gcnew SolidBrush( clr ), nullptr, FontStyle::Bold );
			else
				ShaderKeyWordsStyle = BlueStyle;

			if ( colors->TryGetValue( "ShaderName", clr ) )
				ShaderNamesStyle = gcnew TextStyle( gcnew SolidBrush( clr ), nullptr, FontStyle::Bold );
			else
				ShaderNamesStyle = GrayStyle;

			if ( colors->TryGetValue( "ToolParam", clr ) )
				ToolKeyWordsStyle = gcnew TextStyle( gcnew SolidBrush( clr ), nullptr, FontStyle::Bold );
			else
				ToolKeyWordsStyle = MaroonStyle;

			if ( colors->TryGetValue( "Error", clr ) )
				ErrorStyle = gcnew TextStyle( gcnew SolidBrush( clr ), nullptr, FontStyle::Regular );
			else
				ErrorStyle = RedStyle;

			if ( colors->TryGetValue( "Proxy", clr ) )
				ProxyStyle = gcnew TextStyle( gcnew SolidBrush( clr ), nullptr, FontStyle::Regular );
			else
				ProxyStyle = MagentaStyle;

			StringStyle = gcnew TextStyle( gcnew SolidBrush( Color::FromArgb( 0xaa, 0x51, 0x1e ) ), nullptr, FontStyle::Regular );
			NumberStyle = gcnew TextStyle( gcnew SolidBrush( Color::FromArgb( 167, 161, 87 ) ), nullptr, FontStyle::Regular );
		}

		void HighlightSyntax( FastColoredTextBoxNS::Language language, FastColoredTextBoxNS::Range^ range ) override
		{
			range->tb->CommentPrefix = "//";
			range->tb->LeftBracket = L'[';
			range->tb->RightBracket = L']';
			range->tb->BracketsHighlightStrategy = FastColoredTextBoxNS::BracketsHighlightStrategy::Strategy2;

			range->ClearStyle( CommentStyle, ErrorStyle, ShaderKeyWordsStyle, ShaderNamesStyle, ToolKeyWordsStyle, ProxyStyle, NumberStyle, StringStyle );

			range->SetStyle( CommentStyle, Comment );

			range->SetStyle( ErrorStyle, Error1 );
			range->SetStyle( ErrorStyle, Error2 );

			if ( ShaderKeyWords )
				range->SetStyle( ShaderKeyWordsStyle, ShaderKeyWords );

			if ( ShaderNames )
				range->SetStyle( ShaderNamesStyle, ShaderNames );

			if ( ToolKeyWords )
				range->SetStyle( ToolKeyWordsStyle, ToolKeyWords );

			if ( ProxyKeyWords )
				range->SetStyle( ProxyStyle, ProxyKeyWords );

			range->SetStyle( NumberStyle, Number );
			range->SetStyle( StringStyle, Str );

			range->ClearFoldingMarkers();
			range->SetFoldingMarkers( "{", "}" );
		}

		void AutoIndentNeeded( System::Object^ sender, FastColoredTextBoxNS::AutoIndentEventArgs^ args ) override
		{

		}

		virtual System::Collections::Generic::IEnumerator<FastColoredTextBoxNS::AutocompleteItem^>^ GetEnumerator()
		{
			return gcnew VMTKeyEnumerator( this );
		}

		virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
		{
			return GetEnumerator();
		}

	private:
		ref class VMTKeyEnumerator : System::Collections::Generic::IEnumerator<FastColoredTextBoxNS::AutocompleteItem^>
		{
			System::Collections::Generic::IEnumerator<KeyWord>^ keyWords;
		public:
			VMTKeyEnumerator( VMTSyntaxHighlighter^ parent ) : keyWords( parent->keyWords->GetEnumerator() ) {}
			~VMTKeyEnumerator() {}

			virtual bool MoveNext()
			{
				return keyWords->MoveNext();
			}

			virtual void Reset()
			{
				keyWords->Reset();
			}

			property FastColoredTextBoxNS::AutocompleteItem^ Current
			{
				virtual FastColoredTextBoxNS::AutocompleteItem^ get()
				{
					return keyWords->Current.word;
				}
			}

			property Object^ Current2
			{
				virtual Object^ get() = System::Collections::IEnumerator::Current::get
				{
					return Current;
				}
			}
		};
	};
}