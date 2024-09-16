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

    // Save the PDF document to a file
    HPDF_SaveToFile(pdf, "hello_world_libharu.pdf");

    // Close the PDF document
    HPDF_Free(pdf);

    return 0;
}