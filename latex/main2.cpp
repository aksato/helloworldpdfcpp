#include <inja/inja.hpp>
#include <iostream>
#include <fstream>

int main()
{
    // LaTeX template with placeholders
    std::string latexTemplate = R"(\documentclass{article}
\title{ {{ title }} }
\author{ {{ author }} }
\date{ {{ date }} }

\begin{document}
\maketitle
{{ content }}
\end{document})";

    // Data to fill the template
    nlohmann::json data;
    data["title"] = "My Report";
    data["author"] = "John Doe";
    data["date"] = "September 2024";
    data["content"] = "Hello World! This is an auto-generated LaTeX report.";

    // Render the LaTeX document
    inja::Environment env;
    std::string renderedLatex = env.render(latexTemplate, data);

    // Write the output to a .tex file
    std::ofstream texFile("hello_world_latex2.tex");
    texFile << renderedLatex;
    texFile.close();

    // Compile LaTeX to PDF
    system("pdflatex hello_world_latex2.tex");

    std::cout << "PDF generated successfully!" << std::endl;
    return 0;
}
