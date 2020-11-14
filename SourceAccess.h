//Submodule file

#ifndef SOURCEACCESS_H
#define SOURCEACCESS_H

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

class SourceAccess {
    public:

        int Open(const std::string& fileName);

        std::string GetValue(const std::string& dataId) const;

        void Print(bool printIds = false) const;

        int Size() const;

    private:

        const std::string PARENT_DIRECTORY = "./data/";

        fs::path filePath;

        struct DataPoint {
            std::string id;
            std::string value;
        };

        std::vector<DataPoint> dataPoints;

        int IndexFromId(const std::string& dataId) const;
};

#endif
