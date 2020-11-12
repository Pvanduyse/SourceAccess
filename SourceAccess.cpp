//Submodule file

#include <iostream>
#include <fstream>

#include "SourceAccess.h"

int SourceAccess::Open(std::string fileName) {
    std::ifstream inFile;
    unsigned int size = 0;
    DataPoint newData;
    fs::path newFilePath = PARENT_DIRECTORY + fileName;

    if(newFilePath.extension() == "") {
        newFilePath += ".txt";
    }
    
    inFile.open(newFilePath);
    if(inFile.is_open() == false) {
        return -1;
    }
    filePath = newFilePath;

    inFile >> size;
    inFile.ignore();
    dataPoints.resize(size);

    for(unsigned int i = 0; i < size; i++) {
        
        inFile >> newData.id;
        inFile.ignore();
        getline(inFile, newData.value);

        dataPoints.at(i) = newData;
    }

    inFile.close();
    return 0;
}

std::string SourceAccess::GetValue(std::string dataId) const {
    int index = IndexFromId(dataId);
    if(index == -1) {//IndexFromId returns -1 if a data point was not found
        return "ERROR: No data point of ID [" + dataId + "] was found in " + filePath.generic_string();
    }
    return dataPoints.at(index).value;
}

void SourceAccess::Print(bool printIds) const {
    for(DataPoint data : dataPoints) {
        if(printIds == true){
            std::cout << data.id << " ";
        }
        std::cout << data.value << std::endl;
    }
}

int SourceAccess::Size() const {
    return dataPoints.size();
}

int SourceAccess::IndexFromId(std::string dataId) const {
    for(unsigned int i = 0; i < dataPoints.size(); ++i) {
        if(dataPoints.at(i).id == dataId) {
            return i;
        }
    }
    return -1;
}