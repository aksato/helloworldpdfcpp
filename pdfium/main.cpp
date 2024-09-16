#include "fpdfview.h"
#include "fpdf_edit.h"
#include "fpdf_save.h"
#include <iostream>
#include <cstdio>

struct FileWriter : public FPDF_FILEWRITE
{
    FILE *file;

    static int WriteBlock(FPDF_FILEWRITE *file_write, const void *data, unsigned long size)
    {
        FileWriter *writer = reinterpret_cast<FileWriter *>(file_write);
        return fwrite(data, 1, size, writer->file) == size;
    }

    FileWriter(FILE *file) : file(file)
    {
        FPDF_FILEWRITE::WriteBlock = WriteBlock;
    }
};

int main()
{
    // Initialize PDFium library
    FPDF_InitLibrary();

    // Create a new PDF document and a page
    FPDF_DOCUMENT pdf_doc = FPDF_CreateNewDocument();
    FPDF_PAGE page = FPDFPage_New(pdf_doc, 0, 612, 792); // A4 Page

    // Create and load a font (this will be a built-in font)
    FPDF_PAGEOBJECT text_object;
    FPDF_FONT font = FPDFText_LoadStandardFont(pdf_doc, "Helvetica");

    if (!font)
    {
        std::cerr << "Failed to load font." << std::endl;
        FPDF_CloseDocument(pdf_doc);
        FPDF_DestroyLibrary();
        return 1;
    }

    // Create a text object
    text_object = FPDFPageObj_CreateTextObj(pdf_doc, font, 24.0f); // Font size 24

    // Set the text string
    FPDF_WIDESTRING wide_text = FPDF_WIDESTRING(L"Hello World"); // UTF-16LE format is required
    FPDFText_SetText(text_object, wide_text);

    // Set the position of the text object (x = 100, y = 700, near the top left)
    FPDFPageObj_Transform(text_object, 1, 0, 0, 1, 100, 700);

    // Add the text object to the page
    FPDFPage_InsertObject(page, text_object);

    // Generate the content of the page
    FPDFPage_GenerateContent(page);

    std::cout << "Hello, World! PDF with text created using PDFium!" << std::endl;

    // Save the PDF to a file
    FILE *file = fopen("hello_world_pdfium.pdf", "wb");
    if (!file)
    {
        std::cerr << "Failed to open file for writing." << std::endl;
        FPDF_CloseDocument(pdf_doc);
        FPDF_DestroyLibrary();
        return 1;
    }

    FileWriter writer(file);
    if (!FPDF_SaveAsCopy(pdf_doc, &writer, 0))
    {
        std::cerr << "Failed to save PDF." << std::endl;
    }
    else
    {
        std::cout << "PDF successfully created!" << std::endl;
    }

    // Close the file and clean up
    fclose(file);
    FPDF_CloseDocument(pdf_doc);
    FPDF_DestroyLibrary();

    return 0;
}
