find_package(PDFium CONFIG REQUIRED)

add_executable(HelloPDFium main.cpp)

target_link_libraries(HelloPDFium PRIVATE pdfium)