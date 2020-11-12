//Submodule file

#include <iostream>
#include <fstream>

#include "SourceAccess.h"

void SourceAccess::Open(std::string fileName) {

    filePath = PARENT_DIRECTORY + fileName;

    if(filePath.extension() == "") {
        filePath += ".txt";
    }

    std::ifstream inFile;
    unsigned int size = 0;
    DataPoint newData;
    
    if(fs::exists(filePath) == true) {

        inFile.open(filePath);
        if(inFile.is_open() == false) {
            throw -1;
        }

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
    }

    else {//If the file doesn't exist, try to create it

        fs::create_directories(filePath.parent_path());
        
        std::ofstream tempStream;
        tempStream.open(filePath);
        if(tempStream.is_open() == false) {//If it fails again throw an error
            throw "File creation failed";
        }
        tempStream << 0 << std::endl;
        tempStream.close();

        dataPoints.resize(0);
    }
}

void SourceAccess::Save() const {
    std::ofstream outFile;

    outFile.open(filePath);
    if(outFile.is_open() == false) {
        throw "File creation failed";
    }

    outFile << dataPoints.size() << std::endl;

    for(DataPoint data : dataPoints) {
        outFile << data.id << " " << data.value << std::endl;
    }
}

void SourceAccess::SetValue(std::string dataId, std::string dataValue) {
    int index = IndexFromId(dataId);
    if(index == -1) {//IndexFromId returns -1 if a data point was not found
        DataPoint newDataPoint;
        newDataPoint.id = dataId;
        newDataPoint.value = dataValue;
        dataPoints.push_back(newDataPoint);
    }
    else {
        dataPoints.at(index).value = dataValue;
    }
}

std::string SourceAccess::GetValue(std::string dataId) const {
    int index = IndexFromId(dataId);
    if(index == -1) {//IndexFromId returns -1 if a data point was not found
        return "ERROR: No data point of ID [" + dataId + "] was found in " + filePath.generic_string();
    }
    return dataPoints.at(IndexFromId(dataId)).value;
}

int SourceAccess::Remove(std::string dataId) {
    int index = IndexFromId(dataId);
    if(index == -1) {
        return -1;
    }
    dataPoints.erase(dataPoints.begin() + index);
    return 0;
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