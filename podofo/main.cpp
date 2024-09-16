/**
 * Copyright (C) 2006 by Dominik Seichter <domseichter@web.de>
 *
 * Licensed under GNU General Public License 2.0 or later.
 * Some rights reserved. See COPYING, AUTHORS.
 */

// Include the standard headers for cout to write
// some output to the console.
#include <iostream>

// Now include all PoDoFo header files, to have access
// to all functions of PoDoFo and so that you do not have
// to care about the order of includes.
//
// You should always use podofo.h and not try to include
// the required headers on your own.
#include <podofo/podofo.h>

// All PoDoFo classes are member of the PoDoFo namespace.
using namespace std;
using namespace PoDoFo;

void HelloWorld(const string_view &filename)
{
    PdfMemDocument document;

    // PdfPainter is the class which is able to draw text and graphics
    // directly on a PdfPage object.
    PdfPainter painter;

    // A PdfFont object is required to draw text on a PdfPage using a PdfPainter.
    // PoDoFo will find the font using fontconfig on your system and embed truetype
    // fonts automatically in the PDF file.
    PdfFont *font;

    try
    {
        // The PdfDocument object can be used to create new PdfPage objects.
        // The PdfPage object is owned by the PdfDocument will also be deleted automatically
        // by the PdfDocument object.
        //
        // You have to pass only one argument, i.e. the page size of the page to create.
        // There are predefined enums for some common page sizes.
        // auto &page = document.GetPages().CreatePage(PdfPageSize::A4);
        auto &page = document.GetPages().CreatePage(Rect(0, 0, 595, 842));

        // If the page cannot be created because of an error (e.g. ePdfError_OutOfMemory )
        // a nullptr pointer is returned.
        // We check for a nullptr pointer here and throw an exception using the RAISE_ERROR macro.
        // The raise error macro initializes a PdfError object with a given error code and
        // the location in the file in which the error occurred and throws it as an exception.

        // Set the page as drawing target for the PdfPainter.
        // Before the painter can draw, a page has to be set first.
        painter.SetCanvas(page);

        // Create a PdfFont object using the font "Arial".
        // The font is found on the system using fontconfig and embedded into the
        // PDF file. If Arial is not available, a default font will be used.
        //
        // The created PdfFont will be deleted by the PdfDocument.
        font = document.GetFonts().SearchFont("Arial");

        // If the PdfFont object cannot be allocated return an error.
        if (font == nullptr)
            throw runtime_error("Invalid handle");

        auto &metrics = font->GetMetrics();
        cout << "The font name is " << metrics.GetFontName() << endl;
        cout << "The family font name is " << metrics.GetFontFamilyName() << endl;
        cout << "The font file path is " << metrics.GetFilePath() << endl;
        cout << "The font face index is " << metrics.GetFaceIndex() << endl;

        // Set the font as default font for drawing.
        // A font has to be set before you can draw text on
        // a PdfPainter.
        painter.TextState.SetFont(*font, 18.0);

        // You could set a different color than black to draw
        // the text.
        //
        // painter.SetColor(1.0, 0.0, 0.0);

        // Actually draw the line "Hello World!" on to the PdfPage at
        // the position 2cm,2cm from the top left corner.
        // Please remember that PDF files have their origin at the
        // bottom left corner. Therefore we substract the y coordinate
        // from the page height.
        //
        // The position specifies the start of the baseline of the text.
        //
        // All coordinates in PoDoFo are in PDF units.
        painter.DrawText("Hello World!", 56.69, page.GetRect().Height - 56.69);

        painter.FinishDrawing();

        // The last step is to close the document.
        document.Save(filename);
    }
    catch (PdfError &e)
    {
        // All PoDoFo methods may throw exceptions
        // make sure that painter.FinishPage() is called
        // or who will get an assert in its destructor
        try
        {
            painter.FinishDrawing();
        }
        catch (...)
        {
            // Ignore errors this time
        }

        throw;
    }
}

int main(int argc, char *argv[])
{
    // All PoDoFo functions will throw an exception in case of an error.
    //
    // You should catch the exception to either fix it or report
    // back to the user.
    //
    // All exceptions PoDoFo throws are objects of the class PdfError.
    // Thats why we simply catch PdfError objects.
    try
    {
        // Call the drawing routing which will create a PDF file
        // with the filename of the output file as argument.
        HelloWorld("hello_world_podofo.pdf");
    }
    catch (PdfError &err)
    {
        // We have to check if an error has occurred.
        // If yes, we return and print an error message
        // to the commandline.
        err.PrintErrorMsg();
        return (int)err.GetCode();
    }

    // The PDF was created successfully.
    std::cout << std::endl
              << "Created a PDF file containing the line \"Hello World!\": " << argv[1] << std::endl
              << std::endl;

    return 0;
}