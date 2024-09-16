#include <iostream>
#include <fstream>
#include <cstdlib> // For system()

int main()
{
    // Create and write the LaTeX content into a file
    std::ofstream texFile("hello_world_latex.tex");

    if (!texFile)
    {
        std::cerr << "Failed to create .tex file." << std::endl;
        return 1;
    }

    // Basic LaTeX document content
    texFile << R"(\documentclass{article}
\begin{document}
Hello World!
\end{document})";

    texFile.close();

    // Call pdflatex to generate the PDF
    int result = system("pdflatex hello_world_latex.tex");

    if (result != 0)
    {
        std::cerr << "Failed to compile .tex file to PDF." << std::endl;
        return 1;
    }

    std::cout << "PDF successfully generated!" << std::endl;
    return 0;
}
