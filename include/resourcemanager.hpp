#ifndef PW_RESOURCEMANAGER_HPP
#define PW_RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include "imagedata.hpp"

namespace pipeworks {

class ResourceManager {
  private:
    std::map<std::string, ImageData> loaded_imagedata;
  public:
    ResourceManager();
    ImageData &get_imagedata(std::string name);
    bool is_imagedata_loaded(std::string name);
};

extern ResourceManager g_resourcemanager;

}

#endif // PW_RESOURCEMANAGER_HPP
