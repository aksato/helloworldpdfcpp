#include <iostream>
#include <fstream>
#include <cstdlib>

int main()
{
    // Step 1: Create a simple Markdown file
    std::ofstream mdFile("hello_world_pandoc.md");
    mdFile << "# Hello World\n";
    mdFile << "This is a markdown document converted to PDF using Pandoc.";
    mdFile.close();

    // Step 2: Use Pandoc to convert Markdown to PDF
    std::string pandocCommand = "pandoc hello_world_pandoc.md -o hello_world_pandoc.pdf";
    int result = system(pandocCommand.c_str());

    if (result == 0)
    {
        std::cout << "PDF generated successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Failed to generate PDF." << std::endl;
    }

    return result;
}
