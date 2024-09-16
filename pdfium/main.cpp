#include "fpdfview.h"
#include "fpdf_save.h"
#include "fpdf_edit.h"
#include <iostream>
#include <cstdio>

struct FileWriter : public FPDF_FILEWRITE
{
    FILE *file;

    // Static function to write a block of data
    static int WriteBlock(FPDF_FILEWRITE *file_write, const void *data, unsigned long size)
    {
        FileWriter *writer = reinterpret_cast<FileWriter *>(file_write);
        return fwrite(data, 1, size, writer->file) == size;
    }

    // Constructor
    FileWriter(FILE *file) : file(file)
    {
        // Initialize FPDF_FILEWRITE's WriteBlock function pointer directly
        FPDF_FILEWRITE::WriteBlock = WriteBlock;
    }
};

int main()
{
    FPDF_InitLibrary();

    FPDF_DOCUMENT pdf_doc = FPDF_CreateNewDocument();
    FPDF_PAGE page = FPDFPage_New(pdf_doc, 0, 612, 792); // A4 Page

    // Add some text or content here if necessary
    std::cout << "Hello, World! PDF created with PDFium!" << std::endl;

    // Save the PDF
    FILE *file = fopen("hello_world_pdfium.pdf", "wb");
    if (!file)
    {
        std::cerr << "Failed to open file for writing." << std::endl;
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

    fclose(file);
    FPDF_CloseDocument(pdf_doc);
    FPDF_DestroyLibrary();
    return 0;
}
