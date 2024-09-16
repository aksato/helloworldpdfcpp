#include <iostream>
#include "hpdf.h"

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    std::cerr << "Error: " << error_no << ", detail: " << detail_no << std::endl;
}

int main()
{
    // Create a new PDF document
    HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
    if (!pdf)
    {
        std::cerr << "Failed to create PDF!" << std::endl;
        return 1;
    }

    // Add a new page to the document
    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetWidth(page, 595);
    HPDF_Page_SetHeight(page, 842); // A4 size

    // Set font and font size
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_STATUS status = HPDF_Page_SetFontAndSize(page, font, 12);

    // Begin text on the page
    HPDF_Page_BeginText(page);

    // Set text position
    HPDF_Page_MoveTextPos(page, 200, 800);

    // Add text to the page
    HPDF_Page_ShowText(page, "Hello, World! PDF created with libharu!");

    // End text on the page
    HPDF_Page_EndText(page);

    // Save the PDF document to a file
    HPDF_SaveToFile(pdf, "hello_world_libharu.pdf");

    // Close the PDF document
    HPDF_Free(pdf);

    return 0;
}