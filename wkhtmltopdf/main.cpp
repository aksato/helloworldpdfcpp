#include <iostream>
#include <fstream>
#include <cstdlib>

int main()
{
    // Step 1: Create a simple HTML file
    std::ofstream htmlFile("hello_world_wkhtmltopdf.html");
    htmlFile << "<html><body><h1>Hello World</h1></body></html>";
    htmlFile.close();

    // Step 2: Call wkhtmltopdf to convert HTML to PDF
    std::string command = "wkhtmltopdf hello_world_wkhtmltopdf.html hello_world_wkhtmltopdf.pdf";
    int result = system(command.c_str());

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
