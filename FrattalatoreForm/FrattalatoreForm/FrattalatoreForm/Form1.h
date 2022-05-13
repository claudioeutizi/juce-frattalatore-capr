#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Resources;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^ fractalChoice;


	private: System::Windows::Forms::Button^ generateButton;

	private: System::Windows::Forms::Label^ fractalLabel;
	private: System::Windows::Forms::Label^ FrattalatoreLabel;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->fractalChoice = (gcnew System::Windows::Forms::ComboBox());
			this->generateButton = (gcnew System::Windows::Forms::Button());
			this->fractalLabel = (gcnew System::Windows::Forms::Label());
			this->FrattalatoreLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// fractalChoice
			// 
			this->fractalChoice->Font = (gcnew System::Drawing::Font(L"Stencil", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fractalChoice->FormattingEnabled = true;
			this->fractalChoice->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Mandelbrot set", L"Julia set 1", L"Julia set 2",
					L"Burning Ship"
			});
			this->fractalChoice->Location = System::Drawing::Point(210, 502);
			this->fractalChoice->Name = L"fractalChoice";
			this->fractalChoice->Size = System::Drawing::Size(197, 32);
			this->fractalChoice->TabIndex = 0;
			this->fractalChoice->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::fractalChoice_SelectedIndexChanged);
			// 
			// generateButton
			// 
			this->generateButton->AutoSize = true;
			this->generateButton->Font = (gcnew System::Drawing::Font(L"Stencil", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->generateButton->Location = System::Drawing::Point(252, 658);
			this->generateButton->Name = L"generateButton";
			this->generateButton->Size = System::Drawing::Size(119, 34);
			this->generateButton->TabIndex = 2;
			this->generateButton->Text = L"Generate";
			this->generateButton->UseVisualStyleBackColor = true;
			this->generateButton->Click += gcnew System::EventHandler(this, &Form1::generateButton_Click);
			// 
			// fractalLabel
			// 
			this->fractalLabel->BackColor = System::Drawing::Color::Transparent;
			this->fractalLabel->Font = (gcnew System::Drawing::Font(L"Stencil", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->fractalLabel->Location = System::Drawing::Point(206, 476);
			this->fractalLabel->Name = L"fractalLabel";
			this->fractalLabel->Size = System::Drawing::Size(201, 23);
			this->fractalLabel->TabIndex = 3;
			this->fractalLabel->Text = L"Fractal choice";
			this->fractalLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// FrattalatoreLabel
			// 
			this->FrattalatoreLabel->AutoSize = true;
			this->FrattalatoreLabel->BackColor = System::Drawing::Color::Transparent;
			this->FrattalatoreLabel->Font = (gcnew System::Drawing::Font(L"Stencil", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FrattalatoreLabel->Location = System::Drawing::Point(194, 350);
			this->FrattalatoreLabel->Name = L"FrattalatoreLabel";
			this->FrattalatoreLabel->Size = System::Drawing::Size(222, 33);
			this->FrattalatoreLabel->TabIndex = 3;
			this->FrattalatoreLabel->Text = L"Frattalatore";
			this->FrattalatoreLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(Image::FromFile("..\\..\\Capr_Frattalatore_Background.bmp")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(604, 704);
			this->Controls->Add(this->FrattalatoreLabel);
			this->Controls->Add(this->fractalLabel);
			this->Controls->Add(this->generateButton);
			this->Controls->Add(this->fractalChoice);
			this->Name = L"Form1";
			this->Text = L"Frattalatore Form";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void fractalChoice_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		}
		private: System::Void generateButton_Click(System::Object^ sender, System::EventArgs^ e) {
		}
	};
}
