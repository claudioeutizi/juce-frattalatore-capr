#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

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
	private: System::Windows::Forms::NumericUpDown^ numIterations;

	private: System::Windows::Forms::Button^ generateButton;
	private: System::Windows::Forms::Label^ iterationsLabel;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->fractalChoice = (gcnew System::Windows::Forms::ComboBox());
			this->numIterations = (gcnew System::Windows::Forms::NumericUpDown());
			this->generateButton = (gcnew System::Windows::Forms::Button());
			this->iterationsLabel = (gcnew System::Windows::Forms::Label());
			this->fractalLabel = (gcnew System::Windows::Forms::Label());
			this->FrattalatoreLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numIterations))->BeginInit();
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
			// 
			// numIterations
			// 
			this->numIterations->Font = (gcnew System::Drawing::Font(L"Stencil", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->numIterations->Location = System::Drawing::Point(210, 579);
			this->numIterations->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->numIterations->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numIterations->Name = L"numIterations";
			this->numIterations->Size = System::Drawing::Size(197, 31);
			this->numIterations->TabIndex = 1;
			this->numIterations->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
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
			// 
			// iterationsLabel
			// 
			this->iterationsLabel->BackColor = System::Drawing::Color::Transparent;
			this->iterationsLabel->Font = (gcnew System::Drawing::Font(L"Stencil", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->iterationsLabel->Location = System::Drawing::Point(206, 553);
			this->iterationsLabel->Name = L"iterationsLabel";
			this->iterationsLabel->Size = System::Drawing::Size(201, 23);
			this->iterationsLabel->TabIndex = 3;
			this->iterationsLabel->Text = L"Fractal choice";
			this->iterationsLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
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
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(615, 704);
			this->Controls->Add(this->FrattalatoreLabel);
			this->Controls->Add(this->fractalLabel);
			this->Controls->Add(this->iterationsLabel);
			this->Controls->Add(this->generateButton);
			this->Controls->Add(this->numIterations);
			this->Controls->Add(this->fractalChoice);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numIterations))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
